#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <iostream>
#include <cmath>
#include <cstring>
#include <limits>

/*Librerías necesarias para la gestión de la fecha y hora*/
#include <chrono>
#include <iomanip>
#include <sstream>

#define NC "\e[0m"
#define RED "\e[0;31m"
#define GREEN "\e[0;32m"
#define CYAN "\e[0;36m"
#define REDB "\e[41m"

/* Datatypes */
#include "../datatypes/headers/DTHuesped.h"
#include "../datatypes/headers/DTEmpleado.h"
#include "../datatypes/headers/DTReserva.h"

/* Enums */
#include "../enums/EnumCargo.h"
#include "../enums/EnumComparacionFecha.h"

#include "../iControlador/IControlador.h"
#include "../fabrica/Fabrica.h"

/* Funciones auxiliares*/

void mostrar_menu_principal();
int eleccion_menu_principal();
void press_enter();
Cargo switch_cargo(string str_cargo);
void imprimir_fecha(tm* fecha);
bool verificar_fecha(string fecha_hora_str, tm* nueva_fecha);
bool verificar_fecha_checkin(string fecha_hora_str, tm* nueva_fecha);
bool verificar_fecha_checkout(string fecha_hora_str, tm* fecha_checkout, tm* fecha_checkin);
OrderedDictionary* obtener_hostales();
int obtener_estadias_huesped_fin(string nombre_hostal,string email_huesped);
OrderedDictionary* obtener_estadias_huesped_fin_checkeo(string nombre_hostal,string email_huesped);
OrderedDictionary* listar_comentarios_sr(string email_empleado);
void mostrar_reserva_usuario(OrderedDictionary* dt_reserva);
void mostrar_reservas_hostal(OrderedDictionary* dt_reserva, string nombre_hostal);
OrderedDictionary* obtener_hostales_con_promedio();
OrderedDictionary* obtener_no_empleados_hostal(string nombre_hostal);
OrderedDictionary* obtener_usuarios();
void obtener_huespedes();
void obtener_huesped_completo(string email);
void obtener_empleado_completo(string email);
string obtener_estado_reserva(Estado tipo_estado);

/* Fin funciones auxiliares*/

/*Funciones del menu principal*/
void alta_usuario();
void alta_hostal();
void alta_habitacion();
void asignar_empleado_hostal();
void realizar_reserva();
void consultar_top_3();
void registrar_estadia();
void finalizar_estadia();
void calificar_estadia();
void comentar_calificacion();
void consulta_usuario();
void consulta_hostal();
void consulta_reserva();
void consulta_estadia();
void baja_reserva();
void modificar_fecha();
void datos_prueba();
void exit();
/*Fin funciones del menu principal*/

#endif // FUNCTIONS_H_