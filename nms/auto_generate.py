#coding: utf-8
import os
import sys
from pyplusplus import module_builder

build_path="/home/guicunbin/workspace/some_code/examples/nms/wrapper_nms/"
mb = module_builder.module_builder_t(
         files=['./non_max_suppression.cpp'] #要需要封装的头文件
        ,gccxml_path='/home/guicunbin/dependency/gccxml/gccxml-build/bin/gccxml')

mb.build_code_creator( module_name='py_nms' ) 
#要生成的python模块的名称

mb.code_creator.user_defined_directories.append(build_path)

mb.write_module( "{}/chg_py.cc".format(build_path) )
#要生成的boost.python封装好的代码文件的名称
