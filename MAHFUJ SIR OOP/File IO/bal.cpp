#include <stdio.h>
int arr[1000000];
int gcd(int a,int b)
{
    if(b==0)
        return a;
    else return gcd(b,a%b);
}
int main()
{
    int n,pl,l,i,j,g;
    scanf("%d ",&n);
    for(i=0; i<n; i++)
        scanf("%d",arr+i);
    pl=n;
    l=0;
    for(i=0; i<n && pl>l; i++,--pl)
        if(arr[i]>=1)
        {
            g=arr[i];
            for(j=i+1; j<n; j++)
            {
                g=gcd(g,arr[j]);
                if(g>1)
                    break;
            }
            --j;
            if(l<j-i+1)
                l=j-i+1;
        }
    printf("%d",l);
    return 0;
}
