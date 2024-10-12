#include<EEPROM.h>
long lastms; 
byte h=0,m=0,s=0; 
void setup() {   
  // put your setup code here, to run once:   
  Serial.begin(9600);
  h = EEPROM.read(1)
  m = EEPROM.read(2)
  s = EEPROM.read(3)  
  lastms=millis(); 
  }  
void loop() {
  // put your main code here, to run repeatedly:  
  if(millis()-lastms>=1000){        
    s++;
    if(s>59){             
      m++;
      s=0;        
    }        
    if(m>59){             
      h++;             
      m=0;      
    }
    lastms=millis();        
    Serial.print(h);      
    Serial.print(":");       
    Serial.print(m);       
    Serial.print(":");        
    Serial.println(s);
    if (s > 10){
      EEPROM.write(1, h);
      EEPROM.write(2, m);
      EEPROM.write(3, s);   
    }     
    }
  }