#include "CWage.h"
#include <iostream>
// 构造函数
CWage::CWage(string name, string sex, BDay birthday, double totalSales, double commissionPercent, double timeWorked,
             double hourlyRate)
        : CSales(name, sex, birthday, totalSales, commissionPercent), time(timeWorked), hourmo(hourlyRate) {
    set_kind("Wage");
    computePay();
}
// 计算薪水函数
void CWage::computePay() {
    salesCommission = get_total_sales() * get_commission_percent();
    set_salary(time * hourmo + salesCommission);
}
// 输出信息函数
void CWage::print_data() const {
    CSales::print_data();
    std::cout << "工作小时数：" << time << "\t时薪：" << hourmo << "\t销售提成：" << salesCommission << std::endl;
}
// 获取工作小时函数
double CWage::get_time() const { return time; }
// 获取时薪函数
double CWage::get_hourly_rate() const { return hourmo; }
// 获取销售提成函数
double CWage::get_sales_commission() const { return salesCommission; }
// 设置工作小时函数
void CWage::set_time(double timeWorked) {
    time = timeWorked;
    computePay();
}
// 设置时薪函数
void CWage::set_hourly_rate(double hourlyRate) {
    hourmo = hourlyRate;
    computePay();
}
