/* Ejercicio 2 del trabajo parctico 2 de la materia Algortimos y Estructuras de Datos III
 * Para este ejercicio utilizamos el algortimo de Kosaraju , tomando como referencia
 * https://cp-algorithms.com/graph/strongly-connected-components.html
 * el algortimo implemntado en el link de arriba el cual fue sacado de las referencias de las
 * diapositivas de kosraju de la practica de la materia
 *
 */
//Librerias
#include <iostream>;
#include <vector>;
#include <algorithm>
//+++++++++++++++++++++++++++++++++++++++++++
using namespace std;
//Variables Globales
long n, m;
vector<vector<long>> listaAdj, listaRev;
vector<bool> visitado;
vector<long> order, component;
vector<vector<long>> componetes;
vector<long>fichas;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Realizamos dfs desde la lista de adj
void dfs1(long v) {
    visitado[v] = true;

    for (auto u: listaAdj[v]) {
        if (!visitado[u]) {
            dfs1(u);
        }
    }

    order.push_back(v);
}
// Realizamos dfs desde la lista de adj invertida
void dfs2(long v) {
    visitado[v] = true;
    component.push_back(v);

    for (auto u: listaRev[v]){
        if (!visitado[u]){
            dfs2(u);
        }
    }
}
// Nos fijamos si los elementos que tiran a k son de la misma componente o no
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
// Se fija si hay alguna ficha tira la ficha en la que estoy parada
bool NadieMeTira(long k,long i){
    if(listaRev[k].empty() || MismaComponente( k,i)){
        return true;
    }
    return false;
}
void ejercicio2() {
    for (int i = 0; i < n+1; ++i) {
        if(!visitado[i])dfs1(i);
    }
    visitado.assign(n,false);
    //Invierto el orden que quedo cuando recorri dfs la primera vez
    reverse(order.begin(),order.end());
    //Me armo las componentes fuertemente conexas
    for (auto w :order) {
        if(!visitado[w]){
            dfs2(w);
            componetes.push_back(component);
        }
        component.clear();
    }
    visitado.assign(n+1,false);
    //Agrego el numero mas chico de la primer componente conexa y hago dfs desde el mismo
    fichas.push_back(componetes[0][0]);
    dfs1(componetes[0][0]);
    // Para luego ver cuales son los elemntos que no tire y que nadie tira , cosa de agregarlos a mi lista
    for (int i = 1; i <componetes.size() ; ++i) {
        if(componetes[i][0]!=0&&!visitado[componetes[i][0]]&&NadieMeTira(componetes[i][0],i)) {
            fichas.push_back(componetes[i][0]);
        }
    }



}
// Funcion para imprimir la lista de fichas a tirar
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