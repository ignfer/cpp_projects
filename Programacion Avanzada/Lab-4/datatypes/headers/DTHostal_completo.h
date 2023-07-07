#ifndef DTHOSTAL_COMPLETO_H_
#define DTHOSTAL_COMPLETO_H_

#define NC "\e[0m"
#define GREEN "\e[0;32m"
#define CYAN "\e[0;36m"

#include "../../ICollection/interfaces/IDictionary.h"
#include "../../ICollection/collections/OrderedDictionary.h"
#include "../../ICollection/interfaces/ICollectible.h"
#include "../../ICollection/Integer.h"
#include "DTReview.h"
#include "DTHabitacion.h"
#include <iostream>
using namespace std;

class DTHostal_completo: public ICollectible{
    private:
        string nombre;
        string direccion;
        string telefono;
        float promedio;
        IDictionary* dt_reviews;
        IDictionary* dt_habitaciones;

    public:
        DTHostal_completo();
        DTHostal_completo(string nombre, string direccion, string telefono, float promedio, OrderedDictionary* dt_reviews, OrderedDictionary* dt_habitaciones);
        string get_nombre();
        string get_direccion();
        string get_telefono();
        float get_promedio();
        OrderedDictionary* get_dt_reviews();
        OrderedDictionary* get_dt_habitaciones();
        friend ostream& operator << (ostream& salida, DTHostal_completo hostal);
};

#endif // DTHOSTAL_COMPLETO_H_