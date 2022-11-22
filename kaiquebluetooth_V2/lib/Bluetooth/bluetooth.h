#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <Arduino.h>

class Bluetooth
{

public:
    Bluetooth(String id, String value);
    float Kp(void);
    float Ki(void);
    float Kd(void);
    String Go(void);
    String Stop(void);
    String Calibra(void);
    int Contagem(void);
    String debugger(void);

private:
    float _Kp;
    float _Ki;
    float _Kd;
    int _Contagem;
    String _Go;
    String _Stop;
    String _debugger;
    String _id;
    String _value;
    String _Calibra;

};

#endif