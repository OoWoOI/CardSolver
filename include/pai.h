/*************************************************************************
	> File Name: pai.h
	> Author: 
	> Mail: 
	> Created Time: Mon 20 May 2024 02:26:39 PM CST
 ************************************************************************/

#ifndef _PAI_H
#define _PAI_H

#include <iostream>
#include <vector>
using namespace std;

#define MAX_N 18 

enum class PAI_TYPE {
    DAN_TYPE, /*单张*/
    DUIZI_TYPE,/*对子*/
    SHUNZI_TYPE,/*顺子*/
    SANDAI_TYPE,/*三带*/
    ZHADAN_TYPE,/*炸弹*/
    WANGZHA_TYPE,/*王炸*/
    PASS_TYPE/*不要*/
};


/*牌*/
class PAI {
public :
    PAI(PAI_TYPE type);
    static vector<PAI *> getPai(int *);
    static vector<PAI *> getLegalPai(int *, PAI *);
    static void output_arr(int *);//输出当前牌型情况
    virtual std::ostream &output() = 0;/*输出牌型*/
    virtual void take(int *) = 0;/*将当前牌型取出来*/
    virtual void back(int *) = 0;/*将当前牌放回*/
    virtual bool operator>(PAI *pre) = 0;/*比较上一轮的牌大小*/

    virtual ~PAI() = default;
    
    PAI_TYPE __type;/*牌型*/
};

/*PASS*/
class PASS : public PAI {
public :
    PASS();
    std::ostream &output() override;
    bool operator>(PAI *) override;
    void take(int *) override;
    void back(int *) override;
    static vector<PAI *> get(int *arr);
};

/*单张*/
class DAN : public PAI {
public :
    DAN(int x);
    std::ostream &output() override;
    bool operator>(PAI *) override;
    void take(int *) override;
    void back(int *) override;
    static vector<PAI *> get(int *arr);
private :
    int __x;
};

/*对子*/
class DUIZI : public PAI {
public :
    DUIZI(int x);
    /*原始牌中所有的对子*/
    std::ostream &output() override;
    bool operator>(PAI *) override;
    void take(int *) override;
    void back(int *) override;
    /*获取所有对子牌型*/
    static vector<PAI *>get(int *arr);

private :
    int __x;
};

/*顺子*/
class SHUNZI : public PAI {
public :
    SHUNZI(int x, int len);
    std::ostream &output() override;
    bool operator>(PAI *) override;
    void take(int *) override;
    void back(int *) override;
    /*获取原始牌里的所有顺子*/
    static vector<PAI *>get(int *arr);
private :
    int __x, __len;
};


/*三带*/
class SANDAI : public PAI {
public :
    SANDAI(int x, PAI *dai);
    std::ostream &output() override;
    bool operator>(PAI *) override;
    void take(int *) override;
    void back(int *) override;
    static vector<PAI *>get(int *arr);
private :
    int __x;
    PAI *__dai;
};

/*炸弹*/
class ZHADAN : public PAI {
public :
    ZHADAN(int x);
    std::ostream &output() override;
    bool operator>(PAI *) override;
    void take(int *) override;
    void back(int *) override;
    static vector<PAI *>get(int *arr);
private :
    int __x;
};

/*王炸*/
class WANGZHA : public PAI {
public :
    WANGZHA();
    std::ostream &output() override;
    bool operator>(PAI *) override;
    void take(int *) override;
    void back(int *) override;
    static vector<PAI *>get(int *arr);
};


#endif
