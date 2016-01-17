#include<iostream>
#include<vector>
#include<utility>
#include<queue>
#include<algorithm>
#include<limits.h>
#include<map>


using namespace std;

// source is 0, sink is n-1
struct couple
{
    vector<int> bfspath;
    int flow;
    couple()
    {
        bfspath = {};
        flow = 0;
    }

};

couple bfs(vector<vector<int>> A)
{
    int n = A.size();
    queue<int> myq;
    myq.push(0);
    bool sink = false;
    vector<int> path;
    vector<bool> visited(n,false);
    visited[0] = true;
    couple ans;
    map<int,int> trail;
    trail[0] = 0;

    while(!myq.empty())
    {
        int x = myq.front();
        myq.pop();

        if(x == n-1)
        {
            sink = true;
            break;
        }

        for(int i=0;i< A.size();i++)
        {
            if(A[x][i] != 0 && !visited[i])
            {
                trail[i] = x;
                myq.push(i);
                visited[i] = true;
            }
        }

    }

    int minflow = INT_MAX;
    if(trail.find(n-1) != trail.end())
    {
        int prev = n-1;
        while(prev != 0)
        {
            path.push_back(prev);
            prev = trail[prev];
        }
        path.push_back(0);
    }

    if(path.size()>0)reverse(path.begin(),path.end());
    ans.bfspath = path;
    if(sink)
    {
        for(int i=0;i<ans.bfspath.size()-1;i++)
        {
            minflow = min(abs(A[ans.bfspath[i]][ans.bfspath[i+1]]),minflow);
        }
    }
    ans.flow = minflow;
    return ans;
}


int maxflow(vector<vector<int>>A)
{
    couple T;
    int maxiflow = 0;
    vector<int> path ;
    int n,x,y,to_push;

    T = bfs(A);
    path = T.bfspath;
    to_push = T.flow;


    while(path.size() > 0)
    {
        maxiflow += to_push;
        if(to_push == 0)
        {
            cout<<"Something is wrong"<<endl;
            return 0;
        }

        n = path.size();

        for(int i=0;i < n-1;i++)
        {
            x = path[i];
            y = path[i+1];

            if(A[x][y] > 0)
            {
                A[x][y] -= to_push;
                A[y][x] -= to_push;
            }
            else if (A[x][y] < 0)
            {
                A[x][y] += to_push;
                A[y][x] += to_push;
            }
        }

        T = bfs(A);
        path = T.bfspath;
        to_push = T.flow;
    }
    return maxiflow;
}

int main()
{
    int n;
    cin>>n;
    int h=0,i=0,j=0;
    int total = (n*(n+1)*(n+2))/6;
    int counter = 0;
    int t = 0;
    int idx;
    int C = 0;
    map<int,int>mymap;

    while(counter<total)
    {
        counter ++;
        cin >>t;
        idx = (n*n)*h + n*i + j + 1;
        mymap[idx] = t;

        if(i == 0)
        {
            h++;
            i = h;
            j = 0;
        }
        else if(j==i)
        {
            i--;
            j=0;
        }
        else j++;

    }

    int len = n*n*n;
    vector<int>zeros(len + 2,0);
    vector<vector<int>> A(len + 2,zeros);

    for(auto it = mymap.begin(); it!= mymap.end();++it)
    {
        idx = it->first;
        if(mymap[idx] >= 0)
        {
            A[0][idx] = mymap[idx];
            C += mymap[idx];
        }
        if(mymap[idx] < 0) A[idx][len+1] = -mymap[idx];
    }

    for(auto it = mymap.begin(); it!= mymap.end();++it)
    {
        idx = it->first;
        j = (idx-1)%n;
        i = ((idx-1-j)/n)%n;
        h = (idx - 1)/(n*n);

        int n1 = (n*n)*(h-1) + n*i + j + 1;
        int n2 = (n*n)*(h-1) + n*(i-1) + (j-1) + 1;
        int n3 = (n*n)*(h-1) + n*(i-1) + j + 1;
        if(mymap.find(n1) != mymap.end()) A[idx][n1] = C+1;
        if((i>0 && j>0) && mymap.find(n2) != mymap.end()) A[idx][n2] = C+1;
        if((i>0)&& mymap.find(n3) != mymap.end()) A[idx][n3] = C+1;
    }

    int rr = maxflow(A);
    cout<<C - rr <<endl;
}

