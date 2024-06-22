#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <stdexcept>

using namespace std;

// �������սṹ
struct BDay {
    int year, month, day;
};

// ���� CEmployee ��Ա��
class CEmployee {
protected:
    string _name;   // Ա������
    string _sex;    // Ա���Ա�
    string _kind;   // Ա������
    BDay _birthday; // Ա����������
    double _salary; // Ա��нˮ

public:
    // ���캯��
    CEmployee() : _salary(0.0) {}

    // ��������
    virtual ~CEmployee() {}

    // �������ʺ����������������ֵ�͸�ֵ
    string get_name() const { return _name; }

    double get_salary() const { return _salary; }

    string get_kind() const { return _kind; }

    string get_sex() const { return _sex; }

    BDay get_birthday() const { return _birthday; }

    void set_name(const string &name) { _name = name; }

    void set_sex(const string &sex) { _sex = sex; }

    void set_birthday(const BDay &birthday) { _birthday = birthday; }

    // ��������Ϣ
    virtual void print_data() const {
        cout << "\nԱ��������" << _name << "\t�Ա�" << _sex << "\t���" << _kind << endl;
        cout << "��������" << _birthday.year << "-" << _birthday.month << "-" << _birthday.day
             << "\tнˮ��" << _salary << endl;
    }

    // �����Աнˮ
    virtual void computePay() = 0;
};

// CManager �� ������
class CManager : virtual public CEmployee {
private:
    int late;   // �ٵ��������ٵ�1���50Ԫ
    int leave;  // ����������ٵ�1���200Ԫ
    double m_salary;    // ����̶�нˮ1000Ԫ

public:
    // ���ع��캯��
    CManager(string name, string sex, BDay birthday, int lateDays, int leaveDays)
            : late(lateDays), leave(leaveDays), m_salary(1000) {
        _name = name;
        _sex = sex;
        _kind = "Manager";
        _birthday = birthday;
        computePay();
    }

    // ���������Ϣ
    void print_data() const override {
        CEmployee::print_data();
        cout << "�ٵ�������" << late << "\t���������" << leave << endl;
    }

    // ���㾭����н��_salary=�̶�нˮ���ۿ�
    void computePay() override {
        _salary = m_salary - (late * 50 + leave * 200);
    }

    // �������ʺ����������������ֵ�͸�ֵ
    int get_late() const { return late; }

    int get_leave() const { return leave; }

    double get_m_salary() const { return m_salary; }

    void set_late(int lateDays) {
        late = lateDays;
        computePay();
    }

    void set_leave(int leaveDays) {
        leave = leaveDays;
        computePay();
    }
};

// CSales �� ����Ա��
class CSales : virtual public CEmployee {
private:
    double total;   // �����ܶ�ٵ�1���50Ԫ
    double percent; // �������

public:
    // ���ع��캯��
    CSales(string name, string sex, BDay birthday, double totalSales, double commissionPercent)
            : total(totalSales), percent(commissionPercent) {
        _name = name;
        _sex = sex;
        _kind = "Sales";
        _birthday = birthday;
        computePay();
    }

    // �������Ա��Ϣ
    void print_data() const override {
        CEmployee::print_data();
        cout << "�����ܶ" << total << "\t������ɣ�" << percent << endl;
    }

    // ����нˮ
    void computePay() override {
        _salary = total * percent;
    }

    // �������ʺ����������������ֵ�͸�ֵ
    double get_total_sales() const { return total; }

    double get_commission_percent() const { return percent; }

    void set_total_sales(double totalSales) {
        total = totalSales;
        computePay();
    }

    void set_commission_percent(double commissionPercent) {
        percent = commissionPercent;
        computePay();
    }
};

// CMgr �� �г�������
class CMgr : public CManager, public CSales {
private:
    double fixedSalary; // �̶�����
    double salesCommission; // �������

public:
    // ���ع��캯��
    CMgr(string name, string sex, BDay birthday, int lateDays, int leaveDays, double fixedSal, double salesComm,
         double totalSales, double commissionPercent)
            : CManager(name, sex, birthday, lateDays, leaveDays),
              CSales(name, sex, birthday, totalSales, commissionPercent),
              fixedSalary(fixedSal), salesCommission(salesComm) {
        _kind = "Mgr";
        computePay();
    }

    // ����нˮ
    void computePay() override {
        fixedSalary = get_m_salary() - (get_late() * 50 + get_leave() * 200);
        salesCommission = get_total_sales() * get_commission_percent();
        _salary = fixedSalary + salesCommission;
    }

    // ����г�������Ϣ
    void print_data() const override {
        cout << "\nԱ��������" << _name << "\t�Ա�" << _sex << "\t���" << _kind << endl;
        cout << "��������" << _birthday.year << "-" << _birthday.month << "-" << _birthday.day
             << "\tнˮ��" << _salary << endl;
        cout << "�ٵ�������" << get_late() << "\t���������" << get_leave() << endl;
        cout << "�����ܶ" << get_total_sales() << "\t������ɣ�" << get_commission_percent() << endl;
        cout << "�̶����ʣ�" << fixedSalary << "\t������ɣ�" << salesCommission << endl;
    }

    // �������ʺ�������ȡ�̶����ʺ��������
    double get_fixed_salary() const { return fixedSalary; }

    double get_sales_commission() const { return salesCommission; }

};

// CWage �� ʱн����Ա��
class CWage : public CSales {
private:
    double time;    // ����Сʱ��
    double hourmo;  // ʱн
    double salesCommission; // �������

public:
    // ���ع��캯��
    CWage(string name, string sex, BDay birthday, double totalSales, double commissionPercent, double timeWorked,
          double hourlyRate)
            : CSales(name, sex, birthday, totalSales, commissionPercent), time(timeWorked), hourmo(hourlyRate) {
        _kind = "Wage";
        computePay();
    }

    // ����нˮ
    void computePay() override {
        salesCommission = get_total_sales() * get_commission_percent();
        _salary = time * hourmo + salesCommission;
    }

    // ���ʱн����Ա����Ϣ
    void print_data() const override {
        CSales::print_data();
        cout << "����Сʱ����" << time << "\tʱн��" << hourmo << "\t������ɣ�" << salesCommission << endl;
    }

    // �������ʺ�������ȡ���ֵ�͸�ֵ
    double get_time() const { return time; }

    double get_hourly_rate() const { return hourmo; }

    double get_sales_commission() const { return salesCommission; }

    void set_time(double timeWorked) {
        time = timeWorked;
        computePay();
    }

    void set_hourly_rate(double hourlyRate) {
        hourmo = hourlyRate;
        computePay();
    }
};

// ��ȡ��Ա��Ϣ�ĺ���
void read_employees(vector<CEmployee *> &employees, const string &filename) {
    try {
        ifstream infile(filename);
        if (!infile) {
            // �ļ������׳��쳣
            throw runtime_error("�޷����ļ� " + filename);
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
        cerr << "����쳣��" << e.what() << endl;
    }

}

void write_employees(const vector<CEmployee *> &employees, const string &filename) {
    try {
        ofstream outfile(filename);
        if (!outfile) {
            throw runtime_error("�޷����ļ�" + filename);
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

// ʹ�ö��ֲ��ҽ��� ��������ѯ��Ա��Ϣ�ĺ���
CEmployee *find_employee_by_name(vector<CEmployee *> &employees, const string &name) {
    // �Ȱ������������δ����Ļ���
    sort(employees.begin(), employees.end(), [](CEmployee *a, CEmployee *b) {
        return a->get_name() < b->get_name();
    });

    // ���ֲ���
    int left = 0;
    int right = employees.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (employees[mid]->get_name() == name) {
            // �ҵ���Ӧ��Ϣ������
            return employees[mid];
        } else if (employees[mid]->get_name() < name) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    // û���ҵ���Ա
    return nullptr;
}

// ���չ�Ա��������ѯ��Ϣ�ĺ���
vector<CEmployee *> find_employees_by_type(vector<CEmployee *> &employees, const string &type) {
    vector<CEmployee *> result;
    for (auto &employee: employees) {
        if (employee->get_kind() == type) {
            result.push_back(employee);
        }
    }
    return result;
}

// �޸Ĺ�Ա��Ϣ�ĺ���
void modify_employee(CEmployee *employee) {
    try {
        if (employee) {
            cout << "�޸Ĺ�Ա��Ϣ: " << endl;
            cout << "��ǰ����: " << employee->get_name() << endl;
            cout << "�������µ����� (��Enter�����ֲ���): ";
            string name;
            cin.ignore();
            getline(cin, name);
            if (!name.empty()) {
                employee->set_name(name);
            }

            cout << "��ǰ�Ա�: " << employee->get_sex() << endl;
            cout << "�������µ��Ա� (��Enter�����ֲ���): ";
            string sex;
            getline(cin, sex);
            if (!sex.empty()) {
                employee->set_sex(sex);
            }

            BDay birthday = employee->get_birthday();
            cout << "��ǰ����: " << birthday.year << "-" << birthday.month << "-" << birthday.day << endl;
            cout << "�������µ����� (��ʽ: YYYY MM DD, ��Enter�����ֲ���): ";
            string bday_input;
            getline(cin, bday_input);
            if (!bday_input.empty()) {
                stringstream ss(bday_input);
                int year, month, day;
                ss >> year >> month >> day;
                if (ss.fail()) {
                    throw runtime_error("���ո�ʽ������������ȷ�ĸ�ʽ (YYYY MM DD)��");
                }
                employee->set_birthday({year, month, day});
            }

            // ���ݹ�Ա�����޸����������Ϣ
            string kind = employee->get_kind();
            if (kind == "Manager") {
                CManager *mgr = dynamic_cast<CManager *>(employee);
                if (mgr) {
                    cout << "��ǰ�ٵ�����: " << mgr->get_late() << endl;
                    cout << "�������µĳٵ����� (��Enter�����ֲ���): ";
                    string late_input;
                    getline(cin, late_input);
                    if (!late_input.empty()) {
                        try {
                            int late = stoi(late_input);
                            mgr->set_late(late);
                        } catch (const invalid_argument &e) {
                            throw runtime_error("����ĳٵ�����������Ч��������");
                        } catch (const out_of_range &e) {
                            throw runtime_error("����ĳٵ�����������Ч��Χ��");
                        }
                    }

                    cout << "��ǰ�������: " << mgr->get_leave() << endl;
                    cout << "�������µ�������� (��Enter�����ֲ���): ";
                    string leave_input;
                    getline(cin, leave_input);
                    if (!leave_input.empty()) {
                        try {
                            int leave = stoi(leave_input);
                            mgr->set_leave(leave);
                        } catch (const invalid_argument &e) {
                            throw runtime_error("������������������Ч��������");
                        } catch (const out_of_range &e) {
                            throw runtime_error("������������������Ч��Χ��");
                        }
                    }
                }
            } else if (kind == "Sales") {
                CSales *sales = dynamic_cast<CSales *>(employee);
                if (sales) {
                    cout << "��ǰ�����ܶ�: " << sales->get_total_sales() << endl;
                    cout << "�������µ������ܶ� (��Enter�����ֲ���): ";
                    string total_input;
                    getline(cin, total_input);
                    if (!total_input.empty()) {
                        try {
                            double total = stod(total_input);
                            sales->set_total_sales(total);
                        } catch (const invalid_argument &e) {
                            throw runtime_error("����������ܶ����Ч�����֡�");
                        } catch (const out_of_range &e) {
                            throw runtime_error("����������ܶ����Ч��Χ��");
                        }
                    }

                    cout << "��ǰӶ��ٷֱ�: " << sales->get_commission_percent() << endl;
                    cout << "�������µ�Ӷ��ٷֱ� (��Enter�����ֲ���): ";
                    string percent_input;
                    getline(cin, percent_input);
                    if (!percent_input.empty()) {
                        try {
                            double percent = stod(percent_input);
                            sales->set_commission_percent(percent);
                        } catch (const invalid_argument &e) {
                            throw runtime_error("�����Ӷ��ٷֱȲ�����Ч�����֡�");
                        } catch (const out_of_range &e) {
                            throw runtime_error("�����Ӷ��ٷֱȳ�����Ч��Χ��");
                        }
                    }
                }
            } else if (kind == "Mgr") {
                CMgr *mgr = dynamic_cast<CMgr *>(employee);
                if (mgr) {
                    CSales *sales = mgr;

                    cout << "��ǰ�����ܶ�: " << sales->get_total_sales() << endl;
                    cout << "�������µ������ܶ� (��Enter�����ֲ���): ";
                    string total_input;
                    getline(cin, total_input);
                    if (!total_input.empty()) {
                        try {
                            double total = stod(total_input);
                            sales->set_total_sales(total);
                        } catch (const invalid_argument &e) {
                            throw runtime_error("����������ܶ����Ч�����֡�");
                        } catch (const out_of_range &e) {
                            throw runtime_error("����������ܶ����Ч��Χ��");
                        }
                    }

                    cout << "��ǰӶ��ٷֱ�: " << sales->get_commission_percent() << endl;
                    cout << "�������µ�Ӷ��ٷֱ� (��Enter�����ֲ���): ";
                    string percent_input;
                    getline(cin, percent_input);
                    if (!percent_input.empty()) {
                        try {
                            double percent = stod(percent_input);
                            sales->set_commission_percent(percent);
                        } catch (const invalid_argument &e) {
                            throw runtime_error("�����Ӷ��ٷֱȲ�����Ч�����֡�");
                        } catch (const out_of_range &e) {
                            throw runtime_error("�����Ӷ��ٷֱȳ�����Ч��Χ��");
                        }
                    }
                }
            } else if (kind == "Wage") {
                CWage *wage = dynamic_cast<CWage *>(employee);
                if (wage) {
                    cout << "��ǰ����Сʱ��: " << wage->get_time() << endl;
                    cout << "�������µĹ���Сʱ�� (��Enter�����ֲ���): ";
                    string time_input;
                    getline(cin, time_input);
                    if (!time_input.empty()) {
                        try {
                            double timeWorked = stod(time_input);
                            wage->set_time(timeWorked);
                        } catch (const invalid_argument &e) {
                            throw runtime_error("����Ĺ���Сʱ��������Ч�����֡�");
                        } catch (const out_of_range &e) {
                            throw runtime_error("����Ĺ���Сʱ��������Ч��Χ��");
                        }
                    }

                    cout << "��ǰʱн: " << wage->get_hourly_rate() << endl;
                    cout << "�������µ�ʱн (��Enter�����ֲ���): ";
                    string hourlyRate_input;
                    getline(cin, hourlyRate_input);
                    if (!hourlyRate_input.empty()) {
                        try {
                            double hourlyRate = stod(hourlyRate_input);
                            wage->set_hourly_rate(hourlyRate);
                        } catch (const invalid_argument &e) {
                            throw runtime_error("�����ʱн������Ч�����֡�");
                        } catch (const out_of_range &e) {
                            throw runtime_error("�����ʱн������Ч��Χ��");
                        }
                    }
                }
            }
            employee->computePay(); // ���¼���нˮ
        }
    } catch (const exception &e) {
        cout << "�޸�ʧ��: " << e.what() << endl;
    }
}

// �����������нˮ�ĺ���������sort�������������ö����������򷽷���ʱ�临�Ӷ�Ϊ nlog(n)
void output_salary(const vector<CEmployee *> &employees, const string &filename, const string &sort_by) {
    vector<CEmployee *> sorted_employees = employees;
    // ͨ���������������нˮ
    if (sort_by == "name") {
        sort(sorted_employees.begin(), sorted_employees.end(), [](CEmployee *a, CEmployee *b) {
            return a->get_name() < b->get_name();
        });
        // ͨ��нˮ��С���������нˮ
    } else if (sort_by == "salary") {
        sort(sorted_employees.begin(), sorted_employees.end(), [](CEmployee *a, CEmployee *b) {
            return a->get_salary() < b->get_salary();
        });
        // ͨ����Ա�������������нˮ
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

    // ��������Ա����Ϣд���ļ�����ӡ������̨
    for (const auto &employee: sorted_employees) {
        string name = employee->get_name();
        double salary = employee->get_salary();
        string kind = employee->get_kind();

        outfile << name << " " << salary << " " << kind << endl;
        cout << name << " " << salary << " " << kind << endl; // Print to console
    }

    outfile.close();
}

// ��¼���У��ĺ���
bool admin_login(const string &username, const string &password) {
    const string admin_username = "admin";
    const string admin_password = "123456";
    return username == admin_username && password == admin_password;
}

// ���Ա����Ϣ�ĺ���
void add_employee(vector<CEmployee *> &employees) {
    cout << "ѡ����ӵĹ�Ա����:" << endl;
    cout << "1. Manager" << endl;
    cout << "2. Sales" << endl;
    cout << "3. Mgr" << endl;
    cout << "4. Wage" << endl;
    int choice;
    cin >> choice;

    string name, sex;
    int year, month, day;

    cout << "������������" << endl;
    cin >> name;
    cout << "�������Ա�" << endl;
    cin >> sex;

    try {
        cout << "���������� (��ʽ: YYYY MM DD)��" << endl;
        cin >> year >> month >> day;

        // ���ղ�ͬ����ݣ����������Ϣ������ӹ�Ա
        switch (choice) {
            case 1: {
                int lateDays, leaveDays;
                cout << "������ٵ�������" << endl;
                cin >> lateDays;
                cout << "���������������" << endl;
                cin >> leaveDays;
                employees.push_back(new CManager(name, sex, {year, month, day}, lateDays, leaveDays));
                break;
            }
            case 2: {
                double totalSales, commissionPercent;
                cout << "�����������ܶ" << endl;
                cin >> totalSales;
                cout << "������Ӷ��ٷֱȣ�" << endl;
                cin >> commissionPercent;
                employees.push_back(new CSales(name, sex, {year, month, day}, totalSales, commissionPercent));
                break;
            }
            case 3: {
                int lateDays, leaveDays;
                double totalSales, commissionPercent;
                cout << "������ٵ�������" << endl;
                cin >> lateDays;
                cout << "���������������" << endl;
                cin >> leaveDays;
                cout << "�����������ܶ" << endl;
                cin >> totalSales;
                cout << "������Ӷ��ٷֱȣ� " << endl;
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
                cout << "�����������ܶ" << endl;
                cin >> totalSales;
                cout << "������Ӷ��ٷֱȣ�" << endl;
                cin >> commissionPercent;
                cout << "�����빤��Сʱ����" << endl;
                cin >> timeWorked;
                cout << "������ʱн��" << endl;
                cin >> hourlyRate;
                employees.push_back(new CWage(name, sex, {year, month, day}, totalSales, commissionPercent, timeWorked,
                                              hourlyRate));
                break;
            }
            default:
                throw invalid_argument("��Чѡ�����������Ƿ���ȷ��");
                break;
        }
    } catch (const invalid_argument &e) {
        cout << "�������" << e.what() << endl;
        // ������뻺��������������ѭ����ȡ��������
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// ɾ��Ա����Ϣ�ĺ���
void delete_employee(vector<CEmployee *> &employees) {
    try {
        cout << "������Ҫɾ���Ĺ�Ա������" << endl;
        string name;
        cin >> name;

        auto it = find_if(employees.begin(), employees.end(), [&](CEmployee *emp) {
            return emp->get_name() == name;
        });

        if (it != employees.end()) {
            delete *it;
            employees.erase(it);
            cout << "��Ա " << name << " ��ɾ��..." << endl;
        } else {
            throw runtime_error("δ�ҵ���Ա " + name + "!");
        }
    } catch (const exception &e) {
        cout << "ɾ��ʧ�ܣ�" << e.what() << endl;
    }
}

// ����������������ӦԱ����нˮ��Ϣ
void calculate_average_salary(vector<CEmployee *> &employees, const string &type) {
    vector<CEmployee *> emps = find_employees_by_type(employees, type);

    if (emps.empty()) {
        cout << "δ�ҵ�����Ϊ " << type << " �Ĺ�Ա��" << endl;
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
        cout << "����Ϊ " << type << " �Ĺ�Աƽ��н��Ϊ��" << fixed << setprecision(2) << averageSalary << endl;
        cout << "����Ϊ " << type << " �Ĺ�Ա��н��Ϊ��" << fixed << setprecision(2) << totalSalary << endl;
    }
}


int main() {
    // ��vector�������洢��Ϣ����̬���飬������ƴ�С
    vector<CEmployee *> employees;

    // ��ȡ��Ա��Ϣ�������쳣������ƣ���ȡʧ�����׳��쳣
    try {
        read_employees(employees, "employee.data");
    } catch (const exception &e) {
        cerr << "��ȡ��Ա��Ϣʧ�ܣ�" << e.what() << endl;
        return 1;
    }

    // ��¼��֤��һ��������λ��ᣬ�������������������˳�
    int q = 5;
    while (q--) {
        string username, password;
        cout << "�������û�����" << endl;
        cin >> username;
        cout << "���������룺" << endl;
        cin >> password;

        if (!admin_login(username, password) && q != 0) {
            cout << "�û������������������" << q << "�λ���" << endl;
        } else if (!admin_login(username, password) && q == 0) {
            cout << "��¼ʧ�ܣ�" << endl;
            return 1;
        } else {
            cout << "��¼�ɹ���" << endl;
            cout << "��ӭ������Ա���ʹ���ϵͳ��" << endl;
            break;
        }
    }

    // ��ʾ�˵���ѡ�����
    int choice;
    do {
        try {
            cout << "\n=== ��Ա���ʹ���ϵͳ ===" << endl;
            cout << "1. ��ѯ��Ա��Ϣ" << endl;
            cout << "2. ���нˮ��Ϣ" << endl;
            cout << "3. ���Ա����Ϣ" << endl;
            cout << "4. ɾ��Ա����Ϣ" << endl;
            cout << "5. ����ƽ��н�ʺ���н��" << endl;
            cout << "6. ������й�Ա��Ϣ" << endl;
            cout << "7. �˳�" << endl;
            cout << "����������ѡ��" << endl;
            cin >> choice;

            switch (choice) {
                case 1: {
                    cout << "��ѯ��Ա��Ϣ..." << endl;
                    cout << "a. ��������ѯ" << endl;
                    cout << "b. ����Ա���Ͳ�ѯ" << endl;
                    char option;
                    cout << "����������Ҫ�Ĳ�ѯ��ʽ��" << endl;
                    cin >> option;
                    switch (option) {
                        case 'a': {
                            string name;
                            cout << "��������Ҫ��ѯ��Ա��������";
                            cin >> name;
                            CEmployee *emp = find_employee_by_name(employees, name);
                            if (emp) {
                                emp->print_data();
                                cout << "\n�Ƿ��޸Ĺ�Ա��Ϣ��(y/n)��";
                                char modify_option;
                                cin >> modify_option;
                                if (modify_option == 'y' || modify_option == 'Y') {
                                    modify_employee(emp);
                                    cout << "�����ɹ�����Ա��Ϣ���޸ģ�" << endl;
                                } else {
                                    cout << "��Ա��Ϣδ�޸ģ�" << endl;
                                }
                            } else {
                                cout << "δ�ҵ��ù�Ա��" << endl;
                            }
                            break;
                        }
                        case 'b': {
                            string type;
                            cout << "��������Ҫ��ѯ�Ĺ�Ա���� (Manager, Sales, Mgr, Wage)��";
                            cin >> type;
                            vector<CEmployee *> emps = find_employees_by_type(employees, type);
                            if (emps.empty()) {
                                cout << "δ�ҵ�����Ϊ " << type << " �Ĺ�Ա��" << endl;
                            } else {
                                for (auto emp: emps) {
                                    emp->print_data();
                                }
                            }
                            break;
                        }
                        default:
                            cout << "��Чѡ����������Ƿ���ȷ��" << endl;
                            break;
                    }
                    break;
                }
                case 2: {
                    cout << "���нˮ��Ϣ..." << endl;
                    string sort_by;
                    cout << "����������ʽ (name/salary/type)��";
                    cin >> sort_by;
                    output_salary(employees, "salary_output.txt", sort_by);
                    cout << "нˮ��Ϣ�ѱ����� salary_output.txt" << endl;
                    break;
                }
                case 3: {
                    cout << "���Ա����Ϣ..." << endl;
                    add_employee(employees);
                    break;
                }
                case 4: {
                    cout << "ɾ��Ա����Ϣ..." << endl;
                    delete_employee(employees);
                    break;
                }
                case 5: {
                    char option;
                    do {
                        cout << "=== ���㹤����Ϣ ===" << endl;
                        cout << "1. ����Manager����Ա��н����Ϣ" << endl;
                        cout << "2. ����Sales����Ա��н����Ϣ" << endl;
                        cout << "3. ����Mgr����Ա��н����Ϣ" << endl;
                        cout << "4. ����Wage����Ա��н����Ϣ" << endl;
                        cout << "5. ������һ���˵�" << endl;
                        cout << "����������ѡ��";
                        cin >> option;

                        switch (option) {
                            case '1':
                                calculate_average_salary(employees, "Manager");
                                break;
                            case '2':
                                calculate_average_salary(employees, "Sales");
                                break;
                            case '3':
                                calculate_average_salary(employees, "Mgr");
                                break;
                            case '4':
                                calculate_average_salary(employees, "Wage");
                                break;
                            case '5':
                                cout << "������һ���˵�..." << endl;
                                break;
                            default:
                                cout << "��Чѡ�����������Ƿ���ȷ��" << endl;
                                break;
                        }

                    } while (option != '5');
                    break;
                }
                case 6: {
                    cout << "���ȫ����Ա��Ϣ..." << endl;
                    cout << "���й�Ա��Ϣ���£�" << endl;
                    // ����������͵Ĺ�Ա��Ϣ
                    vector<CEmployee *> emps = find_employees_by_type(employees, "Manager");
                    for (auto emp: emps) emp->print_data();
                    emps = find_employees_by_type(employees, "Sales");
                    for (auto emp: emps) emp->print_data();
                    emps = find_employees_by_type(employees, "Mgr");
                    for (auto emp: emps) emp->print_data();
                    emps = find_employees_by_type(employees, "Wage");
                    for (auto emp: emps) emp->print_data();
                    break;
                }
                case 7:
                    cout << "�˳���Ա���ʹ���ϵͳ..." << endl;
                    cout << "��ӭ�´�ʹ�ã�" << endl;
                    break;
                default:
                    cout << "��Чѡ������������..." << endl;
                    break;
            }

        } catch (const exception &e) {
            cerr << "����" << e.what() << endl;
        }

    } while (choice != 7);

    // �����Ա��Ϣ�������쳣������ƣ�����ʧ�����׳��쳣
    try {
        write_employees(employees, "employee.data");
    } catch (const exception &e) {
        cerr << "�����Ա��Ϣʧ��: " << e.what() << endl;
    }

    // ����ѭ�����ͷŹ�Ա����
    for (auto employee: employees) {
        delete employee;
    }

    return 0;
}
