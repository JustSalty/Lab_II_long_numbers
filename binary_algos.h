#ifndef BINARY_ALGOS_H_INCLUDED
#define BINARY_ALGOS_H_INCLUDED

#include "float_long.h"

using namespace std;

static const vector<int> zero = {0};

//static const int sys = 2;

int binary_pow_int (int a, int n) {
	int res = 1;
	while (n) {
		if (n & 1)
			res *= a;
		a *= a;
		n >>= 1;
	}
	return res;
}

vector<int> binary_pow_vect (vector<int> num, vector<int> power) {
	vector<int> res = one;
	while (power.size() > 0) {
		if (get_mod_two(power))//if (n & 1)
			res = karatsuba_algo(res, num);
		num = karatsuba_algo(num,num);
		cut_last(power, 1);//n >>= 1;
	}
	return res;
}

vector<int> binary_pow_vect_by_mod (vector<int> num, vector<int> power, const vector<int>& mod) {
	vector<int> res = one;
	while (power.size() > 0) {
		if (get_mod_two(power))//if (n & 1)
			res = get_modulo(karatsuba_algo(res, num), mod);
		num = get_modulo(karatsuba_algo(num,num), mod);
		cut_last(power, 1);//n >>= 1;
	}
	return res;
}

bool lemers_luke_bin(vector<int> p)
{
    if (p.size() == 0) throw("\n Empty vector!\n");
    if (p[0] % 2 == 0) throw("\n Even number passed as an argument!\n");
    vector<int> k{1}, s{4}, m{2};
    m = binary_pow_vect(m, p);//while (compare_vectors(k, p) != 0) {m = multiply_by_digit(m, 2); increase_by_one(k);}
    k = one; // k = 1;
    m = subtract_vectors(m, one);
    while (compare_vectors(k, subtract_vectors(p, one)) != 0)
    {
        s = subtract_vectors( get_modulo(get_squared(s), m), two);
        //or s = get_modulo(subtract_vectors(get_squared(s), two), m);
        increase_by_one(k);
    }
    cut_zeroes(s);
    if (s.size() == 0) return true; // is prime
    return false; //is complex
}

bool miller_rabin_bin(vector<int> n, const int& rounds)
{
    if (n.size() == 0) throw("\n Empty vector!\n");
    if (n[0] == 0) throw("\n Even number passed as an argument!\n");
    //if (get_mod_two(n) == 0) throw("\n Even number passed as an argument!\n");

    vector<int> n_min_one = subtract_vectors(n, one), t = n_min_one;
    int s=0; // vector<int> s{0}; s is the power of two in n-1
    while (t[0] == 0) {
    //while(get_mod_two(t) == 0) {
        cut_last(t,1);//divide_vectors(t, two);
        s++; // increase_by_one(s);
    }

    ///cycleA:
    for (int i = 0; i < rounds; ++i) {  // <- cycle A - repeat k times
        int a0 = i + 1; //a0 = rand(2, n-2);
        vector<int> a;
        make_vector(a, a0);
        vector<int> x = a;

        x = binary_pow_vect_by_mod(x, t, n);
        //x = get_modulo(x, n);  // this cycle - x = a^t mod n

        //if (compare_vectors(x, one) == 0 || compare_vectors(x, n_min_one) == 0) break;/// go to next A iteration
        if ( !(compare_vectors(x, one) == 0 || compare_vectors(x, n_min_one) == 0) ) {//
        bool flag = true;
        for (int l = 0; l < s-1 && flag; ++l) // k = one; while (compare_vectors(k, s) <- cycle B
        {
            x = get_modulo(get_squared(x), n);
            if (compare_vectors(x, one) == 0) return true; // is complex
            if (compare_vectors(x, n_min_one) == 0) flag = false; /// go to next iteration of cycle A
        }
        if (flag) return true; /// complex
        }//

    }
    return false; /// possibly prime
}

int Jacobi_bin(vector<int> q, vector<int> p)
{
    if (p[0] == 0) throw("\n Even number passed as denominator to Jacobi!\n");
    if (compare_vectors(q, one) == 0 || compare_vectors(p, one)) return 1;
    if (compare_vectors(GCD(q, p), one) != 0) return 0;
    ///vector<int> s{0}, u = q, v = p;
    vector<int> r, t{0};
    int k;///is power of 2 in q
    r = get_modulo(q, p);//r = u % v;
    t = r;
    cut_zeroes_back(t);
    k = r.size() - t.size();
    int p_mod_eight;
    if (p.size() > 3) p_mod_eight = get_int_base(take_last(p ,3), 2);
    else p_mod_eight = get_int_base(p, 2);
    k %= 2;
    int step;
    if (p_mod_eight == 1 || p_mod_eight == 7) step = pow(1, k);
    else step = pow(-1, k);
    if (compare_vectors(t, one) == 0) return step;
    vector<int> p1 = p, t1 = t;
    int t0;
    ///p0 = get_mod_two(cut_last(p1));
    t0 = get_mod_two(cut_last(t1,1));
    step *= pow(-1, p[1]*t0);///p0*t0
    return step*Jacobi_bin(p, t);


    /**
    do{
        /// ¬ычисл€ем r - наименьший положительный остаток при делении u на v
        r = get_modulo(u, v);//r = u % v;

        t = cut_zeroes_back(r);
        k = r.size() - t.size();
            /// ¬ычисл€ем целое k >= 0 и нечетное t: r = t * 2^k
            ///k = t = 0;
            ///while(r % 2 == 0)
            ///{
                ///k++;        // ѕоказатель степени двойки в числе r
                ///r >>= 1;    // ƒелим r на 2
            ///}
            ///t = r;          // ¬ t находитс€ результат делени€ r на 2^k


        s = (s + k * (v*v - 1)/8 + (t - 1)*(v - 1)/4) % 2;
        if(t == 1)
            return (s) ? 1 : -1;
        /// Ќова€ итераци€
        u = v;
        v = t;
    }while(t >= 3);
    **/
}


bool solovey_shtrassen_bin (vector<int> p, const int& rounds)
{
    if (p.size() == 0) throw("\n Empty vector!\n");
    if (p[0] == 0) throw("\n Even number passed as an argument!\n");
    //if (get_mod_two(n) == 0) throw("\n Even number passed as an argument!\n");
    vector<int> j_pow = cut_last(p, 1);
    for (int i = 0; i < rounds; ++i) {
        int a0 = i + 1; //a0 = rand(2, n-2);
        vector<int> a;
        make_vector(a, a0);
        vector<int> nod = GCD(a, p);
        cut_zeroes(nod);
        if (nod.size() == 0) return true;/// is complex
        vector<int> j = binary_pow_vect_by_mod(a, j_pow, p);
        vector<int> jac;
        int jaci = Jacobi_bin(a, p);///jac is Yacobi symbol for a and p
        if (jaci == -1) jac = subtract_vectors(p, one);
        if (jaci == 1) jac = one;
        if (jaci == 0) jac = {0};
        int mark = compare_vectors(j, jac);
        if (mark == 0) return true;/// is complex
        if ( !(mark == 1) ) ;///? is prime with possibility no more than 1/2
    }
    return false;/// is prime with probability 1 - 2^(-rounds)
}



FloatLong inverse_int(const LongNums& num, const int& precision)/// тут дл€ корректной работы надо мен€ть переменную sys в классе Longnums и файле help_hand на 2
{
    //check if num is 0
    if (num.i_num == zero) throw("\n Zero has no inverse! (function inverse(LongNums&) )\n");
    vector<int> n1 = num.i_num, i = {0};
    int n_size = n1.size(), n = precision, t = 1;
    while (t < n_size) t *= 2;
    int T = t + 3;
    add_zeroes(n1, T-n_size);/// n1 - вз€ли число n и приписали справа к 0. - оно стало дробной частью - или поделили на соотв степень 2
    n_size = n1.size();
    int l = n_size;
    double z0 = (33 / (4 * n1[l] + 2 * n1[l-1] + n1[l-3] + 1)) / 4;/// начальна€ инициализаци€
    FloatLong z(z0, 2); /// в начале у z есть 2 знака после зап€той
    vector<int> V_k = take_first(n1, 4); /// 4 = (2^(0)+3)
    int j = 1, digs = 2, k = 0, last_index_in_num_for_V_k = 4;
    while (j < n){
        for (int l = 0; l < j; ++l){V_k.emplace_back(n1[n_size - ( last_index_in_num_for_V_k + l + 1) ]);}/// дописываем к V_k несколько знаков из n1
        /// каждий раз мы дописываем знаки в V_k с (2^k+3) не включ по (2^(k+1)+3) включ - они берутьс€ из n1
        FloatLong v(i, V_k);
        z = (z << 1) - v*z*z;
        vector<int> z0 = z.f_part;
        k++;/// - номер итерации
        j *=2 ;/// - кол-во цифр в z -1
        digs = j + 1;/// - кол-во цифр в z
        last_index_in_num_for_V_k = j + 3;
        z0 = make_length(z0, digs);///обрезка дробной части до (2^(к+1)) знака
        z.update_f(z0);
    }
    FloatLong res = z << n_size;
    return res;
}

FloatLong inverse_float_0(const FloatLong& num, const int& precision)/// тут дл€ корректной работы надо мен€ть переменную sys в классе Longnums и файле help_hand на 2
{
    //check if num is 0
    if (!num.is_int) throw("\n Not an integer passed as an argument to 'inverse' function!\n");

    vector<int> n1 = num.i_part, i = {0};
    if (n1.size() == 0) throw("\n Zero has no inverse! (function inverse(FloatLong&) )\n");
    //if (n1 == zero) throw("\n Zero has no inverse! (function inverse(FloatLong&) )\n");
    int n_size = n1.size(), n = precision, t = 1;
    while (t < n_size) t *= 2;
    int T = t + 3;
    add_zeroes(n1, T-n_size);/// n1 - вз€ли число n и приписали справа к 0. - оно стало дробной частью - или поделили на соотв степень 2
    n_size = n1.size();
    int l = n_size;
    double z0 = (33 / (4 * n1[l] + 2 * n1[l-1] + n1[l-3] + 1)) / 4;/// начальна€ инициализаци€
    FloatLong z(z0, 2); /// в начале у z есть 2 знака после зап€той
    vector<int> V_k = take_first(n1, 4); /// 4 = (2^(0)+3)
    int j = 1, digs = 2, k = 0, last_index_in_num_for_V_k = 4;
    while (j < n){
        for (int l = 0; l < j; ++l){V_k.emplace_back(n1[n_size - ( last_index_in_num_for_V_k + l + 1) ]);}/// дописываем к V_k несколько знаков из n1
        /// каждий раз мы дописываем знаки в V_k с (2^k+3) не включ по (2^(k+1)+3) включ - они берутьс€ из n1
        FloatLong v(i, V_k);
        z = (z << 1) - ((v*z)*z);
        vector<int> z0 = z.f_part;
        k++;/// - номер итерации
        j *=2 ;/// - кол-во цифр в z -1
        digs = j + 1;/// - кол-во цифр в z
        last_index_in_num_for_V_k = j + 3;
        z0 = make_length(z0, digs);///обрезка дробной части до (2^(к+1)) знака   /// <<--- BUG!!!
        z.update_f(z0);
    }
    FloatLong res = z << n_size;
    return res;
}

FloatLong division_Cook_bin(const vector<int>& num1, const vector<int>& num2)/// n1 - divisible, n2 - divisor
{
    FloatLong n1(num1, {0});
    int precision = num1.size()+1;
    LongNums n2_0(num2);
    FloatLong n2 = inverse_int(n2_0, precision);
    FloatLong res = n1 * n2;
    return res;
}


#endif // BINARY_ALGOS_H_INCLUDED
