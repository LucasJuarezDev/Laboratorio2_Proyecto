#include "VentaManager.h"

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


        if (codigoVenta != codigoActual && SeparadorDeRemitos == false) //ACA SOLO SE MOSTRARA EL CODIGO DE VENTA 1
        { //si es un nuevo grupo de venta
            cout << "==========================================" << endl;
            cout << "VENTA NRO " << codigoVenta << endl;
            cout << "FECHA DE COMPROBANTE: "
                 << ven.getVentaFecha().getDia() << "/"
                 << ven.getVentaFecha().getMes() << "/"
                 << ven.getVentaFecha().getAnio() << endl;
            cout << "------------------------------------------" << endl;
            codigoActual = codigoVenta;
            SeparadorDeRemitos = true; //BANDERA SEPARADORA ACTIVADA
            cout << endl;
        }//si es de la misma venta imprime

        for(int i = 0 ; i < Reg_Prendas ; i ++) //RECORRO TODAS LAS PRENDAS, Y MUESTRO SOLO LAS QUE SE VENDIERON
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
        SeparadorDeRemitos = false; //RESETEO BANDERA

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
    int dia, mes, anio;
    bool Encontro;  //detecta si se encontro o no una venta en esa fecha
    char Salir = 'n';       //usamos char para evitar que se rompa al tocar cualquier tecla
    int cantidad = _ArchVenta.ContarRegistrosVenta();
    Venta obj;

    do
    {
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

        for(int x = 0 ; x < cantidad ; x ++)
        {
            Encontro = false;
            obj = _ArchVenta.LeerVenta(x);
            if(obj.getVentaFecha().getDia() == dia && obj.getVentaFecha().getMes() == mes && obj.getVentaFecha().getAnio() == anio)
            {
                Encontro = true;
                ListarVenta();
                system("pause");
                break;  //para evitar que entre en un bucle infinito
            }
        }
        if(!Encontro)
        {
            cout << "NO SE ENCONTRARON VENTAS EN LA FECHA ' " << dia << "/" << mes << "/" << anio << " '" << endl;
            system("pause");
        }

        system("cls");
        cout << "DESEA SEGUIR BUSCANDO? '1' - NO / CUALQUIER OTRA TECLA - SI" << endl;
        cin >> Salir;

    }while(Salir != '1');

}

//////////////////////////////   DESARROLLO DE SUBMENUS   ///////////////////////////////////////////

void VentaManager::SubMenuCargarVenta()
{
    Venta _ven;
    int cod_venta, CodigoSeleccionado;
    char Salir = 'n';
    Fecha obj;
    int CantPrendas = _ArchiPrenda.ContarRegistrosPrenda();

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
            cout << endl;
            cout << "SELECCIONE EL CODIGO DE PRENDA A VENDER: ";
            cout<<"(TOTAL ACUMULADO AL MOMENTO EN ESTA VENTA : $"<< totalVendido <<")" << endl;
            cin >> CodigoSeleccionado;
            cout << endl;

            // Entramos al archivo de prenda y recorremos todas las prendas
            // Filtramos por el código elegido
            // seteamos el objeto que creamos
            // lo subimos al archivo de venta

            bool prendaEncontrada = false;  // bandera para controlar el guardado de la venta
            //lo de prendaEncontrada es por q al modificar me duolicaba la prenda

            int cInicial=0; //cantidad de ventas segun prenda

            for (int x = 0; x < CantPrendas; x++)
            {
                _Prenda= _ArchiPrenda.LeerPrenda(x);

                if (_Prenda.getCodigo() == CodigoSeleccionado && _Prenda.getEstadoDePrenda())
                {
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

            if (prendaEncontrada) // Solo si encontramos la prenda actualizamos el stock
            {

                for (int x = 0; x < CantPrendas; x++)
                {
                    _Prenda= _ArchiPrenda.LeerPrenda(x);

                    if (_Prenda.getCodigo() == _ven.getCodigo()) // Corregimos aquí el código
                    {
                        int pos = _ArchiPrenda.BuscarCodigoPrenda(x + 1);

                        _Prenda.setCantidad(_Prenda.getCantidad() - cInicial);

                        if (_Prenda.getCantidad() <= 0)
                        {  // Si el stock queda en 0 le hacemos una baja lógica
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

    int opcion;
    cout << "1 - Filtrar por mes y anio" << endl;
    cout << "2 - Filtrar por anio" << endl;
    cin >> opcion;

    switch (opcion) {
        case 1: {
            int mes, anio;
            bool ventasEncontradas = false;

            do { // el do while es para validar que se encuentren fechas validas
                cout << "Ingrese el mes (1-12): ";
                cin >> mes;
                cout << "Ingrese el anio: ";
                cin >> anio;

                // Crear vector dinámico
                Venta *vec = new Venta[CantVentas]; // pedimos memoria por la cantidad de ventas
                Venta _venta, aux;

                int contador = 0;

                // Leer las ventas
                for (int x = 0; x < CantVentas; x++) {
                    _venta = _ArchVenta.LeerVenta(x);

                    // Filtrar por mes y año
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

                    // Mostrar las estadísticas de ventas
                    for (int x = 0; x < contador; x++) {
                        if (vec[x].getCantidad() > 0) {
                            cout << vec[x].getNombrePrenda()<<" "<<vec[x].getModelo() << ": " << vec[x].getCantidad() << endl;
                        }
                    }

                    // Liberar la memoria del vector dinámico
                    delete[] vec;
                }
            } while (!ventasEncontradas);

            break;
        }
        case 2: {
            int anio;
            bool ventasEncontradas = false;

            do { // el do while es para validar que el año sea valido
                cout << "Ingrese el anio: ";
                cin >> anio;

                // Crear vector dinámico
                Venta *vec = new Venta[CantVentas]; // pedimos memoria por la cantidad de ventas
                Venta _venta, aux;

                int contador = 0;

                // Leer las ventas
                for (int x = 0; x < CantVentas; x++) {
                    _venta = _ArchVenta.LeerVenta(x);

                    // Filtrar por año
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

                    // Mostrar las estadísticas de ventas
                    for (int x = 0; x < contador; x++) {
                        if (vec[x].getCantidad() > 0) {
                            cout << vec[x].getNombrePrenda() <<" "<<vec[x].getModelo() << ": " << vec[x].getCantidad() << endl;
                        }
                    }

                    // Liberar la memoria del vector dinámico
                    delete[] vec;
                }
            } while (!ventasEncontradas);

            break;
        }
        default:
            cout << "Opcion no valida. Intente de nuevo." << endl;
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
