#include <LiquidCrystal.h>
#include <DHT.h>
// Humidity pin and type
#define DHT_PIN 7
#define DHT_TYPE DHT11

// LCD pins
const int rs=12, en=11, d4=22, d5=24, d6=26, d7=28;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// temperature and humidity module
DHT dht(DHT_PIN, DHT_TYPE);

float temperature = 0;
float humidity = 0;
int waterLevel = 0;
int waterPin = A5;

void setup() {
  dht.begin();

  lcd.begin(16,2);
  lcd.print("Booting Up...");

}

void loop() {
  delay(1000);
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

// ---Code for replacing analogRead()--- //
  ADMUX = _BV(REFS0) | (0x05 & 0x0F); 
  ADCSRA |= _BV(ADSC);
  while(bit_is_set(ADCSRA,ADSC));
  waterLevel = ADC;
// ------------------------------------ //
  if(waterLevel <= 100){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print(" C");

    lcd.setCursor(0,1);
    lcd.print("Humidity: ");
    lcd.print(humidity);
    lcd.print(" %");
  }
  if(waterLevel > 100 & waterLevel <= 300){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Water Level Low");
    }
}


