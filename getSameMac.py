#!/usr/bin/python
# -*- coding:utf-8 -*-
import sys
cmdArgv = sys.argv

def getMacList(s):
    fr = open(s,'r')#apnum0316_commercial

    mac = []
    for l in fr.readlines():
        l = l.strip('\n')
        l = l.split(',')
        mac.append(l[0])
    fr.close()
    return mac


if __name__=="__main__":
    #s1="~/Documents/data/bupt/apnum/commercial/apnum0316_commercial"
    s1="apnum0316"
    dict1 = getMacList(s1)
    s2="apnum0317"
    dict2 = getMacList(s2)
    s3="apnum0318"
    dict3 = getMacList(s3)
    s4="apnum0319"
    dict4 = getMacList(s4)
    s5="apnum0320"
    dict5 = getMacList(s5)
    s6="apnum0321"
    dict6 = getMacList(s6)
    s7="apnum0322"
    dict7 = getMacList(s7)

    a = set(dict3).intersection(set(dict1).intersection(set(dict2)))
    b = set(dict7).intersection(set(dict6).intersection(set(dict5)))
    c = set(dict4).intersection(a.intersection(b))

    fw = open('buptmac16_22','w')
    for k in c:
        fw.write(k+'\n')
    fw.close()
