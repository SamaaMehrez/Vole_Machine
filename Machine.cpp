#include "Machine.h"
Machine::Machine() {}
void Machine::loadProgramFile() {
    string name;
    cout << "Enter file name: ";
    cin >> name;
    ifstream file(name);
    if (file.fail()) {
        cout << "Failed to open file\n";
        return;
    }

    vector<string> vec;
    string s;
    int words = 0;
    int memoryIndex = 10;

    while (file >> s) {
        words++;
        if (s.size() != 2) {
            cout << "The instruction is not valid. It must be exactly 4 bits (2 hex characters).\n";
            break;
        }
        bool isHex = true;
        for (char ch : s) {
            if (!isxdigit(ch)) {
                isHex = false;
                break;
            }
        }

        if (!isHex) {
            cout << "The instruction is not valid. It contains non-hexadecimal characters.\n";
            break;
        }

        processor.mem().Set(memoryIndex, s);

        if (memoryIndex % 2 == 1) {
            processor.fetch();
            processor.execute();
        }
        memoryIndex++;
    }

}


void Machine::screen() {
    cout<<"**************************************************\n";
    cout<<"The output of screen is: ";
    processor.vec_screen();
    cout<<endl;
    cout<<"**************************************************\n";
}
    void Machine::outputState(){
        cout<<"Registers:\n";
        processor.regg().Print();
        cout<<"\n************************************************\n";
        cout<<"Memory:\n";
        processor.mem().print();
    }
