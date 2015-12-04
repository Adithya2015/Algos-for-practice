// Example program
#include <iostream>
#include <string>
#include <vector>

using namespace std;
int in(string,string);
vector<int> get_T_array(string);
int main()
{
  string p,q;
  p = "abba";
  q = "abaabbbbaaababaaababbbaaababbbaaab";
   cout<<"string p is: "<<p<<endl;
   cout<<"string q is: "<<q<<endl;
    
 if(in(p,q)>=0) cout<<"p is in q at "<<in(p,q)<<endl;
 else cout<<"p is not in q"<<endl;

 vector<int> T = get_T_array(p);
 cout<<T[0];
 for(int i=1;i<T.size();i++)
 {
    cout<<", " <<T[i];    
 }
}

int in(string p, string q)
{
    vector<int> x = get_T_array(p);
    int matches = 0;
    int i=0,j=0;
    int count = 0;
    while(j<q.size() and count < 1000)
    {
        count++;
        cout<<i<<", "<<j<<endl;
        if(p[j-i] == q[j])
        {
            j++;
            if(j-i == p.size()) return i;
        }
        else if(i==j) 
        {
         i++;j++;
        }
        else
        {
            i = j - x[j-i-1];
        }
        
    }
    
    return -1;
}

vector<int> get_T_array(string p)
{
    int n = p.size();
    vector<int> ans(n,0);
    ans[0] = 0; int i = 1;
    int prev_len = 0;
    while(i<n)
    {
        if(p[prev_len] == p[i]) {ans[i] = prev_len+1; prev_len = ans[i];i++;}
        else if(prev_len >0)
        {
            prev_len = ans[prev_len-1];
        }
        else
        {
            if(p[0] == p[i]) ans[i] = 1;
            else ans[i] = 0;
            i++;
        }
    }
    
    return ans;
}


