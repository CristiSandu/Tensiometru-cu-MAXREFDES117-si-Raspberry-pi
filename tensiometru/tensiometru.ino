/*
* Proiect : Tensiometru cu Arduino MEGA 2560 si MAXREFDES117#
* Descriere : Proiectul prezinta implementarea unui cititor de puls care printeaza pe un display de Nokia 5510 
*             graficul pulsului alaturi de valoare concetratiei de oxigen, pe alt display OLED pulsul si SPo2-ul, iar la final 
*             transmite prin serial catre un Rasbery py valorile pt afisare. La fiecare modificare a pulsului se salveaza intr-un fisier: 
*             data,ora pulsul si concetratia de oxigen 
*
*/
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <DS1302.h>
#include <SD.h>
#include <PCD8544.h>
#include "algorithm_by_RF.h"
#include "max30102.h"
#include "U8glib.h"

static PCD8544 lcd;                     // nume display 
File myFile;                            // nume fisier de scriere 
DS1302 rtc(9, 2, 8);                    // asociere rtc pini 9,2,8
U8GLIB_SH1106_128X64 u8g(31,45, 44, 46,33);  // D0=13, D1=11, CS=10, DC=9, Reset=8


static const byte ledPin = 13;

// Dimensiunea LCD-ului
static const byte LCD_WIDTH = 84;
static const byte LCD_HEIGHT = 48;

// Numarul de lini pentru graficul pulsului
static const byte CHART_HEIGHT = 5;
static const byte THERMO_WIDTH = -2;

#define MAX_BRIGHTNESS 255
const byte oxiInt = 10; // pinul de conectare cu MAXREFDES117#

uint32_t elapsedTime,timeStart;
uint32_t aun_ir_buffer[BUFFER_SIZE]; //infrared LED sensor data
uint32_t aun_red_buffer[BUFFER_SIZE];  //red LED sensor data
float old_n_spo2;  // Previous SPO2 value
uint8_t uch_dummy,k;



void setup() {

// setare pini senzor 
    pinMode(oxiInt, INPUT); 
    Wire.begin();

    Serial.begin(115200);
    Serial3.begin(9600);
    
    lcd.begin(LCD_WIDTH, LCD_HEIGHT);
    delay(1000);

    pinMode(ledPin, OUTPUT);
    rtc.halt(false);
    rtc.writeProtect(false);

// Verificare conectare SD card 
    if (!SD.begin(11)) {
      Serial.println("initialization failed!");
      while (1);
    }
    
    Serial.println("initialization done.");
    
    
    maxim_max30102_reset();     // resetare MAXREFDES117
    maxim_max30102_read_reg(REG_INTR_STATUS_1,&uch_dummy);  //Reads/clears the interrupt status register
    maxim_max30102_init();  //initialize the MAXREFDES117
    old_n_spo2=0.0;         // setare initiala a spO2
    
    
    while(Serial.available()==0)  // asteapta pana user-ul apasa o tasta 
    {
      Serial.write(27);       // ESC command
      Serial.print(F("[2J"));  
      Serial.println(F("Press any key to start conversion"));
      delay(10);
    }

    u8g.firstPage();
    uch_dummy=Serial.read();      
    timeStart = millis();              // setare timp de start 
       
}

void loop() {

    float n_spo2,ratio,correl;  //SPO2 value
    int8_t ch_spo2_valid;  //indicator to show if the SPO2 calculation is valid
    int32_t n_heart_rate; //heart rate value
    int8_t  ch_hr_valid;  //indicator to show if the heart rate calculation is valid
    int32_t i;
    char hr_str[10];
    uint32_t un_min, un_max, un_prev_data, un_brightness;     
    
    static byte xChart = LCD_WIDTH;
    digitalWrite(ledPin, HIGH); 

  
    un_brightness=0;
    un_min=0x3FFFF;
    un_max=0;
    
    for(i=0;i<BUFFER_SIZE;i++)
    {
          while(digitalRead(oxiInt)==1);  //asteapta pana nu exista nici-o intrerupere
          maxim_max30102_read_fifo((aun_red_buffer+i), (aun_ir_buffer+i));  //citeste de la MAXREFDES117# FIFO

          // printeaza la monitorul serial red si ir
          Serial.print(i, DEC);
          Serial.print(F("red="));
          Serial.print(aun_red_buffer[i], DEC);
          Serial.print(F(", ir="));
          Serial.print(aun_ir_buffer[i], DEC);    
          Serial.println("");
          
          rf_heart_rate_and_oxygen_saturation(aun_ir_buffer, BUFFER_SIZE, aun_red_buffer, &n_spo2, &ch_spo2_valid, &n_heart_rate, &ch_hr_valid, &ratio, &correl);
    }

    rf_heart_rate_and_oxygen_saturation(aun_ir_buffer, BUFFER_SIZE, aun_red_buffer, &n_spo2, &ch_spo2_valid, &n_heart_rate, &ch_hr_valid, &ratio, &correl); 
    elapsedTime=millis() - timeStart;           // diferenta intre timpul de start si cel curent     
    millis_to_hours(elapsedTime, hr_str); // Time in hh:mm:ss format
    elapsedTime/=1000; // Time in secunde


    // daca HR valid se face continutul 
    if(n_heart_rate!=-999)
    {
    
        lcd.setCursor(0, 0);                               //setez cursorul pe prima linie a lcd-ului 
        lcd.print("HR:");                                  //printez HR si  
        lcd.print(n_heart_rate,DEC);                       //
        lcd.print(" SPO2:");                               //SPO2 
        lcd.print((int)n_spo2,DEC);                        //
        
        
        lcd.print(" ");

        u8g.firstPage();  
          do {
            u8g.setFont(u8g_font_helvR12);  
            u8g.drawStr(0, 15, "HR:");  
            u8g.setPrintPos(60, 15);
            u8g.print(n_heart_rate, DEC);
            u8g.print("B/m");
            
            u8g.drawStr(0, 35, "SPO2:");
            u8g.setPrintPos(60, 35);
            u8g.print((int)n_spo2, DEC);
            u8g.print("%");

            u8g.setPrintPos(0, 55);
            u8g.print(rtc.getTimeStr());
           
          } while( u8g.nextPage() );

        //send data to R Pi
        Serial3.println(n_heart_rate);
        Serial3.println("H");
        Serial3.println((int)n_spo2);
        
        if (xChart >= LCD_WIDTH) {
          xChart = THERMO_WIDTH + 2;
        }
      
        // Update HR coloana in grafic   
        lcd.setCursor(xChart, 0);
        lcd.drawColumn(CHART_HEIGHT, map(n_heart_rate, 0, 150, 0, CHART_HEIGHT*8));  // ...clipped to the 0-150HR range.
        lcd.drawColumn(CHART_HEIGHT, 0);         // ...with a clear marker to see the current chart position.
        
        xChart++;
        
        digitalWrite(ledPin, LOW);  
        delay(500);

        digitalWrite(ledPin, LOW);  
        
        Serial.println("--RF--");
        Serial.print(elapsedTime);
        Serial.print("\t");
        Serial.print(n_spo2);
        Serial.print("\t");
        Serial.print(n_heart_rate, DEC);
        Serial.print("\t");
        Serial.println(hr_str);
        Serial.println("------");


        // deschidere myFile pentru scriere 
        myFile = SD.open("test.txt", FILE_WRITE);

        // daca sa deschis de scrie: timpul, data,HR si SPO2 
        if (myFile) {
        
            Serial.print("Writing to test.txt...");
            myFile.print(rtc.getTimeStr());
            myFile.print(" - ");
            myFile.print(rtc.getDateStr());
            myFile.print(" ");
            myFile.print(n_heart_rate);
            myFile.print(" ");
            myFile.print(n_spo2);
            myFile.println();
            
            // close the file:
            myFile.close();
            Serial.println("done.");
        
        } else {

            // daca fisierul nu se deschide print a error
            Serial.println("error opening test.txt");
        
        }
      
    }
}

// functie transformare milisecunde in ore 
void millis_to_hours(uint32_t ms, char* hr_str)
{
    char istr[6];
    uint32_t secs,mins,hrs;
    secs=ms/1000; // time in seconds
    mins=secs/60; // time in minutes
    secs-=60*mins; // leftover seconds
    hrs=mins/60; // time in hours
    mins-=60*hrs; // leftover minutes
    itoa(hrs,hr_str,10);
    strcat(hr_str,":");
    itoa(mins,istr,10);
    strcat(hr_str,istr);
    strcat(hr_str,":");
    itoa(secs,istr,10);
    strcat(hr_str,istr);
}
