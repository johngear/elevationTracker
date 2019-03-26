
//Include the libraries needed to function
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 20, 4);  // Set the LCD I2C address
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

byte mtn1[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00100,
  B01010,
  B10001,
};

byte mtn2[8] = {
  B00100,
  B01010,
  B10001,
  B00000,
  B00000,
  B00000,
  B00000,
};


double firstElev = 0;  
double highestVertical = 0;
double currentElev = 0;


void setup()  
{
  //ensure that sensor is working before moving forward
  if(!bmp.begin())
  {
    while(1);
  }

  //output initial comments to user
  lcd.init();
  lcd.backlight();
  lcd.begin(20,4); //dimensions of screen
  
  lcd.setCursor(2,0);
  lcd.print("Welcome to the");
  lcd.setCursor(1,1);
  lcd.print("climbing elevation");
  lcd.setCursor(7,2);
  lcd.print("sensor");
  lcd.createChar(0,mtn1);
  lcd.createChar(1,mtn2);

  lcd.setCursor(8,3);
  lcd.write (byte(0));
  lcd.write( byte(1));
  lcd.write (byte(0));
  delay(2000);
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("built by: ");
  lcd.setCursor(4,2);
  lcd.print("John Gearig");
  
  sensors_event_t event;
  bmp.getEvent(&event);
  float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
  firstElev = bmp.pressureToAltitude(seaLevelPressure, event.pressure);
  delay(2000);
}

void loop(){
  sensors_event_t event;
  bmp.getEvent(&event);
  float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
 
  /* Display the results (barometric pressure is measure in hPa) */
  if (event.pressure)
  {
    /* Display atmospheric pressue in hPa */
    lcd.setCursor(0,0);
    lcd.print("Pressure :");
    lcd.setCursor(10,0);
    lcd.print(event.pressure);
    lcd.setCursor(17,0);
    lcd.println("hPa");
        float temperature;
    bmp.getTemperature(&temperature);

    lcd.setCursor(0,1);
    lcd.print("Temp     :");
    lcd.setCursor(11,1);
    lcd.print(temperature);
    lcd.setCursor(17,1);
    lcd.print("C");

    lcd.setCursor(0,2);
    lcd.print("Altitude : "); 
    lcd.setCursor(10,2);
    currentElev = bmp.pressureToAltitude(seaLevelPressure, event.pressure);
    lcd.print(currentElev); 
    lcd.setCursor(17,2) ;
    lcd.print("m");                              
  
  }
  else
  {
    lcd.println("Sensor error");
  }

  if(currentElev - firstElev > highestVertical){
    highestVertical = currentElev-firstElev;
  }
  
  lcd.setCursor(0,3);
  lcd.print("Vert gain: ");
  lcd.setCursor(12,3);
  lcd.print(highestVertical);
  lcd.setCursor(16,3);
  lcd.print(" m");
  delay(1000);
    
  
}

/* 
void displaySensorDetails(void)
{
  sensor_t sensor;
  bmp.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" hPa");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" hPa");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" hPa");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

 */
