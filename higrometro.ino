#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SSD1306Wire.h"

#include "DHT.h"

#define DHTPIN 13 // D7 na placa
#define DHTTYPE DHT22
/*
Por algum motivo, ao desconectar a placa do PC e conectar novamente, parece que o código gravado nela
é perdido. Como se a cada perdade energia, ela perdesse o firmware dela. *verificar se não está setada
para bootloader mode ou algo do gênero.

RESPOSTA;
É algum bug da tela oled, da biblioteca do driver, algo assim...Foi resolvido colocando um delay de no
mínimo 2 segundos antes do display.init(). Após esse delay a tela consegue ser inicializar no reboot do sistema.
*/

// Created by http://oleddisplay.squix.ch/ Consider a donation
// In case of problems make sure that you are using the font file with the correct version!

DHT dht(DHTPIN, DHTTYPE);

// conexão de display(address, SDA, SCL)
SSD1306Wire display(0x3c, D3, D4);

void setup() {
  Serial.begin(115200);
  
  Serial.print(F("DHT22 Teste !!!!!!"));
  dht.begin();
  pinMode(LED_BUILTIN, OUTPUT);
  delay(2000);
  display.init();
  display.clear();
//  display.flipScreenVertically();  
}

// params: float value of sensor, char grandeza 't' or 'h'
void display_value(float value, char grandeza) {
  display.clear();
  char value_str[10];
  gcvt(value, 5, value_str);
  if (grandeza == 't') {
    strcat(value_str, "°C");  
  } else if (grandeza == 'h') {
    strcat(value_str, "%");
  }
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(Creepster_Caps_Regular_54);
  display.drawString(0, 0,value_str);
  display.display();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  display_value(t, 't');
  delay(2500);
  display_value(h, 'h');
  delay(2500);
//  Useful while debugging
//  Serial.print(F("Humidity: "));
//  Serial.print(h);
//  Serial.print(F("%  Temperature: "));
//  Serial.print(t);
//  Serial.print(F("°C "));
//  Serial.print(F("\n"));

}
