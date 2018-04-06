#include<iostream>
#include<vector>


vector<int> bubble_sort(vector<int> &nums){
    int n = nums.size();
    for(int i=0; i<n; i++){
        for(int j=n-1; j>i; j--){
            if(nums[j-1]>nums[j]){
                swap(nums[j-1], nums[j]);
            }
        }
    }
    return nums;
}
