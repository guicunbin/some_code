#include<vector>
#include<iostream>
#include"../../utils/utils.hpp"
using namespace std;


vector<int> insert_sort(vector<int> &nums){
    int n = nums.size();
    for(int i=1; i<n; i++){
        //from nums[0,.....i] to find the point to insert nums[i];
        // nums[i] maybe just stay on original index; so from j--->0
        int insert_idx = i,  insert_num = nums[i];
        while(insert_idx >= 1 && nums[insert_idx - 1] > insert_num){
           nums[insert_idx] = nums[insert_idx - 1];     
           insert_idx -= 1;
        }
        // 为了保证插入排序算法的稳定性，遇到元素相等的时候，一律放在后面
        nums[insert_idx] = insert_num;
        //print_vec(nums);
    }
    return nums;
}
