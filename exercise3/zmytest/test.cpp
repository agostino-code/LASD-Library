#include <iostream>
#include <random>
#include "test.hpp"
#include "../zlasdtest/test.hpp"

using namespace std;
using namespace lasd;
string tipo;

void CreateBinaryTree(){
    int choise=0;
        cout << "0:( test)"<<endl;
        cout << "Che struttura dati vuoi usare: "<<endl
                <<"1:( binarytree puntatori )"<<endl
                <<"2:( binarytree vector )"<<endl
                <<"Scelta: "; cin >> choise;
        switch (choise) {
            case 0:
                lasdtest();
                CreateBinaryTree();
                break;
            case 1:
                CreateBinaryTreeLnk();
                break;
            case 2:
                CreateBinaryTreeVec();
                break;
        }
}

void CreateBinaryTreeLnk() {
    while (tipo != "int" && tipo != "string" && tipo != "double") {
        cout << "Che tipo di dati deve contenere?: ( int / string / double ) : ";
        cin >> tipo;
    }
        RandomBinaryTreeLnk();
        MenuBinaryTree();
}

void CreateBinaryTreeVec() {
    while (tipo != "int" && tipo != "string" && tipo != "double") {
        cout << "Che tipo di dati deve contenere?: ( int / string / double ) : ";
        cin >> tipo;
    }
    RandomBinaryTreeVec();
    MenuBinaryTree();
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

void RandomBinaryTreeLnk(){
    unsigned long n;
    cout << "Dai una dimenzione a questo BinaryTreeLnk: ";
    cin >> n;
    if (tipo == "int") {
        List<int> lc;
        for (unsigned long i = 0; i < n; i++) {
            lc.InsertAtBack(RandomInt());
        }
        binaryTree<int> = new BinaryTreeLnk<int>(lc);
    } else if (tipo == "string") {
        List<string> lc;
        for (unsigned long i = 0; i < n; i++) {
            lc.InsertAtBack(RandomString());
        }
        binaryTree<string> = new BinaryTreeLnk<string>(lc);
    } else if (tipo == "double") {
        List<double> lc;
        for (unsigned long i = 0; i < n; i++) {
            lc.InsertAtBack(RandomDouble());
        }
        binaryTree<double> = new BinaryTreeLnk<double>(lc);
    }
}

void RandomBinaryTreeVec(){
    unsigned long n;
    cout << "Dai una dimenzione a questo BinaryTreeVec: ";
    cin >> n;
    if (tipo == "int") {
        List<int> lc;
        for (unsigned long i = 0; i < n; i++) {
            lc.InsertAtBack(RandomInt());
        }
        binaryTree<int> = new BinaryTreeVec<int>(lc);
    } else if (tipo == "string") {
        List<string> lc;
        for (unsigned long i = 0; i < n; i++) {
            lc.InsertAtBack(RandomString());
        }
        binaryTree<string> = new BinaryTreeVec<string>(lc);
    } else if (tipo == "double") {
        List<double> lc;
        for (unsigned long i = 0; i < n; i++) {
            lc.InsertAtBack(RandomDouble());
        }
        binaryTree<double> = new BinaryTreeVec<double>(lc);
    }
}

void MenuBinaryTree() {
    char again='y';
    do {
        cout<< u8"\033[2J\033[1;1H";
        int choise;
        cout << "Che operazione vuoi effettuare: " << endl
             << "1:( Stampa dell'albero )" << endl
             << "2:( Controllo di Esistenza )" << endl
             << "3:( Funzioni Fold )" << endl
             << "4:( Funzioni Map )" << endl
             << "Scelta: ";
        cin >> choise;
        switch (choise) {
            case 1:
                BinaryTreeStamp();
                break;
            case 2:
                BinaryTreeExist();
                break;
            case 3:
                BinaryTreeFold();
                break;
            case 4:
                BinaryTreeMap();
                break;
        }
        cout <<endl<<"Vuoi effettuare un altra operazione (y/f): ";
        cin >> again;
    } while (again=='y' || again=='Y');
}

    void BinaryTreeStamp(){
        char again='y';
        do {
            cout<< u8"\033[2J\033[1;1H";
            int choise;
            cout << "Che stampa vuoi effettuare: " << endl
                 << "1:( PreOrder )" << endl
                 << "2:( PostOrder )" << endl
                 << "3:( InOrder )" << endl
                 << "4:( Breadth )" << endl
                 << "Scelta: ";
            cin >> choise;
            switch (choise) {
                case 1:
                    StampPreOrder();
                    break;
                case 2:
                    StampPostOrder();
                    break;
                case 3:
                    StampInOrder();
                    break;
                case 4:
                    StampBreadth();
                    break;
            }
            cout <<endl<< "Vuoi effettuare un altra stampa (y/f): ";
            cin >> again;
        } while (again=='y' || again=='Y');
    }

    void StampPreOrder(){
        if (tipo == "int") {
                binaryTree<int>->MapPreOrder(&MapPrint<int>, nullptr);
        } else if (tipo == "string") {
            binaryTree<string>->MapPreOrder(&MapPrint<string>, nullptr);
        }
        else if (tipo == "double") {
            binaryTree<double>->MapPreOrder(&MapPrint<double>, nullptr);
        }
    }

    void StampPostOrder(){
        if (tipo == "int") {
            binaryTree<int>->MapPostOrder(&MapPrint<int>, nullptr);
        } else if (tipo == "string") {
            binaryTree<string>->MapPostOrder(&MapPrint<string>, nullptr);
        }
        else if (tipo == "double") {
            binaryTree<double>->MapPostOrder(&MapPrint<double>, nullptr);
        }
    }


    void StampInOrder(){
        if (tipo == "int") {
            binaryTree<int>->MapInOrder(&MapPrint<int>, nullptr);
        } else if (tipo == "string") {
            binaryTree<string>->MapInOrder(&MapPrint<string>, nullptr);
        }
        else if (tipo == "double") {
            binaryTree<double>->MapInOrder(&MapPrint<double>, nullptr);
        }
    }

    void StampBreadth(){
        if (tipo == "int") {
            binaryTree<int>->MapBreadth(&MapPrint<int>, nullptr);
        } else if (tipo == "string") {
            binaryTree<string>->MapBreadth(&MapPrint<string>, nullptr);
        }
        else if (tipo == "double") {
            binaryTree<double>->MapBreadth(&MapPrint<double>, nullptr);
        }
    }

    void BinaryTreeExist(){
    bool esiste= false;
        cout<<"Verifico l'esistenza di un valore: ";
        if (tipo == "int") {
            int choise;
            cin>>choise;
            esiste=binaryTree<int>->Exists(choise);
        }
        else if (tipo == "string") {
            string choise;
            cin>>choise;
            esiste=binaryTree<string>->Exists(choise);
        }
        else if (tipo == "double") {
            double choise;
            cin>>choise;
            esiste=binaryTree<double>->Exists(choise);
        }
        if(esiste){
            cout<<"Il valore inserito esiste.";
        }
        else{
            cout<<"Il valore inserito non esiste.";
        }
    }

    void BinaryTreeMap(){
        if (tipo == "int") {
            cout<<"3n per gli interi."<<endl;
            binaryTree<int>->Map(&MapInt<int>, nullptr);
        } else if (tipo == "string") {
            string front;
            cout<<"Concatenazione in testa di una specifica stringa."<<endl;
            cout<<"Inserisci la stringa che vuoi concatenare: ";
            cin>>front;
            binaryTree<string>->Map(&MapString<string>, &front);
        }
        else if (tipo == "double") {
            cout<<"n^3 per i float."<<endl;
            binaryTree<double>->Map(&MapDouble<double>, nullptr);
        }
    }

    void BinaryTreeFold(){
        if (tipo == "int") {
            int n;
            int out=1;
            cout<<"Prodotto per gli interi minori di n."<<endl;
            cout<<"Inserisci il valore di n: ";
            cin>>n;
            binaryTree<int>->Fold(&FoldInt<int>,&n,&out);
            cout<<endl<<"Il valore risultante è: "<<out;
        } else if (tipo == "string") {
            int n;
            string out;
            cout<<"Concatenazione per le stringhe con lunghezza minore o uguale a n,"<<endl;
            cout<<"Inserisci il valore di n: ";
            cin>>n;
            binaryTree<string>->Fold(&FoldString<string>,&n,&out);
            cout<<endl<<"Il valore risultante è: "<<out;
        }
        else if (tipo == "double") {
            double n,out;
            cout<<"Somma per i float maggiori di n."<<endl;
            cout<<"Inserisci il valore di n: ";
            cin>>n;
            binaryTree<double>->Fold(&FoldDouble<double>,&n,&out);
            cout<<endl<<"Il valore risultante è: "<<out;
        }
    }


