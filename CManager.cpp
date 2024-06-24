#include "CManager.h"
#include <iostream>

// 构造函数
CManager::CManager(string name, string sex, BDay birthday, int lateDays, int leaveDays)
        : late(lateDays), leave(leaveDays), m_salary(1000) {
    set_name(name);
    set_sex(sex);
    set_kind("Manager");
    set_birthday(birthday);
    computePay();
}
// 输出信息函数
void CManager::print_data() const {
    CEmployee::print_data();
    std::cout << "迟到天数：" << late << "\t请假天数：" << leave << std::endl;
}
// 计算薪水函数
void CManager::computePay() {
    set_salary(m_salary - (late * 50 + leave * 200));
}
// 获取迟到天数函数
int CManager::get_late() const { return late; }
// 获取请假天数函数
int CManager::get_leave() const { return leave; }
// 获取固定工资函数
double CManager::get_m_salary() const { return m_salary; }
// 设置迟到天数函数
void CManager::set_late(int lateDays) {
    late = lateDays;
    computePay();
}
// 设置请假天数函数
void CManager::set_leave(int leaveDays) {
    leave = leaveDays;
    computePay();
}
