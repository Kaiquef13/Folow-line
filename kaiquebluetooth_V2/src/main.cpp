#include <Arduino.h>
#include <Itamotorino.h> // Convertida pra ESP

#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void coreTaskZero();
void coreTaskOne();

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
      1,              /* prioridade da tarefa (0 a N) */
      NULL,           /* referência para a tarefa (pode ser NULL) */
      0);             /* Núcleo que executará a tarefa */

  xTaskCreatePinnedToCore(
      coreTaskOne,   /* função que implementa a tarefa */
      "coreTaskOne", /* nome da tarefa */
      10000,         /* número de palavras a serem alocadas para uso com a pilha da tarefa */
      NULL,          /* parâmetro de entrada para a tarefa (pode ser NULL) */
      2,             /* prioridade da tarefa (0 a N) */
      NULL,          /* referência para a tarefa (pode ser NULL) */
      1);            /* Núcleo que executará a tarefa */
}



void coreTaskZero(void *pvParameters) // BLUTU
{
  String taskMessage = "Bluetooth on core: ";
  taskMessage = taskMessage + xPortGetCoreID();
  Serial.println(taskMessage + "\n");
  while (true)
  {
    if (SerialBT.available())
    {
      String incomingChar = SerialBT.readStringUntil('\n');
      Serial.println(incomingChar);
      Serial.println("");
      delay(10);
    }
    delay(1);
  }
}




void coreTaskOne(void *pvParameters) // CODIGO PRINCIPAL
{
  String taskMessage = "Código principal on core: ";
  taskMessage = taskMessage + xPortGetCoreID();
  Serial.println(taskMessage + "\n");
  while (true)
  {
  }
}

// LOOP
void loop()
{
}
