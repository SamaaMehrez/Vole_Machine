#include "Memory.h"
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