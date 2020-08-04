from multiprocessing.dummy import Pool as ThreadPool
import fire
import urllib
import sys
import os  
import tarfile  
from tqdm import tqdm
import time



def tar_dir(dir_, save_tar_name):
    assert(not os.path.exists(save_tar_name))
    tar = tarfile.open(save_tar_name,'w:gz')
    for root, d, files in tqdm(os.walk(dir_)):
        for fil in files:
            fullpath = os.path.join(root,fil)
            tar.add(fullpath)

    tar.close();



if __name__ == "__main__":
    fire.Fire(tar_dir)
                    


