#include "io_access.h"
using namespace std;

int main(){

uint8_t Data[4] = { 0xff, 0xff, 0xff, 0xff };
int error=dio_readall(Data);
cout<<"Error :"<<error<<endl;
cout<<"Port data:"<< Data[0]<<endl;   
return 0;
}