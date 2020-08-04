import fire
import os

def zip_txt(txt_path, zip_name):
    tmp_txt = "./tmp.txt"
    assert(not os.path.exists(tmp_txt))
    lines = open(txt_path, 'r').readlines();
    lines = [l.strip().split()[0]+"\n" for l in lines if l.strip().split()[0]]
    open(tmp_txt, 'w').writelines(lines)
    
    zip_cmd = "cat {0} | zip -@ {1}.zip".format(tmp_txt, zip_name)


    os.system(zip_cmd)
    print("zip_name = {}.zip".format(zip_name))



if __name__ == "__main__":
    fire.Fire(zip_txt)


