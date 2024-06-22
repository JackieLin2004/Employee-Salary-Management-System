#include "CManager.h"
#include <iostream>

CManager::CManager(string name, string sex, BDay birthday, int lateDays, int leaveDays)
        : late(lateDays), leave(leaveDays), m_salary(1000) {
    set_name(name);
    set_sex(sex);
    set_kind("Manager");
    set_birthday(birthday);
    computePay();
}

void CManager::print_data() const {
    CEmployee::print_data();
    std::cout << "迟到天数：" << late << "\t请假天数：" << leave << std::endl;
}

void CManager::computePay() {
    set_salary(m_salary - (late * 50 + leave * 200));
}

int CManager::get_late() const { return late; }

int CManager::get_leave() const { return leave; }

double CManager::get_m_salary() const { return m_salary; }

void CManager::set_late(int lateDays) {
    late = lateDays;
    computePay();
}

void CManager::set_leave(int leaveDays) {
    leave = leaveDays;
    computePay();
}
