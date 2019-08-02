from tensorflow.python import pywrap_tensorflow
import os
import fire


def read(checkpoint_path):
    reader = pywrap_tensorflow.NewCheckpointReader(checkpoint_path)
    var_to_shape_map = reader.get_variable_to_shape_map()
    lines = [];
    for var_name in var_to_shape_map:
#        if ("/weights" in var_name) or  ("/biases" in var_name):
#            if ("/weights/" in var_name) or  ("/biases/" in var_name): continue;
            lines.append("{}:{}".format(var_name, reader.get_tensor(var_name).shape))
    lines.sort();

    for line in lines:
        print(line);


fire.Fire(read);
