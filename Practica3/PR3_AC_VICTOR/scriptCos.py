#!/usr/bin/env python
# -*- coding: utf-8 -*-
import os
dim = ["1000","1200","1500","2000"]
threads = ["2","4","8","16","32","64","128"]
resultado = open("./cos.txt", "w+")
f = file("./temps_cos_ordenat_de_1000_a_2000_i_de_2_a_128.txt")
cont = 0
for line in f:
	cont = cont+1
	if line.startswith("real"):
  		resultado.write(dim[cont/28]+" "+threads[(cont/4)%7]+" "+line.replace("real\t","").replace("m",":").replace("s",""))