import tensorflow as tf
import os
import numpy as np
os.environ['CUDA_VISIBLE_DEVICES'] = '0'
sess_config = tf.ConfigProto();
sess_config.gpu_options.per_process_gpu_memory_fraction = 0.01;

#bboxes = [
# [ 2,0,1,1, ] ,
# [ 2,0,0,1, ] ,
# [ 2,0.5,1,1, ] ,
# [ 2,0.5,1,1.5, ] ,
# [ 2,0.5,0,3, ] ,
# [ 2,0.6,0,4, ] ,
# [ 2,0.7,0,4.5, ] ,
# [ 3,1.1,0,5.6, ]]



bboxes = [\
 [ 21,10,12,12, ],
 [ 25,5,3,15, ],
 [ 27,5,10,15, ],
 [ 20,5,1,15, ],
 [ 21,15,1,30, ],
 [ 26,6,6,40, ],
 [ 24,7,3,35, ],
 [ 30,11,0,56, ],]



scores = [0.5,0.3,1,0.8,0.2,0.14,1,0.99,]

bboxes_tf = tf.cast(tf.convert_to_tensor(bboxes), tf.float32);
scores    = tf.cast(tf.convert_to_tensor(scores), tf.float32);
max_num   = 10;
IOU_min   = 0.1;
pickes    = tf.image.non_max_suppression(bboxes_tf, scores, max_num, IOU_min);
sess = tf.Session(config = sess_config);


for i in range(1):
    print np.array(bboxes)[sess.run(pickes)]
