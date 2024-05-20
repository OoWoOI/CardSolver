/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 13 May 2024 10:55:11 PM CST
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;


/*
 * (1)拿到原始牌的信息，枚举出所有出牌的可能性：
 *
 * 单张
 * 对子
 * 顺子
 * 双顺子
 * 三带
 * 飞机带翅膀
 * 四带
 * 四张炸弹
 * 双王炸
 * 不要pass
 *
 * */

/*
* (2)牌值 ： 
* ==> 3, 4, 5, 6, 7, 8 ,9 ,10, 11(J), 12(Q), 13(K), 14(A), 15(2), 16(小王), 17(大王)
*
* */


/*牌型枚举类*/
enum class PAI_TYPE {
    DAN, /*单张*/
    DUIZI, /*对子*/
    SHUNZI, /*顺子*/
    SANDAI, /*三带*/
    ZHADAN, /*炸弹*/
    WANGZHA, /*王炸*/
    PASS /*不要*/
};

#define MAX_N 18
string name[MAX_N + 5] = {
    "", "", "", "3", "4", "5", "6", "7", "8", "9", "10",
    "J", "Q", "K", "A", "2", "joker", "JOKER" 
};




/*牌*/
class PAI {

public :
    static vector<PAI *> getPai(int *);
    virtual std::ostream &output() = 0;/*输出牌型*/
    
};

/*PASS*/
class PASS : public PAI {
public :
    PASS() {}
    std::ostream &output() override {
        return cout << "pass" ;
    }
    static vector<PAI *> get(int *arr) {
        vector<PAI *> ret;
        ret.push_back(new PASS());
        return ret;
    }
};

/*单张*/
class DAN : public PAI {
public :

    DAN(int x) : __x(x) {}

    std::ostream &output() override {
        cout << "DAN(单张) : " << name[__x];
        return cout;
    }
    
    static vector<PAI *> get(int *arr) {
        vector<PAI *> ret; 
        for (int i = 3; i < MAX_N; i++) {
            if (arr[i] == 0) continue;
            ret.push_back(new DAN(i));
            
        }
        return ret;
    }

private :
    int __x;
};

/*对子*/
class DUIZI : public PAI {
public :
    DUIZI(int x) : __x(x) {}
    
    /*原始牌中所有的对子*/
    std::ostream &output() override {
        cout << "DUIZI(对子) : " << name[__x];
        return cout;
    }
    
    /*获取所有对子牌型*/
    static vector<PAI *>get(int *arr) {
        vector<PAI *> ret;
        for (int i = 3; i < MAX_N; i++) {
            if (arr[i] < 2) continue;
            ret.push_back(new DUIZI(i));
        }
        return ret;
    }

private :
    int __x;
};

/*顺子*/
class SHUNZI : public PAI {
public :
    
    SHUNZI(int x, int len) : __x(x), __len(len) {}

    std::ostream &output() override {
        cout << "SHUNZI(顺子) : ";
        for (int i = __x;  i < __x + __len; i++) {
            cout << name[i] + " ";
        }
        return cout;
    }
    
    /*获取原始牌里的所有顺子*/
    static vector<PAI *>get(int *arr) {
        vector<PAI *> ret;
        for (int l = 5; l <= 12; l++) {
            for (int i = 3, I = 14 - l + 1; i <= I; i++) {
                int flag = 1;
                for (int j = i; j < i + l; j++) {
                    if (arr[j] > 0) continue;
                    flag = 0;
                    break;
                }
                if (flag == 1) ret.push_back(new SHUNZI(i, l));
            }
        }
        return ret;
    }

private :
    int __x, __len;
};


/*三带*/
class SANDAI : public PAI {
public :
    
    SANDAI(int x, PAI *dai) : __x(x), __dai(dai) {}
    
    std::ostream &output() override {
        cout << "SAN(三) : " << name[__x] << " DAI(带) ";
        __dai->output();
        return cout;
    }
    
    static vector<PAI *>get(int *arr) {
        vector<PAI *>ret;
        for (int i = 3; i < MAX_N; i++) {
            if (arr[i] < 3) continue;
            /*三带空*/
            ret.push_back(new SANDAI(i, new PASS()));
            for (int j = 3; j < MAX_N; j++) {
                if (arr[j] == 0 || i == j) continue;
                ret.push_back(new SANDAI(i, new DAN(j)));
                if (arr[j] >= 2) {
                    ret.push_back(new SANDAI(i, new DUIZI(j)));
                }
                
            }
        }
        return ret;
    }
private :
    int __x;
    PAI *__dai;
};


class ZHADAN : public PAI {
public :
    ZHADAN(int x) : __x(x) {}
    std::ostream &output() override {
        return cout << "ZHADAN(炸弹) : " << name[__x];
    }

    static vector<PAI *>get(int *arr) {
        vector<PAI *> ret;
        for (int i = 3; i < MAX_N; i++) {
            if (arr[i] < 4) continue;
            ret.push_back(new ZHADAN(i));
        }
        return ret;
    }

private :
    int __x;
};

class WANGZHA : public PAI {
public :
    std::ostream &output() override {
        return cout << "WANG ZHA";
    }
    static vector<PAI *>get(int *arr) {
        vector<PAI *> ret;
        if (arr[16] && arr[17]) {
            ret.push_back(new WANGZHA());
        }
        return ret;
    }
};

vector<PAI *> PAI::getPai(int *arr) {
    vector<PAI *> temp1 = DAN::get(arr);
    vector<PAI *> temp2 = DUIZI::get(arr);
    vector<PAI *> temp3 = SHUNZI::get(arr);
    vector<PAI *> temp4 = SANDAI::get(arr);
    vector<PAI *> temp5 = ZHADAN::get(arr);
    vector<PAI *> temp6 = WANGZHA::get(arr);
    vector<PAI *> temp7 = PASS::get(arr);
    vector<PAI *> ret;
    for (auto x : temp1) ret.push_back(x);
    for (auto x : temp2) ret.push_back(x);
    for (auto x : temp3) ret.push_back(x);
    for (auto x : temp4) ret.push_back(x);
    for (auto x : temp5) ret.push_back(x);
    for (auto x : temp6) ret.push_back(x);
    for (auto x : temp7) ret.push_back(x);
    return ret;
}


int main() {
    #define MAX_N 18
    int arr[MAX_N + 5] = {0};
    int x;
    while (cin >> x) {
        if (x == 0) break;
        arr[x] += 1;
    }
    
    vector<PAI *> temp = PAI::getPai(arr);
    for (auto x : temp) {
        x->output() << endl;
    }
    return 0;
 }
