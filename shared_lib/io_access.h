#ifndef UTILS_H_
#define UTILS_H_

#include "read_write_dio.h" 

static DIOWriteRead dio_handle;

// extern "C"
// {
    int dio_readall(char Data[]);
    int dio_writeall(char Data[]);
    int dio_readsingle();
    int dio_writesingle(int id, bool bit);
// }

#endif