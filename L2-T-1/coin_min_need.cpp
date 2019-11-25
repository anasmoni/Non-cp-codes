#include<bits/stdc++.h>
using namespace std;


int min_coin_need(int coin[], int make , int len){

    int dp[make+1];

    dp[0]=0;

    for(int i=1 ; i<=make ; ++i ) dp[i] = INT_MAX ;

    for(int m = 1 ; m <= make ; ++m){

        for(int i=0; i<n ; i++){

            if(coin[i] <= m){

                int temp = dp[m-coin[i]];

                if(temp != INT_MAX && temp+1 < dp[m]) dp[m] = ++temp;
            }
        }
    }

    return dp[make];

}

int main()
{



    return 0;
}
