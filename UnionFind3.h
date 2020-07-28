#ifndef _UF3_H_
#define _UF3_H_

#include <iostream>
#include <cassert>
using namespace std;
namespace UF3{
    class UnionFind{
    private:
        int *parent;
        int count;
        int *rank;
    public:
        UnionFind(int count){
            parent = new int[count];
            rank = new int[count];
            this->count = count;
            parent = new int[count];
            for(int i = 0; i < count; i ++){
                parent[i] = i;
                rank[i] = 1;
            }
        }

        ~UnionFind(){
            delete[] parent;
            delete[] rank;
        }

        int find(int p){
            assert(p >= 0 && p < count);
            while(p != parent[p]){
                p = parent[p];
            }
            return p;
        }

        bool isConnected(int p, int q){
            return find(p) == find(q);
        }

        void unionElements(int p, int q){
            int pRoot = find(p);
            int qRoot = find(q);
            if(pRoot == qRoot){
                return;
            }
            if(rank[pRoot] < rank[qRoot]){
                parent[pRoot] = qRoot;
            }else if(rank[qRoot] < rank[pRoot]){
                parent[qRoot]  = pRoot;
            }
            else{
                parent[pRoot] = qRoot;
                rank[qRoot] += 1;
            }
        }
    };
}
#endif
