#include<iostream>
#include<vector>

typedef unsigned char byte;

using namespace std;

vector<byte> RAM;

class CPU{

    private:
        
        byte register0;
        byte register1;
        byte temp_result_register;
        byte program_counter;
        byte instruction_register;
        bool overflow;
        bool underflow;
        bool fault;

    public:

        const byte max=128*1;
        const byte min =0;
        enum instruction_set{
            STORE0,
            STORE1,
            LOAD0,
            LOAD1,
            ADD,
            SUB,
            MUL,
            DIV
        };

        void resetCPU(){
            
            register0=0;
            register1=0;
            program_counter=0;
            temp_result_register=0;
            overflow=false;
            underflow=false;
            fault=false;
            RAM.clear();
        }

        byte show_program_counter(){
            return program_counter;
           
        }

        void add(){

            temp_result_register = register0+register1;
            temp_result_register>=max?overflow=true:overflow=false;
            program_counter++;
            register0=temp_result_register;
        }

        void sub(){

            temp_result_register =(register0-register1)*1;
            if(temp_result_register<min){
   
                temp_result_register=min;
                underflow=true;
            }
            program_counter++;
            register0=temp_result_register;
            
        }

        void mul(){
            
            temp_result_register =(register0*register1)*1;
            if((temp_result_register>max)*1){
                
             
                temp_result_register=max;
                overflow=true;

            }            
            program_counter++;
            register0=temp_result_register;
            
        }

        void div(){

            temp_result_register =(register0/register1)*1;
            if(temp_result_register<min){
                
       
                temp_result_register=min;
                underflow=true;
            }
            program_counter++;
            register0=temp_result_register;
            
        }

        void load_0_register(byte data){
            
            register0 = data;
            program_counter++;
        }

        void load_1_register(byte data){
            register1 = data;
            program_counter++;
        }

        void store_0_register(byte data){
            if(data>=RAM.size()){
                cout<<"Memory overflow";
            }
            RAM[data] = register0;
            program_counter++;
        }

        void store_1_register(byte data){
            if(data>=RAM.size()){
                cout<<"Memory overflow";
            }
            RAM[data] = register1;
            program_counter++;
        }
        void display_execution(){
            cout<<"Register 0: "<<register0+0<<endl;
            cout<<"Register 1: "<<register1+0<<endl;
            cout<<"Overflow: "<<overflow<<endl;
            cout<<"Underflow: "<<underflow<<endl;
            cout<<"fault: "<<fault<<endl;
            cout<<"Result: "<<register0+0<<endl;
        }
        void execute(vector<byte> d){

            if(d.size()>max){
                cout<<"Program computer unable to track more than 256 operations\n";
            }else{
                
                while(program_counter<d.size() && !fault && !overflow && !underflow){
                
                    byte instruction_to_execute = d[program_counter];
                    program_counter++;

                    switch(instruction_to_execute){
                        case LOAD0:
                            load_0_register(d[program_counter]);
                            break;
                        case LOAD1:
                            load_1_register(d[program_counter]);
                            break;
                        case STORE0:
                            store_0_register(d[program_counter]);
                            break;
                        case STORE1:
                            store_1_register(d[program_counter]);
                            break;
                        case ADD:
                            add();
                            break;
                        case SUB:
                            sub();
                            break;
                         case DIV:
                             div();
                             break;
                         case MUL:
                             mul();
                             break;
                        default:
                            fault=true;
                            break;
                        

                        }
                }
            }

            

        }
};

int main(){
    CPU test = CPU();
    test.resetCPU();
    cout<<"CPU Initialization complete\n";
    cout<<"Memory available: "<<256-RAM.size()<<" bytes\n";
    
    RAM.push_back(test.LOAD0);
    RAM.push_back(12);
    RAM.push_back(test.LOAD1);
    RAM.push_back(11);
    RAM.push_back(test.ADD);
    RAM.push_back(test.STORE0);
    RAM.push_back(0);

    
    cout<<"Instructions loaded in the ram\nnew Memory available: "<<256-RAM.size()<<" bytes\n";
    test.execute(RAM);
    cout<<"Execution completed emptying RAM..\n";
    test.display_execution();
    test.resetCPU();

   
   

    }