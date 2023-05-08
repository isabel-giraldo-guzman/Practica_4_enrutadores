#include "funciones.h"
#include "red.h"
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <random>


const int INF = 1e9;
using namespace std;
string leer_texto(string name_texto)
{
    string datos;
    char letra;
    unsigned long long tamaño;
        fstream base_de_datos;
    base_de_datos.open(name_texto,ios::in | ios::binary | ios::ate);//parametro de entrada binario y coloca el cursor al final del texto
    if(base_de_datos.is_open()){
        tamaño=base_de_datos.tellg();//toma la longitud de datos hasta donde se encuentra el cursor
        base_de_datos.seekg(0);//colocamos el puntero en la primer posicion
        for(unsigned long long i=0;i<tamaño;i++){

            base_de_datos.get(letra);//asigna a letra el caracter en esa posicion
        if(letra!='\r'){
            datos.push_back(letra);//concatenar letra con letra en datos
        }
    }
}
else {datos = "";cout<<"Error en la Lectura"<<endl;}
base_de_datos.close();
return datos;}
red agregar_datos_texto(red& x,string datos){
    string linea,letras,nombre1,nombre2;
    stringstream saltos_linea(datos);//esto es una especie de split para separar las letras o caracteres
    long long int cont=0,valor=0;
    //red x;
    while (getline(saltos_linea, linea, '\n'))
    //        while (getline(saltos_linea, linea, '\n'))
    {
        stringstream grupos(linea);

        while(getline(grupos, letras, ' ')) {
            cont++;
            if(cont%3==0){valor=string_numeros(letras);
                x.cam_enlase_enrutadores_red(nombre1,nombre2,valor);
                x.cam_enlase_enrutadores_red(nombre2,nombre1,valor);}
            else if(cont%2==0){nombre2=letras;}
            else if(cont%1==0){nombre1=letras;}


        }
        cont=0;

    }
    return x;

}

long long int string_numeros(string numeros_txt){
    long long int numero=0;
    for(long long int x=0;numeros_txt[x]!='\0';x++){
        if(numeros_txt[x]>='0' and numeros_txt[x]<='9'){
            numero=numero*10;
            numero=numero+(numeros_txt[x]-48);
        }
    }
    return numero;
}

void dijkstra(vector<vector<long long int>> &grafo, long long int origen,map<string,Router> red_,map<string,Router>::iterator it_red){
    long long int n = grafo.size();
    vector<long long int> distancia(n, INF);
    vector<long long int> previo(n, -1);
    distancia[origen] = 0;
    priority_queue<pair<long long int,long long int>, vector<pair<long long int,long long int>>, greater<pair<long long int,long long int>>> pq;
    pq.push({0, origen});

    while(!pq.empty()) {
        long long int u = pq.top().second;
        long long int distancia_u = pq.top().first;
        pq.pop();
        if(distancia_u > distancia[u]) continue;
        for(long long int v = 0; v < n; ++v) {
            // if(grafo[u][v] != INF) {
            if(grafo[u][v] != (-1)) {
                long long int distancia_v = distancia[u] + grafo[u][v];
                if(distancia_v < distancia[v]) {
                    distancia[v] = distancia_v;
                    previo[v] = u;
                    pq.push({distancia[v], v});
                }
            }
        }
    }

    map<string,Router>::iterator it_red2;
    it_red2=red_.begin();
    for(long long int v = 0; v < n; ++v,it_red2++) {
        if(v == origen) continue;
        // if(distancia[v] == INF) {
        if(distancia[v] == (1000000000)) {
            cout << "No hay camino desde " << it_red->first<< " hasta " << it_red2->first << "\n";
        } else {
            cout << "El camino mas corto desde " << it_red->first << " hasta " << it_red2->first << " es " << distancia[v] << ": ";
            vector<long long int> camino;
            long long int u = v;
            while(u !=-1){
                camino.push_back(u);
                u = previo[u];
            }


            for(long long int i = camino.size()-1; i >= 0; --i) {

                auto it_red=red_.begin();
                long long int lugar=camino[i];
                advance(it_red,lugar);
                cout<<it_red->first<<" ";
                if(i>0){
                    cout<<"-->";
                }
                // cout << camino[i] << " ";
                //cout<<it
            }
            cout << "\n";
        }
    }
}
void red_matriz(red){

}
string numero_string(long long numero){
    string numerof="";
    for(long long x;numero>0;x++){
        numerof=(numero%10)+48;
        numero=numero/10;
    }
    return numerof;
}
bool true_false(int porcentaje){
    //srand(time(nullptr));
    int num_aleatorio=rand()%101;
    return(num_aleatorio<porcentaje);//aqui miramos lo de la probabilidad y si se cumple retorna un true o false si nno
}
red probabilidad(map<string,Router>& a){

    int x=0;
    cout<<"ingrese la probabilidad de 1 a 100 para la conexion de los routers"<<endl;
    cin>> x;
    long long int costo=0,numero_f;
    cout<<"ingrese de cuantos digitos desea el costo de los enlaces"<<endl;
    cin>>costo;
    map<string,Router>::iterator it_red;
    map<string,Router>::iterator it_red2;
    map<string,long long int> cambio;
    //long long int contador=0;
    map<string,long long int>::iterator it_router;

    for (it_red = a.begin(); it_red != a.end(); it_red++){
        cambio=it_red->second.router2();
        for (it_router = (cambio).begin(); it_router != (cambio).end(); it_router++){
            //aqui deberia venir el if
            bool resultado = true_false(x);
            if (resultado){
                if(it_red->first!=it_router->first){
                    numero_f += (long long int)(rand() % ((10)^costo));
                    it_red->second.cam_enlase_enrutadores(it_router->first,numero_f);
                    numero_f=0;
                }}
        }it_red->second.imp_enrutadores();
    }
}

void menu(){
    string salir="1";
    red a;
    while(salir!="0"){
        cout<<"______Bienvenido______"<<'\n';
        cout<<"Marque 1 para: crear red."<<'\n'<<"Marque 2 para: Cargar Red."<<'\n'<<"Marque 3 para:Generar Red Aleatoria"<<'\n'<<"Marque 0 para: Salir."<<'\n';
        cin>>salir;
        if (salir=="1"){salir="9";
            string primer_red;
            cout<<"ingrese el nombre de la primer red. "<<'\n';
            cin>>primer_red;
            a.agg_router_red(primer_red);
            while(salir!="0"){
                cout<<"Marque 1 para: Agregar enrutadores."<<'\n'<<"Marque 2 para: Eliminar enrutadores."<<'\n'<<"Marque 3 para: Modificar el valor del enlace."<<'\n'<<"Marque 4 para imprimir red"<<'\n'<<"marque 5 para ver el camino mas barato entre routers"<<'\n'<<"Marque 0 para: salir."<<'\n';
                cin>>salir;
                if(salir=="1"){
                    string agregar;
                    cout<<"Ingrese el nombre del router que desea agregar, si ya existe no sera agregado."<<'\n';
                    cin>>agregar;
                    a.agg_router_red(agregar);
                }
                else if(salir=="2"){
                    string eliminar;
                    cout<<"ingrese el nombre del router que desea eliminar"<<'\n';
                    cin>>eliminar;

                    a.dllt_router_red(eliminar);
                }

                else if(salir=="3"){

                    string nombre1,nombre2;
                    long long int enlase;
                    cout<<"Ingrese el nombre del Router 1"<<'\n';
                    cin>>nombre1;
                    cout<<"Ingrese el nombre del Router 2"<<'\n';
                    cin>>nombre2;
                    cout<<"Ingrese el valor del nuevo enlace"<<'\n';
                    cin>>enlase;
                    if(nombre1!=nombre2){
                        a.cam_enlase_enrutadores_red(nombre1,nombre2,enlase);}
                    else{
                        cout<<"No se puede cambiar el valor de enlace consigo mismo, este siempre sera cero."<<'\n';
                    }
                    //  }
                }
                else if(salir=="4"){a.imp_router_red();}
                else if(salir=="5"){a.algoritmo_dijkstra();}

            }
        }
        else if(salir=="2"){salir="9";
            string datos=" ";
            string name_texto;
            while(datos==" "){
                cout<<"Ingrese el nombre del texto incluyendo txt"<<'\n';
                cin>>name_texto;
                datos=leer_texto(name_texto);}
            a.archivo_router_red(datos,a);
            a=agregar_datos_texto(a,datos);
            while(salir!="0"){
                cout<<"Marque 1 para: Agregar enrutadores."<<'\n'<<"Marque 2 para: Eliminar enrutadores."<<'\n'<<"Marque 3 para: Modificar el valor del enlase."<<'\n'<<"Marque 4 para imprimir red"<<'\n'<<"marque 5 para ver el camino mas barato entre routers"<<'\n'<<"Marque 0 para: salir."<<'\n';
                cin>>salir;
                if(salir=="1"){salir="9";
                    string agregar;
                    cout<<"Ingrese el nombre del router que desea agregar, si ya existe no sera agregado."<<'\n';
                    cin>>agregar;
                    a.agg_router_red(agregar);
                }
                else if(salir=="2"){salir="9";
                    string eliminar;
                    cout<<"ingrese el nombre del router a eliminar"<<'\n';
                    cin>>eliminar;

                    a.dllt_router_red(eliminar);
                }

                else if(salir=="3"){salir="9";

                    string nombre1,nombre2;
                    long long int enlase;
                    cout<<"Ingrese el nombre del Router 1"<<'\n';
                    cin>>nombre1;
                    cout<<"Ingrese el nombre del Router 2"<<'\n';
                    cin>>nombre2;
                    cout<<"Ingrese el valor del nuevo enlace"<<'\n';
                    cin>>enlase;
                    if(nombre1!=nombre2){
                        a.cam_enlase_enrutadores_red(nombre1,nombre2,enlase);}
                    else{
                        cout<<"No se puede cambiar el valor de enlace consigo mismo, este siempre sera cero."<<'\n';
                    }

                }
                else if(salir=="4"){a.imp_router_red();salir="9";}
                else if(salir=="5"){a.algoritmo_dijkstra();salir="9";}

            }


        }
        else if(salir=="3"){salir="9";
            string rad="";
            int b=0;
            while(b==0){cout<<"Ingrese 0 para: decidir cuantos routers quiere crear"<<'\n'<<"Marque 1 para:La Cantidad de Routers aleatoria de 1 a 100"<<'\n';
                cin>>rad;
                if((rad=="1")or(rad=="0")){b=99;}
            }
            a.aleatorio(a,rad);
            while(salir!="0"){
                cout<<"Marque 1 para: imrpimir RED"<<'\n'<<"Marque 2 para: Generar enlaces Aleatorios"<<'\n'<<"Marque 3 Para: modificar enlaces"<<'\n'<<"Marque 4 para: ver el camino mas favorable"<<'\n'<<"Marque 0 para: salir."<<'\n';
                cin>>salir;
                if(salir=="1"){
                    a.imp_router_red();}
                else if(salir=="2"){a.probabilidad(a);}
                else if(salir=="3"){
                    string nombre1,nombre2;
                    long long int enlase;
                    cout<<"Ingrese el nombre del Router 1"<<'\n';
                    cin>>nombre1;
                    cout<<"Ingrese el nombre del Router 2"<<'\n';
                    cin>>nombre2;
                    cout<<"Ingrese el valor del nuevo enlace"<<'\n';
                    cin>>enlase;
                    if(nombre1!=nombre2){
                        a.cam_enlase_enrutadores_red(nombre1,nombre2,enlase);}
                    else{
                        cout<<"No se puede cambiar el valor de enlace consigo mismo, este siempre sera cero."<<'\n';
                    }}
                else if(salir=="4"){a.algoritmo_dijkstra();salir="9";}
            }
        }
        else{cout<<"Marcacion incorrecta intente de nuevo"<<'\n';}
    }
}
