#include "Quadtree.h"
#include "Header.h"
void MergeXXX(Point *a,Point *Left,int l,Point *Right,int r) {
    int i = 0;
	int j = 0;
	int k =0;
	while(i<l && j< r) {
		if(Left[i].x  < Right[j].x) a[k++] = Left[i++];
		else a[k++] = Right[j++];
	}
	while(i < l) a[k++] = Left[i++];
	while(j < r) a[k++] = Right[j++];
}

void MergeSortXXX(Point *temp,int n) {
	Point* leftarr;
	Point* rightarr;
	int mid;
	if(n < 2){
        return;
	}
	mid = n/2;
	leftarr = new Point[mid];
	rightarr = new Point[n-mid];

	for(int i = 0;i<mid;i++){
        leftarr[i] = temp[i];
	}
	for(int i = mid;i<n;i++){
        rightarr[i-mid] = temp[i];
	}
	MergeSortXXX(leftarr,mid);
	MergeSortXXX(rightarr,n-mid);
	MergeXXX(temp,leftarr,mid,rightarr,n-mid);
    delete[] leftarr;
    delete[] rightarr;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void MergeYYY(Point *a,Point *Left,int l,Point *Right,int r){
    int i = 0;
	int j = 0;
	int k =0;
	while(i<l && j< r) {
       if(Left[i].x==Right[j].x){
            if((Left[i].y  < Right[j].y)) a[k++] = Left[i++];
            else a[k++] = Right[j++];
       }
       else{
        a[k++] = Left[i++];
        //f++;
        //if(!(f+i<l && f+j<r)){
        //    break;
        //}
       }
	}
	while(i < l) a[k++] = Left[i++];
	while(j < r) a[k++] = Right[j++];
}

void MergeSortYYY(Point *temp,int n){
	Point* leftarr;
	Point* rightarr;
	int mid;
	if(n < 2){
        return;
	}
	mid = n/2;
	leftarr = new Point[mid];
	rightarr = new Point[n-mid];

	for(int i = 0;i<mid;i++){
        leftarr[i] = temp[i];
	}
	for(int i = mid;i<n;i++){
        rightarr[i-mid] = temp[i];
	}
	MergeSortYYY(leftarr,mid);
	MergeSortYYY(rightarr,n-mid);
	MergeYYY(temp,leftarr,mid,rightarr,n-mid);
    delete[] leftarr;
    delete[] rightarr;
}



