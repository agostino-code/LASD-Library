#include <iostream>
#include <random>
#include "test.hpp"
#include "../zlasdtest/test.hpp"

using namespace std;
using namespace lasd;
string tipo;

void CreateStruct(){
    int choise=0;
        cout << "0:( test)"<<endl;
        cout << "Che struttura dati vuoi usare: "<<endl
                <<"1:( stacklst )"<<endl
                <<"2:( queuelst )"<<endl
                <<"3:( stackvec )"<<endl
                <<"4:( queuevec )"<<endl
                <<"Scelta: "; cin >> choise;
        switch (choise) {
            case 0:
                lasdtest();
                break;
            case 1:
                CreateStackLst();
                break;
            case 2:
                CreateQueueLst();
                break;
            case 3:
                CreateStackVec();
                break;
            case 4:
                CreateQueueVec();
                break;
        }
}

void CreateStackLst() {
    while (tipo != "int" && tipo != "string" && tipo != "double") {
        cout << "Che tipo di dati deve contenere?: ( int / string / double ) : ";
        cin >> tipo;
    }
        if (tipo == "int") { stack<int> = new StackLst<int>; }
        else {if (tipo == "string") { stack<string> = new StackLst<string>; }
        else { if (tipo == "double") { stack<double> = new StackLst<double>; }}}
        RandomStack();
        MenuStack();
}

void CreateStackVec() {
    while(tipo!="int" && tipo!="string" && tipo!="double") {
        cout << "Che tipo di dati deve contenere?: ( int / string / double ) : ";
        cin >> tipo;
    }
    if (tipo == "int") { stack<int> = new StackVec<int>; }
    else { if (tipo == "string") { stack<string> = new StackVec<string>; }
    else { if (tipo == "double") { stack<double> = new StackVec<double>; } } }
    RandomStack();
    MenuStack();
}

void CreateQueueLst() {
    while(tipo!="int" && tipo!="string" && tipo!="double") {
        cout << "Che tipo di dati deve contenere?: ( int / string / double ) : ";
        cin >> tipo;
    }
    if (tipo == "int") {queue<int> = new QueueLst<int>; }
    else { if (tipo == "string") { queue<string> = new QueueLst<string>; }
    else { if (tipo == "double") { queue<double> = new QueueLst<double>; } }}
    RandomQueue();
    MenuQueue();
}

void CreateQueueVec() {
    while(tipo!="int" && tipo!="string" && tipo!="double") {
        cout << "Che tipo di dati deve contenere?: ( int / string / double ) : ";
        cin >> tipo;
    }
    unsigned long n;
    cout << "Dai una dimenzione a questa queue: ";
    cin >> n;
    if (tipo == "int") { queue<int> = new QueueVec<int>; }
    else { if (tipo == "string") { queue<string> = new QueueVec<string>; }
    else { if (tipo == "double") { queue<double> = new QueueVec<double>; } }}
    RandomQueue();
    MenuQueue();
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

void RandomStack(){
    unsigned long n;
    cout << "Dai una dimenzione a questo stack: ";
    cin >> n;
    if (tipo == "int") {
        for (unsigned long i = 0; i < n; i++) {
            stack<int>->Push(RandomInt());
        }
    } else if (tipo == "string") {
        for (unsigned long i = 0; i < n; i++) {
            stack<string>->Push(RandomString());
        }
    }
    else if (tipo == "double") {
        for (unsigned long i = 0; i < n; i++) {
            stack<double>->Push(RandomDouble());
        }
    }
}

void RandomQueue(){
    unsigned long n;
    cout << "Dai una dimenzione a questo stack: ";
    cin >> n;
    if (tipo == "int") {
        for (unsigned long i = 0; i < n; i++) {
            queue<int>->Enqueue(RandomInt());
        }
    } else if (tipo == "string") {
        for (unsigned long i = 0; i < n; i++) {
            queue<string>->Enqueue(RandomString());
        }
    } else if (tipo == "double") {
        for (unsigned long i = 0; i < n; i++) {
            queue<double>->Enqueue(RandomDouble());
        }
    }
}

void MenuStack() {
    char again='y';
    do {
        //cout<< u8"\033[2J\033[1;1H";
        int choise;
        cout << "Che operazione vuoi effettuare: " << endl
             << "1:( Push )" << endl
             << "2:( Top )" << endl
             << "3:( Pop )" << endl
             << "4:( TopNPop )" << endl
             << "Scelta: ";
        cin >> choise;
        switch (choise) {
            case 1:
                StackPush();
                break;
            case 2:
                StackTop();
                break;
            case 3:
                StackPop();
                break;
            case 4:
                StackTopNPop();
                break;
        }
        cout << "Vuoi effettuare un altra operazione (y/f): ";
        cin >> again;
    } while (again=='y' || again=='y');
}

    void StackPush(){
        if (tipo == "int") {
                stack<int>->Push(RandomInt());
        } else if (tipo == "string") {
                stack<string>->Push(RandomString());
        }
        else if (tipo == "double") {
                stack<double>->Push(RandomDouble());
        }
    }

    void StackTop(){
        if (tipo == "int") {
                cout<<stack<int>->Top()<<endl;
        } else if (tipo == "string") {
                cout<<stack<string>->Top()<<endl;
        }
        else if (tipo == "double") {
                cout<<stack<double>->Top()<<endl;
        }
    }

    void StackPop(){
        if (tipo == "int") {
                stack<int>->Pop();
        } else if (tipo == "string") {
                stack<string>->Pop();
        }
        else if (tipo == "double") {
                stack<double>->Pop();
        }
    }

    void StackTopNPop(){
        if (tipo == "int") {
                cout<<stack<int>->TopNPop()<<endl;
        } else if (tipo == "string") {
                cout<<stack<string>->TopNPop()<<endl;
        }
        else if (tipo == "double") {
                cout<<stack<double>->TopNPop()<<endl;
        }
    }

void MenuQueue() {
    char again='y';
    do{
        cout<< u8"\033[2J\033[1;1H";
        int choise;
    cout << "Che operazione vuoi effettuare: " << endl
         << "1:( Enqueue )" << endl
         << "2:( Head )" << endl
         << "3:( Dequeue )" << endl
         << "4:( HeadNDequeue )" << endl
         << "Scelta: ";
    cin >> choise;
    switch (choise) {
        case 1:
            QueueEnqueue();
            break;
        case 2:
            QueueHead();
            break;
        case 3:
            QueueDequeue();
            break;
        case 4:
            QueueHeadNDequeue();
            break;
    }

    cout << "Vuoi effettuare un altra operazione (y/f): " << endl;
    cin >> again;
    } while (again=='y' || again=='y');
}

void QueueEnqueue(){
    if (tipo == "int") {
            queue<int>->Enqueue(RandomInt());
    } else if (tipo == "string") {
            queue<string>->Enqueue(RandomString());
    } else if (tipo == "double") {
            queue<double>->Enqueue(RandomDouble());
    }
}

void QueueHead(){
        if (tipo == "int") {
            cout<<queue<int>->Head()<<endl;
        } else if (tipo == "string") {
            cout<<queue<string>->Head()<<endl;
        } else if (tipo == "double") {
            cout<<queue<double>->Head()<<endl;
        }
}

void QueueDequeue(){
    if (tipo == "int") {
        queue<int>->Dequeue();
    } else if (tipo == "string") {
        queue<string>->Dequeue();
    } else if (tipo == "double") {
        queue<double>->Dequeue();
    }
}

void QueueHeadNDequeue(){
    if (tipo == "int") {
        cout<<queue<int>->HeadNDequeue()<<endl;
    } else if (tipo == "string") {
        cout<<queue<string>->HeadNDequeue()<<endl;
    } else if (tipo == "double") {
        cout<<queue<double>->HeadNDequeue()<<endl;
    }
}
