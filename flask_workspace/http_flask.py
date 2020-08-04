#coding: utf-8
from flask import Flask
from flask import Flask, request, send_from_directory

import fire
app = Flask(__name__)
 




image_size= "19%"
html_line=\
          "<img src='img_path' alt='img_path' title='img_path' width='{0}' height='{0}'>\n".format(image_size)
image_path="./static/hill/11802008316_30acc73024_z.jpg"

##建立路由，通过路由可以执行其覆盖的方法，可以多个路由指向同一个方法。
@app.route('/index')
def index():
#   return "Hello,World!"
    return html_line.replace("img_path", image_path)


# path = "./static/home/guicunbin.19/workspace/c1_data/"
# 
# @app.route('/')
# def send_path(path):
#     return send_from_directory('js', path)


if __name__=='__main__':
#   app.run(host="0.0.0.0", port='6789', debug=False)
    app.run()


