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
    // 构造函数
    CEmployee();
    // 析构函数
    virtual ~CEmployee();
    // 获取姓名函数
    string get_name() const;
    // 获取薪水函数
    double get_salary() const;
    // 获取类型函数
    string get_kind() const;
    // 获取性别函数
    string get_sex() const;
    // 获取生日函数
    BDay get_birthday() const;
    // 设置姓名函数
    void set_name(const string &name);
    // 设置性别函数
    void set_sex(const string &sex);
    // 设置员工类型函数
    void set_kind(const string &kind);
    // 设置生日函数
    void set_birthday(const BDay &birthday);
    // 设置薪水函数
    void set_salary(double salary);
    // 输出信息函数
    virtual void print_data() const;
    // 计算薪水函数
    virtual void computePay() = 0;
};


#endif //EMPLOYEESALARYMANAGEMENTSYSTEM_CEMPLOYEE_H
