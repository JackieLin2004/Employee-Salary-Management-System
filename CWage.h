#ifndef EMPLOYEESALARYMANAGEMENTSYSTEM_CWAGE_H
#define EMPLOYEESALARYMANAGEMENTSYSTEM_CWAGE_H


#include "CSales.h"

class CWage : public CSales {
private:
    double time;    // 工作小时数
    double hourmo;  // 时薪
    double salesCommission; // 销售提成

public:
    CWage(string name, string sex, BDay birthday, double totalSales, double commissionPercent, double timeWorked,
          double hourlyRate);

    void computePay() override;

    void print_data() const override;

    double get_time() const;

    double get_hourly_rate() const;

    double get_sales_commission() const;

    void set_time(double timeWorked);

    void set_hourly_rate(double hourlyRate);
};


#endif //EMPLOYEESALARYMANAGEMENTSYSTEM_CWAGE_H
