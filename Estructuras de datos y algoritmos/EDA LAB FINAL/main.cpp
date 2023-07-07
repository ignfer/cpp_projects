#include<iostream>
#include<string.h>
#include"estructuras.h"
#include"cabezales.h"
using namespace std;

int main (int argc, char *argv[]) {
	opcion opc; //opc es una variable de tipo enumerado opcion
	char entrada[100];
	char auxEntrada[100];

	/*
	consola
	*/
	while(true){ 
		cout << ">>";
		cin.getline(entrada,100);
		strcpy(auxEntrada,entrada); //crea una copia en auxEntrada de entrada, ya que si modificamos entrada en que_comando, se modifica para el resto del main y perdemos informacion
		opc = que_comando(auxEntrada); //llama a la funcion que_comando y devuelve el ENUM correspondiente del comando contenido en la entrada
		switch(opc){
			case createTable:{
				
				string parametros[1]; //cantidad de parametros esperada
				cortar(entrada,parametros,1);
				out(_createTable(parametros[0]));
			break;}
			case dropTable:{
					
				string parametros[1];
				cortar(entrada,parametros,1);
				out(_dropTable(parametros[0]));
			break;}
			case addCol:{
					
				string parametros[4];
				cortar(entrada,parametros,4);
				out(_add_col(parametros[0],parametros[1],parametros[2],parametros[3]));
			break;}
			case alterCol:{
					
				string parametros[5];
				cortar(entrada,parametros,5);
				out(_alter_col(parametros[0],parametros[1],parametros[2],parametros[3],parametros[4]));
			break;}
			case dropCol:{
				
				string parametros[2];
				cortar(entrada,parametros,2);
				out(_drop_col(parametros[0],parametros[1]));
			break;}
			case insertInto:{
				
				string parametros[3];
				cortar(entrada,parametros,3);
				out(_insertInto(parametros[0],parametros[1],parametros[2]));
			break;}
			case Delete:{
				
				string parametros[2];
				cortar(entrada,parametros,2);
				out(_deleteTupla(parametros[0],parametros[1]));
			break;}
			case update:{
				
				string parametros[4];
				cortar(entrada,parametros,4);
				out(_update(parametros[0],parametros[1],parametros[2],parametros[3]));
				break;}
			case printDataTable:{
				
				string parametros[2];
				cortar(entrada,parametros,2);
				out(_printDataTable(parametros[0],parametros[1]));
			break;}
			case printTables:{
						out(_printTables());
				break;}
			case printMetadata:{
					out(_printMetadata());
			break;}
			case Select:{
					string parametros[3];
					cortar(entrada,parametros,3);
					out(_select(parametros[0],parametros[1],parametros[2]));
			break;}
			case selectWhere:{
				
				string parametros[3];
				cortar(entrada,parametros,3);
				out(_selectWhere(parametros[0],parametros[1],parametros[2]));
			break;}
			case Union:{
				string parametros[3];
				cortar(entrada,parametros,3);
				out(_union(parametros[0],parametros[1],parametros[2]));
			break;}
			case Join:{
				out(_join());
			break;}
			case intersect:{
				out(_intersect());
			break;}
			case Minus:{
				out(_minus());
			break;}
			case redo:{
				out(_redo());
			break;}
			case undo:{
				out(_undo());
			break;}
			case endTransaction:{
				out(_endTransaction());
			break;}
			case beginTransaction:{
				out(_beginTransaction());
			break;}
			case fin:{
				return 0;
			break;}
			case NO_RECONOCIDO:{
				cout << "comando no existente" << endl;}
		}
	}

	return 0;
}
/*TO-DO'S
imprimir la ayuda con una funcion void imprimirAyuda()
preguntar sobre el delete
que tanto hay que respetar el cabezal del tipo retorno? 
hacer un cabezal en el main (capaz llamado base de datos) que apunte a las tablas
*/
