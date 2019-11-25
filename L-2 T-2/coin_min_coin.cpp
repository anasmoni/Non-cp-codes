 #include<bits/stdc++.h>
 using namespace std;

 int a[100005] , MAX=1e9 ;

 void solve(int n , int make){

    int dp[make+1];
    for(int i=1 ; i<=make ; dp[i++]=MAX);
    dp[0]=0;

    for (int i=1; i<=make; i++)
    {
        for (int j=0; j<n; j++)
          if (a[j] <= i)
          {
              int temp = dp[i-a[j]];
              if (temp != MAX && temp + 1 < dp[i])dp[i] = temp + 1;
          }
    }

    if(dp[make]==MAX){cout<<"Impossible\n";return;}

    cout<<"Minimum number of notes  needed -> "<<dp[make]<<endl;
 }

 int main(){

     while(1){

        int n,make;
        cout<<"Enter array size and value V or  0 0 to exit.....\n";
        scanf("%d%d",&n,&make);

        if(!n)break;

        for(int i=0 ; i<n ; scanf("%d",&a[i++]));

        solve(n,make);
     }


    return 0;

 }
