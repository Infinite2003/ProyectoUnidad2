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
        void CargarPorLista(const string& filename);
        void printGuardian(Guardian* guard, int indent) const;
        void printGuardians() const;
        

};

Guardian* ArbolGuardianes::findGuardian(const string& nombre) {
        for (Guardian* guardian : guardians) {
            
            if (guardian->Nombre == nombre) {
                return guardian;
            }
        }

        return nullptr;
}

void ArbolGuardianes::insertarGuardian(const string& nombre, const string& npoder,const string& maestro, const string& villa){

    Guardian* guardian = new Guardian;
    guardian->Nombre = nombre;
    guardian->Npoder = stoi(npoder);
    guardian->Maestro = maestro;
    guardian->Villa = villa;
    guardians.push_back(guardian);

    if (root == nullptr) {
            
            root = guardian;
            cout<<"root"<<endl;
    }
    else {
            
        Guardian* master = findGuardian(maestro);
            
        if(master != nullptr) {
            
            master->hijos.push_back(guardian);
        }
    }
}

void ArbolGuardianes::CargarPorLista(const string& filename){

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
        getline(iss, powerLevel , ',');
        getline(iss, mainMaster, ',');
        getline(iss, village);
        insertarGuardian(name, powerLevel, mainMaster, village);
            
    }
    
    file.close();
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
        
        string nombre;
        vector<string> vecinos;
        ArbolGuardianes ArbolLocal;
        
        Aldeas();
        void Imprimir() const;
        void GuardianesAldea(const string& a, const unordered_map<string, Aldeas> c);
        bool busqueda(int u, int v, vector<bool>& recorrido, vector<int>& Marca);
        void AgregarGuardian(Guardian* guardian, const string& villa);
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



void cargarAldeasPorLista(const string& filename, unordered_map<string, Aldeas>& c){

    
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
        aldea.vecinos.push_back(villaVecinas);
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

void imprimirAldeasDisponibles(vector<string> v){

    for(const string& data : v){

        cout<<data<<endl;
    }
}

void crearGuardian(Guardian* guard, vector<string> v, unordered_map<string,Aldeas> c){

    string name;
    string village;

    cout<<"Ingrese el nombre de su personaje"<<endl;
    cin>>name;

    cout<<"Ingrese la aldea de origen del guardian"<<endl;
    cout<<"Recuerde ingresar el nombre exactamente como esta"<<endl;

    imprimirAldeasDisponibles(v);

    cin>>village;

    
}

int main(){
    
    int opcrear;

    Guardian* jugador;

    ArbolGuardianes tree;
    Aldeas Reino;

    string prueba = "Desert Village";
    
    unordered_map<string,int> Referencia;
    unordered_map<string, Aldeas> conexion;
    vector<string> villas; 

    cargarAldeasPorLista("Aldeas.csv",conexion);
    cargarGuardianesPorLista("Guardianes.csv", conexion, tree);

    tree.printGuardians();
    
    ImprimirAldeas(conexion);
    Reino.GuardianesAldea(prueba, conexion);

    cout<<"Bienvenido a The Guardians Jorney"<<endl;
    cout<<"Primero, desea crear a su personaje, o prefiere elegir uno disponible"<<endl;
    
    cin>>opcrear;

    if(opcrear == 1){

        crearGuardian(jugador,villas, conexion);
        tree.insertarGuardian(jugador->Nombre,to_string(jugador->Npoder),jugador->Maestro,jugador->Villa);
    }
    return 0;
}