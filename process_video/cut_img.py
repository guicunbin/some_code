import os
import fire
from multiprocessing.dummy import Pool as ThreadPool
from tqdm import tqdm
from urllib2 import urlopen
import random
import sys
import time



def now_time():
    return time.strftime("%Y_%m_%d_%H_%M_%S", time.localtime())


def print_with_time(st):
    if(type(st) == list):
        st = '\n'.join(st);
        st = str(now_time()) + "\n" + st
    else:
        st = "{} {}".format(now_time(), st)
    print(st)


def is_valid_url(url):
    is_valid = True;
    if(os.path.exists(url) and url.endswith('.mp4')):
        return True
    try:
        resp = urlopen(url, timeout=5)
    except:
        is_valid = False
    return is_valid



def cut(video_url_txt, save_path, start_line_idx=0, limit_num = 200000):
    lines       = [l.strip() for l in open(video_url_txt, 'r').readlines() if l.strip()]
    lines       = lines[start_line_idx : start_line_idx + limit_num]


    print("\n".join(lines[:5]))
    assert(is_valid_url(lines[0]))

    log         = "./ffmpeg.log"
    fps         = 1/1.0
    size        = "256*256"
#   cmd_tmp     = "ffmpeg -v quiet -vframes 20 -i {0} -r {1} -s {2} -q:v 2 -f image2 {3}/{4}__{5}__%05d.jpg >> {6}"
#   cmd_tmp     = "ffmpeg -v quiet -i {0} -vf fps={1} -s {2} {3}/{4}__{5}__%05d.jpg >> {6}"
#   cmd_tmp     = "ffmpeg -v quiet  -i {0} -r {1} -s {2} -q:v 2 -f image2 -vframes 1 {3}/{4}__{5}.jpg >> {6}"
#   cmd_tmp     = "ffmpeg -v quiet -i {0} -vf fps={1} -s {2} {3}/{4}__{5}__%06d.jpg >> {6}"
    cmd_tmp     = "ffmpeg -v quiet -i {0} -vf fps={1} -s {2} {3}/{4}__{5}__%06d.jpg"

    def map_func(url):
#       assert(is_valid_url(url))
#       cmd_cur = cmd_tmp.format(url, fps, size, save_path, now_time(), 
#                                   random.randint(100000,1000000), log)

        cmd_cur = cmd_tmp.format(url, fps, size, save_path, now_time(), 
                                    random.randint(100000,1000000))
        return cmd_cur

    
    num_thread  = 1
    idx         = 0;
#   cmd_list    = map(map_func, lines)
    while(True):
#       cmd_cur = " &\n".join(map(map_func, lines[idx : idx + num_thread]))
        cmd_cur = " \n".join(map(map_func, lines[idx : idx + num_thread]))
#       print(cmd_cur);     sys.exit();
        print(cmd_cur);
#       sys.exit();
        os.system(cmd_cur)

        if(idx >= len(lines)):
            break;
        print("process {}/{}".format(idx,len(lines)))
        idx    += num_thread



if __name__ == "__main__":
    fire.Fire(cut)



