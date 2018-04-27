#include"./conv_layer.hpp"
#include"../utils/utils.hpp"
#include<cstdlib>


int main()
{
    // define bottom
    int BS = 64;
    vector<MD_Vec<double> > bottom(BS);
    for(int i=0; i<BS; i++){
        bottom[i].shape = {96, 56,  56};
        bottom[i].data = get_rand_vec<double>(bottom[0].shape[0] * bottom[0].shape[1] * bottom[0].shape[2]);
    }
    vector<MD_Vec<double> > top_conv1;
    vector<MD_Vec<double> > top_fc1;




    // LayerType, out_channels, kernel_size, stride, pad, bias_term, lr_w, lr_b,filler::w, filler::b, w_std, b_constant
    const LayerParameter<double> conv1_param(LayerType::conv, 3,  5,  5, 0, false, 1, 0.1, filler::gaussian, filler::constant, 0.01, 0.0); 
    const LayerParameter<double> fc1_param(LayerType::fc,   5, -1, -1, 0, false, 1, 0.1, filler::gaussian, filler::constant, 0.01, 0.0); 

    conv_layer_class<double> conv1(conv1_param, bottom, top_conv1);
    fc_layer_class<double> fc1(fc1_param, top_conv1, top_fc1);
    

    for(int i=0; i<1000; i++){
        conv1.Forward(bottom, top_conv1);
        fc1.Forward(top_conv1, top_fc1);
        
    }

    

    return 0;
}

