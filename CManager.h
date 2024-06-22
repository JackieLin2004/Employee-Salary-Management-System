#ifndef EMPLOYEESALARYMANAGEMENTSYSTEM_CMANAGER_H
#define EMPLOYEESALARYMANAGEMENTSYSTEM_CMANAGER_H


#include "CEmployee.h"

class CManager : virtual public CEmployee {
private:
    int late;   // 迟到天数，迟到1天扣50元
    int leave;  // 请假天数，迟到1天扣200元
    double m_salary;    // 经理固定薪水1000元

public:
    CManager(string name, string sex, BDay birthday, int lateDays, int leaveDays);

    void print_data() const override;

    void computePay() override;

    int get_late() const;

    int get_leave() const;

    double get_m_salary() const;

    void set_late(int lateDays);

    void set_leave(int leaveDays);
};


#endif //EMPLOYEESALARYMANAGEMENTSYSTEM_CMANAGER_H
