#include <bluetooth.h>

Bluetooth::Bluetooth(String id, String value)
{
    this-> _id = id;
    this-> _value = value;
    this-> _Kp;
    this-> _Ki;
    this-> _Kd;
    this-> _Contagem;
    this-> _Go;
    this-> _Stop;
    this-> _debugger;
    this-> _Calibra;

}

float Bluetooth::Kp()
{  
    if (_id == String("Kp"))
    {
        _Kp = _value.toFloat();
        return (_Kp);
        _id = "";
    }

}

float Bluetooth::Ki()
{  
    if (_id == String("Ki"))
    {
        _Ki = _value.toFloat();
        return (_Ki);
        _id = "";
    }

}

float Bluetooth::Kd()
{  
    if (_id == String("Kd"))
    {
        _Kd = _value.toFloat();
        return (_Kd);
        _id = "";
    }

}

String Bluetooth::Go()
{  
    if (_id == String("Go"))
    {
        return ("Go");
        _id = "";
    }

}

String Bluetooth::Stop()
{  
    if (_id == String("Stop"))
    {
        return ("Stop");
        _id = "";
    }
}

String Bluetooth::Calibra()
{  
    if (_id == String("Calibra"))
    {
        _Calibra = _value.toFloat();
        return (_Calibra);
        _id = "";
    }

}

int Bluetooth::Contagem()
{  
    if (_id == String("Contagem"))
    {
        _Contagem = _value.toFloat();
        return (_Contagem);
        _id = "";
    }

}

String Bluetooth::debugger()
{  
    if (_id == String("debugger"))
    {
        _debugger = _value.toFloat();
        return (_debugger);
        _id = "";
    }

}