#ifndef DATOSESTUDIANTE_H
#define DATOSESTUDIANTE_H

class DatosEstudiante
{
private:
    int inscritos, admitidos, nuevosMatriculados, graduado;
    int año, semestre;

public:
    DatosEstudiante(/* args */);
    ~DatosEstudiante();

    int getInscritos() const;

    int getAdmitidos() const;

    int getNuevosMatriculados() const;

    int getGraduado() const;

    int getAño() const;

    int getSemestre() const;
};

#endif