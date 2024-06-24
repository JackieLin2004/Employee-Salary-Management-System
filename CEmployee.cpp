#include "CEmployee.h"
#include <iostream>

// ���캯��
CEmployee::CEmployee() : _salary(0.0) {}
// ��������
CEmployee::~CEmployee() {}
// ��ȡ��������
string CEmployee::get_name() const { return _name; }
// ��ȡнˮ����
double CEmployee::get_salary() const { return _salary; }
// ��ȡԱ�����ͺ���
string CEmployee::get_kind() const { return _kind; }
// ��ȡ�Ա���
string CEmployee::get_sex() const { return _sex; }
// ��ȡ���պ���
BDay CEmployee::get_birthday() const { return _birthday; }
// ������������
void CEmployee::set_name(const string &name) { _name = name; }
// �����Ա���
void CEmployee::set_sex(const string &sex) { _sex = sex; }
// ����Ա�����ͺ���
void CEmployee::set_kind(const string &kind) { _kind = kind; }
// ����Ա�����պ���
void CEmployee::set_birthday(const BDay &birthday) { _birthday = birthday; }
// ����нˮ����
void CEmployee::set_salary(double salary) { _salary = salary; }
// �����Ϣ����
void CEmployee::print_data() const {
    cout << "\nԱ��������" << _name << "\t�Ա�" << _sex << "\t���" << _kind << endl;
    cout << "�������ڣ�" << _birthday.year << "-" << _birthday.month << "-" << _birthday.day
         << "\tнˮ��" << _salary << endl;
}
