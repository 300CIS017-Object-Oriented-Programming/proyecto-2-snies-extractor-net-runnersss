#include "UnionDatos.h"

void UnionDatos::setPrograma(ProgramaAcademico *prog)
{
    programa = prog;
}

void UnionDatos::setInstitucion(DatosInstitucion *inst)
{
    institucion = inst;
}

void UnionDatos::setConsolidados(const vector<Consolidado *> &nuevosConsolidados)
{
    consolidados = nuevosConsolidados;
}

// Métodos get (opcional, si se requiere)
ProgramaAcademico *UnionDatos::getPrograma() const
{
    return programa;
}

DatosInstitucion *UnionDatos::getInstitucion() const
{
    return institucion;
}

vector<Consolidado *> UnionDatos::getConsolidado() const
{
    return consolidados;
}
