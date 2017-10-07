#ifndef HELP_HAND_H_INCLUDED
#define HELP_HAND_H_INCLUDED


#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

#include <iostream>
#include <complex>
#include <vector>
#include <string>
#include <sstream>
#include <ctype.h>
//#include <algorithm>

#define M_PI		3.14159265358979323846

using namespace std;

typedef complex<double> base;

const int sys = 10; //try to change those 10 below to sys and see if that works

int get_len(const long long& a)
{
    int i = 1;
    long long b = a;
    while (b >= 10) { // 10 = sys
        b = int (floor(b / 10)); //10 = sys
        ++i;
    }
    return i;
}

void add_zeroes(vector<int>& num, int amount)
{
    if (amount < 0) throw("\n Cannot add negative number of '0'!\n");
    for (int i = 0; i < amount; ++i){num.emplace_back(0);}
}

void print_vector(const vector<int>& num){
    cout<<"\n ";
    int len = num.size();
    for (int i = 1; i <= len; ++i){
        cout<<num[len - i];
    }
}


vector<int> add_vectors(const vector<int>& num1, const vector<int>& num2)
{
    int perenos = 0, curr_sum = 0, leng = 0;
    vector<int> shorter = num1;
    vector<int> longer = num2;
    if (shorter.size() > longer.size()) {shorter = num2; longer = num1;}
    int short_len = shorter.size(), long_len = longer.size();
    vector<int> res_rev; res_rev.resize(0);

    add_zeroes(shorter, long_len - short_len);
    while (leng < long_len){
        curr_sum = (shorter)[leng] + (longer)[leng];
        res_rev.emplace_back( perenos + (curr_sum % sys) );
        perenos = ( curr_sum - ( curr_sum % sys ) ) / sys;
        ++leng;
    }
    if (perenos == 1) {res_rev.emplace_back(1); ++leng;}
    return res_rev;
}


void split_in_two(vector<int> num, vector<int>& res1, vector<int>& res2)
{
    if (num.size() % 2 != 0) add_zeroes(num, 2 - (num.size() % 2) );
    int leng = num.size(), len = num.size() / 2, i = 0;
    res1 = {0}; res1.resize(0);
    res2 = {0}; res2.resize(0);
    while (i < len) {
        res2.emplace_back(num[i]);
        ++i;
    }
    while (i < leng) {
        res1.emplace_back(num[i]);
        ++i;
    }
}

vector<int>* split_in_n(vector<int> num, const int& n)
{
    if (n < 1) throw("\n Cannot split to <1 vectors!\n");
    vector<int>* reses = new vector<int>[n]; for(int i = 0; i < n; ++i) {reses[i]={0}; reses[i].resize(0);}
    int l = num.size();
    if ( (l % n) != 0 ) add_zeroes(num, n - (l % n) );
    int full_leng = num.size(), one_leng = num.size() / n, curr_glob_poss = 0;
    while (curr_glob_poss < full_leng) {
        reses[curr_glob_poss / one_leng].emplace_back(num[curr_glob_poss]);
        ++curr_glob_poss;
    }
    return reses;
}


void multiply_by_base_power(vector<int>& num, const int& n)
{
    if (n < 0) throw("\n Negative number passed to power function!\n");
    for (int i = 1; i <= n; ++i){num.emplace(num.begin(), 0);}
}

void make_vector(vector<int>& num, const int& n)
{
    if (n < 0) throw("\n Negative number passed to power function!\n");
    num.resize(0);
    if (n == 0) {num = {0}; return;}
    int a = n;
    while (a > 9) {
        num.emplace_back(a%10);
        a /= 10;
    }
    num.emplace_back(a);
}

void cut_zeroes(vector<int>& num)
{
    int l = num.size();
    if (l == 0) return;
    while (num[l - 1] == 0) {
        num.resize(l - 1);
        l--;
    }
}

int get_int(const vector<int>& num)
{
    vector<int> a = num;
    cut_zeroes(a);
    if (a.size() > 10) throw("\n Too large number to convert!\n");
    if (a.size() == 0) return 0;
    int r = 0, l = num.size(), b = 1;
    for (int i = 0; i < l; ++i) {
        //r += (num[i] * pow(sys, i));
        r += (num[i] * b);
        b *= sys;
    }
    return r;
}


void make_equal_sizes(vector<int>& n1, vector<int>& n2)
{
    int longer = n1.size();
    if (longer < n2.size()) longer = n2.size();
    add_zeroes(n1, longer - n1.size());
    add_zeroes(n2, longer - n2.size());
}

int compare_vectors(const vector<int>& num1, const vector<int>& num2)
{
    vector<int> n1 = num1, n2 = num2;
    cut_zeroes(n1);
    cut_zeroes(n2);
    if (n1.size() > n2.size()) return 1;
    if (n2.size() > n1.size()) return -1;
    {
        int i = n1.size() - 1;
        while(n1[i] == n2[i] && i >= 0) {--i;}
        if (i == -1) return 0;
        if (n1[i] > n2[i]) return 1;
        if (n2[i] > n1[i]) return -1;
    }
    return 0;
}

vector<int> subtract__vectors(const vector<int>& num1, const vector<int>& num2)
{
    if (compare_vectors(num1, num2) == -1) throw("\n Cannot subtract vectors!\n");
    int perenos = 0, curr_sum = 0, leng = 0;
    vector<int> bigger = num1, smaller = num2;
    int big_len = bigger.size(), smal_len = smaller.size();
    vector<int> res_rev; res_rev.resize(0);
    add_zeroes(smaller, big_len - smal_len);
    while (leng < big_len){
        curr_sum = (bigger)[leng] - (smaller)[leng] + perenos;
        if (curr_sum < 0) {curr_sum += sys; perenos = -1;} else perenos = 0;
        while (curr_sum < 0) {curr_sum += sys; perenos--;} //sys = 10
        res_rev.emplace_back(curr_sum % sys);// sys = 10
        //if (res_rev[leng] != 0) real_leng = leng;
        //perenos = ( curr_sum - ( curr_sum % sys ) ) / sys;
        ++leng;
    }
    //if (perenos < 0) res_rev.emplace_back(perenos);
    return res_rev;
}

vector<int> divide_vectors(vector<int> a, const vector<int>& b) // returns int (a / b)
{
    vector<int> one{1}, counter{0}, b0 = b;
    cut_zeroes(a);
    cut_zeroes(b0);
    if (b0.size() == 0) throw("\n Division by zero vector! \n");
    if (a.size() == 0) return counter;
    while (compare_vectors(a, b0) == 1) {
        a = subtract__vectors(a, b0);
        counter = add_vectors(counter, one);
    }
    if (compare_vectors(a, b0) == -1) return counter;
    counter = add_vectors(counter, one);
    return counter;
}

vector<int> get_modulo(vector<int> a, const vector<int>& b) // returns a mod b = a % b
{
    vector<int> b0 = b;
    cut_zeroes(a);
    cut_zeroes(b0);
    if (b0.size() == 0) throw("\n Division by zero vector! \n");
    if (a.size() == 0) {a.emplace_back(0); return a;}
    while (compare_vectors(a, b0) == 1) {
        a = subtract__vectors(a, b0);
    }
    return a;
}

void increase_by_one(vector<int>& a)
{
    vector<int> one{1};
    if (a.size() == 0) a = one; else
    a = add_vectors(a, one);
}


vector<base> fft(const vector<base> & num, bool invert) // returns values of (n-1)-degree polynomial in n points of (-1)^(1/n)
{
    vector<base> a = num;
	int n = (int) a.size();
	if (n == 1)  return a;

	vector<base> a0 (n/2),  a1 (n/2);
	for (int i=0, j=0; i<n; i+=2, ++j) {
		a0[j] = a[i];
		a1[j] = a[i+1];
	}
	fft (a0, invert);
	fft (a1, invert);

	double ang = 2 * M_PI / n * (invert ? -1 : 1);
	base w (1),  wn (cos(ang), sin(ang));
	for (int i=0; i<n/2; ++i) {
		a[i] = a0[i] + w * a1[i];
		a[i+n/2] = a0[i] - w * a1[i];
		if (invert)
			a[i] /= 2,  a[i+n/2] /= 2;
		w *= wn;
	}

    return a;
}


#endif // HELP_HAND_H_INCLUDED
