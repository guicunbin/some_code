from data import *
from utils import *
import tensorflow as tf
import numpy as np
gpu_options=tf.GPUOptions(per_process_gpu_memory_fraction=0.1)
sess_config=tf.ConfigProto(gpu_options=gpu_options)
#top_tf = tf.nn.conv2d(input=tf.cast(bottom,tf.float32), filter=tf.cast(weight,tf.float32), strides=[1,1,5,5], padding="VALID", data_format="NCHW")
top_tf = tf.transpose(tf.nn.conv2d(input=tf.transpose(tf.cast(bottom,tf.float32), [0,2,3,1]), filter=tf.cast(weight,tf.float32), strides=[1,5,5,1], padding="VALID", data_format="NHWC"), [0,3,1,2])
sess = tf.Session(config = sess_config)
top_tf_np = sess.run(top_tf)
print "tf ==>\n",top_tf_np
assert [1,2,3] == [1,2,3]
print "cpp =>\n",np.array(top);
assert np_array_equal(top_tf_np,np.array(top))

