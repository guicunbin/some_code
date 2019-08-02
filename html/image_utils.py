import os
from string import Template

img_suffix  = ('.jpg', '.png', '.jpeg', '.bmp')
image_size  = "19%"

html_line=\
"<img src='img_path' alt='img_path' title='img_path' width='{0}' height='{0}'>\n".format(image_size)

def dfs_create_index_html(image_path,  relative_path, fw):
    if(os.path.isdir(image_path)):
        print(image_path)
        cur_html = image_path + "/index.html"
        cur_fw = open(cur_html, 'w')
        for pa in os.listdir(image_path):
            dfs_create_index_html(image_path+"/"+pa, pa, cur_fw)
        cur_fw.close();
        if(len(open(cur_html, 'r').readlines()) == 0):
            os.system('rm {}'.format(cur_html))
    else:
        if(image_path.endswith(img_suffix)):
            fw.write(html_line.replace("img_path", relative_path));

