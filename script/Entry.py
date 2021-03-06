try:
    import cPickle as pickle
except ImportError:
    import pickle
from entity.World import World


gworld = World()


test_var_for_export = 1


def empty_call():
    pass


def get_test_var_for_export():
    return test_var_for_export


def init_world():
    World().init()


def update():
    gworld.update()


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


def run_script(script_content):
    try:
        ll = locals()
        exec(script_content, globals(), ll)
    except Exception as e:
        print("exception, ", e)
        return None

    if 'r' in ll:
        return ll['r']

    return None
