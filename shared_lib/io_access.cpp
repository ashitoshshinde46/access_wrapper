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

static DIOWriteRead dio_handle;

int dio_readall(void *data){
   int err= dio_handle.readall(data);
return err;
}

int dio_writeall(void *data){
       int err= dio_handle.writeall(data);
return err;
}

int dio_readsingle(){
    return 0;
}

int dio_writesingle(int id, bool bit){
       int err= dio_handle.writesingle(id,bit);
return err;
}
