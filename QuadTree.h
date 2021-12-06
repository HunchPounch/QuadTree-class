#pragma once
#include <iostream>
using namespace std;
#include "CArray.h"

class Point{
public:
    double x;
    double y;
    Point(){x = 0; y = 0;};
    Point(double x_, double y_){
        x=x_;
        y=y_;
    }
};


class Rectangle{
public:
    double x, y, w, h, a, b, a1, b1;
    Rectangle(){};
    Rectangle(double x_, double y_, double w_, double h_){x=x_;y=y_;w=w_;h=h_;a = x_;b = y_+h_;a1 = x_+w_;b1 = y_;}

    bool contain_point(Point p){
        return (p.x >= x && p.x < (x + w)) && (p.y >= y && p.y < (y + h));
    }
    bool inersect_Rectangle(Rectangle box){
        return (box.b < b1 || box.b1 > b || box.a1 < a || box.a > a1);
    }
};


class QuadNode{

private:
    void split();
public:

    QuadNode *NW;
    QuadNode *NE;
    QuadNode *SW;
    QuadNode *SE;

    Rectangle *bounds;
    Point *p;
    int Count;
    QuadNode(double x_, double y_, double w_, double h_);

    bool insert(Point point);
    bool isLeaf();
    bool SearchInNode(Point point);
    bool DeletePointInNode(Point point);
    CList GetRangeInNode(Rectangle neighborhood);
};

class Quadtree{

    QuadNode* root;
public:

    Quadtree(double x, double y, double w, double h){
        this->root = new QuadNode(x, y, w, h);
    }

    bool SearchInTree(Point point);
    bool InsertInTree(Point point);
    bool DeletePointInTree(Point point);
    CList GetRangeInTree(Rectangle neighborhood);
    int AmountOfPoints(Rectangle box);
};

