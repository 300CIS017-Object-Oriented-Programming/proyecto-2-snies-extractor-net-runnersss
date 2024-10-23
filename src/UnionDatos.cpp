#include "UnionDatos.h"

void UnionDatos::setPrograma(ProgramaAcademico* prog) {
    programa = prog;
}

void UnionDatos::setInstitucion(DatosInstitucion* inst) {
    institucion = inst;
}

void UnionDatos::setConsolidados(const map<string, Consolidado*>& nuevosConsolidados) {
    consolidados = nuevosConsolidados;
}

// Métodos get (opcional, si se requiere)
ProgramaAcademico* UnionDatos::getPrograma() const {
    return programa;
}

DatosInstitucion* UnionDatos::getInstitucion() const {
    return institucion;
}

Consolidado* UnionDatos::getConsolidado(const string& clave) const {
    auto it = consolidados.find(clave);
    if (it != consolidados.end()) {
        return it->second;
    }
    return nullptr;
}
