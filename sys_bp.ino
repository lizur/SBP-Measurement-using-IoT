#include <dht.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
dht DHT;
#define DHT11_PIN A0
int in = 8;
int Reset=6;
int start=7;
int count=0,i=0,k=0,rate=0,pressure=0;
unsigned long time2,time1;
unsigned long time;
byte heart[8] = 
{
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};
void setup()
{
  lcd.createChar(1, heart);
  lcd.begin(16,2);
  
  lcd.print("Heart Beat ");
  lcd.write(1);
  lcd.setCursor(0,1);
  lcd.print("Monitering");
  pinMode(in, INPUT);
  pinMode(Reset, INPUT);
  pinMode(start, INPUT);
  digitalWrite(Reset, HIGH);
  digitalWrite(start, HIGH);
  delay(1000);
}
void loop()
{
  
  if(!(digitalRead(start)))
  {
    k=0;
    lcd.clear();
    lcd.print("Please wait.......");
    while(k<5)
    {
     if(digitalRead(in))
     {
      if(k==0)
      time1=millis();
      k++;
      while(digitalRead(in));
     }
    }
    
    
      time2=millis();
      rate=time2-time1;
      rate=rate/5;
      rate=60000/rate;
      pressure=(0.2411*rate)+106.27;
      lcd.clear();
      lcd.print("HR:");
      //lcd.setCursor(0,1);
      lcd.print(rate);
      //lcd.print(" ");
      lcd.write(1); 
      lcd.print(", ");
      lcd.print("SBP:");
      lcd.print(pressure);     
      k=0;
      rate=0;
      
      //temperature
    int chk = DHT.read11(DHT11_PIN);
    lcd.setCursor(0,1); 
    lcd.print("T: ");
    lcd.print(DHT.temperature);
    lcd.print((char)223);
    lcd.print("C");
    DHT.temperature=0;
    }
  if(!digitalRead(Reset))
  {
    rate=0;
    pressure=0;
     lcd.clear();
      lcd.print("HR:");
      lcd.setCursor(0,1);
      lcd.write(1);
      lcd.print(rate);
      lcd.print(" & ");
      lcd.print("SBP:");
      lcd.print(pressure);
      k=0;
  }
}


