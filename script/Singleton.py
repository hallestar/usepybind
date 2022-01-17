#!/usr/bin/env
# python3


class Singleton(type):
    _instances = {}

    def __call__(cls, *args, **kwargs):
        # print("in __call__", cls, *args, **kwargs)
        if cls not in Singleton._instances:
            inst = super(Singleton, cls).__call__(*args, **kwargs)
            Singleton._instances[cls] = inst
        else:
            inst = Singleton._instances[cls]
        return inst


if __name__ == '__main__':
    class A(metaclass=Singleton):

        def __init__(self, a, b):
            self.a = a
            self.b = b


    a = A(123123, 3456346)
    b = A(9999, 45555)
    print(a)
    print(b)
