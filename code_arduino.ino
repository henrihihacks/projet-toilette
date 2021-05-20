#include <U8g2lib.h>
/*     Arduino Rotary Encoder Tutorial
 *      
 *  by Dejan Nedelkovski, www.HowToMechatronics.com
 *  
 */

#include <Arduino.h>
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif


 #define clkPin 3
 #define dtPin 2
#define swPin 6
#define digPin1 8
#define digPin2 7
#define chassePin 1

 int counter = 0; 
 int aState;
 int aLastState; 
 int var = 0; 
int swState;
int swLast;
bool appuie=false;
bool bouton=HIGH;
bool verser=true;
bool chasse=HIGH;
int T =20000;
int T1;
int T2;

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   




 void setup() { 
  u8g2.begin();
   
  Serial.begin(9600);
  Serial.println(F("Initialize System"));
   pinMode (clkPin,INPUT);
   pinMode (dtPin,INPUT);
  pinMode(swPin,INPUT_PULLUP);
  pinMode (digPin1,OUTPUT);
  pinMode (digPin2 ,OUTPUT);
  pinMode (chasse , INPUT_PULLUP);

   aLastState = digitalRead(clkPin);   
   
 } 

 void loop() { 
                Affichage();
                Serial.print("Rotary position ");
                Serial.println(counter);
                aState = digitalRead(clkPin); 
               
                
                if ((aState != aLastState) && (appuie==false)) {     
                  
                    if (digitalRead(dtPin) != aState) { 
                      counter = counter - 5;
                       if (counter <0) {
                            counter = 0;
                       }
                    }                                              //partie pour que le compteur aille de 0 a 100 de 5 en 5
                                                      
            else {
                     counter = counter + 5;
                     if ( counter > 100 ) {
                        counter = 100;
                      }
                 }
                    verser=true;
                 }
       
   aLastState = aState; 
 Affichage();
 

 bouton = digitalRead(swPin);                    //bouton pour bloquer la selection
 if (bouton==LOW) {
      appuie= !appuie;
 }
chasse= digitalRead(chassePin);                  //bouton pour déclencher les pompes 
if (chasse==LOW) 
      appuie= !appuie;
  
      //Affichage();
 
      if (verser==true) {
          T1= T / 100 * counter;                          
          T2= T- T1;                              //partie pour les relay (T= temps que met le verre a se remplir en entier) 
       

          digitalWrite(digPin1, HIGH);
          delay(T1);
          digitalWrite(digPin1, LOW);                             

          digitalWrite(digPin2, HIGH);
          delay(T2);
          digitalWrite(digPin2, LOW);

          verser=false;
    
          }
      }
 
 
 
 }

void Affichage( ) {
    u8g2.clearBuffer();          
  u8g2.setFont(u8g2_font_ncenB24_tr); 
   if (appuie==true) {
    u8g2.setCursor(10, 30);
    u8g2.drawFrame(12,2, 115,30);                //affichage du rectangle quand on selectionne un pourcentage
    delay(100);

  
  }
  u8g2.setCursor(40, 30);                         //affichage des chiffres 
  u8g2.print(counter); 
  u8g2.setCursor(100, 30);
  u8g2.print("%");                               //affichage du symbole "%"
  u8g2.sendBuffer();          
  

 }
 
