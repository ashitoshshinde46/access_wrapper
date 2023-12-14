// #include "io_access.h"
#include "aio_acces.h"

using namespace std;

int main(){
/*** Code for Digital IO
uint8_t Data[4] = { 0xff, 0xff, 0xff, 0xff };

int error=dio_readall(Data);
cout<<"Error :"<<error<<endl;
for (int i = 0 ; i < 4 ; i++)
  {
    std::cout << "bits "<< std::dec << i*8 << "-" << (i+1)*8-1 << ": 0x" << std::hex << std::setw(2) << std::setfill('0') << int(Data[i]) << std::endl;
  }
  std::cout << std::endl;
***/
    uint32_t data=0;
    int error= aio_readChannle(1, &data);
  
  
return 0;
}