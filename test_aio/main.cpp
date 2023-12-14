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
for(int i=0;i<100;i++){
    float data=0;
    //for(int ch=1;ch<8;ch++){
    //printf("be Channel read:%d\n",data);
    int error= aio_readChannle(0, &data);
    //printf("Error:%d\n",error);
    printf("Channel read:% 8.4f\n",data);
    //}
  }
  
return 0;
}
