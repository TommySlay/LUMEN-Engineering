// Pin definitions for LoRa
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26

/* DHT11 */
#define DHTPIN 13                               //DHT11
#define DHTTYPE DHT11

/* Fotootpotnik */
#define LDRPIN  34                              // AnalogIn

/* LM393 - vlaga*/
#define Vcc_lm 32                               // DigitalOut
#define lm393_raw 39                            // AnalogIn  

/* NTC Termistor */
#define therm_pin 35                            // AnalogIn

#define baterija 36

//OLED pins
#define OLED_SDA 4
#define OLED_SCL 15
#define OLED_RST 16
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
