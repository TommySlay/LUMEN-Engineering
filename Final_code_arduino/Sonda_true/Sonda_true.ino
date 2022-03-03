/* https://github.com/sandeepmistry/arduino-LoRa
    https://microcontrollerslab.com/ttgo-lora32-sx1276-oled-board-pinout-getting-started-with-arduino-ide/
    https://lora.readthedocs.io/en/latest/#rssi
    večina serial prinotva je za debug i mogu se izbrisati
*/


/*
 * Potrebni libs:
 * 
 * https://github.com/sandeepmistry/arduino-LoRa - lora
 * https://github.com/adafruit/DHT-sensor-library - DHT
 * https://github.com/adafruit/Adafruit_BMP280_Library - BMP280
 * 
 */


// Libs za LoRa
#include <SPI.h>
#include <LoRa.h>

// Za BMP280 pressure senzor
#include <Wire.h>

#include <math.h>
#include "DHT.h"
#include <Adafruit_BMP280.h>

// Pin definitions
#include "Pin_definitions.h"

// Tablica temperatura za termistor
#include "Temperature_table.h"

// Dozvoljeni bandwidth za Europu 
#define BAND 866E6

// Ovo nećemo korisiti vjerovatno samo iskomentiramo serial debug
#define DEBUG_SERIAL 1 // 1 is if we have debug 0 is if we dont have it 

/* BMP280 */
#define razlika 14.03                           // Kompenzacija između stvarne
                                                //i izmjerene vrijednosti (hPa)
/* BMP280 */
Adafruit_BMP280 bmp;                            // I2C sucelje

DHT dht(DHTPIN, DHTTYPE);

byte Adr_sonda = 0xAA; //  Adresa ovog uređaja (Sonde) 
byte Adr_rec = 0xBB; // Adresa receivera

int send_interval = 2000; //  Interval slanja podataka u ms 
byte Sonda_mode = 1;
byte force_send_data = 0; // Ako je jedan poslat će odma podatke 
long prev_time = 0;

void setup() {
  
  Serial.begin(9600);
  Serial.println("Begin...");
  /* LM393 */
  pinMode(Vcc_lm, OUTPUT);
  digitalWrite(Vcc_lm, LOW);//ugasi senzor
   /* DHT11 */
  dht.begin();
  //SPI LoRa pins
  SPI.begin(SCK, MISO, MOSI, SS);
  //setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(BAND)) {
    Serial.println("LoRa failed.");
    while (1) {}
  }

  if (!bmp.begin(0x76)) {
    Serial.println(F("Senzor nije prepoznat, provjeri i2c sucelje"));
    //while (1) delay(10);
    delay(10);
  }

    /* Default postavke iz datasheet-a. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     // Mode rada 
                  Adafruit_BMP280::SAMPLING_X2,     
                  Adafruit_BMP280::SAMPLING_X16,    // Oversampling tlaka
                  Adafruit_BMP280::FILTER_X16,      // Filtriranje 
                  Adafruit_BMP280::STANDBY_MS_500); // Vrijeme u standby-u 

  
}

/* Svakih send_interval vremena pošaljem podatake
    Nakon što sam poslao podatke onda odlazi u receive mode
    U receive mode može dobiti par naredbi
    1. Promijeni mode rada sonde ???
    2. Promijeni interval slanja podataka
    3. Forsiraj slanje podataka
*/
void loop() {
  if (millis() - prev_time > send_interval) {

    // Tu se prikupe svi podaci od senzora i bace se umjesto ovih dummy podataka 10,20,30...
    // Zasad sam stavio adresu na koju šaljem i samo 7 podataka da se šalje al možemo dodat lagano još ak nam treba
    
    int foto = izmjeri_jacinu_svijetlosti();
    int vlaga_tla = izmjeri_vlagu_tla();
    int temp_tla =  Get_temperature();
    int tlak = izmjeri_tlak();
    int vlaga_zraka = izmjeri_vlagu_zraka();
    int temp_zraka = izmjeri_temperaturu_zraka();
    int bat = get_battery_voltage();
    send_data(Adr_rec, temp_zraka, temp_tla, vlaga_zraka, vlaga_tla, tlak, foto, bat);
    //Serial.println("Ja sam sonda i poslao sam 10,20,30... na adresu: " + String(Adr_rec, HEX));
    prev_time = millis();

  }

  // Kada primi naredbu da pošalje podatke instantly
  if (force_send_data == 1) {
    
    int foto = izmjeri_jacinu_svijetlosti();
    int vlaga_tla = izmjeri_vlagu_tla();
    int temp_tla =  Get_temperature();
    int tlak = izmjeri_tlak();
    int vlaga_zraka = izmjeri_vlagu_zraka();
    int temp_zraka = izmjeri_temperaturu_zraka();
    int bat = get_battery_voltage();
    send_data(Adr_rec, temp_zraka, temp_tla, vlaga_zraka, vlaga_tla, tlak, foto, bat);
    force_send_data = 0;
  }

  got_data(LoRa.parsePacket());
}
