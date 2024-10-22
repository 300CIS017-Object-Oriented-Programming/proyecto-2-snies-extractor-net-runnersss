#ifndef DATOSESTUDIANTE_H
#define DATOSESTUDIANTE_H

#include <string>
using std::string;
#include <iostream>
using namespace std;

class DatosInstitucion
{
private:
//Se almacena todos los datos como string para evitar la périda de información
//Por ejemplo un código 0504 perdería el primer 0 al ser almacenado como int
//Además, no se van a realizar operaciones numéricas por lo que
//no es necesario un tipo de dato numérico
    string codigoDeLaInstitucion;
    string iesPadre;
    string institucionDeEducacionSuperiorIes;
    string principalOSeccional;
    string idSectorIes;
    string sectorIes;
    string idCaracter;
    string caracterIes;
    string codigoDelDepartamentoIes;
    string departamentoDeDomicilioDeLaIes;
    string codigoDelMunicipioIes;
    string municipioDeDomicilioDeLaIes;

public:
    ~DatosInstitucion();

    void setCodigoDeLaInstitucion(const std::string&);
    string getCodigoDeLaInstitucion();

    void setIesPadre(const std::string&);
    string getIesPadre();

    void setInstitucionDeEducacionSuperiorIes(const std::string&);
    string getInstitucionDeEducacionSuperiorIes();

    void setPrincipalOSeccional(const std::string&);
    string getPrincipalOSeccional();

    void setIdSectorIes(const std::string&);
    string getIdSectorIes();

    void setSectorIes(const std::string&);
    string getSectorIes();

    void setIdCaracter(const std::string&);
    string getIdCaracter();

    void setCaracterIes(const std::string&);
    string getCaracterIes();

    void setCodigoDelDepartamentoIes(const std::string&);
    string getCodigoDelDepartamentoIes();

    void setDepartamentoDeDomicilioDeLaIes(const std::string&);
    string getDepartamentoDeDomicilioDeLaIes();

    void setCodigoDelMunicipioIes(const std::string&);
    string getCodigoDelMunicipioIes();

    void setMunicipioDeDomicilioDeLaIes(const std::string&);
    string getMunicipioDeDomicilioDeLaIes();

    void imprimir() const {
        std::cout << "Código de la Institución: " << codigoDeLaInstitucion << std::endl;
        std::cout << "IES Padre: " << iesPadre << std::endl;
        std::cout << "Institución de Educación Superior: " << institucionDeEducacionSuperiorIes << std::endl;
        std::cout << "Principal o Seccional: " << principalOSeccional << std::endl;
        std::cout << "ID Sector IES: " << idSectorIes << std::endl;
        std::cout << "Sector IES: " << sectorIes << std::endl;
        std::cout << "ID Caracter: " << idCaracter << std::endl;
        std::cout << "Caracter IES: " << caracterIes << std::endl;
        std::cout << "Código del Departamento: " << codigoDelDepartamentoIes << std::endl;
        std::cout << "Departamento de Domicilio: " << departamentoDeDomicilioDeLaIes << std::endl;
        std::cout << "Código del Municipio: " << codigoDelMunicipioIes << std::endl;
        std::cout << "Municipio de Domicilio: " << municipioDeDomicilioDeLaIes << std::endl;
        std::cout << "-----------------------------------" << std::endl;
    }
};

#endif