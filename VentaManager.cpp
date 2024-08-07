#include "VentaManager.h"
#include <limits>

//////////////////////////////   METODOS DE SUBMENUS   ///////////////////////////////////////////

void VentaManager :: ListarVenta()
{
    Venta ven;
    Prenda pren;
    bool SeparadorDeRemitos = false; //BANDERA QUE PERMITE PONER EL PRECIO AL FINAL SIN REPETIRSE ENTRE OBJETOS PRENDAS
    float totalVendido= 0;
    int Reg_Ventas = _ArchVenta.ContarRegistrosVenta(); // calcula la cantidad de registros de venta
    int Reg_Prendas = _ArchiPrenda.ContarRegistrosPrenda();
    int codigoActual = -1; // para almacenar el codigo de venta actual

    for(int x = 0; x < Reg_Ventas; x++) //RECORRO LAS VENTAS POR SU CODIGO Y MUESTRO TODAS LAS EXISTENTES
    {
        ven = _ArchVenta.LeerVenta(x); // me paro en las ventas
        int codigoVenta = ven.getCodigoVenta();


        if (codigoVenta != codigoActual) //esto para que se muestre la primera vez de cada venta
        { //si es un nuevo grupo de venta
            cout << "==========================================" << endl;
            cout << "VENTA NRO " << codigoVenta << endl;
            cout << "FECHA DE COMPROBANTE: "
                 << ven.getVentaFecha().getDia() << "/"
                 << ven.getVentaFecha().getMes() << "/"
                 << ven.getVentaFecha().getAnio() << endl;
            cout << "------------------------------------------" << endl;
            codigoActual = codigoVenta;
            cout << endl;
        }//si es de la misma venta imprime

        for(int i = 0 ; i < Reg_Prendas ; i ++) //RECORRO TODAS LAS PRENDAS, Y MUESTRO SOLO LAS QUE SE VENDIERON DE ESA VENTA
        {
            pren = _ArchiPrenda.LeerPrenda(i);
            if(pren.getCodigo() == ven.getCodigo()) //LAS RELACIONO POR SU CODIGO
            {
                cout << "PRENDA: " << ven.getNombrePrenda() << endl;
                cout << "CANTIDAD: " << ven.getCantidad() << endl;
                cout << "PRECIO DE LA PRENDA: $" << ven.getPrecioVenta() << endl;
                totalVendido+= pren.GetPrecioVenta(); //ACUMULO LO GASTADO, LA PROPIEDAD DE VENTATOTAL NO FUNCIONABA CORRECTAMENTE
                cout << endl;
            }
        }

        //pregunto si es la ultima venta o si la venta que sigue es distinta al codigo actual
        if (x == Reg_Ventas - 1 || _ArchVenta.LeerVenta(x + 1).getCodigoVenta() != codigoActual)
        {
            cout << "TOTAL VENDIDO: $" << totalVendido << endl;
            cout << endl << endl;
            totalVendido = 0;
        }

    }
        cout << "==========================================" << endl;
}

void VentaManager :: BuscarVentaPorFecha()
{
    int dia, mes, anio, totalVendido;
    bool Encontro;  //detecta si se encontro o no una venta en esa fecha
    char Salir = 'n';       //usamos char para evitar que se rompa al tocar cualquier tecla
    int cantidad = _ArchVenta.ContarRegistrosVenta();
    int Reg_Prendas = _ArchiPrenda.ContarRegistrosPrenda();
    Venta ven;

    do
    {
        int codigoActual = -1;
        system("cls");
        cout << "INGRESE LA FECHA EN LA QUE DESEA BUSCAR UNA VENTA" << endl;
        cout << "--------------------------------------------------" << endl;
        system("pause");
        cout << endl;
        cout << "INDIQUE EL DIA: ";
        cin >> dia;
        cout << endl;
        cout << "INDIQUE EL MES: ";
        cin >> mes;
        cout << endl;
        cout << "INDIQUE EL ANIO: ";
        cin >> anio;
        cout << endl;

        if(dia <= 31 && dia >= 1 && mes <= 12 && mes >= 1 && anio >= 1986 && anio <= 2024)
        {
            system("cls");
            Encontro = false;
            for(int x = 0 ; x < cantidad ; x ++)
            {
                ven = _ArchVenta.LeerVenta(x);
                if(ven.getVentaFecha().getDia() == dia && ven.getVentaFecha().getMes() == mes && ven.getVentaFecha().getAnio() == anio)
                {
                    if(!Encontro)
                    {
                    cout << "|     VENTAS DE LA FECHA ' " << dia << "/" << mes << "/" << anio << " '     |" << endl << endl;
                    }
                    int codigoVenta = ven.getCodigoVenta();
                    Encontro = true;
                    if (codigoVenta != codigoActual) //ACA SOLO SE MOSTRARA EL CODIGO DE VENTA 1
                    { //si es un nuevo grupo de venta
                        cout << "==========================================" << endl;
                        cout << "VENTA NRO " << codigoVenta << endl;
                        cout << "FECHA DE COMPROBANTE: "
                             << ven.getVentaFecha().getDia() << "/"
                             << ven.getVentaFecha().getMes() << "/"
                             << ven.getVentaFecha().getAnio() << endl;
                        cout << "------------------------------------------" << endl;
                        codigoActual = codigoVenta;
                        cout << endl;
                    }//si es de la misma venta imprime

                    for(int i = 0 ; i < Reg_Prendas ; i ++) //RECORRO TODAS LAS PRENDAS, Y MUESTRO SOLO LAS QUE SE VENDIERON
                    {
                        Prenda pren = _ArchiPrenda.LeerPrenda(i);
                        if(pren.getCodigo() == ven.getCodigo()) //LAS RELACIONO POR SU CODIGO
                        {
                            cout << "PRENDA: " << ven.getNombrePrenda() << endl;
                            cout << "CANTIDAD: " << ven.getCantidad() << endl;
                            cout << "PRECIO DE LA PRENDA: $" << ven.getPrecioVenta() << endl;
                            totalVendido+= pren.GetPrecioVenta(); //ACUMULO LO GASTADO, LA PROPIEDAD DE VENTATOTAL NO FUNCIONABA CORRECTAMENTE
                            cout << endl;
                        }
                    }

                    Venta Prox_Venta = _ArchVenta.LeerVenta(x + 1);

                    if (x == cantidad - 1 || Prox_Venta.getCodigoVenta() != codigoActual)
                    {
                        cout << "TOTAL VENDIDO: $" << totalVendido << endl;
                        cout << endl << endl;
                        totalVendido = 0;
                    }
                }
            }
            if(!Encontro)
            {
                cout << "NO SE ENCONTRARON VENTAS EN LA FECHA ' " << dia << "/" << mes << "/" << anio << " '" << endl;
                system("pause");
            }else
            {
            cout << "==========================================" << endl;
            system("pause");
            }

            system("cls");
            cout << "DESEA SEGUIR BUSCANDO? '1' - NO / CUALQUIER OTRA TECLA - SI" << endl;
            cout << "------------------------------------------------------------" << endl;
            cin >> Salir;
        }else
        {
            system("cls");
            cout << "FECHA ERRONEA, INTRODUZCA VALORES LOGICOS." << endl;
            if(cin.fail()) //funciona de forma booleana, si devuelve true significa que hubo un error o lo que se ingreso no corresponde con el tipo de dato
            {
                cin.clear(); //limpia el error en la entrada
                cin.ignore(); //ignora el resto de caracteres que puedan molestar para seguir el flujo del programa
            }
            system("pause");
            system("cls");
            cout << "DESEA SEGUIR BUSCANDO? '1' - NO / CUALQUIER OTRA TECLA - SI" << endl;
            cout << "------------------------------------------------------------" << endl;
            cin >> Salir;
        }


    }while(Salir != '1');

}

void VentaManager::CalcularPorMes() {
    int cantidad_registros = _ArchVenta.ContarRegistrosVenta();
    Venta ven;
    int mes;
    bool igualdad = false;
    int inversion;
    int TotalGenerado = 0;

    // Sacar el total de precios de todas las ventas en el mes que indique el usuario
    if (cantidad_registros > 0) {
        do {
            system("cls");
            cout <<endl<< "Seleccione el mes: " << endl;
            cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
            cout << "1=Enero 2=Febrero 3=Marzo 4=Abril 5=Mayo 6=Junio 7=Julio " << endl;
            cout << "8=Agosto 9=Septiembre 10=Octubre 11=Noviembre 12=Diciembre" << endl;
            cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
            cout << "Ingrese el numero correspondiente al mes: ";
            cout << endl;

            // Leer la entrada del usuario
            cin >> mes;

            // Validar si la entrada es un numero y esta en el rango correcto (1 a 12)
            if (cin.fail() || mes < 1 || mes > 12) {
                cout << "Por favor, ingrese un numero valido de mes (1 a 12)." << endl;
                // Limpiar el estado de error de cin y descartar la entrada incorrecta
                cin.clear(); // Limpia el buffer de entrada
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar la entrada incorrecta
            } else {
                break; // Salir del bucle si la entrada es valida
            }
        } while (true);

        // Verificar si hay ventas en el mes elegido y calcular el total generado
        for (int x = 0; x < cantidad_registros; x++) {
            ven = _ArchVenta.LeerVenta(x);
            if (ven.getVentaFecha().getMes() == mes) {
                igualdad = true;
                TotalGenerado += ven.getPrecioVenta();
            }
        }

        if (igualdad) { // Si hay ventas en ese mes
            do {
                cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
                cout << "Ingrese el monto invertido: $";
                cin >> inversion;

                if (cin.fail() || inversion <= 0) {
                    cout << "Monto incorrecto. Intentelo de nuevo." << endl;
                    // Limpiar el estado de error de cin y descartar la entrada incorrecta
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                } else {
                    break; // Salir del bucle si la entrada es valida
                }
            } while (true);

            system("cls");
            cout << "Genial! Tu monto invertido es " << inversion << endl;

            int ganancia_neta = TotalGenerado - inversion;
            if (ganancia_neta < 0) {
                ganancia_neta = 0;
            }

            float porcentaje_ganancia = (ganancia_neta / inversion) * 100;

            cout << "El total generado por ventas en el mes es: $" << TotalGenerado << endl;
            cout << "La ganancia neta es: $" << ganancia_neta << endl;
            cout << "El porcentaje de ganancia es: " << porcentaje_ganancia << "%" << endl;

        } else {
            cout << "No se pudo realizar la estadistica porque no hay ventas registradas en ese mes" << endl;
        }

    } else {
        cout << "No se registraron ventas en el programa..." << endl;
    }
}

void VentaManager::CalcularPorAnio() {
    int cantidad_registros = _ArchVenta.ContarRegistrosVenta();
    Venta ven;
    int inversion;
    int VecMeses[12] = {0};
    int TotalGenerado = 0;
    int VecTotalGenerado[12] = {0};

    if (cantidad_registros > 0) {
        for (int x = 0; x < cantidad_registros; x++) {
            ven = _ArchVenta.LeerVenta(x);
            VecMeses[ven.getVentaFecha().getMes() - 1] += ven.getPrecioVenta();
            VecTotalGenerado[ven.getVentaFecha().getMes() - 1] += ven.getPrecioVenta();
            TotalGenerado += ven.getPrecioVenta();
        }
    }

    do {
        cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
        cout << "Ingrese el monto invertido de todo el anio: ";
        cin >> inversion;

        if (cin.fail() || inversion <= 0) {
            cout << "Monto incorrecto. Intentelo de nuevo." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    } while (true);

    system("cls");
    cout << "Tu monto invertido es " << inversion << endl;
    cout << "Porcentaje de ganancia y total generado en todos los meses del anio:" << endl;
    cout <<endl;

    for (int i = 0; i < 12; ++i) {
        int inversionMensual = inversion / 12;
        int ganancia_neta = VecTotalGenerado[i] - inversionMensual;
        float PorcentajeGananciaMes = (ganancia_neta / inversionMensual) * 100;

        if (VecTotalGenerado[i] == 0) {
            cout << "Mes " << (i + 1) << ": " << 0 << "%, Total Generado: " << VecTotalGenerado[i] << endl;
            cout <<endl;
        } else {
             cout << "Mes " << (i + 1) << ": " << "Ganancia Neta: " << ganancia_neta<<"$" << ",  Porcentaje de Ganancia: " << PorcentajeGananciaMes << "%,  Total Generado: " << VecTotalGenerado[i]<<"$" << endl;
             cout <<endl;
        }
    }
}

//////////////////////////////   DESARROLLO DE SUBMENUS   ///////////////////////////////////////////

void VentaManager::SubMenuCargarVenta()
{
    Venta _ven;
    int cod_venta, CodigoSeleccionado;
    char Salir = 'n';
    Fecha obj;
    int CantPrendas = _ArchiPrenda.ContarRegistrosPrenda();
    bool bandera;
    if(CantPrendas > 0)
    {
        cout << "BIENVENIDO! ESTA USTED POR REALIZAR UNA VENTA" << endl;
        cout << "----------------------------------------------" << endl;

        float totalVendido= 0; ///acumulador de lo q se vendio total
        cod_venta = _ArchVenta.NuevoCodigoDeVenta();
        _ven.setCodigoDeVenta(cod_venta); //codigo de venta unico, lo genero aca porque dentro de algun bucle puede generar un numero erroneo

        while (Salir != '1')
        {

            _PrendManager.SubmenuInventario();
                cout <<endl<< "SELECCIONE EL CODIGO DE PRENDA A VENDER: ";
                cout<<"(TOTAL ACUMULADO AL MOMENTO EN ESTA VENTA : $"<< totalVendido <<")" << endl;
                cin >> CodigoSeleccionado;
                cout << endl;
            while(cin.fail() ){ //para saber si se ingreso un caracter
                    cin.clear();
                    cin.ignore();
                    system("cls");
                    cout<<"Ingresaste un numero invalido"<<endl;
                    break;
            }


           while(CodigoSeleccionado<0 || CodigoSeleccionado>200 ){// validar que sea un numero valido
                cout<<"Por favor, Ingrese un numero valido"<<endl;//si entro mal....
                system("pause");
                system("cls");
                _PrendManager.SubmenuInventario();
                cout <<endl<< "SELECCIONE EL CODIGO DE PRENDA A VENDER: ";
                cout<<"(TOTAL ACUMULADO AL MOMENTO EN ESTA VENTA : $"<< totalVendido <<")" << endl;
                cin >> CodigoSeleccionado;
                cout << endl;
            }

            bool prendaEncontrada = false;  // bandera para controlar el guardado de la venta
            //lo de prendaEncontrada es por q al modificar me duolicaba la prenda

            int cInicial=0; //cantidad de ventas segun prenda

            for (int x = 0; x < CantPrendas; x++)
            {
                _Prenda= _ArchiPrenda.LeerPrenda(x);

                if (_Prenda.getCodigo() == CodigoSeleccionado && _Prenda.getEstadoDePrenda())
                { //creamos el objeto para guardar en venta
                    _ven.setCodigoPrenda(_Prenda.getCodigo());
                    _ven.setNombrePrenda(_Prenda.getNombrePrenda());
                    _ven.setModelo(_Prenda.getModelo());
                    _ven.setTalle(_Prenda.getTalle());
                    _ven.setColor(_Prenda.getColor());
                    _ven.setPrecioVenta(_Prenda.GetPrecioVenta());
                    _ven.setVentaFecha(obj.ReturnFechaActual());
                    prendaEncontrada = true;  // Marcamos que encontramos la prenda
                    cInicial++;
                    _ven.setCantidad(cInicial);
                    totalVendido+= _Prenda.GetPrecioVenta();
                     //Guardamos la venta una sola vez
                    _ArchVenta.GuardarVenta(_ven);
                    system("cls");
                    cout << "----------------------------------------------" << endl << endl;
                    cout <<"CODIGO DE VENTA NUMERO: "<<_ven.getCodigoVenta() << endl;

                    break;  // Salimos del bucle una vez que encontramos la prenda
                }

            }

            if (prendaEncontrada) // actualizamos el stock de la prenda que se vendio
            {

                for (int x = 0; x < CantPrendas; x++)
                {
                    _Prenda= _ArchiPrenda.LeerPrenda(x);

                    if (_Prenda.getCodigo() == _ven.getCodigo()) //si la prenda es la que se vendio
                    {
                        int pos = _ArchiPrenda.BuscarCodigoPrenda(x + 1);

                        _Prenda.setCantidad(_Prenda.getCantidad() - cInicial); //seteamos la cantidad

                        if (_Prenda.getCantidad() <= 0)
                        {  // Si el stock queda en 0 le hacemos una baja l�gica
                            _Prenda.setEstadoDePrenda(false);
                        }

                        cout <<"EN ESTA VENTA: $"<<totalVendido<< endl << endl;
                        cout << "----------------------------------------------" << endl;
                        _ArchiPrenda.SobreescribirArchivoPrenda(pos, _Prenda);
                        system("pause");
                        break;  // Salimos del bucle una vez que actualizamos la prenda
                    }
                }
            }else
            {
                system("cls");
                cout << "PRENDA NO ENCONTRADA" << endl;
                system("pause");
            }

            ///hacer un for para sobreescrir la venta actualizada
            system("cls");
            cout << "DESEA AGREGAR OTRO PRODUCTO A LA VENTA? CUALQUIER TECLA - SI / 1 - NO" << endl;
            cout<<"(TOTAL ACUMULADO AL MOMENTO EN ESTA VENTA : $"<< totalVendido <<")" << endl;
            cin >> Salir;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");

        }

    }else
    {
        cout << "NO SE REGISTRAN VENTAS" << endl;
    }

}

void VentaManager::SubMenuEstadisticaProductos() {

    int CantVentas = _ArchVenta.ContarRegistrosVenta();

    if (CantVentas <= 0) {
        cout << "NO SE REGISTRARON VENTAS HASTA EL MOMENTO" << endl;
        return;
    }

    char opcion[10];
    system("cls");
    cout << "---------------------------------" << endl;
    cout << "1 - Filtrar por mes y anio" << endl;
    cout << "                              " << endl;
    cout << "2 - Filtrar por anio" << endl;
    cout << "---------------------------------" << endl<<endl;
    cin >> opcion;

    switch (opcion[0]) {
        case '1': {
            int mes, anio;
            bool ventasEncontradas = false;

            do { // el do while es para validar que se encuentren fechas validas
                system("cls");
                cout << "Ingrese el mes (1-12): ";
                cin >> mes;
                while(cin.fail()||mes>12 ||mes<1 ){ //validacion para que se ingrese un mes correcto
                        cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    system("cls");
                    cout << "Debe ingresar un numero entre 1 al 12 "<<endl;
                    cout<< "(--ingrese nuevamente--)" <<endl;
                    cin>> mes;
                }
                cout << "Ingrese el anio: ";
                cin >> anio;
                while(cin.fail()||anio<2024 || anio>2030 ){//validacion para que se ingrese un anio correcto
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    system("cls");
                    cout<< "Estas insertando un anio invalido "<<endl;
                    cout<<"(--por favor, Ingrese un n�mero entre el 2024 y 2030--)" <<endl;
                    cin>> anio;
                }

                // Crear vector din�mico
                Venta *vec = new Venta[CantVentas]; // pedimos memoria por la cantidad de ventas
                Venta _venta, aux;

                int contador = 0;

                // Leer las ventas
                for (int x = 0; x < CantVentas; x++) {
                    _venta = _ArchVenta.LeerVenta(x);

                    // Filtrar por mes y a�o
                    if (_venta.getVentaFecha().getMes() == mes && _venta.getVentaFecha().getAnio() == anio) {
                        bool existe = false;

                        // Comprobar si la venta ya esta en el vector (la primera vez de cada venta no va a entrar)
                        for (int y = 0; y < contador; y++) {
                            if (vec[y].getCodigoPrenda() == _venta.getCodigoPrenda()) {
                                vec[y].setCantidad(vec[y].getCantidad() + _venta.getCantidad());
                                existe = true;
                                break;
                            }
                        }

                        // Si la venta no existe, agregarla al vector (la primera vez de cada venta entra aca)
                        if (!existe) {
                            vec[contador] = _venta;
                            contador++;
                        }
                    }
                }

                if (contador == 0) { // sino se encontro fecha valida tira el cartel y libera memoria
                    cout << "NO SE REGISTRARON VENTAS PARA EL MES Y ANIO INGRESADOS" << endl;
                    cout << "INTENTE CON OTRAS FECHAS VALIDAS" << endl;
                    delete[] vec;
                } else { // si se encontro fecha muestra todo
                    ventasEncontradas = true; // filtro para terminar el ciclo

                    system("cls");
                    cout << "------------------------------------------" << endl;
                    cout << "PRODUCTOS MAS VENDIDOS DEL MES #" << mes << " DEL " << anio << endl;
                    cout << "------------------------------------------" << endl;

                    // Ordenar las ventas por cantidad en orden descendente
                    for (int x = 0; x < contador - 1; x++) {
                        for (int y = 0; y < contador - x - 1; y++) {
                            if (vec[y].getCantidad() < vec[y + 1].getCantidad()) {
                                aux = vec[y + 1];
                                vec[y + 1] = vec[y];
                                vec[y] = aux;
                            }
                        }
                    }

                    // Mostrar las estad�sticas de ventas
                    for (int x = 0; x < contador; x++) {
                        if (vec[x].getCantidad() > 0) {
                            cout << vec[x].getNombrePrenda()<<" "<<vec[x].getModelo() << ": " << vec[x].getCantidad() << endl;
                        }
                    }

                    // Liberar la memoria del vector din�mico
                    delete[] vec;
                }
            } while (!ventasEncontradas);

            break;
        }
        case '2': {
            int anio;
            bool ventasEncontradas = false;

            do { // el do while es para validar que el a�o sea valido
                cout << "Ingrese el anio: ";
                cin >> anio;
                while(cin.fail()||anio<2024 || anio>2030 ){
                    cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    system("cls");
                    cout<< "Estas insertando un anio invalido "<<endl;
                    cout<<"(--por favor, Ingrese un n�mero entre el 2024 y 2030--)" <<endl;
                    cin>> anio;
                }

                // Crear vector din�mico
                Venta *vec = new Venta[CantVentas]; // pedimos memoria por la cantidad de ventas
                Venta _venta, aux;

                int contador = 0;

                // Leer las ventas
                for (int x = 0; x < CantVentas; x++) {
                    _venta = _ArchVenta.LeerVenta(x);

                    // Filtrar por a�o
                    if (_venta.getVentaFecha().getAnio() == anio) {
                        bool existe = false;

                        // Comprobar si la venta ya esta en el vector (la primera vez de cada venta no va a entrar)
                        for (int y = 0; y < contador; y++) {
                            if (vec[y].getCodigoPrenda() == _venta.getCodigoPrenda()) {
                                vec[y].setCantidad(vec[y].getCantidad() + _venta.getCantidad());
                                existe = true;
                                break;
                            }
                        }

                        // Si la venta no existe, agregarla al vector (la primera vez de cada venta entra aca)
                        if (!existe) {
                            vec[contador] = _venta;
                            contador++;
                        }
                    }
                }

                if (contador == 0) { // sino se encontro fecha valida tira el cartel y libera memoria
                    cout << "NO SE REGISTRARON VENTAS PARA EL ANIO INGRESADO" << endl;
                    cout << "INTENTE CON OTRO ANIO VALIDO" << endl;
                    delete[] vec;
                } else { // si se encontro fecha muestra todo
                    ventasEncontradas = true; // filtro para terminar el ciclo

                    system("cls");
                    cout << "------------------------------------------" << endl;
                    cout << "PRODUCTOS MAS VENDIDOS DEL ANIO #" << anio << endl;
                    cout << "------------------------------------------" << endl;

                    // Ordenar las ventas por cantidad en orden descendente
                    for (int x = 0; x < contador - 1; x++) {
                        for (int y = 0; y < contador - x - 1; y++) {
                            if (vec[y].getCantidad() < vec[y + 1].getCantidad()) {
                                aux = vec[y + 1];
                                vec[y + 1] = vec[y];
                                vec[y] = aux;
                            }
                        }
                    }

                    // Mostrar las estad�sticas de ventas
                    for (int x = 0; x < contador; x++) {
                        if (vec[x].getCantidad() > 0) {
                            cout << vec[x].getNombrePrenda() <<" "<<vec[x].getModelo() << ": " << vec[x].getCantidad() << endl;
                        }
                    }

                    // Liberar la memoria del vector din�mico
                    delete[] vec;
                }
            } while (!ventasEncontradas);

            break;
        }
        default:
            system("cls");
            cout << "Opcion no valida. Intente de nuevo." << endl;
            if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout <<endl<< "DEBES TOCAR CUALQUIER TECLA PARA VOLVER E INTENTARLO DE NUEVO" << endl;
                    system("pause");
                }
            break;
    }
}

void VentaManager :: SubMenuHistorialDeVenta()
{
    int cantidad_registros = _ArchVenta.ContarRegistrosVenta();
    int Opcion;

    if(cantidad_registros > 0)
    {
        system("cls");
        cout << "REGISTROS CONTABLES DE VENTAS" << endl;
        cout << "---------------------------------" << endl;
        cout << "1 - VER TODOS" << endl;
        cout << endl;
        cout << "2 - VERLOS POR FECHA" << endl;
        cout << endl;
        cout << "0 - MENU ANTERIOR" << endl;
        cout << "----------------------------------" << endl;
        cin >> Opcion;
        switch(Opcion)
        {
        case 1:
            {
                system("cls");
                ListarVenta();
                break;
            }
        case 2:
            {
                BuscarVentaPorFecha();
                break;
            }

        case 0:
            {
                return;
                break;
            }
        }

    }else
    {
        cout << "NO SE REGISTRAN VENTAS" << endl;
        return;
    }
}


void VentaManager::SubMenuPorcentaDeInversion()
{
    int option;

    system("cls");
    cout<<endl<<"Desea calcular su porcentaje por: "<<endl;
    cout<<" 1 = SOLO UN MES "<<endl;
    cout<< "                   "<<endl;
    cout<<" 2 = TODO EL ANIO "<<endl;
    cout<< "                   "<<endl;
    cout<<" 0 = VOLVER ATRAS"<<endl<<endl;
    cin>>option;
    system("cls");
    switch(option)
        {
        case 1:
            {
                CalcularPorMes();

                break;
            }
        case 2:
            {
                CalcularPorAnio();

                break;
            }
        case 0:
            {
                return;
            }
                break;
        default:
            system("cls");
            //cout<<"Ingresaste un numero invalido, volve a intenttarlo"<<endl;
            //system("cls");

            cout << "Opcion no valida. Intente de nuevo." << endl;
            if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout <<endl<< "DEBES TOCAR CUALQUIER TECLA PARA VOLVER E INTENTARLO DE NUEVO" << endl;
                    system("pause");
                }
            break;
        }

}
