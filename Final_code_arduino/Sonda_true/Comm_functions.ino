

 // Podaci se šalju ovim redosljedom
/*
   1. Adresa primatelja
   2. temperatura vanjska
   3. temperatura tla
   4. vlaga vanjska
   5. vlaga tla
   6. tlak vanjski
   7. jačina svijetla
   8. napunjenost baterije
*/

void send_data(byte adrs, int16_t s1, int16_t s2, int16_t s3, int16_t s4, int16_t s5, int16_t s6, int16_t s7) {
  LoRa.beginPacket();

  LoRa.write(adrs);
  LoRa.write(s1);
  LoRa.write(s2);
  LoRa.write(s3);
  LoRa.write(s4);
  LoRa.write(s5);
  LoRa.write(s6);
  LoRa.write(s7);
  // Error check var ????

  LoRa.endPacket();
}


/* Ovdje sonda prima podatke od receivera 
 *  Ako je kriva adresa receivera onda nemoj ništa raditi 
 *  ako je ok onda radi nešto od ovog: 
 *  1. Promijeni mode rada sonde ???
 *  2. Promijeni interval slanja podataka
 *  3. Forsiraj slanje podataka
 */


 // ako želimo promijeniti postavke šaljemo:
 // Primjer: adresa sonde je 0xAA to je dec 170
 // 170,1,1,2,
 // 170 je adreasa drugi broj je mode treci je force send i cetvrti je interval u min
void got_data(int packetSize) {
  if (packetSize == 0) return;

  int  r_adrs = LoRa.read();
  int r1 = LoRa.read();
  int r2 = LoRa.read();
  int r3 = LoRa.read();

  // Ako je primljena adresa kriva, znači ako je različita od AA onda radi ništa

  if (r_adrs != Adr_sonda) {
    Serial.println("Got data from address" + String(r_adrs, HEX) + "   " + String(r_adrs, DEC) + "ERROR!!") ;
    return;
    // Ako je adresa dobra onda spremi podatke
  } else {
    send_interval = r3 * 60000; // Sending interval // u svrhe testiranja je zasad u sekundama inače SVE U MINUTE !!!
    Sonda_mode = r1;
    force_send_data = r2;
  }

  // Serial.println("Got Data from adr" + String(r_adrs, HEX));
  // Serial.println("Data1 from rec: " + String(r1));
  // Serial.println("Data2 from rec: " + String(r2));
  // Serial.println("Data2 from rec: " + String(r3));



}
