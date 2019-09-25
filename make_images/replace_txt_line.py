import os
import random
import fire


def main(in_txt, ou_txt, delete_line_by_str, add_dir, add_dir_label):
    assert(os.path.exists(add_dir));
    add_dir = os.path.abspath(add_dir)


    add_lines = ["{0}/{1} {2}\n".format(add_dir, f, add_dir_label) for f in os.listdir(add_dir) \
                            if ('.jpg' in f or '.png' in f)]
    print("len(add_lines) = {}".format(len(add_lines)))



    new_lines = open(in_txt, 'r').readlines();

    print("before delete len = {}".format(len(new_lines)))
    new_lines = [line for line in new_lines if delete_line_by_str not in line]
    print("after delete len = {}".format(len(new_lines)))


    new_lines.extend(add_lines)
    print("after  extend(add_lines) len = {}".format(len(new_lines)))
    print("before shuffle new_lines[-10:]= {}".format(new_lines[-10:]))
    random.shuffle(new_lines)
    print("after  shuffle new_lines[-10:]= {}".format(new_lines[-10:]))


    open(ou_txt, 'w').writelines(new_lines)


if __name__ == "__main__":
    fire.Fire(main)



