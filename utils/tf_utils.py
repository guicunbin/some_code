import tensorflow as tf
import os

per_gpu_fraction = 0.01;
gpuid = 0;


sess_config = tf.ConfigProto()
sess_config.gpu_options.per_process_gpu_memory_fraction = per_gpu_fraction
