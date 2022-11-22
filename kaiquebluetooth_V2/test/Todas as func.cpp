#include <Arduino.h>
#include <Itamotorino.h> // Convertida pra ESP
#include <QTRSensors.h>
#include <PID_v1.h> //funciona

#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif


BluetoothSerial SerialBT;

//============================= FUNCNS =====================================
void printBTMenu();
void coreTaskZero(void *pvParameters);
void coreTaskOne(void *pvParameters);
void calibrarSensor();

boolean calibra = false;
String debugger_func = "true";
String message = "";
float KPr;
float KIr;
float KDr;
float MKp;
float MKi;
float MKd;
int pwm_min;
int pwm_max;
int cont_max = 100;
int contD;

void setup()
{
  Serial.begin(9600);
  Serial.println("SegredoAPP_V1");
  SerialBT.begin("SegredoAPP_V1"); // Bluetooth device name
  delay(5000);

  xTaskCreatePinnedToCore(
      coreTaskZero,   /* função que implementa a tarefa */
      "coreTaskZero", /* nome da tarefa */
      10000,          /* número de palavras a serem alocadas para uso com a pilha da tarefa */
      NULL,           /* parâmetro de entrada para a tarefa (pode ser NULL) */
      2,              /* prioridade da tarefa (0 a N) */
      NULL,           /* referência para a tarefa (pode ser NULL) */
      0);             /* Núcleo que executará a tarefa */
}
// LOOP

void loop()
{
}

void coreTaskZero(void *pvParameters) // BLUTU
{
  String taskMessage = "Bluetooth on core: ";
  taskMessage = taskMessage + xPortGetCoreID();
  Serial.println(taskMessage + "\n");
  while (true)
  {
    // Inicio do while 0
    if (SerialBT.available())
    {
      message = SerialBT.readStringUntil('\n');
      // Serial.println(message);
      // Serial.println("");
      delay(1);
    }

    if (message == String("Kp"))
    {
      if (debugger_func = String("true"))
      {
        Serial.println("menssage recived: " + message);
        Serial.println("Old KP var: " + String(KPr, 6));
        Serial.println("Waiting...");
        SerialBT.println("menssage recived: " + message);
        SerialBT.println("Old KP var: " + String(KPr, 6));
        SerialBT.println("Waiting...");
      }

      do
      {
        message = String("");
        message = SerialBT.readStringUntil('\n');
        KPr = message.toFloat();
        if (debugger_func = String("true"))
        {
          Serial.println("LOOP");
          SerialBT.println("LOOP");
        }
        delay(1);
      } while (message == String(""));
      if (debugger_func = String("true"))
      {
        Serial.println("menssage recived: " + message);
        Serial.println("New KP var: " + String(KPr, 6));
        Serial.println("----------------------------");
        SerialBT.println("menssage recived: " + message);
        SerialBT.println("New KP var: " + String(KPr, 6));
        SerialBT.println("----------------------------");
      }
    }
    if (message == String("Ki"))
    {
      if (debugger_func = String("true"))
      {
        Serial.println("menssage recived: " + message);
        Serial.println("Old KI var: " + String(KIr, 6));
        Serial.println("Waiting...");
        SerialBT.println("menssage recived: " + message);
        SerialBT.println("Old KI var: " + String(KIr, 6));
        SerialBT.println("Waiting...");
      }

      do
      {
        message = String("");
        message = SerialBT.readStringUntil('\n');
        KIr = message.toFloat();
        if (debugger_func = String("true"))
        {
          Serial.println("LOOP");
          SerialBT.println("LOOP");
        }
        delay(1);
      } while (message == String(""));
      if (debugger_func = String("true"))
      {
        Serial.println("menssage recived: " + message);
        Serial.println("New KI var: " + String(KIr, 6));
        Serial.println("----------------------------");
        SerialBT.println("menssage recived: " + message);
        SerialBT.println("New KI var: " + String(KIr, 6));
        SerialBT.println("----------------------------");
      }
    }
    if (message == String("Kd"))
    {
      if (debugger_func = String("true"))
      {
        Serial.println("menssage recived: " + message);
        Serial.println("Old KD var: " + String(KDr, 6));
        Serial.println("Waiting...");
        SerialBT.println("menssage recived: " + message);
        SerialBT.println("Old KD var: " + String(KDr, 6));
        SerialBT.println("Waiting...");
      }

      do
      {
        message = String("");
        message = SerialBT.readStringUntil('\n');
        KDr = message.toFloat();
        if (debugger_func = String("true"))
        {
          Serial.println("LOOP");
          SerialBT.println("LOOP");
        }
        delay(1);
      } while (message == String(""));
      if (debugger_func = String("true"))
      {
        Serial.println("menssage recived: " + message);
        Serial.println("New KD var: " + String(KDr, 6));
        Serial.println("----------------------------");
        SerialBT.println("menssage recived: " + message);
        SerialBT.println("New KD var: " + String(KDr, 6));
        SerialBT.println("----------------------------");
      }
    }
    if (message == String("Vmax"))
    {
      if (debugger_func = String("true"))
      {
        Serial.println("menssage recived: " + message);
        Serial.println("Old pwm_max var: " + String(pwm_max));
        Serial.println("Waiting...");
        SerialBT.println("menssage recived: " + message);
        SerialBT.println("Old pwm_max var: " + String(pwm_max));
        SerialBT.println("Waiting...");
      }

      do
      {
        message = String("");
        message = SerialBT.readStringUntil('\n');
        pwm_max = message.toFloat();
        if (debugger_func = String("true"))
        {
          Serial.println("LOOP");
          SerialBT.println("LOOP");
        }
        delay(1);
      } while (message == String(""));
      if (debugger_func = String("true"))
      {
        Serial.println("menssage recived: " + message);
        Serial.println("New pwm_max var: " + String(pwm_max));
        Serial.println("----------------------------");
        SerialBT.println("menssage recived: " + message);
        SerialBT.println("New pwm_max var: " + String(pwm_max));
        SerialBT.println("----------------------------");
      }
    }
    if (message == String("Vmin"))
    {
      if (debugger_func = String("true"))
      {
        Serial.println("menssage recived: " + message);
        Serial.println("Old pwm_min var: " + String(pwm_min));
        Serial.println("Waiting...");
        SerialBT.println("menssage recived: " + message);
        SerialBT.println("Old pwm_min var: " + String(pwm_min));
        SerialBT.println("Waiting...");
      }

      do
      {
        message = String("");
        message = SerialBT.readStringUntil('\n');
        pwm_min = message.toFloat();
        if (debugger_func = String("true"))
        {
          Serial.println("LOOP");
          SerialBT.println("LOOP");
        }
        delay(1);
      } while (message == String(""));
      if (debugger_func = String("true"))
      {
        Serial.println("menssage recived: " + message);
        Serial.println("New pwm_min var: " + String(pwm_min));
        Serial.println("----------------------------");
        SerialBT.println("menssage recived: " + message);
        SerialBT.println("New pwm_min var: " + String(pwm_min));
        SerialBT.println("----------------------------");
      }
    }
    if (message == String("Go"))
    {
      message = String("");
      if (debugger_func = String("true"))
      {
        Serial.println("menssage recived: " + message);
        Serial.println("Starting...");
      }

    }
    if (message == String("stop"))
    {
      message = String("");
      if (debugger_func = String("true"))
      {
        Serial.println("Stopping...");
      }
      contD = cont_max + 1;
    }
    if (message == String("debugger_on"))
    {
      message = String("");
      if (debugger_func = String("true"))
      {
        Serial.println("menssage recived: " + message);
        Serial.println("Old debugger var: " + String(debugger_func));
        Serial.println("Waiting...");
        SerialBT.println("menssage recived: " + message);
        SerialBT.println("Old debugger var: " + String(debugger_func));
        SerialBT.println("Waiting...");
      }
      debugger_func = String("true");
      if (debugger_func = String("true"))

      {
        Serial.println("menssage recived: " + message);
        Serial.println("New debugger var: " + String(debugger_func));
        Serial.println("----------------------------");
        SerialBT.println("menssage recived: " + message);
        SerialBT.println("New debugger var: " + String(debugger_func));
        SerialBT.println("----------------------------");
      }
    }
    if (message == String("debugger_off"))
    {
      message = String("");
      if (debugger_func = String("true"))
      {
        Serial.println("menssage recived: " + message);
        Serial.println("Old debugger var: " + String(debugger_func));
        Serial.println("Waiting...");
        SerialBT.println("menssage recived: " + message);
        SerialBT.println("Old debugger var: " + String(debugger_func));
        SerialBT.println("Waiting...");
      }
      debugger_func = String("false");
      if (debugger_func = String("true"))
      {
        Serial.println("menssage recived: " + message);
        Serial.println("New debugger var: " + String(debugger_func));
        Serial.println("----------------------------");
        SerialBT.println("menssage recived: " + message);
        SerialBT.println("New debugger var: " + String(debugger_func));
        SerialBT.println("----------------------------");
      }
    }
    if (message == String("contagem"))
    {
      if (debugger_func = String("true"))
      {
        Serial.println("menssage recived: " + message);
        Serial.println("Old contagem var: " + String(cont_max));
        Serial.println("Waiting...");
        SerialBT.println("menssage recived: " + message);
        SerialBT.println("Old contagem var: " + String(cont_max));
        SerialBT.println("Waiting...");
      }

      do
      {
        message = String("");
        message = SerialBT.readStringUntil('\n');
        cont_max = message.toInt();
        if (debugger_func = String("true"))
        {
          Serial.println("LOOP");
          SerialBT.println("LOOP");
        }
        delay(1);
      } while (message == String(""));
      if (debugger_func = String("true"))
      {
        Serial.println("menssage recived: " + message);
        Serial.println("New contagem var: " + String(cont_max));
        Serial.println("----------------------------");
        SerialBT.println("menssage recived: " + message);
        SerialBT.println("New contagem var: " + String(cont_max));
        SerialBT.println("----------------------------");
      }
    }

    delay(1);
    // fim do while 0
  }
}

void coreTaskOne(void *pvParameters) // CODIGO PRINCIPAL
{
  String taskMessage = "Código principal on core: ";
  taskMessage = taskMessage + xPortGetCoreID();
  Serial.println(taskMessage + "\n");
}
// Calibrar os sensores


