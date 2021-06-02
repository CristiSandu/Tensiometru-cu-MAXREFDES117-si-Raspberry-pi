# Tensiometru cu MAXREFDES117# si Raspberry-pi

## Introducere

Un sistem care **masoara tensiunea si saturatioa de O2** si
**salveaza logul pe un card microSD** (data si ora la care sa masurat alaturi de SPO2 si tensiune) pentru parsare ulterioara.
alaturi de trimiterea in timp real prin serial catre un Raspberry pi w 0 pentru afisarea unui grafic folosind matplotlib.pyplot. Rezultatele sunt **afisate in timp real** pe un display OLED, iar pe un display de nokia 3310 se afiseaza un grafic minimalist  
Scopul proiectului este de a tine un jurnal al pulsului astfel putandu-se observa evolutia in starea de sanatate sau pur si simplu un o idee asupra tensiunii unei persoane.  
Initial voiam sa fac ceva simplu, dar m-am gandit sa ma extind tinand cont ca am un Arduino Mega la dispozitie.
Proiectul poate fi util din mai multe puncte de vedere, pentru persoanele mai in varsta pot sa isi ia pulsul si sa vada graficul in timp real cat de mare isi doresc (depinzand de dimensiunea monitoruui/televizorului), iar o data pe luna/an pot sa vada cum a evoluat pulsul lor folosind script-ul pus la dispozitie pe datele de pe SD.

## Software Design

Medii Dezvoltare:

- Arduino IDE (pentru proiectul principal)
- PyCharm (pentru scriptul de parsare date SD)
- Visual Studio Code (pentru scriptul de afisare a datelor in timp real pe Raspberry pi)

Biblioteci folosite:

- Wire.h
- SPI.h
- DS1302.h
- SD.h
- PCD8544.h
- algorithm_by_RF.h
- max30102.h
- U8glib.h
- Arduino.h

#### **Pe Arduino**

Programul functioneaza astfel: Pana nu se introduce de la tastatura un caracter masuratoarea nu incepe. Se colecteaza datele intr-un for de la 1 la 100 astfel obtinandu-se o valoare cat mai aproape de realitate. Daca rezultatul obtinut dupa este valid conform algoritmului se trimit datele prin serial la Pi, spre SD card alaturi de data si ora la care s-au inregistrat(aici apare un delay de max 2s), si datele spre ecrane ca sa se afiseze. La inceput se verifica si daca exista un SD card returnand o eroare in caz contrar.

#### **Pe Pi**

Datele se primesc una pe un rand despartite de un caracter, astfel putand sa se faca distinctia intre HR si SPO2. Dupa se ploteaza rezultatul cu ajutorul biblioteci matplotlib.pyplot.

#### **Pe partea de parsare SD**

Aici intervine o parsare simpla de text.

Ca si algoritmi folositi am ales sa raman la algoritmul oferit de producatorul senzorului (varianta originala nu era compatibia cu MEGA) usor modificat gasit [aici](https://github.com/aromring/MAX30102_by_RF). Acest algoritm calculeaza HR si SPO2 folosind datele de la senzor.

## Rezultate

|                                                                                                                                 |                                                                                                                                 |
| :------------------------------------------------------------------------------------------------------------------------------ | :------------------------------------------------------------------------------------------------------------------------------ |
| ![](https://github.com/CristiSandu/Tensiometru-cu-MAXREFDES117-si-Raspberry-pi/blob/main/images/TensiometruRezultateSIC701.jpg) | ![](https://github.com/CristiSandu/Tensiometru-cu-MAXREFDES117-si-Raspberry-pi/blob/main/images/TensiometruRezultateSIC142.jpg) |
| ![](https://github.com/CristiSandu/Tensiometru-cu-MAXREFDES117-si-Raspberry-pi/blob/main/images/hrSDPlot.jpg)                   | ![](https://github.com/CristiSandu/Tensiometru-cu-MAXREFDES117-si-Raspberry-pi/blob/main/images/spo2SDPlot.jpg)                 |
| ![](https://github.com/CristiSandu/Tensiometru-cu-MAXREFDES117-si-Raspberry-pi/blob/main/images/outputSDDemoVideo.jpg)          | ![](https://github.com/CristiSandu/Tensiometru-cu-MAXREFDES117-si-Raspberry-pi/blob/main/images/testVideoDemo.png)              |

## Demo

[Demo YouTube](https://www.youtube.com/watch?v=EvRmBBJJen0)

## Connections

### **SD**

| SD   | MEGA |
| :--- | :--- |
| CS   | P11  |
| SCK  | P52  |
| MOSI | P51  |
| MISO | P50  |
| VCC  | 5V   |
| GND  | GND  |

### **RTC M2**

| RTC M2 | MEGA |
| :----- | :--- |
| VCC    | 5V   |
| GND    | GND  |
| CLK    | P8   |
| DAT    | P2   |
| RST    | P9   |

### **MAXREFDES117#**

| MAX | MEGA |
| :-- | :--- |
| VIN | VIN  |
| SDA | SDA  |
| SCL | SCL  |
| INT | P10  |
| GND | GND  |

### **NOKIA 3310#**

| NOKIA | MEGA     |
| :---- | :------- |
| RST   | P6 - 10K |
| CE    | P7 - 10K |
| DC    | P5 - 10K |
| DIN   | P4 - 10K |
| CLK   | P3 - 10K |
| VCC   | 3.3V     |
| LIGHT | GND      |
| GND   | GND      |

### **OLED DIPALY**

| OLED | MEGA |
| :--- | :--- |
| CS   | P44  |
| DC   | P46  |
| RES  | P33  |
| D1   | P45  |
| D0   | P31  |
| VCC  | 3.3V |
| GND  | GND  |

### **RBPy w0**

| RBPy w0 | LVL shift | MEGA  |
| :------ | --------- | :---- |
| P1      | LV - HV   | 5V    |
| P8      | LV4 - HV4 | RX315 |
| P10     | LV3 - HV3 | TX314 |
| P14     | GND - GND | GND   |

## [OCW - project link](https://ocw.cs.pub.ro/courses/pm/prj2021/abirlica/455)
