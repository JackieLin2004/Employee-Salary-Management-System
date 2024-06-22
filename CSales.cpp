#include "CSales.h"
#include <iostream>

CSales::CSales(string name, string sex, BDay birthday, double totalSales, double commissionPercent)
        : total(totalSales), percent(commissionPercent) {
    set_name(name);
    set_sex(sex);
    set_kind("Sales");
    set_birthday(birthday);
    computePay();
}

void CSales::print_data() const {
    CEmployee::print_data();
    std::cout << "销售总额：" << total << "\t销售提成：" << percent << std::endl;
}

void CSales::computePay() {
    set_salary(total * percent);
}

double CSales::get_total_sales() const { return total; }

double CSales::get_commission_percent() const { return percent; }

void CSales::set_total_sales(double totalSales) {
    total = totalSales;
    computePay();
}

void CSales::set_commission_percent(double commissionPercent) {
    percent = commissionPercent;
    computePay();
}
