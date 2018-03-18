#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""题目来源：http://hihocoder.com/problemset/problem/1014

#1014 : Trie树
时间限制:10000ms
单点时限:1000ms
内存限制:256MB

【描述】

小Hi和小Ho是一对好朋友，出生在信息化社会的他们对编程产生了莫大的兴趣，
他们约定好互相帮助，在编程的学习道路上一同前进。

这一天，他们遇到了一本词典，于是小Hi就向小Ho提出了那个经典的问题：“小
Ho，你能不能对于每一个我给出的字符串，都在这个词典里面找到以这个字符串
开头的所有单词呢？”

身经百战的小Ho答道：“怎么会不能呢！你每给我一个字符串，我就依次遍历词
典里的所有单词，检查你给我的字符串是不是这个单词的前缀不就是了？”

小Hi笑道：“你啊，还是太年轻了！~假设这本词典里有10万个单词，我询问你
一万次，你得要算到哪年哪月去？”

小Ho低头算了一算，看着那一堆堆的0，顿时感觉自己这辈子都要花在上面了...

小Hi看着小Ho的囧样，也是继续笑道：“让我来提高一下你的知识水平吧~你知
道树这样一种数据结构么？”

小Ho想了想，说道：“知道~它是一种基础的数据结构，就像这里说的一样！”

小Hi满意的点了点头，说道：“那你知道我怎么样用一棵树来表示整个词典么？”

小Ho摇摇头表示自己不清楚。

提示一：Trie树的建立

“你看，我们现在得到了这样一棵树，那么你看，如果我给你一个字符串ap，你
要怎么找到所有以ap开头的单词呢？”小Hi又开始考校小Ho。

“唔...一个个遍历所有的单词？”小Ho还是不忘自己最开始提出来的算法。

“笨！这棵树难道就白构建了！”小Hi教训完小Ho，继续道：“看好了！”

提示二：如何使用Trie树

提示三：在建立Trie树时同时进行统计！

“那么现在！赶紧去用代码实现吧！”小Hi如是说道

【输入】

输入的第一行为一个正整数n，表示词典的大小，其后n行，每一行一个单词（不
保证是英文单词，也有可能是火星文单词哦），单词由不超过10个的小写英文字
母组成，可能存在相同的单词，此时应将其视作不同的单词。接下来的一行为一
个正整数m，表示小Hi询问的次数，其后m行，每一行一个字符串，该字符串由不
超过10个的小写英文字母组成，表示小Hi的一个询问。

在20%的数据中n, m<=10，词典的字母表大小<=2.

在60%的数据中n, m<=1000，词典的字母表大小<=5.

在100%的数据中n, m<=100000，词典的字母表大小<=26.

本题按通过的数据量排名哦～

【输出】

对于小Hi的每一个询问，输出一个整数Ans,表示词典中以小Hi给出的字符串为前
缀的单词的个数。

【样例输入】

    5
    babaab
    babbbaaaa
    abba
    aaaaabaa
    babaababb
    5
    babb
    baabaaa
    bab
    bb
    bbabbaab

【样例输出】

    1
    0
    3
    0
    0

"""
gLetters=['a','b','c','d','e',
         'f','g','h','i','j',
         'k','l','m','n','o',
         'p','q','r','s','t',
         'u','v','w','x','y',
         'z']

gLength=len(gLetters)


class ChildrenOverflowError(Exception):
    """子节点数将超过最大字母表数量的异常.
    """
    def __init__(self):
        pass

    def __str__(self):
        return "Number of childs overflow"
    
class Node(object):
    """一个节点。
    """

    def __init__(self, key=None,count=1):
        self.__key = key
        self.__count = count
        self.__children = [None]*gLength
        self.__nchild = 0

    def key(self):
        return self.__key

    def count(self):
        return self.__count

    def increase_count(self):
        self.__count += 1
        return self.__count

    def child(self, letter):
        """获取key等于letter的子节点.若不存在则返回None.
        """
        for c in self.__children :
            if c != None and c.key() == letter:
                return c
        return None
        
    def insert_child(self, letter):
        """Insert a new child with the key of letter.
        """
        n = 0
        while n < len(self.__children):
            if self.__children[n] == None:
                self.__children[n] = Node(letter)
                break
            n += 1
        if n >= len(self.__children):
            raise ChildrenOverflowError()
        else:
            return self.__children[n]

    def __str__(self):
        return "%s:%d" % (self.__key, self.__count)
    
class Trie(object):
    """一棵Trie树.

    Trie树有一个树根节点，不含key。
    """

    def __init__(self):
        """构造一棵空树.
        """
        self.__root = Node()

    def insert(self, word):
        """把单词word插入到Trie树.
        """
        node=self.__root
        for letter in word:
            son = node.child(letter)
            if son == None:
                son = node.insert_child(letter)
                print('<inserted node> ', son)
            else:
                son.increase_count()
                print('<updated node>', son)
            node = son

    def count_prefix(self, word):
        """计算以word为前缀的单词数量.
        """
        node = self.__root
        for letter in word:
            son = node.child(letter)
            if son != None:
                cnt = son.count()
                node = son
            else:
                cnt = 0
                break
        return cnt
    
    def __str__(self):
        return "%s" % self.__root

class Data(object):
    
    def __init__(self, infile):
        with open(infile, 'r') as f:
            self.__lines = [ line.strip('\n\r') for line in f.readlines() ]
        self.__number_words = int(self.__lines[0])
        self.__number_queries = int(self.__lines[1 + self.__number_words])
    
    def words(self):
        """返回所有单词的列表.
        """
        return self.__lines[1:(self.__number_words+1)]

    def queries(self):
        """返回所有的查询字符串.
        """
        return self.__lines[(2+self.__number_words):]

if __name__ == '__main__':
    indata = Data('words.txt')
    print('Words: ', indata.words())
    print('Query: ', indata.queries())
    tree = Trie()
    for w in indata.words():
        tree.insert(w)
    for q in indata.queries():
        print(q, ': ', tree.count_prefix(q))
