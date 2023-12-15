#ifndef UTILS_H_
#define UTILS_H_

#include "read_write_dio.h" 



extern "C"
{
    int readall_dio(int card_id,uint8_t *data);
    int writeall_dio(int card_id,uint8_t *data);
    int readsingle_dio();
    int writesingle_dio(int card_id,int id, bool bit);
}


void start_logger();    
void stop_logger();
#endif
