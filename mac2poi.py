#!/usr/bin/python
# -*- coding:utf-8 -*-
import sys
cmdArgv = sys.argv

def getMacDict(s):
    fr = open(s,'r')#apnum16_22

    macDict = {}
    for l in fr.readlines():
        l = l.strip('\n')
        l = l.split(' ')
        macDict[l[0]] = l[1]
    fr.close()
    return macDict


if __name__=="__main__":
    #s1="~/Documents/data/bupt/apnum/commercial/apnum0316_commercial"
    s1="apnum16_22"
    dict1 = getMacDict(s1)

    no = {} #no[ssid]=clusterNo.
    fr3 = open('ssid16_22','r')
    for l in fr3.readlines():
        l = l.strip('\n')
        l = l.split(',')
        no[l[0]]=l[1]
    fr3.close()

    fr2 = open('buptpoi16_22','r')
    fw = open('apnumpoi16_22','w')
    for l in fr2.readlines():
        l = l.strip('\n')
        l = l.split('|')
        ssid = l[0]
        mac = l[1]
        lon = l[2]
        lat = l[3]
        if mac in dict1:
            fw.write(ssid+'|'+mac+'|'+dict1[mac]+','+lon+','+lat+','+str(no[ssid])+'\n')
    fw.close()
