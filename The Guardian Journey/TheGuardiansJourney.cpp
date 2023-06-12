#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <limits>
#include <unordered_map>
#include <string>
#include <cstring>
#include <algorithm> 
#include <time.h>
#include <climits>

using namespace std;

class Guardian{

    public:

        string Nombre;
        int Npoder;
        string Maestro;
        string Villa;
        vector<Guardian*> hijos;
};

class ArbolGuardianes{
    

    public:

        vector<Guardian*> guardians;
        Guardian* root;

        ArbolGuardianes() : root(nullptr) {}

        Guardian* findGuardian(const string& nombre);
        void insertarGuardian(const string& nombre, const string& npoder,const string& maestro, const string& villa);
        void printGuardian(Guardian* guard, int indent) const;
        void printGuardians() const;
        void updateTreeStructure();

};

void ArbolGuardianes::updateTreeStructure() {

    for (Guardian* guardian : guardians) {
        
        if (guardian->Maestro != "") {
            
            Guardian* master = findGuardian(guardian->Maestro);
            
            if (master != nullptr) {
                    
                master->hijos.push_back(guardian);
            }
        }
            
        else {
            root = guardian;
        }
    }
}

Guardian* ArbolGuardianes::findGuardian(const string& nombre) {
        
    for (Guardian* guardian : guardians) {
            
        if (guardian->Nombre == nombre) {
            return guardian;
        }
    }

    return nullptr;
}

void ArbolGuardianes::insertarGuardian(const string& nombre, const string& npoder,const string& maestro, const string& villa){

    cout<<"Hola"<<endl;
    Guardian* guardian = new Guardian;
    guardian->Nombre = nombre;
    guardian->Npoder = stoi(npoder);
    guardian->Maestro = maestro;
    guardian->Villa = villa;
    guardians.push_back(guardian);

    if (root == nullptr) {
            
            root = guardian;
    }
    else {
            
        Guardian* master = findGuardian(maestro);
            
        if(master != nullptr) {
            
            master->hijos.push_back(guardian);
        }
    }
}

void ArbolGuardianes::printGuardian(Guardian* guard, int indent) const{

     if (guard != nullptr) {
        
        cout << string(indent, ' ') << "- " << guard->Nombre << " (Power Level: " << guard->Npoder << ", Village: " << guard->Villa << ")" <<endl;
        
        for (Guardian* aprendiz : guard->hijos) {
                
            printGuardian(aprendiz, indent + 4);
        }
    }
}

void ArbolGuardianes::printGuardians() const{

    printGuardian(root, 0);
}

class Aldeas{

    public:
        
        int puntos;
        string nombre;
        vector<string> vecinos;
        ArbolGuardianes ArbolLocal;
        
        Aldeas();
        void Imprimir() const;
        void GuardianesAldea(const string& a, const unordered_map<string, Aldeas> c);
        void AgregarGuardian(Guardian* guardian, const string& villa);
        void mostrarDebil();
};

Aldeas::Aldeas(){

    
}

void Aldeas::AgregarGuardian(Guardian* guardian, const string& villa) {

        if(nombre == villa){

            ArbolLocal.insertarGuardian(guardian->Nombre,to_string(guardian->Npoder), guardian->Maestro, guardian->Villa);
        }
}

void Aldeas::Imprimir() const{

    cout<<"Aldeas Vecinas: ";

    for(const string& vecino : vecinos){

        cout<<vecino<<",";
    }

    cout<<endl;
}

void Aldeas::GuardianesAldea(const string& a, unordered_map<string, Aldeas> c){

    cout<<"Guardianes aldea: "<<a<<endl;

    ArbolGuardianes* arbol = &c.at(a).ArbolLocal;

    arbol->printGuardians();
}

void Aldeas::mostrarDebil(){

    Guardian* debil = nullptr;
    int minPoder = INT_MAX;

    for (Guardian* guardian : ArbolLocal.guardians) {
        
        if (guardian->Npoder < minPoder) {
            
            minPoder = guardian->Npoder;
            debil = guardian;
        }
    }


    if (debil != nullptr) {
        
        cout << "Guardian mas debil: " << debil->Nombre << " (Nivel de poder: " << debil->Npoder << ")" << endl;
    }
    
    else {
        
        cout << "No hay guardianes en esta aldea." << endl;
    }
}

bool duplicado(vector<string>& v, string& a){

    return find(v.begin(), v.end(), a) != v.end();
}

void cargarAldeasPorLista(const string& filename, unordered_map<string, Aldeas>& c, vector<string>& v){

    
    ifstream file(filename);   
    
    if (!file) {
            
        cerr << "Failed to open file: " << filename << endl;
        
        return;
    }
    
    string line;
    getline(file, line);
        
    while (getline(file, line)) {
        
        istringstream iss(line);
        string villa;
        string villaVecinas;
        getline(iss,villa,',');
        getline(iss,villaVecinas);

        Aldeas& aldea = c[villa];
        aldea.nombre = villa;
        aldea.puntos = 0;
        aldea.vecinos.push_back(villaVecinas);

        if(!duplicado(v,villa)){

            v.push_back(villa);
        }
    }
    
    file.close(); 
}

void cargarGuardianesPorLista(const string& filename, unordered_map<string, Aldeas>& c, ArbolGuardianes& tree){

    ifstream file(filename);   
    
    if (!file) {
            
        cerr << "Failed to open file: " << filename << endl;
        
        return;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        istringstream iss(line);
        string name, mainMaster, village;
        string powerLevel;
        getline(iss, name, ',');
        getline(iss, powerLevel, ',');
        getline(iss, mainMaster, ',');
        getline(iss, village);

        tree.insertarGuardian(name, powerLevel, mainMaster, village);
        Aldeas& aldea = c[village];
        Guardian* guardian = tree.findGuardian(name);
        aldea.AgregarGuardian(guardian, village);
    }

    file.close();    

}



void ImprimirAldeas(const unordered_map<string,Aldeas>& v){

    for(const auto& par : v){

        const string& key = par.first;
        const Aldeas& valor = par.second;

        cout<<"Villa: "<<key<<endl;
        valor.Imprimir();
        cout<<endl;
    }
}

void imprimirAldeasDisponibles(vector<string>& v){

    for(const string& data : v){

        cout<<data<<endl;
    }
}

void crearGuardian(Guardian*& guard, vector<string>& v, unordered_map<string,Aldeas>& c, ArbolGuardianes& tree){

    string name;
    string village;

    cout<<"Ingrese el nombre de su personaje"<<endl;
    cin>>name;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    imprimirAldeasDisponibles(v);
    
    cout<<"Ingrese la aldea de origen del guardian"<<endl;
    
    cout<<"Recuerde ingresar el nombre exactamente como esta"<<endl;


    getline(cin,village);
    
    guard->Nombre = name;
    guard->Villa = village;
    guard->Npoder = 50;
    guard->Maestro = "Independiente";
    
    cout<<"Agregando a las demas estructuras"<<endl;
    tree.insertarGuardian(name, to_string(50), "Independiente", village);
    tree.findGuardian(name);
    Aldeas& aldea = c[village];
    Guardian* guardian = tree.findGuardian(name);
    aldea.AgregarGuardian(guardian, village);
    
}

void mostrarAdyacencia(unordered_map<string,Aldeas> v, string p){

    for(const auto& data : v){

        const string& key = data.first;
        const Aldeas& value = data.second;

        if(key == p){

            value.Imprimir();
        }
    }
}

/*void elegirGuardian(ArbolGuardianes* tree, Guardian* j){


}*/

void recomendar(unordered_map<string,Aldeas>& c, string& dato){

    for(const auto& data : c){

        const string& key = data.first;;

        if(key == dato){

            c[key].mostrarDebil();
        }
    }
}

void combate(Guardian* j, unordered_map<string,Aldeas>& c, string& dato){

    string eleccion;

    cout<<"Se le recomienda el siguiente oponente"<<endl;

    recomendar(c,dato);

    cout<<"Ingrese el nombre de quien desea enfrentar"<<endl;
    cout<<"Recuerde que debe ingresar el nombre Exacto o no funcionara";
    c[dato].GuardianesAldea(dato, c);

    cin>>eleccion;

    if(c[dato].ArbolLocal.findGuardian(eleccion) != nullptr){

        cout<<"Empieza el combate"<<endl;

        int ganar = rand()%100 + 1;

        if(ganar > j->Npoder){

            cout<<"Has perdido el combate";
        }

        else{

            cout<<"Haz ganado";

            if(c[dato].puntos < 4 && j->Npoder > 100){

                
                j->Npoder = j->Npoder + 1;
                c[dato].puntos = c[dato].puntos + 1;
            }

            else if(j->Npoder >= 100){

                cout<<"No puede tener mas de 100 puntos de poder"<<endl;
                j->Npoder = 100;
            }

            else{

                cout<<"Ya alcanzo el limite de puntos de esta aldea";
            }
        }
    }

    else{

        cout<<"Ingreso el dato de manera incorrecta, recuerde que le advertimos anteriormente que ingrese el nombre exacto"<<endl;
        cout<<"Intentelo de nuevo";
    }

}

void viajar(unordered_map<string, Aldeas> c, string p){

    string destino;
    int opcion;
    int ciclo = 0;

    cout<<"Hacia donde desea viajar"<<endl;
    cout<<"Estas son las aldeas disponibles: "<<endl;

    mostrarAdyacencia(c,p);

    getline(cin,destino);
    
    for(const auto& data : c){

        const string& key = data.first;
        const Aldeas& value = data.second;
        
        if(destino == key){

            cout<<"Ya se encuentra en esta Aldea";
        }

        else if(destino == value.nombre){

            cout<<"Ha viajado a "<< destino<<endl;
            p = destino;
        }

        else{

            cout<<"No existe conexion entre la Aldea actual y la que esta ingresando"<<endl;
            cout<<"¿Desea realizar alquimia?";

            while(ciclo == 0){

                cout<<"1: Si"<<endl;
                cout<<"2: No"<<endl;

                cin>>opcion;

                if(opcion == 1){

                    
                    ciclo = 1;
                }

                else if(opcion == 2){

                    cout<<"Decidio no hacer alquimia"<<endl;
                    ciclo = 1;
                }

                else{

                    cout<<"Ingrese una opcion valida"<<endl;
                }
            }

            
        }
    }

}   

int main(){
    
    srand(time(0));

    int opcrear, ciclo = 0;
    int terminar = 0;
    int opcion = 0;
    int v; 
    string current;
    
    Guardian* jugador = new Guardian;
    ArbolGuardianes tree;
    Aldeas Reino;
    
    unordered_map<string, Aldeas> conexion;
    vector<string> villas; 

    cargarAldeasPorLista("Aldeas.csv",conexion, villas);
    cargarGuardianesPorLista("Guardianes.csv", conexion, tree);

    cout<<"Bienvenido a The Guardians Jorney"<<endl;
    cout<<"Primero, desea crear a su personaje, o prefiere elegir uno disponible"<<endl;

    while(ciclo == 0){

        cout<<"1: Crear mi personaje"<<endl;
        cout<<"2: Elegir un personaje"<<endl;
        cin>>opcrear;
        
        if(opcrear == 1){

            crearGuardian(jugador,villas, conexion, tree);
            current = jugador->Villa;
            ciclo = 1;
        }

        else if(opcrear == 2){

            
        }

        else{

            cout<<"Ingrese una opcion valida"<<endl;
        }
    }

    while(terminar == 0){

        cout<<"Se encuentra en: "<<current<<endl;

        cout<<"Que desea realizar"<<endl;

        cout<<"1: Entrenar"<<endl;
        cout<<"2: Viajar"<<endl;

        cin>>opcion;

        if(opcion == 1){

            combate(jugador,conexion,current);
        }

        else if(opcion == 2){

            viajar(conexion,current);
        }
        else{

            cout<<"Ingrese una opcion valida"<<endl;
        }
    }

    return 0;
}