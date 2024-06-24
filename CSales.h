#ifndef EMPLOYEESALARYMANAGEMENTSYSTEM_CSALES_H
#define EMPLOYEESALARYMANAGEMENTSYSTEM_CSALES_H


#include "CEmployee.h"

class CSales : virtual public CEmployee {
private:
    double total;   // 销售总额
    double percent; // 销售提成

public:
    // 构造函数
    CSales(string name, string sex, BDay birthday, double totalSales, double commissionPercent);
    // 输出信息函数
    void print_data() const override;
    // 计算薪水函数
    void computePay() override;
    // 获取销售总额函数
    double get_total_sales() const;
    // 获取销售提成函数
    double get_commission_percent() const;
    // 设置销售总额函数
    void set_total_sales(double totalSales);
    // 设置销售提成函数
    void set_commission_percent(double commissionPercent);
};


#endif //EMPLOYEESALARYMANAGEMENTSYSTEM_CSALES_H
