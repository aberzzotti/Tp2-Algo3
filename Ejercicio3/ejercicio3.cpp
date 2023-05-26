#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;
using ll = long long;
using nodo =pair<long,long> ;
//Variables globales
vector<nodo> nodos;
ll c;
double u,v;
long n,r,w;
vector<bool>conectados;
// cada nodo se representa con la posicion en el vector nodos
vector<tuple<ll,long,long>> aristas;
//-------------------------------------------------------
double CalcularDistancia(nodo x,nodo y){
    return pow(x.first-y.first, 2) +
                pow(x.second- y.second, 2);//chequear si puedo no hacer raiz
}
void armarAristas(){
    for (int i = 0; i <nodos.size() ; ++i) {
        for (int j = i; j <nodos.size() ; ++j) {
            if (i==j)continue;
            aristas.push_back(make_tuple( CalcularDistancia(nodos[i],nodos[j]),i,j));
        }
    }
}
struct DSU{

    DSU(long n){
        padre = rank = vector<long>(n);
        for(long v = 0; v < n; v++) padre[v] = v;
    }

    long find(long v){
        if(v == padre[v]) return v;
        return padre[v] = find(padre[v]);
    }

    void unite(long u, long v){
        u = find(u), v = find(v);
        if(u == v) return;
        if(rank[u] < rank[v]) swap(u,v);
        padre[v] = padre[u];
        rank[u] = max(rank[u],rank[v]+1);
    }

    vector<long> padre;
    vector<long> rank;
};

pair<double,double> ejercicio3(){
armarAristas();
DSU dsu(n);
conectados.resize(n,false);
    sort(aristas.begin(),aristas.end());
    double utp = 0;
    double fibra = 0;
    int cantAristas = 0;
    int conect=0;
    for(auto [d,x,y] : aristas){
        //si (u,v) es arista segura
        if(conect==n || cantAristas == n-w)return make_pair(utp,fibra);;
        if(dsu.find(x) != dsu.find(y)){
            // agregar
            dsu.unite(x,y);
            cantAristas++;
                if(r>=sqrt(d)){
                utp+=sqrt(d)*u;
                if(!conectados[x])conect++;
                if(!conectados[y])conect++;
                conectados[x]=true;
                conectados[y]=true;
                }else{
                fibra+=sqrt(d)*v;
                if(!conectados[x])conect++;
                if(!conectados[y])conect++;
                conectados[x]=true;
                conectados[y]=true;
                 }

        }
    }
    if(cantAristas == n-1) {
       return make_pair(utp,fibra);
    }
}
int main() {

    cin >> c;
    // Inicializo el grafo

    for (long j = 0; j <c ; ++j) {
        cin>>n>>r>>w>>u>>v;
        for (int i = 0; i < n; ++i) {
            int x,y;cin>>x>>y;
            nodos.push_back(make_pair(x,y));
        }

        pair<double,double>res=ejercicio3();
        cout<<"Caso #"<<j+1<<": ";
        cout<<fixed << setprecision(3) <<res.first<<" "<<res.second<<"\n";
        nodos.resize(0);
        aristas.resize(0);
        conectados.resize(0);
    }


    return 0;
}
