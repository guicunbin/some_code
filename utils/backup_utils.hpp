#ifndef _TEST_H_
#define _TEST_H_

#include<iostream>
#include<fstream>
#include<vector>
#include<time.h>
#include<algorithm>
#include<stdexcept>
#include<string>
#include<math.h>
#include<sstream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<assert.h>
#include<typeinfo>
//#include<cblas.h>
extern "C" {
#include <cblas.h>
}
#include<omp.h>
#include<stdio.h>
//#include<abfg.h>
using namespace std;
typedef vector<vector<vector<vector<float> > > > vec_4df;
typedef vector<vector<vector<float> > > vec_3df;
typedef vector<vector<float> > vec_2df;
typedef vector<float> vec_1df;


template <typename Dtype>
string get_type_str(Dtype obj){
    string s = typeid(obj).name();
    return s;
}




template <typename Dtype>
string num2str(Dtype num){
    // string  to  str also   supported
    std::ostringstream ss;
	ss << num;
	std::string s(ss.str());
	return s;
    //  return std::to_string(num);
}




void throw_error(string commment){
    cout<<commment<<endl;
    throw commment;
}



template <typename Dtype>
void CHECK_equal(Dtype a,  Dtype b, string commment = ""){
    // support:  char string float double .......... float* double*  int* ........
    if(a == b) return;
    throw_error("CHECK_equal error !!!  " + commment + ":  "+num2str<Dtype>(a)+" != "+num2str<Dtype>(b));
}



template <typename Dtype>
void CHECK_equal_by_diff(Dtype a,  Dtype b, string commment = "", double diff = 1e-5){
    // not support Pi, Pf (int*,  float* .........).................
    if(get_type_str(a)[0]=='P') throw_error(" not support this Dtype : " + get_type_str(a));
    if(a == b) return;
    if(double(a) - diff < double(b) && double(b) < double(a) + diff) return;
    throw_error("CHECK_equal error !!!  " + commment + ":  "+num2str<Dtype>(a)+" != "+num2str<Dtype>(b));
}




template <typename Dtype>
void CHECK_less(Dtype a,  Dtype b, string commment = ""){
   if(a >= b){
    throw_error("CHECK_less error !!!  " + commment +": "+ num2str<Dtype>(a)+" >= "+num2str<Dtype>(b));
  }
}


template <typename Dtype>
void CHECK_vector_equal(vector<Dtype> vec1,  vector<Dtype> vec2){
    CHECK_equal(int(vec1.size()), int(vec2.size()), " check_vector_size ");
    int n = vec1.size();
    Dtype* p1 = &vec1[0], *p2 = &vec2[0];
    for(int i=0; i<n; i++){
        CHECK_equal(*(p1++), *(p2++));
    }
}




template <typename Dtype>
void CHECK_vector_equal_by_diff(vector<Dtype> vec1,  vector<Dtype> vec2){
    CHECK_equal(int(vec1.size()), int(vec2.size()), " check_vector_size ");
    int n = vec1.size();
    Dtype* p1 = &vec1[0], *p2 = &vec2[0];
    for(int i=0; i<n; i++){
        CHECK_equal_by_diff(*(p1++), *(p2++));
    }
}




template <typename Dtype>
void print_vec(vector<Dtype> nums, string commment = ""){
    if(commment.size() != 0){
        cout<<endl<<commment;
    }
    cout<<endl<<" [ ";
    for(int i=0; i<nums.size(); i++){
        cout<<nums[i]<<",";
    }
    cout<<" ] "<<endl;
}


template <typename Dtype>
void print_vec_with_comment(vector<Dtype> nums,  string commment){
    cout<<commment<<endl;
    print_vec(nums);
}




template <typename Dtype>
void CHECK_vector_equal_test_success(vector<Dtype> expect_vec, vector<Dtype> output, string function_str){
    cout<<" start CHECK "<<function_str<<" .... "<<endl;

    CHECK_vector_equal<Dtype>(expect_vec, output);

    cout<<endl<<" ===> function: "<<function_str<<" success finished !!"<<endl<<endl;
}



template <typename Dtype>
void CHECK_vector_equal_test_success_by_diff(vector<Dtype> expect_vec, vector<Dtype> output, string function_str){
    cout<<" start CHECK "<<function_str<<" .... "<<endl;

    CHECK_vector_equal_by_diff<Dtype>(expect_vec, output);

    cout<<endl<<" ===> function: "<<function_str<<" success finished !!"<<endl<<endl;
}















template <typename Dtype>
void transpose_matrix(vector<Dtype>&nums,  vector<int> shape){
    if(shape.size()!=2) throw_error(" must be 2dim vector");
    if(shape[0] == shape[1]){
        for(int i=0; i<shape[0]; i++){
            for(int j=0; j<i; j++){
                //swap(nums[i][j], nums[j][i]);
                swap(nums[i * shape[1] + j], nums[j*shape[1] + i]);
            }
        }
    }
    else{
        vector<Dtype> new_nums(shape[0]*shape[1]);
        for(int i=0; i<shape[1]; i++){
            for(int j=0; j<shape[0]; j++){
                //swap(nums[i][j], nums[j][i]);
                new_nums[i * shape[0] + j] = nums[j * shape[1] + i];
            }
        }
        nums = new_nums;
    }
}





template <typename Dtype>
class MD_Vec {
	public:
        // use one Dim  vector to save muti dim vector;   can ensure the address continue
		typedef Dtype value_type;
		vector<Dtype> data;
        vector<Dtype> diff;
		vector<int>  shape;


		MD_Vec(vector<int> sha = {1,1,1}){
			shape = sha;
			int len = 1;
			for(int i=0; i<shape.size(); i++){ len *= shape[i]; }
			data.resize(len,    Dtype(0));
            diff.resize(len,    Dtype(0));
		}


        void print(string commment = ""){
            cout<<" -----------------------------------------------"<<endl;
            cout<<" "<<commment<<endl;
            print_vec_with_comment<int>(shape,   " shape = ");
            print_vec_with_comment<Dtype>(data,    " data  = ");
            print_vec_with_comment<Dtype>(diff,    " diff  = ");
            cout<<" -----------------------------------------------"<<endl;
        }


        void print_shape(){
            cout<<" -----------------------------------------------"<<endl;
            print_vec_with_comment<int>(shape,   " shape = ");
            cout<<" -----------------------------------------------"<<endl;
        }
};





template <typename Dtype>
class BS_Data {
	public:
        // use one Dim  vector to save muti dim vector;   can ensure the address continue
		typedef Dtype value_type;
		vector<MD_Vec<Dtype>> bs_data;
        vector<int> bs_shape;

        BS_data(vector<int> bs_sha){
            CHECK_less(1, int(bs_sha.size()));
            bs_shape = bs_sha;
            bs_data.resize(bs_shape[0]);
            vector<int> MD_Vec_shape(bs_shape.begin()+1, bs_shape.end());

            for(int i=0; i<BS; i++){
                bs_data[i] = MD_Vec<Dtype>(MD_Vec_shape);
            }
        }


        void print_shape(){
            cout<<" -----------------------------------------------"<<endl;
            print_vec_with_comment<int>(bs_shape,   " bs_shape = ");
            cout<<" -----------------------------------------------"<<endl;
        }
};



vector<int> stl_sort(vector<int> &nums){
    sort(nums.begin(), nums.end());
    return nums;
}


struct ListNode{
    int val;
    ListNode * next;
    ListNode(int i=0){
        val = i; 
        //next = nullptr;
        next = NULL;
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






template <typename Dtype>
vector<Dtype> get_rand_vec(int test_size){
    vector<Dtype> test_vec(test_size, 0);
    //for(int i=0; i<test_size; test_vec[i] = Dtype(i),i++);
    for(int i=0; i<test_size; test_vec[i] = Dtype(rand() % 10), i++);
    //for(int i=0; i<test_size; test_vec[i] = rand(),i++);
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




// weight_filler; bias_filler;

enum class filler { constant = 0, gaussian=1 };
enum class LayerType { fc =0, conv=1 };
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
void print_vec_4d(vector<vector<vector<vector<Dtype> > > > & vec_4d){
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
void print_4d_vec_shape(vector<vector<vector<vector<Dtype> > > > &vec_4d){
    string shape_str ="{ "+ to_string(vec_4d.size()) + "," + to_string(vec_4d[0].size()) + "," + to_string(vec_4d[0][0].size()) + "," + to_string(vec_4d[0][0][0].size()) + " } ";
    cout<<" shape = "<<shape_str<<endl;
}



template <typename Dtype>
void mat_mul_use_cblas(Dtype *A, Dtype *B, Dtype *C, int row_op_A, int col_op_B, int col_op_A, bool transpose_A=false, bool transpose_B=false, Dtype alpha = Dtype(0))
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
    
    //cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, row_op_A, col_op_B, col_op_A,  1 , A, col_op_A, B, col_op_B, 0, C, col_op_B);
    
    CBLAS_TRANSPOSE TA = transpose_A ? CblasTrans : CblasNoTrans;
    CBLAS_TRANSPOSE TB = transpose_B ? CblasTrans : CblasNoTrans;
	int lda = (TA == CblasNoTrans) ? col_op_A : row_op_A;  // first dim of the A;   first dim mean the col_op_A
  	int ldb = (TB == CblasNoTrans) ? col_op_B : col_op_A;  // first dim of the B  
    //int ldc = (TB == CblasNoTrans) ? col_op_B : row_op_A;
    int ldc = col_op_B;
    cblas_dgemm(CblasRowMajor, TA, TB, row_op_A, col_op_B, col_op_A,  1 , A, lda, B, ldb, alpha, C, ldc);

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


void load_txt_to_vector_string(const char *txt_path, vector<string>& vec_str){
    fstream fst;
    //fst.open(txt_path, ios::in | ios::out);
    fst.open(txt_path, ios::in);
    string line_str;
    while(std::getline(fst, line_str)){
        vec_str.push_back(line_str);
    }
    fst.close();
}



void putText_to_image(vector<string> & texts,   cv::Mat &image){
	//void cv::putText(  
	//    cv::Mat& img, // 待绘制的图像  
	//    const string& text, // 待绘制的文字  
	//    cv::Point origin, // 文本框的左下角  
	//    int fontFace, // 字体 (如cv::FONT_HERSHEY_PLAIN)  
	//    double fontScale, // 尺寸因子，值越大文字越大  
	//    cv::Scalar color, // 线条的颜色（RGB）  
	//    int thickness = 1, // 线条宽度  
	//    int lineType = 8, // 线型（4邻域或8邻域，默认8邻域）  
	//    bool bottomLeftOrigin = false // true='origin at lower left'  
	//);  

	//	cv::Size cv::getTextSize(  
    //	const string& text,  
    //	cv::Point origin,  
    //	int fontFace,  
    //	double fontScale,  
    //	int thickness,  
    //	int* baseLine  
	//	);  


	int font_face = cv::FONT_HERSHEY_COMPLEX;   
	//int font_face = cv::FONT_HERSHEY_SIMPLEX;   
	double font_scale = 0.5;
	int thickness = 1;
	int baseline;
	cv::Point origin;
	//origin.x = image.cols / 2 - text_size.width / 2;  
	//origin.y = image.rows / 2 + text_size.height / 2; 
    origin.x = 20, origin.y = 20;

    for(int i=0; i<texts.size(); i++){
        string text = texts[i];
	    cv::Size text_size = cv::getTextSize(text, font_face, font_scale, thickness, &baseline);
	    if(image.cols <= text_size.width) {
            cout<<text<<endl;
            throw_error("Text_size > image_size !!! ");
        }
	    cv::putText(image, text, origin, font_face, font_scale, cv::Scalar(0, 0, 255), thickness, 8, 0);
        origin.y += 20;
    }
}



vector<string> split_string(string st,  string sep){
    //seq empty
    if(sep.empty()){
        vector<string> res(st.size());
        string tmp = "";    int i=0;
        for(string::iterator it = st.begin(); it != st.end(); it++){
            res[i++] = tmp + *it;
        }
        return res;
    }
    //seq.size() >= 1;
    int start=0;
    string tmp = "";
    int n1 = st.size(),  n2 = sep.size();
    vector<string> res;
    for(int i=0; i<n1; i++){
        if(sep[0]==st[i]){
            //start 
            bool is_sep = true;
            int j=0;
            for(; j<n2; j++, i++){
                if(sep[j] != st[i])
                    is_sep = false;
            }
            // finish 
            if(is_sep){
                res.push_back(st.substr(start, i-n2-start));
                start = i;
            }
            // need backtrack
            else{
                i = i-j;
            }
        }
    }
    if(start < n1){
        res.push_back(st.substr(start, n1-start));
    }
    return res;
}


template <typename Dtype>
MD_Vec<Dtype> cvMat_2_vector(cv::Mat &image){
	int nr=image.rows;
	int nc=image.cols;
	MD_Vec<Dtype> vec({3, nr, nc});
	for(int i=0;i<nr;i++)
	{
	    for(int j=0;j<nc;j++)
	    {
	        //vec[0][i][j] = image.at<cv::Vec3b>(i,j)[0];
	        //vec[1][i][j] = image.at<cv::Vec3b>(i,j)[1];
	        //vec[2][i][j] = image.at<cv::Vec3b>(i,j)[2];
			vec.data[0          + i*nc + j]  = image.at<cv::Vec3b>(i,j)[0];
			vec.data[nr*nc		+ i*nc + j]  = image.at<cv::Vec3b>(i,j)[1];
			vec.data[2*nr*nc 	+ i*nc + j]  = image.at<cv::Vec3b>(i,j)[2];
	    }
	}
	return vec;
}




MD_Vec<int> read_image_to_vector(string image_path){
    cv::Mat mat = cv::imread(image_path, 3);
	MD_Vec<int> vec3d = cvMat_2_vector<int>(mat);
    return vec3d;
}



template <typename Dtype>
void img2col_by_kernelmat(Dtype* p_vec3d, Dtype* p_vec2d, vector<int> vec3d_shape,  vector<int> vec2d_shape, int kernel_size, int stride, int pad = 0){
    int C_in = vec3d_shape[0], H_in = vec3d_shape[1], W_in = vec3d_shape[2];
    int H_out = (H_in - kernel_size + 2*pad) / stride + 1; 
    int W_out = (W_in - kernel_size + 2*pad) / stride + 1; 
    int H_res = C_in * kernel_size * kernel_size;
    int W_res = H_out * W_out;
    CHECK_equal(H_res, vec2d_shape[0], num2str(__LINE__));
    CHECK_equal(W_res, vec2d_shape[1], num2str(__LINE__));

    Dtype *p_2d = p_vec2d;
    Dtype *p_3d  = p_vec3d;

    for(int c_in=0; c_in<C_in; c_in++){
        for(int k_h=0; k_h<kernel_size; k_h++){
            for(int k_w=0; k_w<kernel_size; k_w++){
            // start one row of the return vec2d;
                for(int h_out=0, h_in = k_h - pad; h_out<H_out; h_out++, h_in += stride){
                    for(int w_out=0, w_in = k_w - pad; w_out<W_out; w_out++, w_in += stride){
                        if(h_in < 0 || h_in >= H_in || w_in < 0 || w_in >= W_in){
                            *p_2d = 0;
                        }
                        *p_2d = p_3d[h_in* W_in + w_in];
                        p_2d ++;
                    }
                }
            //end one row of the return vec2d;
            }
        }
        // travel finished one channel
        p_3d += H_in * W_in;
    }
}





template <typename Dtype>
void col2img_by_kernelmat(Dtype* p_vec3d, Dtype* p_vec2d, vector<int> vec3d_shape,  vector<int> vec2d_shape, int kernel_size, int stride, int pad = 0){
    int C_in = vec3d_shape[0], H_in = vec3d_shape[1], W_in = vec3d_shape[2];
    int H_out = (H_in - kernel_size + 2*pad) / stride + 1; 
    int W_out = (W_in - kernel_size + 2*pad) / stride + 1; 
    int H_res = C_in * kernel_size * kernel_size;
    int W_res = H_out * W_out;
    CHECK_equal(H_res, vec2d_shape[0], num2str(__LINE__));
    CHECK_equal(W_res, vec2d_shape[1], num2str(__LINE__));

    Dtype *p_2d = p_vec2d;
    Dtype *p_3d  = p_vec3d;

    for(int c_in=0; c_in<C_in; c_in++){
        for(int k_h=0; k_h<kernel_size; k_h++){
            for(int k_w=0; k_w<kernel_size; k_w++){
            // start one row of the return vec2d;
                for(int h_out=0, h_in = k_h - pad; h_out<H_out; h_out++, h_in += stride){
                    for(int w_out=0, w_in = k_w - pad; w_out<W_out; w_out++, w_in += stride){
                        if(h_in < 0 || h_in >= H_in || w_in < 0 || w_in >= W_in){
                            *p_2d = 0;
                        }
                        //  *p_2d = p_3d[h_in* W_in + w_in];
                        //  p_2d ++;
                        //  notice: this is add to p_3d; because the diff need add 
                        p_3d[h_in * W_in + w_in] += *p_2d;
                        p_2d ++;
                    }
                }
            //end one row of the return vec2d;
            }
        }
        // travel finished one channel
        p_3d += H_in * W_in;
    }
}


















template <typename Dtype>
void compute_conv2d_by_mat_mul(vector<MD_Vec<Dtype> > &input,   vector<MD_Vec<Dtype>> &output,  MD_Vec<Dtype> &kernel,   int stride,    int pad){
    int bs = input.size();
    int C_out   = output[0].shape[0],      H_out   = output[0].shape[1],  W_out   = output[0].shape[2];
    int C_in    = input[0].shape[0],       H_in    = input[0].shape[1],   W_in    = input[0].shape[2];
    int kernel_size = kernel.shape[3];
	int row_A = C_out;
    int col_A = C_in * kernel_size * kernel_size;
    int row_B = C_in * kernel_size * kernel_size;
    int col_B = H_out * W_out;
    //CHECK_equal(C_out,  kernel.shape[0]);
    //CHECK_equal(C_in,   kernel.shape[1]);
    //CHECK_equal(H_out,  (H_in - kernel_size + 2 * pad) / stride + 1 );
    //CHECK_equal(W_out,  (W_in - kernel_size + 2 * pad) / stride + 1 );
    //#pragma omp parallel for
    for(int i=0; i<bs; i++){
        vector<Dtype> input_data_2d(row_B*col_B);
        img2col_by_kernelmat<Dtype>(&input[i].data[0], &input_data_2d[0], {C_in, H_in, W_in},  {row_B, col_B}, kernel_size, stride, pad);
		// cur_input.shape = {C_in * K_h * K_w,   H_out * W_out}
		// kernel.shape    = {C_out, C_in, K_h, K_w};
		Dtype *A = &kernel.data[0], *B = &input_data_2d[0], *C = &output[i].data[0];
		mat_mul_use_cblas(A, B, C, row_A, col_B, col_A, false, false);
    }
}





template <typename Dtype>
void compute_conv2d_by_mat_mul_backward(vector<MD_Vec<Dtype> > &input,   vector<MD_Vec<Dtype>> &output,  MD_Vec<Dtype> &kernel,   int stride,    int pad){
    int bs = input.size();
    int C_out   = output[0].shape[0],      H_out   = output[0].shape[1],  W_out   = output[0].shape[2];
    int C_in    = input[0].shape[0],       H_in    = input[0].shape[1],   W_in    = input[0].shape[2];
    int kernel_size = kernel.shape[3];
    int row_kernel = C_out;
    int col_kernel = C_in * kernel_size * kernel_size;
    int row_input  = C_in * kernel_size * kernel_size;
    int col_input  = H_out * W_out;
    int row_output = C_out;
    int col_output = H_out * W_out;
    CHECK_equal(C_out,  kernel.shape[0]);
    CHECK_equal(C_in,   kernel.shape[1]);
    CHECK_equal(H_out,  (H_in - kernel_size + 2 * pad) / stride + 1 );
    CHECK_equal(W_out,  (W_in - kernel_size + 2 * pad) / stride + 1 );
    //#pragma omp parallel for
    for(int i=0; i<bs; i++){
        vector<Dtype> input_diff_2d(row_input* col_input);
        vector<Dtype> input_data_2d(row_input* col_input);

        // get col input_data_2d
        img2col_by_kernelmat<Dtype>(&input[i].data[0], &input_data_2d[0], {C_in, H_in, W_in},  {row_input, col_input}, kernel_size, stride, pad);
		// cur_input.shape = {C_in * K_h * K_w,   H_out * W_out}
		// kernel.shape    = {C_out, C_in, K_h, K_w};
        // output.shape    = {C_out, H_out*W_out};
		//void  mat_mul_use_cblas(A, B, C, row_A, col_B, col_A, false,	true);
        

        // from output diff to cur_input diff
		mat_mul_use_cblas(&kernel.data[0], &output[i].diff[0], &input_diff_2d[0], col_kernel, col_output, row_kernel,  true, false);
        // col2img_by_kernelmat  contains add operation
        col2img_by_kernelmat<Dtype>(&input[i].diff[0], &input_diff_2d[0], {C_in, H_in, W_in}, {row_input, col_input},  kernel_size,  stride,  pad);


        // from output diff to kernel diff,  diff = old_diff + new_diff,  so  the final need 1.0 
		mat_mul_use_cblas(&output[i].diff[0], &input_data_2d[0], &kernel.diff[0], row_output, row_input, col_output, false, true, 1.0);
    }
}










template <typename Dtype>
void compute_conv2d_by_7_for(vector<MD_Vec<Dtype> > &input,   vector<MD_Vec<Dtype>> &output,  MD_Vec<Dtype> &kernel,   int stride,    int pad=0){
    int BS = input.size();
    int kernel_size = kernel.shape[3];
    int C_in    = input[0].shape[0],       H_in    = input[0].shape[1],   W_in    = input[0].shape[2];
    int C_out   = output[0].shape[0],      H_out   = output[0].shape[1],  W_out   = output[0].shape[2];
    //  CHECK_equal(input.size(), output.size(), num2str(__LINE__));
    //  CHECK_equal(C_out,  kernel.shape[0], num2str(__LINE__));
    //  CHECK_equal(C_in,   kernel.shape[1], num2str(__LINE__));
    //  CHECK_equal(kernel.shape[2],    kernel.shape[3],   num2str( __LINE__));
    //  CHECK_equal(H_out, (H_in - kernel_size + 2* pad) / stride + 1, num2str(__LINE__));
    //  CHECK_equal(W_out, (W_in - kernel_size + 2* pad) / stride + 1, num2str(__LINE__));
	int row_A = C_out;
    int col_A = C_in * kernel_size * kernel_size;
    int row_B = C_in * kernel_size * kernel_size;
    int col_B = H_out * W_out;
    for(int bs = 0; bs < BS; bs++){
        Dtype* top, *bot, *ker;
        top = &output[bs].data[0];
        ker = &kernel.data[0];
        for(int c_out=0; c_out < C_out; c_out++,  top += H_out * W_out){
            bot = &input[bs].data[0];
            for(int c_in=0; c_in < C_in; c_in ++, bot += H_in * W_in,   ker += kernel_size * kernel_size){
                for(int h_out=0; h_out < H_out; h_out ++){
                    for(int w_out=0; w_out < W_out; w_out ++){
                        for(int kh=0; kh < kernel_size; kh ++){
                            for(int kw=0; kw < kernel_size; kw ++){
                                int h_in = h_out*stride + kh ,   w_in = w_out*stride + kw;
                                //  CHECK_less(h_in, H_in, num2str(__LINE__));
                                //  CHECK_less(w_in, W_in, num2str(__LINE__));
                                //  CHECK_less(bot + h_in * W_in + w_in, &input[bs].data.back() + 1, num2str(__LINE__));
                                //  CHECK_less(ker + kh * kernel_size + kw, &kernel.data.back() + 1, num2str(__LINE__));
                                //  CHECK_less(top + h_out * W_out + w_out,  &output[bs].data.back() + 1,num2str(__LINE__));
                                *(top + h_out * W_out + w_out) += (*(bot + h_in * W_in + w_in)) * (*(ker + kh * kernel_size + kw));
                            }
                        }
                    }
                }
            }
        }
    }
}








// ===============================   relu   ===================================

template <typename Dtype>
void math_RELU(vector<MD_Vec<Dtype> > &input){
    int BS = input.size();
    for(int i=0; i<BS; i++){
        Dtype *p = &input[i].data[0];
        int size_data = input[i].data.size();
        for(int j=0; j<size_data; j++){
            *p = (*p) > 0 ? (*p) : 0;
            p ++;
        }
    }
}



template <typename Dtype>
void math_RELU_backward(vector<MD_Vec<Dtype> > &input){
    int BS = input.size();
    for(int i=0; i<BS; i++){
        Dtype *pdiff = &input[i].diff[0];
        Dtype *pdata = &input[i].data[0];
        int size_data = input[i].data.size();
        for(int j=0; j<size_data; j++){
            *pdiff = (*pdata) > 0 ? (*pdiff) : 0;
            pdiff ++;   pdata ++;
        }
    }
}



// ===============================   relu   ===================================






// ===============================   fc   ===================================

template <typename Dtype>
void compute_fc_by_mat_mul(vector<MD_Vec<Dtype> > &input,   vector<MD_Vec<Dtype>> &output,  MD_Vec<Dtype> &kernel){
    int bs = input.size();
    int C_out   = output[0].shape[0];
    int C_in    = input[0].shape[0];
    CHECK_equal(C_out, kernel.shape[0], num2str(__LINE__));
    CHECK_equal(C_in,  kernel.shape[1], num2str(__LINE__));
	int row_A = C_out;
    int col_A = C_in;
    int row_B = C_in;
    int col_B = 1;
    for(int i=0; i<bs; i++){
		Dtype *A = &kernel.data[0], *B = &input[i].data[0], *C = &output[i].data[0];
        //cout<<" start mat_mul "<<endl;
		mat_mul_use_cblas(A, B, C, row_A, col_B, col_A, false, false);
        //mat_mul_self_implement_2(A, B, C, row_A, col_B, col_A);
    }
}





template <typename Dtype>
void compute_fc_by_mat_mul_backward(vector<MD_Vec<Dtype> > &input,   vector<MD_Vec<Dtype>> &output,  MD_Vec<Dtype> &kernel){
    int bs = input.size();
    int C_out   = output[0].shape[0];
    int C_in    = input[0].shape[0];
    CHECK_equal(C_out, kernel.shape[0], num2str(__LINE__));
    CHECK_equal(C_in,  kernel.shape[1], num2str(__LINE__));
    for(int i=0; i<bs; i++){
		//Dtype *A = &kernel.data[0], *B = &input[i].data[0], *C = &output[i].data[0];
		//mat_mul_use_cblas(A, B, C, row_A, col_B, col_A, false, false);
        //
        // from output[i].diff  to input[i].diff
        // [1, C_out]  * [C_out, C_in];
		Dtype *A = &output[i].diff[0], *B = &kernel.data[0], *C = &input[i].diff[0];
		mat_mul_use_cblas(A, B, C, 1, C_in, C_out, false, false, Dtype(1.0));

        // from output[i].diff  to kernel[i].diff
        // [C_out, 1] * [1,  C_in]
		A = &output[i].diff[0], B = &input[i].data[0], C = &kernel.diff[0];
		mat_mul_use_cblas(A, B, C, C_out, C_in, 1, false, false, Dtype(1.0));
    }
}

// ===============================   fc   ===================================



// ===============================  softmax =================================
template <typename Dtype>
void compute_softmax(vector<MD_Vec<Dtype> > &input,   vector<MD_Vec<Dtype>> &output){
    int BS = input.size();
    CHECK_less(0, BS);
    CHECK_equal(int(input.size()), int(output.size()));
    CHECK_equal(int(input[0].shape.size()),   1);
    CHECK_equal(int(output[0].shape.size()),  1);
    int C_in_out = input[0].shape[0];
    for(int i =0; i<BS; i++){
        Dtype row_sum = 0, *p_in = &input[i].data[0],   *p_ou = &output[i].data[0];
        for(int j=0; j<C_in_out; row_sum += std::exp(*(p_in + j)), j++);
        for(int j=0; j<C_in_out; j++){
            *(p_ou + j) = std::exp(*(p_in + j)) / row_sum;
        }
    }
}

// ===============================  softmax =================================







// ===============================  softmax_cross_entroy_loss =================================
template <typename Dtype>
void compute_softmax_cross_entroy_loss(vector<MD_Vec<Dtype>>&probs, vector<MD_Vec<Dtype>> &labels,  Dtype &loss){
    // loss = mean({log(p_i)})
    int BS = probs.size();
    CHECK_equal(BS, int(labels.size()));    CHECK_less(0, BS);
    int C_in_out = probs[0].data.size();
    loss = 0;
    for(int bs = 0; bs < BS; bs++){
        Dtype *p_lo = &probs[bs].data[0], *p_la = &labels[bs].data[0];
        for(int i=0; i<C_in_out; i++){
            if(*(p_la + i)==0) continue;
            loss += - std::log(std::max(1e-10, *(p_lo + i)));
        }
    }
    loss = loss / BS;
}



template <typename Dtype>
void compute_softmax_cross_entroy_loss_backward(vector<MD_Vec<Dtype>> &logits,  vector<MD_Vec<Dtype>>&probs,   vector<MD_Vec<Dtype>> &labels){
    // just need backward to logits_diff
    int BS = probs.size();
    CHECK_equal(BS, int(labels.size()));    CHECK_less(0, BS);
    int C_in_out = probs[0].data.size();
    for(int bs = 0; bs<BS; bs++){
        Dtype *p_logits_diff = &logits[bs].diff[0], *p_probs_data = &probs[bs].data[0], *p_labels_data = &labels[bs].data[0];
        for(int i=0; i<C_in_out; i++){
            *(p_logits_diff + i) = (1.0 / BS) * (*(p_probs_data + i) - *(p_labels_data + i));
        }
    }
}
// ===============================  softmax_cross_entroy_loss =================================


// ===============================  dw_conv =================================
// ===============================  dw_conv =================================




























#endif

