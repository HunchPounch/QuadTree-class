#define _CRT_SECURE_NO_WARNINGS
#include "CArray.h"
#include <iostream>
using namespace std;

CList::CList(){
    this->SetZero();
}

void CList::SetZero(){
    this->cur = NULL;
    this->Begin = NULL;
    this->End = NULL;
}

CList::~CList(){
    this->Clean();
}

void CList::Clean(){
    this->GoToBegin();
    while(this->DelCur()==0);
    this->SetZero();
}

CList::CList(const CList &b){
    this->SetZero();
    CListNode *temp = b.Begin;
    while(temp!=NULL){
        this->AddAfter(temp->x,temp->y);
        temp = temp->next;
    }
    //this->CopyOnly(b);
}

void CList::GoToBegin(){
    this->cur = this->Begin;

}

void CList::GoToEnd(){
    this->cur = this->End;
}




void CList::CopyOnly(CList b){

    double x;
    double y;
    if(b.IsEmpty()==0){
        b.GoToBegin();
        do{
            b.GetCur(x, y);
            this->GoToEnd();
            this->AddAfter(x, y);
        }
        while(b.GoToNext()==0);
    }
}

int CList::GetCur(double &x_, double &y_)const{
    if(this->IsEmpty())return -1;
    x_ =  this->cur->x;
    y_ = this->cur->y;
    return 0;
}

int CList::GoToNext(){
    if(this->IsEmpty())return -1;
    if(this->cur->next==NULL)return -2;
    this->cur= this->cur->next;
    return 0;
}

int CList::GoToPrev(){
    if(this->IsEmpty())return -1;
    if(this->cur->prev==NULL)return -2;
    this->cur= this->cur->prev;
    return 0;
}

int CList::IsEmpty()const{
    return this->cur==NULL;
}

void CList::AddAfter(const double &x_,const double &y_){
    CListNode *n = new CListNode();
    n->x = x_;
    n->y = y_;
    if(this->IsEmpty()){
        this->cur=n;
        this->Begin=n;
        this->End=n;

    }
    else{
        n->next=this->cur->next;
        n->prev=this->cur;
        this->cur->next=n;
        if(n->next){
            n->next->prev=n;
        }
        else{
            this->End=n;
        }
    }
}

int CList::DelCur(){
    if(this->IsEmpty())return -1;

    if(this->cur->prev){
        this->cur->prev->next=this->cur->next;
    }
    else{
        this->Begin = this->cur->next;
    }

    if(this->cur->next){
        this->cur->next->prev=this->cur->prev;
    }
    else{
        this->End = this->cur->prev;
    }

    if(this->cur->prev){
        this->cur=this->cur->prev;
    }
    else{
        this->cur=this->cur->next;
    }
    return 0;

}

int CList::getlen(){
    this->GoToBegin();
    if(this->IsEmpty()){
        return 0;
    }
    int n = 0;
    while(this->cur->next!=NULL){
        n++;
        this->GoToNext();
    }
    return n+1;
}
