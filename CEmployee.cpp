#include "CEmployee.h"
#include <iostream>

// 构造函数
CEmployee::CEmployee() : _salary(0.0) {}
// 析构函数
CEmployee::~CEmployee() {}
// 获取姓名函数
string CEmployee::get_name() const { return _name; }
// 获取薪水函数
double CEmployee::get_salary() const { return _salary; }
// 获取员工类型函数
string CEmployee::get_kind() const { return _kind; }
// 获取性别函数
string CEmployee::get_sex() const { return _sex; }
// 获取生日函数
BDay CEmployee::get_birthday() const { return _birthday; }
// 设置姓名函数
void CEmployee::set_name(const string &name) { _name = name; }
// 设置性别函数
void CEmployee::set_sex(const string &sex) { _sex = sex; }
// 设置员工类型函数
void CEmployee::set_kind(const string &kind) { _kind = kind; }
// 设置员工生日函数
void CEmployee::set_birthday(const BDay &birthday) { _birthday = birthday; }
// 设置薪水函数
void CEmployee::set_salary(double salary) { _salary = salary; }
// 输出信息函数
void CEmployee::print_data() const {
    cout << "\n员工姓名：" << _name << "\t性别：" << _sex << "\t类别：" << _kind << endl;
    cout << "出生日期：" << _birthday.year << "-" << _birthday.month << "-" << _birthday.day
         << "\t薪水：" << _salary << endl;
}
