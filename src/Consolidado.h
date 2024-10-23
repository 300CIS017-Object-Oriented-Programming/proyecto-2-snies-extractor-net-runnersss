#ifndef CONSOLIDADO_H
#define CONSOLIDADO_H

#include <string>
#include <vector>
#include <iostream>


using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;


class Consolidado
{
private:
    string idSexo;
    string sexo;
    string  ano;
    string  semestre;
    string  inscritos;
    string  admitidos;
    string  matriculados;
    string  matriculadosPrimerSemestre;
    string  graduados;

public:
    // Mantenimiento: Gran cantidad de métodos get y set que tal vez no son estrictamente necesarios
    string  getIdSexo();
    void setIdSexo(const std::string&);

    string getSexo();
    void setSexo(const std::string&);

    string  getAno();
    void setAno(const std::string&);

    string  getSemestre();
    void setSemestre(const std::string&);

    string  getInscritos();
    void setInscritos(const std::string&);

    string  getAdmitidos();
    void setAdmitidos(const std::string&);

    string  getMatriculados();
    void setMatriculados(const std::string&);

    string  getMatriculadosPrimerSemestre();
    void setMatriculadosPrimerSemestre(const std::string&);

    string  getGraduados();
    void setGraduados(const std::string&);
    void imprimir() const {
        std::cout << "Sexo: " << sexo << ", Año: " << ano << ", Semestre: " << semestre
                  << ", Inscritos: " << inscritos << ", Admitidos: " << admitidos
                  << ", Matriculados: " << matriculados << ", Graduados: " << graduados 
                  << ", Matriculados Primer Semestre: "<<matriculadosPrimerSemestre<< std::endl;
    }
};

#endif // CONSOLIDADO_H
