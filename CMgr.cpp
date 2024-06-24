#include "CMgr.h"
#include <iostream>
// 构造函数
CMgr::CMgr(string name, string sex, BDay birthday, int lateDays, int leaveDays, double fixedSal, double salesComm,
           double totalSales, double commissionPercent)
        : CManager(name, sex, birthday, lateDays, leaveDays),
          CSales(name, sex, birthday, totalSales, commissionPercent),
          fixedSalary(fixedSal), salesCommission(salesComm) {
    set_kind("Mgr");
    computePay();
}
// 计算薪水函数
void CMgr::computePay() {
    fixedSalary = get_m_salary() - (get_late() * 50 + get_leave() * 200);
    salesCommission = get_total_sales() * get_commission_percent();
    set_salary(fixedSalary + salesCommission);
}
// 输出信息函数
void CMgr::print_data() const {
    std::cout << "\n员工姓名：" << get_name() << "\t性别：" << get_sex() << "\t类别：" << get_kind() << std::endl;
    std::cout << "出生日期：" << get_birthday().year << "-" << get_birthday().month << "-" << get_birthday().day
              << "\t薪水：" << get_salary() << std::endl;
    std::cout << "迟到天数：" << get_late() << "\t请假天数：" << get_leave() << std::endl;
    std::cout << "销售总额：" << get_total_sales() << "\t销售提成：" << get_commission_percent() << std::endl;
    std::cout << "固定工资：" << fixedSalary << "\t销售提成：" << salesCommission << std::endl;
}
// 获取固定工资函数
double CMgr::get_fixed_salary() const { return fixedSalary; }
// 获取销售提成函数
double CMgr::get_sales_commission() const { return salesCommission; }
