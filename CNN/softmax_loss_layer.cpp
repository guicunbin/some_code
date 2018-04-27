#include<vector>
#include"./LayerParameter.hpp"

template <typename Dtype>
class softmax_loss_layer_class
{
    //private:
    public:

        typedef Dtype value_type;
        int BS;
        int C_in;
        vector<MD_Vec<Dtype> > probs_;


        softmax_loss_layer_class(const LayerParameter<Dtype>& param, vector<MD_Vec<Dtype>> &bottom_0, vector<MD_Vec<Dtype>>& bottom_1,    Dtype &top){
            // bottom_0:  logits;    bottom_1: labels
            BS = bottom.size();
            CHECK_less(0, BS);
            C_in  = bottom[0].shape[0];


            // init top 
            top = Dtype(0);
            // init probs_
            probs_.resize(BS);
            for(int i=0; i<BS; i++){
                probs_[i].shape = {C_in};
                probs_[i].data.resize(C_in, 0);
                probs_[i].diff.resize(C_in, 0);
            }
        }


        void Forward(vector<MD_Vec<Dtype>> &bottom_0,  vector<MD_Vec<Dtype>>&bottom_1,  Dtype &top){
            //from logits to probs_
            compute_softmax(bottom_0, probs_);
            //from probs_ and labels to loss;
            compute_softmax_cross_entroy_loss(probs_, bottom_1, top);
        }

        void Backward(vector<MD_Vec<Dtype>> &bottom_0,  vector<MD_Vec<Dtype>>&bottom_1){
            compute_softmax_cross_entroy_loss_backward(bottom_0, probs_, bottom_1);
        }
};



