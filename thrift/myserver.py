#coding: utf-8
#!/usr/bin/env python

import socket
import sys
import base64
import io
import time
sys.path.append('./gen-py')

from common import common
from common.ttypes import *
import numpy as np
import cv2
from PIL import Image

from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol
from thrift.server import TServer
from thrift_utils import *



def process(image_np):
    cv2.namedWindow("Image");
    cv2.imshow("Image", image_np)
    cv2.waitKey(0)
    return "OK"



class commonHandler:

    def __init__(self):
        pass

    def ping(self):
        res_str =  "transport is  ok ! !"
        return res_str

    
    
    def send(self, image_string):
        """
        :param image_string
        :return: pred_id, probs
        """
        image_np = string_to_image_np(image_string)
        print(image_np.shape)
        result = process(image_np)
        return result




handler = commonHandler()

processor = common.Processor(handler)

#transport = TSocket.TServerSocket("localhost", 9090)
transport =  TSocket.TServerSocket(host="0.0.0.0", port=12345)
tfactory = TTransport.TBufferedTransportFactory()
pfactory = TBinaryProtocol.TBinaryProtocolFactory()

server = TServer.TSimpleServer(processor, transport, tfactory, pfactory)

print ("Starting thrift server in python...")
server.serve()
print ("done!")
