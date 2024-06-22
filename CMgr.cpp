#include "CMgr.h"
#include <iostream>

CMgr::CMgr(string name, string sex, BDay birthday, int lateDays, int leaveDays, double fixedSal, double salesComm,
           double totalSales, double commissionPercent)
        : CManager(name, sex, birthday, lateDays, leaveDays),
          CSales(name, sex, birthday, totalSales, commissionPercent),
          fixedSalary(fixedSal), salesCommission(salesComm) {
    set_kind("Mgr");
    computePay();
}

void CMgr::computePay() {
    fixedSalary = get_m_salary() - (get_late() * 50 + get_leave() * 200);
    salesCommission = get_total_sales() * get_commission_percent();
    set_salary(fixedSalary + salesCommission);
}

void CMgr::print_data() const {
    std::cout << "\nԱ��������" << get_name() << "\t�Ա�" << get_sex() << "\t���" << get_kind() << std::endl;
    std::cout << "�������ڣ�" << get_birthday().year << "-" << get_birthday().month << "-" << get_birthday().day
              << "\tнˮ��" << get_salary() << std::endl;
    std::cout << "�ٵ�������" << get_late() << "\t���������" << get_leave() << std::endl;
    std::cout << "�����ܶ" << get_total_sales() << "\t������ɣ�" << get_commission_percent() << std::endl;
    std::cout << "�̶����ʣ�" << fixedSalary << "\t������ɣ�" << salesCommission << std::endl;
}

double CMgr::get_fixed_salary() const { return fixedSalary; }

double CMgr::get_sales_commission() const { return salesCommission; }
