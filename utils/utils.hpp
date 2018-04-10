#ifndef _TEST_H_
#define _TEST_H_

#include<iostream>
#include<vector>
#include<time.h>
#include<algorithm>
#include<stdexcept>
using namespace std;


vector<int> stl_sort(vector<int> &nums){
    sort(nums.begin(), nums.end());
    return nums;
}

struct ListNode{
    int val;
    ListNode * next;
    ListNode(int i=0){
        val = i; next = nullptr;
    }
};


template <typename T> 
void delete_pointer(T*& a){  
    delete a;  
    a = NULL;  
}


template <typename T> 
void release_vector(vector<T>& nums){
	nums.clear();
	nums.shrink_to_fit();
}


void release_listnode_pointers(ListNode* head){
	if(!head) return;
	ListNode* tmp = head;
	while(head->next){
		tmp = head;
		head = head->next;
		free(tmp);
	};
	free(head);
}


template <typename T> 
bool is_be_sorted(vector<T> nums){
    for(int i=1; i<nums.size(); i++){
        if(nums[i-1] > nums[i]) return false;
    }
    return true;
}



void print_vec(vector<int> nums){
    cout<<endl<<" { ";
    for(auto nu: nums){
        cout<<nu<<",";
    }
    cout<<" } "<<endl;
}


void print_c_array(int nums[], int n){
    cout<<endl<<" { ";
    for(int i=0; i<n; i++){
        cout<<nums[i]<<",";
    }
    cout<<" } "<<endl;
}




void print_listnodes(ListNode* head){
    ListNode *p = head;
    cout<<endl<<" { ";
    while(p){
        cout<<p->val<<",";
        p = p->next;
    }
    cout<<" } "<<endl;
}







vector<int> get_rand_vec(int test_size){
    vector<int> test_vec(test_size, 0);
    for(int i=0; i<test_size; test_vec[i]=i,i++);
    //for(int i=0; i<test_size; test_vec[i]=rand() % 1000,i++);
    //for(int i=0; i<test_size; test_vec[i]=rand(),i++);
    random_shuffle(test_vec.begin(), test_vec.end());
    return test_vec;
}







void print_time_using(clock_t start, string commment){
    cout<<commment<<(double(clock() - start)*1000) / CLOCKS_PER_SEC <<" ms"<<endl; 
}




void print_sort_time(vector<int> sort_func(vector<int>& ), vector<int> test_vec, bool is_print_vec){
    if (is_print_vec){
        cout<<"original = "<<endl; 
        print_vec(test_vec);
    }

    clock_t start = clock();
    //here the assignment is very Time-consuming; 1.5 % time  for bucket_sort
    //test_vec = sort_func(test_vec);
    sort_func(test_vec);
    print_time_using(start, "----------------------------------------------------------------- run_time = ");

    if (is_print_vec){
        cout<<"finally = "<<endl; 
        print_vec(test_vec);
        //test_vec = {0,2,1};
        if(is_be_sorted(test_vec)){
            cout<<"--- YES --- "<<endl;
        }
        else{
            throw std::invalid_argument("-- not sorted ---");
        }
    }
}





#endif

