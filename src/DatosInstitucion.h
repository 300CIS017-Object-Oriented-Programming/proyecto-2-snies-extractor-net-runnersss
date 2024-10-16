#ifndef DATOSESTUDIANTE_H
#define DATOSESTUDIANTE_H

#include <string>

class DatosInstitucion
{
private:
    int codigoInstitucion;
    int iesPadre;
    bool esPrincipal; // true si es principal, false si es seccional
    int idSectorIes;
    std::string sectorIes;
    int idCaracter;
    std::string caracterIes;
    int codigoDepartamentoIes;
    std::string departamentoIes;
    int codigoMunicipioIes;
    std::string municipioIes;

public:
    DatosInstitucion(/* args */);
    ~DatosInstitucion();

    int getCodigoInstitucion() const;

    int getIesPadre() const;

    bool getEsPrincipal() const;

    int getIdSectorIes() const;

    std::string getSectorIes() const;

    int getIdCaracter() const;

    std::string getCaracterIes() const;
    int getCodigoDepartamentoIes() const;
    std::string getDepartamentoIes() const;
    int getCodigoMunicipioIes() const;
    std::string getMunicipioIes() const;
};

#endif