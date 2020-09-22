#pragma once
#include "publicdef.h"
/* 
在本问题中，有根树指满足以下条件的有向图。该树只有
一个根节点，所有其他节点都是该根节点的后继。每一个节点
只有一个父节点，除了根节点没有父节点。

输入一个有向图，该图由一个有着N个节点 (节点值不重复
1, 2, ..., N) 的树及一条附加的边构成。附加的边的两个顶点包含
在1到N中间，这条附加的边不属于树中已存在的边。

结果图是一个以边组成的二维数组。 每一个边 的元素是一对 [u, v]，
用以表示有向图中连接顶点 u 和顶点 v 的边，其中 u 是 v 的一个父节点
。

返回一条能删除的边，使得剩下的图是有N个节点的有根树。若有多个答案
，返回最后出现在给定二维数组的答案

有根树

树， 是否有环


在一棵树中，边的数量比节点的数量少 1。如果一棵树有 N 个节点，则这棵树有 N-1 条边。这道题中的图在树的基础上多了一条附加的边，因此边的数量也是 N。

树中的每个节点都有一个父节点，除了根节点没有父节点。在多了一条附加的边之后，可能有以下两种情况：

附加的边指向根节点，则包括根节点在内的每个节点都有一个父节点，此时图中一定有环路；//  

附加的边指向非根节点，则恰好有一个节点（即被附加的边指向的节点）有两个父节点，此时图中可能有环路也可能没有环路。  // 

要找到附加的边，需要遍历图中的所有的边构建出一棵树，在构建树的过程中寻找导致冲突（即导致一个节点有两个父节点）的边以及导致环路出现的边。

具体做法是，使用数组 parent 记录每个节点的父节点，初始时对于任何 i  N1≤i≤N 都有 parent[i]=i，另外创建并查集，初始时并查集中的每个节点都是一个连通分支，
该连通分支的根节点就是该节点本身。遍历每条边的过程中，维护导致冲突的边和导致环路出现的边，由于只有一条附加的边，因此最多有一条导致冲突的边和一条导致环路出现的边。

当访问到边[u,v] 时，进行如下操作：

如果此时已经有 parent[v]

​
=v，说明 v 有两个父节点，将当前的边 [u,v] 记为导致冲突的边；

否则，令parent[v]=u，然后在并查集中分别找到 u 和 v 的祖先（即各自的连通分支中的根节点），
如果祖先相同，说明这条边导致环路出现，将当前的边 [u,v] 记为导致环路出现的边，如果祖先不同，则在并查集中将 u 和 v 进行合并。

根据上述操作，同一条边不可能同时被记为导致冲突的边和导致环路出现的边。如果访问到的边确实同时导
致冲突和环路出现，则这条边被记为导致冲突的边。

在遍历图中的所有边之后，根据是否存在导致冲突的边和导致环路出现的边，得到附加的边。

如果没有导致冲突的边，说明附加的边一定导致环路出现，而且是在环路中的最后一条被访问到的边，因此附加的边即为导致环路出现的边。

如果有导致冲突的边，记这条边为 [u,v]，则有两条边指向 v，另一条边为parent[v],v]，需要通过判断是否有导致环路的边决定哪条边是附加的边。

如果有导致环路的边，则附加的边不可能是 [u,v]（因为 [u,v]已经被记为导致冲突的边，不可能被记为导致环路出现的边），因此附加的边是 [parent[v],v]。

如果没有导致环路的边，则附加的边是后被访问到的指向 v 的边，因此附加的边是 [u,v]。


*/

// class Solutionpro685 {
// public:
//     
//     vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
//         vector<int> temp;
//         vector<int > ans;
//         struct Elem {
//             int first;
//             int second;
//             Elem(int fir = 0, int sec = 0)
//             {
//                 first = fir;
//                 second = sec;
//             };
//         };
// 
//         vector<Elem> Edges;
// 
//         int N = edges.size();
//         if (N <=1 )return { -1 ,-1};
//         int m = edges.at(0).size();
//         if (m != 2)return ans;
//         int i, j;
//         int root = edges.at(0).at(0);
//         for (i = 0; i < N; i++)
//         {
//          if(edges.at(i).size()==2)Edges.push_back(Elem(edges.at(i).at(0),edges.at(i).at(1)));
//         }
//         //  接下来判断是否有闭环   闭环:1- first,second 都是其他边的second   .2  . first 是其他的second . second 是根
//         // 寻找根
//       
//         for (i = 1; i < N; i++)
//         {
//             j = 0;
//             int count = 0;
//             while (j < N)
//             {
//                 if (j == i) { j++; continue; }
//                 if (Edges.at(i).second == root && Edges.at(i).first == Edges.at(j).second)
//                 {
//                     temp.push_back(Edges.at(i).first);
//                     temp.push_back(Edges.at(i).second);
//                     break;
//                 }
//                 if (Edges.at(i).first == Edges.at(j).second)
//                 {
//                     count++;
//                     if (count == 2)
//                     {
//                         temp.push_back(Edges.at(i).first);
//                         temp.push_back(Edges.at(i).second);
//                         break;
//                     }
//                 }
//                 if (Edges.at(i).second == Edges.at(j).second)
//                 {
//                     count++;
//                     if (count == 2)
//                     {
//                         temp.push_back(Edges.at(i).first);
//                         temp.push_back(Edges.at(i).second);
//                         break;
//                     }
//                 }
//                 j++;
//             }
//         }
//         return temp;
//     }
//     void test()
//     {
//         string inputstr;
//         vector<vector<int>> inputvec;
//         char marks;
//         vector<int> ans;
//         string output;
//         while (getline(cin, inputstr))
//         {
//             inputvec = stringtovectorvector(inputstr);
//             ans = findRedundantDirectedConnection(inputvec);
//             output = vectorTostring(ans);
//             cout << " the answer is " << output<<endl;
//             cout << " do you want to continue .. y/n" << endl;
//             cin.get(marks);
//             if (marks != 'y')break;
//             cin.get();
//         }
//     }
//       
// };

// 并查集 
struct Unionfind {
    vector<int> ancestor;

    Unionfind(int n)
    {
        ancestor.resize(n);
        for (int i = 0; i < n; i++)
        {
            ancestor[i] = i;
        }
    }

    int find(int son)
    {
        return son == ancestor[son] ? son : ancestor[son] = find(ancestor[son]);
    }
    void merge(int u, int v)
    {
        ancestor[find(u)] = find(v);
    }
};


vector<int>  function(vector<vector<int>>& edges)
{
    int nodescount = edges.size();
    Unionfind uf(nodescount + 1);
    vector<int> parent;
    parent.resize(nodescount+1);
    for (int i = 0; i <= nodescount; i++)
    {
        parent[i] = i;
    }
    int conflict = -1;
    int cycle = -1;

    //
    for (int i = 0; i < nodescount; i++)
    {
        int node0 = edges[i][0];
        int node1 = edges[i][1];
        if (parent[node1] != node1)
        {
            conflict = i;
        }
        else
        {
            parent[node1] = node0;
            if (uf.find(node0) == uf.find(node1))
            {
                cycle = i;
            }
            else
            {
                uf.merge(node0, node1);
            }
        }

    }
    vector<int> ans;

    if (conflict < 0)
    {
        ans.push_back(edges[cycle][0]);
        ans.push_back(edges[cycle][1]);
        return ans;
    }
    else
    {
        auto iter = edges[conflict];
        if (cycle > 0)
        {
            ans.push_back(parent[iter[1]]);
            ans.push_back(iter[1]);
            return ans;

        }
        else
        {
            ans.push_back(iter[0]);
            ans.push_back(iter[1]);
            return ans;
        }
    }
    return ans;
}
struct UnionFind {
    vector <int> ancestor;

    UnionFind(int n) {
        ancestor.resize(n);
        for (int i = 0; i < n; ++i) {
            ancestor[i] = i;
        }
    }

    int find(int index) {
        return index == ancestor[index] ? index : ancestor[index] = find(ancestor[index]);
    }

    void merge(int u, int v) {
        ancestor[find(u)] = find(v);
    }
};

class Solutionp685 {
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        int nodesCount = edges.size();
        UnionFind uf = UnionFind(nodesCount + 1);
        auto parent = vector<int>(nodesCount + 1);
        for (int i = 1; i <= nodesCount; ++i) {
            parent[i] = i;
        }
        int conflict = -1;
        int cycle = -1;
        for (int i = 0; i < nodesCount; ++i) {
            auto edge = edges[i];
            int node1 = edge[0], node2 = edge[1];
            if (parent[node2] != node2) {
                conflict = i;  //  
            }
            else {
                parent[node2] = node1;
                if (uf.find(node1) == uf.find(node2)) {
                    cycle = i;
                }
                else {
                    uf.merge(node1, node2);
                }
            }
        }
        if (conflict < 0) {
            auto redundant = vector<int>{ edges[cycle][0], edges[cycle][1] };
            return redundant;
        }
        else {
            auto conflictEdge = edges[conflict];
            if (cycle >= 0) {
                auto redundant = vector<int>{ parent[conflictEdge[1]], conflictEdge[1] };
                return redundant;
            }
            else {
                auto redundant = vector<int>{ conflictEdge[0], conflictEdge[1] };
                return redundant;
            }
        }
    }
         void test()
         {
             string inputstr;
             vector<vector<int>> inputvec;
             char marks;
             vector<int> ans;
             string output;
             while (getline(cin, inputstr))
             {
                 inputvec = stringtovectorvector(inputstr);
                 ans = findRedundantDirectedConnection(inputvec);
                 output = vectorTostring(ans);
                 cout << " the answer is " << output<<endl;
                 cout << " do you want to continue .. y/n" << endl;
                 cin.get(marks);
                 if (marks != 'y')break;
                 cin.get();
             }
         }
};



