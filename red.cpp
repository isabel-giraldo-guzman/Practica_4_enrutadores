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
using namespace std;
bool true_false(int porcentaje);

string numero_string(int numero);
void dijkstra(vector<vector<long long int>> &grafo, long long int origen,map<string,Router> red_,map<string,Router>::iterator it_red);


Router::Router(string _nombre, long long int _enlase)
{
    _enlase=0;
    nombre=_nombre;//le cambiamos el nombre para que sepa que no se refiere al nombre en class
    enlase=_enlase;
    srand(time(NULL));
    agg_enrutadores(_nombre,_enlase);

}

map<string, long long int > &Router::router2()
{
    return nombre_;
}

void Router::agg_enrutadores(string nombre_agg, long long int cost_enlase)
{
    if(nombre_.find(nombre_agg)==nombre_.end()){//verificamos si el nombre no existe
        nombre_.insert(pair<string,long long int>(nombre_agg,cost_enlase));
    }
}

void Router::dltt_enrutadores(string del_nombre)
{
    if(nombre_.find(del_nombre)!=nombre_.end()){

        nombre_.erase(nombre_.find(del_nombre));
    }
}

void Router::imp_enrutadores()
{
    it=nombre_.begin();
    cout<<nombre<<'\t';
    for(long long int itt;itt<nombre_.size();itt++,it++){
        cout<<it->first<<"\t";
    }
    for(it=nombre_.begin(),it=nombre_.begin();it!=nombre_.end();it++){
        cout<< it -> second <<"\t";

    }
    cout<<endl;

}

void Router::imp_enrutadores_nom()
{

    for(it=nombre_.begin(),it=nombre_.begin();it!=nombre_.end();it++){
        cout<< it -> first <<"\t";

    }
    cout<<endl;
}

void Router::cam_enlase_enrutadores(string nombre_mod, long long int num_new)
{
    if(nombre_.find(nombre_mod)!=nombre_.end()){//verificamos si el nombre existe

        nombre_[nombre_mod]= num_new;
    }
}

string Router::router_vector()
{ int x=0;
    long long int z=0;
    for(it=nombre_.begin();it!=nombre_.end();it++,x++);
    string b="",c="";

    for(it=nombre_.begin();it!=nombre_.end();it++){
        z=it->second;
        if(z==-1){z=999;}

        else if(z>9){
            string numerof="",numerof2="";

            for(long long x;z>0;x++){
                if(z==10){numerof="10";
                    numerof2=numerof2+numerof;
                    z=0;}
                else{
                    numerof=(z%10)+48;
                    numerof2=numerof2+numerof;
                    z=z/10;}

            }
            c=c+" "+numerof2;
        }
        else {
            b =(z+48);
            c=c+" "+b;
        }}
    b=c+'\n';
    return b;
}

list <long long int> Router::router_list()
{long long int z=0;
    list<long long int> nombre;
    for(it=nombre_.begin();it!=nombre_.end();it++){
        z=it->second;
        nombre.push_back(z);}
    return nombre;

}

vector<long long> Router::router_list_vt()
{long long int z=0;
    vector<long long int> nombre;
    for(it=nombre_.begin();it!=nombre_.end();it++){
        z=it->second;
        nombre.push_back(z);}
    return nombre;

}

void red::agg_router_red(string nom_agg_red)
{
    Router a(nom_agg_red,0);

    if(red_.find(nom_agg_red)==red_.end()){//miramos si no existe

        for(it_red=red_.begin();it_red!=red_.end();it_red++){
            a.agg_enrutadores(it_red->first,-1);
            it_red->second.agg_enrutadores(nom_agg_red,-1);//agregamos la desconexion en los otros routers
        }
        //a.imp_enrutadores();
        red_.insert(pair<string,Router>(nom_agg_red,a));

        //a.imp_enrutadores();


    }
}
void red::cam_enlase_enrutadores_red(string nombre1,string nombre2, long long valor)
{it_red2=it_red;
    for (it_red = red_.begin(); it_red != red_.end(); ++it_red) {
        if((it_red->first)==nombre1){
            it_red->second.cam_enlase_enrutadores(nombre2,valor);}}
    for(it_red = red_.begin(); it_red != red_.end(); ++it_red){
        if((it_red->first)==nombre2){
            it_red->second.cam_enlase_enrutadores(nombre1,valor);}}
    it_red=it_red2;
}
void red::dllt_router_red(string nom_red_eli)
{it_red=red_.begin();
    if(it_red==red_.end()){cout<<"No tienes Routers"<<'\n';}

    else if(red_.find(nom_red_eli)!=red_.end()){
        Router a(nom_red_eli,0);
        for(it_red=red_.begin();it_red!=red_.end();it_red++){
            //a.dltt_enrutadores(nom_red_eli);
            it_red->second.dltt_enrutadores(nom_red_eli);
        }

        red_.erase(red_.find(nom_red_eli));



    }
}

void red::imp_router_red()
{it_red=red_.begin();
    if(it_red==red_.end()){cout<<"No tiene Routers"<<'\n';}
    else{
        it_red=red_.begin();
        cout<<"RED"<<'\t';
        it_red->second.imp_enrutadores_nom();

        for(it_red=red_.begin();it_red!=red_.end();it_red++){

            it_red->second.imp_enrutadores();

        }
        cout<<endl;}
}

void red::archivo_router_red(string texto,red& open)
{
    string linea,letras;
    stringstream saltos_linea(texto);//esto es una especie de split para separar las letras o caracteres
    long long int cont=0;

    while (getline(saltos_linea, linea, '\n'))
    {
        stringstream grupos(linea);

        while(getline(grupos, letras, ' ')) {
            //cout<<letras<<'\t';
            cont++;
            if(cont%3!=0){
                open.agg_router_red(letras);}
        }

    }
}



void red::algoritmo_dijkstra()
{
    string a="inf",vector_string="";
    list <list<long long int>>lineal;
    vector<vector<long long int>>the_vector;
    for(it_red=red_.begin();it_red!=red_.end();it_red++){
        a=it_red->second.router_vector();
        lineal.push_back(it_red->second.router_list());
        the_vector.push_back(it_red->second.router_list_vt());
        vector_string+=a;
    }

    it_red=red_.begin();
    for(int origen = 0; origen < the_vector.size(); ++origen) {
        //aqui agregamos el nodo de origen cuando nos interese buscar alguno en especidico con un if,agregar nodo fin a la funcion
        cout << "Nodo de origen: " << it_red->first << "\n";

        dijkstra(the_vector, origen,red_,it_red);
        it_red++;
        cout << "\n";
    }
}

void red::aleatorio(red& a, string num3) {

    int num = 0;
    if(num3=="1"){num=rand() % 100 + 1;}
    else{
        cout << "De cuantos routers quiere su red aleatoria" << endl;
        cin >> num;}
    int num2=0;
    int longitud_nombre = ceil(log(num) / log(26));
    if (longitud_nombre <= 26) {
        string letra_random = "";

        while (num > num2) {
            for (int i = 0; i < longitud_nombre; i++) {
                letra_random += (char)(97 + rand() % (26)); // Se agrega cada letra generada al final del string
            }
            //hacer un contador por si sale una letra repetida
            a.agg_router_red(letra_random);
            letra_random = ""; // Se reinicia el string para la siguiente iteración
            num2=0;
            for(a.it_red=a.red_.begin();a.it_red!=a.red_.end();a.it_red++,num2++){}

        }}
    else {
        cout << "La cantidad de routers excede la cantidad de letras disponibles" << endl;
    }

}

void red::probabilidad(red &a)
{

    int x=0;
    cout<<"ingrese la probabilidad de 1 a 100 para la conexion de los routers"<<endl;
    cin>> x;
    long long int costo=0,numero_f=0;
    cout<<"ingrese de cuantos digitos desea el costo de los enlaces"<<endl;
    cin>>costo;
    map<string,long long int> cambio;
    map<string,long long int>::iterator it_router;
    for (a.it_red = a.red_.begin(); a.it_red != a.red_.end(); a.it_red++){
        cambio=(a.it_red->second.router2());


        for (it_router = (cambio).begin(); it_router != (cambio).end(); it_router++){
            //aqui deberia venir el if
            bool resultado = true_false(x);
            if (resultado){
                if(a.it_red->first!=it_router->first){

                    numero_f = (long long int)(rand() % (int)(pow(10, costo) - 1) + 1);

                    a.cam_enlase_enrutadores_red(a.it_red->first,it_router->first,numero_f);
                    numero_f=0;
                }}
        }
        cambio.clear();
    };



}
