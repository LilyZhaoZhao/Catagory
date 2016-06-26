#!/usr/bin/python
# -*- coding:utf-8 -*-
import sys
cmdArgv = sys.argv

def mac2num(s1,s2,s3):
    fr = open(s1,'r')#bupt_mac_no
    fr2 = open(s2,'r')#apnum0316
    fw = open(s3,'w')#0316

    no = {}
    for l in fr.readlines():
        l = l.strip('\n')
        l = l.split()
        mac = l[0]
        number = l[1]
        no[mac]=number
    fr.close()

    for line in fr2.readlines():
        line = line.strip('\n')
        l = line.split(',')
        mac = l[0]
        num = no[mac]
        fw.write(line+','+str(num)+'\n')

    fr2.close()
    fw.close()


if __name__=="__main__":
    mac2num(cmdArgv[1],cmdArgv[2],cmdArgv[3])
