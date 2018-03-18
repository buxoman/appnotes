#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
#1000 A + B


时间限制:1000ms
单点时限:1000ms
内存限制:256MB


描述

求两个整数A+B的和

输入

输入包含多组数据。
每组数据包含两个整数A(1 ≤ A ≤ 100)和B(1 ≤ B ≤ 100)。

输出

对于每组数据输出A+B的和。

样例输入

    1 2
    3 4

样例输出

    3
    7

Created on Sat Mar 10 21:26:09 2018

@author: buhongbo
"""

class Plus(object):
    
    def __init__(self, a, b):
        self.__a = int(a)
        self.__b = int(b)

    def __evaluate(self):
        return self.__a + self.__b
        
    def __str__(self):
        return '%d' % self.__evaluate()
    
    __repr__ = __str__
    
    
class Tester(object):
    
    def __init__(self, infile):
        self.__current = -1
        with open(infile, 'r') as f:
            self.__lines = f.readlines()
    
    def __iter__(self):
        return self
    
    def __next__(self):
        self.__current = self.__current + 1
        if self.__current == len(self.__lines):
            raise StopIteration()
        else:
            return self.__lines[self.__current].strip('\n\r').split()

def main():
    t = Tester('a_plus_b.txt')
    for a,b in t:
        print(Plus(a,b))
    
if __name__ == '__main__':
    main()