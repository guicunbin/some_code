#include<vector>
#include"./LayerParameter.hpp"

template <typename Dtype>
class conv_layer_class
{
    //private:

    public:

        typedef Dtype value_type;
        MD_Vec<Dtype> weight_mat;
        MD_Vec<Dtype> bias_mat;

        int kernel_size;
        int stride;
        int pad;
        int BS;
        int C_in,  H_in,    W_in;
        int C_out, H_out,   W_out;


        conv_layer_class(const LayerParameter<Dtype>& param,  vector<MD_Vec<Dtype> > &bottom,  vector<MD_Vec<Dtype> > &top){
            kernel_size = param.kernel_size;
            stride = param.stride;
            pad = param.pad;
            BS = bottom.size();
       
            CHECK_less(0, BS);
            C_in  = bottom[0].shape[0];     H_in = bottom[0].shape[1];  W_in = bottom[0].shape[2];
            C_out = param.out_channels;
            H_out = (H_in - kernel_size + 2 * pad) / stride + 1;
            W_out = (W_in - kernel_size + 2 * pad) / stride + 1;


            // init top 
            int size_top = C_out * H_out * W_out;
            top.resize(BS);
            for(int i=0; i<BS; i++){
                top[i].shape = {C_out, H_out, W_out};
                top[i].data.resize(size_top, Dtype(0));
            }



            if(!param.bias_term){
                //weight_mat.resize(param.kernel_size,vec_3d(param.kernel_size,vec_2d(param.in_channels,vec_1d(param.out_channels, Dtype(1.0)))));
                weight_mat.shape = {C_out, C_in, kernel_size,  kernel_size};
                weight_mat.data  = get_rand_vec<Dtype>(C_out * C_in * kernel_size * kernel_size);

                //  bias_mat.shape = {C_out};
                //  bias_mat.data.resize(C_out, Dtype(0.0));
            }
            else{
                throw_error("the conv with bias are not implement");
            }
        }


        void Forward(vector<MD_Vec<Dtype> > &bottom,  vector<MD_Vec<Dtype> > &top){
            //compute_conv2d_by_7_for(bottom, top, weight_mat, stride, pad);
            compute_conv2d_by_mat_mul(bottom, top, weight_mat, stride, pad);
        }


        void Backward(vector<MD_Vec<Dtype>> &bottom,  vector<MD_Vec<Dtype> > &top){
            compute_conv2d_by_mat_mul_backward(bottom, top, weight_mat, stride, pad);
        }
};



