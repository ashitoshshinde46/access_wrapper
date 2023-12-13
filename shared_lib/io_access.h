#ifndef UTILS_H_
#define UTILS_H_

#include "read_write_dio.h" 

static DIOWriteRead dio_handle;

extern "C"
{
    int dio_readall(void *data);
    int dio_writeall(void *data);
    int dio_readsingle();
    int dio_writesingle(int id, bool bit);
}

#endif