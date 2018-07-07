#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Dec 12 11:20:26 2017

@author: petulaa
"""

import pandas as pd
import numpy as np
import sys


file_path = sys.argv[1]
host_ID = float(sys.argv[2])

locations = pd.read_csv(file_path, header=None, delim_whitespace=True, comment = '#', 
                        index_col = False, usecols = [0,3], engine = 'c',
                         names = ['ID','file'])

IDs = locations['ID'].values
files = locations['file'].values

entry = np.where(IDs == host_ID)[0][0]
tree_file = files[entry][0:-4]

print(tree_file)