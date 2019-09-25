import numpy as np
import cv2
import os
from tqdm import tqdm
import fire



def show(save_dir):
    for i in tqdm(os.listdir(save_dir)):
        save_path_full = "{}/{}".format(save_dir, i)
        if(not os.path.isfile(save_path_full)): 
            continue;
        img     = cv2.imread(save_path_full)
        try:
            cv2.imshow('img', img);
        except:
            continue;
        cv2.waitKey(0);
    
if __name__ == "__main__":
    fire.Fire(show)

