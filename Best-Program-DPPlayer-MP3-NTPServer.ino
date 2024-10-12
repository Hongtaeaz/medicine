#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define ledPin1 D3
#define ledPin2 D4
#define ledPin3 D6
#define ledPin4 D7
SoftwareSerial mp3Serial(D0, D5); // RX, TX

#define ON LOW
#define OFF HIGH

const char *ssid     = "internet";
const char *password = "123456789";

unsigned long period = 1000;
unsigned long last_time = 0;

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

// LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address 0x27, 16 column and 2 rows

// Week Days
String weekDays[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
// Month names
String months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

int valueSwitch;
bool check = true;
void setup () {

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  digitalWrite(ledPin1, OFF);
  digitalWrite(ledPin2, OFF);
  digitalWrite(ledPin3, OFF);
  digitalWrite(ledPin4, OFF);
  digitalWrite(ledPin1, ON); delay(1000);
  digitalWrite(ledPin2, ON); delay(1000);
  digitalWrite(ledPin3, ON); delay(1000);
  digitalWrite(ledPin4, ON); delay(1000);
  digitalWrite(ledPin1, OFF);
  digitalWrite(ledPin2, OFF);
  digitalWrite(ledPin3, OFF);
  digitalWrite(ledPin4, OFF);
  Serial.begin (115200);

  // LCD initialization
  lcd.begin();
  lcd.backlight();

  for (int Rx = 1; Rx <= 10; Rx++) {
    Serial.println("Rx : " + String(Rx));
    delay(200);
  }
  mp3Serial.begin (9600);
  mp3_set_serial(mp3Serial);
  mp3_set_volume(5);
  Serial.println("Start");
  lcd.setCursor(0, 0); 
  lcd.print("SSID: internet"); 
  lcd.setCursor(0, 1);  
  lcd.print("PASS: 123456789");
  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Initialize NTPClient to get time
  timeClient.begin();
  timeClient.setTimeOffset(25200);  // Set time offset for your timezone (e.g., GMT+7)
}

void loop () {


  if ( millis() - last_time > period) {
    last_time = millis();
    timeClient.update();
    time_t epochTime = timeClient.getEpochTime();
    struct tm *ptm = gmtime((time_t *)&epochTime);
    String formattedTime = timeClient.getFormattedTime();
    int currentHour = timeClient.getHours();
    int currentMinute = timeClient.getMinutes();
    int currentSecond = timeClient.getSeconds();
    String weekDay = weekDays[timeClient.getDay()];
    int monthDay = ptm->tm_mday;
    int currentMonth = ptm->tm_mon + 1;
    String currentMonthName = months[currentMonth - 1];
    int currentYear = ptm->tm_year + 1900;
    String currentDate = weekDay + " " + String(monthDay) + "/" + String(currentMonth) + "/" + String(currentYear);
    lcd.clear();
    lcd.setCursor(0, 0);  // Set cursor to the first line
    lcd.print(currentDate);  // Display day/month/year
    String currentTime = formattedTime;
    lcd.setCursor(4, 1);  // Set cursor to the second line
    lcd.print(currentTime);  // Display time (HH:MM:SS)
    Serial.print("Current date: ");
    Serial.println(currentDate);
    Serial.print("Current time: ");
    Serial.println(currentTime);
    Serial.println("");
    if ( (currentHour == 7) && (currentMinute == 30) && (currentSecond >= 1 && currentSecond <= 25) ) {
      if (check == true) {
        digitalWrite(ledPin1, ON);
        check = false;
        mp3_play(1);
      }
      digitalWrite(ledPin1, OFF);
      check = true;
    }
    if ( (currentHour == 8) && (currentMinute == 30) && (currentSecond >= 1 && currentSecond <= 25) ) {
      if (check == true) {
        digitalWrite(ledPin1, ON);
        check = false;
        mp3_play(1);
      }
      digitalWrite(ledPin1, OFF);
      check = true;
    }
    if ( (currentHour == 11) && (currentMinute == 30) && (currentSecond >= 1 && currentSecond <= 25) ) {
      if (check == true) {
        digitalWrite(ledPin2, ON);
        check = false;
        mp3_play(1);
      }
      digitalWrite(ledPin2, OFF);
      check = true;
    }
    if ( (currentHour == 12) && (currentMinute == 30) && (currentSecond >= 1 && currentSecond <= 25) ) {
      if (check == true) {
        digitalWrite(ledPin2, ON);
        check = false;
        mp3_play(1);
      }
      digitalWrite(ledPin2, OFF);
      check = true;
    }
    if ( (currentHour == 15) && (currentMinute == 30) && (currentSecond >= 1 && currentSecond <= 25) ) {
      if (check == true) {
        digitalWrite(ledPin3, ON);
        check = false;
        mp3_play(1);
      }
      digitalWrite(ledPin3, OFF);
      check = true;
    }
    if ( (currentHour == 17) && (currentMinute == 00) && (currentSecond >= 1 && currentSecond <= 25) ) {
      if (check == true) {
        digitalWrite(ledPin3, ON);
        check = false;
        mp3_play(1);
      }
      digitalWrite(ledPin3, OFF);
      check = true;
    }
    if ( (currentHour == 21) && (currentMinute == 00) && (currentSecond >= 1 && currentSecond <= 25) ) {
      if (check == true) {
        digitalWrite(ledPin4, ON);
        check = false;
        mp3_play(1);
      }
      digitalWrite(ledPin4, OFF);
      check = true;
    }
  }
}
