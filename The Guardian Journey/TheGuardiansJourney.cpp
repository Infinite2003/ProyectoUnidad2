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
    
    private:

        vector<Guardian*> guardians;
        Guardian* root;
        
    
    public:

        ArbolGuardianes() : root(nullptr) {}

        Guardian* findGuardian(const string& nombre);
        void insertarGuardian(const string& nombre, const string& npoder,const string& maestro, const string& villa);
        void CargarPorLista(const string& filename);
        void printGuardian(Guardian* guard, int indent);
        void printGuardians();
        

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

void ArbolGuardianes::printGuardian(Guardian* guard, int indent){

     if (guard != nullptr) {
        
        cout << string(indent, ' ') << "- " << guard->Nombre << " (Power Level: " << guard->Npoder << ", Village: " << guard->Villa << ")" <<endl;
        
        for (Guardian* aprendiz : guard->hijos) {
                
            printGuardian(aprendiz, indent + 4);
        }
    }
}

void ArbolGuardianes::printGuardians(){

    printGuardian(root, 0);
}

class Aldeas{

    private:

        int Vectores;
        vector<vector<int>> Adyasencia;

    public:

        Aldeas();
        Aldeas(int vectores);
        void addEdge(int u, int v);
        void printgraf();
        void adyacencia(int u, unordered_map<int, string> aldea);
        bool busqueda(int u, int v, vector<bool>& recorrido, vector<int>& Marca);

};

Aldeas::Aldeas(int vectores){

    Vectores = vectores;
    Adyasencia.resize(vectores, vector<int>(vectores,0));
}

void Aldeas::addEdge(int u, int v){

    Adyasencia[u][v] = 1;
    Adyasencia[v][u] = 1;
}

void Aldeas::printgraf(){

    for(int p = 0; p < Vectores; p++){

        for(int q = 0; q < Vectores; q++){

            cout<<Adyasencia[p][q]<<"";
        }

        cout<<'\n';
    }
}

void Aldeas::adyacencia(int u, unordered_map<int, string> aldea){

    cout<<"Aldeas donde puede viajar"<<endl;
    auto it = aldea.find(u);

    if(it != aldea.end()){

        cout<<"Esta en:"<<it->first;
        cout<<"Puede viajar a:"<<endl;

        for(int v = 0; v < Vectores; v++){

            if(Adyasencia[u][v] == 1){

                auto ip = aldea.find(v);
                if(ip != aldea.end()){

                    cout<<ip->first<<endl;
                }
                
            }
        }
    }
}

int main(){

    ArbolGuardianes tree;

    tree.CargarPorLista("Guardianes.txt");
    tree.printGuardians();


    return 0;
}