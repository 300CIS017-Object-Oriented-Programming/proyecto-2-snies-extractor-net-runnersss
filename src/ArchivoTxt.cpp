#include "ArchivoTXT.h"

void ArchivoTXT::guardar(const std::string &ruta, multimap<int, ProgramaAcademico *> &mapadeProgramasAcademicos, vector<string> etiquetasColumnas)
{
    bool estadoCreacion = false;
    string rutaCompleta = ruta + "resultados.csv";
    ofstream archivoResultados(rutaCompleta);
    if (archivoResultados.is_open())
    {
        // Imprimimos en el archivo las etiquetas (Primera fila)
        for (int i = 0; i < etiquetasColumnas.size(); i++)
        {
            archivoResultados << etiquetasColumnas[i] << ";";
        }
        archivoResultados << "GRADUADOS;INSCRITOS;MATRICULADOS;NEOS" << endl;

        multimap<int, ProgramaAcademico *>::iterator it;
        // Leemos todos los programas del mapa para imprimirlos en el archivo
        for (it = mapadeProgramasAcademicos.begin(); it != mapadeProgramasAcademicos.end(); it++)
        {
            // Imprimimos cada uno de los 8 consolidados por programa
            for (int i = 0; i < 8; i++)
            {
                // Imprimimos toda la información base del programa academico
                archivoResultados << (it->second)->getCodigoDeLaInstitucion() << ";";
                archivoResultados << (it->second)->getIesPadre() << ";";
                archivoResultados << (it->second)->getInstitucionDeEducacionSuperiorIes() << ";";
                archivoResultados << (it->second)->getPrincipalOSeccional() << ";";
                archivoResultados << (it->second)->getIdSectorIes() << ";";
                archivoResultados << (it->second)->getSectorIes() << ";";
                archivoResultados << (it->second)->getIdCaracter() << ";";
                archivoResultados << (it->second)->getCaracterIes() << ";";
                archivoResultados << (it->second)->getCodigoDelDepartamentoIes() << ";";
                archivoResultados << (it->second)->getDepartamentoDeDomicilioDeLaIes() << ";";
                archivoResultados << (it->second)->getCodigoDelMunicipioIes() << ";";
                archivoResultados << (it->second)->getMunicipioDeDomicilioDeLaIes() << ";";
                archivoResultados << (it->second)->getCodigoSniesDelPrograma() << ";";
                archivoResultados << (it->second)->getProgramaAcademico() << ";";
                archivoResultados << (it->second)->getIdNivelAcademico() << ";";
                archivoResultados << (it->second)->getNivelAcademico() << ";";
                archivoResultados << (it->second)->getIdNivelDeFormacion() << ";";
                archivoResultados << (it->second)->getNivelDeFormacion() << ";";
                archivoResultados << (it->second)->getIdMetodologia() << ";";
                archivoResultados << (it->second)->getMetodologia() << ";";
                archivoResultados << (it->second)->getIdArea() << ";";
                archivoResultados << (it->second)->getAreaDeConocimiento() << ";";
                archivoResultados << (it->second)->getIdNucleo() << ";";
                archivoResultados << (it->second)->getNucleoBasicoDelConocimientoNbc() << ";";
                archivoResultados << (it->second)->getIdCineCampoAmplio() << ";";
                archivoResultados << (it->second)->getDescCineCampoAmplio() << ";";
                archivoResultados << (it->second)->getIdCineCampoEspecifico() << ";";
                archivoResultados << (it->second)->getDescCineCampoEspecifico() << ";";
                archivoResultados << (it->second)->getIdCineCodigoDetallado() << ";";
                archivoResultados << (it->second)->getDescCineCodigoDetallado() << ";";
                archivoResultados << (it->second)->getCodigoDelDepartamentoPrograma() << ";";
                archivoResultados << (it->second)->getDepartamentoDeOfertaDelPrograma() << ";";
                archivoResultados << (it->second)->getCodigoDelMunicipioPrograma() << ";";
                archivoResultados << (it->second)->getMunicipioDeOfertaDelPrograma() << ";";

                // Imprimimos la información del consolidado: (ID SEXO;SEXO;AÑO;SEMESTRE;ADMITIDOS;GRADUADOS;INSCRITOS;MATRICULADOS;NEOS)
                Consolidado *consolidadoActual = (it->second)->getConsolidado(i);
                archivoResultados << consolidadoActual->getIdSexo() << ";";
                archivoResultados << consolidadoActual->getSexo() << ";";
                archivoResultados << consolidadoActual->getAno() << ";";
                archivoResultados << consolidadoActual->getSemestre() << ";";
                archivoResultados << consolidadoActual->getAdmitidos() << ";";
                archivoResultados << consolidadoActual->getGraduados() << ";";
                archivoResultados << consolidadoActual->getInscritos() << ";";
                archivoResultados << consolidadoActual->getMatriculados() << ";";
                archivoResultados << consolidadoActual->getMatriculadosPrimerSemestre();
                // Saltamos de linea para la siguiente fila
                archivoResultados << endl;
            }
        }

        // Cambiamos el valor del booleano si logramos llegar hasta este punto
        estadoCreacion = true;
        // Imprimimos ruta donde quedo el archivo
        cout << "Archivo Creado en: " << rutaCompleta << endl;
    }

    archivoResultados.close();
}
