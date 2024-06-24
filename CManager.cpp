#include "CManager.h"
#include <iostream>

// ���캯��
CManager::CManager(string name, string sex, BDay birthday, int lateDays, int leaveDays)
        : late(lateDays), leave(leaveDays), m_salary(1000) {
    set_name(name);
    set_sex(sex);
    set_kind("Manager");
    set_birthday(birthday);
    computePay();
}
// �����Ϣ����
void CManager::print_data() const {
    CEmployee::print_data();
    std::cout << "�ٵ�������" << late << "\t���������" << leave << std::endl;
}
// ����нˮ����
void CManager::computePay() {
    set_salary(m_salary - (late * 50 + leave * 200));
}
// ��ȡ�ٵ���������
int CManager::get_late() const { return late; }
// ��ȡ�����������
int CManager::get_leave() const { return leave; }
// ��ȡ�̶����ʺ���
double CManager::get_m_salary() const { return m_salary; }
// ���óٵ���������
void CManager::set_late(int lateDays) {
    late = lateDays;
    computePay();
}
// ���������������
void CManager::set_leave(int leaveDays) {
    leave = leaveDays;
    computePay();
}
