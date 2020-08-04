import os
import fire

def main(in_file):
    assert(not os.path.exists(in_file))


if __name__ == "__main__":
    fire.Fire(main)

