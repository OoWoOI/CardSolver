/*************************************************************************
	> File Name: getStonePlay.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 19 May 2024 07:42:57 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;


bool __slove(int n, int flag) {
    if (n == 1 && flag == 0) return false;
    if (n == 2) return true;
    return __slove(n - 1, flag == 0) || __slove(n / 2, flag == 0);
}


bool slove(int n) {
    return __slove(n - 1, 0) || __slove(n / 2, 0);
}


int main() {
    
    int n;

    cin >> n; 

    //给定N值，A先取，问A的输赢?
    cout << (slove(n) ? "YES" : "NO") << endl;
    return 0;
}
