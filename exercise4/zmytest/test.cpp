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
                <<"1:( BST )"<<endl
                <<"Scelta: "; cin >> choise;
        switch (choise) {
            case 0:
                lasdtest();
                CreateBinaryTree();
                break;
            case 1:
                CreateBST();
                break;
        }
}

void CreateBST() {
    while (tipo != "int" && tipo != "string" && tipo != "double") {
        cout << "Che tipo di dati deve contenere?: ( int / string / double ) : ";
        cin >> tipo;
    }
        RandomBST();
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

void RandomBST(){
    unsigned long n;
    cout << "Dai una dimenzione a questo BST: ";
    cin >> n;
    if (tipo == "int") {
        binaryTree<int> =new BST<int>;
        for (unsigned long i = 0; i < n; i++) {
            binaryTree<int>->Insert(RandomInt());
        }
    } else if (tipo == "string") {
        binaryTree<string> =new BST<string>;
        for (unsigned long i = 0; i < n; i++) {
            binaryTree<string>->Insert(RandomString());
        }
    } else if (tipo == "double") {
        binaryTree<double> =new BST<double>;
        for (unsigned long i = 0; i < n; i++) {
           binaryTree<double>->Insert(RandomDouble());
        }
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
             << "4:( Funzioni di Inserimento )" << endl
             << "5:( Funzioni di Rimozione )" << endl
             << "6:( Funzioni di ( Min-Max-Pre-Suc )" << endl
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
                BinaryTreeInsertMenu();
                break;
            case 5:
                BinaryTreeRemoveMenu();
                break;
            case 6:
                BinaryTreeVisit();
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

void BinaryTreeInsertMenu() {
    char again = 'y';
    do {
        cout << u8"\033[2J\033[1;1H";
        int choise;
        cout << "Che Inserimento vuoi effettuare: " << endl
             << "1:( Insert (copy) )" << endl
             << "2:( Insert (move) )" << endl
             << "Scelta: ";
        cin >> choise;
        switch (choise) {
            case 1:
                BinaryTreeInsertCopy();
                break;
            case 2:
                BinaryTreeInsertMove();
                break;
        }
        cout << endl << "Vuoi effettuare un altro inserimento (y/f): ";
        cin >> again;
    } while (again == 'y' || again == 'Y');
}

void BinaryTreeInsertCopy(){
    if (tipo == "int") {
        int n;
        cout<<"Inserisci il valore da inserire: ";
        cin>>n;
        binaryTree<int>->Insert(n);
    } else if (tipo == "string") {
        string n;
        cout<<"Inserisci il valore da inserire: ";
        cin>>n;
        binaryTree<string>->Insert(n);
    }
    else if (tipo == "double") {
        double n;
        cout<<"Inserisci il valore da inserire: ";
        cin>>n;
        binaryTree<double>->Insert(n);
    }
}

void BinaryTreeInsertMove(){
    if (tipo == "int") {
        int n;
        cout<<"Inserisci il valore da inserire: ";
        cin>>n;
        binaryTree<int>->Insert(std::move(n));
    } else if (tipo == "string") {
        string n;
        cout<<"Inserisci il valore da inserire: ";
        cin>>n;
        binaryTree<string>->Insert(std::move(n));
    }
    else if (tipo == "double") {
        double n;
        cout<<"Inserisci il valore da inserire: ";
        cin>>n;
        binaryTree<double>->Insert(std::move(n));
    }
}

void BinaryTreeRemoveMenu() {
    char again = 'y';
    do {
        cout << u8"\033[2J\033[1;1H";
        int choise;
        cout << "Che rimozione vuoi effettuare: " << endl
             << "1:( Remove )" << endl
             << "2:( Remove Predecessor )" << endl
             << "3:( Remove Successor )" << endl
             << "4:( Remove Min )" << endl
             << "5:( Remove Max )" << endl
             << "Scelta: ";
        cin >> choise;
        switch (choise) {
            case 1:
                BinaryTreeRemove();
                break;
            case 2:
                BinaryTreeRemovePredecessor();
                break;
            case 3:
                BinaryTreeRemoveSuccessor();
                break;
            case 4:
                BinaryTreeRemoveMin();
                break;
            case 5:
                BinaryTreeRemoveMax();
                break;
        }
        cout << endl << "Vuoi effettuare un altra rimozione (y/f): ";
        cin >> again;
    } while (again == 'y' || again == 'Y');
}

void BinaryTreeRemove(){
    if (tipo == "int") {
        int n;
        cout<<"Inserisci il valore da rimuovere: ";
        cin>>n;
        binaryTree<int>->Remove(n);
    } else if (tipo == "string") {
        string n;
        cout<<"Inserisci il valore da rimuovere: ";
        cin>>n;
        binaryTree<string>->Remove(n);
    }
    else if (tipo == "double") {
        double n;
        cout<<"Inserisci il valore da rimuovere: ";
        cin>>n;
        binaryTree<double>->Remove(n);
    }
}

void BinaryTreeRemovePredecessor(){
    if (tipo == "int") {
        int n;
        cout<<"Inserisci il valore da rimuovere: ";
        cin>>n;
        binaryTree<int>->RemovePredecessor(n);
    } else if (tipo == "string") {
        string n;
        cout<<"Inserisci il valore da rimuovere: ";
        cin>>n;
        binaryTree<string>->RemovePredecessor(n);
    }
    else if (tipo == "double") {
        double n;
        cout<<"Inserisci il valore da rimuovere: ";
        cin>>n;
        binaryTree<double>->RemovePredecessor(n);
    }
}

void BinaryTreeRemoveSuccessor(){
    if (tipo == "int") {
        int n;
        cout<<"Inserisci il valore da rimuovere: ";
        cin>>n;
        binaryTree<int>->RemoveSuccessor(n);
    } else if (tipo == "string") {
        string n;
        cout<<"Inserisci il valore da rimuovere: ";
        cin>>n;
        binaryTree<string>->RemoveSuccessor(n);
    }
    else if (tipo == "double") {
        double n;
        cout<<"Inserisci il valore da rimuovere: ";
        cin>>n;
        binaryTree<double>->RemoveSuccessor(n);
    }
}

void BinaryTreeRemoveMin(){
    if (tipo == "int") {
        int n;
        binaryTree<int>->RemoveMin();
    } else if (tipo == "string") {
        string n;
        binaryTree<string>->RemoveMin();
    }
    else if (tipo == "double") {
        double n;
        binaryTree<double>->RemoveMin();
    }
}

void BinaryTreeRemoveMax(){
    if (tipo == "int") {
        int n;
        binaryTree<int>->RemoveMax();
    } else if (tipo == "string") {
        string n;
        binaryTree<string>->RemoveMax();
    }
    else if (tipo == "double") {
        double n;
        binaryTree<double>->RemoveMax();
    }
}

void BinaryTreeVisit() {
    char again = 'y';
    do {
        cout << u8"\033[2J\033[1;1H";
        int choise;
        cout << "Che stampa vuoi effettuare: " << endl
             << "1:( Predecessor )" << endl
             << "2:( Successor )" << endl
             << "3:( Min )" << endl
             << "4:( Max )" << endl
             << "Scelta: ";
        cin >> choise;
        switch (choise) {
            case 1:
                BinaryTreePredecessor();
                break;
            case 2:
                BinaryTreeSuccessor();
                break;
            case 3:
                BinaryTreeMin();
                break;
            case 4:
                BinaryTreeMax();
                break;
        }
        cout << endl << "Vuoi effettuare un altra stampa (y/f): ";
        cin >> again;
    } while (again == 'y' || again == 'Y');
}

void BinaryTreePredecessor(){
    if (tipo == "int") {
        int n;
        cout<<"Inserisci il valore di cui vuoi il predecessore: ";
        cin>>n;
        cout<<endl<<"Predecessore: "<<binaryTree<int>->Predecessor(n);
    } else if (tipo == "string") {
        string n;
        cout<<"Inserisci il valore di cui vuoi il predecessore: ";
        cin>>n;
        cout<<endl<<"Predecessore: "<<binaryTree<string>->Predecessor(n);
    }
    else if (tipo == "double") {
        double n;
        cout<<"Inserisci il valore di cui vuoi il predecessore: ";
        cin>>n;
        cout<<endl<<"Predecessore: "<<binaryTree<double>->Predecessor(n);
    }
}

void BinaryTreeSuccessor(){
    if (tipo == "int") {
        int n;
        cout<<"Inserisci il valore di cui vuoi il successore: ";
        cin>>n;
        cout<<endl<<"Successore: "<<binaryTree<int>->Successor(n);
    } else if (tipo == "string") {
        string n;
        cout<<"Inserisci il valore di cui vuoi il successore: ";
        cin>>n;
        cout<<endl<<"Successore: "<<binaryTree<string>->Successor(n);
    }
    else if (tipo == "double") {
        double n;
        cout<<"Inserisci il valore di cui vuoi il successore: ";
        cin>>n;
        cout<<endl<<"Successore: "<<binaryTree<double>->Successor(n);
    }
}

void BinaryTreeMin(){
    if (tipo == "int") {
        cout<<"Minimo: "<<binaryTree<int>->Min();
    } else if (tipo == "string") {
        cout<<"Minimo: "<<binaryTree<string>->Min();
    }
    else if (tipo == "double") {
        cout<<"Minimo: "<<binaryTree<double>->Min();
    }
}

void BinaryTreeMax(){
    if (tipo == "int") {
        cout<<"Massimo: "<<binaryTree<int>->Max();
    } else if (tipo == "string") {
        cout<<"Massimo: "<<binaryTree<string>->Max();
    }
    else if (tipo == "double") {
        cout<<"Massimo: "<<binaryTree<double>->Max();
    }
}
