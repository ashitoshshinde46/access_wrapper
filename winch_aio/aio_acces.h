#ifndef UTILS_H_AIO
#define UTILS_H_AIO

#include "read_write_aio.h" 

static AIOWriteRead aio_handle;

extern "C"
{
    int aio_readChannle(int ch, float *data);
    // int dio_writeall(void *data);
    // int dio_readsingle();
    // int dio_writesingle(int id, bool bit);
}

#endif
