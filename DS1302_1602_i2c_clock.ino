// USING ARDUINO 1.6.5.EXE
// DS1302_LCD (C)2010 Henning Karlsen +2015 NTGERALT 
// web: http://www.henningkarlsen.com/electronics
//
// A quick demo of how to MIX DS1302-library and DHT11 into 1602 I2C LCD.
//
// DS1302:  
//          CE pin    -> Arduino Digital 2
//          I/O pin   -> Arduino Digital 3
//          SCLK pin  -> Arduino Digital 4
//          VCC  -> 5V
//          GND  -> GND
// I2C 1302 LCD:     
//            SDA       -> A4
//            SCL       -> A5
//          VCC  -> 5V
//          GND  -> GND
// DHT11: 
//          IO DATA  -> Arduino Digital 4
//          VCC  -> 5V
//          GND  -> GND

 
#include <dht11.h>    
#include <DS1302.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
dht11 DHT11;     //定義DHT11 物件
#define DHT11PIN 5  //定義讀取資料的 Pin腳 

// Init the DS1302
DS1302 rtc(2, 3, 4);

// Init the LCD
LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  // Set the clock to run-mode, and disable the write protection
  rtc.halt(false);
  rtc.writeProtect(false);
  lcd.init(); // initialize the lcd 
lcd.backlight(); //Open the backlight


// The following lines can be commented out to use the values already stored in the DS1302
//去掉斜杠将刷新1302时钟计时为下面设置
// rtc.setDOW(MONDAY);        // Set Day-of-Week to FRIDAY
// rtc.setTime(5, 59, 30);     // Set the time to 12:00:00 (24hr format)
//rtc.setDate(17, 9, 2015);   // Set the date to August 6th, 2010
}

void loop()
{
 lcd.setCursor(0, 0); //將游標設定在第一行第一個位置(column 0, line 1)  
   int chk = DHT11.read(DHT11PIN);  //檢查DHT感測器的回應  
     
    lcd.print((float)DHT11.humidity,0);//读取湿度，小数点后0位       
    lcd.print("%");       //添加单位
    lcd.print((float)DHT11.temperature, 0);    //读取温度   
    lcd.print((char)223);
    lcd.print("C ");   


           
  
  // Display time centered on the upper line
  lcd.setCursor(8, 0);
  lcd.print(rtc.getTimeStr());
  
  // Display abbreviated Day-of-Week in the lower left corner
  lcd.setCursor(0, 1);
  lcd.print(rtc.getDOWStr(FORMAT_LONG));
  
  // Display date in the lower right corner
  lcd.setCursor(6, 1);
  lcd.print(rtc.getDateStr());

  // Wait one second before repeating :)
  delay (1000);
}
