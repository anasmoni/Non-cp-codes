#include<bits/stdc++.h>

using namespace std;

typedef long long int lli;

typedef pair<int,int> pii;
typedef pair<double,double> pdd;
typedef pair<double,int> pdi;

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

#define pr76_dim 76
#define berlin52_dim 52
#define st70_dim 70

#define MAX 111

#define k_cases 5
#define n_cases 10
#define k_best 5

vector<pdd> berlin , pr , st;
bool visited[MAX];

vector<int>Best4Tour_NNH[4] , Best4Tour_SH[4] ;

void Get_Input(){

    ifstream inp;

    inp.open("berlin52.tsp");

    double x,y;

    for(int i=1; i<=berlin52_dim; i++){
        inp>>x>>x>>y;
        berlin.pb({x,y});
    }

    inp.close();

    inp.open("pr76.txt");

    for(int i=1; i<=pr76_dim; i++){
        inp>>x>>x>>y;
        pr.pb({x,y});
    }

    inp.close();

    inp.open("st70.tsp");

    for(int i=1; i<=st70_dim; i++){

        inp>>x>>x>>y;
        st.pb({x,y});
    }
    inp.close();
  //  cout<<pr.size()<<" "<<berlin.size()<<" "<<st.size()<<endl;
}

double Dist(pdd p1 , pdd p2){

    double ret = (p1.fi - p2.fi)*(p1.fi - p2.fi) + (p1.se - p2.se)*(p1.se - p2.se);

    ret = sqrt(ret);

    return ret;
}

///Nearest Neighbour Heuristic (NNH)

int Simple_NNH(vector<pdd>&v){

    set<int>k_starts;

    int s = v.size() , best_start = 0;
    double best_cost = inf;

    while(k_starts.size()<k_cases){
        int r = rand()%s;
        k_starts.insert(r);
    }

    vector<double>costs;

    while(k_starts.size()){

        auto it = k_starts.begin();

        int start = *it;

        k_starts.erase(it);
        Fill(visited , false);
        vector<int>tour;

        int curr = start;
        double tot_dist = 0;

        while(1){

            visited[curr] = true;
            tour.pb(curr);
            int nn = -1;
            double dist = inf;

            for(int i=0; i<v.size(); i++){

                if(visited[i]) continue;

                double d = Dist(v[i] , v[curr]);

                if(dist>d){
                    nn = i;
                    dist = d;
                }
            }

            if(nn == -1){
                tot_dist += Dist(v[start] , v[curr]);
                tour.pb(start);
                break;
            }

            tot_dist += dist;
            curr = nn;
        }

        costs.pb(tot_dist);

        if(tot_dist<best_cost){
            best_cost = tot_dist;
            best_start = start;
            Best4Tour_NNH[0] = tour;
        }
    }

    double average = 0 , best = inf , worst = 0;

    for(double d : costs){
        average += d;
        best = min(d,best);
        worst = max(d,worst);
    }

    average /= k_cases;

    cout<<average<<"\t"<<best<<"\t"<<worst<<"\n\n";

    return best_start;
}

int parent[MAX];
vector<int>Graph[MAX];

void dfs(int now , int p , vector<int>&tour){

    tour.pb(now);

    for(int v : Graph[now]){

        if(v == p) continue;

        dfs(v,now,tour);
    }
}

int Find(int x)
{
    if(x==parent[x])return x;
    return parent[x]=Find(parent[x]);
}

int Simple_SH(vector<pdd>&v){

    set<int>k_starts;

    int s = v.size() , best_start = 0;
    double best_cost = inf;

    while(k_starts.size()<k_cases){
        int r = rand()%s;
        k_starts.insert(r);
    }

    vector<double>costs;
    vector<int>Next(MAX);

    while(k_starts.size()){

        auto it = k_starts.begin();

        int start = *it;
        k_starts.erase(it);

        double tot_dist = 0;
        int edges[MAX];

        Fill(edges,0);
        for(int no = 0 ; no<MAX; no++)Graph[no].clear();

        priority_queue<pair<double,pii> >pq;

        for(int i=0; i<v.size(); i++){

            for(int j=i+1; j<v.size(); j++){

                if(i==start || j == start) continue;

                double s_ij = Dist(v[i],v[start]) + Dist(v[j],v[start]) - Dist(v[i],v[j]);

                pq.push(mp(s_ij,pii(i,j)) );
            }
        }

        for(int no = 0 ; no<v.size(); no++) parent[no] = no;

        while(pq.size()){

            pair<double,pii> p = pq.top();
            pq.pop();

            int i = p.se.fi;
            int j = p.se.se;

            if(Find(i) != Find(j)){
                parent[ parent[i] ] = parent[j];
                Graph[i].pb(j);
                Graph[j].pb(i);
                tot_dist += Dist(v[i],v[j]);
            }
        }
        vector<int>tour;

        for(int i=0; i<v.size(); i++){

            if(i == start)continue;

            if(Find(i) != Find(start)){
                parent[ parent[start] ] = parent[i];

                tot_dist += Dist(v[start],v[i]);

                tour.pb(start);
                dfs(i,-1,tour);
                break;

            }
            //cout<<" ___ "<<tour.size()<<endl;
        }

        tot_dist += Dist(v[start],v[tour.back()]);
        tour.pb(start);

        costs.pb(tot_dist);

        if(tot_dist<best_cost){
            best_cost = tot_dist;
            best_start = start;
            Best4Tour_SH[0] = tour;
        }
    }

    double average = 0 , best = inf , worst = 0;

    for(double d : costs){
        average += d;
        best = min(d,best);
        worst = max(d,worst);
    }

    average /= k_cases;

    cout<<average<<"\t"<<best<<"\t"<<worst<<"\n\n";

    return best_start;
}


void Randomized_NNH(vector<pdd>&v , int start){

    vector<double>costs;

    vector<int>tour[n_cases];
    set<pair<double,int> >tourCosts;

    for(int Case = 1 ; Case<=n_cases ; Case++){

        Fill(visited , false);

        int curr = start;
        double tot_dist = 0;


        while(1){

            visited[curr] = true;
            tour[Case-1].pb(curr);

            priority_queue<pdi>k_nbrs; /// k best neighbors

            for(int i=0; i<v.size(); i++){

                if(visited[i]) continue;

                double d = Dist(v[i] , v[curr]);

                k_nbrs.push({d,i});
            }

            if(k_nbrs.size() == 0)break;

            while(k_nbrs.size()>k_best) k_nbrs.pop();

            int pop_more = rand()%k_nbrs.size();

            while(pop_more--) k_nbrs.pop();

            tot_dist += k_nbrs.top().fi;
            curr = k_nbrs.top().se;
        }
        tour[Case-1].pb(start);
        tourCosts.insert({tot_dist,Case-1});
        costs.pb(tot_dist);
    }

    for(int i=1; i<=3; i++){
        auto it = tourCosts.begin();
        pair<double,int> p = *it;
        Best4Tour_NNH[i] = tour[p.se];
        tourCosts.erase(it);
    }

    double average = 0 , best = inf , worst = 0;

    for(double d : costs){
        average += d;
        best = min(d,best);
        worst = max(d,worst);
    }

    average /= n_cases;

    cout<<average<<"\t"<<best<<"\t"<<worst<<"\n\n";
}

int Randomized_SH(vector<pdd>&v , int start){

    vector<double>costs;
    vector<int>Tours[n_cases];
    set<pair<double,int> >tourCosts;

    for(int Case=1 ; Case<=n_cases; Case++){

        double tot_dist = 0;

        priority_queue<pair<double,pii> >pq;

        for(int i=0; i<v.size(); i++){

            for(int j=i+1; j<v.size(); j++){

                if(i==start || j == start) continue;

                double s_ij = Dist(v[i],v[start]) + Dist(v[j],v[start]) - Dist(v[i],v[j]);

                pq.push(mp(s_ij,pii(i,j)) );
            }
        }

        for(int no = 0 ; no<v.size(); no++) parent[no] = no;
        for(int no = 0 ; no<MAX; no++)Graph[no].clear();

        while(pq.size()){

            int ith = max(1,rand()%k_best);

            pair<double,pii> p;
            vector<pair<double,pii> >tempStore;
            ith = min(ith , (int)pq.size());

            while(ith>1){
                ith--;
                p = pq.top();
                pq.pop();
                tempStore.pb(p);
            }

            p = pq.top();
            pq.pop();

            while(tempStore.size()){
                pq.push(tempStore.back());
                tempStore.pop_back();
            }

            int i = p.se.fi;
            int j = p.se.se;

            if(Find(i) != Find(j)){
                parent[ parent[i] ] = parent[j];
                Graph[i].pb(j);
                Graph[j].pb(i);
                tot_dist += Dist(v[i],v[j]);
            }
        }

        vector<int>tour;

        for(int i=0; i<v.size(); i++){

            if(i == start)continue;

            if(Find(i) != Find(start)){
                parent[ parent[start] ] = parent[i];

                tot_dist += Dist(v[start],v[i]);

                tour.pb(start);
                dfs(i,-1,tour);
                break;

            }
            //cout<<" ___ "<<tour.size()<<endl;
        }

        tot_dist += Dist(v[start],v[tour.back()]);
        tour.pb(start);

        costs.pb(tot_dist);
        Tours[Case-1] = tour;
        tourCosts.insert({tot_dist,Case-1});
    }

    for(int i=1; i<=3; i++){
        auto it = tourCosts.begin();
        pair<double,int> p = *it;
        Best4Tour_SH[i] = Tours[p.se];
        tourCosts.erase(it);
    }

    double average = 0 , best = inf , worst = 0;

    for(double d : costs){
        average += d;
        best = min(d,best);
        worst = max(d,worst);
    }

    average /= n_cases;

    cout<<average<<"\t"<<best<<"\t"<<worst<<"\n\n";
}


int main()
{

    /*
     ios_base::sync_with_stdio(false);
    cin.tie(0);
    */

    //freopen("output.txt","w",stdout);

    Get_Input();

    //cout<<berlin.size()<<" "<<pr.size()<<" "<<st.size()<<endl;;

    int best_start_pr_NNH , best_start_berlin_NNH , best_start_st_NNH;
    int best_start_pr_SH , best_start_berlin_SH , best_start_st_SH;

                                cout<<"\t\t\t\tSimple_NNH : \n\n";

    cout<<"pr76\t\t";
    best_start_pr_NNH = Simple_NNH(pr);

    cout<<"berlin52\t";
    best_start_berlin_NNH = Simple_NNH(berlin);

    cout<<"st70\t\t";
    best_start_st_NNH = Simple_NNH(st);

                                cout<<"\n\t\t\t\tSimple_SH : \n\n";

    cout<<"pr76\t\t";
    best_start_pr_SH = Simple_SH(pr);

    cout<<"berlin52\t";
    best_start_berlin_SH = Simple_SH(berlin);

    cout<<"st70\t\t";
    best_start_st_SH = Simple_SH(st);

                                cout<<"\n\n\t\t\t\tRandomized_NNH : \n\n";

    cout<<"pr76\t\t";
    Randomized_NNH(pr , best_start_pr_NNH);

    cout<<"berlin52\t";
    Randomized_NNH(berlin , best_start_berlin_NNH);

    cout<<"st70\t\t";
    Randomized_NNH(st , best_start_st_NNH);


                                cout<<"\n\n\t\t\t\tRandomized_SH : \n\n";

    cout<<"pr76\t\t";
    Randomized_SH(pr , best_start_pr_SH);

    cout<<"berlin52\t";
    Randomized_SH(berlin , best_start_berlin_SH);

    cout<<"st70\t\t";
    Randomized_SH(st , best_start_st_SH);



    return 0;
}
