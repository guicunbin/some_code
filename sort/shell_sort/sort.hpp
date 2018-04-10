#include<vector>
#include<climits>
#include<iostream>
#include<cmath>
#include"../../utils/utils.hpp"
using namespace std;

void shell_sort_insert_sort_step(vector<int>& nums, int &n, int step){
    // every column col[][1] = [step, step+1, .... 2*step] 
    for(int i=step; i<n; i++){
        int insert_idx = i, insert_num = nums[i];
        while( insert_idx >= step && nums[insert_idx - step] > insert_num){
            nums[insert_idx] = nums[insert_idx - step];
            insert_idx -= step;
        }
        nums[insert_idx] = insert_num;
    }
    //  cout<<"step = "<<step<<endl;    print_vec(nums);
}



int shell_sort_step_f1(int i){
    return 9 * (pow(4,i) - pow(2, i)) + 1;
}


int shell_sort_step_f2(int i){
    return pow(2, i+2) * (pow(2, i+2) - 3) + 1;
}


vector<int> shell_sort(vector<int> & nums){
    int n = nums.size();
    if(n<=1) return nums;
    vector<int> steps;
    
    //  //clock_t start_time = clock();



    //  // must be from n/2 to 1; can't be from 1 to n/2;
    //  for(int step = n/2; step >=1 ;  steps.push_back(step), step /=2);
    //  int steps_size = steps.size();
    //  for(int i=0; i<steps_size/2; swap(steps[i], steps[steps_size-1-i]),i++);



    //  // this is the best steps {1, 5, 19, .....}
    int i=0, j=0;
    int tmp1 = shell_sort_step_f1(i);
    int tmp2 = shell_sort_step_f2(j);
    while(true){
        //cout<<"tmp1, tmp2 = "<<tmp1<<","<<tmp2<<endl;
        if(min(tmp1, tmp2) >= n) break;
        if(tmp1 < tmp2){
            steps.push_back(tmp1);
            i ++;
            tmp1 = shell_sort_step_f1(i);
        }
        else{
            steps.push_back(tmp2);
            j++;
            tmp2 = shell_sort_step_f2(j);
        }
    }
    //print_time_using(start_time, "build steps vector run_time = ");




    for(int i=steps.size()-1; i>=0; i--){
        shell_sort_insert_sort_step(nums, n, steps[i]);
    }


    //  print_vec(steps);
    //  //shell_sort_insert_sort_step(nums, n, 1);
    return nums;
}
