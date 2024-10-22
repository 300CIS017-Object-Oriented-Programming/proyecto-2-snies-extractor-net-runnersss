#include "Consolidado.h"

int Consolidado::getIdSexo()
{
    return idSexo;
}

void Consolidado::setIdSexo(int idSexo)
{
    this->idSexo = idSexo;
}

string Consolidado::getSexo()
{
    return sexo;
}

void Consolidado::setSexo(const std::string&sexo)
{
    this->sexo = sexo;
}

int Consolidado::getAno()
{
    return ano;
}

void Consolidado::setAno(int ano)
{
    this->ano = ano;
}

int Consolidado::getSemestre()
{
    return semestre;
}
void Consolidado::setSemestre(int semestre)
{
    this->semestre = semestre;
}

int Consolidado::getInscritos()
{
    return inscritos;
}

void Consolidado::setInscritos(int inscritos)
{
    this->inscritos = inscritos;
}

int Consolidado::getAdmitidos()
{
    return admitidos;
}

void Consolidado::setAdmitidos(int admitidos)
{
    this->admitidos = admitidos;
}

int Consolidado::getMatriculados()
{
    return matriculados;
}

void Consolidado::setMatriculados(int matriculados)
{
    this->matriculados = matriculados;
}

int Consolidado::getMatriculadosPrimerSemestre()
{
    return matriculadosPrimerSemestre;
}

void Consolidado::setMatriculadosPrimerSemestre(int matriculadosPrimerSemestre)
{
    this->matriculadosPrimerSemestre = matriculadosPrimerSemestre;
}

int Consolidado::getGraduados()
{
    return graduados;
}

void Consolidado::setGraduados(int graduados)
{
    this->graduados = graduados;
}
