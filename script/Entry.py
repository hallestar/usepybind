try:
    import cPickle as pickle
except ImportError:
    import pickle
from entity.World import World


gr = World()


def init_world():
    World().init()


def update():
    gr.update()


def print_vector():
    import tester
    tester.print_list([1, 2, 3, 4])


def print_dict():
    import tester
    tester.print_dict({1: 2, 4: 5, 5: 1})


def python_call_cpp_print_list(nums):
    for n in nums:
        print(n, end=', ')
    print('\n')


def python_call_cpp_print_dict(num_dict):
    for k, v in num_dict.items():
        print('k:{}, v:{}'.format(k, v), end=', ')
    print('\n')


def change_npc_property():
    from tester import CNpc

    p = CNpc("hallestar", 18)
    p.set_level(20)
    return pickle.dumps(p, 2)


def load_npc_from_bytes(data):
    npc = pickle.loads(data)
    print("Npc", npc)
