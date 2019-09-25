import numpy as np
import cv2
import os
from tqdm import tqdm
import fire

def random_pixels():
    img     = np.random.uniform(0, 255, (256, 256, 3)).astype(np.uint8)
    return img


def random_same_pixels():
    img = [0,0,0]
    for i in range(3):
        pix    = int(np.random.uniform(0, 255, []).astype(np.uint8))
        img[i] = pix * np.ones((1, 256, 256))
    img = np.concatenate(img)
    img = np.transpose(img, (1,2,0))
    return img



def make(save_dir, num_image, is_need_show=False):
    os.system('mkdir -p {}'.format(save_dir))
    for i in tqdm(range(num_image)):
        i_str   = str(i).zfill(10)
        save_path_full = "{}/{}.jpg".format(save_dir, i_str)

        img = random_same_pixels();
        if is_need_show:
            cv2.imshow('img', img);
            cv2.waitKey(0);
        cv2.imwrite(save_path_full, img, [int(cv2.IMWRITE_PNG_COMPRESSION), 0])

    
if __name__ == "__main__":
    fire.Fire(make)
