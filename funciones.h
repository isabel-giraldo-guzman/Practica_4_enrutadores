#ifndef FUNCIONES_H
#define FUNCIONES_H
#include "funciones.h"
#include "red.h"
//#include "funciones.cpp"
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <fstream>
#include <sstream>
using namespace std;
string leer_texto(string name_texto);
red crear_routers_texto(string texto);
red agregar_datos_texto(red &x, string datos);
long long int string_numeros(string numeros_txt);
void dijkstra(vector<vector<long long int>> &grafo, long long int origen,map<string,Router> red_,map<string,Router>::iterator it_red);
string numero_string(int numero);
red aleatory();
bool true_false(int porcentaje);
red probabilidad(map<string,Router>& a);

void menu();

#endif // FUNCIONES_H
