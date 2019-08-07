#coding:utf-8
#!/usr/bin/env python

import time
import sys
import random
import os
from PIL import Image
import numpy as np
import cv2
from thrift_utils import *
import model_from_server

image_path_root = "./test_jpgs/"
image_path_list  = ["{}/{}".format(image_path_root, v) for v in os.listdir(image_path_root)]
random.shuffle(image_path_list)
#server_ip, server_port = ('10.108.248.248', 12345)
server_ip, server_port = ('10.95.45.117', 12345)
myModel = model_from_server.Model(server_ip, server_port)

while(1):
    total_cnt = 100
    size_list = [[100,100,3], [200, 200, 3], [400,400,3], [600,600,3], [600,1200,3], \
                 [1200,1200,3],  [2560, 2560, 3], [4800,4800,3]]
    for jdx in range(len(size_list)):
        #size_ = size_list[jdx]
        #print("testing size = " + str(size_))
        size_ = "from imgs"
        t_total = 0;
        random.shuffle(image_path_list)
        real_cnt = 0;
        for idx in range(total_cnt):
            #image_np    =   np.random.uniform(0, 255, size_).astype(np.uint8)
            image_np    =   cv2.imread(image_path_list[idx % len(image_path_list)])
            try:
                print("size = "+str(image_np.shape))
            except:
                continue
            image_string= image_np_to_string(image_np)
            t1          = time.time();
            result      = myModel.test_from_image_string(image_string)
            t_total    += time.time() - t1;
            real_cnt   += 1
        avg_time = (t_total*1000)/real_cnt
        print(">>  size = {}; each image time using  {} ms ".format(size_, round(avg_time, 3)));


