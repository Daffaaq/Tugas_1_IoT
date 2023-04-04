#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SimpleDHT.h>

// Pin untuk LED RGB
#define REDPIN D3
#define GREENPIN D5
#define BLUEPIN D6

// Inisialisasi LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Set suhu normal
float suhuNormal = 25.0;

// DHT11
#define pinDHT 7
SimpleDHT11 dht11(D7);

byte temperature = 0;
byte humidity = 0;

void setup()
{
  // Inisialisasi pin LED RGB
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);

  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();

  // Tampilkan waktu saat ini pada LCD
  lcd.setCursor(0, 0);
  lcd.print("04-04-2023 15:32");
}

void loop()
{
  // cek DHT11
  int err = SimpleDHTErrSuccess;

  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess)
  {
    Serial.print("Pembacaan DHT11 gagal, err=");
    Serial.println(err);
    delay(1000);
    return;
  }

  // Konversi suhu ke Fahrenheit
  float suhuCelcius = (float)temperature;
  float suhuFahrenheit = suhuCelcius * 1.8 + 32;

  // Tampilkan suhu dalam Celcius dan Fahrenheit pada LCD
  lcd.setCursor(0, 1);
  lcd.print("Suhu: ");
  lcd.print(suhuCelcius);
  lcd.print((char)223);
  lcd.print("C / ");
  lcd.print(suhuFahrenheit);
  lcd.print((char)223);
  lcd.print("F ");

  // Atur warna LED RGB berdasarkan suhu
  if (suhuCelcius < suhuNormal - 2)
  {
    // Suhu dingin, LED hijau berkedip
    digitalWrite(GREENPIN, HIGH);
    digitalWrite(REDPIN, LOW);
    digitalWrite(BLUEPIN, LOW);
    delay(500);
    digitalWrite(GREENPIN, LOW);
    delay(500);
  }
  else if (suhuCelcius > suhuNormal + 2)
  {
    // Suhu tinggi, LED merah berkedip
    digitalWrite(REDPIN, HIGH);
    digitalWrite(GREENPIN, LOW);
    digitalWrite(BLUEPIN, LOW);
    delay(500);
  }
}