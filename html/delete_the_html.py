import os
import fire


def delete(root_path):
    for fil in os.listdir(root_path):
        fil_full = '{}/{}'.format(root_path, fil)
        if(fil == 'index.html'): 
            cmd = 'rm -rf {}'.format(fil_full)
            print(cmd)
            os.system(cmd)
        elif(os.path.isdir(fil_full)):
            delete(fil_full)



if __name__ == "__main__":
    fire.Fire(delete)
