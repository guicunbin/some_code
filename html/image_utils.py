import os
import sys
from string import Template
from tqdm import tqdm


img_suffix  = ('.jpg', '.png', '.jpeg', '.bmp')
#image_size  = "99%"
#image_size  = "49%"
image_size  = "19%"



html_line=\
"<img src='img_path' alt='img_path' title='img_path' width='{0}' height='{0}'>\n".format(image_size)

def dfs_create_index_html(image_path,  relative_path, fw, exclude_string="!@#$%^&*()<<!@#$^%&"):
   #print(exclude_string); sys.exit(">> debug");
   #print(exclude_string, relative_path);#  sys.exit(">> debug");
    if(exclude_string in relative_path):
        return;
    if(os.path.isdir(image_path)):
        print(image_path)
        cur_html = image_path + "/index.html"
        cur_fw = open(cur_html, 'w')
        for pa in os.listdir(image_path):
            dfs_create_index_html(image_path+"/"+pa, pa, cur_fw, exclude_string)
        cur_fw.close();
        if(len(open(cur_html, 'r').readlines()) == 0):
            os.system('rm {}'.format(cur_html))
    else:
        if(image_path.endswith(img_suffix)):
            fw.write(html_line.replace("img_path", relative_path));





def create_index_html_from_txt(image_list_txt):
    root_path_ = "/home/html_tmp/"
    root_path  = "{}/{}".format(root_path_, image_list_txt.split('/')[-1].split(".txt")[0])
#   os.system('sudo mkdir -p {0}; cp {1} {0}'.format(root_path, image_list_txt))
    cmd        = 'sudo mkdir -p {0};'.format(root_path)
    print(cmd)
    os.system(cmd)
#   print(root_path)
    image_lines = [ l.strip().split() for l in open(image_list_txt, 'r').readlines()]
    image_lines.sort();

    # create dir
    dir_set = list(set([l[1] for l in image_lines]));
    dir_set.sort();
    for d in tqdm(dir_set):
        cur_path    = "{}/{}".format(root_path, d)
        os.system("sudo mkdir -p {}".format(cur_path))
        html_lines  =   [ html_line.replace('img_path', l[0].replace("/home/guicunbin.19/", 'http://10.224.16.30:1111/')) for l in image_lines if l[1] == d]
        index_html  =   "{}/index.html".format(cur_path);
        with open(index_html, 'w') as fw:
            fw.writelines(html_lines)
    return root_path_

