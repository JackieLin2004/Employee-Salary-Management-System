#ifndef EMPLOYEESALARYMANAGEMENTSYSTEM_SYSTEM_H
#define EMPLOYEESALARYMANAGEMENTSYSTEM_SYSTEM_H


#include <vector>
#include <string>
#include "CEmployee.h"
#include "CManager.h"
#include "CSales.h"
#include "CMgr.h"
#include "CWage.h"

using namespace std;

class EmployeeSystem {
private:
    vector<CEmployee *> employees;

public:
    EmployeeSystem() = default;

    // 读取雇员信息的函数
    void read_employees(const string &filename);

    // 保存雇员信息函数，将更新的信息写进文件
    void write_employees(const string &filename) const;

    // 使用二分查找进行 按姓名查询雇员信息的函数
    CEmployee *find_employee_by_name(const string &name);

    // 按照雇员类型来查询信息的函数
    vector<CEmployee *> find_employees_by_type(const string &type);

    // 修改雇员信息的函数
    void modify_employee(CEmployee *employee);

    // 按照类型输出薪水的函数，采用sort函数来排序，内置多种优秀排序方法，时间复杂度为 nlog(n)
    void output_salary(const string &filename, const string &sort_by) const;

    // 登录身份校验的函数
    bool admin_login(const string &username, const string &password);

    // 添加员工信息的函数
    void add_employee();

    // 删除员工信息的函数
    void delete_employee();

    // 按照类型来计算相应员工的薪水信息
    void calculate_average_salary(const string &type);

    void startEmployeeSalaryManagementSystem();
};


#endif //EMPLOYEESALARYMANAGEMENTSYSTEM_SYSTEM_H
