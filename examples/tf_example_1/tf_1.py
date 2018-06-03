import tensorflow as tf
import sys
sys.path.append("/home/guicunbin/workspace/some_code/utils/")
from tf_utils import *

sess = tf.Session(config = sess_config)
num_dim = 2;


bottom = tf.random_uniform(shape=[2,32,32,3], dtype = tf.float32);
input_shape = tf.shape(bottom)
to_caffe = tf.transpose(bottom, [0, 3, 1, 2])
#reshaped_shape = tf.concat(axis=0, values=[[1, num_dim, -1], [input_shape[2]]])
#reshaped_shape = [1, num_dim, -1, bottom.get_shape().as_list()[2]]
reshaped_shape = [1, num_dim, -1, input_shape[2]]
reshaped = tf.reshape(to_caffe,reshaped_shape)
to_tf = tf.transpose(reshaped, [0, 2, 3, 1])

#print sess.run(reshaped_shape)
print reshaped_shape
print sess.run(tf.shape(reshaped))
