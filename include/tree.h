/*************************************************************************
	> File Name: tree.h
	> Author: 
	> Mail: 
	> Created Time: Mon 20 May 2024 04:54:54 PM CST
 ************************************************************************/

#ifndef _TREE_H
#define _TREE_H

#include <vector>
#include <pai.h>

class Node {
public :
    Node();
    Node(PAI *, int);/*上一手牌的信息AND是否为必胜态*/
    int __win;/*必胜：1, 必败：0*/
    PAI *__p;
    vector<Node *> child;
};

void getTree(Node *, int *, int *);



#endif
