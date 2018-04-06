#include<iostream>
#include<vector>
#include"../../utils/utils.hpp"
#include"../quick_sort/sort.hpp"
#include"../bubble_sort/sort.hpp"
#include"../select_sort/sort.hpp"
#include<algorithm>
#include<time.h>
using namespace std;

int main(){
    int test_size = 1000000;                 cout<<"test_size  ="<<test_size<<endl;
    bool is_print_vec = (test_size < 50);


    vector<int> TEST_VEC = get_rand_vec(test_size);
    vector<int> test_vec;



    cout<<"---------------------------------------------------         quick_sort_use_extra_space"<<endl;
    test_vec = TEST_VEC;        print_sort_time(quick_sort_use_extra_space, test_vec, is_print_vec);

    cout<<"---------------------------------------------------         quick_sort_in_place"<<endl;
    test_vec = TEST_VEC;        print_sort_time(quick_sort_in_place, test_vec, is_print_vec);

    cout<<"---------------------------------------------------         bubble_sort"<<endl;
    test_vec = TEST_VEC;        print_sort_time(bubble_sort, test_vec, is_print_vec);

    cout<<"---------------------------------------------------         select_sort"<<endl;
    test_vec = TEST_VEC;        print_sort_time(select_sort, test_vec, is_print_vec);
}


