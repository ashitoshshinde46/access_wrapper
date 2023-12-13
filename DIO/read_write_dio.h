#ifndef UTILS_
#define UTILS_


#include <list>
#include <algorithm>
#include <string.h>
#include <chrono>
#include <thread>
#include <iomanip>
#include <iostream>
#include "aiousb.h"

// #include "AiousbSamples.inc"

static const std::list<uint16_t> IIRO_PIDS =
{
  0x8010,
  0x8011,
  0x8012,
  0x8014,
  0x8015,
  0x8016,
  0x8018,
  0x8019,
  0x801A,
  0x801C,
  0x801D,
  0x801E,
  0x801F,
};

class DIOWriteRead{
public:
    DIOWriteRead();
    int readall(void *data);
    int writeall(void *data);
    int readsingle();
    int writesingle(int i, bool bit);
    ~DIOWriteRead();
private:
    int Status;
    AIOUSB::aiousb_device_handle Device;
    uint64_t SerialNum;
    
};

#endif