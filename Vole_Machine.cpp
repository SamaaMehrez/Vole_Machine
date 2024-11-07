#include "Vole_Machine.h"
#include<bits/stdc++.h>
using namespace std;
Memory::Memory():memory(256,"00"){}
void Memory:: Set(int addr,string val){
    if(addr<0 or addr>256){
        cout<<"Memory address is not between 0 and 256\n";
    }
    memory[addr]=std::move(val);
}
string Memory::Get(int addr){
    if(addr<0 or addr>256){
        cout<<"Memory address is not between 0 and 256\n";
    }
    return memory[addr];
}
void Memory:: print(){
    int count=0,count2=0;
    cout<<" ";
    for(int k=0;k<16;k++){
    cout<<setw(3)<<k;
    }
    cout<<endl;
    cout<<0<<"  ";
    for(int i=1;i<=memory.size();i++){
        count++;
        cout<<memory[i-1]<<" ";
        if(count==16 and i!=memory.size()){
            cout<<endl;
            count2++;
            cout<<count2<<"  ";
            count=0;
        }

    }
}
Register::Register():registers(16,"00"){
}
void Register:: Set_reg(int reg,string val){
    if(reg<0 or reg>15){
        cout<<"Register index is not between 0 and 15\n";
    }
    registers[reg]=std::move(val);
}
string Register:: Get_Specific_Reg(int reg){
    if(reg<0 or reg>15){
        cout<<"Register index is not between 0 and 15\n";
    }
    return registers[reg];
}
void Register:: Print(){
    int count=0;
    for(int i=1;i<=registers.size();i++){
        count++;

        if(i>=11){
            cout<<"R"<<hex<<i-1<<": "<<registers[i-1]<<" ";
        }
        else{
            cout<<"R"<<i-1<<": "<<registers[i-1]<<" ";
        }
        if(count==4){
            cout<<endl;
            count=0;
        }
    }
}
CU::CU(){}
void CU:: load(int regIndex, int memAddress, Register& registers,Memory& memory) {
    if (regIndex >= 16  or memAddress >= 256) {
        cout<<"Invalid register or memory address\n";
    }
    string value=memory.Get(memAddress);
    registers.Set_reg(regIndex,value);
    cout<<"Loaded Value:"<<value<<" from memory["<<memAddress<<"] to register["<<regIndex<<"]\n";
}
void CU:: load_2(int regIndex,string index,Register& registers) {
    if (regIndex >= 16) {
        cout<<"Invalid register address\n";
    }
    registers.Set_reg(regIndex,index);
    cout<<"Loaded Value:"<<index<<" to register["<<regIndex<<"]\n";
}
void CU:: store(int regIndex, int memAddress,Register& registers,Memory& memory) {
    if (regIndex >= 16 or memAddress >= 256) {
        cout<<"Invalid register or memory address\n";
    }
    string value=registers.Get_Specific_Reg(regIndex);
    memory.Set(memAddress,value);
    cout<<"Store Value:"<<value<<" from register["<<regIndex<<"] to memory["<<memAddress<<"]\n";
}
void CU::move(int regIndex1, int regIndex2,Register& registers) {
    if (regIndex1 >= 16 or regIndex2 >= 16) {
        cout<<"Invalid register or memory address\n";
    }
    string value=registers.Get_Specific_Reg(regIndex1);
    registers.Set_reg(regIndex2,value);
    cout<<"Move Value:"<<value<<" from register["<<regIndex1<<"] to register["<<regIndex2<<"]\n";
}
bool CU:: jump(int idxReg,Register&reg){
    string com=reg.Get_Specific_Reg(idxReg);
    if(com==reg.Get_Specific_Reg(0)){
        return true;
    }
    else{
        return false;
    }

}

string ALU::decimalToHexadecimal(int decimal) {
    if (decimal < 0) {
        decimal = (decimal + 0x100) & 0xFF;
    }

    vector<char> hexDigits = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    string hexResult = "";

    while (decimal > 0) {
        int remainder = decimal % 16;
        hexResult = hexDigits[remainder] + hexResult;
        decimal /= 16;
    }

    while (hexResult.length() < 2) {
        hexResult = "0" + hexResult;
    }

    return hexResult;
}


int ALU::hexadecimalToDecimal(const std::string& hexStr) {
    int decimalValue = 0;
    int base = 1;

    for (int i = hexStr.length() - 1; i >= 0; --i) {
        char hexDigit = hexStr[i];

        if (hexDigit >= '0' && hexDigit <= '9') {
            decimalValue += (hexDigit - '0') * base;
        }
        else if (hexDigit >= 'A' && hexDigit <= 'F') {
            decimalValue += (hexDigit - 'A' + 10) * base;
        }
        else if (hexDigit >= 'a' && hexDigit <= 'f') {
            decimalValue += (hexDigit - 'a' + 10) * base;
        }
        else {
            cout << "Invalid hexadecimal character: " << hexDigit << "\n";
            return -1;
        }

        base *= 16;
    }

    if (decimalValue >= 0x80) {
        decimalValue -= 0x100;
    }

    return decimalValue;
}


void ALU::add(int idx1, int idx2, int idx3, Register &reg) {
    int addition= hexadecimalToDecimal(reg.Get_Specific_Reg(idx1))+ hexadecimalToDecimal(reg.Get_Specific_Reg(idx2));
    reg.Set_reg(idx3, decimalToHexadecimal(addition));
    cout<<"Add Value:"<<addition<<"from adding register["<<idx1<<"] and register["<<idx2<<"] to register["<<idx3<<"]\n";
}


bool ALU::isValidHexadecimal(const string& hexStr) {
    for (char c : hexStr) {
        if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'))) {
            return false;
        }
    }
    return true;
}

string ALU::hexToBinary(const string& hexStr) {
    string binaryStr;
    for (char hexChar : hexStr) {
        int hexValue = stoi(string(1, hexChar), nullptr, 16);
        binaryStr += bitset<4>(hexValue).to_string();
    }
    return binaryStr;
}

float ALU::binaryToFloat(const string& binaryStr) {
    if (binaryStr.size() != 8) {
        cout<<"Invalid binary input\n";
    }

    int sign = binaryStr[0] == '0' ? 1 : -1;
    int exponent = bitset<3>(binaryStr.substr(1, 3)).to_ulong();
    int mantissa = bitset<4>(binaryStr.substr(4, 4)).to_ulong();

    float decimalValue = sign * pow(2, exponent - 4) * (mantissa / 16.0);
    return decimalValue;
}


string ALU::floatToBinary(float value) {
    int sign = value < 0 ? 1 : 0;
    value = fabs(value);

    int exponent = static_cast<int>(log2(value)) + 4;
    float mantissa = (value / pow(2, exponent - 4)) * 16;

    string binary = to_string(sign);
    binary += bitset<3>(exponent).to_string();
    binary += bitset<4>(static_cast<int>(mantissa)).to_string();
    return binary;
}


string ALU::binaryToHex(const string& binaryStr) {
    int decimal = stoi(binaryStr, nullptr, 2);
    stringstream ss;
    ss << hex << uppercase << decimal;
    return ss.str();
}

void ALU::addFloatHexRegisters(int f_idx1, int f_idx2, int f_idx3, Register& reg) {

    string hex1 = reg.Get_Specific_Reg(f_idx1);
    string hex2 = reg.Get_Specific_Reg(f_idx2);

    if (!isValidHexadecimal(hex1) || !isValidHexadecimal(hex2)) {
        cout<<"Invalid hexadecimal input\n";
    }


    string binary1 = hexToBinary(hex1);
    string binary2 = hexToBinary(hex2);
    float value1 = binaryToFloat(binary1);
    float value2 = binaryToFloat(binary2);

    float result = value1 + value2;


    string binaryResult = floatToBinary(result);
    string hexResult = binaryToHex(binaryResult);


    reg.Set_reg(f_idx3, hexResult);
    cout<<"Add Value:"<<hexResult<<" from adding register["<<f_idx1<<"] and register["<<f_idx2<<"] to register["<<f_idx3<<"]\n";
}

Memory& CPU::mem() {
    return memory;

}
Register& CPU::regg() {
    return reg;
}
CPU::CPU(): programCounter(10), alu() { }
void CPU::fetch() {
    if(programCounter%2==0) {
        instructionRegister = memory.Get(programCounter) + memory.Get(programCounter + 1);
        programCounter += 2;
    }
    else{
        instructionRegister = memory.Get(programCounter-1) + memory.Get(programCounter);
        programCounter += 2;
    }
}
void CPU::execute() {
    if (!flag) {
        char op;
        string last3;
        op = instructionRegister[0];
        string first, last;
        if (op == '1') {
            first += instructionRegister[1];
            last += instructionRegister[2];
            last += instructionRegister[3];
            cu.load(alu.hexadecimalToDecimal(first), alu.hexadecimalToDecimal(last), reg, memory);
        } else if (op == '2') {
            first += instructionRegister[1];
            last += instructionRegister[2];
            last += instructionRegister[3];
            cu.load_2(alu.hexadecimalToDecimal(first), last, reg);

        } else if (op == '3') {
            first += instructionRegister[1];
            last += instructionRegister[2];
            last += instructionRegister[3];
            cu.store(alu.hexadecimalToDecimal(first), alu.hexadecimalToDecimal(last), reg, memory);
            if(last=="00"){
                vec.push_back(memory.Get(alu.hexadecimalToDecimal(last)));
            }
        } else if (op == '4') {
            first += instructionRegister[1];
            last += instructionRegister[2];
            last += instructionRegister[3];
            cu.move(alu.hexadecimalToDecimal(first), alu.hexadecimalToDecimal(last), reg);

        } else if (op == '5') {
            string last1;
            first += instructionRegister[1];
            last += instructionRegister[2];
            last1 += instructionRegister[3];
            alu.add(alu.hexadecimalToDecimal(last), alu.hexadecimalToDecimal(last1), alu.hexadecimalToDecimal(first),
                    reg);
        }

        else if(op=='B'){
            first+=instructionRegister[1];
            last += instructionRegister[2];
            last += instructionRegister[3];
            if(cu.jump(alu.hexadecimalToDecimal(first),reg)){
                string a=memory.Get(alu.hexadecimalToDecimal(last));
                if(alu.hexadecimalToDecimal(last)%2==0){
                    string full=a+memory.Get(alu.hexadecimalToDecimal(last)+1);
                    programCounter=alu.hexadecimalToDecimal(last);
                    cout<<"Jump to memory["<<last<<"]\n";
                    while(memory.Get(programCounter)!="00") {
                        fetch();
                        execute();
                    }
                }
                else{
                    string full=memory.Get(alu.hexadecimalToDecimal(last)-1)+a;
                    programCounter=alu.hexadecimalToDecimal(last);
                    cout<<"Jump to memory["<<last<<"]\n";
                    while(memory.Get(programCounter)!="00") {
                        fetch();
                        execute();
                    }
                }
            }
        }

        else if (op == 'C') {
            flag=1;
            first += instructionRegister[1];
            last += instructionRegister[2];
            last += instructionRegister[3];
            if (first == "0" and last == "00") {
                cout << "HALT instruction encountered. Stopping execution.\n";
            }


        } else if (op == '6') {
            string last1;
            first += instructionRegister[1];
            last += instructionRegister[2];
            last1 += instructionRegister[3];
            alu.addFloatHexRegisters(alu.hexadecimalToDecimal(last), alu.hexadecimalToDecimal(last1),
                                     alu.hexadecimalToDecimal(first), reg);
        }

    }


}
void CPU:: vec_screen(){
    cout<<"[";
    for(int i=0;i<vec.size();i++){
        if(i!=vec.size()-1){
            cout<<vec[i]<<" , ";
        }
        else{
            cout<<vec[i];
        }

    }
    if(vec.empty()){
        cout<<"00";
    }
    cout<<"]";

}
Machine::Machine() {}
void Machine::loadProgramFile() {
    string name;
    cout << "Enter file name:";
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
