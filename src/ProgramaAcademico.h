#ifndef PROGRAMA_ACADEMICO_H
#define PROGRAMA_ACADEMICO_H

#include <string>
#include <vector>
#include <unordered_map>

#include <iostream>
#include "Consolidado.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::map;


class ProgramaAcademico
{
    int codigoSniesDelPrograma;
    string programaAcademico;
    int idNivelAcademico;
    string nivelAcademico;
    int idNivelDeFormacion;
    string nivelDeFormacion;
    int idMetodologia;
    string metodologia;
    int idArea;
    string areaDeConocimiento;
    int idNucleo;
    string nucleoBasicoDelConocimientoNbc;
    int idCineCampoAmplio;
    string descCineCampoAmplio;
    int idCineCampoEspecifico;
    string descCineCampoEspecifico;
    int idCineCodigoDetallado;
    string descCineCodigoDetallado;
    int codigoDelDepartamentoPrograma;
    string departamentoDeOfertaDelPrograma;
    int codigoDelMunicipioPrograma;
    string municipioDeOfertaDelPrograma;
    unordered_map<int, Consolidado *> consolidados;

public:
    ProgramaAcademico();

    void setCodigoSniesDelPrograma(int);
    int getCodigoSniesDelPrograma();

    void setProgramaAcademico(string &);
    string getProgramaAcademico();

    void setIdNivelAcademico(int);
    int getIdNivelAcademico();

    void setNivelAcademico(string &);
    string getNivelAcademico();

    void setIdNivelDeFormacion(int);
    int getIdNivelDeFormacion();

    void setNivelDeFormacion(string &);
    string getNivelDeFormacion();

    void setIdMetodologia(int);
    int getIdMetodologia();
    void setMetodologia(string &);
    string getMetodologia();

    void setIdArea(int);
    int getIdArea();
    void setAreaDeConocimiento(string &);
    string getAreaDeConocimiento();
    void setIdNucleo(int);
    int getIdNucleo();
    void setNucleoBasicoDelConocimientoNbc(string &);
    string getNucleoBasicoDelConocimientoNbc();
    void setIdCineCampoAmplio(int);
    int getIdCineCampoAmplio();
    void setDescCineCampoAmplio(string &);
    string getDescCineCampoAmplio();
    void setIdCineCampoEspecifico(int);
    int getIdCineCampoEspecifico();
    void setDescCineCampoEspecifico(string &);
    string getDescCineCampoEspecifico();
    void setIdCineCodigoDetallado(int);
    int getIdCineCodigoDetallado();
    void setDescCineCodigoDetallado(string &);
    string getDescCineCodigoDetallado();
    void setCodigoDelDepartamentoPrograma(int);
    int getCodigoDelDepartamentoPrograma();
    void setDepartamentoDeOfertaDelPrograma(string &);
    string getDepartamentoDeOfertaDelPrograma();
    void setCodigoDelMunicipioPrograma(int);
    int getCodigoDelMunicipioPrograma();
    void setMunicipioDeOfertaDelPrograma(string &);
    string getMunicipioDeOfertaDelPrograma();
    void setConsolidado(Consolidado *, int);
    Consolidado *getConsolidado(int);

    ~ProgramaAcademico();
    void setDato(string, string);
    string getDato(string);
    Consolidado *getConsolidado(int);
};

#endif