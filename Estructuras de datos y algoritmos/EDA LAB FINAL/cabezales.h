
#ifndef CABEZALES_H
#define CABEZALES_H
//cabezales funciones.cpp
opcion que_comando(char input[]);
int contar_tuplas(bd &base_datos);
void cortar(char entrada[],string parametros[], int cantidad_parametros);
void cortar_dospuntos(char entrada[],string parametros[],int cantidad_parametros);
tipo_retorno crearTabla(string nombre_tabla,bd &base_datos );
tipo_retorno dropearTabla(string nombre_tabla, bd &base_datos);
tipo_retorno add_col(string nombre_tabla,string nombre_col,string tipo_col,string calificador,bd &base_datos);
tipo_retorno drop_col(string nombre_tabla, string nombre_col, bd &base_datos);
tipo_retorno alter_col(string nombre_tabla, string nombre_col,string tipo_col_nuevo,string calificador_nuevo, string nombre_col_nuevo,bd &base_datos);
tipo_retorno insertarInto(string nombre_tabla,string columnas_tupla,string valores_tupla,bd base_datos);
tipo_retorno delete_tupla(string nombre_tabla, string condiciones, bd &base_datos);
tipo_retorno updatear(string nombre_tabla, string condicion, string nombre_col,string valor,bd &base_datos);
tipo_retorno __selectWhere(string nombre_tabla_origen,string condicion,string nombre_tabla_destino,bd &base_datos);
tipo_retorno print_data_table (string nombre_tabla, string ordenada_por,bd &base_datos);
bool existe_tabla_en_memoria(bd &base_datos);
void cortar_condicion(char entrada[],string parametros[],int cantidad_parametros);
void encontrar_columna(t &tabla, string condicion);
tipo_retorno print_tables(bd base_datos);
tipo_retorno print_meta_data(bd base_datos);
tipo_retorno select(string tabla1,string columnas,string tabla2,bd &base_datos);
tipo_retorno _Union(string nombre_tabla_1,string nombre_tabla_2,string nombre_tabla_3,bd &base_datos);
tipo_retorno dropTables(bd &base_datos,string nombre_tabla);
//cabezales retorno.cpp
void out(tipo_retorno retorno);
void inicializar();
tipo_retorno _createTable(string nombre_tabla);
tipo_retorno _dropTable(string nombre_tabla);
tipo_retorno _add_col(string nombre_tabla,string nombre_col,string tipo_col,string calificador);
tipo_retorno _drop_col(string nombre_tabla,string nombre_col);
tipo_retorno drop_table(string nombre_tabla);
tipo_retorno _alter_col(string nombre_tabla, string nombre_col,string tipo_col_nuevo,string calificador_nuevo, string nombre_col_nuevo);
tipo_retorno _insertInto(string nombre_tabla, string columnas_tupla, string valores_tupla);
tipo_retorno _deleteTupla(string nombre_tabla, string condiciones);
tipo_retorno _update(string nombre_tabla, string condicion, string nombre_col,string valor);
tipo_retorno _selectWhere(string nombre_tabla_origen, string condicion,string nombre_tabla_destino);
tipo_retorno _printDataTable(string nombre_tabla,string ordenada_por);
tipo_retorno _printTables();
tipo_retorno _printMetadata();
tipo_retorno _select(string tabla1,string columnas,string tabla2);
tipo_retorno _union(string nombre_tabla_1,string nombre_tabla_2,string nombre_tabla_3);
tipo_retorno _join();
tipo_retorno _intersect();
tipo_retorno _minus();
tipo_retorno _redo();
tipo_retorno _undo();
tipo_retorno _beginTransaction();
tipo_retorno _endTransaction();
#endif

