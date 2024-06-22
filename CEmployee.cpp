#include "CEmployee.h"
#include <iostream>

CEmployee::CEmployee() : _salary(0.0) {}

CEmployee::~CEmployee() {}

string CEmployee::get_name() const { return _name; }

double CEmployee::get_salary() const { return _salary; }

string CEmployee::get_kind() const { return _kind; }

string CEmployee::get_sex() const { return _sex; }

BDay CEmployee::get_birthday() const { return _birthday; }

void CEmployee::set_name(const string &name) { _name = name; }

void CEmployee::set_sex(const string &sex) { _sex = sex; }

void CEmployee::set_kind(const string &kind) { _kind = kind; }

void CEmployee::set_birthday(const BDay &birthday) { _birthday = birthday; }

void CEmployee::set_salary(double salary) { _salary = salary; }

void CEmployee::print_data() const {
    cout << "\nԱ��������" << _name << "\t�Ա�" << _sex << "\t���" << _kind << endl;
    cout << "�������ڣ�" << _birthday.year << "-" << _birthday.month << "-" << _birthday.day
         << "\tнˮ��" << _salary << endl;
}
