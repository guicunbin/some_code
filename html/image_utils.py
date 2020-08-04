import os
import sys
from string import Template
from tqdm import tqdm


img_suffix  = ('.jpg', '.png', '.jpeg', '.bmp')
#image_size  = "99%"
#image_size  = "49%"
#image_size  = "49%"
#image_size  = "19%"
image_size  = "49%"
#image_size  = "33%"
#image_size  = "100%"




def sort_txt(txt):
    lines = open(txt, 'r').readlines();
    lines.sort();
    open(txt, 'w').writelines(lines)


html_line=\
"<img src='img_path' alt='img_path' title='img_path' width='{0}' height='{0}'>\n".format(image_size)

def dfs_create_index_html(image_path,  relative_path, fw, exclude_string="!@#$%^&*()<<!@#$^%&"):
    
    if(exclude_string in image_path):
        return;
    if(os.path.isdir(image_path)):
        print(image_path)
        cur_html= image_path + "/index.html"
#       cur_fw  = open(cur_html, 'w')
        cur_fw  = [];
        for pa in os.listdir(image_path):
           #if("2020-01-10-173836_16760" in pa):
           #    print(image_path, pa);
           #    sys.exit();
            dfs_create_index_html(image_path+"/"+pa, pa, cur_fw, exclude_string)
#       cur_fw.close();
#       sort_txt(cur_html)
#       if(len(open(cur_html, 'r').readlines()) == 0):
#           os.system('rm {}'.format(cur_html))
        if(len(cur_fw)!=0):
            cur_fw.sort();
            open(cur_html, 'w').writelines(cur_fw)
    else:
        if(image_path.endswith(img_suffix)):
#           fw.write(html_line.replace("img_path", relative_path));


           #if("2020-01-10-173836_16760" in relative_path):
           #    print(relative_path, html_line.replace("img_path", relative_path));
           #    sys.exit();


            fw.append(html_line.replace("img_path", relative_path));





def create_index_html_from_txt(image_list_txt, txt_line_old_path, txt_line_new_path):
    root_path_ = "/home/html_tmp/"
    root_path  = "{}/{}".format(root_path_, "_".join((image_list_txt.split('/')[-2:])))
#   os.system('sudo mkdir -p {0}; cp {1} {0}'.format(root_path, image_list_txt))
    cmd        = 'sudo mkdir -p {0};'.format(root_path)
    print(cmd)
    os.system(cmd)
#   print(root_path)
    image_lines = [ l.strip().split() for l in open(image_list_txt, 'r').readlines()]
    image_lines.sort();

    line_len    = len(image_lines[0])


    if(line_len == 2):
        # create dir
        dir_set = list(set([l[1] for l in image_lines]));
        dir_set.sort();
        for d in tqdm(dir_set):
            cur_path    = "{}/{}".format(root_path, d)
            os.system("sudo mkdir -p {}".format(cur_path))
            html_lines  =   [ html_line.replace('img_path', l[0].replace(txt_line_old_path,  txt_line_new_path)) for l in image_lines if l[1] == d]
            index_html  =   "{}/index.html".format(cur_path);
            print(index_html)
            with open(index_html, 'w') as fw:
                fw.writelines(html_lines)


    elif(line_len >= 3):
        # create dir
        print("line_len = ", line_len)
        dir_set     = list(set(["_".join(l[1:-1]) for l in image_lines]));
        dir_set.sort();
        dir_set_2   = list(set([l[-1] for l in image_lines]));
        dir_set_2.sort();
#       print("dir_set   = ", dir_set)
        print("dir_set_2 = ", dir_set_2)
        for d in tqdm(dir_set):
            for d_2 in tqdm(dir_set_2):
                cur_path    = "{}/{}/{}".format(root_path, d, d_2)
                print("d, d_2, cur_path = ", (d, d_2, cur_path))
                os.system("sudo mkdir -p {}".format(cur_path))
                html_lines  =   [ html_line.replace('img_path', l[0].replace(txt_line_old_path,  txt_line_new_path)) for l in image_lines if (l[1] == d and l[2] == d_2)]
                index_html  =   "{}/index.html".format(cur_path);
                print(index_html)
                with open(index_html, 'w') as fw:
                    fw.writelines(html_lines)







    return root_path_

