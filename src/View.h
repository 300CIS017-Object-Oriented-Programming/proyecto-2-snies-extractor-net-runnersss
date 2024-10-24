#ifndef VIEW_H
#define VIEW_H
#include "SNIESController.h"
#include "Settings.h"
#include <cctype>
#include "EscrituraTxt.h"
#include "EscrituraJson.h"
#include "Escritura.h"
using std::to_string;
#include <iostream>

using namespace std;

class View
{
private:
    SNIESController *controlador;
    Settings ajustes;
    bool esEntero(const std::string &str);
    bool eleccionUsuario();

public:
    View();
    ~View();
    bool mostrarPantallaBienvenido();
    void mostrarDatosExtra();
    void buscarPorPalabraClaveYFormacion();
    void salir();
    bool isConvetibleToInt(const string &);
    void parametrizacion();
    void exportacionDatos(map<std::string, UnionDatos *> unificacion);
};

#endif