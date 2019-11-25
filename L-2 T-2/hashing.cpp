#include<bits/stdc++.h>
using namespace std;

typedef long long int lli;
typedef pair<int,int> pii;
typedef vector<int> vec;

#define pb push_back
#define mp make_pair
#define mt make_tuple
#define scn(n) scanf("%d",&n)
#define scnll(n) scanf("%lld",&n)
#define scn2(n,m) scanf("%d%d",&n,&m)
#define scn3(n,m,w) scanf("%d%d%d",&n,&m,&w)
#define scn2ll(n,m) scanf("%lld%lld",&n,&m)
#define atoz(v) v.begin(),v.end()
#define Fill(a,v) memset(a,v,sizeof(a))
#define sz(v) v.size()
#define fi first
#define se second
#define inf 1e9
#define pi acos(-1.0)
#define sqr(x) x*x
#define max3(a,b,c) max(a,max(b,c))
#define min3(a,b,c) min(a,min(b,c))

#define N 10000
#define len 5
#define dflag -1

string alpha;
void initalpha(){
    for(int i=0; i<26; i++){
        alpha += (char)('A'+i);
    }
    for(int i=0; i<26; i++){
        alpha += (char)('a'+i);
    }
}

long Hash1(string s)//BP
{

    long hsh = 0;

    for(int i = 0; i < sz(s); i++) hsh = (hsh << 7) ^ s[i];

    return abs(hsh);
}

long Hash2(string s)//DJB
{
    long hsh = 5381;

    for(int i = 0; i < s.size(); i++)  hsh = ((hsh << 5) + hsh) + s[i];

    return abs(hsh);
}

long Hash3(string s)//DEk
{
    long hsh = sz(s);

    for(int i = 0; i <sz(s); i++)  hsh = ((hsh << 5) ^ (hsh >> 27)) ^ s[i] ;

    return abs(hsh);
}

class LProb
{

public:


    int *HTable;
    int coll;
    bool h1,h2,h3;
    string str[N];

    LProb(bool hh1, bool hh2, bool hh3)
    {

        HTable = new int[N];

        h1 = hh1;
        h2 = hh2;
        h3 = hh3;
        coll=0;

        for(int i=0; i<N; i++)
        {
            HTable[i]=0;
            str[i]="";
        }


    }


    int getIdx(string s)
    {

        long  hsh;

        if(h1) hsh = Hash1(s);

        if(h2) hsh = Hash2(s);

        if(h3) hsh = Hash3(s);

        return hsh%N;
    }

    int Search(string s, bool forDelete=false)
    {
        int hsh  = getIdx(s);
        int idx = hsh;
        //cout<<idx<<endl;
        if(HTable[idx]==0)return 0;
        else if(str[idx]==s)return forDelete ? idx : HTable[idx];

        for(int i=1; str[idx]!=s ; i++)
        {
            idx = (hsh + i)%N;

            if(str[idx]==s)return forDelete ? idx : HTable[idx];
            if(idx==hsh || HTable[idx]==0)return 0;
        }
    }

    void Insert(string s, int val)
    {
        int hsh  = getIdx(s);
        int idx = hsh;
        coll += (HTable[idx]>0);

        for(int i=1; HTable[idx]>0 ; i++)
        {
            idx = (hsh+i)%N;
        }

        HTable[idx] = val;
        str[idx] = s;
    }

    void Delete(string s)
    {
        int ix = Search(s,true);

        if(ix)
        {
            HTable[ix]=dflag;
            str[ix]="";
        }
    }

};


string make(int mul=3)
{
    string s;
    //cout<<"make\n";
    for(int i=0 ; i<len; i++){
        int r = rand()%52;
        s += alpha[r];
    }
    //cout<<s<<" s\n";
    return s;
}

void Linear_Probing()
{
    cout<<"Linear Probing :......\n\n\n";

    cout<<"Hash 1 : \n";

    LProb LPB1(1,0,0);

    for(int i=0; i<N; )
    {
        string s = make();
        // cout<<s<<endl;
        if(LPB1.Search(s)==0)LPB1.Insert(s,++i);

    }

    cout<<"collision: "<<LPB1.coll<<endl;

    clock_t    start;
    start = std::clock();

    for(int i=0; i<N; i++) LPB1.Search(make(7));

    std::cout << "Time: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;

    cout<<"Hash 2 : \n";

    LProb LPB2(0,1,0);

    for(int i=0; i<N; )
    {
        string s = make(5);
        // cout<<s<<endl;
        if(LPB2.Search(s)==0)LPB2.Insert(s,++i);

    }

    cout<<"collision: "<<LPB2.coll<<endl;

    start = std::clock();

    for(int i=0; i<N; i++) LPB2.Search(make(11));

    std::cout << "Time: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;


    cout<<"Hash 3 : \n";

    LProb LPB3(0,0,1);

    for(int i=0; i<N; )
    {
        string s = make(2);
        // cout<<s<<endl;
        if(LPB3.Search(s)==0)LPB3.Insert(s,++i);

    }

    cout<<"collision: "<<LPB3.coll<<endl;

    start = std::clock();

    for(int i=0; i<N; i++) LPB3.Search(make(17));

    std::cout << "Time: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;

    cout<<"\n--------------\n\n\n";
}



struct node
{
    string s;
    int data;
    node *prev;
    node *next;
};

struct node * New_Node(string s,int item)
{
    struct node * newNode ;
   // newNode = (struct node*) malloc (sizeof(struct node)) ;
   newNode = new node;
    newNode->data = item ;
    newNode->s = s;
    newNode->prev  = NULL;
    newNode->next = NULL;
   // cout<<newNode->s<<endl;
    return newNode;
}

class SChain
{

public:


    node* HTable[N];
    int coll;
    bool h1,h2,h3;

    SChain(bool hh1, bool hh2, bool hh3)
    {

        h1 = hh1;
        h2 = hh2;
        h3 = hh3;
        coll=0;

        for(int i=0; i<N; i++) HTable[i]=0;
    }


    int getIdx(string s)
    {

        long  hsh;

        if(h1) hsh = Hash1(s);

        if(h2) hsh = Hash2(s);

        if(h3) hsh = Hash3(s);

        return hsh%N;
    }

    void Delete_Node(int idx, node *nd)
    {
        if(nd->next==NULL)
        {
            if(nd->prev==NULL)nd=0;
            else nd->prev = NULL;
        }
        else
        {

            if(nd->prev==NULL) nd->next->prev = NULL;
            else
            {
                nd->next->prev = nd->prev;
                nd->prev->next = nd->next;
            }
        }
    }

    int Search(string s, bool forDelete=false)
    {
      //  cout<<"search\n";
        int idx  = getIdx(s);
        if(HTable[idx]==0)return 0;

        node *nd = HTable[idx];

        while(nd){
            if(nd->s==s){
                int d = nd->data;
                if(forDelete)Delete_Node(idx,nd);
                return d;
            }
            nd = nd->next;
        }
        return 0;
    }

    void Insert(string s, int val)
    {
        int idx  = getIdx(s);
      //  cout<<idx<<endl;

        if(HTable[idx]==0){
            HTable[idx] = New_Node(s,val);
          //  cout<<"oka\n";
        }
        else{
            node *nd = HTable[idx];
            coll++;
            //cout<<"wtf\n";
            while(nd->next){nd=nd->next;}

            node *temp = New_Node(s,val);
            temp->prev = nd;
            nd->next = temp;
        }

    }

    void Delete(string s)
    {
        int ix = Search(s,true);
    }

};


void Sep_chain()
{

    cout<<"Separate Chaining......\n\n";


    cout<<"Hash 1 : \n";

    SChain SC1(1,0,0);

    for(int i=0; i<N; )
    {
        string s = make();
        // cout<<s<<endl;
        if(SC1.Search(s)==0)SC1.Insert(s,++i);
        //cout<<"dfdfdd\n";

    }

    cout<<"collision: "<<SC1.coll<<endl;

    clock_t    start;
    start = std::clock();

    for(int i=0; i<N; i++) SC1.Search(make(7));

    std::cout << "Time: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;

    cout<<"Hash 2 : \n";

    SChain SC2(0,1,0);

    for(int i=0; i<N; )
    {
        string s = make(5);

        if(SC2.Search(s)==0)SC2.Insert(s,++i);
    }

    cout<<"collision: "<<SC2.coll<<endl;

    start = std::clock();

    for(int i=0; i<N; i++) SC2.Search(make(11));

    std::cout << "Time: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;


    cout<<"Hash 3 : \n";

    SChain SC3(0,0,1);

    for(int i=0; i<N; )
    {
        string s = make(2);
        // cout<<s<<endl;
        if(SC3.Search(s)==0)SC3.Insert(s,++i);

    }

    cout<<"collision: "<<SC3.coll<<endl;

    start = std::clock();

    for(int i=0; i<N; i++) SC3.Search(make(17));

    std::cout << "Time: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;

    cout<<"\n--------------\n\n\n";


}

int main()
{
    initalpha();

    Linear_Probing();

    Sep_chain();


    return 0;
}











/**taking inputs

#include<bits/stdc++.h>
using namespace std;


void Init_input()
{
    ifstream inFile;
    inFile.open("input.txt");
    int cnt=0;

    while(inFile>>input[cnt++]);
    NI = cnt;

    inFile.close();
}

void Search_input()
{
    ifstream inFile;
    inFile.open("search.txt");
    int cnt=0;

    while(inFile>>sinput[cnt++]);

    NS=cnt;
    inFile.close();
}

string make(string s){

	for(int i=0; i<s.size(); i++){
		int r = rand()%26;
		s[i] = (char)('A'+r);
	}
	return s;
}

int main(){

	freopen("input.txt","w",stdout);

	map<string,bool>mp;

	for(int i=1; i<=10000 ;){
		string s = make("MANAS");
		if(!mp[s]){
			cout<<s<<endl;
			mp[s]=true;
			i++;
		}
	}
}


**/

