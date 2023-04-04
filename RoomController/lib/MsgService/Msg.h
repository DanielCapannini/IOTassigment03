#ifdef _MSG_
#define _MSG_

#include <Arduino.h>

class Msg
{
public:
    Msg(String msg){
        _msg = msg;
    }
    String getMsg(){
        return _msg;
    }
private:
    String _msg;
};

#endif