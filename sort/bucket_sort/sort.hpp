#include<vector>
#include<iostream>
#include<climits>
#include"../../utils/utils.hpp"
using namespace std;

void bucket_sort_sort_each_bucket_i(vector<int>& nums){
    int min_num = INT_MAX, max_num = INT_MIN, n = nums.size();
    for(auto nu:nums){
        min_num = nu < min_num ? nu : min_num;
        max_num = nu > max_num ? nu : max_num;
    }
    int size = max_num - min_num + 1;
    vector<int> C(size, 0);
    for(auto nu: nums){
        C[nu-min_num] ++;
    }

    //// Method 1:  travel the C, fill the (val + min_num) when C[val]!=0;  
    // O(max_num - min_num + 1); 
    for(int nu=0, i=0; nu<size; nu++){
        while(C[nu]-- >0){
            nums[i++] = nu + min_num;
        }
    }
    C.clear();  C.shrink_to_fit();
}




vector<int> bucket_sort(vector<int> &nums){
    clock_t t1, t2;
    int n = nums.size();    if(n<=1) return nums;
    int max_num = INT_MIN, min_num = INT_MAX;
    for(auto nu: nums){
        max_num = nu > max_num ? nu : max_num;
        min_num = nu < min_num ? nu : min_num;
    }

    /// ====================== define the BUCKET_NUM and BUCKET_STEP ====================

    int BUCKET_NUM = n ;
    int BUCKET_STEP = ceil((max_num - min_num + 1) / BUCKET_NUM);
    cout<<"BUCKET_NUM, BUCKET_STEP = "<<BUCKET_NUM<<","<<BUCKET_STEP<<endl;

    vector<vector<int>> bucket(BUCKET_NUM);

    /// ====================== insert nums[i] ====================
    // t1 = clock();
    for(auto nu: nums){
        int index = (nu - min_num) / BUCKET_STEP;
        bucket[index].push_back(nu);
    }
    //print_time_using(t1, "insert run_time = ");




    // sort every bucket[i]
    //t1 = clock();
    for(int i=0; i<BUCKET_NUM; i++){
        if(bucket.size()>1){
            bucket_sort_sort_each_bucket_i(bucket[i]);
        }
    }
    //print_time_using(t1,    "sort each bucket_i run_time = ");


    /// ====================== merge every bucket to fill the nums   ====================
    //t1 = clock();
    int index =0;
    for(int i=0; i<BUCKET_NUM; i++){
        if(bucket[i].empty()) continue;
        for(int j=0; j<bucket[i].size(); j++){
            nums[index ++] = bucket[i][j];
        }
    }
    //print_time_using(t1,    "sort each bucket_i run_time = ");



    //t1 = clock();
	release_vector(bucket);
    //print_time_using(t1,    "release_vector run_time = ");

    return nums;
}


