#include <OneWire.h>
#include <DallasTemperature.h>

OneWire ourWire(30);                //Se establece el pin 2  como bus OneWire

DallasTemperature sensors(&ourWire); //Se declara una variable u objeto para nuestro sensor
int Mq2;
int MQ135;
int lectura;
const int pin = 2;

void setup() {0
  delay(1000);
  Serial.begin(9600);
  sensors.begin();   //Se inicia el sensor
  Serial.begin(9600);
  Serial.begin(9600);
  Serial.begin(9600);
  pinMode(pin, OUTPUT);
}

void loop() {
  //TEMPERATURA
  //temp,metano,adc,voltaje,Rs,amoniaco,ppm,humedad
  sensors.requestTemperatures();   //Se envía el comando para leer la temperatura
  float temp = sensors.getTempCByIndex(0); //Se obtiene la temperatura en ºC
  Serial.print(temp);
  Serial.print(String(","));

  //MQ2 METANO
  int adc_MQ2 = analogRead(A0); //Lemos la salida analógica  del MQ
  float voltaje_MQ2 = adc_MQ2 * (4.34 / 1023.0); //Convertimos la lectura en un valor de voltaje
  float Rs_MQ2 = 10 * ((4.34 - voltaje_MQ2) / voltaje_MQ2); //Calculamos Rs con un RL de 1k
  float CH4 = 24.411 * pow(Rs_MQ2 / 11.1109091, -0.382); // calculamos la concentración  de CH4 con la ecuación obtenida.
  //-------Enviamos los valores por el puerto serial------------

  //metano, ppm
  Serial.print(CH4 / 1000, 4);


  //MQ135 AMONIACO
  int adc_MQ135 = analogRead(A2); //Leemos la salida analógica  del MQ
  float voltaje_MQ135 = adc_MQ135 * (5 / 1023.0); //Convertimos la lectura en un valor de voltaje
  float Rs_MQ135 = 10 * ((5 - voltaje_MQ135) / voltaje_MQ135); //Calculamos Rs con un RL de 10k
  float O3 = 6.4014 * pow(Rs_MQ135 / 16.8993333, -0.402); // calculamos la concentración  de NH3 con la ecuación obtenida.
  //-------Enviamos los valores por el puerto serial------------
  Serial.print(String(","));
   // amoniaco, ppm
  Serial.print(O3 / 1000, 4);
  Serial.print(String(","));


  //HUMEDAD FC-28
  int lectura = analogRead(A4);
  //humedad
 /* Serial.print(lectura);
  Serial.print(String(","));*/
  //Rango de lecturas 1000 - 1023


  //Convertir a lectura de porcentaje de humedad
  int lecturaPorcentaje = map(lectura, 0, 1023, 100, 0);
  Serial.print(lecturaPorcentaje);
  Serial.println(String(","));
  delay(2000);


}
