#include "Quadtree.h"
#include "Header.h"
#include "test.h"


int main(){

    if(main_test() == 1){
        cout << "tests not passed" << endl << endl;
        return 1;
    }

    Point point;
    Rectangle Box;
    double x,y,h,w;
    char file_name[256] = "";
    int mode = -1;
    int n = 0;
    cout << "Enter the initial rectangle for work:" << endl;
    cout << "Enter rectangle center coordinates:" << endl;
    cin >> x >> y;
    cout << "Enter the height of rectangle:" << endl;
    cin >> h;
    cout << "Enter the width of rectangle:" << endl;
    cin >> w;
    if(w<=0 || h <=0){
        cout << "incorrect input" << endl;
        return -1;
    }

    Rectangle iBox(x-w/2,y-h/2,w+0.0001,h+0.0001);
    Quadtree Qtree(x-w/2,y-h/2,w+0.0001,h+0.0001);
    while(1){
        cout <<endl << endl << "Select next number:" << endl;
        cout << "1 -- load points from file" << endl;
        cout << "2 -- Add point" << endl;
        cout << "3 -- Remove point" << endl;
        cout << "4 -- Get the number of points in the QuadTree" << endl;
        cout << "5 -- Get points out of range" << endl;
        cout << "6 -- Is the point contained in the tree?" << endl;
        cout << "7 -- Exit" << endl << endl;
        cin >> mode;

        if(mode == 1){
            cout << "Enter file name" << endl;
            cin >> file_name;
            ifstream fin(file_name);
            double x,y;
            if(!(fin.is_open())){
                cout << "File not find\n";
                exit(-1);
            }
            while(!fin.eof()){
                fin >> x >> y;
                point.x=x;
                point.y=y;
                if(!Qtree.SearchInTree(point)){
                    Qtree.InsertInTree(point);
                }
            }
            fin.close();
        }

        if(mode == 2){
            cout << "Enter point coordinates" << endl;
            cin >> x >> y;
            point.x = x;
            point.y = y;
            if(Qtree.SearchInTree(point)){
                cout << "The point was not added because it already exists" << endl;
            }
            else{
                if(!Qtree.InsertInTree(point)){
                    cout << "This point is not contained in the original rectangle"<< endl;
                }
                else{
                    cout << "The point added" << endl;
                }
            }
        }

        if(mode == 3){
            cout << "Enter point coordinates" << endl;
            cin >> x >> y;
            point.x = x;
            point.y = y;
            if(Qtree.DeletePointInTree(point)){
                cout << "Point removed" << endl;
            }
            else{
                cout << "Point not found" << endl;
            }
        }

        if(mode == 4){
            n = Qtree.AmountOfPoints(iBox);
            cout << endl << "Amount of points is: " << n << endl;
        }

        if(mode == 5){
            cout << "Enter the rectangle:" << endl;
            cout << "Enter rectangle center coordinates:" << endl;
            cin >> x >> y;
            cout << "Enter the height of rectangle:" << endl;
            cin >> h;
            cout << "Enter the width of rectangle:" << endl;
            cin >> w;
            if(w<=0 || h <=0){
                cout << "incorrect input" << endl;
                return -1;
            }
            Rectangle range(x-w/2,y-h/2,w+0.0001,h+0.0001);
            CList l(Qtree.GetRangeInTree(range));
            if(l.IsEmpty()){
                cout << "No points found in this range" << endl;
                continue;
            }
            n = l.getlen();
            l.GoToBegin();
            Point *arr = new Point[n];
            l.GetCur(x,y);
            arr[0].x = x;
            arr[0].y = y;
            int i=1;
            while(l.GoToNext()==0){
                l.GetCur(x,y);
                arr[i].x = x;
                arr[i].y = y;
                i++;
            }
            MergeSortXXX(arr,n);
            MergeSortYYY(arr,n);
            cout << endl << "Points: " << endl;
            for(int i=0;i<n; i++){
                cout << arr[i].x<< " " << arr[i].y << endl;
            }
            delete[] arr;
        }

        if(mode == 6){
            cout << "Enter point coordinates:" << endl;
            cin >> x >> y;
            point.x = x;
            point.y = y;
            if(Qtree.SearchInTree(point)){
                cout << "This point exists" << endl;
            }
            else{
                cout << "This point does not exist" << endl;
            }
        }

        if(mode == 7){
            break;
        }

        if(mode != 1 && mode != 2 && mode != 3 && mode != 4 && mode != 5 && mode != 6 && mode != 7){
            cout << "incorrect input" << endl;
            break;
        }
    }

    return 0;
}
