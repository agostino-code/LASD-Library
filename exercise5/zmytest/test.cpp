#include <iostream>
#include <random>
#include "test.hpp"
#include "../zlasdtest/test.hpp"

using namespace std;
using namespace lasd;
string tipo;

void CreateHashTable(){
    int choise=0;
        cout << "0:( test)"<<endl;
        cout << "Che struttura dati vuoi usare: "<<endl
                <<"1:( HashTable OpenAdressing )"<<endl
                <<"2:( HashTable ClosedAdressing )"<<endl
                <<"Scelta: "; cin >> choise;
        switch (choise) {
            case 0:
                lasdtest();
                CreateHashTable();
                break;
            case 1:
                CreateOpn();
                break;
            case 2:
                CreateCls();
                break;
        }
}

void CreateOpn() {
    while (tipo != "int" && tipo != "string" && tipo != "double") {
        cout << "Che tipo di dati deve contenere?: ( int / string / double ) : ";
        cin >> tipo;
    }
        RandomOpn();
        MenuHashTable();
}

void CreateCls() {
    while (tipo != "int" && tipo != "string" && tipo != "double") {
        cout << "Che tipo di dati deve contenere?: ( int / string / double ) : ";
        cin >> tipo;
    }
    RandomCls();
    MenuHashTable();
}

int RandomInt(){
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<std::mt19937::result_type> dist6(1,99);
    return dist6(rng);
}

string RandomString(){
        static const char alphanum[] =
                "abcdefghijklmnopqrstuvwxyz";
        std::string tmp_s;
        tmp_s.reserve(4);

        for (int i = 0; i < 4; ++i) {
            tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
        }

        return tmp_s;
}

double RandomDouble(){
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(1, 10);
    return dist(gen);
}

void RandomOpn(){
    unsigned long n;
    cout << "Dai una dimenzione a questa HashTable OpenAdressing: ";
    cin >> n;
    if (tipo == "int") {
        hashTable<int> =new HashTableOpnAdr<int>;
        for (unsigned long i = 0; i < n; i++) {
            hashTable<int>->Insert(RandomInt());
        }
    } else if (tipo == "string") {
        hashTable<string> =new HashTableOpnAdr<string>;
        for (unsigned long i = 0; i < n; i++) {
            hashTable<string>->Insert(RandomString());
        }
    } else if (tipo == "double") {
        hashTable<double> =new HashTableOpnAdr<double>;
        for (unsigned long i = 0; i < n; i++) {
           hashTable<double>->Insert(RandomDouble());
        }
    }
}

void RandomCls(){
    unsigned long n;
    cout << "Dai una dimenzione a questa HashTable OpenAdressing: ";
    cin >> n;
    if (tipo == "int") {
        hashTable<int> =new HashTableClsAdr<int>;
        for (unsigned long i = 0; i < n; i++) {
            hashTable<int>->Insert(RandomInt());
        }
    } else if (tipo == "string") {
        hashTable<string> =new HashTableClsAdr<string>;
        for (unsigned long i = 0; i < n; i++) {
            hashTable<string>->Insert(RandomString());
        }
    } else if (tipo == "double") {
        hashTable<double> =new HashTableClsAdr<double>;
        for (unsigned long i = 0; i < n; i++) {
            hashTable<double>->Insert(RandomDouble());
        }
    }
}

void MenuHashTable() {
    char again='y';
    do {
        cout<< u8"\033[2J\033[1;1H";
        int choise;
        cout << "Che operazione vuoi effettuare: " << endl
             << "1:( Stampa dell' Hashtable )" << endl
             << "2:( Controllo di Esistenza )" << endl
             << "3:( Funzioni Fold )" << endl
             << "4:( Funzioni di Inserimento )" << endl
             << "5:( Funzioni di Rimozione )" << endl
             << "Scelta: ";
        cin >> choise;
        switch (choise) {
            case 1:
                HashStamp();
                break;
            case 2:
                HashExist();
                break;
            case 3:
                HashFold();
                break;
            case 4:
                HashInsertMenu();
                break;
            case 5:
                HashRemove();
                break;
        }
        cout <<endl<<"Vuoi effettuare un altra operazione (y/f): ";
        cin >> again;
    } while (again=='y' || again=='Y');
}

    void HashStamp() {
        if (tipo == "int") {
            hashTable<int>->Map(&MapPrint<int>, nullptr);
        } else if (tipo == "string") {
            hashTable<string>->Map(&MapPrint<string>, nullptr);
        } else if (tipo == "double") {
            hashTable<double>->Map(&MapPrint<double>, nullptr);
        }
    }


    void HashExist(){
    bool esiste= false;
        cout<<"Verifico l'esistenza di un valore: ";
        if (tipo == "int") {
            int choise;
            cin>>choise;
            esiste=hashTable<int>->Exists(choise);
        }
        else if (tipo == "string") {
            string choise;
            cin>>choise;
            esiste=hashTable<string>->Exists(choise);
        }
        else if (tipo == "double") {
            double choise;
            cin>>choise;
            esiste=hashTable<double>->Exists(choise);
        }
        if(esiste){
            cout<<"Il valore inserito esiste.";
        }
        else{
            cout<<"Il valore inserito non esiste.";
        }
    }

    void HashFold(){
        if (tipo == "int") {
            int n;
            int out=1;
            cout<<"Prodotto per gli interi minori di n."<<endl;
            cout<<"Inserisci il valore di n: ";
            cin>>n;
            hashTable<int>->Fold(&FoldInt<int>,&n,&out);
            cout<<endl<<"Il valore risultante è: "<<out;
        } else if (tipo == "string") {
            int n;
            string out;
            cout<<"Concatenazione per le stringhe con lunghezza minore o uguale a n,"<<endl;
            cout<<"Inserisci il valore di n: ";
            cin>>n;
            hashTable<string>->Fold(&FoldString<string>,&n,&out);
            cout<<endl<<"Il valore risultante è: "<<out;
        }
        else if (tipo == "double") {
            double n,out;
            cout<<"Somma per i float maggiori di n."<<endl;
            cout<<"Inserisci il valore di n: ";
            cin>>n;
            hashTable<double>->Fold(&FoldDouble<double>,&n,&out);
            cout<<endl<<"Il valore risultante è: "<<out;
        }
    }

void HashInsertMenu() {
        cout << u8"\033[2J\033[1;1H";
        int choise;
        cout << "Che Inserimento vuoi effettuare: " << endl
             << "1:( Insert (copy) )" << endl
             << "2:( Insert (move) )" << endl
             << "Scelta: ";
        cin >> choise;
        switch (choise) {
            case 1:
                HashInsertCopy();
                break;
            case 2:
                HashInsertMove();
                break;
        }
}

void HashInsertCopy(){
    if (tipo == "int") {
        int n;
        cout<<"Inserisci il valore da inserire: ";
        cin>>n;
        hashTable<int>->Insert(n);
    } else if (tipo == "string") {
        string n;
        cout<<"Inserisci il valore da inserire: ";
        cin>>n;
        hashTable<string>->Insert(n);
    }
    else if (tipo == "double") {
        double n;
        cout<<"Inserisci il valore da inserire: ";
        cin>>n;
        hashTable<double>->Insert(n);
    }
}

void HashInsertMove(){
    if (tipo == "int") {
        int n;
        cout<<"Inserisci il valore da inserire: ";
        cin>>n;
        hashTable<int>->Insert(std::move(n));
    } else if (tipo == "string") {
        string n;
        cout<<"Inserisci il valore da inserire: ";
        cin>>n;
        hashTable<string>->Insert(std::move(n));
    }
    else if (tipo == "double") {
        double n;
        cout<<"Inserisci il valore da inserire: ";
        cin>>n;
        hashTable<double>->Insert(std::move(n));
    }
}

void HashRemove(){
    if (tipo == "int") {
        int n;
        cout<<"Inserisci il valore da rimuovere: ";
        cin>>n;
        hashTable<int>->Remove(n);
    } else if (tipo == "string") {
        string n;
        cout<<"Inserisci il valore da rimuovere: ";
        cin>>n;
        hashTable<string>->Remove(n);
    }
    else if (tipo == "double") {
        double n;
        cout<<"Inserisci il valore da rimuovere: ";
        cin>>n;
        hashTable<double>->Remove(n);
    }
}
