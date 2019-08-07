#coding:utf-8
#!/usr/bin/env python

import time
import sys
import random
import os
import io
from PIL import Image
import base64
sys.path.append('./gen-py')
from common.ttypes import *

from common import common

import numpy as np
import cv2
from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol


def read_image_to_string(image_path):
#   decimg = cv2.imread(image_path)
    decimg = np.array(Image.open(image_path))
    return image_np_to_string(decimg)


def image_np_to_string(image_np):
	pil_img = Image.fromarray(image_np)
	buff = io.BytesIO()
	pil_img.save(buff, format="JPEG")
	new_image_string = base64.b64encode(buff.getvalue())#.decode("utf-8")
	return new_image_string


def string_to_image_np(base64_string):
    # Take in base64 string and return cv image
    imgdata = base64.b64decode(str(base64_string))
    image = Image.open(io.BytesIO(imgdata))
    decimg = cv2.cvtColor(np.array(image), cv2.COLOR_BGR2RGB)
    #  decimg  = imgdata
    return decimg

