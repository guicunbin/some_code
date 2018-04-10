#include"../../utils/utils.hpp"
#include<iostream>
#include<vector>
using namespace std;

vector<int> count_sort(vector<int>& nums){
    int min_num = INT_MAX, max_num = INT_MIN, n = nums.size();
    for(auto nu:nums){
        min_num = nu < min_num ? nu : min_num;
        max_num = nu > max_num ? nu : max_num;
    }
    int size = max_num - min_num + 1;
    //  cout<<"----- *****  The counting array size = "<<size<<endl;
    //  if size is too larger ,the c array  will stack overflow and raise "Segment error"; but vector allocate memory from heap; so don't limit the size 
    //  int C[size];    fill_n(C, size, 0);//for(int i=0; i<size; C[i++]=0);
    //  int C array will faster 10% than vector<int>
    vector<int> C(size, 0);
    //  cout<<"after init the counting array"<<endl;
    //  counting 
    for(auto nu: nums){
        C[nu-min_num] ++;
    }
    //  cout<<"after travel nums and counting"<<endl;
    //  fill the nums by the counting array

    //// Method 1:  travel the C, fill the (val + min_num) when C[val]!=0;  // O(max_num - min_num + 1); 
    //  this Method will be faster and don't need extra a new res array
    //  cout<<"start fill the nums depend on the counting array"<<endl;
    for(int nu=0, i=0; nu<size; nu++){
        //cout<<"i= "<<i<<endl;
        while(C[nu]-- >0){
            nums[i++] = nu + min_num;
        }
    }
    //cout<<"counting array size, capacity = "<<C.size()<<","<<C.capacity()<<endl;
    C.clear();  C.shrink_to_fit();
    //  cout<<"after shrink_to_fit(), counting array size, capacity = "<<C.size()<<","<<C.capacity()<<endl;
    //  cout<<"after all operates"<<endl;
    return nums;

    //// Method 2:  first travel the C, sum the prev ==> C[i] = sum(C[0....i-1]);  // O(max_num - min_num + 1); 
    //  for(int i=1; i<size; C[i]+=C[i-1],i++); //C[nu - min_num]-1 mean the index of nu in nums;
    //  vector<int> res(n, 0);
    //  for(int i=n-1;  i>=0; i--){
    //      res[--C[nums[i]-min_num]] = nums[i];
    //  }
    //  return res;
}
