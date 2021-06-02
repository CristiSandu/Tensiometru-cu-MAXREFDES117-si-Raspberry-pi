# Tensiometru cu MAXREFDES117# si Raspberry-pi

## Images

|                                                                                                                                 |                                                                                                                                 |
| :------------------------------------------------------------------------------------------------------------------------------ | :------------------------------------------------------------------------------------------------------------------------------ |
| ![](https://github.com/CristiSandu/Tensiometru-cu-MAXREFDES117-si-Raspberry-pi/blob/main/images/TensiometruRezultateSIC701.jpg) | ![](https://github.com/CristiSandu/Tensiometru-cu-MAXREFDES117-si-Raspberry-pi/blob/main/images/TensiometruRezultateSIC142.jpg) |
| ![](https://github.com/CristiSandu/Tensiometru-cu-MAXREFDES117-si-Raspberry-pi/blob/main/images/hrSDPlot.jpg)                   | ![](https://github.com/CristiSandu/Tensiometru-cu-MAXREFDES117-si-Raspberry-pi/blob/main/images/spo2SDPlot.jpg)                 |
| ![](https://github.com/CristiSandu/Tensiometru-cu-MAXREFDES117-si-Raspberry-pi/blob/main/images/outputSDDemoVideo.jpg)          | ![](https://github.com/CristiSandu/Tensiometru-cu-MAXREFDES117-si-Raspberry-pi/blob/main/images/testVideoDemo.png)              |

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
