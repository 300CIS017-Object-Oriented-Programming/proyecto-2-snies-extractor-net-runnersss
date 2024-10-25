[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/QApazJy0)

## SNIES Extractor
Gracias al grupo que me presetó el código fuente de este proyecto

## Presentación general
En este proyecto se utilizarán 5 clases para cumplir el propósito de extraer la información del Sistema Nacional de Información de Educación Superior. Para el usuario, este tendrá una interfaz por terminal que le indicará los pasos a seguir y la información que necesita digitar.

## Cumplimiento de Requerimientos

1. **Solicitar rango de años a analizar**  
   En el menú, se le pregunta al usuario cuál es el primer año de búsqueda, tomando en cuenta que los rangos de años siempre son consecutivos, el segundo año de búsqueda se calcula a partir del primero.

2. **Lectura de archivos .csv correspondientes**  
   A partir de los años ingresados por el usuario, el controlador (clase `SNIESController`) leerá la información de los archivos apropiados uno por uno.

3. **Calcular admitidos, inscritos, graduados, matriculados y matriculados de primer semestre por programa y por año**  
   El SNIES-Extractor, mediante su controlador, calculará estos datos por cada programa y año a partir de los datos en bruto que extrae de los archivos .csv apropiados.

4. **Generación de Archivos de Salida**  
   Al terminar de extraer la información y procesarla, el SNIES-Extractor generará un archivo de resultados en la siguiente carpeta que ya debería estar parametrizada en el disco duro:  
   `C:\SNIES_EXTRACTOR\outputs\resultados.csv`.

5. **Visualización de Datos**  
   El SNIES-Extractor muestra al usuario el consolidado de estudiantes por año en programas presenciales o virtuales, la diferencia porcentual anual entre la cantidad de nuevos matriculados durante los años de búsqueda por programa y la lista de programas sin nuevos matriculados en 3 semestres consecutivos. Además, permitirá al usuario exportar esta información en un archivo ubicado en la carpeta ya parametrizada:  
   `C:\SNIES_EXTRACTOR\outputs\extras.csv`.

6. **Filtrado de Programas**  
   Se le pregunta al usuario si desea hacer una búsqueda con 2 filtros entre los programas solicitados: una palabra clave para buscar según los nombres de programas y el nivel de formación de los programas.

7. **Validación de Datos**  
   El SNIES-Extractor es un programa de C++ robusto que puede detectar errores a la hora de recibir información fuera de rangos esperados, tanto de parte del usuario como de la lectura de los archivos .csv.

Más abajo podrán encontrar el diagrama UML de las clases.

# Correción de errores
   ###  1) Refactorizacion inicial del diagrama de clases : 
Se añadieron nueva clases en el diagrama UML (GestorJson, GestorDatos) donde GestorDatos es la clase padre que hereda sus metodos a las otras clases.

   ### 2) Creación clase GestorJson :
Se implemento una nueva clase que permite exportar documentos de tipo .Json.
   ### 3) Creación clase GestorTxt :
Se implemento una nueva clase que permite exportar documentos de tipo .Txt.

   ### 4) Refactorización clases Consolidado y ProgramaAcademico :
   Se refactorizo las clases Consolidado y ProgramaAcademico para adecuarlas a los principios GRASP.
   ### 5) Creacion clase Settings :
   se implemento una nueva clase en el proyecto donde el usuario es libre de la configuracion.
   ### 6) Modificación de los prototipos de las clases :
   Se modificaron diferentes atributos y metodos de las clases Consolidado, ProgramaAcademico, GestorCSV y SNIESController con el objetivo de reducir la complejidad, aumentar la cohesión y disminuir la codependencia.
   ### 7) Creacion de clase GestorDatos :
   Se implemento una nueva clase quien es la clase padre de GestorCsv, GestorJson, GestorTXT.
   ### 8) Refactorización del metodo exportarDatos :
   se realizaron correciones en el header ya que sonarline siguirio cambiar nuetros std:: en la cabezera y tambien se añadio la libreria estandar.
   ### 9) Implementacion clases ProgramaAcademico y Consolidado
   Se implemento los prototipos de esas clases teniendo como objetivo la construccion de una serie de métodos auxiliares que permitan facilitar las tareas y métodos de las demás clases.
   ### 10) Solucion de error en la clase GestorCSV :
   Se soluciono el error usando using namespace std::.

# Diagrama Mermaid

*El vector de Consolidados tendrá siempre 8 posiciones [0-7] donde:*
*vector[0] es primer año, primer semestre, hombres*
*vector[1] es primer año, segundo semestre, hombres*
*vector[2] es primer año, primer semestre, mujeres*
*vector[3] es primer año, segundo semestre, mujeres*
*vector[4] es segundo año, primer semestre, hombres*
*vector[5] es segundo año, segundo semestre, hombres*
*vector[6] es segundo año, primer semestre, mujeres*
*vector[7] es segundo año, segundo semestre, mujeres*
```mermaid
classDiagram

    class Consolidado{
        -string idSexo
        -string sexo
        -string  ano
        -string  semestre
        -string  inscritos
        -string  admitidos
        -string  matriculados
        -string  matriculadosPrimerSemestre
        -string  graduados
        +string  getIdSexo()
        +void setIdSexo(const std::string&)

        +string getSexo()
        +void setSexo(const std::string&)

        +string  getAno()
        +void setAno(const std::string&)

        +string  getSemestre()
        +void setSemestre(const std::string&)

        +string  getInscritos()
        +void setInscritos(const std::string&)

        +string  getAdmitidos()
        +void setAdmitidos(const std::string&)

        +string  getMatriculados()
        +void setMatriculados(const std::string&)

        +string  getMatriculadosPrimerSemestre()
        +void setMatriculadosPrimerSemestre(const std::string&)

        +string  getGraduados()
        +void setGraduados(const std::string&)
    }




    class DatosInstitucion{
        -string codigoDeLaInstitucion;
        -string iesPadre;
        -string institucionDeEducacionSuperiorIes;
        -string principalOSeccional;
        -string idSectorIes;
        -string sectorIes;
        -string idCaracter;
        -string caracterIes;
        -string codigoDelDepartamentoIes;
        -string departamentoDeDomicilioDeLaIes;
        -string codigoDelMunicipioIes;
        -string municipioDeDomicilioDeLaIes;

        ~DatosInstitucion();

        +void setCodigoDeLaInstitucion(const std::string &);
        +string getCodigoDeLaInstitucion();

        +void setIesPadre(const std::string &);
        +string getIesPadre();

        +void setInstitucionDeEducacionSuperiorIes(const std::string &);
        +string getInstitucionDeEducacionSuperiorIes();

        +void setPrincipalOSeccional(const std::string &);
        +string getPrincipalOSeccional();

        +void setIdSectorIes(const std::string &);
        +string getIdSectorIes();

        +void setSectorIes(const std::string &);
        +string getSectorIes();

        +void setIdCaracter(const std::string &);
        +string getIdCaracter();

        +void setCaracterIes(const std::string &);
        +string getCaracterIes();

        +void setCodigoDelDepartamentoIes(const std::string &);
        +string getCodigoDelDepartamentoIes();

        +void setDepartamentoDeDomicilioDeLaIes(const std::string &);
        +string getDepartamentoDeDomicilioDeLaIes();

        +void setCodigoDelMunicipioIes(const std::string &);
        +string getCodigoDelMunicipioIes();

        +void setMunicipioDeDomicilioDeLaIes(const std::string &);
        +string getMunicipioDeDomicilioDeLaIes();
    }

    class ProgramaAcademico{
        -string codigoSniesDelPrograma;
        -string programaAcademico;
        -string idNivelAcademico;
        -string nivelAcademico;
        -string idNivelDeFormacion;
        -string nivelDeFormacion;
        -string idMetodologia;
        -string metodologia;
        -string idArea;
        -string areaDeConocimiento;
        -string idNucleo;
        -string nucleoBasicoDelConocimientoNbc;
        -string idCineCampoAmplio;
        -string descCineCampoAmplio;
        -string idCineCampoEspecifico;
        -string descCineCampoEspecifico;
        -string idCineCodigoDetallado;
        -string descCineCodigoDetallado;
        -string codigoDelDepartamentoPrograma;
        -string departamentoDeOfertaDelPrograma;
        -string codigoDelMunicipioPrograma;
        -string municipioDeOfertaDelPrograma;
        +ProgramaAcademico();
        +void setCodigoSniesDelPrograma(const std::string&);
        +string getCodigoSniesDelPrograma();

        +void setProgramaAcademico(const std::string&);
        +string getProgramaAcademico();

        +void setIdNivelAcademico(const std::string&);
        +string getIdNivelAcademico();

        +void setNivelAcademico(const std::string&);
        +string getNivelAcademico();

        +void setIdNivelDeFormacion(const std::string&);
        +string getIdNivelDeFormacion();

        +void setNivelDeFormacion(const std::string&);
        +string getNivelDeFormacion();

        +void setIdMetodologia(const std::string&);
        +string getIdMetodologia();
        +void setMetodologia(const std::string&);
        +string getMetodologia();

        +void setIdArea(const std::string&);
        +string getIdArea();
        +void setAreaDeConocimiento(const std::string&);
        +string getAreaDeConocimiento();
        +void setIdNucleo(const std::string&);
        +string getIdNucleo();
        +void setNucleoBasicoDelConocimientoNbc(const std::string&);
        +string getNucleoBasicoDelConocimientoNbc();
        +void setIdCineCampoAmplio(const std::string&);
        +string getIdCineCampoAmplio();
        +void setDescCineCampoAmplio(const std::string&);
        +string getDescCineCampoAmplio();
        +void setIdCineCampoEspecifico(const std::string&);
        +string getIdCineCampoEspecifico();
        +void setDescCineCampoEspecifico(const std::string&);
        +string getDescCineCampoEspecifico();
        +void setIdCineCodigoDetallado(const std::string&);
        +string getIdCineCodigoDetallado();
        +void setDescCineCodigoDetallado(const std::string&);
        +string getDescCineCodigoDetallado();
        +void setCodigoDelDepartamentoPrograma(const std::string&);
        +string getCodigoDelDepartamentoPrograma();
        +void setDepartamentoDeOfertaDelPrograma(const std::string&);
        +string getDepartamentoDeOfertaDelPrograma();
        +void setCodigoDelMunicipioPrograma(const std::string&);
        +string getCodigoDelMunicipioPrograma();
        +void setMunicipioDeOfertaDelPrograma(const std::string&);
        +string getMunicipioDeOfertaDelPrograma();
    }

    class UnionDatos{
        -ProgramaAcademico *programa;
        -DatosInstitucion *institucion;
        -vector<Consolidado *> consolidados;
        +void setPrograma(ProgramaAcademico *prog);
        +void setInstitucion(DatosInstitucion *inst);

        +void setConsolidados(const vector<Consolidado *> &nuevosConsolidados);

        +ProgramaAcademico *getPrograma() const;
        +DatosInstitucion *getInstitucion() const;
        +vector<Consolidado *> getConsolidado() const;
    }
    class SNIESController{
        -map<string, ProgramaAcademico *> programasAcademicos;
        -map<string, DatosInstitucion *> datosInstituciones;
        -map<string, map<string, Consolidado *>> listaConsolidados;
        -map<std::string, UnionDatos *> unificacion;
        -GestorCsv *gestorCsvObj;
        -EscrituraTxt *gestorTxtObj;
        -EscrituraJson *gestorJsonObj;
        -vector<string> etiquetasColumnas;
        -string rutaOutput;
        -std::vector<std::vector<std::string>> asignarAdmitidos(int anio1);
        -std::vector<std::vector<std::string>> asignarInscritos(int anio);
        -std::vector<std::vector<std::string>> asignarMatriculados(int anio);
        -std::vector<std::vector<std::string>> asignarMatriculadosPrimerSemestre(int anio);
        -std::vector<std::vector<std::string>> asignarGraduados(int anio);
        -std::unordered_map<std::string, int> nombresEncabezados(std::vector<std::vector<std::string>> &datos);
        -std::string normalizarCodigo(const string &primerComponente, const string &segundoComponente, const string &separador);
        -std::string convertirMinusculas(const std::string &cadena);

        +SNIESController();
        +~SNIESController();
        +void unificacionDatos();
        +void determinarObjetosDatos(string &anio1);
        +void determinarObjetosConsolidados(string &anio1);
        +void exportarCVSDExtraSinMatricula(const map<std::string, std::string> &programasSinMatriculados);
        +void exportarTXTDExtraSinMatricula(const map<std::string, std::string> &programasSinMatriculados);
        +void exportarJSONDExtraSinMatricula(const map<std::string, std::string> &programasSinMatriculados);
        +void exportarCVSPorcentajeAnual(const map<std::string, pair<int, int>> &programaDiferenciaPorcentual);
        +void exportarTXTPorcentajeAnual(const map<std::string, pair<int, int>> &programaDiferenciaPorcentual);
        +void exportarJSONPorcentajeAnual(const map<std::string, pair<int, int>> &programaDiferenciaPorcentual);
        +void exportarCSV(const string &nombreArchivo);
        +void exportarTXT(const string &nombreArchivo);
        +void exportarJSON(const string &nombreArchivo);
        +map<std::string, pair<int, int>> diferenciaPorcentualAnual();
        +int formulaPorcentual(int totalAnio1, int totalAnio2);
        +map<std::string, std::string> sinMatriculasNuevas();
        +void busquedaPalabraClave(const string &palabraClave);
        +void mostrarMapa(const map<std::string, UnionDatos *> &mapDatosConpalabraclave);
    }

    class GestorCsv{
        +Settings config;
        -GestorCsv() = default;
        -unordered_map<string, int> extraerEncabezados(const string &ruta);
        -vector<vector<string>> extraerDatos(string &ruta);
        -unordered_map<string, int> extraerIndices(string &ruta, std::vector<std::string> camposImportantes);
        -void eliminarIndices(std::unordered_map<std::string, int> &indices, std::vector<std::vector<std::string>> &datos);
        -bool escrituraCsv(map<std::string, UnionDatos *> unificacion, string &ruta);
        -string escribirDatosCsv(const UnionDatos *unionDatos);
}

    class View{
    -SNIESController *controlador;
    -Settings ajustes;
    -bool esEntero(const std::string &str);
    -bool eleccionUsuario();
    +View();
    ~View();
    +void menuBusqueda();
    +void mostrarPantallaBienvenido();
    +void mostrarDatosExtra();
    +bool isConvetibleToInt(const string &);
    +void parametrizacion();
    +void menuExportacionDatos();
    +void printTextTiposExportacion();
    }

    class Settings{
        +static string ADMITIDOS_FILE_PATH;
        +static string MATRICULADOS_FILE_PATH;
        +static string NEOS_FILE_PATH;
        +static string INSCRITOS_FILE_PATH;
        +static string PROGRAMAS_FILTRAR_FILE_PATH;
        +static string BASE_PATH;
        +static string OUTPUT_PATH;
        +static string DELIMITADOR;
        +static string GRADUADOS_FILE_PATH;
        +static vector<string> camposImportantes;
        +static vector<string> camposConsolidados;
        +static void setRutaBase(const string &nuevaRutaBase);
        +static void setAnioProgramas(string anioProgramas);
        +static void setDelimitador(const char &delimitador);
        +static string getDelimitador();
}

    class Escritura{
        +virtual bool escrituraDatos(map<std::string, UnionDatos *> unificacion, string &ruta) = 0;
        +virtual bool escrituraNoMatriculados(const map<std::string, std::string> &programasSinMatriculados) = 0;
        +virtual bool escrituraPorcentajeDesencenso(const map<std::string, pair<int, int>> &programaYDifirencialAnual) = 0;
        +virtual ~Escritura() = default;
}
    class EscrituraJson{
        -json convertirDatos(const UnionDatos *unionDatos);
        +bool escrituraDatos(std::map<std::string, UnionDatos *> unificacion, std::string &ruta) override;
        +bool escrituraNoMatriculados(const std::map<std::string, std::string> &programasSinMatriculados) override;
        +bool escrituraPorcentajeDesencenso(const std::map<std::string, pair<int, int>> &programaYDifirencialAnual) override;
}
    class EscrituraTxt{
        -string convertirDatos(const UnionDatos *unionDatos);
        +bool escrituraDatos(std::map<std::string, UnionDatos *> unificacion, std::string &ruta) override;
        +bool escrituraNoMatriculados(const std::map<std::string, std::string> &programasSinMatriculados) override;
        +bool escrituraPorcentajeDesencenso(const std::map<std::string, pair<int, int>> &programaYDifirencialAnual) override;
    }
    class Main{
        -int main()
    }
    Main..>View:usa
    View-->SNIESController : Contiene
    SNIESController o-- ProgramaAcademico:Tiene varios
    SNIESController o-- Consolidado:Tiene varios
    SNIESController o-- DatosInstitucion:Tiene varios
    SNIESController o-- UnionDatos:Tiene varios
    SNIESController --> Escritura:Tiene
    SNIESController --> GestorCsv:tiene
    UnionDatos o-- Consolidado:Tiene varios
    UnionDatos --> ProgramaAcademico:Tiene
    UnionDatos --> DatosInstitucion:Tiene
    Escritura <|-- EscrituraTxt:Hereda
    Escritura <|-- EscrituraJson:Hereda
    GestorCsv --> Settings:Tiene
```
