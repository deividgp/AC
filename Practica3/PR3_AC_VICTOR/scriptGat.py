#!/usr/bin/env python
# -*- coding: utf-8 -*-

import glob
import os
from itertools import groupby

path = "/mnt/c/Users/Victor/Desktop/test/"

result_gat = open(path+"gat.txt", "w")

def keyfunc(s):
  return [int(''.join(g)) if k else ''.join(g) for k, g in groupby(s, str.isdigit)]
        
def get_time_gat(filename):
  with open(filename) as file:
    file = open(filename)
    for line in file:
      if "elapsed" in line:
        return line.split(" ")[2].replace('elapsed','')+"\n"

def clean_file_name(name):
  return name.replace('mxmVictor','').replace('.temps','')[::-1].replace('.',' ',1)[::-1].replace('.','')

os.chdir(path+"mxmVictor_gat")

files = sorted(glob.glob("*.temps"), key=keyfunc)
for file in files:
  result_gat.write(clean_file_name(file)+" "+get_time_gat(file))

result_gat.close()