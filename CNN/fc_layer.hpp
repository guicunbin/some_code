#include<vector>
#include"./LayerParameter.hpp"

template <typename Dtype>
class fc_layer_class
{
    //private:

    public:

        typedef Dtype value_type;
        MD_Vec<Dtype> weight_mat;
        MD_Vec<Dtype> bias_mat;

        int BS;
        int C_in;
        int C_out;


        fc_layer_class(const LayerParameter<Dtype>& param,  vector<MD_Vec<Dtype> > &bottom,  vector<MD_Vec<Dtype> > &top){
            BS = bottom.size();
       
            CHECK_less(0, BS);
            C_in  = bottom[0].shape[0];
            C_out = param.out_channels;


            // init top 
            int size_top = C_out;
            top.resize(BS);
            for(int i=0; i<BS; i++){
                top[i].shape = {C_out};
                top[i].data.resize(size_top, Dtype(0));
                top[i].diff.resize(size_top, Dtype(0));
            }


            weight_mat.shape = {C_out, C_in};
            weight_mat.data  = get_rand_vec<Dtype>(C_out * C_in);

            
            if(param.bias_term){
                throw_error("the fc with bias are not implement");
            }
        }


        void Forward(vector<MD_Vec<Dtype> > &bottom,  vector<MD_Vec<Dtype> > &top){
            compute_fc_by_mat_mul(bottom, top, weight_mat);
        }


        void Backward(vector<MD_Vec<Dtype> > &bottom,  vector<MD_Vec<Dtype> > &top){
            compute_fc_by_mat_mul_backward(bottom, top, weight_mat);
        }

};



