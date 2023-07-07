#ifndef DTREVIEW_H_
#define DTREVIEW_H_

#include "../../ICollection/interfaces/ICollectible.h"
#include "../../enums/EnumEstado.h"

#include <iostream>
#include <chrono>

using namespace std;
class Review;
class DTReview: public ICollectible{
    private:
        int codigo;
        chrono::system_clock::time_point fecha;
        int calificacion;
        string comentario;
    public:
        DTReview();
        DTReview(Review* review);
        DTReview(int codigo, tm* fecha, int calificacion,string comentario);
        int get_codigo();
        tm* get_fecha();
        int get_calificacion();
        string get_comentario();
        friend ostream& operator << (ostream& salida, DTReview review);
};

#endif // DTREVIEW_H_