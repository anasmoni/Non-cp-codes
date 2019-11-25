#include<bits/stdc++.h>

using namespace std;

string s,t,lcs;
int m,n,len;
int dp[1000][1000];

void LCS()
{
    for(int i=0 ; i<=m ; i++)
    {
        for(int j=0 ; j<=n ; ++j)
        {
            if(!i || !j)dp[i][j]=0;

            else if(s[i-1]==t[j-1])
            {
                dp[i][j] = dp[i-1][j-1]+1;
            }
            else dp[i][j] = max(dp[i-1][j] , dp[i][j-1]);
        }
    }

    len = dp[m][n];
    cout<<max(len,1)<<endl;
}

void print(int i, int j){

    if(!i || !j ){for(int i=lcs.size()-1 ; i>=0; cout<<lcs[i--]); cout<<endl; return;}

    if (s[i-1] == t[j-1]){lcs += s[--i]; print(i,j-1);}

    else if (dp[i-1][j] > dp[i][j-1])print(i-1,j);
    else print(i,j-1);
}




int main()
{
    while(true)
    {
        cout<<"Enter 0 0 to exit.....\n";

        cin>>s>>t;
        if(s=="0")break;

        n = t.size();
        m = s.size();

        LCS();
        lcs=" ";
        if(len)print(m,n);

    }
    return 0;
}
