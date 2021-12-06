#pragma once
#include <iostream>
using namespace std;

class CListNode{

public:
    double x;
    double y;

    CListNode *prev;
    CListNode *next;
    CListNode(){prev = next = NULL;}
};

class CList{

private:
    CListNode *cur;
    CListNode *Begin;
    CListNode *End;

public:
    CList();
    ~CList();
    CList(const CList &b);

    void SetZero();
    void Clean();
    void CopyOnly(CList b);
    void GoToBegin();
    void GoToEnd();
    int GetCur(double &x_, double &y_)const;
    int GoToNext();
    int GoToPrev();
    int IsEmpty ()const;
    void AddAfter(const double &x_,const double &y_);
    int DelCur();
    int getlen();

};
