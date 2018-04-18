#include"./utils.hpp"
#define row_A  1000  //1000  // 5
#define col_B  1000  //1000  // 4
#define col_A  1000  //1000  // 2
#define size_A row_A*col_A
#define size_B col_A*col_B
#define size_C row_A*col_B


void test_mat_mul(){
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







void test_vec_address(){
    //  vector<int> shape = {3,3,2,2};
    //  vec_4df vec = get_4D_vec(shape);
    //  float *p_vec = &vec[0][0][0][0];
    //  for(int i0=0; i0<shape[0]; i0++){
    //      for(int i1=0; i1<shape[1]; i1++){
    //          for(int i2=0; i2<shape[2]; i2++){
    //              for(int i3=0; i3<shape[3]; i3++){
    //                  cout<<"vec["<<i0<<"]["<<i1<<"]["<<i2<<"]["<<i3<<"],  address  = "<<vec[i0][i1][i2][i3]<<", "<<&vec[i0][i1][i2][i3];
    //                  cout<<"===> *p_vec = "<<*p_vec<<endl;
    //                  p_vec ++;
    //              }
    //          }
    //      }
    //  }
    
    //vector<int> vec_1d = get_rand_vec(10);
    int vec_1d[10]; get_rand_c_array(vec_1d, 10);
    print_c_array(vec_1d, 10);
    int *p = vec_1d;
    for(int i=0; i<10; i++){
        cout<<"&vec_1d[i], vec_1d[i], p, *p = "<<&vec_1d[i]<<","<<vec_1d[i]<<";  "<<p<<","<<*p<<endl;
        p++;
    }
}








int main(){
    test_mat_mul();    
    //test_vec_address();
}




