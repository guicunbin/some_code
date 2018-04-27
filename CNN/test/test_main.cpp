#include"../conv_layer.hpp"
#include"../../utils/utils.hpp"
#include<cstdlib>


int main()
{
    // define bottom
    //vec_4df bottom = get_4D_vec({1, 3, 16, 16});
    //vec_4df top;
    int BS = 1;
    vector<MD_Vec<double> > bottom(BS);
    bottom[0].shape = {3, 16, 16};
    bottom[0].data = get_rand_vec<double>(bottom[0].shape[0] * bottom[0].shape[1] * bottom[0].shape[2]);
    vector<MD_Vec<double> > top;

    // out_channels, kernel_size, stride, pad, bias_term, lr_w, lr_b,filler::w, filler::b
    const LayerParameter<double> conv1_param(LayerType::conv, 1, 5, 5, 0, false, 1, 0.1, filler::gaussian, filler::constant, 0.01, 0.0); 
    //conv1_param.print();

    conv_layer_class<double> conv1(conv1_param, bottom, top);

    //cout<<" exit()"<<endl; exit(0);

    //cout<<"start Forward  "<<endl;
    clock_t start = clock();
    conv1.Forward(bottom, top);
    //print_time_using(start, "conv1.Forward using time = ");


    print_vec(conv1.weight_mat.data,"weight = \\");

    print_vec(bottom[0].data,       "bottom = \\");
    
    print_vec(top[0].data,          "top = \\");

    return 0;
}

