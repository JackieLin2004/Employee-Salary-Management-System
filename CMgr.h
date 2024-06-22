#ifndef EMPLOYEESALARYMANAGEMENTSYSTEM_CMGR_H
#define EMPLOYEESALARYMANAGEMENTSYSTEM_CMGR_H


#include "CManager.h"
#include "CSales.h"

class CMgr : public CManager, public CSales {
private:
    double fixedSalary; // 固定工资
    double salesCommission; // 销售提成

public:
    CMgr(string name, string sex, BDay birthday, int lateDays, int leaveDays, double fixedSal, double salesComm,
         double totalSales, double commissionPercent);

    void computePay() override;

    void print_data() const override;

    double get_fixed_salary() const;

    double get_sales_commission() const;
};


#endif //EMPLOYEESALARYMANAGEMENTSYSTEM_CMGR_H
