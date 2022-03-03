
// otpor od 10kohm u seriji
int izmjeri_jacinu_svijetlosti(){
  /* Fotootpotnik */
  /* Mjerenje jacine svjetlosti u postotcima */
  
  int value_12 = analogRead(LDRPIN);            // 0-4095
  /* Pretvaranje iz 12- bitne vrijednosti u postotak koji kasnije
       treba pomnožiti s mjernim rasponom/100 (30 000/100) */
  float udio = (float)value_12/4095.0;
  int postotak_svjetlosti = udio * 100;
  
  //Serial.print("postotak svjetlosti:");
  // Serial.print(postotak_svjetlosti);            // Vrijednosti od 0-100
  //Serial.println(" %");
  
  return postotak_svjetlosti;                   // Vrijednosti od 0-100
}



int izmjeri_vlagu_tla(){
  /* LM393 */
  /* Mjerenje vlage tla u postotcima */
  
  digitalWrite(Vcc_lm, HIGH);                   // Upali senzor
  delay(100);
  
  unsigned int vlaga_tla = analogRead(lm393_raw); // Ocitaj vrijednost senzora
  //Serial.println(vlaga_tla);
  
  digitalWrite(Vcc_lm, LOW);                    // Ugasi senzor
  /*ocitanje = map(ocitanje, voda, zrak,100%,0%)  */
  vlaga_tla = map(vlaga_tla, 700, 4095, 100, 0); // Pretvori u postotak
  vlaga_tla = constrain(vlaga_tla, 0, 100);     // Vraća vlagu tla, 0 ili 100
                                                // 0 = vlaga tla < 3200
                                                // 100 = vlaga tla >= 4095
  //Serial.print("Postotak vlage = ");
  //Serial.print(vlaga_tla);                      // Vrijednosti od 0-100
  //Serial.println("%");
  
  return vlaga_tla;                             // Vrijednosti od 0-100

}

// Najveći tlak ikad 1084
// Prosjek tlaka 1013.25
// Najmanji tlak (van tornada) 870
// uzimam da je min vrijednost ikad 870 i max 1084 i to se skalira od 0-255

int izmjeri_tlak(){
  /* BMP280 */

 
  float tlak_raw = bmp.readPressure();          // 100357 Pa
  float tlak_hpa = (int)(tlak_raw /100) + razlika;   // 1017.87 hPa
  tlak_hpa = round(tlak_hpa);                   // 1018
  int tlak_byte = map(tlak_hpa, 870, 1084 , 0, 255);
  return tlak_byte;
    //Serial.print("Tlak zraka: ");
    //Serial.print(tlak_hpa);         
    //Serial.println(" hPa ");           
    //Serial.print("Tlak zraka: ");
    //Serial.print(tlak_byte);         
    //Serial.println(" bytes");         
  

}

/* DEKLARACIJA POTREBNIH FUNKCIJA */
/* Parametri zraka */

int izmjeri_temperaturu_zraka() {
  /* DHT11 */
  /* Mjerenje temperature zraka u CELZIJUSIMA - preciznost od 1*C */
  /* senzor je spor - očitavanja mogu kasniti 2 sekunde */
       
  float t = dht.readTemperature();              //25.6
  int temp_zraka = round(t) ;                   //26
    
  //Serial.print("Temperatura zraka: ");
  //Serial.print(temp_zraka);                     // Temperatura u *C 
  //Serial.println(" *C\t ");
  
  return temp_zraka;                            // Temperatura u *C 
}

int izmjeri_vlagu_zraka() {
  /* DHT11 */
  /* Mjerenje vlage zraka u postotcima - preciznost od 1 % */
  /* Senzor je spor - očitavanja mogu kasniti 2 sekunde */
       
  float h = dht.readHumidity();                 //45.00
  int vlaga_zraka = h;                          //45
  
  //Serial.print("Vlaga zraka: ");
  //Serial.print(vlaga_zraka);
  //Serial.println(" %\t");
  
  return vlaga_zraka;                           // Vrijednosti od 0-100
}


/*****************************************************************************
  Dobivamo temperaturu tla pomoću termistora koji je u seriji sa 51kohm otporom
  Jedna noga termistora na 3v3 druga na pin i otpor od 51kohm te druga noga otpora na gnd
  Get voltage on thermistor that is in series with 51kohm resistor
  Then by using this code: https://github.com/PCrnjak/Thermistor-table-generator-using-Steinhart-Hart-equation
  We got lookup table that connects value from analog read to temperature
******************************************************************************/
int Get_temperature() {

  int16_t raw = analogRead(therm_pin);
  int16_t T_ = map(raw, 0, 4095, 0, 1023); // Downscale our 12 bit ADC to 10 bit since our lookup table is 10 bit
  //Serial.print("Temperatura tla: ");
  //Serial.print(Temp_table[T_]);                       // Temperatura u *C 
  //Serial.println(" C");
  return Temp_table[T_];

}


// Dohvati napon na bateriji
// 0 = 0V, 44 = 4.4 V
int get_battery_voltage(){

int16_t raw = analogRead(baterija);
int16_t V_ = map(raw, 0, 4095, 0, 44);
return V_;  
}
