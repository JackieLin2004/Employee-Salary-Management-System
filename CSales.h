#ifndef EMPLOYEESALARYMANAGEMENTSYSTEM_CSALES_H
#define EMPLOYEESALARYMANAGEMENTSYSTEM_CSALES_H


#include "CEmployee.h"

class CSales : virtual public CEmployee {
private:
    double total;   // 销售总额
    double percent; // 销售提成

public:
    CSales(string name, string sex, BDay birthday, double totalSales, double commissionPercent);

    void print_data() const override;

    void computePay() override;

    double get_total_sales() const;

    double get_commission_percent() const;

    void set_total_sales(double totalSales);

    void set_commission_percent(double commissionPercent);
};


#endif //EMPLOYEESALARYMANAGEMENTSYSTEM_CSALES_H
