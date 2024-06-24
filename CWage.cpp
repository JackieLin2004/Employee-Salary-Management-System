#include "CWage.h"
#include <iostream>
// ���캯��
CWage::CWage(string name, string sex, BDay birthday, double totalSales, double commissionPercent, double timeWorked,
             double hourlyRate)
        : CSales(name, sex, birthday, totalSales, commissionPercent), time(timeWorked), hourmo(hourlyRate) {
    set_kind("Wage");
    computePay();
}
// ����нˮ����
void CWage::computePay() {
    salesCommission = get_total_sales() * get_commission_percent();
    set_salary(time * hourmo + salesCommission);
}
// �����Ϣ����
void CWage::print_data() const {
    CSales::print_data();
    std::cout << "����Сʱ����" << time << "\tʱн��" << hourmo << "\t������ɣ�" << salesCommission << std::endl;
}
// ��ȡ����Сʱ����
double CWage::get_time() const { return time; }
// ��ȡʱн����
double CWage::get_hourly_rate() const { return hourmo; }
// ��ȡ������ɺ���
double CWage::get_sales_commission() const { return salesCommission; }
// ���ù���Сʱ����
void CWage::set_time(double timeWorked) {
    time = timeWorked;
    computePay();
}
// ����ʱн����
void CWage::set_hourly_rate(double hourlyRate) {
    hourmo = hourlyRate;
    computePay();
}
