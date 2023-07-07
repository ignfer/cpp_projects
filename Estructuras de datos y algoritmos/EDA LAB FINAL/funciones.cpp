#include<iostream>
#include<string.h>
#include "estructuras.h"
using namespace std;
/*
se hacen modulares la cantidad de if necesarios para saber a que comando hace referencia la entrada del usuario
*/
opcion que_comando(char entrada[]){
	char *nombre_comando;
	nombre_comando = strtok (entrada,"("); //corta la entrada y se queda con la primera parte o sea el nombre del comando
	if(strcmp(nombre_comando,"createTable") == 0){
	return createTable;
	}

	if(strcmp(nombre_comando,"dropTable") == 0){
	return dropTable;
	}

	if(strcmp(nombre_comando,"addCol") == 0){
	return addCol;
	}
	
	if(strcmp(nombre_comando,"alterCol") == 0){
		return 	alterCol;
	}

	if(strcmp(nombre_comando,"dropCol") == 0){
	return dropCol;
	}

	if(strcmp(nombre_comando,"insertInto") == 0){
	return insertInto;
	}

	if(strcmp(nombre_comando,"delete") == 0){
	return Delete;
	}
	
	if(strcmp(nombre_comando,"update") == 0){
		return update;
	}

	if(strcmp(nombre_comando,"printDataTable") == 0){
	return printDataTable;
	}
	
	if(strcmp(nombre_comando,"printTables") == 0){
		return printTables;
	}
	
	if(strcmp(nombre_comando,"selectWhere") == 0){
	return selectWhere;
	}
	if(strcmp(nombre_comando,"select") == 0){
		return Select;
	}
	if(strcmp(nombre_comando,"Union") == 0){
		return Union;
	}
	if(strcmp(nombre_comando,"printMetadata") == 0){
		return printMetadata;
	}
	if(strcmp(nombre_comando,"Join") == 0){
		return Join;
	}
	if(strcmp(nombre_comando,"intersect") == 0){
		return intersect;
	}
	if(strcmp(nombre_comando,"minus") == 0){
		return Minus;
	}
	if(strcmp(nombre_comando,"undo") == 0){
		return undo;
	}
	if(strcmp(nombre_comando,"redo") == 0){
		return redo;
	}
	if(strcmp(nombre_comando,"beginTransaction") == 0){
		return beginTransaction;
	}
	if(strcmp(nombre_comando,"endTransaction") == 0){
		return endTransaction;
	}
	if(strcmp(nombre_comando,"fin") == 0){
		return fin;
	}else{
		return NO_RECONOCIDO;
	}

}

/*
recibe la entrada del usuario y carga en el array (que recibe como segundo parametro) todos los parametros individuales	
*/
void cortar(char entrada[],string parametros[],int cantidad_parametros){
	//!si viene sin parametros da error
	//parametros[] es un array que va a contener todos los parametros ya cortados

	char *comando = entrada; //define un array desde memoria para poder asignarle entrada(because of C)
	char *parametro_individual; //puntero a una cadena de caracteres, cortada de 'comando[]', que es basicamente un parametro

	parametro_individual = strtok (comando,",()"); //array que contiene el texto cortado
	int i = 0;
		while(parametro_individual != NULL && i < cantidad_parametros){
			parametro_individual = strtok(NULL,",()");
			if(parametro_individual == NULL){
				parametros[i] = " ";
				cout << parametros [i] << endl;
			}else{
				parametros[i] = parametro_individual;
			}
			i += 1;
			
		}
}

void cortar_dospuntos(char entrada[],string parametros[],int cantidad_parametros){
	//!si viene sin parametros da error
	//parametros[] es un array que va a contener todos los parametros ya cortados
		
	char *comando = entrada; //define un array desde memoria para poder asignarle entrada(because of C)
	char *parametro_individual = " "; //puntero a una cadena de caracteres, cortada de 'comando[]', que es basicamente un parametro
	parametro_individual = strtok (comando,":"); //array que contiene el texto cortado
	int i = 0;
	
	while(parametro_individual != NULL && i < cantidad_parametros ){

		parametros[i] = parametro_individual;
		parametro_individual = strtok(NULL,":");
		
		i += 1;
		
	}
}
	void cortar_condicion(char entrada[],string parametros[],int cantidad_parametros){
		//!si viene sin parametros da error
		//parametros[] es un array que va a contener todos los parametros ya cortados
		
		char *comando = entrada; //define un array desde memoria para poder asignarle entrada(because of C)
		char *parametro_individual; //puntero a una cadena de caracteres, cortada de 'comando[]', que es basicamente un parametro
		
		parametro_individual = strtok (comando,"><="); //array que contiene el texto cortado
		int i = 0;
		while(parametro_individual != NULL && i < cantidad_parametros){
			
			
			if(parametro_individual == NULL){
				parametros[i] = " ";
				cout << parametros [i] << endl;
			}else{
				parametros[i] = parametro_individual;
			}
			i += 1;
			parametro_individual = strtok(NULL,"><=");
		}
	}
/*!==============================================INICIO AUXILIARES==============================================*/
	
bool parametro_vacio(string nombre_tabla){
	bool respuesta = false;
		if(nombre_tabla == "" || nombre_tabla == " "){ //control si nombre tabla viene vacio
			respuesta = true;
		}
	return respuesta;
}

bool existe_tabla(string nombre_tabla,bd &base_datos){
	
	if(nombre_tabla == base_datos -> tabla -> nombre_tabla){
		return true;
	}else{
		existe_tabla(nombre_tabla , base_datos-> tabla_izq);
		existe_tabla(nombre_tabla , base_datos-> tabla_der);
		return false;
	}
}
bool existe_tabla_en_memoria(bd &base_datos){
	if(base_datos -> tabla){
		return true;
	}else{
		existe_tabla_en_memoria(base_datos-> tabla_izq);
		existe_tabla_en_memoria(base_datos-> tabla_der);
		return false;
	}
}
int cantidad_tablas(bd &base_datos){
		if(base_datos -> tabla){
			return 1 + cantidad_tablas(base_datos -> tabla_izq) + cantidad_tablas(base_datos -> tabla_der);
		}
}
	
string control_calificador(string calificador){
	//funcion que checkea el calificador de columna ingresado
	if(calificador == "PRIMARY KEY"){
		return "PRIMARY_KEY";
	}
	if(calificador ==  "NOT EMPTY"){
		return  "NOT EMPTY";
	}
	if(calificador ==  "ANY"){
		return  "ANY";
	}else{
		return "ERROR";
	}
}
	
string control_tipo(string tipo_col){
	//funcion que checkea el tipo de columna ingresado
	if( tipo_col == "string" ){
		return "string";
	}
	if( tipo_col ==  "integer" ){
		return  "integer";
	}else{
		return "ERROR";
	}
}
	
bool existe_columna(string nombre_col,t &tabla){
	bool respuesta = false;
	
	col respaldo_columna = tabla -> columna; //creo un respaldo del cabezal de columna
		while(tabla -> columna){
			if( tabla -> columna -> nombre == nombre_col){ //si en las columnas existentes se repite el nombre de la que queremos guardar
				//cout<< tabla -> nombre_tabla<<"======"<<nombre_col;
				respuesta = true;
			}
			 tabla -> columna =  tabla -> columna -> sig;
		}
	 tabla -> columna = respaldo_columna; //recupero el cabezal
	return respuesta;
}

	
int contar_tuplas_de_una_tabla(t auxiliar_tabla){
	int cantidad = 0;
	c respaldo_tupla = auxiliar_tabla -> columna -> tupla;
	while(auxiliar_tabla -> columna -> tupla){
		cantidad += 1;
		auxiliar_tabla -> columna -> tupla = auxiliar_tabla -> columna -> tupla -> sig;
	}
	auxiliar_tabla -> columna -> tupla = respaldo_tupla;
	return cantidad;
}
	

int contar_columnas_de_una_tabla(t tabla){
	int cantidad = -1; //siempre creamos indice por defecto pero no nos interesa contarlo como columna por eso arrancamos en -1
	col respaldo_columna = tabla -> columna;
	while(tabla -> columna){
		cantidad += 1;
		tabla -> columna = tabla -> columna -> sig;
		
	}
	tabla -> columna = respaldo_columna;
	return cantidad; 
}


bool es_primary_de_una_tabla(string nombre_col,t tabla){
	bool respuesta = false;
	//respaldo cabezal para no perderlo
	col cabezal_col = tabla -> columna;
	while( tabla -> columna){ //recorro las columnas
		if(tabla -> columna -> nombre == nombre_col){ //si encuentro la columna que estoy buscando, dejo de recorrer
			break;
		}
		 tabla -> columna = tabla -> columna -> sig;
	}
	if(tabla -> columna -> calificador == "PRIMARY KEY"){ //si es primary key devuelvo true
		respuesta = true;
		tabla -> columna = cabezal_col;
		return respuesta;
	}else{ //de lo contrario devuelvo false y recupero el cabezal
		tabla -> columna = cabezal_col; //recupero el cabezal(lo vuelvo a apuntar al principio)
		return respuesta;	
	}
}
	
bool existe_col_de_una_tabla(string nombre_columna,t tabla){
	bool respuesta = false;
	//respaldo cabezal para no perderlo
	col cabezal_col = tabla -> columna;
	//muevo la lista hasta que la siguiente posicion este vacia
	while(tabla -> columna){
		if(tabla -> columna -> nombre == nombre_columna){ //si encuentra una coincidencia, cambia respuesta a verdadero
			respuesta = true;
		}
		tabla -> columna = tabla -> columna -> sig;
	}
	tabla -> columna = cabezal_col; //recupero el cabezal(lo vuelvo a apuntar al principio)
	return respuesta;
}
	
bool esVacio(bd base_datos){
	if(base_datos == NULL){
		return true;
	}
	return false;
}



	
t buscar_tabla(bd base_datos,string nombre_tabla){
	if (!esVacio(base_datos)){
		if(base_datos -> tabla -> nombre_tabla == nombre_tabla)
			return base_datos -> tabla;
		else
			if(strcmp(nombre_tabla.c_str(),(base_datos -> tabla -> nombre_tabla).c_str()) < 0)
			return buscar_tabla(base_datos -> tabla_izq,nombre_tabla);
			else
				return buscar_tabla(base_datos -> tabla_der,nombre_tabla);
	}else{
		return NULL;
	}
}
	
/*!==============================================FIN AUXILIARES==============================================*/
	
	
	
/*!==============================================INICIO IMPLEMENTACIONES==============================================*/
	
tipo_retorno crearTabla(string nombre_tabla,bd &base_datos){
	
	//!==== INICIO CONTROLES ====
	if(parametro_vacio(nombre_tabla)){
		cout << "-Nombre de tabla vacio!" << endl;
		return ERROR;
	}
	if(buscar_tabla(base_datos,nombre_tabla) != NULL){
		cout << "-Tabla ya existente!" << endl;
		return ERROR;
	}
	//!==== FIN CONTROLES ====
	
	t tabla = new _tabla;
	tabla -> nombre_tabla = nombre_tabla;
	
	//!==== INICIO GENERAR INDICE ====
	col columna = new _columna;
	columna -> nombre = "indice";
	columna -> tipo = "integer";
	columna -> calificador = "NOT_EMPTY";
	columna -> tupla = NULL;
	tabla -> columna = columna;
	//!==== FIN GENERAR INDICE ====	
	
	if(esVacio(base_datos)) { //si la base de datos es vacia en el momento de la insercion 
		base_datos = new _base_datos;
		base_datos -> tabla = tabla;
		base_datos -> tabla_izq = NULL;
		base_datos -> tabla_der = NULL;
		base_datos -> padre = NULL;
		
	}else{ //si la base de datos NO es vacia en el momento de la insercion
		if(strcmp(nombre_tabla.c_str(),(base_datos -> tabla -> nombre_tabla).c_str()) > 0) { //pregunta para ordenar por derecha
			crearTabla(nombre_tabla,base_datos -> tabla_der); 
			base_datos -> tabla_der -> padre = base_datos;
		}else{
			if(strcmp(nombre_tabla.c_str(),(base_datos -> tabla -> nombre_tabla).c_str()) < 0) { //pregunta para ordenar por izquierda
				crearTabla(nombre_tabla,base_datos -> tabla_izq);
				base_datos -> tabla_izq -> padre = base_datos;
			}
		}
	}
	base_datos->nombre_tabla = nombre_tabla;
	return OK;
}
	
bd buscar(bd base_datos,string tabla){
	if (!esVacio(base_datos)){
		if(base_datos->tabla->nombre_tabla==tabla)
			return base_datos;
		else
			if(base_datos->tabla->nombre_tabla > tabla)
			return buscar(base_datos->tabla_izq,tabla);
			else
				return buscar(base_datos->tabla_der,tabla);
	}else{
		return NULL;
	}
}

bd _dropTables(bd base_datos,string nombre_tabla){
	if(base_datos == NULL){
		return base_datos;
	}
	if(strcmp(base_datos ->tabla-> nombre_tabla.c_str(), nombre_tabla.c_str())>0){
		base_datos-> tabla_izq = _dropTables(base_datos->tabla_izq,nombre_tabla);
		return base_datos;
	}
	else if(strcmp(base_datos -> tabla->nombre_tabla.c_str() , nombre_tabla.c_str())<0){
		base_datos -> tabla_der = _dropTables(base_datos ->tabla_der,nombre_tabla);
		return base_datos;
	}
	if(base_datos->tabla_izq == NULL){
		bd auxiliar = base_datos->tabla_der;
		delete(base_datos);
		return auxiliar;
	}
	else if(base_datos->tabla_der == NULL){
		bd auxiliar = base_datos->tabla_izq;
		delete(base_datos);
		return auxiliar;
	}else{
		
		bd succParent = base_datos;
		bd succ= base_datos -> tabla_der;
		while(succ ->tabla_izq != NULL){
			succParent = succ;
			succ = succ->tabla_izq;
		}
		
		
		if(succParent != base_datos){
			succParent -> tabla_izq = succ -> tabla_der;
		}else{
			succParent -> tabla_der = succ -> tabla_der;
		}
		base_datos -> nombre_tabla = succ -> nombre_tabla;
		delete(succ);
		delete(base_datos);
	}
}
tipo_retorno dropTables(bd &base_datos, string nombre_tabla){
	base_datos = _dropTables(base_datos,nombre_tabla);
	return OK;
}

tipo_retorno  add_col(string nombre_tabla,string nombre_col,string tipo_col,string calificador,bd &base_datos){
	t auxiliar_tabla = buscar_tabla(base_datos,nombre_tabla);
	//!==== INICIO CONTROLES ====
	if(parametro_vacio(nombre_tabla)){ //control tabla vacio
		cout << "-Nombre tabla no especificado!" << endl;
		return ERROR;
	}
	if(buscar_tabla(base_datos,nombre_tabla) == NULL){ //control que la tabla exista
		cout << "-No existe la tabla especificada!" << endl;
		return ERROR;
	}
	if(parametro_vacio(nombre_col)){ //control columna vacio
		cout << "-Nombre columna no especificado!" << endl;
		return ERROR;
	} 
	if(parametro_vacio(tipo_col)){ //control tipo_col vacio
		cout << "-Tipo columna no especificado!" << endl;
		return ERROR;
	}
	if(existe_columna(nombre_col,auxiliar_tabla)){ //control columna a agregar ya existe
		cout << "-Columna ya existente!" << endl;
		return ERROR;
	}
	
	if(contar_tuplas_de_una_tabla(buscar_tabla(base_datos,nombre_tabla)) > 0){ //control la tabla tiene tuplas y el calificador debe ser ANY
		if(calificador != "ANY"){
			cout << "-La tabla ya contiene tuplas, el tipo de la columna debe ser ANY!" << endl;
			return ERROR;
		}
	}
	//!==== FIN CONTROLES ====

	/*inicializo la columna y le asigno los datos de columna ingresado*/
	col columna = new _columna;
	columna -> nombre = nombre_col;
	columna -> calificador = calificador;
	columna -> tipo = control_tipo(tipo_col);
	
	/*dejo columna apuntando a NULL*/
	columna -> sig = NULL;
	columna -> tupla = NULL;
	
	if(control_tipo(columna -> tipo) == "ERROR"){ //tipo de error el usuario no ingreso un tipo de columna avisado
		cout << "-Tipo de columna ingresado no corresponde!" << endl;
		return ERROR;
	}
	if(control_calificador(columna -> calificador) == "ERROR"){ //tipo de error el usuario no ingreso un tipo de columna avisado
		cout << "-Tipo de columna ingresado no corresponde!" << endl;
		return ERROR;
	}
	
	
	col cabezal_col = auxiliar_tabla -> columna;//me guardo el primer lugar de la lista de columnas(el indice) para dejar el cabezal apuntando a este cuando termine
	//muevo la lista hasta que la siguiente posicion este vacia
	while(auxiliar_tabla -> columna -> sig != NULL){
		auxiliar_tabla -> columna = auxiliar_tabla -> columna -> sig;
	}
	//auxiliar_tabla -> columna = cabezal_col; //lo hago abajo
	auxiliar_tabla -> columna -> sig = columna; //pongo en el ultimo lugar la columna que acabo de crear	
	
	//!============================ INICIO CASO DE TENER QUE RELLENAR VACIO ============================ 
	auxiliar_tabla -> columna = cabezal_col; //recupero el cabezal para el correcto funcionamiento de contar_tuplas
	int cantidad_tuplas = contar_tuplas_de_una_tabla(buscar_tabla(base_datos,nombre_tabla));

	if(cantidad_tuplas > 0){//! en caso de ingresar columnas ya existiendo tuplas, hay que rellenar la nueva columna
		while(auxiliar_tabla -> columna -> sig){ //me paro en la nueva ultima columna
			auxiliar_tabla -> columna = auxiliar_tabla -> columna -> sig;
		}

		for(int i = 0; i < cantidad_tuplas;i++){
			if(tipo_col == "string"){
				c tupla_a_rellenar = new _campo; 
				strcpy(tupla_a_rellenar -> valor.texto,"EMPTY"); //guardo en la tupla a rellenar el valor empty
				tupla_a_rellenar -> sig = auxiliar_tabla -> columna -> tupla;
				auxiliar_tabla -> columna -> tupla = tupla_a_rellenar;
			}
			if(tipo_col == "integer"){
				c tupla_a_rellenar = new _campo; 
				tupla_a_rellenar -> valor.entero = NULL;
				tupla_a_rellenar -> sig = auxiliar_tabla -> columna -> tupla;
				auxiliar_tabla -> columna -> tupla = tupla_a_rellenar;
			}
		}
	}
	//recupero el cabezal(lo vuelvo apuntar al principio)
	auxiliar_tabla -> columna = cabezal_col;
	return OK;
}

tipo_retorno drop_col(string nombre_tabla, string nombre_col, bd &base_datos){
	
	//!==== INICIO CONTROLES ====
	if(parametro_vacio(nombre_tabla)){ //control tabla vacio
		cout << "-Nombre tabla no especificado!" << endl;
		return ERROR;
	}
	if(buscar_tabla(base_datos,nombre_tabla) == NULL){
		cout << "-No existe dicha tabla!" << endl;
		return ERROR;
	}
	if(parametro_vacio(nombre_col)){ //control tabla vacio
		cout << "-Nombre columna no especificado!" << endl;
		return ERROR;
	}
	if(es_primary_de_una_tabla(nombre_col,buscar_tabla(base_datos,nombre_tabla)) && contar_columnas_de_una_tabla(buscar_tabla(base_datos,nombre_tabla)) > 0){
		cout << "-La columna que intenta eliminar es PRIMARY KEY y la tabla tiene mas columnas!" << endl;
		return ERROR;
	}
	//!==== FIN CONTROLES ====

	t auxiliar_tabla = buscar_tabla(base_datos,nombre_tabla);
	col respaldo_columna = auxiliar_tabla -> columna;
		while(auxiliar_tabla -> columna -> sig -> nombre != nombre_col){ //recorre hasta encontrar la columna a eliminar
			auxiliar_tabla -> columna = auxiliar_tabla -> columna -> sig;
		}
			while(auxiliar_tabla -> columna -> sig -> tupla){ //recorro los campos hasta quedarme en la columna previa a la que quiero borrar
				c campo_a_borrar = auxiliar_tabla -> columna -> sig -> tupla; //genero un auxiliar para borrar
				auxiliar_tabla -> columna -> sig -> tupla = campo_a_borrar -> sig; //me muevo al campo siguiente
				delete campo_a_borrar; //borro el campo a borrar
			}
		col columna_a_borrar = 	auxiliar_tabla -> columna -> sig; //apunto a la columna que tengo que borrar una vez vacie las tuplas
		auxiliar_tabla -> columna -> sig = auxiliar_tabla -> columna -> sig -> sig; //engancho las columna previa para que omita la columna que voy a borrar
		auxiliar_tabla -> columna = respaldo_columna; //recupero el cabezal de columna
		delete columna_a_borrar; //finalmente borro la columna y libero el espacio en memoria
	return OK;
}
	


tipo_retorno alter_col(string nombre_tabla, string nombre_col,string tipo_col_nuevo,string calificador_nuevo, string nombre_col_nuevo,bd &base_datos){
	
	//!==== INICIO CONTROLES ====
	if(parametro_vacio(nombre_tabla)){
		cout << "-Nombre tabla no especificado!" << endl;
		return ERROR;
	}
	if(buscar_tabla(base_datos,nombre_tabla) == NULL){ 	//si la tabla no existe devuelve error
		cout << "-Tabla no existente!" << endl;
		return ERROR;
	}
	if(!existe_col_de_una_tabla(nombre_col,buscar_tabla(base_datos,nombre_tabla))){ //si la columna no existe devuelve error
		cout << "-Columna no existente!" << endl;
		return ERROR;
	}
	if(parametro_vacio(nombre_col)){
		cout << "-Nombre columna no especificado!" << endl;
		return ERROR;
	}
	if(es_primary_de_una_tabla(nombre_col,buscar_tabla(base_datos,nombre_tabla))){ 	//si nombre_col es primary key devuelve error
		cout << "-La columna que intenta modificar es PRIMARY KEY!" << endl;
		return ERROR;
	}
	if(control_tipo(tipo_col_nuevo) == "ERROR" ){ 	// que tipo_col_nuevo y calificador_nuevo correspondan
		cout << "-Tipo de columna nuevo no corresponde!" << endl;
		return ERROR;
	}
	if(control_calificador(calificador_nuevo) == "ERROR" ){
		cout << "-Tipo de columna nuevo no corresponde!" << endl;
		return ERROR;
	}
	//!==== FIN CONTROLES ====
	
	t auxiliar_tabla = buscar_tabla(base_datos,nombre_tabla);
	col cabezal_col = auxiliar_tabla -> columna;
	while(auxiliar_tabla -> columna){
		if(auxiliar_tabla -> columna -> nombre == nombre_col){ //si encuentra una coincidencia actualizo la columna
			col columna = auxiliar_tabla -> columna; //por comodidad "abrevio" el nombre
			columna -> nombre = nombre_col_nuevo; //actualizo el nombre
			columna -> calificador = calificador_nuevo; //actualizo el calificador
			columna -> tipo = tipo_col_nuevo; //actualizo el tipo
		}
		auxiliar_tabla -> columna = auxiliar_tabla -> columna -> sig;
	}
	auxiliar_tabla -> columna = cabezal_col; //recupero el cabezal(lo vuelvo a apuntar al principio)
	return OK;
}
	
col traer_columna(string nombre_col,t auxiliar_tabla){ 
	col respaldo = auxiliar_tabla -> columna; //creo un respaldo en la primera columna para volver luego de irme
		while(auxiliar_tabla -> columna -> nombre != nombre_col){ //recorro la lista de columnas hasta encontrar la que le pase por parametro
			auxiliar_tabla -> columna = auxiliar_tabla -> columna -> sig;
		}
	col columna_a_cargar = auxiliar_tabla -> columna; //una vez encontrada cargo la columna en lo que voy a devolver
	auxiliar_tabla -> columna = respaldo; //recupero la referencia
	return columna_a_cargar; //devuelvo la columna a cargar
}
	
bool verificar_primary(string nombre_col,string dato,t auxiliar_tabla){
	col respaldo = auxiliar_tabla -> columna; //creo el respaldo
	bool respuesta = true; //inicializo la respuesta
	
		while(auxiliar_tabla -> columna -> nombre != nombre_col){ //me muevo hasta pararme en la columna que me interesa
			auxiliar_tabla -> columna = auxiliar_tabla -> columna -> sig;
		}
			c respaldo_tupla = auxiliar_tabla -> columna -> tupla; //creo un respaldo de la primera tupla
			while(auxiliar_tabla -> columna -> tupla){ //recorro todas las tuplas
				/*
				en cada tupla pregunto por coincidencias dependiendo de si la columna es de tipo string
				o integer, asi no pregunto dos veces
				*/
				if(auxiliar_tabla -> columna -> tipo == "string"){
					if(auxiliar_tabla -> columna -> tupla -> valor.texto == dato){ //si encuentro una coincidencia devuelvo error
						respuesta = false;
					}
				}
					if(auxiliar_tabla -> columna -> tipo == "integer"){
						if(auxiliar_tabla -> columna -> tupla -> valor.entero == stoi(dato)){ //si encuentro una coincidencia devuelvo error
							respuesta = false;
						}
					}
				auxiliar_tabla -> columna -> tupla = auxiliar_tabla -> columna -> tupla -> sig;
			}
			
	auxiliar_tabla -> columna -> tupla = respaldo_tupla; //respaldo la tupla
	auxiliar_tabla -> columna = respaldo; //respaldo la columna
	return respuesta;
}
void mostrar_tablas(bd base_datos){
	if(!base_datos){
		return;
	}else{
		cout << base_datos -> tabla -> nombre_tabla << endl;
		mostrar_tablas(base_datos -> tabla_izq);
		mostrar_tablas(base_datos -> tabla_der);
	}
}
tipo_retorno insertarInto(string nombre_tabla,string columnas_tupla,string valores_tupla,bd base_datos){
	
	t auxiliar_tabla = buscar_tabla(base_datos,nombre_tabla);

	//declaro los arrays que van a contener los campos de las columnas y los valores ya cortados
	string columnas[20];
	string valores[20];
	//declaro las cadenas de caracteres en las que voy a hacer el parse de las respectivas columnas y valores
	char _columnas_tupla[100]; 
	char _valores_tupla[100]; 
	strcpy(_columnas_tupla,columnas_tupla.c_str()); //hago el parse para las columnas
	strcpy(_valores_tupla,valores_tupla.c_str()); //hago el parse para los valores
	cortar_dospuntos(_columnas_tupla,columnas,20); //corto  columnas_tupla y me las traigo en "columnas"
	cortar_dospuntos(_valores_tupla,valores,20); //corto los valores_tupla y me las traigo en "valores"
	
	//!==== INICIO CONTROLES ====
	
	/*
	recorro 1 a 1 las columnas ya cortadas que se me pasaron por parametros(son maximo 20),
	en cada ciclo voy creando en 'columna_auxiliar' y realizo el control sobre dicho dato
	en caso de que sea primary, pregunto si ese valor ya existe y ademas no este vacio
	en caso de que sea not empty, pregunto solamente si ese valor no esta vacio 
	y en caso de any no realizo control
	
	la funcion traer columna, nos devuelve un dato de tipo columna que corresponde a la columna de la base de datos buscandola solo con su nombre 
	es decir, traer_columna(nombre) nos va a cargar en columna_auxiliar todos los correspondientes datos aunque nosotros le metamos solo el nombre.
	
	la funcion verificar_primary, recorre las tuplas de esa columna y en caso de encontrar un valor 
	repetido devuelve el correspondiente mensaje de error
	
	*/
	
	for(int i = 0; i < 20; i++){ //recorro todas las columnas ingresadas para ir controlandolas
		if(columnas[i] == ""){ //si encuentro una columna vacia me voy
			break;
		}
		
			col columna_auxiliar = traer_columna(columnas[i],auxiliar_tabla);
		
				if(columna_auxiliar -> calificador == "PRIMARY KEY"){ //si la columna del ciclo actual es primary
					if(valores[i] == " " || valores[i] == ""){ //reviso que no este vacio el campo que se le va a insertar
						cout << "-Esta intentando ingresar un campo vacio en un campo clave!"<< endl;
						return ERROR;
					}
					if(!verificar_primary(columnas[i],valores[i],auxiliar_tabla)){ //la reviso, en caso de no haber cumplido la verificacion devuelvo error
						cout << "-Esta intentando ingresar un campo clave repetido!"<< endl;
						return ERROR;
					}
				}
					if(columna_auxiliar -> calificador == "NOT EMPTY"){ //si la columna del ciclo actual es not empty
						if(valores[i] == " " || valores[i] == ""){ //reviso que no este vacio el campo que se le va a insertar
							cout << "-Esta intentando ingresar un campo vacio en un campo que no puede ser vacio!"<< endl;
							return ERROR;
						}
					}
	}
	
	if(!auxiliar_tabla){
		cout << "-ERROR Tabla no encontrada!" << endl;
		return ERROR;
	}
	//!==== FIN CONTROLES ====
	
	
	//!============== INICIO GESTION INDICE ==============
	if(!auxiliar_tabla -> columna -> tupla){
		c campo_a_insertar = new _campo;
		campo_a_insertar -> sig = NULL;
		campo_a_insertar -> valor.entero = 0;
		auxiliar_tabla -> columna -> tupla = campo_a_insertar;
	}else{
		c campo_a_insertar = new _campo;
		campo_a_insertar -> sig = NULL;
		c respaldo_tupla = auxiliar_tabla -> columna -> tupla;
		
			while(auxiliar_tabla -> columna -> tupla -> sig){
				auxiliar_tabla -> columna -> tupla = auxiliar_tabla -> columna -> tupla -> sig;
			}
		
		campo_a_insertar -> valor.entero = auxiliar_tabla -> columna -> tupla -> valor.entero + 1;
		auxiliar_tabla -> columna -> tupla -> sig = campo_a_insertar;
		auxiliar_tabla -> columna -> tupla = respaldo_tupla;
	}
	//!============== FIN GESTION INDICE ==============

	
	//!============== INICIO RELLENAR RESTO DE COLUMNAS ============== 
	int j = 0;
	col respaldo_columna = auxiliar_tabla -> columna;
	auxiliar_tabla -> columna = auxiliar_tabla -> columna -> sig; //apunto a la columna siguiente al indice
	while(auxiliar_tabla -> columna){ //mientras haya tablas
		for (int i = 0; i < 20; i++){
			if (auxiliar_tabla -> columna -> nombre == columnas[i]){ //si la columna en la que estoy es de las que quiero insertar
				/*!===============caso si esta vacia la columna===============*/
				if(auxiliar_tabla -> columna -> tupla == NULL){
					c campo_a_insertar = new _campo;
					if(auxiliar_tabla -> columna -> tipo == "string"){ //si la columna guarda strings, guardo una string
						strcpy(campo_a_insertar -> valor.texto , valores[j].c_str());
					}
					if(auxiliar_tabla -> columna -> tipo == "integer"){ //si la columna guarda integers, guardo un integer
						int auxiliar_entero = 0; //declaro un auxiliar entero
						auxiliar_entero = stoi(valores[j]); //convierto el string a integer para poder guardarlo
						campo_a_insertar -> valor.entero = auxiliar_entero;
					}
					j += 1;
					campo_a_insertar -> sig = NULL;	
					auxiliar_tabla -> columna -> tupla = campo_a_insertar;
				}else{/*!===============caso si NO esta vacia la columna===============*/
					c respaldo_tupla = auxiliar_tabla -> columna -> tupla;
					c campo_a_insertar = new _campo;
					while(auxiliar_tabla -> columna -> tupla -> sig){ //me muevo hasta el ultimo valor cargado de la columna
						auxiliar_tabla -> columna -> tupla = auxiliar_tabla -> columna -> tupla -> sig;
					}
					
					if(auxiliar_tabla -> columna -> tipo == "string"){ //si la columna guarda strings, guardo una string
						strcpy(campo_a_insertar -> valor.texto , valores[j].c_str());
					}
					if(auxiliar_tabla -> columna -> tipo == "integer"){ //si la columna guarda integers, guardo un integer
						campo_a_insertar -> valor.entero = stoi(valores[j]); //convierto el string a integer para poder guardarlo
					}
					
					auxiliar_tabla -> columna -> tupla -> sig = campo_a_insertar; //en el ultimo lugar de la columna guardo el nuevo campo
					campo_a_insertar -> sig = NULL; //ahora apunto el nuevo ultimo lugar a null
					j += 1;
					auxiliar_tabla -> columna -> tupla = respaldo_tupla; //recupero el cabezal
				}
			}
		}
		auxiliar_tabla -> columna = auxiliar_tabla -> columna -> sig;
	}
	//!============== FIN RELLENAR RESTO DE COLUMNAS ============== 
	
	auxiliar_tabla -> columna = respaldo_columna;
	return OK;
}

int condicion_tupla(string condicion){
	int respuesta = -1;
	if(strstr(condicion.c_str(),"<") && strstr(condicion.c_str(),">")){
		//cout << "desigual" << endl; 
		respuesta = 0;
	}
	if(strstr(condicion.c_str(),"=")){
		//cout << "igual" << endl; 
		respuesta = 1;
	}
	if(strstr(condicion.c_str(),">") && !(strstr(condicion.c_str(),"<"))){
		//cout << "mayor que" << endl;
		respuesta = 2;
	}
	if(strstr(condicion.c_str(),"<") && !(strstr(condicion.c_str(),">"))){
		//cout << "menor" << endl; 
		respuesta = 3;
	}
	
	return respuesta;
	
}
void encontrar_columna(t &tabla,string condicion){
	while(tabla -> columna -> nombre != condicion && tabla -> columna != NULL){
		tabla -> columna = tabla -> columna -> sig;
	}
}

int indice_a_borrar(bd &base_datos, string condicion, int tipo_borrado,int cantidad_de_indice_a_saltear,t auxiliar_tabla) {

	/*
	tipo_borrado nos define que pregunta vamos a hacer es decir, si vamos a buscar valores mayores, 
	menores, o diferentes
	*/
	
	int j = cantidad_de_indice_a_saltear;
	int cantidad_tuplas = contar_tuplas_de_una_tabla(auxiliar_tabla);
	c cabezal_tupla = NULL;
	col cabezal_columna = NULL;
	//le resto al for los indices a saltear de manera que no haga iteraciones de mas y se rompa todo.
	for (int k = 0; k<cantidad_tuplas-cantidad_de_indice_a_saltear;k++){
		
		cabezal_tupla = auxiliar_tabla -> columna -> tupla;
		string tipo_dato_de_columna = auxiliar_tabla -> columna -> tipo;
		for(int i = 0;i<j;i++){
			auxiliar_tabla -> columna -> tupla = auxiliar_tabla -> columna -> tupla ->sig;
		}
		//!================= INICIO CASO BORRAR POR DIFERENCIA =================  
		if(tipo_borrado == 0){ //caso borrar por diferencia
			if(tipo_dato_de_columna == "integer"){ //caso borrar por diferencia de enteros
				if(auxiliar_tabla  -> columna -> tupla -> valor.entero != stoi(condicion)){
					
				}else{
					j += 1;
				}
			}
			if(tipo_dato_de_columna == "string"){ //caso borrar por diferencia de strings
				if(auxiliar_tabla  -> columna -> tupla -> valor.texto != condicion){
					
				}else{
					j += 1;
				}
			}
			auxiliar_tabla -> columna -> tupla = cabezal_tupla;
		}
		//!================= FIN CASO BORRAR POR DIFERENCIA =================
		
		//!================= INICIO CASO BORRAR POR IGUALDAD =================  
		if(tipo_borrado == 1){ //caso borrar por igualdad
			if(tipo_dato_de_columna == "integer"){ //caso borrar por igualdad de enteros
				if(auxiliar_tabla  -> columna -> tupla -> valor.entero == stoi(condicion)){
					
				}else{
					j += 1;
				}
			}
			if(tipo_dato_de_columna == "string"){ //caso borrar por igualdad de strings
				if(auxiliar_tabla -> columna -> tupla -> valor.texto == condicion){
					
				}else{
					j += 1;
				}
			}
			auxiliar_tabla -> columna -> tupla = cabezal_tupla;
		}
		//!================= FIN CASO BORRAR POR IGUALDAD =================
		
		//!================= INICIO CASO BORRAR POR MAYOR QUE =================  
		if(tipo_borrado == 2){ //caso borrar por mayor que
			if(tipo_dato_de_columna == "integer"){ //caso borrar por mayor que de enteros
				if(auxiliar_tabla  -> columna -> tupla -> valor.entero > stoi(condicion)){
					
				}else{
					j += 1;
				}
			}
			if(tipo_dato_de_columna == "string"){ //caso borrar por mayor que de strings
					string campo = auxiliar_tabla  -> columna -> tupla -> valor.texto;
					int comparacion = campo.compare(condicion);
					if(comparacion < 0){
						
					}else{
						j += 1;
					}		
			}
			auxiliar_tabla -> columna -> tupla = cabezal_tupla;
		}
		//!================= FIN CASO BORRAR POR MAYOR QUE=================
		
		//!================= INICIO CASO BORRAR POR MENOR QUE =================  
		if(tipo_borrado == 3){ //caso borrar por menor que
			if(tipo_dato_de_columna == "integer"){ //caso borrar por menor que de enteros
				if(auxiliar_tabla  -> columna -> tupla -> valor.entero < stoi(condicion)){
					
				}else{
					j += 1;
				}
			}
			if(tipo_dato_de_columna == "string"){ //caso borrar por menor que de strings
				string campo = auxiliar_tabla  -> columna -> tupla -> valor.texto;
				int comparacion = campo.compare(condicion);
				if(comparacion > 0){
					
				}else{
					j += 1;
				}		
			}
			auxiliar_tabla -> columna -> tupla = cabezal_tupla;
		}
		//!================= FIN CASO BORRAR POR MENOR QUE=================
		
	}
	auxiliar_tabla -> columna = cabezal_columna;
	//base_datos -> tablas -> columna -> tupla = cabezal_tupla;
	return j;
}

c borrar_recursivo(c campo, int indice){
	if(indice < 0){
		return campo;
	}
	if (campo == NULL){
		return NULL;
	}
	if(indice == 0){
		c aux_siguiente = campo->sig;
		delete(campo);
		return aux_siguiente;
	}
	campo -> sig = borrar_recursivo(campo -> sig, indice-1);
	return campo;
}	

tipo_retorno delete_tupla(string nombre_tabla, string condiciones, bd &base_datos){
	
	t auxiliar_tabla = buscar_tabla(base_datos,nombre_tabla);
	
	string condiciones_cortadas[20]; //array de strings que contendra las condiciones previamente cortadas
	char _condiciones[100]; //recibe el parse del parametro 'condiciones'
	t tabla = auxiliar_tabla; //renombro para acortar tiempo
	col cabezal_columna = tabla -> columna; //respaldo la primera columna
	c cabezal_tupla = tabla -> columna -> tupla; //respaldo la primera tupla
	
	strcpy(_condiciones,condiciones.c_str()); //guardo 'condiciones' que viene por parametro en '_condiciones' que declare arriba
	cortar_condicion(_condiciones,condiciones_cortadas,20); //corto  '_condiciones' y me las traigo en 'condiciones_cortadas'
	/*
	entramos al siguiente if en caso de que la condicion sea <>, = , < , >
	cada operacion le corresponde un valor numerico del 0 al 3
	*/
	if(condicion_tupla(condiciones) == 0 || condicion_tupla(condiciones) == 1 || condicion_tupla(condiciones) == 2 || condicion_tupla(condiciones) == 3){ 
		/*
		la justificacion del siguiente for es que si lo que queremos borrar esta en mas de 1 tupla, 
		tendriamos que volver a ejecutar el comando, es decir borrariamos de a 1 coincidencia, repitiendo
		la operacion l veces donde l es la cantidad de tuplas de la tabla, cubrimos todos los posibles
		casos de repeticion incluso si todas las tuplas cuentan con el valor que queremos buscar
		*/
		int tope = contar_tuplas_de_una_tabla(auxiliar_tabla); //guardo la primera vez la cantidad de tuplas ya que si lo guardo en el for, se actualiza con cada eliminacion y nunca borra la ultima tupla
		for(int l = 0; l <= tope;l++){
			encontrar_columna(tabla,condiciones_cortadas[0]); //encuentro la columna dado su nombre
			
			int j = indice_a_borrar(base_datos,condiciones_cortadas[1],condicion_tupla(condiciones),0,auxiliar_tabla); //que tanto tengo que bajar en cada columna
			auxiliar_tabla  -> columna = cabezal_columna;
			int cantidad_columnas = contar_columnas_de_una_tabla(auxiliar_tabla);
			tabla -> columna = cabezal_columna;
			
			for(int i = 0; i<=cantidad_columnas;i++){
				tabla-> columna -> tupla = borrar_recursivo(tabla -> columna -> tupla,j);
				tabla -> columna = tabla -> columna -> sig;
			}
			tabla -> columna = cabezal_columna;
		}
	}
	return OK;
	
}

c updatear_recursivo(c campo, int indice,string valor,string tipo_dato){
	if(indice < 0){
		return campo;
	}
	if (campo == NULL){
		return NULL;
	}
	if(indice == 0){
		if(tipo_dato == "string"){
			strcpy(campo -> valor.texto,valor.c_str());	
		}
		if(tipo_dato == "integer"){
			campo -> valor.entero = stoi(valor);
		}
		return campo;
	}
	campo -> sig = updatear_recursivo(campo -> sig, indice-1,valor,tipo_dato);
	return campo;
}
	
tipo_retorno updatear(string nombre_tabla, string condiciones, string nombre_col,string valor,bd &base_datos){
	
	t auxiliar_tabla = buscar_tabla(base_datos,nombre_tabla);
	
	if(parametro_vacio(nombre_tabla)){
		cout << "-Nombre tabla no especificado!" << endl;
		return ERROR;
	}
	
	string condiciones_cortadas[20]; //array de strings que contendra las condiciones previamente cortadas
	char _condiciones[100]; //recibe el parse del parametro 'condiciones'
	t tabla = auxiliar_tabla; //renombro para acortar tiempo
	col cabezal_columna = tabla -> columna; //respaldo la primera columna
	c cabezal_tupla = tabla -> columna -> tupla; //respaldo la primera tupla
	
	strcpy(_condiciones,condiciones.c_str()); //guardo 'condiciones' que viene por parametro en '_condiciones' que declare arriba
	cortar_condicion(_condiciones,condiciones_cortadas,20); //corto  '_condiciones' y me las traigo en 'condiciones_cortadas'
	/*
	analogo al delete 
	*/
	//cout << "donde " << condiciones_cortadas[0] << "(" << condicion_tupla(condiciones) << ")" << condiciones_cortadas[1] << " hacer que " << nombre_col << " = " << valor << endl;
	if(condicion_tupla(condiciones) == 0 || condicion_tupla(condiciones) == 1 || condicion_tupla(condiciones) == 2 || condicion_tupla(condiciones) == 3){ 
		/*
		analogo al delete 
		*/
		int tope = contar_tuplas_de_una_tabla(auxiliar_tabla); //guardo la primera vez la cantidad de tuplas ya que si lo guardo en el for, se actualiza con cada eliminacion y nunca borra la ultima tupla
		for(int l = 0; l < tope;l++){
			encontrar_columna(tabla,condiciones_cortadas[0]); //encuentro la columna dado su nombre
			int j = indice_a_borrar(base_datos,condiciones_cortadas[1],condicion_tupla(condiciones),l,auxiliar_tabla); //que tanto tengo que bajar en cada columna
			auxiliar_tabla -> columna = cabezal_columna;
			tabla -> columna = cabezal_columna;
			encontrar_columna(tabla,nombre_col); //me muevo a la columna a cambiar
			tabla -> columna -> tupla = updatear_recursivo(tabla -> columna -> tupla,j,valor,tabla -> columna -> tipo);//hago el cambio
			//encontrar_columna(tabla,condiciones_cortadas[0]);
			tabla -> columna = cabezal_columna;
		}
		tabla -> columna = cabezal_columna;
		tabla -> columna -> tupla = cabezal_tupla;
	}
	/*!le agrega a la funcion de indice a borrar un campo que indica el numero de tuplas que quieres que se saltee,que en este caso
	como va aumentando por iteracion puse la misma variable l, despues lo que hice en indice_a_borrar es que a j de entrada le sumo
	el numero de variables que quiero que saltee asi si se llama a la funcion con el numero de campos a saltear siendo 1 va a saltearse siempre el primer campo
	y va a empezar desde el segundo campo y asi.*/
	return OK;
}
	
tipo_retorno insertar_coincidencias(t auxiliar_tabla,int j,bd base_datos,string nombre_tabla){
	
	//!======= INICIO CONSEGUIR TUPLAS ======= 
	
	col respaldo_columna = auxiliar_tabla -> columna;
	int iteracion = 0;
	
	string argumentos_columna[20];
	string argumentos_tupla[20];
	
	while(auxiliar_tabla -> columna){ //BUCLE X
		c respaldo_tupla = auxiliar_tabla -> columna -> tupla;
		for(int k = 0; k < j; k++){ //BUCLE Y MUEVO Y
			auxiliar_tabla -> columna -> tupla = auxiliar_tabla -> columna -> tupla -> sig;
		}
			if(auxiliar_tabla -> columna -> tipo == "integer"){
				argumentos_tupla[iteracion] = to_string(auxiliar_tabla -> columna -> tupla -> valor.entero);
			}
				if(auxiliar_tabla -> columna -> tipo == "string"){
					argumentos_tupla[iteracion] = auxiliar_tabla -> columna -> tupla -> valor.texto;
				}
				
		auxiliar_tabla -> columna -> tupla = respaldo_tupla; //RECUPERO Y
		
		argumentos_columna[iteracion] = auxiliar_tabla -> columna -> nombre;
		iteracion += 1;
		
		auxiliar_tabla -> columna = auxiliar_tabla -> columna -> sig; //MUEVO X
	}
	
	auxiliar_tabla -> columna = respaldo_columna; //RECUPERO X
	
	
	//!======= FIN CONSEGUIR TUPLAS ======= 
	
	bool seguir = true;
	
	auxiliar_tabla = buscar_tabla(base_datos,nombre_tabla);
	
	for(int i = 0; i < 20; i++){ //!EVITO INSERTAR REPETIDOS
		if(argumentos_columna[i] == ""){ //si encuentro una columna vacia me voy
			break;
		}
		col columna_auxiliar = traer_columna(argumentos_columna[i],auxiliar_tabla);
			if(columna_auxiliar -> calificador == "PRIMARY KEY"){
				if(!verificar_primary(argumentos_columna[i],argumentos_tupla[i],auxiliar_tabla)){ //la reviso, en caso de no haber cumplido la verificacion devuelvo error
					seguir = false;
				}
			}
	}
	
	
	//!======= INICIO INSERCION ======= 
	
	int i = 0;
	while(argumentos_columna[i] != "" && seguir){
		//cout << argumentos_columna[i];
		t auxiliar_tabla = buscar_tabla(base_datos,nombre_tabla);
		col respaldo_columna = auxiliar_tabla -> columna;
			
			for(int j = 0; j < i; j++){
				auxiliar_tabla -> columna = auxiliar_tabla -> columna -> sig;
			}
			
		c campo_a_insertar = new _campo;
			if(auxiliar_tabla -> columna -> tipo == "string"){
				strcpy(campo_a_insertar -> valor.texto,argumentos_tupla[i].c_str());
			}
				if(auxiliar_tabla -> columna -> tipo == "integer"){
					campo_a_insertar -> valor.entero = stoi(argumentos_tupla[i].c_str());
				}
				
			campo_a_insertar -> sig = auxiliar_tabla -> columna -> tupla;
			auxiliar_tabla -> columna -> tupla = campo_a_insertar;	
			
			auxiliar_tabla -> columna = respaldo_columna;
			i += 1;
		
	}
	
	//!======= FIN INSERCION ======= 
	
	
	
}
tipo_retorno __selectWhere(string nombre_tabla_origen,string condiciones,string nombre_tabla_destino,bd &base_datos){
	
	//!==== INICIO CONTROLES ====
	
	if(parametro_vacio(nombre_tabla_origen)){
		cout << "-Nombre de tabla1 no especificado!" << endl;
		return ERROR;
	}
	if(buscar_tabla(base_datos,nombre_tabla_origen) == NULL){
		cout << "-Tabla1 no existente!" << endl;
		return ERROR;
	}
	if(buscar_tabla(base_datos,nombre_tabla_destino) != NULL){
		cout << "-Tabla2 ya existente!" << endl;
		return ERROR;
	}
	
	//!==== FIN CONTROLES ====
	
	
	t auxiliar_tabla = buscar_tabla(base_datos,nombre_tabla_origen);
	
	string condiciones_cortadas[20]; //array de strings que contendra las condiciones previamente cortadas
	char _condiciones[100]; //recibe el parse del parametro 'condiciones'
	
	col respaldo_columna = auxiliar_tabla -> columna; //respaldo la primera columna
	c cabezal_tupla = auxiliar_tabla -> columna -> tupla; //respaldo la primera tupla
	
	strcpy(_condiciones,condiciones.c_str()); //guardo 'condiciones' que viene por parametro en '_condiciones' que declare arriba
	cortar_condicion(_condiciones,condiciones_cortadas,20); //corto  '_condiciones' y me las traigo en 'condiciones_cortadas'
	
	//!==== INICIO CREO LA TABLA DESTINO ====
	crearTabla(nombre_tabla_destino,base_datos);
	while(auxiliar_tabla -> columna){ //le añado las columnas de la tabla origen a la tabla destino
		add_col(nombre_tabla_destino,auxiliar_tabla -> columna -> nombre,auxiliar_tabla -> columna -> tipo,auxiliar_tabla -> columna -> calificador,base_datos);
		auxiliar_tabla -> columna = auxiliar_tabla -> columna -> sig;
	}
	cout << endl;
	auxiliar_tabla -> columna = respaldo_columna;
	
	//!==== FIN CREO LA TABLA DESTINO ====
	
	
	if(parametro_vacio(condiciones)){ //!CASO SELECT * 
		
		int tope = contar_tuplas_de_una_tabla(auxiliar_tabla); //guardo la primera vez la cantidad de tuplas ya que si lo guardo en el for, se actualiza con cada eliminacion y nunca borra la ultima tupla
		for(int l = 0; l <= tope;l++){
			int j = l;
			auxiliar_tabla  -> columna = respaldo_columna;
			int cantidad_columnas = contar_columnas_de_una_tabla(auxiliar_tabla);
			auxiliar_tabla -> columna = respaldo_columna;
			if(j < tope){
				insertar_coincidencias(auxiliar_tabla,j,base_datos,nombre_tabla_destino);
			}
			cout << endl;
			auxiliar_tabla -> columna = respaldo_columna;
		}
		return OK;
	}
	
	if(condicion_tupla(condiciones) == 0 || condicion_tupla(condiciones) == 1 || condicion_tupla(condiciones) == 2 || condicion_tupla(condiciones) == 3){ 
		
		int tope = contar_tuplas_de_una_tabla(auxiliar_tabla); //guardo la primera vez la cantidad de tuplas ya que si lo guardo en el for, se actualiza con cada eliminacion y nunca borra la ultima tupla
		for(int l = 0; l <= tope;l++){
			encontrar_columna(auxiliar_tabla,condiciones_cortadas[0]); //encuentro la columna dado su nombre
			
			int j = indice_a_borrar(base_datos,condiciones_cortadas[1],condicion_tupla(condiciones),l,auxiliar_tabla); //que tanto tengo que bajar en cada columna
			auxiliar_tabla  -> columna = respaldo_columna;
			int cantidad_columnas = contar_columnas_de_una_tabla(auxiliar_tabla);
			auxiliar_tabla -> columna = respaldo_columna;
			
				if(j < tope){
						insertar_coincidencias(auxiliar_tabla,j,base_datos,nombre_tabla_destino);
				}
				
			cout << endl;
			auxiliar_tabla -> columna = respaldo_columna;
		}
	}
	return OK;
	
}
tipo_retorno print_data_table(string nombre_tabla, string ordenada_por,bd &base_datos){
	
	//!==== INICIO CONTROLES ====
	
	if(parametro_vacio(nombre_tabla)){ //control tabla vacio
		cout << "-Nombre tabla no especificado!" << endl;
		return ERROR;
	}
	if(!existe_tabla_en_memoria(base_datos)){
		cout << "-No existe la tabla especificada!" << endl;
		return ERROR;
	}
	if(buscar_tabla(base_datos,nombre_tabla) == NULL){ //control que la tabla exista
		cout << "-No existe la tabla especificada!" << endl;
		return ERROR;
	}
	
	//!==== FIN CONTROLES ====
	
	
	t auxiliar_tabla = buscar_tabla(base_datos,nombre_tabla); //mando a buscar la tabla con el nombre tabla que se me pasa por parametro
	col cabezal_col = auxiliar_tabla -> columna; //respaldo columna
	
	cout<<"================="<< auxiliar_tabla -> nombre_tabla <<"================="<<endl;
	//imprimo los nombres de las columnas
	
	while(auxiliar_tabla -> columna){
		cout<<(auxiliar_tabla -> columna -> nombre)<<":";
		auxiliar_tabla -> columna = auxiliar_tabla -> columna -> sig;
	}
	cout << endl;

	auxiliar_tabla -> columna = cabezal_col;

	//la j la declaro afuera del while por que no quiero que se resetee en lo que imprimo las tuplas
	int j = 0;
	int cantidad_tuplas = 0;
	cantidad_tuplas = contar_tuplas_de_una_tabla(auxiliar_tabla);
	
	//ciclo el for hasta la ultima tupla que seria la cantidad de tuplas que tengo
	for (int k = 0; k < cantidad_tuplas;k++){
		//me paro en la primer columna (indice)
		while(auxiliar_tabla -> columna){
			//me guardo la primer tupla para despues devolverla  a su lugar
			c cabezal_tupla = auxiliar_tabla -> columna -> tupla;
			//por cada linea que imprimo voy aumentando el numero de veces que baja
				for(int i = 0;i<j;i++){
					auxiliar_tabla -> columna -> tupla = auxiliar_tabla-> columna -> tupla ->sig;
				}
					//imprimo el contenido de la tupla
					if(auxiliar_tabla -> columna -> tipo == "string"){
						cout<<(auxiliar_tabla -> columna -> tupla -> valor.texto)<<":";
					}
						if(auxiliar_tabla -> columna -> tipo == "integer"){
							cout<<(auxiliar_tabla -> columna -> tupla -> valor.entero)<<":";
						}
							//devuelvo la tupla a su lugar y me muevo a la siguiente columna
							auxiliar_tabla -> columna -> tupla = cabezal_tupla;
							auxiliar_tabla -> columna = auxiliar_tabla -> columna -> sig;
		}
		
		//como ya imprimi una tupla ej la tupla 1 ahora j incrementa para imprimir la tupla 2
		j += 1;
		cout<<endl;
		//y como ya cicle todas las primeras tuplas de todas las columnas vuelvo a la primer columna
		//para ciclar todas las segundas tuplas y asi hasta el numero maximo de tuplas
		auxiliar_tabla -> columna = cabezal_col;
	}
	auxiliar_tabla -> columna = cabezal_col;
	cout << endl;

	return OK;
}
tipo_retorno print_tables(bd base_datos){
	if (base_datos  == NULL){
		return OK;
	}else{
		cout<<"+"<<base_datos -> tabla -> nombre_tabla<<"+"<<endl;
		return print_tables(base_datos -> tabla_der);
		return print_tables(base_datos -> tabla_izq);
	}
}
void print_meta_data_columna(col columna){
	col aux_columna = columna;
	while(columna){
		cout<<"--"<<columna -> nombre<<"-"<<columna -> tipo<<"-"<<columna -> calificador<<endl;
		columna = columna -> sig;
	}
	columna = aux_columna;
}
tipo_retorno print_meta_data(bd base_datos){
	if (base_datos  == NULL){
		return OK;
	}else{
		cout<<"+"<<base_datos -> tabla -> nombre_tabla<<endl;
		print_meta_data_columna(base_datos -> tabla->columna);
		cout<<endl;
		return print_meta_data(base_datos -> tabla_der);
		return print_meta_data(base_datos -> tabla_izq);
	}
}
bool esta_en(string nombre,string nombres[]){
	for(int i = 0; i < 20;i++){
		if (nombre == nombres[i]){
			return true;
			
		}
	}
	return false;
}
c duplicar_tuplas(c tupla){
	if(tupla == NULL){
		return NULL;
	}
	c nueva_tupla = new _campo;
	nueva_tupla -> valor = tupla -> valor;
	nueva_tupla -> sig = duplicar_tuplas(tupla->sig);
	return nueva_tupla;
}

void insertar_tupla(c &tupla_a_insertar,string columna,string tabla,bd base_datos){
	t tabla_a_insertar = buscar_tabla(base_datos,tabla);
	col auxiliar = tabla_a_insertar -> columna;
	
		while(tabla_a_insertar -> columna -> nombre != columna){
			
			tabla_a_insertar ->columna = tabla_a_insertar->columna -> sig;
		}
		tabla_a_insertar ->columna -> tupla = tupla_a_insertar;
		
}
tipo_retorno select(string tabla1,string columnas,string tabla2,bd &base_datos){
	
	
	//!==== INICIO CONTROLES ====
	
	if(parametro_vacio(tabla1)){
		cout << "-Tabla no existente!" << endl;
		return ERROR;
	}
	if(buscar_tabla(base_datos,tabla2)){
		cout << "-Tabla destino ya existente" << endl;
		return ERROR;
	}
	if(parametro_vacio(columnas)){
		cout << "-Columnas no especificadas!" << endl;
		return ERROR;
	}
	
	//!==== FIN CONTROLES ====
	
	crearTabla(tabla2,base_datos);
	t auxiliar_tabla1 = buscar_tabla(base_datos,tabla1);
	t auxiliar_tabla2 = buscar_tabla(base_datos,tabla2);
	//declaro los arrays que van a contener los campos de las columnas y los valores ya cortados
	string columnas_cortadas[20];
	//declaro las cadenas de caracteres en las que voy a hacer el parse de las respectivas columnas y valores
	char _columnas_tupla[100]; 
	strcpy(_columnas_tupla,columnas.c_str()); //hago el parse para las columnas
	cortar_dospuntos(_columnas_tupla,columnas_cortadas,20); //corto  columnas_tupla y me las traigo en "columnas"
	
	col cabezal_tabla2 = auxiliar_tabla2 -> columna;
	col cabezal_tabla1 = auxiliar_tabla1 -> columna;
	
	
	
	while(auxiliar_tabla1 -> columna){
		if (esta_en(auxiliar_tabla1 -> columna -> nombre,columnas_cortadas)){
			add_col(tabla2,auxiliar_tabla1 -> columna -> nombre,auxiliar_tabla1 -> columna-> tipo,auxiliar_tabla1 -> columna -> calificador,base_datos);
		}
		auxiliar_tabla1 -> columna = auxiliar_tabla1 -> columna -> sig;
	}
	
	auxiliar_tabla1 -> columna = cabezal_tabla1;
	
	
	col respaldo_columna_tabla1 = auxiliar_tabla1 -> columna; //RESPALDO BUCLE 2
	col respaldo_columna_tabla2 = auxiliar_tabla2 -> columna; //RESPALDO BUCLE 1
	
		while(auxiliar_tabla2 -> columna){ // CREO BUCLE 1
			while(auxiliar_tabla1 -> columna -> nombre != auxiliar_tabla2 -> columna -> nombre){ //CREO BUCLE 2
				auxiliar_tabla1 -> columna = auxiliar_tabla1 -> columna -> sig; //MUEVO BUCLE 2
			}
			c aux = duplicar_tuplas(auxiliar_tabla1->columna->tupla); //me consigo todo los campos y los voy colocando
				while(aux){
					if(auxiliar_tabla1 -> columna -> tipo == "integer"){ //!caso ingresar campo entero
						c aux2 = new _campo;
						aux2 -> valor.entero = aux -> valor.entero;
						aux2 -> sig = auxiliar_tabla2 -> columna -> tupla;
						auxiliar_tabla2 -> columna -> tupla = aux2;
					}
					if(auxiliar_tabla1 -> columna -> tipo == "string"){ //!caso ingresar campo texto
						c aux2 = new _campo;
						strcpy(aux2 -> valor.texto,aux -> valor.texto);
						aux2 -> sig = auxiliar_tabla2 -> columna -> tupla;
						auxiliar_tabla2 -> columna -> tupla = aux2;
					}
					
					aux = aux -> sig;
				}
			auxiliar_tabla1 -> columna = respaldo_columna_tabla1; //RECUPERO BUCLE 2
			auxiliar_tabla2 -> columna = auxiliar_tabla2 -> columna -> sig; //MUEVO BUCLE 1
		}
	auxiliar_tabla2 -> columna = respaldo_columna_tabla2; //RECUPERO BUCLE 1

	return OK;
}
	
tipo_retorno _Union(string nombre_tabla_1,string nombre_tabla_2,string nombre_tabla_3,bd &base_datos){
	
	//!==== INICIO CONTROLES ====
	
	if(parametro_vacio(nombre_tabla_1)){
		cout << "-Tabla no existente!" << endl;
		return ERROR;
	}
	if(parametro_vacio(nombre_tabla_2)){
		cout << "-Tabla no existente!" << endl;
		return ERROR;
	}
	if(buscar_tabla(base_datos,nombre_tabla_3)){
		cout << "-Tabla destino ya existente" << endl;
		return ERROR;
	}
	if(!buscar_tabla(base_datos,nombre_tabla_1)){
		cout << "-Tabla no existente" << endl;
		return ERROR;
	}
	if(!buscar_tabla(base_datos,nombre_tabla_2)){
		cout << "-Tabla no existente" << endl;
		return ERROR;
	}
	
	//!==== FIN CONTROLES ====
	
	
	crearTabla(nombre_tabla_3,base_datos);
	t auxiliar_tabla1 = buscar_tabla(base_datos,nombre_tabla_1);
	t auxiliar_tabla2 = buscar_tabla(base_datos,nombre_tabla_2);

	col respaldo_columna1 = auxiliar_tabla1 -> columna;
	
		while(auxiliar_tabla1 -> columna){
			add_col(nombre_tabla_3,auxiliar_tabla1 -> columna -> nombre,auxiliar_tabla1 -> columna-> tipo,auxiliar_tabla1 -> columna -> calificador,base_datos);
			auxiliar_tabla1 -> columna = auxiliar_tabla1 -> columna -> sig;
		}
	
	auxiliar_tabla1 -> columna = respaldo_columna1;
	
	t auxiliar_tabla3 = buscar_tabla(base_datos,nombre_tabla_3);	
	col respaldo_columna_tabla1 = auxiliar_tabla1 -> columna; //RESPALDO BUCLE 2
	col respaldo_columna_tabla2 = auxiliar_tabla2 -> columna; //RESPALDO BUCLE 1
	col respaldo_columna_tabla3 = auxiliar_tabla3 -> columna; 
		
		while(auxiliar_tabla3 -> columna){ // CREO BUCLE 1
			while(auxiliar_tabla1 -> columna -> nombre != auxiliar_tabla3 -> columna -> nombre){ //CREO BUCLE 2
				auxiliar_tabla1 -> columna = auxiliar_tabla1 -> columna -> sig; //MUEVO BUCLE 2
				auxiliar_tabla2 -> columna = auxiliar_tabla2 -> columna -> sig; 
			}
			c aux_t1 = duplicar_tuplas(auxiliar_tabla1 -> columna -> tupla); //me consigo todo los campos y los voy colocando
			c aux_t2 = duplicar_tuplas(auxiliar_tabla2 -> columna -> tupla); //me consigo todo los campos y los voy colocando
			while(aux_t1){ //!LLENO EN T3 CON T1
				if(auxiliar_tabla1 -> columna -> tipo == "integer"){ //!caso ingresar campo entero
					c aux1 = new _campo;
					aux1 -> valor.entero = aux_t1 -> valor.entero;
					aux1 -> sig = auxiliar_tabla3 -> columna -> tupla;
					auxiliar_tabla3 -> columna -> tupla = aux1;
				}
				if(auxiliar_tabla1 -> columna -> tipo == "string"){ //!caso ingresar campo texto
					c aux1 = new _campo;
					strcpy(aux1 -> valor.texto,aux_t1 -> valor.texto);
					aux1 -> sig = auxiliar_tabla3 -> columna -> tupla;
					auxiliar_tabla3 -> columna -> tupla = aux1;
				}
				
				aux_t1 = aux_t1 -> sig;
			}
			while(aux_t2){ //!LLENO EN T3 CON T2
				if(auxiliar_tabla2 -> columna -> tipo == "integer"){ //!caso ingresar campo entero
					c aux2 = new _campo;
					aux2 -> valor.entero = aux_t2 -> valor.entero;
					aux2 -> sig = auxiliar_tabla3 -> columna -> tupla;
					auxiliar_tabla3 -> columna -> tupla = aux2;
				}
				if(auxiliar_tabla2 -> columna -> tipo == "string"){ //!caso ingresar campo texto
					c aux2 = new _campo;
					strcpy(aux2 -> valor.texto,aux_t2 -> valor.texto);
					aux2 -> sig = auxiliar_tabla3 -> columna -> tupla;
					auxiliar_tabla3 -> columna -> tupla = aux2;
				}
				
				aux_t2 = aux_t2 -> sig;
			}
			auxiliar_tabla1 -> columna = respaldo_columna_tabla1; //RECUPERO BUCLE 2
			auxiliar_tabla2 -> columna = respaldo_columna_tabla2;
			auxiliar_tabla3 -> columna = auxiliar_tabla3 -> columna -> sig; //MUEVO BUCLE 1
		}
		auxiliar_tabla3 -> columna = respaldo_columna_tabla3; //RECUPERO BUCLE 1
		
	return OK;
}
	
	
	
	

/*!==============================================FIN IMPLEMENTACIONES==============================================*/
	
	/*
	como funcion strtok();
	dada una cadena de caracteres(no funciona con strings) ejemplo "createTable(zaza)"
	y los separadores como segundo parametro 
	ej strtok(cadena,"1 2") siendo 1 y 2 los caracteres separadores, para diferenciar entre separadores se usa el espacio 

	al llamar a strtok una primera vez la funcion va a tomar el contenido desde el primer caracter de la cadena provista
	hasta que se encuentre con uno de los caracteres separadores.

	en las llamadas consecuentes a la funcion strtok con NULL como cadena va a tomar el contenido desde el caracter siguiente
	al ultimo separador encontrado hasta que se encuentre con uno de los caracteres separadores nuevamente.

	esto se va a repetir hasta que se termine la cadena.
	*/
	

