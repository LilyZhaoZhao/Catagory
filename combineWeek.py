#!/usr/bin/python
# -*- coding:utf-8 -*-
import sys
cmdArgv = sys.argv

def getDict(s):
    fr = open(s,'r')#apnum0316_commercial

    macDict = {}
    for l in fr.readlines():
        l = l.strip('\n')
        l = l.split(',')
        mac = l[0]
        conns24 = []
        for i in range(1,25):
            conns24.append(l[i])
        macDict[mac]=conns24
    fr.close()
    return macDict


if __name__=="__main__":
    #s1="~/Documents/data/bupt/apnum/commercial/apnum0316_commercial"
    s1="0316"
    dict1 = getDict(s1)
    s2="0317"
    dict2 = getDict(s2)
    s3="0318"
    dict3 = getDict(s3)
    s4="0319"
    dict4 = getDict(s4)
    s5="0320"
    dict5 = getDict(s5)
    s6="0321"
    dict6 = getDict(s6)
    s7="0322"
    dict7 = getDict(s7)

    a = set(dict3.keys()).intersection(set(dict1.keys()).intersection(set(dict2.keys())))
    b = set(dict7.keys()).intersection(set(dict6.keys()).intersection(set(dict5.keys())))
    c = set(dict4.keys()).intersection(a.intersection(b))

    fw = open('apnum16_22','w')
    for k in c:
        fw.write(k+' ')
        l = dict1[k]
        for i in range(24):
            fw.write(str(l[i])+',')
        l = dict2[k]
        for i in range(24):
            fw.write(str(l[i])+',')
        l = dict3[k]
        for i in range(24):
            fw.write(str(l[i])+',')
        l = dict4[k]
        for i in range(24):
            fw.write(str(l[i])+',')
        l = dict5[k]
        for i in range(24):
            fw.write(str(l[i])+',')
        l = dict6[k]
        for i in range(24):
            fw.write(str(l[i])+',')
        l = dict7[k]
        for i in range(23):
            fw.write(str(l[i])+',')
        fw.write(str(l[23])+'\n')
    fw.close()
