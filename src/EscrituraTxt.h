#ifndef ESCRITURATXT_H
#define ESCRITURATXT_H

#include <string>
#include <map>
#include "Escritura.h"
#include "Settings.h"

class EscrituraTxt : public Escritura
{
private:
    std::string convertirDatos(const UnionDatos *unionDatos);
public:
    bool escrituraDatos(std::map<std::string, UnionDatos *> unificacion, std::string &ruta) override;
};

#endif // ESCRITURATXT_H
