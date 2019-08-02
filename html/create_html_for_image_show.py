import os
import fire
import image_utils
import subprocess




def create(image_root, show_port):
    tmp_file="./index.html"
    fw = open(tmp_file, 'w')
    image_utils.dfs_create_index_html(image_root, "", fw);
    fw.close();
    os.system('rm {}'.format(tmp_file))

    print("create success !!")
    cmd_str = "cd {} &&  python3 -m http.server {}".format(image_root, show_port);
    result = subprocess.check_output(cmd_str, shell=True)

#   os.system(cmd)
#   res = os.popen(cmd);
#   print(res.readlines());


fire.Fire(create)
