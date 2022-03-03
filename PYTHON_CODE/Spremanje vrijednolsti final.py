import datetime
import time
from datetime import date
import serial
import csv

x_vrijeme = 1
y_senzor1 = 1
y_senzor2 = 1
y_senzor3 = 1
y_senzor4 = 1
y_senzor5 = 1
y_senzor6 = 1

fieldnames = ["x_vrijeme", "y_senzor1", "y_senzor2","y_senzor3","y_senzor4","y_senzor5","y_senzor6"]

with open('data_test.csv', 'w') as csv_file:
    csv_writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
    csv_writer.writeheader()

arduinoData = serial.Serial('COM3',9600)

i = 0

today = date.today()  # daje nam točan datum
minute = datetime.datetime.now().minute  # daje nam minute
# pretvara minute iz integer u string kako bi po njoj mogli nazvati file s promjenom minute
minutestr = str(minute)

# ddmmYY
# daje nam oblik u kojem se ispisuje datum npr. "22052021" -> 22.05.2021.
d1 = today.strftime("%d%m%Y")
# daje nam samo 3. i 4. znak u stringu jer se gleda broj između znakova 0A1B2C3D4, ABCD bi ispisao CD
mjesec = d1[2:4]
godina = d1[4:]  # ispisuje od 4. znaka pa nadalje

mjesec1 = mjesec  # pretvara mjesec u drugu varijablu kako bi mogli pratiti promjenu stanja
godina1 = godina
minute1 = minute

# otvara file pod imenom godine+Average.txt "2021Average" i overwritea sve sta je u njemu
with open(godina+'Average.txt', 'w') as a:
    a.write('Mjesec, Tempz, Tempt, Vlagaz, Vlagat, Tlak, Svjetlost\n')

while True:



            today = date.today()
            minute = datetime.datetime.now().minute
            d1 = today.strftime("%d%m%Y")
            mjesec = d1[2:4]
            godina = d1[4:]

            # varijable za izracunavanje srednje vrijednosti
            atz = 0
            avz = 0
            asvj = 0
            att = 0
            avt = 0
            at = 0

            # varijable za izračunavanje zbroja za srednje vrijednosti
            ztz = 0
            zvz = 0
            zsvj = 0
            ztt = 0
            zvt = 0
            zt = 0
            i = 1

            minute1 = minute

            if godina != godina:  # pracenje promjene mjeseca sa uvijetom da se otvori novi file
                # otvara file pod imenom godine+Average.txt "2021Average" i overwritea sve sta je u njemu
                with open(godina + 'Average.txt', 'w') as a:
                    a.write('Mjesec, Tempz, Tempt, Vlagaz, Vlagat, Tlak, Svjetlost\n')

            godina1 = godina  # praćenje promjene mjeseca

            # otvaranje i overwriteanje filea. umjesto "minutestr" stavljamo mjesec
            with open(minutestr + '_' + godina + '.txt', 'w') as f:
                f.write('Tempz, Tempt, Vlagaz, Vlagat, Tlak, Svjetlost\n')

            while minute == minute1:  # petlja se vrti sve dok se minuta ne promjeni, inače bi trebao biti mjesec umjesto minuta

                while (arduinoData.inWaiting() == 0):  # čekaj dok se ne pojavi vrijednost
                    pass  # čekaj dok se ne pojavi vrijednost
                    with open('data_test.csv', 'a') as csv_file:
                        csv_writer = csv.DictWriter(csv_file, fieldnames=fieldnames)

                        arduinoString = arduinoData.readline()  # pričitaj tekst iz serial porta
                        dataArray = arduinoString.decode().split(",")  # razdvoji tekst

                        dt = datetime.datetime.now().replace(microsecond=0)
                        x_vrijeme = dt.time()
                        y_senzor55 = ((y_senzor5 * (1084 - 870) / 255)) + 870

                        info = {

                            "x_vrijeme": x_vrijeme,
                            "y_senzor1": y_senzor1,
                            "y_senzor2": y_senzor2,
                            "y_senzor3": y_senzor3,
                            "y_senzor4": y_senzor4,
                            "y_senzor5": y_senzor55,
                            "y_senzor6": y_senzor6
                        }

                        csv_writer.writerow(info)
                        print(x_vrijeme, y_senzor1, y_senzor2, y_senzor3, y_senzor4, y_senzor55, y_senzor6)

                        y_senzor1 = float(dataArray[0])  # pretvori str u float
                        y_senzor2 = float(dataArray[1])
                        y_senzor3 = float(dataArray[2])
                        y_senzor4 = float(dataArray[3])
                        y_senzor5 = float(dataArray[4])
                        y_senzor6 = float(dataArray[5])

                        tempz = y_senzor1  # °C
                        tempt = y_senzor2  # %
                        vlagz = y_senzor3  # %
                        vlagt = y_senzor4  # °C
                        tlak = y_senzor55  # %
                        svj = y_senzor6  # hPa




                    today = date.today()
                    minute = datetime.datetime.now().minute
                    minutestr = str(minute)
                    # ddmmYY
                    d1 = today.strftime("%d%m%Y")
                    print("d1 =", d1)

                    mjesec = d1[2:4]
                    godina = d1[4:]
                    print(mjesec)  # ispisivanje mjeseca radi praćenja vrijednosti
                    print(godina)  # ispisivanje godina
                    print(minute)  # ispisivanje minuta
                    print(minute1)

                    # otvaranje filea i dodavanje retka sa pripadajućim vrijednostima
                    with open(minutestr + '_' + godina + '.txt', 'a') as f:
                        f.write('{}, {}, {}, {}, {}, {}\n'.format(round(tempz), round(tempt), round(vlagz), round(vlagt),
                                                                  round(tlak), round(svj)))

                    # spremanje novih vrijednosti
                    ztz += tempz
                    zvz += vlagz
                    zsvj += svj
                    ztt += tempt
                    zvt += vlagt
                    zt += tlak

                    # izracunavanje srednje vrijednosti za sve senzore kroz cijeli tekući mjesec
                    atz = ztz / i
                    avz = zvz / i
                    asvj = zsvj / i
                    att = ztt / i
                    avt = zvt / i
                    at = zt / i
                    i += 1

                    if minute1 != minute:  # inače bi bilo "if mjesec1 != mjesec" jer se mijenja kako se mijenja mjesec
                        # dodavanje vrijednosti u sljedecem formatu
                        with open(godina + 'Average.txt', 'a') as a:
                            a.write(
                                '{}, {}, {}, {}, {}, {}, {}\n'.format(mjesec, round(atz), round(att), round(avz), round(avt),
                                                                      round(at), round(asvj)))
                    # pracenje promjene minute da ne bi morali pratiti mjesec dana nego recimo 5 min
                    if minute1 != minute:
                        break
                    minute1 = minute