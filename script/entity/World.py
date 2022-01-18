#!/usr/bin/env pytnon3

from Singleton import Singleton


class Npc(object):

    def __init__(self, id):
        self._name = ''
        self._age = 10
        self._tick_no = 0

    def update(self):
        self._tick_no += 1


class World(metaclass=Singleton):
    def __init__(self):
        self._npcs = {}
        self._tick_no = 0

    def init(self):
        for x in range(1, 100):
            self._npcs[x] = Npc(x)

    def get_npc_ids(self):
        return list(self._npcs.keys())

    def get_npc_by_id(self, npc_id):
        return self._npcs[npc_id] if npc_id in self._npcs else None

    def update(self):
        self._tick_no += 1
        # print("World update world_ptr:{}, cur_tick:{}, npc_cnt:{}".format(id(self), self._tick_no, len(self._npcs)))

        for npc in self._npcs.values():
            npc.update()

