#ifndef EMPLOYEESALARYMANAGEMENTSYSTEM_CWAGE_H
#define EMPLOYEESALARYMANAGEMENTSYSTEM_CWAGE_H


#include "CSales.h"

class CWage : public CSales {
private:
    double time;    // 工作小时数
    double hourmo;  // 时薪
    double salesCommission; // 销售提成

public:
    // 构造函数
    CWage(string name, string sex, BDay birthday, double totalSales, double commissionPercent, double timeWorked,
          double hourlyRate);
    // 计算薪水函数
    void computePay() override;
    // 输出信息函数
    void print_data() const override;
    // 获取工作小时函数
    double get_time() const;
    // 获取时薪函数
    double get_hourly_rate() const;
    // 获取销售提成函数
    double get_sales_commission() const;
    // 设置工作小时函数
    void set_time(double timeWorked);
    // 设置时薪函数
    void set_hourly_rate(double hourlyRate);
};


#endif //EMPLOYEESALARYMANAGEMENTSYSTEM_CWAGE_H
