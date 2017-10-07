#ifndef LONGS_FIN_H_INCLUDED
#define LONGS_FIN_H_INCLUDED

#include "algos.h"

LongNums& Karatsuba(const LongNums& num1, const LongNums& num2)
{
    vector<int> n1 = num1.i_num, n2 = num2.i_num;
    vector<int> n_res = karatsuba_algo(n1, n2);
    LongNums res(n_res);
    return res;
}

LongNums& Toomthree(const LongNums& num1, const LongNums& num2)
{
    vector<int> n1 = num1.i_num, n2 = num2.i_num;
    vector<int> n_res = toom_three(n1, n2);
    LongNums res(n_res);
    return res;
}

LongNums& ToomCook(const LongNums& num1, const LongNums& num2, const int& n)
{
    vector<int> n1 = num1.i_num, n2 = num2.i_num;
    vector<int> n_res = toom_cook(n1, n2, n);
    LongNums res(n_res);
    return res;
}

#endif // LONGS_FIN_H_INCLUDED
