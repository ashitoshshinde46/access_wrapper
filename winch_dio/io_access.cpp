#include "io_access.h" 

// void start_logger(){
// el::Configurations conf("logging_config.conf");
// el::Loggers::reconfigureAllLoggers(conf);
// el::Loggers::addFlag(el::LoggingFlag::StrictLogFileSizeCheck);

// LOG(TRACE) <<"trace log enabled";
// LOG(DEBUG) <<"DEBUG log enabled";
// LOG(ERROR) <<"ERROR log enabled";
// LOG(WARNING) <<"WARNING log enabled";
// LOG(INFO) <<"INFO log enabled";
// }
    
// void stop_logger(){
//     el::Helpers::uninstallPreRollOutCallback();
// }

// start_logger();

static DIOWriteRead dio_handle_1("/dev/accesio/usb_iiro_16_0_1");

static DIOWriteRead dio_handle_2("/dev/accesio/usb_iiro_16_1_2");


int readall_dio(int card_id,uint8_t *data){

int err;
if (card_id==1){
   err= dio_handle_1.readall(data);
   }
   else{
   err= dio_handle_2.readall(data);
   }
return err;
}

int writeall_dio(int card_id, uint8_t *data){
	int err;
	if (card_id==1){
       err= dio_handle_1.writeall(data);
       }
       else{
       err= dio_handle_2.writeall(data);
       }
return err;
}

int readsingle_dio(){
    return 0;
}

int writesingle_dio(int card_id,int id, bool bit){
int err;
if (card_id==1){
       err= dio_handle_1.writesingle(id,bit);
       }
       else{
       err= dio_handle_2.writesingle(id,bit);
       }
return err;
}
