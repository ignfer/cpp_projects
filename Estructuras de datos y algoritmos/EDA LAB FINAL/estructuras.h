#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H
#include<iostream>
#include<string.h>
using namespace std;
/*
cada tabla apunta a un indice y cada indice apunta a un campo y cada campo apunta a otro campo (los campos apuntandose entre si representan una tupla)
el indice 0 contiene los campos que son columnas
*/

union dato{
	int entero;
	char texto[20];
};

typedef struct _campo{
	dato valor;
	_campo *sig;
}*c;

typedef struct _columna{
	string nombre;
	string tipo;
	string calificador;
	_campo *tupla;
	_columna *sig;
}*col;

typedef struct _tabla{
	string nombre_tabla;
	_columna *columna; 
}*t;

typedef struct _base_datos{
	_base_datos *tabla_izq; // direccion de la tabla
	_base_datos *tabla_der;
	_base_datos *padre;
	_tabla *tabla;
	string nombre_tabla;
}*bd;

typedef enum _opcion{
	createTable,dropTable,addCol,alterCol,dropCol,insertInto,Delete,update,printDataTable,fin,printTables,selectWhere,Select,Union,printMetadata,Join,intersect,Minus,undo,redo,beginTransaction,endTransaction,NO_RECONOCIDO
}opcion;

typedef enum _retorno{
	OK,ERROR,NO_IMPLEMENTADA
}tipo_retorno;
#endif

