#include<vector>
#include<iostream>
using namespace std;

vector<int> select_sort(vector<int> &nums){
    int n = nums.size();
    for(int i=0; i<n; i++){
        // select sort same as bubble sort;    are both  O(n**2)
        //but select sort swap only one time in one loop;
        int min_val_idx = i; 
        for(int j=n-1; j>i; j--){
            if(nums[j] < nums[min_val_idx]){
                min_val_idx = j;
            }
        }
        //cout<<"min_val_idx = "<<min_val_idx<<endl;
        swap(nums[i], nums[min_val_idx]);
    }
    return nums;
}


