#include "read_write_dio.h" 

DIOWriteRead dio_handle;

extern "C"
{
    int dio_readall(uint8_t Data);
    int dio_writeall(uint8_t Data);
    int dio_readsingle();
    int dio_writesingle(int id, bool bit);
}