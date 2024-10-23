#ifndef PROGRAMA_ACADEMICO_H
#define PROGRAMA_ACADEMICO_H

#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <iostream>
#include "Consolidado.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::map;
using std::unordered_map;

class ProgramaAcademico
{
    string codigoSniesDelPrograma;
    string programaAcademico;
    string idNivelAcademico;
    string nivelAcademico;
    string idNivelDeFormacion;
    string nivelDeFormacion;
    string idMetodologia;
    string metodologia;
    string idArea;
    string areaDeConocimiento;
    string idNucleo;
    string nucleoBasicoDelConocimientoNbc;
    string idCineCampoAmplio;
    string descCineCampoAmplio;
    string idCineCampoEspecifico;
    string descCineCampoEspecifico;
    string idCineCodigoDetallado;
    string descCineCodigoDetallado;
    string codigoDelDepartamentoPrograma;
    string departamentoDeOfertaDelPrograma;
    string codigoDelMunicipioPrograma;
    string municipioDeOfertaDelPrograma;

public:
    ProgramaAcademico();
    void setCodigoSniesDelPrograma(const std::string&);
    string getCodigoSniesDelPrograma();

    void setProgramaAcademico(const std::string&);
    string getProgramaAcademico();

    void setIdNivelAcademico(const std::string&);
    string getIdNivelAcademico();

    void setNivelAcademico(const std::string&);
    string getNivelAcademico();

    void setIdNivelDeFormacion(const std::string&);
    string getIdNivelDeFormacion();

    void setNivelDeFormacion(const std::string&);
    string getNivelDeFormacion();

    void setIdMetodologia(const std::string&);
    string getIdMetodologia();
    void setMetodologia(const std::string&);
    string getMetodologia();

    void setIdArea(const std::string&);
    string getIdArea();
    void setAreaDeConocimiento(const std::string&);
    string getAreaDeConocimiento();
    void setIdNucleo(const std::string&);
    string getIdNucleo();
    void setNucleoBasicoDelConocimientoNbc(const std::string&);
    string getNucleoBasicoDelConocimientoNbc();
    void setIdCineCampoAmplio(const std::string&);
    string getIdCineCampoAmplio();
    void setDescCineCampoAmplio(const std::string&);
    string getDescCineCampoAmplio();
    void setIdCineCampoEspecifico(const std::string&);
    string getIdCineCampoEspecifico();
    void setDescCineCampoEspecifico(const std::string&);
    string getDescCineCampoEspecifico();
    void setIdCineCodigoDetallado(const std::string&);
    string getIdCineCodigoDetallado();
    void setDescCineCodigoDetallado(const std::string&);
    string getDescCineCodigoDetallado();
    void setCodigoDelDepartamentoPrograma(const std::string&);
    string getCodigoDelDepartamentoPrograma();
    void setDepartamentoDeOfertaDelPrograma(const std::string&);
    string getDepartamentoDeOfertaDelPrograma();
    void setCodigoDelMunicipioPrograma(const std::string&);
    string getCodigoDelMunicipioPrograma();
    void setMunicipioDeOfertaDelPrograma(const std::string&);
    string getMunicipioDeOfertaDelPrograma();

    void imprimir() const {
        std::cout << "Código SNIES del Programa: " << codigoSniesDelPrograma << std::endl;
        std::cout << "Programa Académico: " << programaAcademico << std::endl;
        std::cout << "ID Nivel Académico: " << idNivelAcademico << std::endl;
        std::cout << "Nivel Académico: " << nivelAcademico << std::endl;
        std::cout << "ID Nivel de Formación: " << idNivelDeFormacion << std::endl;
        std::cout << "Nivel de Formación: " << nivelDeFormacion << std::endl;
        std::cout << "ID Metodología: " << idMetodologia << std::endl;
        std::cout << "Metodología: " << metodologia << std::endl;
        std::cout << "ID Área: " << idArea << std::endl;
        std::cout << "Área de Conocimiento: " << areaDeConocimiento << std::endl;
        std::cout << "ID Núcleo: " << idNucleo << std::endl;
        std::cout << "Núcleo Básico del Conocimiento: " << nucleoBasicoDelConocimientoNbc << std::endl;
        std::cout << "ID Cine Campo Amplio: " << idCineCampoAmplio << std::endl;
        std::cout << "Descripción Cine Campo Amplio: " << descCineCampoAmplio << std::endl;
        std::cout << "ID Cine Campo Específico: " << idCineCampoEspecifico << std::endl;
        std::cout << "Descripción Cine Campo Específico: " << descCineCampoEspecifico << std::endl;
        std::cout << "ID Cine Código Detallado: " << idCineCodigoDetallado << std::endl;
        std::cout << "Descripción Cine Código Detallado: " << descCineCodigoDetallado << std::endl;
        std::cout << "Código del Departamento del Programa: " << codigoDelDepartamentoPrograma << std::endl;
        std::cout << "Departamento de Oferta del Programa: " << departamentoDeOfertaDelPrograma << std::endl;
        std::cout << "Código del Municipio del Programa: " << codigoDelMunicipioPrograma << std::endl;
        std::cout << "Municipio de Oferta del Programa: " << municipioDeOfertaDelPrograma << std::endl;
        std::cout << "-----------------------------------" << std::endl;
    }
};

#endif