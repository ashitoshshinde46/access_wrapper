#include "aio_acces.h" 

// DIOWriteRead dio_handle;


int aio_readChannle(int ch, float *data_r){
	double data=0;
   int err= aio_handle.readChannel(ch, &data);
   *data_r=data;
return 1;
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
