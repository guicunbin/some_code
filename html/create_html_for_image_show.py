import os
import fire
import image_utils
import subprocess
from tqdm import tqdm




def create(     image_root_or_list, 
                show_port, 
                exclude_string          ="!@#$^&%$%#@$%^&*&^%#@@!@#$#&&", 
                txt_line_old_path       ="/home/guicunbin.19/",
                txt_line_new_path       ="http://10.224.16.30:1111/"):
    if(os.path.isfile(image_root_or_list)):
        image_root_or_list = image_utils.create_index_html_from_txt(image_root_or_list,
                        txt_line_old_path,      txt_line_new_path);
    else:
#       tmp_file="./index.html"
#       fw = open(tmp_file, 'w')
#       image_utils.dfs_create_index_html(image_root_or_list, "", fw, exclude_string);
#       fw.close();
#       os.system('rm {}'.format(tmp_file))
        fw_lines  =[];
        image_utils.dfs_create_index_html(image_root_or_list, "", fw_lines, exclude_string);




    print(image_root_or_list)
    print("create success !!")
#   cmd_str = "cd {} &&  python3 -m http.server {}".format(image_root_or_list, show_port);
    cmd_str = "cd {} &&  python -m SimpleHTTPServer {}".format(image_root_or_list, show_port);
#   cmd_str = "cd {} &&  http-server ./ -p {}".format(image_root_or_list, show_port);

    result = subprocess.Popen(cmd_str, shell=True)
    try:
        while 1:
            pass
    except KeyboardInterrupt:
        result.kill()
        print('\n\n\n>  closed the show_port : {}\n\n\n\n'.format(show_port))
        



fire.Fire(create)
