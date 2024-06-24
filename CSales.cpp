#include "CSales.h"
#include <iostream>

// 构造函数
CSales::CSales(string name, string sex, BDay birthday, double totalSales, double commissionPercent)
        : total(totalSales), percent(commissionPercent) {
    set_name(name);
    set_sex(sex);
    set_kind("Sales");
    set_birthday(birthday);
    computePay();
}
// 输出信息函数
void CSales::print_data() const {
    CEmployee::print_data();
    std::cout << "销售总额：" << total << "\t销售提成：" << percent << std::endl;
}
// 计算薪水函数
void CSales::computePay() {
    set_salary(total * percent);
}
// 获取销售总额函数
double CSales::get_total_sales() const { return total; }
// 获取销售提成函数
double CSales::get_commission_percent() const { return percent; }
// 设置销售总额函数
void CSales::set_total_sales(double totalSales) {
    total = totalSales;
    computePay();
}
// 设置销售提成函数
void CSales::set_commission_percent(double commissionPercent) {
    percent = commissionPercent;
    computePay();
}
