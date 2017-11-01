#ifndef FLOAT_LONG_H_INCLUDED
#define FLOAT_LONG_H_INCLUDED

//#include "longs.h"'
//#include "help_hand.h"
#include "algos.h"

class FloatLong// : public LongNums
{
private:
    static const int sys = 10;
    int len, i_s, f_s;
    int digits_after_dot;

public:
    vector<int> i_num;
    vector<int> i_part, f_part;
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
    bool operator <(const FloatLong& other)const;
    bool operator ==(const FloatLong& other)const;
    FloatLong& operator =(const FloatLong& other);
    ///FloatLong& operator =(FloatLong&& other);
    FloatLong& operator +(const FloatLong& other)const;
    FloatLong& operator -(const FloatLong& other)const;
    //FloatLong& karatsuba(const LongNums& other)const;
    FloatLong& operator* (const FloatLong& other)const;
    ///FloatLong& operator>>(const int& k)const;
    FloatLong& operator<<(const int& k)const;
    FloatLong& operator*=(const FloatLong& other);
    FloatLong& operator+=(const FloatLong& other);
    ///FloatLong& operator>>=(const int& k);
};

FloatLong::FloatLong()
{
    i_num = {0};
    i_part = {0};
    f_part = {0};
    i_s = 0;
    f_s = 0;
    digits_after_dot = 0;
}

FloatLong::FloatLong(const long long& a):len(get_len(a)), digits_after_dot(0)
{
    if (a < 0) throw("\n Cannot assign negative value!\n");
    i_num.resize(len);
    int j = 1;
    long long b = a;
    while (b > 9){
        int mod = b % 10;
        b = (b - mod) / 10;
        i_num[len - j] = mod;
        ++j;
    }
    i_num[len - j] = b;
    i_part = i_num;
    f_part = {0};
    i_s = i_num.size();
    f_s = 0;
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
    if (digits_after_dot == 0) i_num = i_part; else
    i_num = merge_i_and_f(i_part, f_part);
    len = i_s + f_s;
}

FloatLong::FloatLong(const vector<int>& int_p, const vector<int>& frac_p)
{
    this->build_with_i_f(int_p, frac_p);
}

FloatLong::FloatLong(const double& a, const int& decimals)
{
    if (a < 0) throw("\n Cannot assign negative value!\n");
    if (decimals < 0) throw("\n Number cannot have negative number of decimals after dot!\n");
    if (a == 0) {
        i_num = {0};
        i_part = {0};
        f_part = {0};
        i_s = 0;
        f_s = 0;
        digits_after_dot = 0;
        ///this -> FloatLong(0);
        /// this->build_with_i_f({0},{0});
    }
    int i = floor(a);
    vector<int> i_p;
    make_vector_base(i_p, i, 2);
    double f = a - i;
    if (decimals == 0) {
        i_part = i_p;
        f_part = {0};
        this -> build_with_i_f(i_p, f_part);
    } else {
    int f_ = (int)(f* pow(10, decimals));///int f_ = (int)( f * pow(10, digits_after_dot) );
    vector<int> f_p;
    make_vector_base(f_p, f_, 2);
    this -> build_with_i_f(i_p, f_p);
    }
}

FloatLong::FloatLong(const vector<int>& number, int digs_after_dot)
{
    if (digs_after_dot < 0) throw("\n Number cannot have negative number of decimals after dot!\n");
    if (number.size() == 0) {

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
    }
}

FloatLong::operator string()const{
    std::ostringstream oss;
    for (int i = 0; i < i_s; ++i){
        oss<<this->i_part[i_s - i - 1];
    }
    oss<<'.';
    for (int i = 0; i < f_s; ++i){
        oss<<this->f_part[f_s - i - 1];
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

FloatLong& FloatLong::operator+(const FloatLong& other)const
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

FloatLong& FloatLong::operator-(const FloatLong& other)const
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

FloatLong& FloatLong::operator*(const FloatLong& other)const
{
    vector<int> res_v = karatsuba_algo(this->i_num, other.i_num);
    int digs = this->digits_after_dot + other.digits_after_dot;
    FloatLong res(res_v, digs);
    return res;//(*res_)
}

FloatLong& FloatLong::operator<<(const int& k)const
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

FloatLong& FloatLong::operator*=(const FloatLong& other)
{
    (*this) = (*this) * other;
    return (*this);
}

FloatLong& FloatLong::operator+=(const FloatLong& other)
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

FloatLong& inverse(const vector<int>& num)
{

}

#endif // FLOAT_LONG_H_INCLUDED
