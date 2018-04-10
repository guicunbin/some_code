#include<iostream>
#include<vector>
#include"../../utils/utils.hpp"
using namespace std;

vector<int> merge_sort_merge_two_list(vector<int>& nums1, vector<int> & nums2){
    int n1= nums1.size(), n2 = nums2.size();
    int i=0, j=0, k=0;
    vector<int> res(n1+n2, 0);
    while(i<n1 && j<n2){
        if(nums1[i] < nums2[j]){
            res[k++] = nums1[i++]; 
        }
        else{
            res[k++] = nums2[j++]; 
        }
    }
    return res;
}



void merge_sort_merge_two_part(vector<int> &nums, vector<int> &nums_copy, int left, int step, int n){
    // merge nums[l1 ....l1_max] and  nums[r1 .... r1_max];
    int     l1 = left,   l1_max = left + step -1,    r1 = left + step,      r1_max = left + 2*step - 1;
    r1_max = r1_max >=n ? n-1 : r1_max;
    //cout<<"l1, l1_max, r1, r1_max, n = "<<l1<<","<<l1_max<<","<<r1<<","<<r1_max<<","<<n<<endl;
    int i = left;
    while(l1 <= l1_max && r1 <= r1_max){
        if(nums[l1] < nums[r1]){
            nums_copy[i++] = nums[l1++];
        }
        else{
            nums_copy[i++] = nums[r1++];
        }
    }
    //cout<<"l1, r1 = "<<l1<<","<<r1<<endl;
    //cout<<"after first while ==> nums_copy = ";   print_vec(nums_copy);
    while(l1 <= l1_max){    nums_copy[i++]=nums[l1++];   }
    while(r1 <= r1_max){    nums_copy[i++]=nums[r1++];   }
    //cout<<"after third while ==> nums_copy = ";   print_vec(nums_copy);
    //for(int j=left; j<=r1_max; cout<<"j = "<<j<<endl,     nums[j] = nums_copy[j], j++);
    //cout<<"after copy ===> nums = "; print_vec(nums);
}


vector<int> merge_sort(vector<int>& nums){
    int n = nums.size();
    for(int step = 1; step < n; step *=2){
        //print_vec(nums);
        vector<int> nums_copy = nums;
        // travel all neigbor left and left+step list 
        for(int left=0; left + step <n; left += 2*step){
            merge_sort_merge_two_part(nums, nums_copy, left, step, n);
        }
        nums = nums_copy;
    }
    return nums;
}

