#!/usr/bin/python

import itertools

'''
Print out the index of a string in it's permutation sequence
e.g. cab is 4 in abc, acb, bac, bca, cab, ...
e.g. babc is 3 in abbc, abcb, acbb, babc, ... (no duplication entries)
'''


def perm_string_idx(input):
  
    input_tuple = tuple(input)
    sorted_input = sorted(input)
    deduplicator = set([])
    perm_generator = itertools.permutations(sorted_input)
    ret = 0
    for iter in perm_generator:
        if input_tuple == iter:
            return ret
        if iter not in deduplicator:
            ret += 1
            deduplicator.add(iter)
