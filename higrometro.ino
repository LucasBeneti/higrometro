#include <stdio.h>
#include <stdlib.h>
#include "SSD1306Wire.h"

#include "DHT.h"

#define DHTPIN 13 // D7 na placa
#define DHTTYPE DHT22
/*
Por algum motivo, ao desconectar a placa do PC e conectar novamente, parece que o código gravado nela
é perdido. Como se a cada perdade energia, ela perdesse o firmware dela. *verificar se não está setada
para bootloader mode ou algo do gênero.
*/

// Created by http://oleddisplay.squix.ch/ Consider a donation
// In case of problems make sure that you are using the font file with the correct version!

DHT dht(DHTPIN, DHTTYPE);

// conexão de display(address, SDA, SCL)
SSD1306Wire display(0x3c, D3, D4);

void setup() {
  Serial.begin(9600);
  
  Serial.print(F("DHT22 Teste !!!!!!"));
  dht.begin();
  pinMode(LED_BUILTIN, OUTPUT);
//  digitalWrite(LED_BUILTIN, HIGH);
//    delay(500);
//    digitalWrite(LED_BUILTIN, LOW);
//    delay(500);
//  for (int i=0; i <= 1; i++) {
//    digitalWrite(LED_BUILTIN, HIGH);
//    delay(500);
//    digitalWrite(LED_BUILTIN, LOW);
//    delay(500);
//  }
  delay(2000);
  display.init();
  
//  if (!display.init()) {
//    showError();
//  }
  display.clear();
//  display.flipScreenVertically();
  display.setFont(Roboto_Medium_24);
  
}

void showError() {
  for (int i=0; i < 20; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
  }
}

void loop() {
  delay(2000);
  char buffer[sizeof(unsigned int)*16+1];
//  display.init();
  display.clear();
  // put your main code here, to run repeatedly:
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(Roboto_Medium_24);
  display.drawString(60, 5,"Temp: 25*");
//  display.setFont(Roboto_Medium_24);
//  display.drawString(10, 26,"Humi: 55%");
  display.setFont(Roboto_Medium_24);
  utoa(display.getWidth(), buffer, 10);
  display.drawString(20, 30, buffer);

  display.display();
  /* medicoes do DHT22 */
  float h = dht.readHumidity();
  float c = dht.readTemperature();

  if (isnan(h) || isnan(c)) {
    Serial.println(F("Erro na medida do sensor..."));
  }
  float hic = dht.computeHeatIndex(c, h, false);
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(c);
  Serial.print(F("°C "));
  
//  delay(2000);
}
