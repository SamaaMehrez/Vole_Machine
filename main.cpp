#include "Vole_Machine.h"
#include<bits/stdc++.h>
using namespace std;
int main() {
    Machine machine;
    char choice;
    while(true) {
        cout << "<-- Menu -->\n1- Load and Execute the program\n2- Output the Memory,Screen and Registers\n3- "
                "Exit\nYour choice:";
        cin >> choice;
        if (choice == '1') {
            machine.loadProgramFile();
            continue;
        } else if (choice == '2') {
            machine.outputState();
            cout << endl;
            machine.screen();
            continue;
        }
        else if (choice == '3') {
            cout << "Thank you for using this program\n";
            break;
        }
        else{
            cout<<"Invalid,please enter a valid choice\n";
            continue;
        }


    }



    return 0;
}

