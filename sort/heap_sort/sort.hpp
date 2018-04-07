#include<vector>
#include<climits>
#include<iostream>
#include"../../utils/utils.hpp"
using namespace std;
typedef void (*pointer_func)(int,vector<int>&, int);

void Max_heapify(int pi, vector<int> &nums, int end_i){
    // pi is the parent i node
    int max_child = max((2*pi+1 <= end_i)? nums[2*pi +1] : INT_MIN,   (2*pi+2 <= end_i) ? nums[2*pi +2] : INT_MIN);
    if(max_child > nums[pi]){
        if(2*pi + 2 <=  end_i){
            if(nums[2*pi+1] > nums[2*pi +2]){
                swap(nums[pi], nums[2*pi+1]);
                Max_heapify(2*pi+1, nums, end_i);
            }
            else{
                swap(nums[pi], nums[2*pi+2]);
                Max_heapify(2*pi+2, nums, end_i);
            }
        }
        else if(2*pi + 1 <= end_i){
            swap(nums[pi], nums[2*pi+1]);
            Max_heapify(2*pi+1, nums, end_i);
        }
    }
}


void Max_heapify_elegant(int start, vector<int> &nums, int end){
    int dad = start;
    int son = 2 * dad + 1;
    while(son <= end){
        //cout<<"dad = "<<dad<<endl;
        son += (son + 1 <= end && nums[son + 1] > nums[son])?1:0;
        if(nums[dad] >= nums[son]) return;
        else{
            swap(nums[dad], nums[son]);
            dad = son;
            son = 2 * dad + 1;
        }
    }
}




vector<int> heap_sort(vector<int> &nums){
    int n = nums.size();
    if(n<=1) return nums;

    // use Function pointer
    pointer_func Max_heap = Max_heapify_elegant;

    // build the max_heap
    for(int pi = floor((n-1)/2); pi >=0; pi --){
        Max_heap(pi, nums, n-1);
    }
    //cout<<"after build max_heap = "<<endl; print_vec(nums);
    // heap sort
    for(int i= n-1; i > 0; i--){
        swap(nums[0], nums[i]);
        Max_heap(0, nums, i-1);
    }
    return nums;
}
