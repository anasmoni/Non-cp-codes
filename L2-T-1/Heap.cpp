#include<bits/stdc++.h>
using namespace std;

int *heap;
int sz = 1e6;
int Heap_size=0 , Heap_len=0;

void init(){
    heap = new int[sz];
}

int parent(int i){return i/2;}

int Left(int i){ return 2*i;}

int Right(int i) {return 2*i+1;}

void Max_Heapify(int i){

    int l = Left(i);
    int r = Right(i);
    int big;

    if(l<=Heap_size && heap[i] < heap[l]) big = l;
    else big = i;

    if(r <= Heap_size && heap[r] > heap[big])big = r;

    if(big!=i){
        swap(heap[big],heap[i]);
        Max_Heapify(big);
    }
}

void Build_Max_Heap(){

    Heap_len = Heap_size;

    for(int i=Heap_size/2 ; i>=1 ; i--) Max_Heapify(i);
}

void Heap_Sort(){

    Build_Max_Heap();

    for(int i=Heap_len ; i>1 ; i--){
        swap(heap[1],heap[i]);
        Heap_size--;
        Max_Heapify(1);
    }
    Heap_size = Heap_len;
}

void print_heap(){

    for(int i=1 ; i<=Heap_size ; cout<<heap[i++]<<" ");
    cout<<endl;
}

int Heap_Max(){ return heap[1];}

int Heap_Extract_Max(){

    if(Heap_size<1){cout<<"Empty heap.....\n";return -1;}

    int mx = heap[1];
    heap[1] = heap[Heap_size];
    Heap_size--;
    Max_Heapify(1);
    return mx;

}

void Heap_increase_key(int i, int key){

    if(key<heap[i])return;

    heap[i] = key;

    while(i>1 && heap[parent(i)] < heap[i]){
        swap(heap[parent(i)] , heap[i]);
        i = parent(i);
    }


}

void Max_Heap_insert(int item){

    heap[++Heap_size] = -1e9 ;

    Heap_increase_key(Heap_size , item);
}



int main()
{
   init();

   while(1){

       printf("1. insert. 2.increase. 3.Extract_max. 4.print_heap. 5.max_element.\n");
       printf("6.exit. 7.Heap_sort. 8.Build_max_heap.\n");

       int i; cin>>i;
       if(i==1){
        int item; cin>>item;
        Max_Heap_insert(item);
       }
       else if(i==2){
        int key; cin>>i>>key; Heap_increase_key(i,key);
       }
       else if(i==3){
        cout<<Heap_Extract_Max()<<endl;
       }
       else if(i==4)print_heap();
       else if(i==5)cout<<Heap_Max()<<endl;
       else if(i==6)break;
       else if(i==7)Heap_Sort();
       else if(i==8)Build_Max_Heap();
   }

    return 0;
}
