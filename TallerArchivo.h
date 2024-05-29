#ifndef TALLERARCHIVO_H_INCLUDED
#define TALLERARCHIVO_H_INCLUDED
#include "taller.h"

class TallerArchivo
{
    private:
    Taller obj;
public:
    bool GuardarTaller(Taller obj);
    Taller LeerTaller(int indice);
    int ContarRegistrosTaller();
};

#endif // TALLERARCHIVO_H_INCLUDED
