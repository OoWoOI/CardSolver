/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 20 May 2024 05:48:10 PM CST
 ************************************************************************/

#include<iostream>
#include<pai.h>
#include<tree.h>
#include<stack>
using namespace std;

int b[MAX_N + 5] = {0};
int a[MAX_N + 5] = {0};


void read(FILE *fin, int *arr) {
    int x;
    while (fscanf(fin, "%d", &x) != EOF) {
        if (x == 0) break;
        arr[x] += 1;
    }
    return ;
}

void read_data() {
  
    FILE *fin = fopen("input.txt", "r");
    read(fin, a);
    read(fin, b);
    fclose(fin);  
    return ;
}


void output_arr(int *arr) {
    
    return ;
}

void output_solution(Node *root, int *a, int *b) {
    
    stack<Node *> s;
    s.push(root);

    while (!s.empty()) {
        printf("%s : ", s.size() % 2 ? "-->" : "  ");
        PAI::output_arr(a);
        printf("%s : ", s.size() % 2 ? "  " : "-->");
        PAI::output_arr(b);
        Node *node = s.top();
        int no;
        do {
            printf("[%3d] : back\n", -1);

            for (int i = 0; i < node->child.size(); i++) {
                printf("[%3d] : [%d]", i, node->child[i]->__win);
                node->child[i]->__p->output() << endl;
            }

            cout << "input : ";
            cin >> no;
            if (no >= -1 || no < node->child.size()) break;
           
        } while (1);

        if (no == -1) {
            s.pop();
            node->__p->back(s.size() % 2 ? a : b);
        } else {
            node->child[no]->__p->take(s.size() % 2 ? a : b);
            s.push(node->child[no]);
        }
    }
    
    return ;
}

int main() {
    read_data();
    cout << "read data done ......" << endl;
    Node *root = new Node();
    cout << "start analysis ......" << endl;
    getTree(root, a, b);
    cout << "analysis done ......" << endl;
    output_solution(root, a, b);
    return 0;
}

