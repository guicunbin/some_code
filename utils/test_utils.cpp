#include"./utils.hpp"
//#include<opencv2/core/core.hpp>
//#include<opencv2/highgui/highgui.hpp>

//#define row_A  1000  //1000  // 5
//#define col_B  1000  //1000  // 4
//#define col_A  1000  //1000  // 2
//#define size_A row_A*col_A
//#define size_B col_A*col_B
//#define size_C row_A*col_B
void test_CHECK_equal(){
    CHECK_equal_by_diff<double>(1e-6, 1.5e-6, " diff = 1e-6 ", 1e-6);
    CHECK_equal_by_diff<double>(1e-7, 1.2e-7, " diff = 1e-7 ", 1e-7);
    CHECK_vector_equal_test_success_by_diff(vector<double>{1.1e-4, 1.2e-4}, vector<double>{1.1001e-4, 1.200001e-4}, __FUNCTION__);
}


void test_get_type_str(){
    int i =9;
    int *pi = &i;
    float f = 9;
    double d = 9;
    string st_i = "i";
    string st_pi = "Pi";
    string st_f = "f";
    string st_d = "d";
    CHECK_equal(get_type_str(i),  st_i);
    CHECK_equal(get_type_str(pi), st_pi);
    CHECK_equal(get_type_str(f),  st_f);
    CHECK_equal(get_type_str(d),  st_d);
    cout<<" "<<__FUNCTION__<<" success finished !! "<<endl;
}


void get_conv_test_data(vector<MD_Vec<double>> &bs_in, vector<MD_Vec<double>> &bs_out, MD_Vec<double>& kernel){
    int C_in = 2,  H_in = 3, W_in = 3, stride = 1, kernel_size = 2, C_out = 3, pad = 0, bs = 1;
    int H_out = (H_in - kernel_size + 2*pad) / stride + 1;
    int W_out = (W_in - kernel_size + 2*pad) / stride + 1;
    //build  input
    for(int i=0; i<bs; i++){
        bs_in[i].data = {1,1,1,2,2,2,3,3,3,  10,10,10,20,20,20,30,30,30};
        bs_in[i].diff = {1,0,0,0,0,0,0,0,-1,  1,  1,2,  0,0,0, 0,0,0};
        bs_in[i].shape= {C_in, H_in, W_in};
    }
    //build kernel 
    kernel.data= {1,1,1,1, 2,2,2,2,  1,1,1,1,  2,2,2,2,  1,1,1,1,  2,2,2,2};
    kernel.diff= {0,0,0,0, -1,2,1,0, 0,0,0,0,  1,1,1,0,  0,0,0,0,  0,0,1,0};
    kernel.shape={C_out, C_in, kernel_size, kernel_size};
    //init output
    for(int i=0; i<bs; i++){
        bs_out[i].shape = {C_out, H_out, W_out};
        bs_out[i].data.resize(C_out*H_out*W_out);
        bs_out[i].diff = {1,0,1,2,  1,0,0,1,  0,3,0,1};
    }
}


void get_softmax_test_data(vector<MD_Vec<double>> &logits, vector<MD_Vec<double>> &probs, vector<MD_Vec<double>> &labels){
    //build  input
    int C_in_out = 3,   bs = 2;
    vector<vector<double>> logits_data = {{1, 3, 1},  {1,  2, 2}};
    vector<vector<double>> logits_diff = {{1, 1, 0},  {-1, 0, 2}};
    vector<vector<double>> probs_data = {{1, 0, 0},  {0,  1, 0}};
    vector<vector<double>> probs_diff = {{0, 2, 1},  {2,-1, 0}};
    for(int i=0; i<bs; i++){
        logits[i].data = logits_data[i];
        logits[i].diff = logits_diff[i]; 
        logits[i].shape= {C_in_out};
    }
    //init output
    for(int i=0; i<bs; i++){
        probs[i].data = probs_data[i];
        probs[i].diff = probs_diff[i];
        probs[i].shape= {C_in_out};
    }


    for(int i=0; i<bs; i++){
        labels[i].data = probs_data[i];
        labels[i].diff = probs_diff[i];
        labels[i].shape= {C_in_out};
    }
}




void test_mat_mul_run_time(){
    int row_A   =  300;
    int col_B   =  500;
    int col_A   =  300;
    int size_A  =  row_A*col_A;
    int size_B  =  col_A*col_B;
    int size_C  =  row_A*col_B;
    cout<<"row_A,col_B,col_A = "<<row_A<<","<<col_B<<","<<col_A<<endl;
    //double A[row_A*col_A];
    //double B[col_A*col_B];
    //double C[row_A*col_B];
    //static double A[size_A];
    //static double B[size_B];
    //static double C[size_C];
    vector<double> vec_A(size_A);
    vector<double> vec_B(size_B);
    vector<double> vec_C(size_C);

    double * A = &vec_A[0];
    double * B = &vec_B[0];
    double * C = &vec_C[0];


    clock_t start = clock();
    get_rand_c_array<double>(A, row_A*col_A);
    get_rand_c_array<double>(B, col_A*col_B);
    //print_c_array(C, row_A*col_B);
    //fill_n(C, row_A*col_B, 0);
    //print_c_array(C, row_A*col_B);
    //cout<<"------start mat_mul"<<endl;
    start = clock();
    mat_mul_use_cblas<double> (A, B, C, row_A, col_B, col_A);
    print_time_using(start, "mat_mul_use_cblas using time = ");
    if(size_A < 50) print_c_array(C, row_A*col_B);
    //print_c_array(C, row_A*col_B);


    start = clock();
    mat_mul_self_implement_1<double>(A, B, C, row_A, col_B, col_A);
    print_time_using(start, "mat_mul_self_implement_1 using time = ");
    if(size_A < 50) print_c_array(C, row_A*col_B);
    //print_c_array(C, row_A*col_B);


    start = clock();
    mat_mul_self_implement_2<double>(A, B, C, row_A, col_B, col_A);
    print_time_using(start, "mat_mul_self_implement_2 using time = ");
    if(size_A < 50) print_c_array(C, row_A*col_B);
    //print_c_array(C, row_A*col_B);

}




void test_mat_mul(){
    int row_A   =  3;
    int col_B   =  3;
    int col_A   =  2;
    int size_A  =  row_A*col_A;
    int size_B  =  col_A*col_B;
    int size_C  =  row_A*col_B;

    vector<double> vec_A = {1,2,3,4,5,6};
    vector<double> vec_B = {0,1,2,3,4,5};
    vector<double> vec_C = {0,0,0,0,0,0,0,0,0};
    vector<double> expect_vec = {6,9,12,12,19,26,18,29,40};
    double * A = &vec_A[0],  * B = &vec_B[0],    * C = &vec_C[0];
    
    vec_C = {0,0,0,0,0,0,0,0,0};
    mat_mul_use_cblas<double> (A, B, C, row_A, col_B, col_A);
    CHECK_vector_equal_test_success(vec_C, expect_vec, "mat_mul_use_cblas");

    vec_C = {0,0,0,0,0,0,0,0,0};
    mat_mul_self_implement_1<double> (A, B, C, row_A, col_B, col_A);
    CHECK_vector_equal_test_success(vec_C, expect_vec, "mat_mul_self_implement_1");


    vec_C = {0,0,0,0,0,0,0,0,0};
    mat_mul_self_implement_2<double> (A, B, C, row_A, col_B, col_A);
    CHECK_vector_equal_test_success(vec_C, expect_vec, "mat_mul_self_implement_2");



    expect_vec = {2,8,14,4,18,32,6,28,50};
    vec_C = {0,0,0,0,0,0,0,0,0};
    mat_mul_use_cblas<double> (A, B, C, row_A, col_B, col_A,false,true);
    print_vec(vec_C);
    CHECK_vector_equal_test_success(vec_C, expect_vec, "mat_mul_use_cblas");



    expect_vec = {3,8,16,4,21,32,5,28,50};
    //vec_C = {0,0,0,0,0,0,0,0,0};
    vec_C = {1,0,2,0,3,0,-1,0,0};
    mat_mul_use_cblas<double> (A, B, C, row_A, col_B, col_A,false,true, 1.0);
    print_vec(vec_C);
    CHECK_vector_equal_test_success(vec_C, expect_vec, "mat_mul_use_cblas");

}





void test_vec_address(){
    int vec_1d[10]; get_rand_c_array(vec_1d, 10);
    print_c_array(vec_1d, 10);
    int *p = vec_1d;
    //  int address_int = &vec_1d[0];
    //  invalid conversion from ‘int*’ to ‘int’
    for(int i=0; i<10; i++){
        //cout<<"&vec_1d[i], vec_1d[i], p, *p = "<<&vec_1d[i]<<","<<vec_1d[i]<<";  "<<p<<","<<*p<<endl;
        CHECK_equal(&vec_1d[i], p, num2str(__LINE__));
        CHECK_equal(vec_1d[i], *p, num2str(__LINE__));
        CHECK_equal((&vec_1d[i])+1, p+1, num2str(__LINE__));
        //CHECK_equal(address_int, p, num2str(__LINE__));
        //address_int += 4;
        p++;
    }
    cout<<" function : "<<__FUNCTION__<<" success finished !!! "<<endl;
}




void test_load_txt_to_vector_string(){
    const char* txt = "./test_txt.txt";
    vector<string> vec_str;
    load_txt_to_vector_string(txt, vec_str);
    vector<string> expect_vec =  {"abcd efg", "--------------",  "0000000",  "12345"};

    CHECK_vector_equal_test_success(vec_str, expect_vec, __FUNCTION__);
}



void test_num2str(){
    int num_int = 100;
    string expect_str = "100";
    string s = num2str<int>(num_int);
    CHECK_equal(s, expect_str);


    float num_float = 10.98;
    expect_str = "10.98";
    s = num2str<float>(num_float);
    CHECK_equal(s, expect_str);
}


void test_putText_to_image(){
    //创建空白图用于绘制文字  
	cv::Mat image = cv::Mat::zeros(cv::Size(640, 480), CV_8UC3);  
	//设置蓝色背景  
	image.setTo(cv::Scalar(100, 0, 0));  
	//设置绘制文本的相关参数  
	vector<string> texts = {"Hello World!", "YES", "OK", "goupi  butong"};  
	//显示绘制解果  
    putText_to_image(texts,image);
	cv::imshow("image", image);
	cv::waitKey(1000);
    cv::destroyAllWindows();
}




void test_split_string(){
    string st = "abc#hello#ui#hello#mkl#00#helll#1";
    //string seq = "hello";
    string seq = "hello";
    vector<string> res = split_string(st, seq);
    vector<string> expect_vec = {"abc#","#ui#", "#mkl#00#helll#1"};
    CHECK_vector_equal_test_success(expect_vec, res, __FUNCTION__);
}



void test_img2col_by_kernelmat(){
    int C_in = 2,  H_in = 3, W_in = 3, stride = 1, kernel_size = 2;
    int H_out = (H_in - kernel_size) / stride + 1,      W_out = H_out;
    vector<int> vec3d = {1,1,1,2,2,2,3,3,3,10,10,10,20,20,20,30,30,30};//get_rand_vec(C_in * H_in * W_in);
    vector<int> vec2d(C_in * kernel_size * kernel_size * H_out * W_out, 0);
    img2col_by_kernelmat<int>(&vec3d[0], &vec2d[0], {C_in, H_in, W_in}, {C_in*kernel_size*kernel_size,  H_out*W_out}, kernel_size, stride);
    vector<int> expect_vec = {1,1,2,2,1,1,2,2,2,2,3,3,2,2,3,3,10,10,20,20,10,10,20,20,20,20,30,30,20,20,30,30};
    CHECK_vector_equal_test_success(expect_vec, vec2d, __FUNCTION__);
}






void test_col2img_by_kernelmat(){
    int C_in = 2,  H_in = 3, W_in = 3, stride = 1, kernel_size = 2;
    int H_out = (H_in - kernel_size) / stride + 1,      W_out = H_out;
    vector<int> vec3d = {1,1,1,2,2,2,3,3,3,10,10,10,20,20,20,30,30,30};
    //get_rand_vec(C_in * H_in * W_in);
    vector<int> vec2d(C_in * kernel_size * kernel_size * H_out * W_out, 0);
    img2col_by_kernelmat<int>(&vec3d[0], &vec2d[0], {C_in, H_in, W_in}, {C_in*kernel_size*kernel_size,  H_out*W_out}, kernel_size, stride);
    vector<int> expect_vec = {1,1,2,2,1,1,2,2,2,2,3,3,2,2,3,3,10,10,20,20,10,10,20,20,20,20,30,30,20,20,30,30};
    CHECK_vector_equal(expect_vec, vec2d);


    vector<int> new_vec3d(C_in* H_in *W_in);
    col2img_by_kernelmat(&new_vec3d[0], &vec2d[0], {C_in, H_in, W_in}, {C_in*kernel_size*kernel_size,  H_out*W_out}, kernel_size, stride);
    


    expect_vec = {1,2,1,4,8,4,3,6,3,10,20,10,40,80,40,30,60,30};
    print_vec_with_comment(new_vec3d, "new_vec3d =");
    CHECK_vector_equal_test_success(expect_vec, new_vec3d, __FUNCTION__);

}







void test_compute_conv2d_by_mat_mul(){
    int C_in = 2,  H_in = 3, W_in = 3, stride = 1, kernel_size = 2, C_out = 3, pad = 0, bs = 1;
    int H_out = (H_in - kernel_size) / stride + 1;
    int W_out = (W_in - kernel_size) / stride + 1;
    vector<MD_Vec<double> > bs_in(bs);
    MD_Vec<double> kernel({C_out, C_in, kernel_size, kernel_size});
    vector<MD_Vec<double> > bs_out(bs);
    get_conv_test_data(bs_in, bs_out, kernel);
    // expect_vec
    vector<double> expect_vec = { 126,126,210,210,126,126,210,210,126,126,210,210 };

    // start conv2d 
    compute_conv2d_by_mat_mul(bs_in,  bs_out, kernel, stride, pad);

    for(int i=0; i<bs; CHECK_vector_equal_test_success(expect_vec, bs_out[i++].data, __FUNCTION__));
}



void test_transpose_matrix(){

    vector<double> nums = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    vector<double> expect_vec = {1,3,5,7,9,11,13,15,2,4,6,8,10,12,14,16};
    //print_vec_with_comment(nums, "shape = {8,2}");
    transpose_matrix(nums, {8,2});

    CHECK_vector_equal_test_success(expect_vec, nums, __FUNCTION__);

}






void test_compute_conv2d_by_7_for(){
    int C_in = 2,  H_in = 3, W_in = 3, stride = 1, kernel_size = 2, C_out = 3, pad = 0, bs = 1;
    vector<MD_Vec<double> > bs_in(bs);
    vector<MD_Vec<double> > bs_out(bs);
    MD_Vec<double> kernel({C_out, C_in, kernel_size, kernel_size});
    get_conv_test_data(bs_in, bs_out, kernel);
    // expect_vec
    vector<double> expect_vec = { 126,126,210,210,126,126,210,210,126,126,210,210 };
    // start conv2d 
    compute_conv2d_by_7_for(bs_in,  bs_out, kernel, stride, pad);
    //CHECK_vector_equal(expect_vec, bs_out[0].data);
    //cout <<"    "<<__FUNCTION__<<"    success finished "<<endl;
    for(int i=0; i<bs; CHECK_vector_equal_test_success(expect_vec, bs_out[i++].data, __FUNCTION__));
}




void test_compute_conv2d_by_mat_mul_backward(){
    int C_in = 2,  H_in = 3, W_in = 3, stride = 1, kernel_size = 2, C_out = 3, pad = 0, bs = 1;
    int H_out = (H_in - kernel_size) / stride + 1;
    int W_out = (W_in - kernel_size) / stride + 1;
    //build  input
    vector<MD_Vec<double> > bs_in(bs);
    MD_Vec<double> kernel({C_out, C_in, kernel_size, kernel_size});
    vector<MD_Vec<double> > bs_out(bs);
    get_conv_test_data(bs_in, bs_out, kernel);
    // expect_vec
    vector<double> expect_vec_out_data = {126,126,210,210,126,126,210,210,126,126,210,210 };
    vector<double> expect_vec_out_diff = {1,0,1,2,  1,0,0,1,  0,3,0,1};
    //vector<double> expect_vec_inp_diff = {2,5,3,  3,10,7,  1,5,4, 4,10,6, 6,20,14, 2,10,8};
    vector<double> expect_vec_inp_diff = {3,5,3,  3,10,7,  1,5,3, 5,11,8, 6,20,14, 2,10,8};
    vector<double> expect_vec_ker_diff = {7,7,11,11,69,72,111,110, 3,3,5,5,31,31,51,50, 5,5,9,9,50,50,91,90};


    // start conv2d 

    compute_conv2d_by_mat_mul(bs_in,  bs_out, kernel, stride, pad);

    compute_conv2d_by_mat_mul_backward(bs_in,  bs_out, kernel, stride, pad);


    //  kernel.print(" kernel = "); 
    //  bs_in[0].print(" bs_in = "); 
    //  bs_out[0].print(" bs_out = "); 
    for(int i=0; i<bs; CHECK_vector_equal_test_success(expect_vec_out_data, bs_out[i++].data, num2str(__LINE__)));
    for(int i=0; i<bs; CHECK_vector_equal_test_success(expect_vec_out_diff, bs_out[i++].diff, num2str(__LINE__)));
    for(int i=0; i<bs; CHECK_vector_equal_test_success(expect_vec_inp_diff, bs_in[i++].diff, num2str(__LINE__)));
    for(int i=0; i<bs; CHECK_vector_equal_test_success(expect_vec_ker_diff, kernel.diff, __FUNCTION__), i++);
}





void test_math_RELU_forward_and_backward(){
    int BS = 1;
    vector<MD_Vec<double>> input(BS);
    input[0].data = {1,2,3,-4, -1, 0};
    input[0].diff = {0,1,0, 2, -1, 0};
    input[0].shape= {3,2};

    vector<double> expect_vec_inp_data = {1,2,3,0,0,0};
    vector<double> expect_vec_inp_diff = {0,1,0,0,0,0};
    vector<int> expect_vec_inp_shap = {3,2};
    
    math_RELU(input);
    math_RELU_backward(input);


    CHECK_vector_equal_test_success(expect_vec_inp_data, input[0].data, num2str(__LINE__));
    CHECK_vector_equal_test_success(expect_vec_inp_diff, input[0].diff, num2str(__LINE__));
    CHECK_vector_equal_test_success(expect_vec_inp_shap, input[0].shape, __FUNCTION__);
}








void test_compute_fc_by_mat_mul_forward_and_backward(){
    int BS = 1,  C_in = 4,   C_out = 2;
    cout<<num2str(__LINE__)<<endl;
    vector<MD_Vec<double>> bs_in(BS);
    for(int i=0; i<BS; i++){
        bs_in[i].data = {1, 0,2, 1};
        bs_in[i].diff = {1,-1,0, 2};
        bs_in[i].shape= {C_in};
    }

    cout<<num2str(__LINE__)<<endl;
    MD_Vec<double> kernel;
    kernel.data = {1,2,1,0,  2,0, 1,1};
    kernel.diff = {1,0,1,0,  0,0,-1,1};
    kernel.shape= {C_out, C_in};


    vector<MD_Vec<double>> bs_out(BS);
    for(int i=0; i<BS; i++){
        bs_out[i].data = {0, 2};
        bs_out[i].diff = {-1,9};
        bs_out[i].shape= {C_out};
    }
    // expect_vec
    vector<double> expect_bs_in_data  = bs_in[0].data;
    vector<double> expect_bs_in_diff  = {18,-3,8,11};
    vector<double> expect_bs_out_data = {3, 5};
    vector<double> expect_bs_out_diff = bs_out[0].diff;
    vector<double> expect_kernel_data = kernel.data;
    vector<double> expect_kernel_diff = {0,0,-1,-1,9,0,17,10};

    cout<<num2str(__LINE__)<<endl;
    // compute_fc_by_mat_mul
    compute_fc_by_mat_mul(bs_in, bs_out, kernel);
    compute_fc_by_mat_mul_backward(bs_in, bs_out, kernel);
   
    for(int i=0; i<BS; i++){
        CHECK_vector_equal_test_success(expect_bs_in_data,  bs_in[i].data,  num2str(__LINE__));
        CHECK_vector_equal_test_success(expect_bs_in_diff,  bs_in[i].diff,  num2str(__LINE__));
        CHECK_vector_equal_test_success(expect_bs_out_data, bs_out[i].data, num2str(__LINE__));
        CHECK_vector_equal_test_success(expect_bs_out_diff, bs_out[i].diff, num2str(__LINE__));
    }
    CHECK_vector_equal_test_success(expect_kernel_data, kernel.data,    num2str(__LINE__));
    CHECK_vector_equal_test_success(expect_kernel_diff, kernel.diff,    __FUNCTION__);
}








void test_compute_softmax_and_softmax_loss_forward_backward(){
    int C_in_out = 3, BS = 2;
    vector<MD_Vec<double>> logits(BS);
    vector<MD_Vec<double>> probs(BS);
    vector<MD_Vec<double>> labels(BS);
    get_softmax_test_data(logits, probs, labels);
    double loss = 18;

    vector<vector<double>> expect_probs_data  = {{0.10650698,  0.78698611,  0.10650698}, {0.15536238,  0.42231879,  0.42231879}};
    vector<vector<double>> expect_probs_diff(BS);       for(int i=0; i<BS; expect_probs_diff[i] = probs[i].diff, i++);
    vector<vector<double>> expect_logits_data(BS);      for(int i=0; i<BS; expect_logits_data[i] = logits[i].data, i++);
    vector<vector<double>> expect_logits_diff = {{-0.44674651,  0.39349306,  0.05325349},{0.07768119, -0.28884061,  0.21115939}};
    vector<vector<double>> expect_labels_data(BS);      for(int i=0; i<BS; expect_labels_data[i] = labels[i].data, i++);
    vector<vector<double>> expect_labels_diff(BS);      for(int i=0; i<BS; expect_labels_diff[i] = labels[i].diff, i++);
    double expect_loss = 1.5507697898355257;

    compute_softmax(logits, probs);
    compute_softmax_cross_entroy_loss(probs, labels, loss);
    compute_softmax_cross_entroy_loss_backward(logits, probs, labels);

    for(int i=0; i<BS; i++){
        CHECK_vector_equal_test_success_by_diff(expect_logits_data[i],  logits[i].data,  num2str(__LINE__));
        CHECK_vector_equal_test_success_by_diff(expect_logits_diff[i],  logits[i].diff,  num2str(__LINE__));

        CHECK_vector_equal_test_success_by_diff(expect_probs_data[i],  probs[i].data,  num2str(__LINE__));
        CHECK_vector_equal_test_success_by_diff(expect_probs_diff[i],  probs[i].diff,  num2str(__LINE__));

        CHECK_vector_equal_test_success_by_diff(expect_labels_data[i],  labels[i].data,  num2str(__LINE__));
        CHECK_vector_equal_test_success_by_diff(expect_labels_diff[i],  labels[i].diff,  num2str(__LINE__));
    }
    CHECK_vector_equal_test_success_by_diff(vector<double>{expect_loss,}, vector<double>{loss,}, __FUNCTION__);

}






int main(){
    test_CHECK_equal();
    test_get_type_str();
    test_compute_softmax_and_softmax_loss_forward_backward();
    test_compute_fc_by_mat_mul_forward_and_backward();
    test_math_RELU_forward_and_backward();
    test_compute_conv2d_by_mat_mul_backward();
    test_img2col_by_kernelmat();
    test_col2img_by_kernelmat();
    test_compute_conv2d_by_7_for();
    test_compute_conv2d_by_mat_mul();
    test_transpose_matrix();
    test_split_string();
    test_putText_to_image();
    test_num2str();
    test_load_txt_to_vector_string();
    test_mat_mul();
    test_vec_address();
    test_mat_mul_run_time();
}




