import fire
import cv2
import os
from multiprocessing.dummy import Pool as ThreadPool
from tqdm import tqdm

img_suffix  = tuple(['.jpg', '.png', '.jpeg', '.bmp'])
size        = 256

def is_dir(p):
    return os.path.isdir(p);


def get_img_list(p):
    if(is_dir(p)):
        li = [];
        for p_sub in os.listdir(p):
            li +=  get_img_list("{}/{}".format(p, p_sub));
        return li;
    if(p.endswith(img_suffix)):
        return [p];
    return [None];


def resize_one(p):
    if(p and p.endswith(img_suffix)):
        img = cv2.imread(p);
        if (img.shape[:2] == (size, size)):
            return;
        img = cv2.resize(img, (size, size))
        cv2.imwrite(p, img);
    

def resize_main(p):
    li      = get_img_list(p)
    li      = [l for l in li if l]
    pool    = ThreadPool(16)
    pool.map(resize_one,  tqdm(li))
    pool.close()

    
if __name__ == "__main__":
    fire.Fire(resize_main);

