#ifndef LONGS_H_INCLUDED
#define LONGS_H_INCLUDED

#include "help_hand.h"

class LongNums
{
private:
    static const int sys = 10;
    int len;

public:
    vector<int> i_num;
    //vector<char> c_num;
    //Multer *m;


public:
    LongNums(const long long& a);
    LongNums(const int& leng, const std::string number);
    LongNums(const vector<int>& number);
    //LongNums_0& operator *(const LongNums_0& other)const;
    operator string()const;
    bool operator <(const LongNums& other)const;
    bool operator ==(const LongNums& other)const;
    LongNums& operator +(const LongNums& other)const;
    LongNums& operator -(const LongNums& other)const;
    LongNums& karatsuba(const LongNums& other)const;
    //LongNums& get_time((*f), const LongNums& other)const;
};

LongNums::LongNums(const long long& a):len(get_len(a))
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
}

LongNums::LongNums(const int& leng, const std::string number)
{
    int s = number.size(); bool flag = 0;
    for (int i = 1; i <= s; ++i){
        //if ( !isdigit(number[i-1]) ) throw("\n Not a number passed as an argument!\n");
        if ( !(number[i-1] > 46 && number[i-1] < 58) ) throw("\n Not a number passed as an argument!\n");
        //i_num[len - i] = number[i-1];
        if (number[s - i] == '0' && flag == 0) {} else {
            this->i_num.emplace_back( (number[s - i] - '0') );
            flag = 1;
        }
    }
    len = i_num.size();
}

LongNums::LongNums(const vector<int>& number)
{
    int s = number.size(); bool flag = 0;
    this->i_num.resize(0);

    /*
    for (int i = 1; i <= s; ++i){
        //if ( !isdigit(number[i-1]) ) throw("\n Not a number passed as an argument!\n");
        //if ( !(number[i-1] > 46 && number[i-1] < 58) ) throw("\n Not a number passed as an argument!\n");
        if (number[s - i] == 0 && flag == 0) {} else {
            this->i_num.emplace(i_num.begin(), number[s - i]);
            flag = 1;
        }
    } */


    vector<int> a = number;
    cut_zeroes(a);
    s = a.size();
    for (int i = 1; i<= s; ++i) {
        this->i_num.emplace(i_num.begin(), a[s - i]);
    }


    len = this->i_num.size();
}

LongNums::operator string()const{
    std::ostringstream oss;
    for (int i = 0; i < len; ++i){
        oss<<this->i_num[len - 1 - i];
    }
    return oss.str();
}

bool LongNums::operator <(const LongNums& other) const{
    if (this->len < other.len) return 1;
    if (this->len > other.len) return 0;
    int i = other.i_num.size() - 1;
    while(this->i_num[i] == other.i_num[i] && i >= 0)
    {--i;}
    if (i == -1) return 0;
    if (this->i_num[i] > other.i_num[i]) return 0;
    return 1;
}

bool LongNums::operator ==(const LongNums& other)const{
    if (this->i_num.size() != other.i_num.size()) return 0;
    int i = other.i_num.size() - 1;
    while(this->i_num[i] == other.i_num[i] && i >= 0)
    {--i;}
    if (i == -1) return 1;
    return 0;
}

LongNums& LongNums::operator+(const LongNums& other) const{
    int perenos = 0, curr_sum = 0, leng = 0;
    vector<int> shorter = this->i_num;
    vector<int> longer = other.i_num;
    int short_len = this->len, long_len = other.len;
    if (this->len > other.len) {shorter = other.i_num; longer = this->i_num; short_len = other.len; long_len = this->len;}
    //int* sizea = &leng;
    vector<int> res_rev; res_rev.resize(0);

    add_zeroes(shorter, long_len - short_len);
    while (leng < long_len){
        curr_sum = (shorter)[leng] + (longer)[leng];
        res_rev.emplace_back( perenos + (curr_sum % sys) );
        perenos = ( curr_sum - ( curr_sum % sys ) ) / sys;
        ++leng;
    }

    /*
    while (leng < short_len){
        curr_sum = (shorter)[leng] + (longer)[leng];
        res_rev[leng] = perenos + (curr_sum % sys);
        perenos = ( curr_sum - ( curr_sum % sys ) ) / sys;
        ++leng;
    }
    while (leng < long_len){
        curr_sum = (longer)[leng] + perenos;
        res_rev[leng] = (curr_sum % sys);
        perenos = curr_sum - (curr_sum % sys);
        ++leng;
    } */


    if (perenos == 1) {res_rev.emplace_back(1); ++leng;}
    //for(int i=0; i<res_rev.size(); ++i){cout<<res_rev[i];}

    LongNums res(res_rev);
    //LongNums_0* res_; res_ = &res;
    return res;//(*res_)
}

LongNums& LongNums::operator-(const LongNums& other) const{
    int perenos = 0, curr_sum = 0, leng = 0; //real_leng;
    if ((*this) < other) throw("\n Cannot substract! Negative result!\n");
    if ((*this) == other) {
        LongNums res(0);
        return res;
    }
    vector<int> shorter = other.i_num;
    vector<int> longer = this->i_num;
    int short_len = other.len, long_len = this->len;
    vector<int> res_rev; res_rev.resize(0);
    //vector<int> res_rev = {0}; res_rev.resize(long_len);

    add_zeroes(shorter, long_len - short_len);
    while (leng < long_len){
        curr_sum = (longer)[leng] - (shorter)[leng] + perenos;
        if (curr_sum < 0) {curr_sum += 10; perenos = -1;} else perenos = 0;
        while (curr_sum < 0) {curr_sum += 10; perenos--;}
        res_rev.emplace_back(curr_sum % sys);
        //if (res_rev[leng] != 0) real_leng = leng;
        //perenos = ( curr_sum - ( curr_sum % sys ) ) / sys;
        ++leng;
    }
    //res_rev.resize(real_leng);
    //if (perenos == 1) {res_rev.emplace_back(1); ++leng;}
    LongNums res(res_rev);
    return res;
}




#endif // LONGS_H_INCLUDED
