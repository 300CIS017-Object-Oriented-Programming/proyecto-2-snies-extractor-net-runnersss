#ifndef ESCRITURAJSON_H
#define ESCRITURAJSON_H

#include <map>
#include <string>
#include "Escritura.h"
#include "json.hpp"
#include "UnionDatos.h"

using json = nlohmann::json;

class EscrituraJson : public Escritura
{
public:
    bool escrituraDatos(std::map<std::string, UnionDatos *> unificacion, std::string &ruta) override;
    
private:
    json convertirDatos(const UnionDatos *unionDatos);
};

#endif // ESCRITURAJSON_H
