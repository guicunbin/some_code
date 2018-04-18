#ifndef _TEST_H_
#define _TEST_H_

#include<iostream>
#include<vector>
#include<time.h>
#include<algorithm>
#include<stdexcept>
#include<string>
//#include<cblas.h>
extern "C" {
#include <cblas.h>
}
#include<stdio.h>
//#include<abfg.h>
using namespace std;
typedef vector<vector<vector<vector<float>>>> vec_4df;
typedef vector<vector<vector<float>>> vec_3df;
typedef vector<vector<float>> vec_2df;
typedef vector<float> vec_1df;


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


template <typename Dtype>
void print_vec(vector<Dtype> nums){
    cout<<endl<<" [ ";
    for(auto nu: nums){
        cout<<nu<<",";
    }
    cout<<" ] "<<endl;
}

template <typename Dtype>
void print_c_array(Dtype nums[], int n){
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


template <typename Dtype>
void get_rand_c_array(Dtype* test_vec, int test_size){
    //for(int i=0; i<test_size; test_vec[i]=rand() % 10,i++);
    for(int i=0; i<test_size; test_vec[i]=(rand() % 100) / 10.0,i++);
    if(test_size < 50){
        print_c_array(test_vec, test_size);
    }
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


void throw_error(string commment){
    throw std::invalid_argument(commment);
}


// weight_filler; bias_filler;

enum class filler { gaussian, constant };
enum class LayerType { fc, conv };
//  class filler{
//      public:
//          int gaussian = 0;
//          int constant = 1;
//  };
//  
//  
//  class LayerType{
//      public:
//          int fc = 0;
//          int conv = 1;
//  };



vec_4df get_4D_vec(vector<int> shape){
    vec_4df res(shape[0], vec_3df(shape[1], vec_2df(shape[2], vec_1df(shape[3], 0.0))));
    for(int i1 = 0; i1 < shape[0]; i1++){
        for(int i2=0; i2 < shape[1]; i2++){
            for(int i3=0; i3<shape[2]; i3++){
                for(int i4=0; i4<shape[3]; i4++){
                    res[i1][i2][i3][i4] = i2 * 1.0;
                }
            }
        }
    }
    return res;
}



template <typename Dtype> 
void print_vec_4d(vector<vector<vector<vector<Dtype>>>> & vec_4d){
    int s1 = vec_4d.size(),         s2 = vec_4d[0].size();
    int s3 = vec_4d[0][0].size(),   s4 = vec_4d[0][0][0].size();
    cout<<" [ ";
    for(int i1 = 0; i1 < s1; i1 ++){
        cout<<" [ ";
        for(int i2 = 0; i2 < s2; i2 ++){
            cout<<" [ ";
            for(int i3 = 0; i3 < s3; i3 ++){
                print_vec(vec_4d[i1][i2][i3]);  cout<<","<<endl;
            }
            cout<<" ], ";
        }
        cout<<" ], ";
    }
    cout<<" ] "<<endl;
}

template <typename Dtype>
void gaussian_init_4dim_vector(vector<vector<vector<vector<Dtype>>>> &vec_4d){
    int s1 = vec_4d.size(),         s2 = vec_4d[0].size();
    int s3 = vec_4d[0][0].size(),   s4 = vec_4d[0][0][0].size();
    for(int i1 = 0; i1 < s1; i1 ++){
        for(int i2 = 0; i2 < s2; i2 ++){
            for(int i3 = 0; i3 < s3; i3 ++){
                for(int i4 = 0; i4 < s4; i4 ++){
                    vec_4d[i1][i2][i3][i4] = Dtype(i2 * rand() % 10);
                }
            }
        }
    }
}


template <typename Dtype>
void print_4d_vec_shape(vector<vector<vector<vector<Dtype>>>> &vec_4d){
    string shape_str ="{ "+ to_string(vec_4d.size()) + "," + to_string(vec_4d[0].size()) + "," + to_string(vec_4d[0][0].size()) + "," + to_string(vec_4d[0][0][0].size()) + " } ";
    cout<<" shape = "<<shape_str<<endl;
}



template <typename Dtype>
void mat_mul_use_cblas(Dtype *A, Dtype *B, Dtype *C, int row_A, int col_B, int col_A)
{
// --------------------------------------------------------------------
// http://www.netlib.org/lapack/explore-html/d1/d54/group__double__blas__level3_gaeda3cbd99c8fb834a60a6412878226e1.html#gaeda3cbd99c8fb834a60a6412878226e1
//  subroutine dgemm    (   character   TRANSA,
//          character   TRANSB,
//          integer     M,
//          integer     N,
//          integer     K,
//          double precision    ALPHA,
//          double precision, dimension(lda,*)  A,
//          integer     LDA,
//          double precision, dimension(ldb,*)  B,
//          integer     LDB,
//          double precision    BETA,
//          double precision, dimension(ldc,*)  C,
//          integer     LDC 
//          )       

// DGEMM  performs one of the matrix-matrix operations
//    C := alpha*op( A )*op( B ) + beta*C,
// 	where  op( X ) is one of
//   op( X ) = X   or   op( X ) = X**T,
//	 alpha and beta are scalars, and A, B and C are matrices, with op( A )
//	 an m by k matrix,  op( B )  a  k by n matrix and  C an m by n matrix.
    
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, row_A, col_B, col_A,  1 , A, col_A, B, col_B, 0, C, col_B);

}




template <typename Dtype>
void mat_mul_self_implement_1(Dtype* A, Dtype* B, Dtype* C, int row_A, int col_B, int col_A, bool row_major = true){
    // just static Dtype res[100]; can return res; http://blog.51cto.com/forlinux/1530404
    Dtype tmp;
    for(int i=0; i<row_A; i++){
        for(int j=0; j<col_B; j++){
            tmp = 0;
            for(int k1=0; k1<col_A; k1++){
                tmp += (*(A + i*col_A + k1)) * (*(B + k1*col_B + j));
            }
            *(C + i*col_B + j) = tmp;
        }
    }
}




template <typename Dtype>
void mat_mul_self_implement_2(Dtype* A, Dtype* B, Dtype* C,  int row_A, int col_B, int col_A, bool row_major = true){
    Dtype tmp;
    Dtype *pa = A, *pb = B, *pc = C;
    for(int i=0; i<row_A; i++){
        for(int j=0; j<col_B; j++){
            tmp = 0; // use tmp 可以提高缓存命中率,更快
            //C[i * col_B + j] = 0;
            for(int k1=0; k1<col_A; k1++){
                //tmp += A[i*col_A + k1] * B[k1 * col_B + j];
                tmp += *(pa + k1) * B[k1 * col_B + j];
                //C[i * col_B + j] += A[i*col_A + k1]*B[k1 * col_B + j];
            }
            //C[i * col_B + j] = tmp;
            *(pc + j) = tmp;
            //pc[j] = tmp;
        }
        pa += col_A;
        pc += col_B;
    }
}


#endif

