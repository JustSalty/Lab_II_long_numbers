#include <stdio.h>
#include <windows.h>
//#include "longs_fin.h"
#include "float_long.h"
#include "binary_algos.h"

//#include <iostream>
//#include <vector>

//26.09 changed 10 to sys in subtract_vectors, get_int and some others

using namespace std;


int main00()
{

    //**
    FloatLong a(2.1, 2), b(1.5, 1), c(1.0, 0);
    a.print();
    b.print();
    FloatLong d0({2,1,0},1);
    c.print();
    d0.print();

    FloatLong d = a + b; ///e = b + c, f = b - c, g = a - c, a0(2), h = b * a0;
    ///printf("\n %s + %s = %s ", std::string(a).c_str(), std::string(b).c_str(), std::string(d).c_str());
    ///cout<<"\n "<<string(a)<<" + "<<string(b)<<" = "<<string(d);

    //**/

    /** FloatLong tests for constructors
    vector<int> a{2,1,0}, b{0,1}, c{1,0};
    FloatLong a1(a,b), b1(a,c);
    a1.print();
    b1.print();
    **/


    /* //multiply vector by digit function test
    int a = 2;
    vector<int> b{9,5}, c = multiply_by_digit(b, a);
    cout<<"\n";
    print_vector(b);
    cout<<"\n";
    print_vector(c);
    cout<<"\n\n";
    */


    /* // luke-lemers test
    vector<int> a{7};
    bool b = lemers_luke(a);
    if (b) cout<<"\n Prime!\n"; else cout<<"\n Complex!\n";
    */

    /* // division and modulo test
    vector<int> ar1{0,0,0,1}; print_vector(ar1); cout<<endl;
    vector<int> ar2{9,9}; print_vector(ar2); cout<<endl;
    vector<int> ar3{0}; ar3 = divide_vectors(ar1, ar2); print_vector(ar3); cout<<endl;
    ar3 = get_modulo(ar1, ar2); print_vector(ar3); cout<<endl;
    */

    /** /// shtrassen test
    vector<int> n1{1,1}, n2{1,2};
    vector<int> n = shtrassen(n1, n2); cout<<endl;
    //cut_zeroes(n);
    print_vector(n); cout<<endl;
    **/

    /* // split function test
    int n = 2;
    vector<int> a{0,2,1};
    vector<int>* a_n = split_in_n(a,n);
    cout<<endl;
    for (int i = 0; i < n; ++i) {print_vector(a_n[i]);} cout<<endl;
    */

    /* // subtraction test
    vector<int> ar1{0,0,0,1,0}; print_vector(ar1); cout<<endl;
    vector<int> ar2{9,9,0}; print_vector(ar2); cout<<endl;
    vector<int> ar3{0}; ar3 = subtract_vectors(ar1, ar2); print_vector(ar3); cout<<endl;
    */

    /*
    vector<int> n1{0,1,1}, n2{2,1,0};
    vector<int> n = bad_toom_cook(n1, n2, 4); cout<<endl;
    cut_zeroes(n);
    print_vector(n); cout<<endl;
    */

    /* // toom-cook test
    vector<int> n1{1,1}, n2{9,1,0};
    vector<int> n = toom_cook(n1, n2, 2); cout<<endl;
    cut_zeroes(n);
    print_vector(n); cout<<endl;
    */


    /* // karatsuba test
    vector<int> n1{1,0,0,0}, n2{0,1,1};
    vector<int> n = karatsuba_algo(n1, n2); cout<<endl;
    cut_zeroes(n);
    print_vector(n); cout<<"\n\n";
    */

    /* function that makes a vector by a number test
    vector<int> a;
    make_vector(a, 0);
    cout<<"\n";
    print_vector(a);
    cout<<"\n\n";
    */
    /* // same here
    int a = 12;
    vector<int> a1{0};  make_verctor(a1,a);
    print_vector(a1);
    int a2 = get_int(a1);
    printf("\n %d \n", a2);
    //cout<<endl<<a2<<endl;
    */


    /* // dynamic vector test
    vector<int>* arr = new vector<int>[2];
    vector<int> ar0{2,1}, ar1{1,1};
    arr[0] = ar0; arr[1] = ar1;
    print_vector(arr[2]);
    */

    /* // half-split, addition and subtraction test
    vector<int> arr{0,2,1,0,0}; print_vector(arr);
    vector<int> ar1{0}, ar2{0}; split_in_two(arr, ar1, ar2); print_vector(ar1); print_vector(ar2);
    //vector<int> ar3{0}; ar3 = add_vectors(ar1, ar2); print_vector(ar3);
    //vector<int> ar5{1,1,1};
    //vector<int> ar4{0}; ar4 = subtract_vectors(ar5, ar2); print_vector(ar4);
    //vector<int> b1{1,1}, b2{1,9}, b0{0}; b0 = add_vectors(b1, b2); print_vector(b0);
    */

    /*
    vector<int> arr{0,2,1,0,0};
    LongNums_0 a(arr);
    cout<<"\n\n"<<string(a)<<endl;
    */

    /*
    LongNums_0 a(9), b(11), c = b-a;
    cout<<"\n\n"<<string(c)<<"\n";
    */

    /*
    vector<int> a = {0, 1, 2};
    a.emplace_back(3);
    a.insert(a.end(), 3);
    cout<<"\n\n"<<a[3]<<a.size()<<"\n";
    */

    return 0;
}

int main()
{

    try{
    main00();
    }

    catch(const char* msg){cout<<"\n Sorry, an error occured:"<<msg<<endl;}
    catch(...){cout<<"\n Unidentified exception caught!\n";}

    system("pause");
    return 0;
}

int main0(){

    /*
    int a = 0; char c = a;
    while(c != '0') {++a; c = a;}; cout<<"\n "<<a<<"\n "<<c<<"\n";


    int *p;
    int a = 5;
    p = &a;
    int* q;
    q = p;
    ++(*p);
    cout<<endl<<*p<<endl;
    */

    //LongNums_0 a0(12), b0(7);
    //char* f = "03"; LongNums_0 a(2, f);
    //f = "07"; LongNums_0 b(2, f);
    //cout<<"\n\n "<<string(a0)<<string(b0)<<endl;
    //LongNums_0 c = a + b;
    //LongNums_0 c = a0 + b0;
    //cout<<"\n "<<string(c)<<"\n";


    //char* f = "12"; char* g = "10";
    //char* f = new char[3]; f = "011";
    //char* g = new char[3]; g = "011";
    //multiply_small(f, 2, g, 2);
    //cout<<endl<<string(multiply_small(f,2,g,2))<<endl;


    /*
    int a = 199;
    cout<<"\n "<<get_len(a)<<"\n\n"; */

    return 0;
}
