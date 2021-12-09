#include "test.h"
#include "Header.h"
#include "cstdlib"

int test1(){
    Quadtree Qtree(-100000,-100000,100000,100000);
    Point *arr = new Point[3000000];
     double x, y;
    for(int i=0;i<3000000; i++){
        arr[i].x = (double)rand();
        arr[i].y = (double)rand();
    }
    for(int i=0;i<3000000; i++){
        if(!Qtree.SearchInTree(arr[i])){
            Qtree.InsertInTree(arr[i]);

        }
        else{
            arr[i].x=1000000;
            arr[i].y=1000000;
        }
    };

    int k=0;
    for(int i=0;i<3000000; i++){
        if(arr[i].x <= 25000 && arr[i].x >= -25000 && arr[i].y <= 25000 && arr[i].y >= -25000){
            k++;
        }
    }
    Point *answer = new Point[k];
    int j =0;
    for(int i=0;i<3000000 && j<k; i++){
        if(arr[i].x <= 25000 && arr[i].x >= -25000 && arr[i].y <= 25000 && arr[i].y >= -25000){
            answer[j] = arr[i];
            j++;
        }
    }
    MergeSortXXX(answer, k);
    MergeSortYYY(answer, k);
    Rectangle Box(-25000,-25000,50000+0.000001, 50000+0.000001);
    CList l(Qtree.GetRangeInTree(Box));
    int n = l.getlen();
    l.GoToBegin();
    Point *arr1 = new Point[n];
    l.GetCur(x,y);
    arr1[0].x = x;
    arr1[0].y = y;
    int i=1;
    while(l.GoToNext()==0){
        l.GetCur(x,y);
        arr1[i].x = x;
        arr1[i].y = y;
        i++;
    }
    MergeSortXXX(arr1,n);
    MergeSortYYY(arr1,n);

    int c = 0;

    for(int i =0; i<n; i++){
        if(answer[i].x != arr1[i].x || answer[i].y != arr1[i].y){
            c++;
        }
    }
    delete[] answer;
    delete[] arr;
    delete[] arr1;
    if(c==0){
        cout << "test1 passed" << endl;
        return 0;
    }
    else {
        cout << "test1 not passed" << endl;
        return 1;
	}

}

int test2(){
    Quadtree Qtree(-500,-500,1000,1000);
    Point point1(1,1);
    Point point2(2,2);
    Qtree.InsertInTree(point1);
    Qtree.InsertInTree(point2);
    Qtree.DeletePointInTree(point1);
    Rectangle Box(-500,-500,1000,1000);
    int n = Qtree.AmountOfPoints(Box);
    if(n==1){
        cout << "test2 passed" << endl;
        return 0;
    }
    else {
        cout << "test2 not passed" << endl << endl;
        return 1;
	}

}


int main_test(){
    if(test1() + test2() == 0){
        return 0;
    }
    else return 1;
}

