#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

void menus_restaurantes() {
    //Se usan para leer el txt
    string sline,line, aux;
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

int main(){

    menus_restaurantes();

    return 0;
}
