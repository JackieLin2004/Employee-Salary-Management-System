#ifndef EMPLOYEESALARYMANAGEMENTSYSTEM_CEMPLOYEE_H
#define EMPLOYEESALARYMANAGEMENTSYSTEM_CEMPLOYEE_H


#include <string>
#include "BDay.h"

using namespace std;

class CEmployee {
private:
    string _name;   // 员工姓名
    string _sex;    // 员工性别
    string _kind;   // 员工类型
    BDay _birthday; // 员工出生日期
    double _salary; // 员工薪水

public:
    CEmployee();

    virtual ~CEmployee();

    string get_name() const;

    double get_salary() const;

    string get_kind() const;

    string get_sex() const;

    BDay get_birthday() const;

    void set_name(const string &name);

    void set_sex(const string &sex);

    void set_kind(const string &kind);

    void set_birthday(const BDay &birthday);

    void set_salary(double salary);

    virtual void print_data() const;

    virtual void computePay() = 0;
};


#endif //EMPLOYEESALARYMANAGEMENTSYSTEM_CEMPLOYEE_H
