#ifndef ALGOS_H_INCLUDED
#define ALGOS_H_INCLUDED

#include "help_hand.h"
#include "longs.h"

const vector<int> one{1}, two{2};

vector<int> subtract_vectors(const vector<int>& num1, const vector<int>& num2)
{
    if (compare_vectors(num1, num2) == -1) throw("\n Cannot subtract vectors!\n");
    int perenos = 0, curr_sum = 0, leng = 0;
    vector<int> bigger = num1, smaller = num2;
    LongNums n1(num1), n2(num2);
    if (n1 < n2) {bigger = num2; smaller = num1;}
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

vector<int> karatsuba_algo(vector<int> num1, vector<int> num2)
{
    vector<int> res_num; res_num.resize(0);
    int longer = num1.size();
    if (longer < num2.size()) longer = num2.size();
    if (longer % 2 == 1) longer++;
    int len = longer / 2;
    add_zeroes(num1, longer - num1.size());
    add_zeroes(num2, longer - num2.size());
    if (num1.size() < 3) {
        int n1 = get_int(num1),
        n2 = get_int(num2),
        n = n1*n2;
        vector<int> n_res;
        make_vector(n_res, n);
        return n_res;
    }
    vector<int> a{0}, b{0}, c{0}, d{0};
    split_in_two(num1, a, b);
    split_in_two(num2, c, d);
    /*
    vector<int> *a0 = new vector<int>,
                *b0 = new vector<int>,
                *d1 = new vector<int>,
                *d2 = new vector<int>,
                *d3 = new vector<int>;
                *a0 = add_vectors(a,b);
                *b0 = add_vectors(c,d);
                *d1 = karatsuba_algo((*a0), (*b0));
                // *d1 = karatsuba_algo(add_vectors(a, b), add_vectors(c ,d));
                *d2 = karatsuba_algo(a, c);
                *d3 = karatsuba_algo(b, d);
    delete a0; delete b0;
    */

    vector<int> a0 = add_vectors(a,b),
                b0 = add_vectors(c,d),
                d1 = karatsuba_algo(a0, b0),
                //*d1 = karatsuba_algo(add_vectors(a, b), add_vectors(c ,d));
                d2 = karatsuba_algo(a, c),
                d3 = karatsuba_algo(b, d);


    vector<int> *d4 = new vector<int>;
    *d4 = subtract_vectors(subtract_vectors(d1, d2), d3);
    //*d4 = subtract_vectors(subtract_vectors((*d1), (*d2)), (*d3));
    multiply_by_base_power((*d4), len);
    multiply_by_base_power(d2, longer);
    //for(int i = 0; i < longer; ++i){d2->emplace(d2->begin(), 0);}
    //for(int i = 0; i < len; ++i){d4->emplace(d4->begin(), 0);}
    res_num = add_vectors(*d4, add_vectors(d2, d3));
    return res_num;
}


vector<int> toom_cook(vector<int> num1, vector<int> num2, const int& n)
{
    vector<int> n1 = num1, n2 = num2;
    cut_zeroes(n1);
    cut_zeroes(n2);
    if (n1.size() == 0 || n2.size() == 0) {vector<int> res{0}; return res;}
    if (n1.size() < 3 && n2.size() < 3) {
        int n_1 = get_int(n1),
        n_2 = get_int(n2),
        n = n_1*n_2;
        vector<int> n_res;
        make_vector(n_res, n);
        return n_res;
    }

    make_equal_sizes(n1, n2);
    vector<int>* nums1 = split_in_n(n1, n);
    vector<int>* nums2 = split_in_n(n2, n);
    int step = 0;
    if (n1.size() % n > 0) ++step;
    step += n1.size() / n;

    vector<int>* new_powers = new vector<int>[2*n-1]; for (int i = 0; i < (2*n-1); ++i) {new_powers[i] = {0};}
    vector<int> gen_sum1{0}, gen_sum2{0};
    for (int i = 0; i < n; ++i){
        gen_sum1 = add_vectors(gen_sum1, nums1[i]);
        gen_sum2 = add_vectors(gen_sum2, nums2[i]);
    }
    vector<int> all_product = toom_cook(gen_sum1, gen_sum2, n);
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j <= i; ++j) {
            new_powers[i] = add_vectors( new_powers[i], toom_cook(nums1[j], nums2[i-j], n) );
        }
    }
    for (int i = 2*n - 2; i > n - 1; --i) {
        for (int j = n - 1; j >= i - (n - 1); --j) {
            new_powers[i] = add_vectors( new_powers[i], toom_cook(nums1[j], nums2[i-j], n) );
        }
    }
    delete[] nums1;
	delete[] nums2;

    vector<int> sum_all_except_mid{0};
    int j = 0;
    while (j < (2*n-1) ) {
        if (j != n-1) sum_all_except_mid = add_vectors(sum_all_except_mid, new_powers[j]);
        ++j;
    }
    new_powers[n - 1] = subtract_vectors(all_product, sum_all_except_mid);
    vector<int> res_num; res_num.resize(0);
    for (int i = 0; i < (2*n-1); ++i) {
        multiply_by_base_power(new_powers[i], i*step);
        res_num = add_vectors(res_num, new_powers[i]);
    }
    //cut_zeroes(res_num);
    return res_num;
}


vector<int> toom_three(vector<int>& num1, vector<int>& num2)
{
    return toom_cook(num1, num2, 3);
}

vector<int> get_squared(const vector<int>& a)
{
    vector<int> res = toom_cook(a, a, 2);
    return res;
}

////////////////////////////////////////////////////////////////////////
/*
vector<int> bad_toom_cook(vector<int> num1, vector<int> num2, const int& n)
{
    vector<int> n1 = num1, n2 = num2;
    cut_zeroes(n1);
    cut_zeroes(n2);
    if (n1.size() == 0 || n2.size() == 0) {vector<int> res{0}; return res;}
    if (n1.size() < 3 && n2.size() < 3) {
        int n_1 = get_int(n1),
        n_2 = get_int(n2),
        n = n_1*n_2;
        vector<int> n_res;
        make_vector(n_res, n);
        return n_res;
    }

    make_equal_sizes(n1, n2);
    vector<int>* nums1 = split_in_n(n1, n);
    vector<int>* nums2 = split_in_n(n2, n);
    int step = 0;
    if (n1.size() % n > 0) ++step;
    step += n1.size() / n;

    vector<int>* new_powers = new vector<int>[2*n-1]; for (int i = 0; i < (2*n-1); ++i) {new_powers[i] = {0};}
    vector<int> gen_sum1{0}, gen_sum2{0};
    for (int i = 0; i < n; ++i){
        gen_sum1 = add_vectors(gen_sum1, nums1[i]);
        gen_sum2 = add_vectors(gen_sum2, nums2[i]);
    }
    vector<int> all_product = toom_cook(gen_sum1, gen_sum2, n);
    for (int i = 0; i <= n - 1; ++i) {
        for (int j = 0; j <= i; ++j) {
            new_powers[i] = add_vectors( new_powers[i], toom_cook(nums1[j], nums2[i-j], n) );
        }
    }
    for (int i = 2*n - 2; i > n - 1; --i) {
        for (int j = n - 1; j >= i - (n - 1); --j) {
            new_powers[i] = add_vectors( new_powers[i], toom_cook(nums1[j], nums2[i-j], n) );
        }
    }
    delete[] nums1;
	delete[] nums2;

    vector<int> res_num; res_num.resize(0);
    for (int i = 0; i < (2*n-1); ++i) {
        multiply_by_base_power(new_powers[i], i*step);
        res_num = add_vectors(res_num, new_powers[i]);
    }
    //cut_zeroes(res_num);
    return res_num;
}
*/
////////////////////////////////////////////////////////////////////////


vector<int> shtrassen(vector<int> a, vector<int> b)
{
    make_equal_sizes(a, b);
    add_zeroes(a, a.size());
    add_zeroes(b, b.size());
    int n = a.size();
    vector<base> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
	/*
	size_t n = 1;
	while (n < max (a.size(), b.size()))  n <<= 1;
	n <<= 1;
	fa.resize (n),  fb.resize (n);
	*/

	fa = fft(fa, false);
	fb = fft(fb, false);
	for (int i=0; i < n; ++i)
		fa[i] *= fb[i];
	fa = fft(fa, true);

    vector<int> res;
	res.resize (n);
	for (int i=0; i < n; ++i)
		res[i] = int (fa[i].real() + 0.5);

    int carry = 0;
	for (int i=0; i < n; ++i) {
		res[i] += carry;
		carry = res[i] / sys;
		res[i] %= sys;
	}

    return res;

///////////////////////////////////////////////////////////////////
    /*
    vector<int> n1 = num1, n2 = num2;
    cut_zeroes(n1);
    cut_zeroes(n2);
    if (n1.size() == 0 || n2.size() == 0) {vector<int> res{0}; return res;}
    if (n1.size() < 3 && n2.size() < 3) {
        int n_1 = get_int(n1),
        n_2 = get_int(n2),
        n = n_1*n_2;
        vector<int> n_res;
        make_vector(n_res, n);
        return n_res;
    }

    make_equal_sizes(n1, n2);
    int len = n1.size();
    add_zeroes(n1, len);
    add_zeroes(n2, len);
    vector<int> res_vals; res_vals.resize(0);
    vector<int> vals1 = fft(n1);
    vector<int> vals2 = fft(n2);
    for (int i = 0; i < 2*len; ++i)
    {
        res_vals[i] = vals1[i] * vals2[i];
    }
    vector<int> res_num = rfft(res_vals);
    return res_num;
    */
}


bool lemers_luke(vector<int> a)
{
    if (a.size() == 0) throw("\n Empty vector!\n");
    if (a[0] % 2 == 0) throw("\n Even number passed as an argument!\n");
    vector<int> k{1}, s{4}, m{2};
    //int k = 1, s = 4;
    while (compare_vectors(k, a) != 0) {m = multiply_by_digit(m, 2); increase_by_one(k);}

    k = one; // k = 1;
    m = subtract_vectors(m, k);
    while (compare_vectors(k, subtract_vectors(s, one)) != 0)
    {
        s = get_modulo(subtract_vectors(get_squared(s), two), m);
        increase_by_one(k);
    }

    /*  // for k - a long number, k is the power
    k = one;
    m = subtract_vectors(m, k);
    while (compare_vectors(k, subtract_vectors(s, one)) != 0)
    {
        s = get_modulo(subtract_vectors(get_squared(s), two), m);
        increase_by_one(k);
    }
    */

    cut_zeroes(s);
    if (s.size() == 0) return true; // is prime
    return false; //is complex
}

bool lemers_luke_int(int a)
{
    //if (a.size() == 0) throw("\n Empty vector!\n");
    if (a % 2 == 0) throw("\n Even number passed as an argument!\n");
    long long k = 1, s = 4, m = 2;
    while (k != a) {m *= 2; ++k;}
    k = 1;
    m -= k;
    while (k != s - 1)
    {
        //s = get_modulo(subtract_vectors(get_squared(s), two), m);
        s = (s * s - 2) % m;
        ++k;
    }
    if (s == 0) return true; // is prime // cout<<"prime";
    return false; //is complex // cout<<"";
}


bool miller_rabin(vector<int> n)
{
    if (n.size() == 0) throw("\n Empty vector!\n");
    if (n[0] % 2 == 0) throw("\n Even number passed as an argument!\n");
    vector<int> t = n, n_min_one = subtract_vectors(n, one);
    t = subtract_vectors(t, one);
    int s=0; // vector<int> s{0};
    while(get_mod_two(t) == 0) {
        divide_vectors(t, two);
        s++; // increase_by_one(s);
    }

    while (true) {  // <- cycle A
        int a;
        //a = rand(2, n-2);
        vector<int> x;
        make_vector(x, a);// for a - vector x = a;

        vector<int> k{0};
        while (compare_vectors(k, t)) != 0) // x = a^t
        {
            x = karatsuba_algo(x, a);
            increase_by_one(k);
        }
        x = get_modulo(x, n);  // this cycle - x = a^t mod n

        if (compare_vectors(x, one) == 0 || compare_vectors(x, n_min_one) == 0) break;
        for (int i = 0; i <= s; ++i) // k = one; while (compare_vectors(k, s) <- cycle B
        {
            x = get_modulo(get_squared(x), n);
            if (compare_vectors(x, one) == 0) return true; // is complex
            if (compare_vectors(x, n_min_one) == 0) break; // go to next iteration of cycle B
        }
        return true; // complex

    }
    return false; // possibly prime
}


bool solov_shtrassen(vector<int> a)
{
    return true;//is prime
}






#endif // ALGOS_H_INCLUDED
