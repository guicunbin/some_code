#include<cmath>
#include<iostream>
#include<vector>
#include"../../utils/utils.hpp"
#include"../quick_sort/sort.hpp"
#include"../bubble_sort/sort.hpp"
#include"../select_sort/sort.hpp"
#include"../insert_sort/sort.hpp"
#include"../heap_sort/sort.hpp"
#include"../merge_sort/sort.hpp"
#include"../count_sort/sort.hpp"
#include"../bucket_sort/sort.hpp"
#include"../radix_sort/sort.hpp"
#include"../shell_sort/sort.hpp"
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
    cout<<"TEST_VEC use memory == "<<(sizeof(int) * TEST_VEC.capacity()) * 1.0 / pow(10, 6) << " MB "<<endl;

    cout<<"===================================================         stl_sort"<<endl;
    test_vec = TEST_VEC;        print_sort_time(stl_sort, test_vec, is_print_vec);




    cout<<endl<<endl<<"============ O(n**2) ============= "<<endl;

    cout<<"===================================================         bubble_sort"<<endl;
    test_vec = TEST_VEC;        print_sort_time(bubble_sort, test_vec, is_print_vec);

    cout<<"===================================================         select_sort"<<endl;
    test_vec = TEST_VEC;        print_sort_time(select_sort, test_vec, is_print_vec);

    cout<<"===================================================         insert_sort"<<endl;
    test_vec = TEST_VEC;        print_sort_time(insert_sort, test_vec, is_print_vec);


    cout<<"===================================================         shell_sort"<<endl;
    test_vec = TEST_VEC;        print_sort_time(shell_sort, test_vec, is_print_vec);






    cout<<endl<<endl<<"============ O(n*log(n)) ============= "<<endl;

    cout<<"===================================================         heap_sort"<<endl;
    test_vec = TEST_VEC;        print_sort_time(heap_sort, test_vec, is_print_vec);

    //  cout<<"===================================================         quick_sort_use_extra_space"<<endl;
    //  test_vec = TEST_VEC;        print_sort_time(quick_sort_use_extra_space, test_vec, is_print_vec);

    //  cout<<"===================================================         quick_sort_in_place_use_stack"<<endl;
    //  test_vec = TEST_VEC;        print_sort_time(quick_sort_in_place_use_stack, test_vec, is_print_vec);

    cout<<"===================================================         quick_sort_in_place"<<endl;
    test_vec = TEST_VEC;        print_sort_time(quick_sort_in_place, test_vec, is_print_vec);

    cout<<"===================================================         merge_sort"<<endl;
    test_vec = TEST_VEC;        print_sort_time(merge_sort, test_vec, is_print_vec);






    cout<<endl<<endl<<"============ O(n) ============= "<<endl;

    cout<<"===================================================         bucket_sort"<<endl;
    test_vec = TEST_VEC;        print_sort_time(bucket_sort, test_vec, is_print_vec);

    cout<<"===================================================         radix_sort"<<endl;
    test_vec = TEST_VEC;        print_sort_time(radix_sort, test_vec, is_print_vec);

    cout<<"===================================================         count_sort"<<endl;
    test_vec = TEST_VEC;        print_sort_time(count_sort, test_vec, is_print_vec);

}

