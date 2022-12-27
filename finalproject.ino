#define BLYNK_TEMPLATE_ID "TMPLn9DgB2E2"
#define BLYNK_DEVICE_NAME "Quickstart Device"
#define BLYNK_AUTH_TOKEN "o4tpnRdfMPYxI2MyQncAxKU4kOPDF2Q6"
char ssid [] = "vivo 1820";
char pass [] = "12345678";
// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = BLYNK_AUTH_TOKEN;
BlynkTimer timer;

float cahaya ;
  int hujan;
  int posisi = 0;

#include <Servo.h>

Servo myservo;  // create servo object to control a servo

#include <Wire.h>
#include <BH1750_WE.h>
#define BH1750_ADDRESS 0x23
BH1750_WE myBH1750 = BH1750_WE(BH1750_ADDRESS); 


void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V1, posisi);
    Blynk.virtualWrite(V2, hujan);
    Blynk.virtualWrite(V4, cahaya);

}



void setup() {
  // put your setup code here, to run once:
   myservo.attach(12);  // attaches the servo on GIO2 to the servo object
     Wire.begin();
  myBH1750.init();//sensor cahaya
  Serial.begin(9600);
  myservo.write(0);//pin d6
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);

}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();
   cahaya = myBH1750.getLux(); //pin scl sdh
   hujan = (analogRead(A0)); //pin analog
  
  Serial.print(cahaya);
  Serial.print("  ");
  Serial.print(hujan);
  Serial.print("  ");
  Serial.println(posisi);


  
  
  if (cahaya > 10 && hujan > 1000 && posisi == 0)
  {//cerah tidak hujan dan posisi diluar
    myservo.write(180);
    posisi = 1;
  }
  else if(cahaya < 10 && hujan > 1000 && posisi == 0)
  {//gelap tidak hujan posisi dalam
   myservo.write(0);
   posisi = 0;
  }
  else if (cahaya > 10 && hujan < 1000 && posisi == 0)
  {//cerah tapi hujan posisi dalam
    myservo.write(0);
    posisi = 0;
  }
  else if (cahaya < 10 && hujan < 1000 && posisi == 0)
  {//gelap dan hujan posisi dalam
    myservo.write(0);
    posisi = 0;
  }
  else if (cahaya > 10 && hujan > 1000 && posisi == 1)
  {//cerah dan tidak hujan posisi diluar
    myservo.write(180);
    posisi = 1;
  }
  else if (cahaya < 10 && hujan > 1000 && posisi == 1)
  {//gelap dan tidak hujan posisi diluar
    myservo.write(0);
    posisi = 0;
  }
  else if (cahaya > 10 && hujan < 1000 && posisi == 1)
  {//cerah dan hujan diluar
    myservo.write(0);
    posisi = 0;
  }
  else if (cahaya < 10 && hujan < 1000 && posisi == 1)
  {//gelap dan hujan posisi masuk
    myservo.write(0);
    posisi = 0;
  }

  
}
