#ifndef FLOAT_LONG_H_INCLUDED
#define FLOAT_LONG_H_INCLUDED

//#include "longs.h"'
//#include "help_hand.h"
#include "algos.h"

/// 02.11.17 - changed operator '=' to return not FloatLong&, but but
/// 02.11.17 - changed back but added 'return (*this);'
/// 02.11.17 - changed operators '+', '-', '*', '<<', and others, return type from FloatLong& to FloatLong

const int base_sys = 2;/// dublicates FloatLong::sys

class FloatLong// : public LongNums
{
private:
    static const int sys = 2;
    int len, i_s, f_s;
    int digits_after_dot;

public:
    vector<int> i_num;
    vector<int> i_part, f_part;
    bool is_int = false;
    //vector<char> c_num;
    //Multer *m;


public:
    FloatLong();
    FloatLong(const long long& a);
    FloatLong(const double& a, const int& decimals);//decimals == digits after dot
    void build_with_i_f(const vector<int>& int_p, const vector<int>& frac_p);
    //FloatLong(const LongNums& n);
    //FloatLong(const int& leng, const std::string number);
    FloatLong(const vector<int>& int_p, const vector<int>& frac_p);
    FloatLong(const vector<int>& number, int digs_after_dot);
    //LongNums_0& operator *(const LongNums_0& other)const;
    void print();
    void update_f(const vector<int>& f_p);
    operator string()const;
    ///bool operator <(const FloatLong& other)const;
    bool operator ==(const FloatLong& other)const;
    FloatLong& operator =(const FloatLong& other);
    ///FloatLong& operator =(FloatLong&& other);
    FloatLong operator +(const FloatLong& other)const;
    FloatLong operator -(const FloatLong& other)const;
    //FloatLong& karatsuba(const LongNums& other)const;
    FloatLong operator* (const FloatLong& other)const;
    ///FloatLong& operator>>(const int& k)const;
    FloatLong operator<<(const int& k)const;
    FloatLong operator*=(const FloatLong& other);
    FloatLong operator+=(const FloatLong& other);
    ///FloatLong& operator>>=(const int& k);
};

FloatLong::FloatLong()
{
    i_num = {0};
    i_part = {0};
    f_part = {0};
    i_s = 1;
    f_s = 1;
    digits_after_dot = 0;
    len = 2;
    is_int = true;
}

FloatLong::FloatLong(const long long& a):digits_after_dot(0), is_int(true)
{
    if (a < 0) throw("\n Cannot assign negative value!\n");
    make_vector_base(i_part, a, base_sys);
    f_part = {0};
    i_num = merge_i_and_f(i_part, f_part);
    i_s = i_part.size();
    f_s = 1;
    len = i_s + f_s;
}

void FloatLong::build_with_i_f(const vector<int>& int_p, const vector<int>& frac_p)
{
    vector<int> i_p = int_p, f_p = frac_p;
    cut_zeroes(i_p);
    cut_zeroes_back(f_p);
    if (i_p.size() == 0) i_part = {0};
    else i_part = i_p;
    if (f_p.size() == 0) {f_part = {0}; digits_after_dot = 0;}
    else {f_part = f_p; digits_after_dot = f_p.size();}
    i_s = i_part.size();
    f_s = f_part.size();
    //if (digits_after_dot == 0) i_num = i_part; else
    i_num = merge_i_and_f(i_part, f_part);
    len = i_s + f_s;
}

FloatLong::FloatLong(const vector<int>& int_p, const vector<int>& frac_p)
{
    this->build_with_i_f(int_p, frac_p);
    if (f_s == 0) is_int = true;
}

FloatLong::FloatLong(const double& a, const int& decimals)
{
    if (a < 0) throw("\n Cannot assign negative value!\n");
    if (decimals < 0) throw("\n Number cannot have negative number of decimals after dot!\n");
    if (a == 0) {
        i_num = {0};
        i_part = {0};
        f_part = {0};
        i_s = 1;
        f_s = 1;
        digits_after_dot = 0;
        is_int = true;
        len = 2;
        return;
        ///this -> FloatLong(0);
        /// this->build_with_i_f({0},{0});
    }
    int i = floor(a);
    vector<int> i_p;
    make_vector_base(i_p, i, base_sys);
    if (decimals == 0) {
        i_part = i_p;
        f_part = {0};
        is_int = true;
        this -> build_with_i_f(i_p, f_part);
    } else {
    vector<int> f_p = make_float(a, decimals);
    this -> build_with_i_f(i_p, f_p);
    ///if (f_s == 0) is_int = true;
    }
}

FloatLong::FloatLong(const vector<int>& number, int digs_after_dot)
{
    if (digs_after_dot < 0) throw("\n Number cannot have negative number of decimals after dot!\n");
    if (number.size() == 0) {
        i_num = {0};
        i_part = {0};
        f_part = {0};
        i_s = 1;
        f_s = 1;
        digits_after_dot = 0;
        is_int = true;
        len = 2;
    } else {
    vector<int> i_p, f_p;
    int i = 0;
    while (i < digs_after_dot)
    {
        f_p.emplace_back(number[i]);
        ++i;
    }
    while (i < number.size())
    {
        i_p.emplace_back(number[i]);
        ++i;
    }
    this -> build_with_i_f(i_p, f_p);
    if (f_s == 0) is_int = true;
    }
}

FloatLong::operator string()const{
    std::ostringstream oss;
    int ips = i_part.size(), fps = f_part.size();
    for (int i = 0; i < ips; ++i){
        oss<<this->i_part[ips - i - 1];
    }
    oss<<'.';
    for (int i = 0; i < fps; ++i){
        oss<<this->f_part[fps - i - 1];
    }
    return oss.str();
}

void FloatLong::print()
{
    cout<<string(*this)<<endl;
}

FloatLong& FloatLong::operator =(const FloatLong& other)
{
    this->i_num = other.i_num;
    this->i_part = other.i_part;
    this->f_part = other.f_part;
    this->i_s = other.i_s;
    this->f_s = other.f_s;
    this->digits_after_dot = other.digits_after_dot;
    return (*this);
}

void FloatLong::update_f(const vector<int>& f_p)
{
    this->build_with_i_f(i_part, f_p);
}

/**
FloatLong& FloatLong::operator =(FloatLong&& other)
{

}
**/

bool FloatLong::operator ==(const FloatLong& other)const
{
    if (this->i_num.size() != other.i_num.size() || this->digits_after_dot != other.digits_after_dot) return 0;
    int i = other.i_num.size() - 1;
    while(this->i_num[i] == other.i_num[i] && i >= 0)
    {--i;}
    if (i == -1) return 1;
    return 0;
}

FloatLong FloatLong::operator+(const FloatLong& other)const
{
    //vector<int> res_rev; res_rev.resize(0);
    vector<int> n1_i = this->i_part, n1_f = this->f_part, n2_i = other.i_part, n2_f = other.f_part;
    make_equal_sizes(n1_i, n2_i);
    make_equal_sizes_back(n1_f, n2_f);
    vector<int> n1 = merge_i_and_f(n1_i, n1_f);
    vector<int> n2 = merge_i_and_f(n2_i, n2_f);
    vector<int> n_res = add_vectors(n1, n2);
    int digs = this->digits_after_dot, digs2 = other.digits_after_dot;
    if (digs < digs2) digs = digs2;
    FloatLong res(n_res, digs);
    return res;//(*res_)
}

FloatLong FloatLong::operator-(const FloatLong& other)const
{
    //vector<int> res_rev; res_rev.resize(0);
    vector<int> n1_i = this->i_part, n1_f = this->f_part, n2_i = other.i_part, n2_f = other.f_part;
    make_equal_sizes(n1_i, n2_i);
    make_equal_sizes_back(n1_f, n2_f);
    vector<int> n1 = merge_i_and_f(n1_i, n1_f);
    vector<int> n2 = merge_i_and_f(n2_i, n2_f);
    vector<int> n_res = subtract_vectors(n1, n2);
    int digs = this->digits_after_dot, digs2 = other.digits_after_dot;
    if (digs < digs2) digs = digs2;
    FloatLong res(n_res, digs);
    return res;//(*res_)
}

FloatLong FloatLong::operator*(const FloatLong& other)const
{
    vector<int> res_v = karatsuba_algo(this->i_num, other.i_num);
    int digs = this->digits_after_dot + other.digits_after_dot;
    FloatLong res(res_v, digs);
    return res;//(*res_)
}

FloatLong FloatLong::operator<<(const int& k)const
{
    if (k < 0) throw("\n Cannot move by negative value!\n");
    vector<int> num = this->i_num;
    int digs = digits_after_dot;
    digs -= k;
    if (digs < 0) {
        add_zeroes(num, -digs);
        digs = 0;
    }
    FloatLong res(num, digs);
    return res;
}

/**
FloatLong& FloatLong::operator>>(const int& k)const
{
    vector<int> num = this->i_num;
    cut_last(num, k);
    vector<int> res_v = num;
    int digs = this->digits_after_dot - k;
    if (digs < 0) digs = 0;
    FloatLong res(res_v, digs);
    return res;
}
**/

FloatLong FloatLong::operator*=(const FloatLong& other)
{
    (*this) = (*this) * other;
    return (*this);
}

FloatLong FloatLong::operator+=(const FloatLong& other)
{
    (*this) = (*this) + other;
    return (*this);
}

/**
FloatLong& FloatLong::operator>>=(const int& k)
{
    (*this) = (*this) >> k;
    return (*this);
}
**/

/**
FloatLong& inverse(const vector<int>& num)
{

}
**/

#endif // FLOAT_LONG_H_INCLUDED
