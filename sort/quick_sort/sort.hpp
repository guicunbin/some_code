#include"../../utils/utils.hpp"
#include<iostream>
#include<vector>
#include<stdlib.h>
//#include<stack>
#include<utility>
using namespace std;


vector<int> quick_sort_concat(vector<int> left, int pivot, vector<int> right){
    vector<int> res = left;
    res.push_back(pivot);
    if(right.empty()) return res;
    res.insert(res.end(), right.begin(), right.end());
    return res;
}






vector<int> quick_sort_use_extra_space(vector<int> &nums){
    if(nums.empty()) return {};
    vector<int> left, right;
    int pivot_index = rand() % nums.size();
    int pivot = nums[pivot_index];
    for(int i=0; i<nums.size(); i++){
        if(i==pivot_index) continue;
        if(nums[i] <= pivot) left.push_back(nums[i]);
        else right.push_back(nums[i]);
    }
    //cout<<"-------\n left, pivot, right = "<<endl; print_vec(left);    cout<<pivot<<endl;   print_vec(right); cout<<"-----\n";
    vector<int> res = quick_sort_concat(quick_sort_use_extra_space(left), pivot, quick_sort_use_extra_space(right));
    return res;
}



void quick_sort_in_place_split(vector<int>&nums, int left_index, int right_index){
    // random a val of the nums to put this val to correct index and make :  the max(left) <= this_val <= min(right)
    if(left_index >= right_index) return;
    //  // move the pivot_value to the end of this sequence
    //  int pivot_index = rand() % (right_index - left_index + 1) + left_index;
    //  swap(nums[pivot_index], nums[right_index]);
    int pivot_index = right_index;
    int store_idx = left_index;
    for(int i=left_index; i<right_index; i++){
        if(nums[i]<nums[right_index]){
            swap(nums[store_idx ++ ], nums[i]); 
        }
    }
    // move the pivot_index to the split_point
    //cout<<"store_idx = "<<store_idx<<endl;
    swap(nums[store_idx], nums[right_index]);
    
    quick_sort_in_place_split(nums, left_index, store_idx-1);
    quick_sort_in_place_split(nums, store_idx+1,right_index);
}




vector<int> quick_sort_in_place_use_stack(vector<int>&nums){
    // random a val of the nums to put this val to correct index and make :  the max(left) <= this_val <= min(right)
    int n = nums.size();    if(n<=1) return nums;
    int left_index = 0, right_index = n-1;
    //stack<pair<int,int>> vec_sta;
    vector<pair<int,int>> vec_sta;
    vec_sta.push_back(make_pair(left_index, right_index));
    while(!vec_sta.empty()){
        pair<int,int> back = vec_sta.back();  vec_sta.pop_back();
        left_index = back.first, right_index = back.second;
        int pivot_index = rand() % (right_index - left_index + 1) + left_index;
        // after this swap;  the pivot_value = nums[right_index];
        swap(nums[pivot_index], nums[right_index]);
        int store_idx = left_index;
        for(int i= left_index;  i<right_index;  i++){
            if(nums[i] < nums[right_index]){
                swap(nums[store_idx ++], nums[i]);
            }
        }
        // move the pivot_index to the split_point
        swap(nums[store_idx], nums[right_index]);
        if(left_index < store_idx - 1)
            vec_sta.push_back(pair<int,int>{left_index, store_idx - 1});
        if(store_idx + 1 < right_index)
            vec_sta.push_back(pair<int,int>{store_idx + 1, right_index});
    }
    return nums;
}






vector<int> quick_sort_in_place(vector<int> &nums){
    quick_sort_in_place_split(nums, 0, int(nums.size()) - 1);
    return nums;
}

