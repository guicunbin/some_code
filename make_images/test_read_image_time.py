import jpeg4py
import os
import time
import cv2
import random
from tqdm import tqdm


test_image_root = "/home/guicunbin.19/workspace/c1_data/c1_data_256/baby/everphoto/"
test_images = ["{}/{}".format(test_image_root, f) for f in os.listdir(test_image_root)]
random.shuffle(test_images)

test_cnt    = 1000



start_time = time.time();
for idx in tqdm(range(test_cnt)):
    image_np = jpeg4py.JPEG(test_images[idx]).decode()
time_using = round((time.time() - start_time) * 1.0/ test_cnt, 3)
print("time_using = {} s/each".format(time_using))




start_time = time.time();
for idx in tqdm(range(test_cnt)):
    image_np = cv2.imread(test_images[idx])
time_using = round((time.time() - start_time) * 1.0/ test_cnt, 3)
print("time_using = {} s/each".format(time_using))



