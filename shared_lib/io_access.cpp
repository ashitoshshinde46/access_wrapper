#include "io_access.h" 

// DIOWriteRead dio_handle;

int dio_readall(void *data){
   int err= dio_handle.readall(Data);
return err;
}

int dio_writeall(void *data){
       int err= dio_handle.writeall(Data);
return err;
}

int dio_readsingle(){
    return 0;
}

int dio_writesingle(int id, bool bit){
       int err= dio_handle.writesingle(id,bit);
return err;
}