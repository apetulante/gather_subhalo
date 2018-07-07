# -*- coding: utf-8 -*-
"""
Created on Thu Jun 15 09:21:36 2017

@author: petulaa
"""

import numpy as np
import sys

#range of all trees between tree_startrange (tree_#_#_#) and tree_endrange (tree_#_#_#)

tree_startrange1 = int(sys.argv[1])
tree_startrange2 = int(sys.argv[2])
tree_startrange3 = int(sys.argv[3])

tree_endrange1 = int(sys.argv[4])
tree_endrange2 = int(sys.argv[5])
tree_endrange3 = int(sys.argv[6])

filename = 'tree_range_tree_%d_%d_%d_to_tree_%d_%d_%d.txt' %(tree_startrange1, tree_startrange2, tree_startrange3, tree_endrange1, tree_endrange2, tree_endrange3)

trees_to_loop = open(filename, 'w')

if tree_endrange1 == tree_startrange1:
    if tree_endrange2 == tree_startrange2:
        i = tree_startrange1
        j = tree_startrange2
        for k in range (tree_startrange3, tree_endrange3+1):
            tree = 'tree_%d_%d_%d' % (i, j, k)
            trees_to_loop.write(tree)
            trees_to_loop.write('\n')

if tree_endrange1 == tree_startrange1:
    if tree_endrange2 == tree_startrange2 + 1:
        i = tree_startrange1
        for j in range (tree_startrange2, tree_startrange2 + 1):
            for k in range (tree_startrange3, 11):
                tree = 'tree_%d_%d_%d' % (i, j, k)
                trees_to_loop.write(tree)
                trees_to_loop.write('\n')
        for j in range (tree_endrange2, tree_endrange2 + 1):
            for k in range (0, tree_endrange3 + 1):
                tree = 'tree_%d_%d_%d' % (i, j, k)
                trees_to_loop.write(tree)
                trees_to_loop.write('\n')
                
if tree_endrange1 == tree_startrange1:
    if tree_endrange2 > tree_startrange2 + 1:
        i = tree_startrange1
        for j in range (tree_startrange2, tree_startrange2 + 1):
            for k in range (tree_startrange3, 11):
                tree = 'tree_%d_%d_%d' % (i, j, k)
                trees_to_loop.write(tree)
                trees_to_loop.write('\n') 
        for j in range (tree_startrange2+1, tree_endrange2):
            for k in range (0,11):
                tree = 'tree_%d_%d_%d' % (i, j, k)
                trees_to_loop.write(tree)
                trees_to_loop.write('\n')
        for j in range (tree_endrange2, tree_endrange2 + 1):
            for k in range (0, tree_endrange3 + 1):
                tree = 'tree_%d_%d_%d' % (i, j, k)
                trees_to_loop.write(tree)
                trees_to_loop.write('\n')

if tree_endrange1 == tree_startrange1 + 1:
    i = tree_startrange1
    j = tree_startrange2
    for k in range (tree_startrange3, 11):
        tree = 'tree_%d_%d_%d' % (i, j, k)
        trees_to_loop.write(tree)
        trees_to_loop.write('\n')
    for j in range (tree_startrange2 + 1, 11):
        for k in range (0, 11):
            tree = 'tree_%d_%d_%d' % (i, j, k)
            trees_to_loop.write(tree)
            trees_to_loop.write('\n')
    i=tree_endrange1
    for j in range (0, tree_endrange2):
        for k in range (0, 11):
            tree = 'tree_%d_%d_%d' % (i, j, k)
            trees_to_loop.write(tree)
            trees_to_loop.write('\n')
    for j in range (tree_endrange2, tree_endrange2 + 1):
        for k in range (0, tree_endrange3+1):
            tree = 'tree_%d_%d_%d' % (i, j, k)
            trees_to_loop.write(tree)
            trees_to_loop.write('\n')  
            
if tree_endrange1 > tree_startrange1 + 1:
    i = tree_startrange1
    j = tree_startrange2
    for k in range (tree_startrange3, 11):
        tree = 'tree_%d_%d_%d' % (i, j, k)
        trees_to_loop.write(tree)
        trees_to_loop.write('\n')
    for j in range (tree_startrange2 + 1, 11):
        for k in range (0, 11):
            tree = 'tree_%d_%d_%d' % (i, j, k)
            trees_to_loop.write(tree)
            trees_to_loop.write('\n')
    for i in range(tree_startrange1 + 1, tree_endrange1):
        for j in range(0,11):
            for k in range(0,11):
                tree = 'tree_%d_%d_%d' % (i, j, k)
                trees_to_loop.write(tree)
                trees_to_loop.write('\n')
    i=tree_endrange1
    for j in range (0, tree_endrange2):
        for k in range (0, 11):
            tree = 'tree_%d_%d_%d' % (i, j, k)
            trees_to_loop.write(tree)
            trees_to_loop.write('\n')
    for j in range (tree_endrange2, tree_endrange2 + 1):
        for k in range (0, tree_endrange3+1):
            tree = 'tree_%d_%d_%d' % (i, j, k)
            trees_to_loop.write(tree)
            trees_to_loop.write('\n') 
            
        
trees_to_loop.close()
