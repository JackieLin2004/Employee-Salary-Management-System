#include "system.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <stdexcept>

using namespace std;

// 读取雇员信息的函数
void EmployeeSystem::read_employees(const string &filename) {
    try {
        ifstream infile(filename);
        if (!infile) {
            // 文件出错抛出异常
            throw runtime_error("无法打开文件 " + filename);
        }

        string line, kind, name, sex;
        int year, month, day, lateDays, leaveDays;
        double totalSales, commissionPercent, fixedSal, salesComm, timeWorked, hourlyRate;

        while (infile >> kind) {
            if (kind == "Manager") {
                infile >> name >> sex >> year >> month >> day >> lateDays >> leaveDays;
                employees.push_back(new CManager(name, sex, {year, month, day}, lateDays, leaveDays));
            } else if (kind == "Sales") {
                infile >> name >> sex >> year >> month >> day >> totalSales >> commissionPercent;
                employees.push_back(new CSales(name, sex, {year, month, day}, totalSales, commissionPercent));
            } else if (kind == "Mgr") {
                infile >> name >> sex >> year >> month >> day >> lateDays >> leaveDays >> totalSales
                       >> commissionPercent;
                fixedSal = 0.0;
                salesComm = totalSales * commissionPercent;
                employees.push_back(
                        new CMgr(name, sex, {year, month, day}, lateDays, leaveDays, fixedSal, salesComm, totalSales,
                                 commissionPercent));
            } else if (kind == "Wage") {
                infile >> name >> sex >> year >> month >> day >> totalSales >> commissionPercent >> timeWorked
                       >> hourlyRate;
                salesComm = totalSales * commissionPercent;
                employees.push_back(new CWage(name, sex, {year, month, day}, totalSales, commissionPercent, timeWorked,
                                              hourlyRate));
            }
        }

        infile.close();
    } catch (const exception &e) {
        cerr << "相关异常：" << e.what() << endl;
    }
}

// 保存雇员信息函数，将更新的信息写进文件
void EmployeeSystem::write_employees(const string &filename) const {
    try {
        ofstream outfile(filename);
        if (!outfile) {
            throw runtime_error("无法打开文件" + filename);
        }

        for (const auto &employee: employees) {
            const string &kind = employee->get_kind();
            const string &name = employee->get_name();
            const BDay &birthday = employee->get_birthday();

            if (kind == "Manager") {
                const CManager *mgr = dynamic_cast<const CManager *>(employee);
                if (mgr) {
                    outfile << kind << " " << name << " " << mgr->get_sex() << " "
                            << birthday.year << " " << birthday.month << " " << birthday.day << " "
                            << mgr->get_late() << " " << mgr->get_leave() << endl;
                }
            } else if (kind == "Sales") {
                const CSales *sales = dynamic_cast<const CSales *>(employee);
                if (sales) {
                    outfile << kind << " " << name << " " << sales->get_sex() << " "
                            << birthday.year << " " << birthday.month << " " << birthday.day << " "
                            << sales->get_total_sales() << " " << sales->get_commission_percent() << endl;
                }
            } else if (kind == "Mgr") {
                const CMgr *mgr = dynamic_cast<const CMgr *>(employee);
                if (mgr) {
                    outfile << kind << " " << name << " " << mgr->get_sex() << " "
                            << birthday.year << " " << birthday.month << " " << birthday.day << " "
                            << mgr->get_late() << " " << mgr->get_leave() << " "
                            << mgr->get_total_sales() << " " << mgr->get_commission_percent() << " "
                            << mgr->get_fixed_salary() << " " << mgr->get_sales_commission() << endl;
                }
            } else if (kind == "Wage") {
                const CWage *wage = dynamic_cast<const CWage *>(employee);
                if (wage) {
                    outfile << kind << " " << name << " " << wage->get_sex() << " "
                            << birthday.year << " " << birthday.month << " " << birthday.day << " "
                            << wage->get_total_sales() << " " << wage->get_commission_percent() << " "
                            << wage->get_time() << " " << wage->get_hourly_rate() << endl;
                }
            }
        }

        outfile.close();
    } catch (const exception &e) {
        cerr << "Exception occurred: " << e.what() << endl;
    }
}

// 使用二分查找进行 按姓名查询雇员信息的函数
CEmployee *EmployeeSystem::find_employee_by_name(const string &name) {
    // 先按姓名排序（如果未排序的话）
    sort(employees.begin(), employees.end(), [](CEmployee *a, CEmployee *b) {
        return a->get_name() < b->get_name();
    });

    // 二分查找
    int left = 0;
    int right = employees.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (employees[mid]->get_name() == name) {
            // 找到对应信息并返回
            return employees[mid];
        } else if (employees[mid]->get_name() < name) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    // 没有找到雇员
    return nullptr;
}

// 按照雇员类型来查询信息的函数
vector<CEmployee *> EmployeeSystem::find_employees_by_type(const string &type) {
    vector<CEmployee *> result;
    for (auto &employee: employees) {
        if (employee->get_kind() == type) {
            result.push_back(employee);
        }
    }
    return result;
}

// 修改雇员信息的函数
void EmployeeSystem::modify_employee(CEmployee *employee) {
    try {
        if (employee) {
            cout << "修改雇员信息：" << endl;
            cout << "当前姓名：" << employee->get_name() << endl;
            cout << "请输入新的姓名 (或按Enter键保持不变)：";
            string name;
            cin.ignore();
            getline(cin, name);
            if (!name.empty()) {
                employee->set_name(name);
            }

            cout << "当前性别：" << employee->get_sex() << endl;
            cout << "请输入新的性别 (或按Enter键保持不变)：";
            string sex;
            getline(cin, sex);
            if (!sex.empty()) {
                employee->set_sex(sex);
            }

            BDay birthday = employee->get_birthday();
            cout << "当前生日：" << birthday.year << "-" << birthday.month << "-" << birthday.day << endl;
            cout << "请输入新的生日 (格式: YYYY MM DD, 或按Enter键保持不变)：";
            string bday_input;
            getline(cin, bday_input);
            if (!bday_input.empty()) {
                stringstream ss(bday_input);
                int year, month, day;
                ss >> year >> month >> day;
                if (ss.fail()) {
                    throw runtime_error("生日格式错误，请输入正确的格式 (YYYY MM DD)!");
                }
                employee->set_birthday({year, month, day});
            }

            // 根据雇员类型修改其他相关信息
            string kind = employee->get_kind();
            if (kind == "Manager") {
                CManager *mgr = dynamic_cast<CManager *>(employee);
                if (mgr) {
                    cout << "当前迟到天数：" << mgr->get_late() << endl;
                    cout << "请输入新的迟到天数 (或按Enter键保持不变)：";
                    string late_input;
                    getline(cin, late_input);
                    if (!late_input.empty()) {
                        try {
                            int late = stoi(late_input);
                            mgr->set_late(late);
                        } catch (const invalid_argument &e) {
                            throw runtime_error("输入的迟到天数不是有效的整数！");
                        } catch (const out_of_range &e) {
                            throw runtime_error("输入的迟到天数超出有效范！");
                        }
                    }

                    cout << "当前请假天数：" << mgr->get_leave() << endl;
                    cout << "请输入新的请假天数 (或按Enter键保持不变)：";
                    string leave_input;
                    getline(cin, leave_input);
                    if (!leave_input.empty()) {
                        try {
                            int leave = stoi(leave_input);
                            mgr->set_leave(leave);
                        } catch (const invalid_argument &e) {
                            throw runtime_error("输入的请假天数不是有效的整数！");
                        } catch (const out_of_range &e) {
                            throw runtime_error("输入的请假天数超出有效范围！");
                        }
                    }
                }
            } else if (kind == "Sales") {
                CSales *sales = dynamic_cast<CSales *>(employee);
                if (sales) {
                    cout << "当前销售总额：" << sales->get_total_sales() << endl;
                    cout << "请输入新的销售总额 (或按Enter键保持不变)：";
                    string total_input;
                    getline(cin, total_input);
                    if (!total_input.empty()) {
                        try {
                            double total = stod(total_input);
                            sales->set_total_sales(total);
                        } catch (const invalid_argument &e) {
                            throw runtime_error("输入的销售总额不是有效的数字！");
                        } catch (const out_of_range &e) {
                            throw runtime_error("输入的销售总额超出有效范围！");
                        }
                    }

                    cout << "当前佣金百分比：" << sales->get_commission_percent() << endl;
                    cout << "请输入新的佣金百分比 (或按Enter键保持不变): ";
                    string percent_input;
                    getline(cin, percent_input);
                    if (!percent_input.empty()) {
                        try {
                            double percent = stod(percent_input);
                            sales->set_commission_percent(percent);
                        } catch (const invalid_argument &e) {
                            throw runtime_error("输入的佣金百分比不是有效的数字！");
                        } catch (const out_of_range &e) {
                            throw runtime_error("输入的佣金百分比超出有效范围！");
                        }
                    }
                }
            } else if (kind == "Mgr") {
                CMgr *mgr = dynamic_cast<CMgr *>(employee);
                if (mgr) {
                    CSales *sales = mgr;

                    cout << "当前销售总额：" << sales->get_total_sales() << endl;
                    cout << "请输入新的销售总额 (或按Enter键保持不变)：";
                    string total_input;
                    getline(cin, total_input);
                    if (!total_input.empty()) {
                        try {
                            double total = stod(total_input);
                            sales->set_total_sales(total);
                        } catch (const invalid_argument &e) {
                            throw runtime_error("输入的销售总额不是有效的数字！");
                        } catch (const out_of_range &e) {
                            throw runtime_error("输入的销售总额超出有效范围！");
                        }
                    }

                    cout << "当前佣金百分比：" << sales->get_commission_percent() << endl;
                    cout << "请输入新的佣金百分比 (或按Enter键保持不变)：";
                    string percent_input;
                    getline(cin, percent_input);
                    if (!percent_input.empty()) {
                        try {
                            double percent = stod(percent_input);
                            sales->set_commission_percent(percent);
                        } catch (const invalid_argument &e) {
                            throw runtime_error("输入的佣金百分比不是有效的数字！");
                        } catch (const out_of_range &e) {
                            throw runtime_error("输入的佣金百分比超出有效范围！");
                        }
                    }
                }
            } else if (kind == "Wage") {
                CWage *wage = dynamic_cast<CWage *>(employee);
                if (wage) {
                    cout << "当前工作小时数：" << wage->get_time() << endl;
                    cout << "请输入新的工作小时数 (或按Enter键保持不变)：";
                    string time_input;
                    getline(cin, time_input);
                    if (!time_input.empty()) {
                        try {
                            double timeWorked = stod(time_input);
                            wage->set_time(timeWorked);
                        } catch (const invalid_argument &e) {
                            throw runtime_error("输入的工作小时数不是有效的数字！");
                        } catch (const out_of_range &e) {
                            throw runtime_error("输入的工作小时数超出有效范围！");
                        }
                    }

                    cout << "当前时薪：" << wage->get_hourly_rate() << endl;
                    cout << "请输入新的时薪 (或按Enter键保持不变)：";
                    string hourlyRate_input;
                    getline(cin, hourlyRate_input);
                    if (!hourlyRate_input.empty()) {
                        try {
                            double hourlyRate = stod(hourlyRate_input);
                            wage->set_hourly_rate(hourlyRate);
                        } catch (const invalid_argument &e) {
                            throw runtime_error("输入的时薪不是有效的数字！");
                        } catch (const out_of_range &e) {
                            throw runtime_error("输入的时薪超出有效范围！");
                        }
                    }
                }
            }
            // 重新计算薪水
            employee->computePay();
        }
    } catch (const exception &e) {
        cout << "修改失败：" << e.what() << endl;
    }
}

// 按照类型输出薪水的函数，采用sort函数来排序，内置多种优秀排序方法，时间复杂度为 nlog(n)
void EmployeeSystem::output_salary(const string &filename, const string &sort_by) const {
    vector<CEmployee *> sorted_employees = employees;
    // 通过姓名排序来输出薪水
    if (sort_by == "name") {
        sort(sorted_employees.begin(), sorted_employees.end(), [](CEmployee *a, CEmployee *b) {
            return a->get_name() < b->get_name();
        });
        // 通过薪水大小排序来输出薪水
    } else if (sort_by == "salary") {
        sort(sorted_employees.begin(), sorted_employees.end(), [](CEmployee *a, CEmployee *b) {
            return a->get_salary() < b->get_salary();
        });
        // 通过雇员类型排序来输出薪水
    } else if (sort_by == "type") {
        sort(sorted_employees.begin(), sorted_employees.end(), [](CEmployee *a, CEmployee *b) {
            return a->get_kind() < b->get_kind();
        });
    }

    ofstream outfile(filename);
    if (!outfile) {
        cerr << "Unable to open file " << filename << endl;
        return;
    }

    // 将排序后的员工信息写入文件并打印到控制台
    for (const auto &employee: sorted_employees) {
        string name = employee->get_name();
        double salary = employee->get_salary();
        string kind = employee->get_kind();

        outfile << name << " " << salary << " " << kind << endl;
        cout << name << " " << salary << " " << kind << endl; // Print to console
    }

    outfile.close();
}

// 登录身份校验的函数
bool EmployeeSystem::admin_login(const string &username, const string &password) {
    const string admin_username = "admin";
    const string admin_password = "123456";
    return username == admin_username && password == admin_password;
}

// 添加员工信息的函数
void EmployeeSystem::add_employee() {
    cout << "选择添加的雇员类型:" << endl;
    cout << "1. Manager" << endl;
    cout << "2. Sales" << endl;
    cout << "3. Mgr" << endl;
    cout << "4. Wage" << endl;
    int choice;
    cin >> choice;

    string name, sex;
    int year, month, day;

    cout << "请输入姓名：" << endl;
    cin >> name;
    cout << "请输入性别：" << endl;
    cin >> sex;

    try {
        cout << "请输入生日 (格式: YYYY MM DD)：" << endl;
        cin >> year >> month >> day;

        // 按照不同的身份，输入相关信息，来添加雇员
        switch (choice) {
            case 1: {
                int lateDays, leaveDays;
                cout << "请输入迟到天数：" << endl;
                cin >> lateDays;
                cout << "请输入请假天数：" << endl;
                cin >> leaveDays;
                employees.push_back(new CManager(name, sex, {year, month, day}, lateDays, leaveDays));
                break;
            }
            case 2: {
                double totalSales, commissionPercent;
                cout << "请输入销售总额：" << endl;
                cin >> totalSales;
                cout << "请输入佣金百分比：" << endl;
                cin >> commissionPercent;
                employees.push_back(new CSales(name, sex, {year, month, day}, totalSales, commissionPercent));
                break;
            }
            case 3: {
                int lateDays, leaveDays;
                double totalSales, commissionPercent;
                cout << "请输入迟到天数：" << endl;
                cin >> lateDays;
                cout << "请输入请假天数：" << endl;
                cin >> leaveDays;
                cout << "请输入销售总额：" << endl;
                cin >> totalSales;
                cout << "请输入佣金百分比： " << endl;
                cin >> commissionPercent;
                double fixedSal = 0.0;
                double salesComm = totalSales * commissionPercent;
                employees.push_back(
                        new CMgr(name, sex, {year, month, day}, lateDays, leaveDays, fixedSal, salesComm, totalSales,
                                 commissionPercent));
                break;
            }
            case 4: {
                double totalSales, commissionPercent, timeWorked, hourlyRate;
                cout << "请输入销售总额：" << endl;
                cin >> totalSales;
                cout << "请输入佣金百分比：" << endl;
                cin >> commissionPercent;
                cout << "请输入工作小时数：" << endl;
                cin >> timeWorked;
                cout << "请输入时薪：" << endl;
                cin >> hourlyRate;
                employees.push_back(new CWage(name, sex, {year, month, day}, totalSales, commissionPercent, timeWorked,
                                              hourlyRate));
                break;
            }
            default:
                throw invalid_argument("无效选择！请检查输入是否正确！");
                break;
        }
    } catch (const invalid_argument &e) {
        cout << "输入错误：" << e.what() << endl;
        // 清空输入缓冲区，避免无限循环读取错误输入
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// 删除员工信息的函数
void EmployeeSystem::delete_employee() {
    try {
        cout << "请输入要删除的雇员姓名：" << endl;
        string name;
        cin >> name;

        auto it = find_if(employees.begin(), employees.end(), [&](CEmployee *emp) {
            return emp->get_name() == name;
        });

        if (it != employees.end()) {
            delete *it;
            employees.erase(it);
            cout << "雇员 " << name << " 已删除..." << endl;
        } else {
            throw runtime_error("未找到雇员 " + name + "!");
        }
    } catch (const exception &e) {
        cout << "删除失败：" << e.what() << endl;
    }
}

// 按照类型来计算相应员工的薪水信息
void EmployeeSystem::calculate_average_salary(const string &type) {
    vector<CEmployee *> emps = find_employees_by_type(type);

    if (emps.empty()) {
        cout << "未找到类型为 " << type << " 的雇员！" << endl;
        return;
    }

    double totalSalary = 0.0;
    int count = 0;

    for (auto emp: emps) {
        totalSalary += emp->get_salary();
        count++;
    }

    if (count > 0) {
        double averageSalary = totalSalary / count;
        cout << "类型为 " << type << " 的雇员平均薪资为：" << fixed << setprecision(2) << averageSalary << endl;
        cout << "类型为 " << type << " 的雇员总薪资为：" << fixed << setprecision(2) << totalSalary << endl;
    }
}

void EmployeeSystem::startEmployeeSalaryManagementSystem() {
    // 读取雇员信息，采用异常处理机制，读取失败则抛出异常
    try {
        read_employees("employee.data");
    } catch (const exception &e) {
        cerr << "读取雇员信息失败：" << e.what() << endl;
        return;
    }

    // 登录验证，一共允许五次机会，如若五次输出均错误，则退出
    int q = 5;
    while (q--) {
        string username, password;
        cout << "请输入用户名：" << endl;
        cin >> username;
        cout << "请输入密码：" << endl;
        cin >> password;

        if (!admin_login(username, password) && q != 0) {
            cout << "用户名或密码错误！您还有" << q << "次机会" << endl;
        } else if (!admin_login(username, password) && q == 0) {
            cout << "登录失败！" << endl;
            return;
        } else {
            cout << "登录成功！" << endl;
            cout << "欢迎来到雇员工资管理系统！" << endl;
            break;
        }
    }

    // 显示菜单和选择操作
    int choice;
    do {
        try {
            cout << "\n=== 雇员工资管理系统 ===" << endl;
            cout << "1. 查询雇员信息" << endl;
            cout << "2. 输出薪水信息" << endl;
            cout << "3. 添加员工信息" << endl;
            cout << "4. 删除员工信息" << endl;
            cout << "5. 计算平均薪资和总薪资" << endl;
            cout << "6. 输出所有雇员信息" << endl;
            cout << "7. 退出" << endl;
            cout << "请输入您的选择：" << endl;
            cin >> choice;

            switch (choice) {
                case 1: {
                    cout << "查询雇员信息..." << endl;
                    cout << "a. 按姓名查询" << endl;
                    cout << "b. 按雇员类型查询" << endl;
                    char option;
                    cout << "请输入您需要的查询方式：" << endl;
                    cin >> option;
                    switch (option) {
                        case 'a': {
                            string name;
                            cout << "请输入需要查询雇员的姓名：";
                            cin >> name;
                            CEmployee *emp = find_employee_by_name(name);
                            if (emp) {
                                emp->print_data();
                                cout << "\n是否修改雇员信息？(y/n)：";
                                char modify_option;
                                cin >> modify_option;
                                if (modify_option == 'y' || modify_option == 'Y') {
                                    modify_employee(emp);
                                    cout << "操作成功！雇员信息已修改！" << endl;
                                } else {
                                    cout << "雇员信息未修改！" << endl;
                                }
                            } else {
                                cout << "未找到该雇员！" << endl;
                            }
                            break;
                        }
                        case 'b': {
                            string type;
                            cout << "请输入需要查询的雇员类型 (Manager, Sales, Mgr, Wage)：";
                            cin >> type;
                            vector<CEmployee *> emps = find_employees_by_type(type);
                            if (emps.empty()) {
                                cout << "未找到类型为 " << type << " 的雇员！" << endl;
                            } else {
                                for (auto emp: emps) {
                                    emp->print_data();
                                }
                            }
                            break;
                        }
                        default:
                            cout << "无效选项！请检查输入是否正确！" << endl;
                            break;
                    }
                    break;
                }
                case 2: {
                    cout << "输出薪水信息..." << endl;
                    string sort_by;
                    cout << "请输入排序方式 (name/salary/type)：";
                    cin >> sort_by;
                    output_salary("salary_output.txt", sort_by);
                    cout << "薪水信息已保存至 salary_output.txt" << endl;
                    break;
                }
                case 3: {
                    cout << "添加员工信息..." << endl;
                    add_employee();
                    break;
                }
                case 4: {
                    cout << "删除员工信息..." << endl;
                    delete_employee();
                    break;
                }
                case 5: {
                    char option;
                    do {
                        cout << "=== 计算工资信息 ===" << endl;
                        cout << "1. 计算Manager类型员工薪资信息" << endl;
                        cout << "2. 计算Sales类型员工薪资信息" << endl;
                        cout << "3. 计算Mgr类型员工薪资信息" << endl;
                        cout << "4. 计算Wage类型员工薪资信息" << endl;
                        cout << "5. 返回上一级菜单" << endl;
                        cout << "请输入您的选择：";
                        cin >> option;

                        switch (option) {
                            case '1':
                                calculate_average_salary("Manager");
                                break;
                            case '2':
                                calculate_average_salary("Sales");
                                break;
                            case '3':
                                calculate_average_salary("Mgr");
                                break;
                            case '4':
                                calculate_average_salary("Wage");
                                break;
                            case '5':
                                cout << "返回上一级菜单..." << endl;
                                break;
                            default:
                                cout << "无效选择！请检查输入是否正确！" << endl;
                                break;
                        }

                    } while (option != '5');
                    break;
                }
                case 6: {
                    cout << "输出全部雇员信息..." << endl;
                    cout << "所有雇员信息如下：" << endl;
                    // 输出所有类型的雇员信息
                    vector<CEmployee *> emps = find_employees_by_type("Manager");
                    for (auto emp: emps) emp->print_data();
                    emps = find_employees_by_type("Sales");
                    for (auto emp: emps) emp->print_data();
                    emps = find_employees_by_type("Mgr");
                    for (auto emp: emps) emp->print_data();
                    emps = find_employees_by_type("Wage");
                    for (auto emp: emps) emp->print_data();
                    break;
                }
                case 7:
                    cout << "退出雇员工资管理系统..." << endl;
                    cout << "欢迎下次使用！" << endl;
                    break;
                default:
                    cout << "无效选择！请重新输入..." << endl;
                    break;
            }

        } catch (const exception &e) {
            cerr << "错误：" << e.what() << endl;
        }

    } while (choice != 7);

    // 保存雇员信息，采用异常处理机制，保存失败则抛出异常
    try {
        write_employees("employee.data");
    } catch (const exception &e) {
        cerr << "保存雇员信息失败: " << e.what() << endl;
    }

    // 采用循环来释放雇员对象
    for (auto employee: employees) {
        delete employee;
    }
}
