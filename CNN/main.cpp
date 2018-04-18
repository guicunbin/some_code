#include"./conv_layer.hpp"
#include"../utils/utils.hpp"
#include<cstdlib>


int main()
{
    // define bottom
    vec_4df bottom = get_4D_vec({1, 3, 16, 16});
    vec_4df top;

    // in_channels, out_channels, kernel_size, stride, pad, bias_term, lr_w, lr_b,filler::w, filler::b
    const LayerParameter<float> conv1_param(LayerType::conv, 3, 1, 5, 5, 0, false, 1, 0.1, filler::gaussian, filler::constant, 0.01, 0.0); 
    //conv1_param.print();

    conv_layer_class<float> conv1(conv1_param);

    //cout<<"exit()"<<endl; exit(0);

    //cout<<"start Forward  "<<endl;
    //clock_t start = clock();
    conv1.Forward(bottom, top);
    //print_time_using(start, "conv1.Forward using time = ");







    print_vec_4d(conv1.weight_mat, "weight = \\");

    print_vec_4d(bottom, "bottom = \\");
    
    print_vec_4d(top, "top = \\");

    return 0;
}

