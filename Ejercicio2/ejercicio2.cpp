//Librerias
#include <iostream>;
#include <vector>;
#include <algorithm>

using namespace std;
//Variables Globales
long n, m;
vector<vector<long>> listaAdj, listaRev;
vector<bool> visitado;
vector<long> order, component;
vector<vector<long>> componetes;
vector<long>fichas;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++
void dfs1(long v) {
    visitado[v] = true;

    for (auto u: listaAdj[v]) {
        if (!visitado[u]) {
            dfs1(u);
        }
    }

    order.push_back(v);
}

void dfs2(long v) {
    visitado[v] = true;
    component.push_back(v);

    for (auto u: listaRev[v]){
        if (!visitado[u]){
            dfs2(u);
        }
    }
}
bool MismaComponente(long k,long i){
    long cant=0;
    for (int j = 0; j <listaRev[k].size() ; ++j) {
        if(find(componetes[i].begin(),componetes[i].end(),listaRev[k][j])!=componetes[i].end()){
            cant++;
        }else{
            return false;
        }
    }
    return true;
}
bool NadieMeTira(long k,long i){
    if(listaRev[k].empty() || MismaComponente( k,i)){
        return true;
    }
    return false;
}
void ejercicio2() {
    //visitado.assign(n+1,false);
    for (int i = 0; i < n+1; ++i) {
        if(!visitado[i])dfs1(i);
    }
    visitado.assign(n,false);
    reverse(order.begin(),order.end());
    for (auto w :order) {
        if(!visitado[w]){
            dfs2(w);
            componetes.push_back(component);
        }
        component.clear();
    }
    visitado.assign(n+1,false);
   /* for (int i = 0; i <componetes.size() ; ++i) {
        if(componetes[i][0]!=0&&NadieMeTira(componetes[i][0],i)){
            dfs1(componetes[i][0]);
            for (int j = 0; j <fichas.size() ; ++j) {
                if(visitado[fichas[j]]){
                    fichas.erase(fichas.begin()+j);
                }
            }
            fichas.push_back(componetes[i][0]);
            visitado.assign(n+1,false);
        }
    }*/
    fichas.push_back(componetes[0][0]);
    dfs1(componetes[0][0]);
    for (int i = 1; i <componetes.size() ; ++i) {
        if(componetes[i][0]!=0&&!visitado[componetes[i][0]]&&NadieMeTira(componetes[i][0],i)) {
            fichas.push_back(componetes[i][0]);
        }
    }



}
void imprimirLista( ) {
    for ( long i = 0; i < fichas.size(); ++i) {
        cout << fichas[i]<< " ";
    }
    cout << endl;
}
int main() {
    cin >> n >> m;
    listaAdj.resize(n+1);
    listaRev.resize(n+1);
    for (int k = 0; k < m; ++k) {
        long i, j;
        cin >> i >> j;
        listaAdj[i].push_back(j);
        listaRev[j].push_back(i);
    }
    visitado.assign(n+1, false);
    ejercicio2();
    cout << fichas.size()<<"\n";
    sort(fichas.begin(),fichas.end());
imprimirLista();
    return 0;

}
