#include<vector>
#include<iostream>
using namespace std;


vector<int> insert_sort(vector<int> &nums){
    int n = nums.size();
    for(int i=1; i<n; i++){
        // use nums[i]  insert in  nums[0.....i-1]
        int j=i-1,  nums_i = nums[i];
        for( ; j>=0; j--){
            if(nums[j] <= nums_i){
                nums[j+1] = nums_i;    break;
            }
            else{
                nums[j+1] = nums[j];
            }
        }
        if(j==-1) nums[j+1] = nums_i; 
    } 
    return nums;
}
