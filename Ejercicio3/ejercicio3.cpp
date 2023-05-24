#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;
using nodo =tuple<long,long> ;
vector<nodo> nodos;
long CalcularDistancia(nodo x,nodo y){
    return sqrt(pow(get<0>(x)- get<0>(y), 2) +
                pow(get<1>(x)- get<1>(y), 2));//chequear si puedo no hacer raiz
}



pair<long,long> ejercicio3(){

}
int main() {
    long c;
    cin >> c;
    // Inicializo el grafo

    for (long j = 0; j <c ; ++j) {
        int n,e,w,u,v;cin>>n,e,w,u,v;
        nodos.resize(n);
        for (int i = 0; i < n; ++i) {
            int x,y;cin>>x,y;
            nodos.push_back(make_tuple(x,y));
        }

        pair<long,long>res=ejercicio3();
        cout<<"Caso #"<<j<<": "<<res.first<<" "<<res.second<<"\n";
    }


    return 0;
}
