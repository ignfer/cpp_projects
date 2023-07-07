#ifndef HUESPED_H_
#define HUESPED_H_
#include "Usuario.h"
#include "Empleado.h"
#include "../../datatypes/headers/DTHuesped.h"
#include "../../ICollection/collections/OrderedDictionary.h"
#include "../../classes/headers/ReservaGrupal.h"
#include "../../classes/headers/ReservaIndividual.h"
#include "../../ICollection/Integer.h"
class Estadia;
class ReservaGrupal;
class Huesped: public Usuario{
    private:
        bool es_tecno;
        IDictionary* reservas_individuales;
        IDictionary* reservas_grupales;
        IDictionary* estadias;
    public:
        Huesped();
        Huesped(string nombre, string email, string contrasena, bool es_tecno);
        Huesped(DTHuesped nuevo_huesped);
        bool get_es_tecno();
        DTHuesped get_DT();
        OrderedDictionary* get_reservas_individuales();
        OrderedDictionary* get_reservas_grupales();
        void asignar_reserva(ReservaGrupal* rg);
        void asignar_reserva(ReservaIndividual* ri);
        void alta_estadia(Huesped* ptr_huesped,int codigo_reserva);
        void alta_estadia(Huesped* ptr_huesped, int codigo_reserva, tm* checkin);
        void asignar_estadia_usuario(Estadia* ptr_estadia);
        int existe_estadia_activa(string nombre_hostal);
        void existe_estadia_activa(int codigo_estadia, tm* checkout);
        void existe_estadia_activa(int codigo_estadia);
        OrderedDictionary* estadia_fin(string nombre_hostal);
        void calificarHostal(Hostal* ptr_hostal,int codigo_estadia,string comentario, int calificacion);
        void calificarHostal(Hostal* ptr_hostal,int codigo_estadia,string comentario, int calificacion, tm* fecha);
        OrderedDictionary* listar_comentarios_sin_resp(string nombre_hostal);
        void alta_respuesta(int codigo_review, Empleado* ptr_empleado,string respuesta);
        void alta_respuesta(int codigo_review, Empleado* ptr_empleado,string respuesta, tm* fecha);
        int contar_estadias_activas();
        int contar_estadias_activas(string nombre_hostal);
};


#endif // HUESPED_H_