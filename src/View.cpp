#include "View.h"
using namespace std;
View::View()
{
    controlador = new SNIESController();
}

View::~View()
{
    controlador->~SNIESController();
}

bool View::esEntero(const std::string &str)
{
    if (str.empty())
        return false;

    for (char const &c : str)
    {
        if (!std::isdigit(c))
        {
            return false;
        }
    }
    return true;
}

void View::mostrarPantallaBienvenido()
{
    char userAnswer;
    cout << "======================  !Bienvenido al SNIES-Extractor!  ==========================" << endl;
    cout << "===================================================================================" << endl;
    cout << "IMPORTANTE: Los archivos deben estar en una carpeta 'SNIES_EXTRACTOR' con carpetas" << endl;
    cout << "inputs y outputs, donde se encuentren todos los archivos CSV del SNIES." << endl;
    cout << "===================================================================================" << endl;
    parametrizacion();

    string userText;
    cout << endl;
    cout << "A continuacion, se procesaran los datos de los programas academicos que seleccione" << endl;

    string anio1;
    string anio2;
    cout << "--Escriba el primer anio de busqueda: ";
    cin >> anio1;

    if (!esEntero(anio1))
    {
        throw std::invalid_argument("El valor ingresado no es correcto");
    }

    cout << "--Escriba el segundo anio de busqueda: ";
    cin >> anio2;
    cout << endl;

    if (!esEntero(anio2))
    {
        throw std::invalid_argument("El valor ingresado no es correcto");
    }

    if (anio1 >= anio2)
    {
        throw std::invalid_argument("El segundo anio debe ser mayor que el primero");
    }

    cout << "..................................Procesando datos................................." << endl;

    controlador->determinarObjetosDatos(anio1);
    int incremento;
    string incrementoString;

    for (incremento = stoi(anio1); incremento <= stoi(anio2); incremento++)
    {
        incrementoString = std::to_string(incremento);
        controlador->determinarObjetosConsolidados(incrementoString);
    }

    controlador->unificacionDatos();

    cout << endl;
    cout << "!Datos procesados con exito!" << endl;

    menuExportacionDatos();

    cout << endl;
    cout << "===================================================================================" << endl;
    cout << "Desea realizar un filtrado de programas academicos?" << endl;
    cout << "--Ingrese 'Y' o 'N' segun corresponda:" << endl;

    if (eleccionUsuario())
    {
        menuBusqueda();
    }

    cout << endl;
    cout << "===================================================================================" << endl;
    cout << "Desea obtener los datos extra calculados?" << endl;
    cout << "--Ingrese 'Y' o 'N' segun corresponda:" << endl;

    if (eleccionUsuario())
    {
        mostrarDatosExtra();
    }
    cout << endl;

    cout << "===================================================================================" << endl;
    cout << "                    !Gracias Por Utilizar SNIES-EXTRACTOR! :D                      " << endl;
    cout << "===================================================================================" << endl;
}

void View::parametrizacion()
{
    string anioProgramas;
    cout << "==========================Parametros Por Defecto===================================" << endl;
    cout << "Ruta base de la carpeta SNIES_EXTRACTOR/inputs es: " << endl;
    cout << Settings::BASE_PATH << std::endl;
    cout << "Delimitador por defecto: " << Settings::DELIMITADOR << std::endl;
    cout << "Desea realizar cambios?" << std::endl;
    cout << "--Ingrese 'Y' o 'N' segun corresponda: ";

    if (eleccionUsuario())
    {
        string nuevaRuta;
        char delimitador;
        cout << "--Ingrese la nueva ruta base: " << std::endl;
        cin >> nuevaRuta;
        ajustes.setRutaBase(nuevaRuta);

        cout << "--Ingrese el nuevo delimitador: " << std::endl;
        cin >> delimitador;
        ajustes.setDelimitador(delimitador);
    }
    cout << "===================================================================================" << endl;
}
bool View::eleccionUsuario()
{
    char userAnswer;
    cin >> userAnswer;
    userAnswer = static_cast<char>(tolower(userAnswer));
    if (userAnswer != 'y' && userAnswer != 'n')
    {
        throw std::invalid_argument("La opcion ingresada es incorrecta");
    }
    if (userAnswer == 'y')
        return true;

    return false;
}

bool View::isConvetibleToInt(const string &str)
{
    try
    {
        std::size_t pos;
        int num = std::stoi(str, &pos);

        // Verificamos si se ha convertido toda la cadena
        return pos == str.length();
    }
    catch (const std::invalid_argument &)
    {
        // No se pudo convertir: la cadena no es un número válido
        return false;
    }
    catch (const std::out_of_range &)
    {
        // No se pudo convertir: el número está fuera del rango de int
        return false;
    }
}

void View::menuExportacionDatos()
{
    string nombreArchivo;
    cout << endl;
    cout << "===================================================================================" << endl;
    cout << "--Ingrese el nombre con el que se almacenara el archivo exportado: " << endl;
    cin >> nombreArchivo;
    cout << endl;
    int eleccion;
    printTextTiposExportacion();
    cin >> eleccion;

    switch (eleccion)
    {
    case 1:
        controlador->exportarCSV(nombreArchivo);
        break;
    case 2:
        controlador->exportarTXT(nombreArchivo);
        break;
    case 3:
        controlador->exportarJSON(nombreArchivo);
        break;
    default:
        cout << "Eleccion no correcta" << endl;
    }
    cout << "Archivo exportado exitosamente!" << endl;
    cout << endl;
    cout << "Se encuentra en la ruta: " << Settings::OUTPUT_PATH << endl;
}

void View::mostrarDatosExtra()
{
    std::map<std::string, pair<int, int>> mapPorcentual = controlador->diferenciaPorcentualAnual();
    std::map<std::string, pair<int, int>>::iterator itMap;
    int eleccion;
    cout << "===================================================================================" << endl;
    cout << "Diferencia porcentual anual de los nuevos estudiantes matricualados" << endl;
    cout << "Como desea que se muestren los datos los datos?" << endl;
    cout << "1) Mostrar en terminal" << endl;
    cout << "2) Exportar como archivo" << endl;
    cin >> eleccion;
    if (eleccion == 1)
    {
        for (itMap = mapPorcentual.begin(); itMap != mapPorcentual.end(); itMap++)
        {
            cout << "Para el programa: " << itMap->first << endl;
            cout << "Hay una diferencia anual del 2021 al 2022 de: " << itMap->second.first << endl;
            cout << "Y una diferencia del 2022 al 2023 de: " << itMap->second.second << endl;
        }
    }
    else if (eleccion == 2)
    {
        printTextTiposExportacion();
        cin >> eleccion;
        if (eleccion == 1)
        {
            controlador->exportarCVSPorcentajeAnual(mapPorcentual);
        }
        else if (eleccion == 2)
        {
            controlador->exportarTXTPorcentajeAnual(mapPorcentual);
        }
        else if (eleccion == 3)
        {
            controlador->exportarJSONPorcentajeAnual(mapPorcentual);
        }
        else
            cout << "Eleccion no valida" << endl;
    }
    else
        cout << "Eleccion valida" << endl;
    map<std::string, std::string> mapSinMatriculasNuevas = controlador->sinMatriculasNuevas();
    map<std::string, std::string>::iterator itSinMatri;
    cout << "===================================================================================" << endl;
    cout << "Programas que no tienen nuevos estudiantes matriculados durante 3 anios o mas" << endl;
    cout << "Como desea que se muestren los datos los datos?" << endl;
    cout << "1) Mostrar en terminal" << endl;
    cout << "2) Exportar como archivo" << endl;
    cin >> eleccion;
    if (eleccion == 1)
    {
        for (itSinMatri = mapSinMatriculasNuevas.begin(); itSinMatri != mapSinMatriculasNuevas.end(); itSinMatri++)
        {
            cout << "Codigo Snies: " << itSinMatri->first << endl;
            cout << "Programa: " << itSinMatri->second << endl;
        }
    }
    else if (eleccion == 2)
    {
        printTextTiposExportacion();
        cin >> eleccion;
        if (eleccion == 1)
        {
            controlador->exportarCVSDExtraSinMatricula(mapSinMatriculasNuevas);
        }
        else if (eleccion == 2)
        {
            controlador->exportarTXTDExtraSinMatricula(mapSinMatriculasNuevas);
        }
        else if (eleccion == 3)
        {
            controlador->exportarJSONDExtraSinMatricula(mapSinMatriculasNuevas);
        }
        else
            cout << "Eleccion no valida" << endl;
    }
    else
        cout << "Eleccion no valida" << endl;
}

void View::menuBusqueda()
{
    string palabraClave;
    cout << endl;
    cout << "===================================================================================" << endl;
    cout << "--Ingrese la palabra clave con la que desea filtrar los programas academicos: " << endl;
    cin >> palabraClave;
    controlador->busquedaPalabraClave(palabraClave);
}

void View::printTextTiposExportacion()
{
    cout << "--Ingrese la opcion del tipo de formato para el archivo" << endl;
    cout << "1) CVS" << endl;
    cout << "2) txt" << endl;
    cout << "3) json" << endl;
    cout << endl;
}