/*************************************************************************
	> File Name: pai.cc
	> Author: 
	> Mail: 
	> Created Time: Mon 13 May 2024 10:55:11 PM CST
 ************************************************************************/

#include "../include/pai.h" 

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



static string name[MAX_N + 5] = {
    "", "", "", "3", "4", "5", "6", "7", "8", "9", "10",
    "J", "Q", "K", "A", "2", "joker", "JOKER" 
};

/*PAI*/
PAI::PAI(PAI_TYPE type) : __type(type) {}

PASS::PASS() : PAI(PAI_TYPE::PASS_TYPE) {}

/*PASS*/
std::ostream &PASS::output() {
    return cout << "PASS(不要)" ;
}

vector<PAI *> PASS::get(int *arr) {
        vector<PAI *> ret;
        ret.push_back(new PASS());
        return ret;
}

bool PASS::operator>(PAI *pre) {
    return pre->__type != PAI_TYPE::PASS_TYPE;
}

void PASS::take(int *arr) {return ;}

void PASS::back(int *arr) {return ;}


/*单张*/

DAN::DAN(int x) : PAI(PAI_TYPE::DAN_TYPE) , __x(x) {}

std::ostream &DAN::output() {
    cout << "DAN(单张) : " << name[__x];
    return cout;
}
    
vector<PAI *> DAN::get(int *arr) {
    vector<PAI *> ret; 
    for (int i = 3; i < MAX_N; i++) {
        if (arr[i] == 0) continue;
        ret.push_back(new DAN(i));
        
    }
    return ret;
}

void DAN::take(int *arr) { arr[this->__x] -= 1; }

void DAN::back(int *arr) { arr[this->__x] += 1; }

bool DAN::operator>(PAI *pre) {
    switch (pre->__type) {
        case PAI_TYPE::PASS_TYPE : return true;
        case PAI_TYPE::DAN_TYPE : {
            DAN *__pre = dynamic_cast<DAN *>(pre);
            return this->__x > __pre->__x;
        } break;
        default : return false;
    }    
    return false;
}


/*对子*/
DUIZI::DUIZI(int x) : PAI(PAI_TYPE::DUIZI_TYPE) , __x(x) {}
    
    /*原始牌中所有的对子*/
std::ostream &DUIZI::output() {
    cout << "DUIZI(对子) : " << name[__x];
    return cout;
}

bool DUIZI::operator>(PAI *pre) {
   switch (pre->__type) {
       case PAI_TYPE::PASS_TYPE : return true;
       case PAI_TYPE::DUIZI_TYPE : {
           DUIZI *__pre = dynamic_cast<DUIZI *>(pre);
           return this->__x > __pre->__x;
       } break;
       default : return false;
   }    
   return false;
}
   
/*获取所有对子牌型*/
vector<PAI *> DUIZI::get(int *arr) {
    vector<PAI *> ret;
    for (int i = 3; i < MAX_N; i++) {
        if (arr[i] < 2) continue;
        ret.push_back(new DUIZI(i));
    }
    return ret;
}

void DUIZI::take(int *arr) { arr[this->__x] -= 2; }

void DUIZI::back(int *arr) { arr[this->__x] += 2; }

/*顺子*/
SHUNZI::SHUNZI(int x, int len) : 
    PAI(PAI_TYPE::SHUNZI_TYPE) , 
    __x(x), 
    __len(len) 
    {

    }

std::ostream &SHUNZI::output() {
        cout << "SHUNZI(顺子) : ";
        for (int i = __x;  i < __x + __len; i++) {
            cout << name[i] + " ";
        }
        return cout;
}
    
    /*获取原始牌里的所有顺子*/
vector<PAI *> SHUNZI::get(int *arr) {
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

bool SHUNZI::operator>(PAI *pre) {
   switch (pre->__type) {
       case PAI_TYPE::PASS_TYPE : return true;
       case PAI_TYPE::SHUNZI_TYPE : {
           SHUNZI *__pre = dynamic_cast<SHUNZI *>(pre);
           if (this->__len != __pre->__len) return false;
           return this->__x > __pre->__x;
       } break;
       default : return false;
   }    
   return false;
}

void SHUNZI::take(int *arr) { 
    for (int i = __x; i < __x + __len; i++) { arr[i] -= 1;}
    return ;
}

void SHUNZI::back(int *arr) { 
    for (int i = __x; i < __x + __len; i++) {arr[i] += 1;}
    return ;
}

/*三带*/
SANDAI::SANDAI(int x, PAI *dai) :
    PAI(PAI_TYPE::SANDAI_TYPE),
    __x(x), 
    __dai(dai) 
    {
        
    }
    
std::ostream& SANDAI::output() {
    cout << "SAN(三) : " << name[__x] << " DAI(带) ";
    __dai->output();
    return cout;
}
    
vector<PAI *> SANDAI::get(int *arr) {
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

bool SANDAI::operator>(PAI *pre) {
   switch (pre->__type) {
       case PAI_TYPE::PASS_TYPE : return true;
       case PAI_TYPE::SANDAI_TYPE : {
           SANDAI *__pre = dynamic_cast<SANDAI *>(pre);
           if (__pre->__dai->__type != this->__dai->__type) return false;
           return this->__x > __pre->__x;
       } break;
       default : return false;
   }    
   return false;
}

void SANDAI::take(int *arr) {
    arr[this->__x] -= 3;
    this->__dai->take(arr);
    return ;
}

void SANDAI::back(int *arr) {
    arr[this->__x] += 3;
    this->__dai->back(arr);
    return ;
}

/*炸弹*/
ZHADAN::ZHADAN(int x) : PAI(PAI_TYPE::ZHADAN_TYPE), __x(x) {}

std::ostream &ZHADAN::output() {
    return cout << "ZHADAN(炸弹) : " << name[__x];
}

void ZHADAN::take(int *arr) {
    arr[this->__x] -= 4;
    return ;
}

void ZHADAN::back(int *arr) {
    arr[this->__x] += 4;
    return ;
}

vector<PAI *> ZHADAN::get(int *arr) {
    vector<PAI *> ret;
    for (int i = 3; i < MAX_N; i++) {
        if (arr[i] < 4) continue;
        ret.push_back(new ZHADAN(i));
    }
    return ret;
}

bool ZHADAN::operator>(PAI *pre) {
   switch (pre->__type) {
       case PAI_TYPE::WANGZHA_TYPE : return false;
       case PAI_TYPE::ZHADAN_TYPE : {
           ZHADAN *__pre = dynamic_cast<ZHADAN *>(pre);
           return this->__x > __pre->__x;
       } break;
       default : return true;
   }    
   return false;
}

/*王炸*/

WANGZHA::WANGZHA() : PAI(PAI_TYPE::WANGZHA_TYPE) {}

std::ostream& WANGZHA::output() {
    return cout << "WANGZHA(王炸)";
}

void WANGZHA::take(int *arr) {
    arr[16] -= 1;
    arr[17] -= 1;
    return ;
}

void WANGZHA::back(int *arr) {
    arr[16] += 1;
    arr[17] += 1;
    return;
}


vector<PAI *> WANGZHA::get(int *arr) {
    vector<PAI *> ret;
    if (arr[16] && arr[17]) {
        ret.push_back(new WANGZHA());
    }
    return ret;
}

bool WANGZHA::operator>(PAI *pre) {
   switch (pre->__type) {
       case PAI_TYPE::WANGZHA_TYPE : return false;
       default : return true;
   }    
   return false;
}


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

vector<PAI *> PAI::getLegalPai(int *arr, PAI *pai) {
    vector<PAI *> temp1 = getPai(arr);
    vector<PAI *> temp;

    for (auto x : temp1) {
        if (x->operator>(pai)) temp.push_back(x);
        else {
            delete x;   
        }
    }

    return temp;
}

void PAI::output_arr(int *arr) {
    
    for (int i = 3; i < MAX_N; i++) {
        if (arr[i] == 0) continue;
        cout << name[i] << "*" <<  arr[i] << " ";
    }
    cout << endl;
    return ;
}

