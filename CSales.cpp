#include "CSales.h"
#include <iostream>

// ���캯��
CSales::CSales(string name, string sex, BDay birthday, double totalSales, double commissionPercent)
        : total(totalSales), percent(commissionPercent) {
    set_name(name);
    set_sex(sex);
    set_kind("Sales");
    set_birthday(birthday);
    computePay();
}
// �����Ϣ����
void CSales::print_data() const {
    CEmployee::print_data();
    std::cout << "�����ܶ" << total << "\t������ɣ�" << percent << std::endl;
}
// ����нˮ����
void CSales::computePay() {
    set_salary(total * percent);
}
// ��ȡ�����ܶ��
double CSales::get_total_sales() const { return total; }
// ��ȡ������ɺ���
double CSales::get_commission_percent() const { return percent; }
// ���������ܶ��
void CSales::set_total_sales(double totalSales) {
    total = totalSales;
    computePay();
}
// ����������ɺ���
void CSales::set_commission_percent(double commissionPercent) {
    percent = commissionPercent;
    computePay();
}
