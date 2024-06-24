#ifndef EMPLOYEESALARYMANAGEMENTSYSTEM_CMGR_H
#define EMPLOYEESALARYMANAGEMENTSYSTEM_CMGR_H


#include "CManager.h"
#include "CSales.h"

class CMgr : public CManager, public CSales {
private:
    double fixedSalary; // 固定工资
    double salesCommission; // 销售提成

public:
    // 构造函数
    CMgr(string name, string sex, BDay birthday, int lateDays, int leaveDays, double fixedSal, double salesComm,
         double totalSales, double commissionPercent);
    // 计算薪水函数
    void computePay() override;
    // 输出信息函数
    void print_data() const override;
    // 获取固定工资函数
    double get_fixed_salary() const;
    // 获取销售提成函数
    double get_sales_commission() const;
};


#endif //EMPLOYEESALARYMANAGEMENTSYSTEM_CMGR_H
