#ifndef _TEST_H_
#define _TEST_H_

#include<iostream>
#include<vector>
#include<time.h>
#include<algorithm>
using namespace std;

void print_vec(vector<int> nums){
    cout<<endl<<" { ";
    for(auto nu: nums){
        cout<<nu<<",";
    }
    cout<<" } "<<endl;
}


vector<int> get_rand_vec(int test_size){
    vector<int> test_vec(test_size, 0);
    for(int i=0; i<test_size; test_vec[i]=i,i++);
    random_shuffle(test_vec.begin(), test_vec.end());
    return test_vec;
}



void print_sort_time(vector<int> sort_func(vector<int>& ), vector<int> test_vec, bool is_print_vec){
    if (is_print_vec){
        cout<<"original = "<<endl; 
        print_vec(test_vec);
    }

    clock_t start = clock();
    test_vec = sort_func(test_vec);
    clock_t end   = clock();
    cout<<"----------------------------------------------------------------- run_time = "<<double(end - start) / CLOCKS_PER_SEC<<endl;

    if (is_print_vec){
        cout<<"finally = "<<endl; 
        print_vec(test_vec);
    }
}


#endif

