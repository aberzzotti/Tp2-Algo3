#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <iomanip>
using namespace std;
using lista = vector<vector< long>>;
// Variables Globales
lista grafo;
vector<bool> visitado;
vector<pair< long,  long>> puentes;
 
void imprimirLista( long n) {
    // Imprimo la matriz por filas
    for ( long i = 0; i < n; ++i) {
        for ( long j = 0; j < grafo[i].size(); ++j) {
            cout << grafo[i][j] + 1 << " ";  // Add +1 to prlong long the actual vertex number
        }
        cout << endl;
    }
}
 
vector<bool> visited;
vector< long> tin, low;
 long timer;
 
void is_bridge( long v, long long to) {
    auto it1 = find(grafo[v].begin(), grafo[v].end(), to);
    if (it1 != grafo[v].end()) {
        grafo[v].erase(it1);
    }
 
    auto it2 = find(grafo[to].begin(), grafo[to].end(), v);
    if (it2 != grafo[to].end()) {
        grafo[to].erase(it2);
    }
}
 
void dfs2( long v,  long p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    for ( long to : grafo[v]) {
        if (to == p) continue;
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs2(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v]) {
                is_bridge(v, to);
            }
        }
    }
}
 
void find_bridges() {
     long n = grafo.size();
    timer = 0;
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    for ( long i = 0; i < n; ++i) {
        if (!visited[i])
            dfs2(i);
    }
}
 
void listaAdy( long v,  long w) {
    grafo[v - 1].push_back(w - 1);
    grafo[w - 1].push_back(v - 1);
    grafo[v - 1].resize(grafo[v - 1].size());
    grafo[w - 1].resize(grafo[w - 1].size());
}
 
vector< double> componentSizes;
 
void dfs( long v) {
    visited[v] = true;
    ++componentSizes.back();
    for ( long to : grafo[v]) {
        if (!visited[to]) {
            dfs(to);
        }
    }
}
 
void findComponents() {
     long n = grafo.size();
    visited.assign(n, false);
    componentSizes.clear();
 
    for ( long i = 0; i < n; ++i) {
        if (!visited[i]) {
            componentSizes.push_back(0);
            dfs(i);
        }
    }
}
 
int main() {
     long n, m;
    cin >> n >> m;
    // Inicializo el grafo
    grafo.resize(n);
    visitado.assign(n, false);
    for ( long i = 0; i < m; i++) {
         long v, w;
        cin >> v >> w;
        listaAdy(v, w);
    }
    find_bridges();
 
    findComponents();
 
     double probaDeGanar = 0;
     double verticesTotales = 0;
    for ( double size : componentSizes) {
    	if(size>1){
        verticesTotales += size;
        probaDeGanar += ((size * (size - 1)) / 2);
    	}
    }
 
    probaDeGanar = (1.0*probaDeGanar) / ((verticesTotales * (verticesTotales - 1)) / 2.0);
 
     double probaDePerder = 1 - probaDeGanar;
 
    cout << fixed << setprecision(5) << probaDePerder << endl;
    return 0;
}
