#include "Quadtree.h"
#include "CArray.h"
#include <iostream>
using namespace std;



QuadNode::QuadNode(double x_, double y_, double w_, double h_){
    this->bounds = new Rectangle( x_,y_,w_,h_);
    this->p = NULL;
    this->NW = NULL;
    this->NE = NULL;
    this->SE = NULL;
    this->SW = NULL;
    Count = 0;
}

bool QuadNode::isLeaf(){return NW==NULL;}


bool QuadNode::insert(Point point){

    if(!this->bounds->contain_point(point)){
        return false;
    }

    if(isLeaf()){
        if (Count < 1){
            this->p = new Point[1];
            this->p[0] = point;
            Count++;
            return true;
        }
        split();
    }

    ///////////////////
    if(NW->insert(point)){
        return true;
    }

    if(NE->insert(point)){
        return true;
    }

    if(SW->insert(point)){
        return true;
    }

    if(SE->insert(point)){
        return true;
    }

    return false;

}


void QuadNode::split(){

    double x= bounds->x;
    double y= bounds->y;
    double w= bounds->w;
    double h= bounds->h;

    NW= new QuadNode( x , y , w/2 , h/2);
    NE= new QuadNode( x+w/2, y, w/2, h/2);
    SW= new QuadNode( x , y + h/2 ,w/2,h/2);
    SE= new QuadNode( x + w/2 , y + h/2 , w/2 , h/2);

    for(int i=0; i<1;i++){
        if(NW->insert(p[0])){
            break;
        }
        if(NE->insert(p[0])){
            break;
        }
        if(SW->insert(p[0])){
            break;
        }
        if(SE->insert(p[0])){
            break;
        }
    }
    this->Count = 0;
    delete[] this->p;
    this->p = NULL;
}

bool QuadNode::SearchInNode(Point point){
    if(!this->bounds->contain_point(point)){
        return false;
    }

    if(this->isLeaf() && this->p!=NULL){
        if(this->p[0].x == point.x && this->p[0].y == point.y){
            return true;
        }
        else{
            return false;
        }
    }
    if(this->isLeaf()&& this->p == NULL){
        return false;
    }


    if(this->NW->SearchInNode(point)){
        return true;
    }
     if(this->NE->SearchInNode(point)){
        return true;
    }
    if(this->SW->SearchInNode(point)){
        return true;
    }
    if(this->SE->SearchInNode(point)){
        return true;
    }

    return false;

}


bool Quadtree::SearchInTree(Point point){
    if(!this->root->bounds->contain_point(point)){
        return false;
    }

    if(this->root->isLeaf()&& this->root->p!=NULL){
        if(this->root->p[0].x == point.x && this->root->p[0].y == point.y){
            return true;
        }
        else{
            return false;
        }
    }
    if(this->root->isLeaf()&& this->root->p == NULL){
        return false;
    }

    if(this->root->NW->SearchInNode(point)){
        return true;
    }
    if(this->root->NE->SearchInNode(point)){
        return true;
    }
    if(this->root->SW->SearchInNode(point)){
        return true;
    }
    if(this->root->SE->SearchInNode(point)){
        return true;
    }

    return false;
}

bool Quadtree::InsertInTree(Point point){
    return this->root->insert(point);
}



bool QuadNode::DeletePointInNode(Point point){
     if(!this->bounds->contain_point(point)){
        return false;
     }

    if(this->isLeaf()&& this->p!=NULL){
        if(this->p[0].x == point.x && this->p[0].y == point.y){
            delete[] this->p;
            this->p = NULL;
            this->Count = 0;
            return true;
        }
        else{
            return false;
        }
    }
    if(this->isLeaf()){
        return false;
    }

    if(this->NW->DeletePointInNode(point)){
        return true;
    }
     if(this->NE->DeletePointInNode(point)){
        return true;
    }
    if(this->SW->DeletePointInNode(point)){
        return true;
    }
    if(this->SE->DeletePointInNode(point)){
        return true;
    }

    return false;
}





bool Quadtree::DeletePointInTree(Point point){
    if(!this->root->bounds->contain_point(point)){
        return false;
    }

    if(this->root->isLeaf()&& this->root->p!=NULL){
        if(this->root->p[0].x == point.x && this->root->p[0].y == point.y){
            delete[] this->root->p;
            this->root->p = NULL;
            this->root->Count = 0;
            return true;
        }
        else{
            return false;
        }
    }

    if(this->root->isLeaf()){
        return false;
    }

    if(this->root->NW->DeletePointInNode(point)){
        return true;
    }
    if(this->root->NE->DeletePointInNode(point)){
        return true;
    }
    if(this->root->SW->DeletePointInNode(point)){
        return true;
    }
    if(this->root->SE->DeletePointInNode(point)){
        return true;
    }

    return false;
}

CList QuadNode::GetRangeInNode(Rectangle neighborhood){
    CList ArrayForPoints;

    if(this->bounds->inersect_Rectangle(neighborhood)){
        return ArrayForPoints;
    }

    for(int i=0;i<this->Count;i++){
        if(neighborhood.contain_point(this->p[0])){
            ArrayForPoints.AddAfter(this->p[0].x,this->p[0].y);
        }
    }
    if(this->isLeaf()){
        return ArrayForPoints;
    }

    ArrayForPoints.CopyOnly(this->NW->GetRangeInNode(neighborhood));
    ArrayForPoints.CopyOnly(this->NE->GetRangeInNode(neighborhood));
    ArrayForPoints.CopyOnly(this->SW->GetRangeInNode(neighborhood));
    ArrayForPoints.CopyOnly(this->SE->GetRangeInNode(neighborhood));

    return ArrayForPoints;
}





CList Quadtree::GetRangeInTree(Rectangle neighborhood){
    CList ArrayForPoints;

    if(this->root->bounds->inersect_Rectangle(neighborhood)){
        return ArrayForPoints;
    }

    for(int i=0;i<this->root->Count;i++){
        if(neighborhood.contain_point(this->root->p[0])){
            ArrayForPoints.AddAfter(this->root->p[0].x,this->root->p[0].y);
        }
    }
    if(this->root->isLeaf()){
        return ArrayForPoints;
    }

    ArrayForPoints.CopyOnly(this->root->NW->GetRangeInNode(neighborhood));
    ArrayForPoints.CopyOnly(this->root->NE->GetRangeInNode(neighborhood));
    ArrayForPoints.CopyOnly(this->root->SW->GetRangeInNode(neighborhood));
    ArrayForPoints.CopyOnly(this->root->SE->GetRangeInNode(neighborhood));

    return ArrayForPoints;
}


int Quadtree::AmountOfPoints(Rectangle box){
    CList l(this->GetRangeInTree(box));
    int n = 0;
    n = l.getlen();
    return n;
}

Quadtree::~Quadtree(){
    Point point;
    double x,y;
    CList l = this->root->GetRangeInNode(Rectangle(this->root->bounds->x,this->root->bounds->y,this->root->bounds->w,this->root->bounds->h));
    if(l.getlen() == 0){
        x=y;
    }
    else{
        l.GetCur(x,y);
        point.x = x;
        point.y = y;
        this->root->DeletePointInNode(point);
        while(l.GoToNext()==0){
            l.GetCur(x,y);
            point.x = x;
            point.y = y;
            this->root->DeletePointInNode(point);
        }
    }
    this->root->DeleteNode();

}


void QuadNode::DeleteNode(){

    if(this->isLeaf()){
        delete this->bounds;
        return;
    }

    if(this->NW->isLeaf()){
        delete this->NW->bounds;
        delete this->NE->bounds;
        delete this->SW->bounds;
        delete this->SE->bounds;
        delete this->NW;
        delete this->NE;
        delete this->SW;
        delete this->SE;
    }
    else{
        this->NW->DeleteNode();
        this->NE->DeleteNode();
        this->SW->DeleteNode();
        this->SE->DeleteNode();
    }

}
