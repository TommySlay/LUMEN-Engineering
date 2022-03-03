/* https://github.com/sandeepmistry/arduino-LoRa
    https://microcontrollerslab.com/ttgo-lora32-sx1276-oled-board-pinout-getting-started-with-arduino-ide/
    https://lora.readthedocs.io/en/latest/#rssi

*/


// For LoRa
#include <SPI.h>
#include <LoRa.h>

// For OLED display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Pin definitions
#include "Pin_definitions.h"

int Vanjska_vlaga = 0;
int Tlo_vlaga = 0;
int Vanjska_temperatura = 0;
int Tlo_temperatura = 0;
int Tlak_zrak = 0;
int Jacina_sunca = 0;
int Stanje_baterije = 0;

// Allowed band for Europe
#define BAND 866E6

// Init display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

byte Adr_sonda = 0xAA; // Address of reciver
byte Adr_rec = 0xBB; // Address of this device

long prev_time = 0;
int count = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Begin...");

  //reset OLED display
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(20);
  digitalWrite(OLED_RST, HIGH);

  //initialize OLED
  Wire.begin(OLED_SDA, OLED_SCL);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); 
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("LORA REC");
  display.display();

  // Sa ovim "ugasiš" display
  //delay(1000);
  //display.clearDisplay();
  //display.display();

  //SPI LoRa pins
  SPI.begin(SCK, MISO, MOSI, SS);
  //setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(BAND)) {
    Serial.println("LoRa failed.");
    while (1) {}
  }
}

void loop() {

  Read_Serial_and_Send();

  got_data(LoRa.parsePacket());
}
