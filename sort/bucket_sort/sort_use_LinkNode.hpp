#include<vector>
#include<iostream>
#include<climits>
#include"../../utils/utils.hpp"
using namespace std;

void bucket_sort_insert_to_bucket(ListNode *prehead, int val){
    // here use insert_sort
    //cout<<"val = "<<val<<endl;  print_listnodes(prehead);
    ListNode* pre = prehead, *cur = prehead->next;
    ListNode* new_node = new ListNode(val);
    while(cur && cur->val <= val){
        pre = cur;
        cur = cur->next;
    }
    // insert into the front of the cur
    pre->next = new_node;
    new_node->next = cur;
}


ListNode* merge_two_sorted_listnodes_general(ListNode* prehead1, ListNode* prehead2){
    ListNode* prehead = new ListNode(-1);
    //  cout<<"this is in merge func  start ";     print_listnodes(prehead);
    //  cout<<"prehead1 = ";                print_listnodes(prehead1);
    //  cout<<"prehead2 = ";                print_listnodes(prehead2);
    ListNode* pre = prehead, *l1 = prehead1->next, *l2 = prehead2->next;
    while(l1 && l2){
        if(l1->val < l2->val){
            pre->next = l1;     l1 = l1->next;  pre = pre->next;
        }
        else{
            pre->next = l2;     l2 = l2->next;  pre = pre->next;
        }
    }
    if(l1){pre->next = l1;}
    if(l2){pre->next = l2;}
    //  cout<<"this is in merge func;  end  ";     print_listnodes(prehead);
    return prehead;
}




vector<int> bucket_sort(vector<int> &nums){
    int n = nums.size();    if(n<=1) return nums;
    int max_num = INT_MIN, min_num = INT_MAX;
    for(auto nu: nums){
        max_num = nu > max_num ? nu : max_num;
        min_num = nu < min_num ? nu : min_num;
    }


    /// ====================== define the BUCKET_NUM and BUCKET_STEP ====================

    //  int BUCKET_NUM = (max_num - min_num + 1) / 1000;
    //  BUCKET_NUM = (BUCKET_NUM == 0) ? (n / 2) : BUCKET_NUM;
    //  int BUCKET_NUM = (max_num - min_num + 1); 
    int BUCKET_NUM = n ;
    int BUCKET_STEP = ((max_num - min_num + 1) / BUCKET_NUM) + 1;
    cout<<"BUCKET_NUM, BUCKET_STEP = "<<BUCKET_NUM<<","<<BUCKET_STEP<<endl;



    /// ====================== init the bucket vector               ====================

    //vector<ListNode*> bucket(BUCKET_NUM, new ListNode(-1));   // this is error 
    //vector<ListNode*> bucket(BUCKET_NUM, (ListNode*)(-1));    // this is error
    vector<ListNode*> bucket(BUCKET_NUM);
    for(int i=0;    i<BUCKET_NUM;   bucket[i++] = new ListNode(-1));



    /// ====================== insert nums[i] and sort every bucket ====================
    for(auto nu: nums){
        int index = (nu - min_num) / BUCKET_STEP;
        //cout<<"nu, min_num, index = "<<nu<<","<<min_num<<","<<index<<endl;
        bucket_sort_insert_to_bucket(bucket[index], nu);
    }



    /// ====================== merge every bucket                   ====================
    // because the nums in bucket[i-1] all less the nums in bucket[i]; so from bucket[0] start;
    ListNode* tail = bucket[0];
    //cout<<"bucket[0] = ";   print_listnodes(bucket[0]->next);
    while(tail->next){
        tail = tail -> next;
    }

    // just need to Link tail and head;  O(n);   n is the size of the sorted nums;
    for(int i=1; i<BUCKET_NUM; i++){
        if(bucket[i]->next){
            tail->next = bucket[i]->next;
            while(tail->next){ tail = tail->next; }
        }
    }
    // fill nums
    ListNode* prehead = bucket[0];
    for(int i=0; i<n; i++){
        nums[i] = prehead->next->val;
        prehead = prehead->next;
    }

    // ==========	release bucket and ListNodes 	=============
    //	cout<<"bucket.capacity() = "<<bucket.capacity()<<endl;
    release_listnode_pointers(bucket[0]);
    //	cout<<"bucket.capacity() = "<<bucket.capacity()<<endl;
	//	bucket.clear();	bucket.shrink_to_fit();
	release_vector(bucket);
    //cout<<"bucket.capacity() = "<<bucket.capacity()<<endl;

    return nums;
}


