/*
 * Ejercicio 3 del trabajo practico 2 de Algoritmos y Estructuras de Datos III
 * Para este trabajo utilizamos la implementacion de Kruskal dada por el docente Julian Braier ,
 * como guia para luego modificarla en fucnion de la consigna pedida
 */
//Librerias
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <cmath>
//+++++++++++++++++++++++++++++++++++++++++++++++++++
using namespace std;
using ll = long long;
using nodo = pair<long, long>;
//Variables globales
vector<nodo> nodos;
ll c;
double u, v;
long n, r, w;
vector<bool> conectados;
// cada nodo se representa con la posicion en el vector nodos
vector<tuple<ll, long, long>> aristas;

//-------------------------------------------------------
struct DSU {

    DSU(long n) {
        padre = rank = vector<long>(n);
        for (long v = 0; v < n; v++) padre[v] = v;
    }

    long find(long v) {
        if (v == padre[v]) return v;
        return padre[v] = find(padre[v]);
    }

    void unite(long u, long v) {
        u = find(u), v = find(v);
        if (u == v) return;
        if (rank[u] < rank[v]) swap(u, v);
        padre[v] = padre[u];
        rank[u] = max(rank[u], rank[v] + 1);
    }

    vector<long> padre;
    vector<long> rank;
};

//-------------------------------------------------------
// Para el calculo no realizo la raiz ya que si la sqrt(x)<sqrt(y) -> x<y , para no perder presicion hago la raiz despues
double CalcularDistancia(nodo x, nodo y) {
    return pow(x.first - y.first, 2) +
           pow(x.second - y.second, 2);
}
//-------------------------------------------------------
//Me armo el conjunto de aristas que conectan todos mis nodos , tomando como etiqueta de nodo la posicion en el vector nodos
    void armarAristas() {
        for (int i = 0; i < nodos.size(); ++i) {
            for (int j = i; j < nodos.size(); ++j) {
                if (i == j)continue;
                aristas.push_back(make_tuple(CalcularDistancia(nodos[i], nodos[j]), i, j));
            }
        }
    }
//-------------------------------------------------------
    pair<double, double> ejercicio3() {
        armarAristas();
//Creo la estructura DSU que voy a utilizar para Kruskal
        DSU dsu(n);
//Marci todos los nodos como no conectadosd
        conectados.resize(n, false);
//Ordeno las aristas en funcion de la primer componente de la tupla , la cual es la distancia
        sort(aristas.begin(), aristas.end());
        //Declaro algunas variables locales
        double utp = 0;
        double fibra = 0;
        int cantAristas = 0;
        int conect = 0;
        //Arranco a recorrer las aristas ya ordenadas para ir quedandome con las mas pequeñas
        for (auto [d, x, y]: aristas) {
            //En caso de ya haber llegado a tener cantidad de aristas igual a la cantidad de nodos menos los modems es porque
            //ya esdtoy conectando todas las oficionas y las que faltan tendrian los modems
            //De manera similar si tengo todos los nodos conectados no necesito continuar con Kruskal
            if (conect == n || cantAristas == n - w)return make_pair(utp, fibra);;
            if (dsu.find(x) != dsu.find(y)) {
                // agregar
                dsu.unite(x, y);
                cantAristas++;
                //me fijo si tengo la distancia para usar utp o fibra y marco mo conectados esos nodos
                if (r >= sqrt(d)) {
                    utp += sqrt(d) * u;
                    if (!conectados[x])conect++;
                    if (!conectados[y])conect++;
                    conectados[x] = true;
                    conectados[y] = true;
                } else {
                    fibra += sqrt(d) * v;
                    if (!conectados[x])conect++;
                    if (!conectados[y])conect++;
                    conectados[x] = true;
                    conectados[y] = true;
                }

            }
        }
        //En caso de tener el arbol y que no cortara antes , devuelo los valores de utp y fibra
        if (cantAristas == n - 1) {
            return make_pair(utp, fibra);
        }
    }
//-------------------------------------------------------
    int main() {

        cin >> c;
        for (long j = 0; j < c; ++j) {
            cin >> n >> r >> w >> u >> v;
            for (int i = 0; i < n; ++i) {
                int x, y;
                cin >> x >> y;
                nodos.push_back(make_pair(x, y));
            }

            pair<double, double> res = ejercicio3();
            cout << "Caso #" << j + 1 << ": ";
            cout << fixed << setprecision(3) << res.first << " " << res.second << "\n";
            nodos.resize(0);
            aristas.resize(0);
            conectados.resize(0);
        }

        return 0;
    }
