#include<vector>
#include"./LayerParameter.hpp"
#include"../utils/utils.hpp"

template <typename Dtype>
class conv_layer_class
{
    //private:

    public:

        typedef Dtype value_type;
        typedef vector<vector<vector<vector<Dtype>>>> vec_4d;
        typedef vector<vector<vector<Dtype>>> vec_3d;
        typedef vector<vector<Dtype>> vec_2d;
        typedef vector<Dtype> vec_1d;
        LayerParameter<Dtype> param;
        vec_4d diff;
        vec_4d weight_mat;
        vec_1d bias_mat;


        conv_layer_class(const LayerParameter<Dtype>& pa){
            param = pa;
            if(!param.bias_term){
                weight_mat.resize(param.kernel_size, vec_3d(param.kernel_size, vec_2d(param.in_channels, vec_1d(param.out_channels, Dtype(1.0)))));
                gaussian_init_4dim_vector(weight_mat);
            }
            else{
                throw_error("the conv with bias are not implement");
            }
        }


        void Forward(vector<vec_3d>&bottom,vector<vec_3d>&top){
            int kernel_size = param.kernel_size;
            int stride = param.stride;
            int pad = param.pad;
            int bs  = bottom.size();
            int c_in= bottom[0].size();
            int w_in= bottom[0][0].size();
            int h_in= bottom[0][0][0].size();
            int c_out = param.out_channels;
            int h_out = (h_in - kernel_size)/stride + 1;
            int w_out = (w_in - kernel_size)/stride + 1;
            // top resize to real_shape and set to zero
            top.resize(bs, vec_3d(c_out, vec_2d(h_out, vec_1d(w_out, Dtype(0)))));
            // start to conv_compute
            for(int idx_bs = 0; idx_bs < bs; idx_bs++){
                for(int idx_c_out=0; idx_c_out < c_out; idx_c_out++){
                    for(int idx_c_in=0; idx_c_in < c_in; idx_c_in ++){

                        for(int idx_h_out=0; idx_h_out < h_out; idx_h_out ++){
                            for(int idx_w_out=0; idx_w_out < w_out; idx_w_out ++){
                                for(int idx_kh=0; idx_kh < kernel_size; idx_kh ++){
                                    for(int idx_kw=0; idx_kw < kernel_size; idx_kw ++){
                                        int idx_h_in = idx_kh + idx_h_out*stride,   idx_w_in = idx_kw + idx_w_out*stride;
                                        top[idx_bs][idx_c_out][idx_h_out][idx_w_out] += \
        bottom[idx_bs][idx_c_in][idx_h_in][idx_w_in] * weight_mat[idx_kh][idx_kw][idx_c_in][idx_c_out];
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        //void Backward(vector<vec_3d>&bottom,vector<vec_3d>&top);
};



