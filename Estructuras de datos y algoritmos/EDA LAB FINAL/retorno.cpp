#include<iostream>
#include<string.h>
#include "estructuras.h"
#include "cabezales.h"
using namespace std;
bd base_datos = NULL;



void out(tipo_retorno retorno){
	switch (retorno){
	case OK:
		cout << endl << "OK" << endl;
		break;
	case ERROR:
		cout << endl << "ERROR" << endl;
		break;
	case NO_IMPLEMENTADA:
		cout << endl << "NO IMPLEMENTADA" << endl;
		break;
	}
}
	
tipo_retorno _createTable(string nombre_tabla){
	return crearTabla(nombre_tabla,base_datos);
}
tipo_retorno _dropTable(string nombre_tabla){
	return dropTables(base_datos,nombre_tabla);
}
tipo_retorno _add_col(string nombre_tabla,string nombre_col,string tipo_col,string calificador){
	return add_col(nombre_tabla,nombre_col,tipo_col,calificador,base_datos);
}

tipo_retorno _drop_col(string nombre_tabla,string nombre_col){
	return drop_col(nombre_tabla,nombre_col,base_datos);
}
	
tipo_retorno _alter_col(string nombre_tabla, string nombre_col,string tipo_col_nuevo,string calificador_nuevo, string nombre_col_nuevo){
	return alter_col(nombre_tabla,nombre_col,tipo_col_nuevo,calificador_nuevo,nombre_col_nuevo,base_datos);
}

tipo_retorno _insertInto(string nombre_tabla, string columnas_tupla, string valores_tupla){
	return insertarInto(nombre_tabla,columnas_tupla,valores_tupla,base_datos);
}
	
tipo_retorno _deleteTupla(string nombre_tabla, string condiciones){
	return delete_tupla(nombre_tabla,condiciones,base_datos);
}

tipo_retorno _update(string nombre_tabla, string condicion, string nombre_col,string valor){
	return updatear(nombre_tabla,condicion,nombre_col,valor,base_datos);
}

	
tipo_retorno _selectWhere(string nombre_tabla_origen, string condicion,string nombre_tabla_destino){
	return __selectWhere(nombre_tabla_origen,condicion,nombre_tabla_destino,base_datos);
}
	
tipo_retorno _printDataTable(string nombre_tabla,string ordenada_por){
	return print_data_table(nombre_tabla,ordenada_por,base_datos);
}
tipo_retorno _printTables(){
	
	return print_tables(base_datos);
}
tipo_retorno _printMetadata(){
	
	return print_meta_data(base_datos);
}
tipo_retorno _select(string tabla1,string columnas,string tabla2){
	return select(tabla1,columnas,tabla2,base_datos);
}
tipo_retorno _union(string nombre_tabla_1,string nombre_tabla_2,string nombre_tabla_3){
	return _Union(nombre_tabla_1,nombre_tabla_2,nombre_tabla_3,base_datos);
}
tipo_retorno _join(){
	return NO_IMPLEMENTADA;
}
tipo_retorno _intersect(){
	return NO_IMPLEMENTADA;
}
tipo_retorno _minus(){
	return NO_IMPLEMENTADA;
}
tipo_retorno _redo(){
	return NO_IMPLEMENTADA;
}
tipo_retorno _undo(){
	return NO_IMPLEMENTADA;
}
tipo_retorno _beginTransaction(){
	return NO_IMPLEMENTADA;
}
tipo_retorno _endTransaction(){
	return NO_IMPLEMENTADA;
}
