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

int curr=0; // current scop id
int buckets=0  , row , column;

long Hash_fun(string s)//BP
{

    long hsh = 0;

    for(int i = 0; i < sz(s); i++) hsh = (hsh << 7) ^ s[i];

    return abs(hsh);
}

class SymbolInfo{

    string name,type;
    SymbolInfo *next;

public:

    SymbolInfo(){
        next = NULL;
    }

    void set_Info(string n, string t){
        name = n;
        type = t;
    }

    string get_name(){
        return name;
    }

    string get_type(){
        return type;
    }

    void set_next(SymbolInfo *temp){
        next = temp;
    }

    SymbolInfo * get_next(){
        return next;
    }

    ~SymbolInfo(){
        delete next;
    }

};

class ScopeTable{

    int id,N; // N = number of buckets
    SymbolInfo** Hash;
    ScopeTable* parentScope;

public :

    ScopeTable(int n){
        id = curr++;
        N = n;
        Hash = new SymbolInfo*[n];
        parentScope = NULL;

        for(int i=0; i<N; i++)Hash[i] = NULL;
    }

    int get_id(){
        return id;
    }

    void set_parent(ScopeTable * s){
        parentScope = s;
    }

    ScopeTable* get_parent(){
        return parentScope;
    }

    SymbolInfo* Lookup(string name ){

        int idx = Hash_fun(name)%N;

        SymbolInfo *sym = Hash[idx];
        row = idx;
        column = 0;

        while(sym != NULL){
            column++;
            if(sym->get_name() == name)return sym;

            sym = sym->get_next();
        }

        return NULL;
    }

    bool Insert(string name , string type){

        SymbolInfo* is_exist = Lookup(name);

        if(is_exist != NULL){
            cout<<"<"<<name<<" : "<<type<<"> already exists in current ScopeTable\n";
            return false;
        }

        int idx = Hash_fun(name)%N;
        row = idx;
        column = 0;

        SymbolInfo* notun = new SymbolInfo();
        notun->set_Info(name,type);

        if(Hash[idx] == NULL){
            Hash[idx] = notun;
            return true;
        }

        SymbolInfo *sym = Hash[idx] ;

        while(sym->get_next() != NULL){
            sym = sym->get_next();
            column++;
        }

        sym->set_next(notun);

        return true;
    }

    bool Delete(string name){

        SymbolInfo* is_exist = Lookup(name);

        if(is_exist == NULL){
            return false;
        }

        int idx = Hash_fun(name)%N;
        row = idx;
        column = 0;

        if(Hash[idx]->get_name() == name){
            Hash[idx] = Hash[idx]->get_next();
            return true;
        }

        SymbolInfo *sym = Hash[idx];
        SymbolInfo *prev = Hash[idx];

        while(sym->get_name() != name){
            column++;
            prev = sym;
            sym = sym->get_next();
        }

        prev->set_next(sym->get_next());
        delete sym;

        return true;

    }

    void Print(){

        cout<<"ScopeTable # "<<id<<endl;

        for(int i=0; i<N; i++){

            SymbolInfo *sym = Hash[i];
            cout<<i<<" -->  ";

            while(sym != NULL){
                cout<<"<"<<sym->get_name()<<" : "<<sym->get_type()<<">   ";
                sym = sym->get_next();

            }
            cout<<endl;
        }
    }

    ~ScopeTable(){
        if(Hash != NULL)delete Hash;
        if(parentScope != NULL)delete parentScope;
    }

};

class SymbolTable{

    ScopeTable* curr_scop;

public:

    SymbolTable(){
        curr_scop = new ScopeTable(buckets);
    }

    void Enter_Scope(){

        ScopeTable* temp = new ScopeTable(buckets);
        temp->set_parent(curr_scop);
        curr_scop = temp;
        cout<<"New ScopeTable with id "<<(curr-1)<<" created\n";
    }

    void Exit_Scop(){

        if(curr_scop == NULL){
            cout<<"No Scop Found to EXit\n";
            return ;
        }

        curr_scop = curr_scop->get_parent();
        curr--;

        cout<<"ScopeTable with id "<<curr<<" removed\n";

        if(curr_scop == NULL)exit(0);

    }

    bool Insert(string namy, string type){

        bool ret =  curr_scop->Insert(namy , type);

        if(ret) cout<<" Inserted in ScopeTable# "<<curr_scop->get_id()<<" at position "<<row<<","<<column<<endl;

        return ret;
    }

    bool Remove(string namy){

        bool ret = curr_scop->Delete(namy);

        if(ret)cout<<"Deleted entry at "<<row<<","<<column<<" from current ScopeTable\n";
        else cout<<"Not Found\n";

        return ret;
    }

    SymbolInfo* Lookup(string name){

        ScopeTable* temp = curr_scop;

        while(temp != NULL){

            SymbolInfo* sym = temp->Lookup(name);

            if(sym != NULL){
                cout<<"Found in ScopeTable# "<<temp->get_id()<<" at position "<<row<<","<<column<<endl;
                return sym;
            }

            temp = temp->get_parent();
        }

        cout<<"Not Found\n";

        return NULL;
    }

    void Print_Current_ScopeTable(){
        curr_scop->Print();
    }

    void Print_All_ScopeTable(){

        ScopeTable* temp = curr_scop;

        while(temp != NULL){

            temp->Print();

            cout<<"\n\n";

            temp = temp->get_parent();
        }

    }

    ~SymbolTable(){
        if(curr_scop != NULL)delete curr_scop;
    }

};



int main()
{
    ///freopen("debug.txt","w",stdout);
    /*
     ios_base::sync_with_stdio(false);
    cin.tie(0);
    */


    cin>>buckets;

    SymbolTable SymTab;

    while(1){

        char c;
        string name,type;

        cin>>c;


        if(c == '0')break;

        if(c == 'I'){

            cin>>name>>type;

            SymTab.Insert(name,type);
        }

        if(c == 'L'){
            cin>>name;

            SymTab.Lookup(name);
        }

        if(c == 'D'){
            cin>>name;

            SymTab.Remove(name);
        }

        if(c == 'P'){
            char a;
            cin>>a;

            if(a == 'A'){
                    SymTab.Print_All_ScopeTable();
            }
            else SymTab.Print_Current_ScopeTable();
        }

        if(c == 'S'){
            SymTab.Enter_Scope();
        }

        if(c == 'E'){
            SymTab.Exit_Scop();
        }
    }

    return 0;
}
