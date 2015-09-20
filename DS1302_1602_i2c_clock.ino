// DS1302_LCD (C)2010 Henning Karlsen +2015 NTGERALT 
// web: http://www.henningkarlsen.com/electronics
//
// A quick demo of how to MIX DS1302-library and DHT11 into 1602 I2C LCD.

// DS1302:  
//          CE pin    -> Arduino Digital 2
//          I/O pin   -> Arduino Digital 3
//          SCLK pin  -> Arduino Digital 4
//          VCC  -> 5V
//          GND  -> GND


//1602 I2C  LCD:     
//            SDA       -> A4
//            SCL       -> A5
//          VCC  -> 5V
//          GND  -> GND


// DHT11: 
//          IO DATA  -> Arduino Digital 4
//          VCC  -> 5V
//          GND  -> GND

   
   
   #define SCK_PIN 4
   #define IO_PIN 3
   #define RST_PIN 2
   #define dht_dpin 5
   #include <dht.h>   
   #include <DS1302.h>
   #include <Wire.h> 
   #include <LiquidCrystal_I2C.h>
   LiquidCrystal_I2C lcd(39,16,2);  // 0x27 ou 39
   DS1302 rtc(RST_PIN, IO_PIN, SCK_PIN);
   dht DHT;  

   void setup(){
    
   lcd.init();        // initializa o lcd 
   lcd.backlight();   // acende a luz de fundo no lcd
  
   rtc.halt(false);
   rtc.writeProtect(false);
    
   }

   void loop(){
 
   /* Os comandos abaixo servem para acertar data e hora retire
   as barras e acerte os valores, carregue o programa, recoloque 
   as barras e recarregue o programa novamente*/
   
/////////////////SET TIMES HERE/////////////
//rtc.setDOW(1);             
//rtc.setTime(00, 53, 00);   
//rtc.setDate(20, 9, 2015);  
   DHT.read11(dht_dpin);   //去library裡面找DHT.read11  
   lcd.setCursor(0, 1);
   lcd.print((float)DHT.humidity,0);
   lcd.print("%");   
   lcd.print((float)DHT.temperature, 0); 
   lcd.print((char)223);
   lcd.println("C ");  
   lcd.setCursor(8, 1);
   lcd.print(rtc.getTimeStr());
   
   lcd.setCursor(12, 0);
   lcd.print(rtc.getDOWStr(FORMAT_SHORT));
   
   lcd.setCursor(1,0);
   lcd.print(rtc.getDateStr(FORMAT_SHORT));

   delay (1000);
   }
