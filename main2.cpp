/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 20 May 2024 02:26:09 PM CST
 ************************************************************************/

#include <pai.h>


void usage(int max_no) {
    
    if (max_no >= 1) cout << "1 : DAN(单张)" << endl;
    if (max_no >= 2) cout << "2 : DUIZI(对子)" << endl;
    if (max_no >= 3) cout << "3 : SHUNZI(顺子)" << endl;
    if (max_no >= 4) cout << "4 : SANDAI(三带)" << endl;
    if (max_no >= 5) cout << "5 : ZHADAN(炸弹)" << endl;
    if (max_no >= 6) cout << "6 : WANGZHA(王炸)" << endl;
    if (max_no >= 7) cout << "7 : PASS(不要)" << endl;
    cout << "input : ";
    
    return ;
}


PAI *read_pai(int max_no = 7) {
    PAI *ret;
    int no, x, len;
    while (1) {
       usage(max_no);
       cin >> no;
       if (no > 7) continue; 
       switch (no) {
            case 1: {/*单带*/
                cin >> x;
                ret = new DAN(x);
            } break;
            case 2: {/*对子*/
                cin >> x;
                ret = new DUIZI(x);
            } break;
            case 3: {/*顺子*/
                cin >> x >> len;
                ret = new SHUNZI(x, len);
            } break;
            case 4: {/*三带*/
               cin >> x;
               PAI *dai = read_pai(2);
               ret = new SANDAI(x, dai);
            } break;
            case 5: {/*ZHADAN*/
                cin >> x;
                ret = new ZHADAN(x);
            } break;
           case 6: {
               ret = new WANGZHA();
           }  break;
           case 7: {
               ret = new PASS();
           } break;
        }
        break;
    }
  
    return ret;
}

int main() {
    int arr[MAX_N + 5] = {0};
    int x;
    while (cin >> x) {
        if (x == 0) break;
        arr[x] += 1;
    }
    
    PAI *pai = read_pai();
    
    vector<PAI *> temp = PAI::getLegalPai(arr, pai);/*获取合法的牌*/
    for (auto x : temp) {
        x->output() << endl;
    }

    return 0;
}
