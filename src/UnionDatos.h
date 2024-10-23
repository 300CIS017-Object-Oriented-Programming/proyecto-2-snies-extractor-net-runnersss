#ifndef UNIONDATOS_H
#define UNIONDATOS_H

#include <map>
#include <string>
#include "ProgramaAcademico.h"
#include "DatosInstitucion.h"
#include "Consolidado.h"

using std::map;
using std::string;
using std::vector;

class UnionDatos {
private:
    ProgramaAcademico* programa;
    DatosInstitucion* institucion;
    vector<Consolidado*> consolidados;

public:
    void setPrograma(ProgramaAcademico* prog);
    void setInstitucion(DatosInstitucion* inst);
    
    void setConsolidados(const vector<Consolidado*>& nuevosConsolidados);

    ProgramaAcademico* getPrograma() const;
    DatosInstitucion* getInstitucion() const;
    Consolidado* getConsolidado(const string& clave) const;
    void imprimir() {
        if (programa) {
            programa->imprimir();
        }
        if (institucion) {
            institucion->imprimir();
        }
        for (const auto& consolidado : consolidados) {
            if (consolidado) { 
                consolidado->imprimir(); 
            }
        }
    }
};

#endif // UNIONDATOS_H
