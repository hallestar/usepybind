#!/usr/bin/env pytnon3

from Singleton import Singleton


class Npc(object):

    def __init__(self, name, age):
        self._name = name
        self._age = age
        self._tick_no = 0

    def update(self):
        self._tick_no += 1


class World(metaclass=Singleton):
    def __init__(self):
        self._npcs = {}
        self._tick_no = 0

    def get_npc_by_id(self, npc_id):
        return self._npcs[npc_id] if npc_id in self._npcs else None

    def update(self):
        self._tick_no += 1
        print("World update world_ptr:{}, cur_tick:{}, npc_cnt:{}".format(id(self), self._tick_no, ))

        for npc in self._npcs.values():
            npc.update()

