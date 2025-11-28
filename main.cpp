#include <fstream>
#include <sstream>
#include <iostream>
#include <stdlib.h>
using namespace std;

int findMin(int *distancias, int *procesados) {
    int min = INT_MAX;
    int minIndex = 0;

    for (int i = 0; i < 900; i++) {
        if (procesados[i] != 1 && distancias[i] < min) {
            min = distancias[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void Dijkstra (int origen, int** matrix, int destino)
{
    int *distancias = (int *) malloc(900 * sizeof(int));
    int *procesados = (int *) calloc(900, sizeof(int));
    int *desde = (int *) calloc(900, sizeof(int));
    int i, j, u;
    int nueva_distancia;

    for ( i = 0; i < 900; i++) {
        distancias[i] = INT_MAX;
    }
    distancias[origen] = 0;

    for ( i = 0; i < 900; i++) {
        u = findMin(distancias, procesados);
        procesados[u] = 1;

        for ( j = 0; j < 900; j++) {
            if (matrix[u][j] != 0) {
                nueva_distancia = distancias[u] + matrix[u][j];
                if (nueva_distancia < distancias[j]) {
                    distancias[j] = nueva_distancia;
                    desde[j] = u;
                }
            }
        }
    }

    int current_index = destino;
    while (current_index != origen) {
        int x = current_index / 30;
        int y = current_index % 30;
        cout << "(" << x << "," << y << ")" << endl;
        current_index = desde[current_index];
    }
    int x = origen / 30;
    int y = origen % 30;
    cout << "(" << x << "," << y << ")" << endl;

    free(procesados);
    free(desde);
    free(distancias);
}

void menus_restaurantes() {
    //Se usan para leer el txt
    string sline,line;
    int index;
    string r,p;
    int a,b,precio;

    ifstream inFile("menuFile.txt");

    //Matriz del grafo y arreglos con los restaurantes
    int **menus;
    string *restaurantes;
    string *platillos;

    //Parametros donde se guardaran el tamaño del grafo
    int iline = 0;
    int R = 0, P = 0, size = 0;

    if(inFile.is_open()) {
        while (getline(inFile,sline)) {
            //Sie es la primera linea
            if (iline == 0) {
                line = sline;
                index = line.find(" ");

                R = stoi(line.substr(0,index));
                line = line.substr(index+1);
                index = line.find(" ");
                P = stoi(line.substr(0,index));

                size = R+P;
                menus = new int *[size];
                for(int i = 0; i < size; i++) {
                    menus[i] = new int[size];
                    for(int j = 0; j < size; j++) {
                        menus[i][j] = 0;
                    }
                }

                restaurantes = new string[R];
                for(int i = 0; i < R; i++) {
                    restaurantes[i] = " ";
                }
                platillos = new string[P];
                for(int i = 0; i < P; i++) {
                    platillos[i] = " ";
                }

                iline++;
            }else {
                line = sline;
                index = line.find(":");
                line = line.substr(index+1);
                index = line.find("O:");
                r = line.substr(0,index-1);
                bool found = false;
                for(int i = 0; i < R; i++) {
                    if (r == restaurantes[i]) {
                        found = true;
                        a = i;
                        break;
                    }
                }
                if(!found) {
                    for(int i = 0; i < R; i++) {
                        if(restaurantes[i] == " ") {
                            restaurantes[i] = r;
                            a = i;
                            break;
                        }
                    }
                }else {
                    found = false;
                }

                line = line.substr(index+2);
                index = line.find("(");
                p = line.substr(0,index);
                for(int i = 0; i < P; i++) {
                    if(p == platillos[i]) {
                        found = true;
                        b = i;
                        break;
                    }
                }
                if(!found) {
                    for(int i = 0; i < P; i++) {
                        if(platillos[i] == " ") {
                            platillos[i] = p;
                            b = i;
                            break;
                        }
                    }
                }

                line = line.substr(index+1);
                index = line.find(")");
                precio = stoi(line.substr(0,index));

                menus[a][b+R] = precio;
                menus[b+R][a] = precio;

                iline++;
            }
        }
    }
    inFile.close();

    cout << "Ingrese el nombre de un restaurante: ";
    string restaurante;
    getline(cin, restaurante);
    cout << endl;

    int indexr = -1;
    for(int i = 0; i < R; i++) {
        if (restaurantes[i] == restaurante) {
            indexr = i;
            break;
        }
    }
    if (indexr != -1) {
        cout << "Menu de " << restaurantes[indexr] << endl;
        for(int i = 0; i < P; i++) {
            if (menus[indexr][i+R] != 0) {
                cout << platillos[i] << " precio: " << menus[indexr][i+R] << endl;
            }
        }
    }else {
        cout << "Restuarante no existe\n";
    }
    cout << endl;

    string platillo;
    cout << "Ingrese el nombre de un platillo: ";
    getline(cin, platillo);
    cout << endl;

    int indexp = -1;
    for(int i = 0; i < P; i++) {
        if (platillos[i] == platillo) {
            indexp = i;
            break;
        }
    }
    if (indexp != -1) {
        cout << "Restaurantes que ofrecen " << platillos[indexp] << endl;
        for(int i = 0; i < R; i++) {
            if (menus[i][indexp+R] != 0) {
                cout << restaurantes[i] << " precio: " << menus[i][indexp+R] << endl;
            }
        }
    }else {
        cout << "Platillo no existe\n";
    }

    delete[] restaurantes;
    delete[] platillos;
    for(int i = 0; i < size; i++) {
        delete[] menus[i];
    }
    delete[] menus;
}

void grid_rutas(){
    //Se usan para leer el txt
    string sline,line, aux;
    int index;
    int a,b;
    int x1,y1,x2,y2;
    int distance;

    //Matriz del grafo y arreglo con los dinosaurios
        int* matrix[900];
        for(int i = 0; i < 900; i++) {
            matrix[i] = new int[900];
            for(int j = 0; j < 900; j++) {
                matrix[i][j] = 0;
            }
        }

    ifstream cityFile("city30x30.txt");

    if(cityFile.is_open()){
        while(getline(cityFile, sline)){
            line = sline;
            index = line.find(",");
            x1 = stoi(line.substr(1,index));

            line = line.substr(index+2);
            index = line.find(")");
            y1 = stoi(line.substr(0,index));

            line = line.substr(index+3);
            index = line.find(",");
            x2 = stoi(line.substr(0,index));

            line = line.substr(index+2);
            index = line.find(")");
            y2 = stoi(line.substr(0,index));

            line = line.substr(index+2);
            distance = stoi(line.substr(0));

            a = x1*30 + y1;
            b = x2*30 + y2;

            matrix[a][b] = distance;
            matrix[b][a] = distance;
        }
    }
    cityFile.close();

    string *restaurantes = new string[900];
    for(int i = 0; i < 900; i++) {
        restaurantes[i] = " ";
    }

    ifstream restaurantesFile("restaPlaces.txt");
    if(restaurantesFile.is_open()) {
        while (getline(restaurantesFile,sline)) {
            line = sline;
            index = line.find("(");
            string nombre = line.substr(0,index-1);

            line = line.substr(index+1);
            index = line.find(",");
            int x = stoi(line.substr(0,index));

            line = line.substr(index+2);
            index = line.find(")");
            int y = stoi(line.substr(0,index));

            int indexr = x*30 + y;
            restaurantes[indexr] = nombre;
        }
    }
    restaurantesFile.close();

    ifstream ordersFile("orders30x30.txt");
    if(ordersFile.is_open()) {
        while(getline(ordersFile,sline)) {
            string orden_completa;
            string restaurante;
            line = sline;
            index = line.find(")(");
            orden_completa = line.substr(0,index+1);

            line = line.substr(index+2);
            index = line.find(",");
            a = stoi(line.substr(0,index));

            line = line.substr(index+2);
            index = line.find(")");
            b = stoi(line.substr(0,index));

            index = orden_completa.find("R:");
            restaurante = orden_completa.substr(index+2);
            index = restaurante.find("O:");
            restaurante = restaurante.substr(0,index-1);

            cout << restaurante << endl;

            int p1 = 0;
            for(int i = 0; i < 900; i++) {
                if(restaurante == restaurantes[i]) {
                    p1 = i;
                    break;
                }
            }
            int p2 = a*30 + b;

            cout << orden_completa << "\nCamino mas corto\n";
            Dijkstra(p2,matrix,p1);
            cout << endl;
        }
    }

    for(int i = 0; i < 900; i++) {
        delete[] matrix[i];
    }
    delete[] restaurantes;
}

int main(){

    menus_restaurantes();

    grid_rutas();

    return 0;
}
