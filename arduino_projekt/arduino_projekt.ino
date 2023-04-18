//pliki nagłówkowe używane przez LINX
#include <SPI.h>
#include <Wire.h>
#include <EEPROM.h>
#include <Servo.h>
#include <dht.h>
#include <LinxArduinoUno.h>
#include <LinxSerialListener.h>

dht pomiar;  //zmienna typu dht

#define DHT11_PIN 2 

//Utworzenie wskaźnika do obiektu typu LINX który tworzymy w Setup()
LinxArduinoUno* LinxDevice;

int DHT();

void setup() {
  //Inicjalizacja obiektu LINX
  LinxDevice = new LinxArduinoUno();

  //Stworzenie połączenia między układem a LINX
  LinxSerialConnection.Start(LinxDevice, 0);
  LinxSerialConnection.AttachCustomCommand(0, DHT); //dołączenie stworznej funkcji DHT
}

void loop() {
  //oczekiwanie na dane z LabVIEW
  LinxSerialConnection.CheckForCommands();

 
}
//stworzenie własnej funkcji
int DHT(unsigned char numInputBytes, unsigned char* input, unsigned char* numResponseBytes, unsigned char* response) {
  pomiar.read11(DHT11_PIN); //odczyt danych z Pinu 2
  response[0] = (unsigned char)pomiar.humidity; //wartość wilgotności
  response[1] = (unsigned char)pomiar.temperature; // wartość temperatury
  *numResponseBytes = 2;

  delay(500);
}
