/* 
*
* Lesson 82: Using VL53L1X 400cm Laser Distance Sensor LCD with Arduino  
Watch full video details of this code https://youtu.be/Lt-Zhm_XY38

 Library used: http://librarymanager/All#SparkFun_VL53L1X

 * This Arduin sketch display distnace using VL53L1X distance sensor on LCD1602 or LCD2004 with I2C module (4 wires)
 * 
The distance is can be selected to ba in "mm", "inches", "feet", "cm" and "meter"


 * Written by Ahmad Shamshiri on Jun 18, 2020 in Ajax, Ontario, Canada
 * in Ajax, Ontario, Canada. www.robojax.com
 * 

  This video is part of Arduino Step by Step Course which starts here: https://youtu.be/-6qSrDUA5a8

 

If you found this tutorial helpful, please support me so I can continue creating 
content like this. You can support me on Patreon http://robojax.com/L/?id=63

or make donation using PayPal http://robojax.com/L/?id=64
  
 * This code is "AS IS" without warranty or liability. Free to be used as long as you keep this note intact.* 
 * This code has been download from Robojax.com
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

 VL53L1X distance reading from Sparkfun https://github.com/sparkfun/SparkFun_VL53L1X_Arduino_Library
  *   Reading distance from the laser based VL53L1X
  By: Nathan Seidle
  Revised by: Andy England
  SparkFun Electronics
  Date: April 4th, 2018

*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display


const uint8_t I2C_ADDRESS =0x27;
const uint8_t LCD_CHAR= 16;
const uint8_t LCD_ROW= 2;
LiquidCrystal_I2C lcd(I2C_ADDRESS, LCD_CHAR,LCD_ROW);

#include "SparkFun_VL53L1X.h" //Click here to get the library: http://librarymanager/All#SparkFun_VL53L1X

//Optional interrupt and shutdown pins.
#define SHUTDOWN_PIN 2
#define INTERRUPT_PIN 3

SFEVL53L1X distanceSensor;
//Uncomment the following line to use the optional shutdown and interrupt pins.
//SFEVL53L1X distanceSensor(Wire, SHUTDOWN_PIN, INTERRUPT_PIN);

int distance=0;
void setup()
{
  Wire.begin();
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();


   if (distanceSensor.begin() != 0) //Begin returns 0 on a good init
  {
      lcd.print("Sensor failed");
      lcd.setCursor(0,1);
      lcd.print("check wiring!");      
    while (1)
      ;
  }

   //distanceSensor.setDistanceModeShort();
  distanceSensor.setDistanceModeLong();
      lcd.print("Robojax VL53L1X");
      lcd.setCursor(0,1);
      lcd.print("Mode: Medium"); 
      //lcd.print("Mode: Long");          
      delay(2000);       
      clearCharacters(LCD_ROW-1,0, LCD_CHAR-1);
      lcd.setCursor(0,1);
      lcd.print("Distance: ");         

}//setup() end



void loop()
{
  getDistance();
  printDistance('f');

  // if distance is greator thatn 185mm do something
  if(distance >185)
  {
    // somethig here
  }
 delay(300);
}




/*
 * getDistance()
 * displays gets the distance for VL53L1X laser sensor
 * updates the "distance" variable with distance in mm
 * 
 */
int getDistance()
{
  distanceSensor.startRanging(); //Write configuration bytes to initiate measurement

  while (!distanceSensor.checkForDataReady())
  {
    delay(1);
  }
  distance = distanceSensor.getDistance(); //Get the result of the measurement from the sensor
  distanceSensor.clearInterrupt();

  distanceSensor.stopRanging();
  
}//getDistance()  end


/*
 * printDistance(char unit)
 * displays value and title on LCD1602
 * How to use:
 * printDistance('m');

 */
void printDistance(char unit)
{
   // Robojax.com LCD1602 for VL53L1X d
  float distanceInches = distance * 0.0393701;
  float distanceFeet = distanceInches / 12.0 - 8;
  float distanceMeter = distance/1000.00;
  float distanceCm= distance/10.00;

  
   clearCharacters(1,9, LCD_CHAR-1 );
   lcd.setCursor (9,1); //
   if(unit =='i')
   {
    
    lcd.print(distanceInches);    
    lcd.print("in");
    
   }
   if(unit =='m')
   {
    lcd.print(distance);    
    lcd.print("mm");
    
   }
   if(unit =='f')
   {
    lcd.print(distanceFeet);    
    lcd.print("ft");
   }
   if(unit =='c')
   {
    lcd.print(distanceCm);    
    lcd.print("cm");
   }  
   if(unit =='a')
   {
    lcd.print(distanceMeter);    
    lcd.print("m");
   }         
 // Robojax.com LCD1602 for LM35 Demo
}  

/*
   clearCharacters(uint8_t row,uint8_t start, uint8_t stop)
 * @brief clears a line of display (erases all characters)
 * @param none
 * @return does not return anything
 * Written by Ahmad Shamshiri
 * www.Robojax.com code May 28, 2020 at 16:21 in Ajax, Ontario, Canada
 */
void clearCharacters(uint8_t row,uint8_t start, uint8_t stop )
{
    for (int i=start; i<=stop; i++)
    {
    lcd.setCursor (i,row); //  
    lcd.write(254);
    } 

}//clearCharacters
