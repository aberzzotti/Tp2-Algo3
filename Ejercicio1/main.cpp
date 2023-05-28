/* Ejercicio 1 del trabajo practico 2 de la materia algoritmos y estructuras de datos 3
 * Para este ejercicio se tomo como referencia el algoritmo para hayar puentes de
 *https://cp-algorithms.com/graph/bridge-searching.html
 * link que fue tomado de las referencias de las diapos de bgs dfs de la catedra
 */
//Librerias
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
//+++++++++++++++++++++++++++++++++++++++
using namespace std;
typedef long long int tint;
using lista = vector<vector<long long>>;
// Variables Globales
vector<long long> componentSizes;
vector<bool> visited;
vector<long long> tin, low;
long long timer;
lista grafo;
vector<bool> visitado;
struct puente{
    long long u, v;
};
vector<puente> puentes;
//+++++++++++++++++++++++++++++++++++++++
//Funcion que mira si es un puente la arista v to
void is_bridge(long long v, long long to) {
    puentes.push_back({v, to});
}
//+++++++++++++++++++++++++++++++++++++++
//Fucnion que remueve del grafo las aristas puentes
void remove_bridge(long long v, long long to) {
    auto it1 = find(grafo[v].begin(), grafo[v].end(), to);
    if (it1 != grafo[v].end()) {
        grafo[v].erase(it1);
    }

    auto it2 = find(grafo[to].begin(), grafo[to].end(), v);
    if (it2 != grafo[to].end()) {
        grafo[to].erase(it2);
    }
}
//+++++++++++++++++++++++++++++++++++++++
//Funcion que realiza dfs
void dfs(long long v) {
    visited[v] = true;
    ++componentSizes.back();
    for (long long to : grafo[v]) {
        if (!visited[to]) {
            dfs(to);
        }
    }
}
//+++++++++++++++++++++++++++++++++++++++
//Funcion que hace dfs viendo cuando en que momento recorro cada arista
void dfs2(long long v, long long p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    for (long long to : grafo[v]) {
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
//+++++++++++++++++++++++++++++++++++++++
//Funcion que encuentra los puentes del grafo
void find_bridges() {
    long long n = grafo.size();
    timer = 0;
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    for (long long i = 0; i < n; ++i) {
        if (!visited[i])
            dfs2(i);
    }
}

//+++++++++++++++++++++++++++++++++++++++
//Funcion que encuentra las componentes conexas
void findComponents() {
    long long n = grafo.size();
    visited.assign(n, false);
    componentSizes.clear();

    for (long long i = 0; i < n; ++i) {
        if (!visited[i]) {
            componentSizes.push_back(0);
            dfs(i);
        }
    }
}
//+++++++++++++++++++++++++++++++++++++++
//Funcion que arma la lista Ady
void listaAdy( long v,  long w) {
    grafo[v - 1].push_back(w - 1);
    grafo[w - 1].push_back(v - 1);
    grafo[v - 1].resize(grafo[v - 1].size());
    grafo[w - 1].resize(grafo[w - 1].size());
}
//+++++++++++++++++++++++++++++++++++++++
int main() {
    long long n, m;
    cin >> n >> m;
    // Inicializo el grafo
    grafo.resize(n);
    visitado.assign(n, false);
    for (long long i = 0; i < m; i++) {
        long long v, w;
        cin >> v >> w;
        listaAdy(v, w);
    }
    find_bridges();
    for (long long i = 0; i <puentes.size() ; ++i) {
        remove_bridge(puentes[i].u,puentes[i].v);
    }
    findComponents();
//Hago  el calculo de la probabilidad
    tint probaDeGanarX2 = 0;
    tint verticesTotales = 0;
    for (long long size : componentSizes) {
        verticesTotales += size;
        probaDeGanarX2 += size * (size - 1);
    }
    tint opcionesTotales = (verticesTotales * (verticesTotales - 1));
    double probaDePerder = (opcionesTotales - probaDeGanarX2) / (1.0 * opcionesTotales);
    cout << fixed << setprecision(5) << probaDePerder << endl;

    return 0;
}