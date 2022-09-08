#include<iostream> //
#include<fstream>

using namespace std;

void cargarVec(ifstream& archilec, int x, string vec[]){

    for (int i = 0; i < x && archilec >> vec[i]; ++i);

}

void mostrar(const string vec[], int dim){

	for (int i = 0; i < dim; ++i)
		cout << "vec[" << i << "]= " << vec[i] << endl;

}

void mostrarmat(const float m[][5], int dfil){

    const int dcol {5}; // solo por prolijidad

	for (int i = 0; i < dfil; ++i) {
		for (int j = 0; j < dcol; ++j)
			cout << m[i][j] << '\t';
		cout << endl;
	}
}

void buscarMax(int n, int esp, int& max, int& x){
    if(n > max){
        max = n;
        x = esp;    
    }
}

int mayor(const float clieprod[][5], int dfil, const string vecCli[], const string vecProd[]){
    
    // Punto 1

	const int dcol {5}; // solo por prolijidad
    int cont {0};
    int max {0};
    int icliente;

    cout << endl;
    cout << "Listado por clientes, de los tipos de productos que superen los 13000 Kg acumulados:" << endl;
	for (int i = 0; i < dfil; ++i){
        cout << vecCli[i] << ": ";
        cont = 0;
        for (int j = 0; j < dcol; ++j){
            if(clieprod[i][j] > 13000) {
				cout << vecProd[j] << ", ";
                cont++;
			}
        }
        
        buscarMax(cont, i, max, icliente);
        
        /*if(i == 0 || cont > max){
            max = cont;
            icliente = i; // guardo el numero del cliente con mayor productos q pesen + q 13000kg
        }*/

        cout << endl;

        if(cont == 0){
            cout << " No transporto ningun producto que supere los 13000 kg " << endl;
        }
    }
    
    return icliente; // devuelvo el id del cliente con mayor cantidad de productos q pesen + q 13000kg
}

void ordenaryMostrar(int dim, float vec[], int vec2[], const string vecProd[]){
            int imax;
            for(int pos = 0; pos < dim-1; pos++){
                imax = pos;
            for(int i = pos+1; i < dim; i++){
                if(vec[i] < vec[pos]){
                    imax = i;
                    swap(vec[pos], vec[imax]);
                    swap(vec2[pos], vec2[imax]);
                }
            }
            }

            for(int i = 0; i < dim; ++i){
                cout << vecProd[vec2[i]] << ": " << vec[i] << endl;
            }
}

int listar(const int x, const float clieprod[][5], const string vecProd[], const float clieproddis[][5], const string vecCli[]){

    // Punto 2

    const int dcol {5}; // solo por prolijidad
    int iproduc;
    int max {0};
    float distancia[dcol];
    int producto[dcol];

    cout << endl;
        cout << "Cliente con mayor cantidad de tipos de productos que hayan superado 13000 kg" << endl;
        cout << vecCli[x] << endl;
        cout << "Listado de Km recorridos por tipo de producto" << endl;
        for (int j = 0; j < dcol; ++j){

            distancia[j] = clieproddis[x][j]; // guardo las distancias
            producto[j] = j; // guardo el nombre de los productos
            
            buscarMax(clieproddis[x][j], j, max, iproduc);

            /*if(clieproddis[i][j] > max){
                max = clieproddis[i][j];
                iproduc = j; // guardo el id del producto con mayor cantidad de kilómetros recorridos
            }*/
    }
    
    ordenaryMostrar(dcol, distancia, producto, vecProd);

   return iproduc; // devuelvo el id del producto con mayor cantidad de kilómetros recorridos
}

void cantViajes(ifstream& archilec, int idprod, const string vecProd[]){

    // Punto 3

    int cont{0};
    int iclien, iprod;
    float peso, dist;

	while (archilec >> iclien >> iprod >> peso >> dist) {
		if(iprod == idprod){
            cont++;
        }
	}
	archilec.close();

    cout << endl;
    cout << "Cantidad de entregas para el tipo de producto " << vecProd[idprod] << ": " << cont << endl;
    }


int main(){

    const int nclien {8};  
    const int nprod {5};

    string producto[nprod]; //nombre de los productos
	string cliente[nclien]; //nombre de los clientes

    float clieprod[nclien][nprod] {}; //total de kilos transportados x Cliente/Producto
    float clieproddis[nclien][nprod] {}; //distancia recorrida x Cliente/Producto

    bool debug {false}; //Para sacar carteles de seguimiento

    //Leo el archivo de nombres, de clientes y productos
	ifstream archilec;
	archilec.open("Nombres.txt");
	if (!archilec) {
		cout << "Error al tratar de abrir el archivo de nombres" << endl;
		return 1;
	}

    cargarVec(archilec, nclien, cliente); // Cargo clientes
    cargarVec(archilec, nprod, producto); // Cargo productos

    /*for (int i = 0; i < nclien && archilec >> cliente[i]; ++i); // Cargo clientes
    for (int i = 0; i < nprod && archilec >> producto[i]; ++i); // Cargo productos*/

    if (debug) {
        mostrar(cliente, nclien);
		cout << "\n============================\n" << endl;
		mostrar(producto, nprod);		
	}
	archilec.close();

    archilec.open("Datos.txt");
	if (!archilec) {
		cout << "Error al tratar de abrir el archivo de producción" << endl;
		return 1;
	}

	int iclien, iprod;
    float peso, dist;
	while (archilec >> iclien >> iprod >> peso >> dist) {
		clieprod[iclien][iprod] += peso;
        clieproddis[iclien][iprod] += dist;
	}
	archilec.close();

    if (debug) {
		cout << "\n===============Producción=============\n" << endl;
		mostrarmat(clieprod, nclien);
        cout << "\n===============Distancia Produc=============\n" << endl;
		mostrarmat(clieproddis, nclien);
		cout << endl;
	}

    // Puntos 1,2 y 3
    archilec.open("Datos.txt");
	if (!archilec) {
		cout << "Error al tratar de abrir el archivo de producción" << endl;
        return 1;
	}

    cantViajes(archilec, listar(mayor(clieprod, nclien, cliente, producto), clieprod, producto, clieproddis, cliente), producto);

    return 0;
}
