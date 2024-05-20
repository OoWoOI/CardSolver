
#include <tree.h>
#include <pai.h>

Node::Node() : __p(new PASS()), __win(0) {}

Node::Node(PAI *p, int win = 0) : __p(p), __win(win) {}

static bool checkEmpty(int *arr) {
    for (int i = 3; i < MAX_N; i++) {
        if (arr[i]) return false;
    }
    return true;
}


void getTree(Node *root, int *a, int *b) {
    if (checkEmpty(b)) {
        root->__win = 0;
        return ;
    }
    vector<PAI *> temp = PAI::getLegalPai(a, root->__p);
    
    for (int i = 0; i < temp.size(); i++) {
        Node *node = new Node(temp[i], 0);
        temp[i]->take(a);
        getTree(node, b, a);/*交换出牌顺序*/
        temp[i]->back(a);
        root->child.push_back(node);/*添加node到子孩子中去*/
        if (node->__win == 0) root->__win = 1;/*将当前结点标记为必胜态*/
    }
    
    return ;
}
