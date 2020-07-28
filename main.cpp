#include <iostream>
#include "UnionFindTestHelper.h"
#include "UnionFind4.h"
#include <vector>
#include <cassert>
using namespace std;

vector<vector<int>>  make_rand_map(int n){
    vector<vector<int>> vec(n, vector<int>(n));
    srand(time(NULL));
    for(int i = 0; i < n; i ++){
        for(int j = 0;  j < n; j ++){
            vec[i][j] = rand() % 2;
            cout<<vec[i][j]<<" ";
        }
        cout<<endl;
    }
    return vec;
}


/*Convert two dimensional array into one only
1 2 3 4
           => 1 2 3 4 5 6 7 8
5 6 7 8
*/
vector<int> reduce(vector<vector<int>> &vec){
    int count = vec.size() * vec.size();
    vector<int> t_vec = vector<int>(count);
    int k = 0;
    for(int i = 0; i < vec.size(); i ++){
        for(int j = 0; j < vec.size(); j++){
            t_vec[k] = vec[i][j];
            k ++;
        }
    }
    return t_vec;
}


//vec[x][y] = arr[x * size() + y]  eg: (0,0 => 0, (0, 1) => 1 
int transform_xy(int x, int y, const vector<vector<int>> &vec){
    //4 X 4
    //1, 3 => 7
    assert(x >= 0 && x < vec.size());
    assert(y >= 0 && y < vec.size());
    return x * vec.size() + y;
}

//position
struct Node{
    Node(int x, int y){
        this->x = x;
        this->y = y;
    }
    int x, y;
};


//load relation
void load_relation(UF4::UnionFind &uf, const vector<vector<int>> &vec){
    //analyze union relation
    //each element has up right down left 4 direction
    for(int x = 0; x < vec.size(); x ++){
        for(int y = 0; y < vec.size(); y ++){
            Node up = Node(x - 1, y);
            Node right = Node(x, y + 1);
            Node down = Node(x + 1, y);
            Node left = Node(x, y - 1);
            //analyze and uion
            int q = transform_xy(x, y, vec);
            if(up.x >= 0 && up.x < vec.size() && up.y >= 0 && up.y < vec.size()){
                if(vec[up.x][up.y] == vec[x][y]){
                    int p = transform_xy(up.x, up.y, vec);
                    uf.unionElements(p, q);
                }
            }
            if(right.x >= 0 && right.x < vec.size() && right.y >= 0 && right.y < vec.size()){
                if(vec[right.x][right.y] == vec[x][y]){
                    int p = transform_xy(right.x, right.y, vec);
                    uf.unionElements(p, q);
                }
            }
            if(down.x >= 0 && down.x < vec.size() && down.y >= 0 && down.y < vec.size()){
                if(vec[down.x][down.y] == vec[x][y]){
                    int p = transform_xy(down.x, down.y, vec);
                    uf.unionElements(p, q);
                }
            }
            if(left.x >= 0 && left.x < vec.size() && left.y >= 0 && left.y < vec.size()){
                if(vec[left.x][left.y] == vec[x][y]){
                    int p = transform_xy(left.x, left.y, vec);
                    uf.unionElements(p, q);
                }
            }
        }
    }
}


int main() {
    int n = 50;
    //for debug
    //UnionFindTestHelper::testUF1(n);
    //UnionFindTestHelper::testUF2(n);
    //UnionFindTestHelper::testUF3(n);
    //UnionFindTestHelper::testUF4(n);
    //init map n x n
    //cout<<"-------------------"<<endl;
    //for(int i = 0; i < arr.size(); i ++){
    //    cout<<arr[i]<<" ";
    //}
    //cout<<endl;
    //int x = 1, y = 3;
    //cout<<"x : "<<x<<" y :"<<y<<" res: "<<map[x][y]<<endl;
    //int p = transform_xy(x, y, map);
    //cout<<"p "<<p<<" value: "<<arr[p]<<endl;
    //cout<<"is connected? "<<isConneted(Node(0, 0), Node(0,1))<<endl;
    

    vector<vector<int>> map = make_rand_map(n);
    vector<int> arr = reduce(map);
    
    //instance union-find
    UF4::UnionFind uf = UF4::UnionFind(n * n);

    //load relatetion
    load_relation(uf, map);

    //check is connected
    int x1 = 0, y1 = 0;
    int p = transform_xy(x1, y1, map);
    int x2 = 1, y2 = 1;
    int q = transform_xy(x2, y2,map);

    //print result
    cout<<"is connected?:"<<uf.isConnected(p, q)<<endl;
    return 0;
}
