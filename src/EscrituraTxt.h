#include "Escritura.h"

class EscrituraTxt : public Escritura
{
    bool escrituraDatos(map<std::string, UnionDatos *> unificacion, string &ruta) override;
    string convertirDatos(const UnionDatos *unionDatos);
};