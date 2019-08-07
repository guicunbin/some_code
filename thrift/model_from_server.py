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

from thrift_utils import *




class Model:
    def __init__(self, server_ip, server_port):
        try:
            transport = TSocket.TSocket(server_ip, server_port)
            self.transport = TTransport.TBufferedTransport(transport)
            protocol = TBinaryProtocol.TBinaryProtocol(self.transport)
            client = common.Client(protocol)
            self.model = client
            transport.open()
            print("sever -->  " + self.model.ping())
        except Thrift.TException, ex:
        	print "%s" % (ex.message)
        
        
    def __del__(self):
        self.transport.close()
        print(">> __del__ called ")    
        
    
    def test_from_path(self, image_path):
        image_string = read_image_to_string(image_path)
        res          = self.model.send(image_string)
        return res 

    def test(self, image_np):
        image_string = image_np_to_string(image_np)
        res          = self.model.send(image_string)
        return res

    def test_from_image_string(self, image_string):
        return self.model.send(image_string)

