#include<bits/stdc++.h>
#include <stdlib.h>

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

void MyAssert(bool ok){
    if(ok==false){
        cout<<"Assertion Failed.....";
        exit(0);
    }
}

vector<int>SHIFT , PI_1 , PI_2 , P , PI , CP_1 , CP_2 , E ;

string transposed_data,modified_key,Key_in_iter_i , expanded_bits ;

string plaintext , key;
string pt_bin_rep; /// binary rep of plain text (with padding)
string key_bin_rep;

vector<string> keys;

void InitArrays(){

SHIFT = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

PI_1 = {40, 8, 48, 16, 56, 24, 64, 32,
        39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30,
        37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28,
        35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26,
        33, 1, 41, 9, 49, 17, 57, 25};


P = {16, 7, 20, 21, 29, 12, 28, 17,
     1, 15, 23, 26, 5, 18, 31, 10,
     2, 8, 24, 14, 32, 27, 3, 9,
     19, 13, 30, 6, 22, 11, 4, 25};


PI_2 = {35, 38, 46, 6, 43, 40, 14, 45,
        33, 19, 26, 15, 23, 8, 22, 10,
        12, 11, 5, 25, 27, 21, 16, 31,
        28, 32, 34, 24, 9, 37, 2, 1};

PI = {58, 50, 42, 34, 26, 18, 10, 2,
      60, 52, 44, 36, 28, 20, 12, 4,
      62, 54, 46, 38, 30, 22, 14, 6,
      64, 56, 48, 40, 32, 24, 16, 8,
      57, 49, 41, 33, 25, 17, 9, 1,
      59, 51, 43, 35, 27, 19, 11, 3,
      61, 53, 45, 37, 29, 21, 13, 5,
      63, 55, 47, 39, 31, 23, 15, 7};


CP_1 = {57, 49, 41, 33, 25, 17, 9,
        1, 58, 50, 42, 34, 26, 18,
        10, 2, 59, 51, 43, 35, 27,
        19, 11, 3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15,
        7, 62, 54, 46, 38, 30, 22,
        14, 6, 61, 53, 45, 37, 29,
        21, 13, 5, 28, 20, 12, 4};

CP_2 = {14, 17, 11, 24, 1, 5, 3, 28,
        15, 6, 21, 10, 23, 19, 12, 4,
        26, 8, 16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55, 30, 40,
        51, 45, 33, 48, 44, 49, 39, 56,
        34, 53, 46, 42, 50, 36, 29, 32};

E= {32, 1, 2, 3, 4, 5,
 4, 5, 6, 7, 8, 9,
 8, 9, 10, 11, 12, 13,
 12, 13, 14, 15, 16, 17,
 16, 17, 18, 19, 20, 21,
 20, 21, 22, 23, 24, 25,
 24, 25, 26, 27, 28, 29,
 28, 29, 30, 31, 32, 1};

}

string To_Binary(string s){
    string ret ;

    for(int i=0; i<s.size(); i++){
        char c = s[i];
        bitset<8>bs;
        bs = bitset<8>(c);
        for(int j=bs.size()-1; j>=0; j--) ret += (bs[j]?'1':'0');
    }
    while(ret.size()%64) ret += '0';
    return ret;
}

string To_String(string bin){

    MyAssert(bin.size()%8 == 0);
    string ret ;

    for(int i=0; (i+7)<bin.size(); i += 8){

        bitset<8>bs(bin.substr(i,8));

        char c = bs.to_ulong();
        ret += c;
    }
    return ret;
}


string Rotate_Left(string s, int n){

    for(int i=0; i<n; i++) s += s[i];
    s = s.substr(n);
    return s;
}

string XOR(string a , string b){

    MyAssert(a.size() == b.size());
    string ret ;

    for(int i=0; i<a.size(); i++){
        ret += (a[i]==b[i]?'0' : '1');
    }
    return ret;
}

string f(string R_i_1 , string ki){

    string e;

    for(int i=0; i<E.size(); i++) e += R_i_1[ E[i]-1 ];

    MyAssert(e.size() == ki.size() && e.size()==48);

    string shorten_result;
    string result_xor = XOR(e,ki);

    for(int i=0; i<PI_2.size(); i++) shorten_result += result_xor[ PI_2[i]-1 ];

    string ret;

    MyAssert(shorten_result.size() == P.size() && P.size() == 32);

    for(int i=0; i<32; i++) ret += shorten_result[ P[i]-1 ];

    return ret;
}

void Make_Keys(){

    modified_key.clear();

    for(int i=0; i<CP_1.size(); i++) modified_key += key_bin_rep[ CP_1[i]-1 ];

    for(int iter=0; iter<16; iter++){

        string mf = modified_key;

        string L_28 = mf.substr(0,28);
        string R_28 = mf.substr(28);

        mf = Rotate_Left(L_28,SHIFT[iter]) + Rotate_Left(R_28,SHIFT[iter]);

        Key_in_iter_i.clear();
        for(int i=0; i<CP_2.size(); i++) Key_in_iter_i += mf[ CP_2[i]-1 ];

        keys.pb(Key_in_iter_i);
    }
}

void Init(){

    cout<<"Enter Plain_Text : ";
    getline(cin,plaintext);
    cout<<"Enter Key : ";
    getline(cin,key);

    pt_bin_rep = To_Binary(plaintext);
    key_bin_rep = To_Binary(key);

    InitArrays();
    Make_Keys();
}

string DES_Encrypt(string data){

    MyAssert(data.size() == 64);

    transposed_data.clear();

    for(int i=0; i<PI.size(); i++) transposed_data += data[PI[i]-1];

    for(int iter=0; iter<16; iter++){

        string L_i, L_i_1 ,R_i , R_i_1;

        L_i_1 = transposed_data.substr(0,32);
        R_i_1 = transposed_data.substr(32);
        L_i = R_i_1;
        R_i = XOR(L_i_1 , f(R_i_1, keys[iter]) );
        //cout<<keys[iter]<<endl;
       if(iter == 15){
            swap(L_i,R_i);
       }
        transposed_data = L_i + R_i;
    }
    string send;
    for(int i=0; i<PI_1.size(); i++) send += transposed_data[PI_1[i]-1];
    return send;
}

string Encrypt(){
    string Encrypted;

    for(int i=0; (i+63)<pt_bin_rep.size(); i += 64){
        Encrypted += DES_Encrypt(pt_bin_rep.substr(i,64));
    }

    cout<<"\n\Ciphered : "<<To_String(Encrypted)<<"\n\n";
    return Encrypted;
}

string DES_Decrypt(string data){

     transposed_data.clear();

    for(int i=0; i<PI.size(); i++) transposed_data += data[PI[i]-1];

    for(int i=15; i>=0; i--){

        string L_i, L_i_1 ,R_i , R_i_1;

        Key_in_iter_i = keys[i];

        L_i_1 = transposed_data.substr(0,32);
        R_i_1 = transposed_data.substr(32);
        L_i = R_i_1;
        R_i = XOR(L_i_1 , f(R_i_1, Key_in_iter_i) );

        if(i==0)swap(L_i,R_i);

        transposed_data = L_i + R_i;
    }
    string send;
    for(int i=0; i<PI_1.size(); i++) send += transposed_data[PI_1[i]-1];
    return send;
    return send;
}


void Decrypt(string Encrypted){

    string decrypted;

    for(int i=0; (i+63)<Encrypted.size(); i += 64){
        decrypted += DES_Decrypt(Encrypted.substr(i,64));
    }
    cout<<"\n\DeCiphered : "<<To_String(decrypted)<<"\n\n";
}

int main()
{
    Init();

    Decrypt(Encrypt());

    return 0;
    ///return main();
}

/**
Hello World
megabuck

Attack_at_dawn!
cse_buet
*/

///sin and cos expect input in radians not degrees. so use , sin(degrees * pi / 180)
