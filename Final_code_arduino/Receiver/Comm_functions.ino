
/* Receiver prima podatke ovako po ovom dolje redu! */
/* Prvi podatak koji se prima je adresa sonde koju i receiver zna
 *  Ako je ona kriva javlja error i neće slati podtake prema serialu
 *  Ako je adresa dobra receiver šalje podtake dalje na serial u 
 *  formatu gdje su podaci razdvojeni sa zarezima!
 *  Podaci se šalju po istom ovom redosljedu dolje!
 *  Primjer 10,20,30,40,50,60,70\n 
 *  Znamo da je poslan zadnji podatak pomoću '\n'
 *  Podaci mogu biti max veličine byte, to je napravljeno zbog više razloga
 *  1. jednostavnost
 *  2. Lora ima mali bandwidth
 */
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

void got_data(int packetSize) {
  if (packetSize == 0) return;

  int r_adrs = LoRa.read();
  int r1 = LoRa.read();
  int r2 = LoRa.read();
  int r3 = LoRa.read();
  int r4 = LoRa.read();
  int r5 = LoRa.read();
  int r6 = LoRa.read();
  int r7 = LoRa.read();


  // Ako je adresa kriva izbaci ovaj error!
  if (r_adrs != Adr_rec) {
    Serial.println("Error: Recipient address does not match local address");
    return;
    // Ako je adresa dobra onda spremi ove podatke!
  } else {

    Vanjska_temperatura = r1;
    Tlo_temperatura = r2;
    Vanjska_vlaga = r3;
    Tlo_vlaga = r4;
    Tlak_zrak = r5;
    Jacina_sunca = r6;
    Stanje_baterije = r7;
    
    Serial.print(Vanjska_temperatura);
    Serial.print(",");
    Serial.print(Tlo_temperatura);
    Serial.print(",");
    Serial.print(Vanjska_vlaga);
    Serial.print(",");
    Serial.print(Tlo_vlaga);
    Serial.print(",");
    Serial.print(Tlak_zrak);
    Serial.print(",");
    Serial.print(Jacina_sunca);
    //Serial.print(",");
    //Serial.print(Stanje_baterije);
    Serial.print("\n");
    


  }

  //Serial.println("Got Data from adr" + String(r_adrs, HEX));
  //Serial.println("---------------New data---------------");
  //Serial.println("Data1 from sonda: " + String(r1));
  //Serial.println("Data2 from sonda: " + String(r2));
  //Serial.println("Data3 from sonda: " + String(r3));
  //Serial.println("Data4 from sonda: " + String(r4));
  //Serial.println("Data5 from sonda: " + String(r5));
  //Serial.println("Data6 from sonda: " + String(r6));
  //Serial.println("Data6 from sonda: " + String(r7));

}

/* Čita serial port */

void Read_Serial_and_Send() {

  if (Serial.available() > 0) {

    String d1  = Serial.readStringUntil(','); // adresa primatelja
    Serial.read(); // ovo skipa zarez
    String d2 = Serial.readStringUntil(','); // mode sonde
    Serial.read();
    String d3 = Serial.readStringUntil(','); // zahtjev da pošalje
    Serial.read();
    String d4 = Serial.readStringUntil('\n'); // Send interval u min
    Serial.read();

    int I1 = d1.toInt();
    int I2 = d2.toInt();
    int I3 = d3.toInt();
    int I4 = d4.toInt();

    if ( I1 == Adr_sonda) {
      LoRa.beginPacket();
      LoRa.write(I1);
      LoRa.write(I2);
      LoRa.write(I3);
      LoRa.write(I4);

      LoRa.endPacket();
    } else {
      
      //Serial.print("Ops wrong address");
    }
  }

}

// ne koristi se
void show_data_on_display() {

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("LORA Rec");
  display.setCursor(0, 20);
  display.setTextSize(1);
  display.print("LoRa packet sent.");
  display.setCursor(0, 30);
  display.print("counter: ");
  display.setCursor(80, 30);
  display.print("holder");
  display.setCursor(10, 40);
  display.print("holder");
  display.display();

}
