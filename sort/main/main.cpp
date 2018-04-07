#include<iostream>
#include<vector>
#include"../../utils/utils.hpp"
#include"../quick_sort/sort.hpp"
#include"../bubble_sort/sort.hpp"
#include"../select_sort/sort.hpp"
#include"../insert_sort/sort.hpp"
#include"../heap_sort/sort.hpp"
#include<time.h>
using namespace std;

int main(int argc, char *argv[]){
    //int test_size = 10;                 
    //cin>>test_size;
    //cout<<"argc = "<<argc<<endl;
    if(argc != 2){
        cout<<"usage:  ./a.out test_size"<<endl;
        return -1;
    }
    int test_size = atoi(argv[1]);
    cout<<"test_size  ="<<test_size<<endl;
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

    cout<<"---------------------------------------------------         insert_sort"<<endl;
    test_vec = TEST_VEC;        print_sort_time(insert_sort, test_vec, is_print_vec);


    cout<<"---------------------------------------------------         heap_sort"<<endl;
    test_vec = TEST_VEC;        print_sort_time(heap_sort, test_vec, is_print_vec);
}


