#include "CWage.h"
#include <iostream>

CWage::CWage(string name, string sex, BDay birthday, double totalSales, double commissionPercent, double timeWorked,
             double hourlyRate)
        : CSales(name, sex, birthday, totalSales, commissionPercent), time(timeWorked), hourmo(hourlyRate) {
    set_kind("Wage");
    computePay();
}

void CWage::computePay() {
    salesCommission = get_total_sales() * get_commission_percent();
    set_salary(time * hourmo + salesCommission);
}

void CWage::print_data() const {
    CSales::print_data();
    std::cout << "工作小时数：" << time << "\t时薪：" << hourmo << "\t销售提成：" << salesCommission << std::endl;
}

double CWage::get_time() const { return time; }

double CWage::get_hourly_rate() const { return hourmo; }

double CWage::get_sales_commission() const { return salesCommission; }

void CWage::set_time(double timeWorked) {
    time = timeWorked;
    computePay();
}

void CWage::set_hourly_rate(double hourlyRate) {
    hourmo = hourlyRate;
    computePay();
}
