#ifndef RED_H
#define RED_H
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
using namespace std;



class Router
{
private://atributos
    string nombre;
    long long int enlase;//inesesario por que es =0
    map<string,long long int> nombre_;//definimos el mapa toma los valores
    map<string,long long int>::iterator it;//definimos el iterador el saca la info de map

public://metodos
    Router(string,long long int);//hacemos el costructor
    //map<string,long long int> router2();
    map<string,long long int>& router2();


    void agg_enrutadores(string, long long int);//agregamos al mapa lo indicado
    void dltt_enrutadores(string);//eliminamos enrutadores
    void imp_enrutadores();//impimimos(atualizamos) enrutadores
    void imp_enrutadores_nom();//imprimimos las keys
    void cam_enlase_enrutadores(string,long long int);//cambiamos valor de enlace
    //void cam_enlase_enrutadores_red2(string nombre1,string nombre2, long long valor,red& a);//lo usamos para probabilidad intento
    string router_vector();
    list<long long int> router_list();
    vector<long long int>router_list_vt();

};

class red
{
private:
    string nom_red;
    map<string,Router> red_;//definimos el mapa toma los valores
    map<string,Router>::iterator it_red;
    map<string,Router>::iterator it_red2;//definimos el iterador el saca la info de map
    //map<string, Router>* red_=new map<string, Router>;



public:
    //red (string nick);
    void agg_router_red(string);
    void cam_enlase_enrutadores_red(string nombre1,string nombre2, long long valor);
    void dllt_router_red(string);
    void imp_router_red();
    void archivo_router_red(string,red&);
    void algoritmo_dijkstra();
    void aleatorio(red&, string );
    void probabilidad(red&);


};

#endif // RED_H
