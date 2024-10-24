#include "Escritura.h"
#include "json.hpp"

using json = nlohmann::json;

class EscrituraJson : public Escritura
{
    bool escrituraDatos(map<std::string, UnionDatos *> unificacion, string &ruta) override;
    json convertirDatos(const UnionDatos *unionDatos);
};