import fire


class common_model:
    def __init__(self, a, b):
        self.a = a;
        self.b = b;


    def train(self):
        self.show();
        pass


    def test(self):
        self.show();
        pass


    def train_test(self):
        self.show();
        pass


    def show(self):
        print("\n\n")
        print(self);
        attrs = vars(self)
        print('\n'.join(">> %s: %s" % item for item in attrs.items()))
        print("\n\n")



if __name__ == "__main__":
    fire.Fire(common_model)
