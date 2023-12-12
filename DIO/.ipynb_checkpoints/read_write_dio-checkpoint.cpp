#include "read_write_dio.h"

DIOWriteRead::DIOWriteRead(){
 // AIOUSB::AiousbInit();
  int err= DeviceHandleByPath ("", &Device);

  // Status = SampleGetDeviceHandle(argc, argv, &Device);

  if ( 0 != err )
  {
    std::cout << "Unable to get device handle" << std::endl;
    // SampleUsage(argc, argv);
    // exit (-1);
  }

  uint32_t NameSize = 255;
  char Name[NameSize];
  uint32_t Pid;

  AIOUSB::QueryDeviceInfo(Device, &Pid, &NameSize, Name, nullptr, nullptr);
  AIOUSB::GetDeviceSerialNumber(Device, &SerialNum);
  std::cout << Name << " detected [" << std::hex << Pid << std::dec << "]" << std::endl;
  std::cout << "Serial Number: " <<std::hex << SerialNum << std::dec << std::endl;

  std::cout << Name << " detected" << std::endl;

  if (std::find(IIRO_PIDS.begin(), IIRO_PIDS.end(), Pid) == IIRO_PIDS.end())
  {
    std::cout << "This sample is not intended for use with " << Name << std::endl;
    // exit(-1);
  }
    
    uint8_t Data[4] = { 0xff, 0xff, 0xff, 0xff };

  std::cout << "Energizing all relays" << std::endl;
  AIOUSB::DIO_WriteAll(Device, Data);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  std::cout << "Performing walking bit on relays" << std::endl;

}


int DIOWriteRead::readall(char Data[]){
    
AIOUSB::DIO_ReadAll(Device, Data);

}


int DIOWriteRead::writeall(char Data[]){
AIOUSB::DIO_WriteAll(Device, Data);
}

int DIOWriteRead::readsingle(){

}


int DIOWriteRead::writesingle(int i, bool bit){
 AIOUSB::DIO_Write1(Device, i, bit);
}



DIOWriteRead::~DIOWriteRead(){


}