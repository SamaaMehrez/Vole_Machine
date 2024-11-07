#include "ALU.h"
#include <string>
#include <vector>
using namespace std;
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