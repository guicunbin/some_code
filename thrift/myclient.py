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

server_ip, server_port = ('10.95.45.117', 12345)
myModel = model_from_server.Model(server_ip, server_port)
while(1):
    image_path = "./test_jpgs/0000139.jpg"

    image_np    = cv2.imread(image_path)
    print("size = "+str(image_np.shape))

    image_string= image_np_to_string(image_np)
    result      = myModel.test_from_image_string(image_string)


