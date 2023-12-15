#include "read_write_dio.h"

DIOWriteRead::DIOWriteRead(){

   ofstream outFile("login.txt");
    
      // Write the login information to the file
  outFile << "in DIO constructor" << endl;
  // outFile << "Password: " << password << endl;

  // Close the file
  outFile.close();

  // Write to the file
  // MyFile << "in DIOWriteRead constructor"<<std::endl;

  // Close the file
 
    AIOUSB::AiousbInit();
  // int err= DeviceHandleByIndex (0, &Device);
// int argc;
// char **argv;
// err = SampleGetDeviceHandle(argc, argv, &Device);
  int  err =AIOUSB::DeviceHandleByPath("/dev/accesio/usb_iiro_16_1_2", &Device);

  if ( 0 == err )
  {
  uint32_t NameSize = 255;
  char Name[NameSize];
  uint32_t Pid;
  AIOUSB::QueryDeviceInfo(Device, &Pid, &NameSize, Name, nullptr, nullptr);
  AIOUSB::GetDeviceSerialNumber(Device, &SerialNum);
  std::cout << Name << " detected [" << std::hex << Pid << std::dec << "]" << std::endl;
  std::cout << "Serial Number: " <<std::hex << SerialNum << std::dec << std::endl;
  std::cout << Name << " detected" << std::endl;

  // if (std::find(IIRO_PIDS.begin(), IIRO_PIDS.end(), Pid) == IIRO_PIDS.end())
  // {
  //   std::cout << "This sample is not intended for use with " << Name << std::endl;
  //   // exit(-1);
  // }
    
    uint8_t Data[4] = { 0xff, 0xff, 0xff, 0xff };

  std::cout << "Energizing all relays" << std::endl;
  AIOUSB::DIO_WriteAll(Device, Data);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  std::cout << "Performing walking bit on relays" << std::endl;
       std::cout << "Performing walking bit on relays" << std::endl;

  for (int i = 0 ; i < 8 ; i++)
  {
    AIOUSB::DIO_Write1(Device, i, 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    AIOUSB::DIO_Write1(Device, i, 0);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  }
    else{
std::cout << "Unable to get device handle" << std::endl;
    // SampleUsage(argc, argv);
    // exit (-1);
        Status=-1;
  }
}


int DIOWriteRead::readall(void *data){
if (Status==0){
AIOUSB::DIO_ReadAll(Device, data);
return Status;
}
    return -1;

}


int DIOWriteRead::writeall(void *data){
    if (Status==0){
AIOUSB::DIO_WriteAll(Device, data);
        return Status;
}
    return -1;
}

int DIOWriteRead::readsingle(){
return -1;
}


int DIOWriteRead::writesingle(int i, bool bit){
     if (Status==0){
 AIOUSB::DIO_Write1(Device, i, bit);
         return Status;
}
    return -1;
}



DIOWriteRead::~DIOWriteRead(){
    // MyFile << "in DIOWriteRead destructor"<<std::endl;
 // MyFile.close();
}