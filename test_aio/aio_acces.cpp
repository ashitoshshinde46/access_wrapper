#include "aio_acces.h" 

// DIOWriteRead dio_handle;


int aio_readChannle(int ch, uint32_t *data){
   int err= aio_handle.readChannel(ch, data);
return err;
}

// int dio_writeall(void *data){
//        int err= dio_handle.writeall(data);
// return err;
// }

// int dio_readsingle(){
//     return 0;
// }

// int dio_writesingle(int id, bool bit){
//        int err= dio_handle.writesingle(id,bit);
// return err;
// }