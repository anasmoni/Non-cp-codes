#include<bits/stdc++.h>
#include <windows.h>
using namespace std;

typedef long long int lli;
typedef unsigned long long int ulli;
typedef pair<int,int> pii;

#define ones(x) __builtin_popcount(x)
#define onesl(x) __builtin_popcountl(x)
#define onesll(x) __builtin_popcountll(x)

#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple
#define scn(n) scanf("%d",&n)
#define scnll(n) scanf("%lld",&n)
#define scn2(n,m) scanf("%d%d",&n,&m)
#define scn3(n,m,w) scanf("%d%d%d",&n,&m,&w)
#define scn2ll(n,m) scanf("%lld%lld",&n,&m)
#define atoz(v) v.begin(),v.end()
#define ratoz(v) v.rbegin(),v.rend()
#define Fill(a,v) memset(a,v,sizeof(a))
#define sz(v) v.size()
#define fi first
#define se second
#define inf 1e9
#define pi acos(-1.0)
#define sqr(x) x*x
#define max3(a,b,c) max(a,max(b,c))
#define min3(a,b,c) min(a,min(b,c))
#define ten(n) (int)1e##n
#define tenll(n) (lli)1e##n
#define mod 1000000007
#define FastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

int Set(int N,int pos)
{
    return N=N | (1<<pos);
}
int reset(int N,int pos)
{
    return N = N & ~(1<<pos);
}
bool check(int N,int pos)
{
    return (bool)(N & (1<<pos));
}

///priority_queue< int, vector< int >, greater< int > > minHeap;


string char_to_bin(char c)
{
    int n = (int)c;
    string bin ;

    if(n == 0) return "0";

    while(n)
    {
        if(n%2) bin += '1';
        else bin += '0';
        n /= 2;
    }
    reverse(atoz(bin));

    while(bin.size()<8) bin = "0" + bin;

    return bin;
}

char bin_to_char(string s)
{

    int n = 0;

    for(int po = s.size()-1,i=0 ; po>=0; po--,i++)
    {
        if(s[i]=='1')n += (1<<po);
    }
    ///cout<<n<<endl;
    return ((char)n);
}

bool is_pow_2(int n)
{

    if(n==0)return false;

    while(n%2 == 0) n /= 2;

    return (n==1);
}

int Append_CRC_checksum(vector<char>&frame, string poly)
{

    string crc;

    for(int i=1; i<poly.size(); i++) frame.pb('0');

    for(int i=0; i<frame.size(); i++)
    {

        if(crc.size()<poly.size())
        {
            if(crc.size()==0 && frame[i]=='0')continue;
            crc += frame[i];
        }
        if(crc.size()<poly.size())continue;

        for(int j=0; j<crc.size(); j++)
        {

            crc[j] = (crc[j]==poly[j]?'0':'1');
        }
        reverse(atoz(crc));
        while(crc.size())
        {
            if(crc.back()=='0')crc.pop_back();
            else break;
        }
        if(crc.size()) reverse(atoz(crc));
    }
    for(int i=1; i<poly.size(); i++) frame.pop_back();

    cout<<"\n\nData bits after appending CRC checksum <sent frame>:\n\n";

    for(char c : frame)cout<<c;
    while(crc.size()<(poly.size()-1))crc = "0" + crc;
    for(int i=0; i<crc.size(); i++)
    {


        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);

        cout<<crc[i];
        frame.pb(crc[i]);
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

    return (int)crc.size();
}

float RandProb(void)
{
    float x;
    x = rand() / (double)RAND_MAX;
    return x;
}

void Error_Detection(vector<char>&frame, string poly)
{

    string crc;
  //  cout<<"\n++++++\n";
    for(int i=0; i<frame.size(); i++)
    {
//cout<<frame[i];
        if(crc.size()<poly.size())
        {
            if(crc.size()==0 && frame[i]=='0')continue;
            crc += frame[i];
        }
        if(crc.size()<poly.size())continue;

        for(int j=0; j<crc.size(); j++)
        {

            crc[j] = (crc[j]==poly[j]?'0':'1');
        }
        reverse(atoz(crc));
        while(crc.size())
        {
            if(crc.back()=='0')crc.pop_back();
            else break;
        }
        if(crc.size()) reverse(atoz(crc));
    }
//cout<<"\n____________ "<<endl;
    cout<<"\n\nResult of CRC checksum matching :  ";
    if(crc.size() == 0)cout<<"No Error\n\n";
    else cout<<"Error detected \n\n";

}

int main()
{
    ///freopen("output.txt","w",stdout);
    ///freopen("input.txt","r",stdin);

    ///FastIO;

    string data_string, gen_poly;
    int m;
    double p;

    cout<<"Enter data string : ";
    getline(cin,data_string);
    cout<<"Enter number of data bytes in a row <m> : ";
    cin>>m;
    cout<<"Enter probability : ";
    cin>>p;
    cout<<"Enter generator polynomial : ";
    cin>>gen_poly;

    while(data_string.size()%m) data_string += '~';

    cout<<"Data string after padding :   "<<data_string<<"\n\n";

    int rows = data_string.size()/m;

    string data_block[rows+1], data_block_with_chk_bit[rows+1];

    for(int r=0,i=0; r<rows; r++)
    {

        for(int cm = m ; cm ; cm--, i++)
        {
            data_block[r] += char_to_bin(data_string[i]);
        }
    }

    cout<<"Data block < ascii code of m characters per row >\n";

    for(int r = 0; r<rows; r++)
    {
        cout<<data_block[r]<<endl;
    }

    for(int r=0; r<rows; r++)
    {

        for(int i=0, j=1 ; i<data_block[r].size(); i++, j++)
        {

            if(is_pow_2(j))
            {
                data_block_with_chk_bit[r] += 'c';
                i--;
            }
            else data_block_with_chk_bit[r] += data_block[r][i];
        }
    }

    for(int r=0; r<rows; r++)
    {

        for(int j=0 ; j<data_block_with_chk_bit[r].size() ; j++)
        {


            if(data_block_with_chk_bit[r][j] == 'c')
            {

                int cnt = 0;
                int taken = 0;
                bool take = true;

                for(int k=j ; k<data_block_with_chk_bit[r].size(); k++)
                {


                    if(take)
                    {
                        cnt += (data_block_with_chk_bit[r][k] == '1');
                    }
                    taken = (taken+1)%(j+1);

                    if(taken == 0) take = !take;

                }
                data_block_with_chk_bit[r][j] = (cnt%2? '1' : '0');
            }

        }
    }



    cout<<"\n\nData block after adding check bits\n\n";

    vector<char>column_frame;

    for(int r=0; r<rows; r++)
    {

        for(int j=0 ; j<data_block_with_chk_bit[r].size() ; j++)
        {

            if(is_pow_2(j+1))
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
            }
            cout<<data_block_with_chk_bit[r][j];
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        }
        cout<<endl;
    }

    for(int j=0; j<data_block_with_chk_bit[0].size(); j++)
    {

        for(int r=0; r<rows; r++)
        {

            column_frame.pb(data_block_with_chk_bit[r][j]);
        }
    }

    cout<<"\n\nData bits after column-wise serialization\n\n";

    for(char c : column_frame)cout<<c;

    int crc_size = Append_CRC_checksum(column_frame,gen_poly);

    cout<<"\n\nReceived Frame: \n\n";

    vector<bool>flipped(column_frame.size(),false);

    for(int i=0; i<column_frame.size(); i++)
    {

        double x = RandProb();

        if(x<=p && p>0.0)
        {
            column_frame[i] = (column_frame[i]=='0'? '1' : '0');
            flipped[i] = true;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        }
        cout<<column_frame[i];
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    }

    Error_Detection(column_frame,gen_poly);

    for(int i=1; i<=crc_size; i++) column_frame.pop_back();

    for(int j=0, i=0; i<column_frame.size(); j++)
    {

        for(int r=0; r<rows; r++, i++)
        {

            data_block_with_chk_bit[r][j] = column_frame[i];

            if(flipped[i]) data_block_with_chk_bit[r][j] = (column_frame[i]=='1'?'l':'o');

        }
    }

    cout<<"\n\nData block after removing CRC checksum bits : \n\n";

    for(int r=0 ; r<rows;  r++)
    {

        for(int i=0; i<data_block_with_chk_bit[r].size(); i++)
        {
            char c = data_block_with_chk_bit[r][i];
            if(c == 'l' || c == 'o')
            {
                c = (c=='l'?'1':'0');
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
            }
            cout<<c;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        }
        cout<<endl;
    }

    string final_data_block[rows+1];

    for(int r=0 ; r<rows;  r++)
    {
        int idx = 0;

        for(int i=0; i<data_block_with_chk_bit[r].size(); i++)
        {
            if(is_pow_2(i+1) == false){
                continue;
            }

            char c = data_block_with_chk_bit[r][i];
            if(c == 'l' || c == 'o')
            {
                idx += (i+1);
            }
        }

        for(int i=0; i<data_block_with_chk_bit[r].size(); i++)
        {
            char c = data_block_with_chk_bit[r][i];

            if(idx == i+1) c = (c=='1'?'0':'1');

            if(is_pow_2(i+1) == false){
                final_data_block[r] += c;

            }
        }
    }

    cout<<"\n\nData block after removing check bits :\n\n";



    for(int r=0 ; r<rows;  r++)
    {
        for(int i=0; i<final_data_block[r].size(); i++)
        {
            cout<<final_data_block[r][i];
        }
        cout<<endl;
    }

    cout<<"\n\nOutput Frame : ";

    for(int r=0 ; r<rows;  r++)
    {
        string now ;
        int cnt = 0;
        for(int i=0; i<final_data_block[r].size(); i++)
        {
            cnt++;
            now += final_data_block[r][i];
            if(cnt%8 == 0){
                cout<<bin_to_char(now);
                now.clear();
            }
        }
    }



    return 0;
    ///return main();
}

///sin and cos expect input in radians not degrees. so use , sin(degrees * pi / 180)
