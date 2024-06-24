#ifndef EMPLOYEESALARYMANAGEMENTSYSTEM_CMANAGER_H
#define EMPLOYEESALARYMANAGEMENTSYSTEM_CMANAGER_H


#include "CEmployee.h"

class CManager : virtual public CEmployee {
private:
    int late;   // 迟到天数，迟到1天扣50元
    int leave;  // 请假天数，迟到1天扣200元
    double m_salary;    // 经理固定薪水1000元

public:
    // 构造函数
    CManager(string name, string sex, BDay birthday, int lateDays, int leaveDays);
    // 输出信息函数
    void print_data() const override;
    // 计算薪水函数
    void computePay() override;
    // 获取迟到天数函数
    int get_late() const;
    // 获取请假天数函数
    int get_leave() const;
    // 获取固定薪水函数
    double get_m_salary() const;
    // 设置迟到天数函数
    void set_late(int lateDays);
    // 设置请假天数函数
    void set_leave(int leaveDays);
};


#endif //EMPLOYEESALARYMANAGEMENTSYSTEM_CMANAGER_H
