#include "io_access.h" 

// DIOWriteRead dio_handle;

int dio_readall(uint8_t Data){
   int err= dio_handle.readall(Data);
return err;
}

int dio_writeall(uint8_t Data){
       int err= dio_handle.writeall(Data);
return err;
}

int dio_readsingle(){
}

int dio_writesingle(int id, bool bit){
       int err= dio_handle.writesingle(id,bit);
return err;
}