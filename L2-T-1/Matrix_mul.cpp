#include<bits/stdc++.h>
using namespace std;

int mat(int a[] , int n){

    int dp[n][n] , i , j , k , col ;

    for(int i=1 ; i<n ; i++)dp[i][i]=0;

    for(col = 2 ; col<n ; col++){

        for(i=1 , j=col ; i<n-col+1 ; j++,++i){

            dp[i][j] = INT_MAX;

            for( k = i ; k<j ; k++){

                int temp = dp[i][k] + dp[k+1][j] + a[i-1]*a[k]*a[j];

                dp[i][j] = min(dp[i][j],temp);
            }
        }
    }

    return dp[1][n-1];
}

int main()
{
    int n;
    cin>>n;
    int a[n];

    for(int i=0  ; i<n; cin>>a[i++]);

    cout<<mat(a,n);

    return 0;
}
