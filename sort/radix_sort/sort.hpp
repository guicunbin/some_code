#include<vector>
#include<iostream>
#include<climits>
#include"../../utils/utils.hpp"
using namespace std;

// just sort the positive number;
// if nums has negative number split it to another vector to sorted them
vector<int> radix_sort(vector<int>& nums){
    //================ first  get the max_num to define the k ===================== 
    int max_num = INT_MIN, n = nums.size();
    if(n<=1) return nums;
    for(auto nu: nums){
        max_num = nu > max_num ? nu : max_num;
    }
    int k = 0;
    while(max_num){
        k += 1;
        max_num /= 10;
    }

    // count_sort k times
    vector<int> tmp_vec = nums;
    int radix = 1;
    int C[10];
    for(int i=0; i<k; i++){
        // init the Count array
        fill_n(C, 10, 0);
        for(auto nu: nums){
            C[nu / radix % 10] ++;
        }
        //print_c_array(C, 10);
        for(int i=1; i<10; i++){
            C[i] += C[i-1];
        }
        //print_c_array(C, 10);   cout<<"start filling the tmp_vec "<<endl;
        for(int i=n-1; i>=0; i--){
            //cout<<"-----------------------------------"<<endl;print_c_array(C, 10);
            tmp_vec[--C[nums[i] / radix % 10]] = nums[i];
            //print_vec(tmp_vec);   cout<<"-----------------------------------<<endl;
        }


        // tmp_vec to nums and radix *= 10;
        nums = tmp_vec;
        radix *= 10;
    }
    release_vector(tmp_vec);
    return nums;
}

