#include <dht.h>
#include <DS1302.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h> //A4+A5
#include <MQ135.h>
#include <SoftwareSerial.h>
#include <AltSoftSerial.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <string.h>


Time t;
#define DHT22_PIN A1
const int sensorAnalogPin = A0;

const int buttonSet = A2;
const int buttonPlus = A3;
const int buttonMoins = 13;

const int RELAY_T = 2;
const int RELAY_H = 7;
const int RELAY_C = 11;
const int RELAY_cool = 3;
const int RELAY_5 = 12;

dht DHT;
MQ135 gasSensor = MQ135(sensorAnalogPin);
int j = 1, jj = 1;

int chk;
float ppm;
float TEMPERATURE = 37.7;
float TEMPERATUREcool = 42;
float HUMIDITE = 65.0;
float CO2 = 5.2;
float OXIDECARBONE = 5.0;
int   NUMBEROFDAY = 21;
int k = 0;
int BEGAIN = 0;
int FINISH = 1;

struct
{
  uint32_t total;
  uint32_t ok;
  uint32_t crc_error;
  uint32_t time_out;
  uint32_t connect;
  uint32_t ack_l;
  uint32_t ack_h;
  uint32_t unknown;
} stat = { 0, 0, 0, 0, 0, 0, 0, 0};

AltSoftSerial esp;
DS1302 rtc(4, 5, 6);
String data, mq;
float mqf;
void setup()
{
  pinMode(buttonSet, INPUT_PULLUP);
  pinMode(buttonPlus, INPUT_PULLUP);
  pinMode(buttonMoins, INPUT_PULLUP);
  pinMode(RELAY_T, OUTPUT);
  pinMode(RELAY_H, OUTPUT);
  pinMode(RELAY_C, OUTPUT);
  pinMode(RELAY_cool, OUTPUT);
delay(5000);
  //    pinMode(LED_SET, OUTPUT);

  rtc.halt(false);
  rtc.writeProtect(false);
  rtc.setDOW(THURSDAY);

  rtc.setTime(16, 33, 0);
  rtc.setDate(14, 3, 2018);


  esp.begin(9600);
  Serial.begin(9600);
  float rzero = gasSensor.getRZero();
  Serial.print("R0: ");
  Serial.print("\t");
  Serial.println(rzero);  // Valeur à reporter ligne 27 du fichier mq135.h après 48h de préchauffage
  Serial.println();
  Serial.println("status,\t\tHumidity (%),\tTemperature (C),\tCO2 (%),\t\t Date ,\t\t\t Hours, \t\t j, \t\t jj,");

  Wire.begin();
  lcd.begin();
  lcd.backlight();
}
void loop()
{
  chk = DHT.read22(DHT22_PIN);
  ppm = gasSensor.getPPM();
  stat.total++;
  state();
  //   date_time();
  lcd.clear();
  display_data();
  diplay_monotor_data();

  button_state();
  compare_temperature();


  delay(10000);
}

void state(void)
{


  switch (chk)
  {
    case DHTLIB_OK:
      stat.ok++;
      Serial.print("OK,\t");
      break;
    case DHTLIB_ERROR_CHECKSUM:
      stat.crc_error++;
      Serial.print("Checksum error,\t");
      break;
    case DHTLIB_ERROR_TIMEOUT:
      stat.time_out++;
      Serial.print("Time out error,\t");
      break;
    case DHTLIB_ERROR_CONNECT:
      stat.connect++;
      Serial.print("Connect error,\t");
      break;
    case DHTLIB_ERROR_ACK_L:
      stat.ack_l++;
      Serial.print("Ack Low error,\t");
      break;
    case DHTLIB_ERROR_ACK_H:
      stat.ack_h++;
      Serial.print("Ack High error,\t");
      break;
    default:
      stat.unknown++;
      Serial.print("Unknown error,\t");
      break;
  }
}

void display_data(void) {
  //display date
  t = rtc.getTime();
  lcd.print(t.date, DEC);
  lcd.print("/");
  lcd.print(rtc.getMonthStr());
  lcd.print("/");
  lcd.print(t.year, DEC);
  lcd.setCursor ( 0, 1 );
  lcd.print(t.hour, DEC);
  lcd.print(":");
  lcd.print(t.min, DEC);
  lcd.print(":");
  lcd.print(t.sec, DEC);
  delay(1000);
  lcd.clear();
  //display data

  lcd.setCursor(0, 0);
  lcd.print("H:");
  lcd.print(DHT.humidity - 0);
  lcd.print("% ");
  lcd.print("T:");
  lcd.print(DHT.temperature - 1);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("CO2:");
  lcd.print(ppm / 10000, 5);
  lcd.print("%");

}

void diplay_monotor_data(void) {
  t = rtc.getTime();
  Serial.print("\t");
  Serial.print(DHT.humidity - 0, 2);
  Serial.print("\t");
  Serial.print("\t");
  Serial.print("\t");
  Serial.print(DHT.temperature - 1, 2);
  Serial.print("\t");
  Serial.print("\t");
  Serial.print(ppm / 10000, 5);
  Serial.print("\t");
  Serial.print("\t");
  Serial.print(t.year, DEC);
  Serial.print('/');
  Serial.print(rtc.getMonthStr());
  Serial.print('/');
  Serial.print(t.date, DEC);
  Serial.print("\t");
  Serial.print("\t");
  Serial.print(t.hour, DEC);
  Serial.print(':');
  Serial.print(t.min, DEC);
  Serial.print(':');
  Serial.print(t.sec, DEC);
  Serial.print("\t");
  Serial.print("\t");
  Serial.print(j, 1);
  Serial.print("\t");
  Serial.print("\t");
  Serial.print(jj, 1);
  Serial.println();
  mqf = ppm;
  mq = mqf;

  send_data(DHT.temperature, DHT.humidity, mq);
}
/*void date_time(void){
    DateTime now = RTC.now();
    lcd.setCursor(0, 3);
    lcd.print(now.hour(),DEC);
    lcd.setCursor(2, 3);
    lcd.print(':');
    lcd.setCursor(3, 3);
    lcd.print(now.minute(),DEC);

    lcd.setCursor(6, 3);
    lcd.print(now.day(),DEC);
    lcd.setCursor(8, 3);
    lcd.print('/');
    lcd.setCursor(9, 3);
    lcd.print(now.month(),DEC);
    lcd.setCursor(11, 3);
    lcd.print('/');
    lcd.setCursor(12, 3);
    lcd.print(now.year(),DEC);

    if(now.second()>=57){
      jj++;
      if(jj==1440){//86400 pour 24 Heures X 60 minutes X 60 secondes
        j++;
        jj=0;
      }
    }
  }
*/
void display_data_Control(void) {
  Serial.println();
  Serial.print("\t");
  Serial.print("\t");
  Serial.print("\t");
  Serial.print(HUMIDITE, 2);
  Serial.print("\t");
  Serial.print("\t");
  Serial.print("\t");
  Serial.print(TEMPERATURE, 2);
  Serial.print("\t");
  Serial.print("\t");
  Serial.print("\t");
  Serial.print(OXIDECARBONE, 2);
  Serial.print("\t");
  Serial.print("\t");
  Serial.print("\t");
  Serial.print(NUMBEROFDAY);
  Serial.print("\t");
  Serial.print("\t");
  Serial.print("\t");
  Serial.print(BEGAIN, 1);
  Serial.print("\t");
  Serial.print("\t");
  Serial.print("\t");
  Serial.print(FINISH, 1);
  Serial.print("\t");
  Serial.print("\t");
  Serial.print("\t");
  Serial.print(k, 1);
}

void display_data_Control_lcd(void) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("H");
  lcd.setCursor(2, 0);
  lcd.print(HUMIDITE);
  lcd.setCursor(6, 0);
  lcd.print("%");

  lcd.setCursor(9, 0);
  lcd.print("T");
  lcd.setCursor(11, 0);
  lcd.print(TEMPERATURE);
  lcd.setCursor(15, 0);
  lcd.print("C");

  lcd.setCursor(2, 1);
  lcd.print("CO2");
  lcd.setCursor(6, 1);
  lcd.print(OXIDECARBONE);
  lcd.setCursor(12, 1);
  lcd.print("PPM");

  lcd.setCursor(4, 2);
  lcd.print("DAY");
  lcd.setCursor(9, 2);
  lcd.print(NUMBEROFDAY);
}

void display_lcd(void) {
  if (k == 0) {
    lcd.setCursor(9, 0);
    lcd.noBlink();
    delay(100);
    lcd.blink();
    delay(500);
  }
  if (k == 1) {
    lcd.setCursor(0, 0);
    lcd.noBlink();
    delay(100);
    lcd.blink();
    delay(500);
  }
  if (k == 2) {
    lcd.setCursor(1, 1);
    lcd.noBlink();
    delay(100);
    lcd.blink();
    delay(500);
  }
  if (k == 3) {
    lcd.setCursor(3, 2);
    lcd.noBlink();
    delay(100);
    lcd.blink();
    delay(500);
  }
  if (k == 4) {
    lcd.noBlink();
  }
}


void button_state(void) {
  BEGAIN = 0;
  FINISH = 1;
loop_0:
  delay(1000);
  if ((digitalRead(buttonSet) == LOW) && !BEGAIN && FINISH) {
    while (1) {
      display_data_Control_lcd();
      display_lcd();
      display_data_Control();
      //          digitalWrite(LED_SET,LOW);
      BEGAIN = 1;
      FINISH = 1;
loop_1:
      delay(600);
      if (k == 0) {
        while (1) {
          if (digitalRead(buttonPlus) == LOW) {
            delay(500);
            TEMPERATURE = TEMPERATURE + 0.2;
            if (TEMPERATURE > 50.0)TEMPERATURE = 1.0;
            display_data_Control_lcd();
            display_lcd();
            display_data_Control();
          }
          if (digitalRead(buttonMoins) == LOW) {
            delay(500);
            TEMPERATURE = TEMPERATURE - 0.2;
            if (TEMPERATURE < 1.0)TEMPERATURE = 50.0;
            display_data_Control_lcd();
            display_lcd();
            display_data_Control();
          }
          delay(600);
          if ((digitalRead(buttonPlus) == LOW) && (digitalRead(buttonMoins) == LOW)) {
            k = 1;
            goto loop_1;
          }
        }
      }
      delay(600);
      if (k == 1) {
        while (1) {
          display_lcd();
          if (digitalRead(buttonPlus) == LOW) {
            delay(500);
            HUMIDITE = HUMIDITE + 0.2;
            if (HUMIDITE > 100.0)HUMIDITE = 1.0;
            display_data_Control_lcd();
            display_lcd();
            display_data_Control();
          }
          if (digitalRead(buttonMoins) == LOW) {
            delay(500);
            HUMIDITE = HUMIDITE - 0.2;
            if (HUMIDITE < 1.0)HUMIDITE = 100.0;
            display_lcd();
            display_data_Control_lcd();
            display_data_Control();
          }
          delay(600);
          if ((digitalRead(buttonPlus) == LOW) && (digitalRead(buttonMoins) == LOW)) {
            k = 2;
            goto loop_1;
          }
        }
      }
      delay(600);
      if (k == 2) {
        while (1) {
          display_lcd();
          if (digitalRead(buttonPlus) == LOW) {
            delay(500);
            OXIDECARBONE = OXIDECARBONE + 0.01;
            if (OXIDECARBONE > 20.0)OXIDECARBONE = 0.00;
            display_data_Control_lcd();
            display_lcd();
            display_data_Control();
          }
          if (digitalRead(buttonMoins) == LOW) {
            delay(500);
            OXIDECARBONE = OXIDECARBONE - 0.01;
            if (OXIDECARBONE < 0.00)OXIDECARBONE = 20.0;
            display_data_Control_lcd();
            display_lcd();
            display_data_Control();
          }
          delay(600);
          if ((digitalRead(buttonPlus) == LOW) && (digitalRead(buttonMoins) == LOW)) {
            k = 3;
            goto loop_1;
          }
        }
      }
      delay(600);
      if (k == 3) {
        while (1) {
          display_lcd();
          if ((digitalRead(buttonPlus) == LOW) || (digitalRead(buttonMoins) == LOW)) {
            delay(500);
            j = 1;
            display_data_Control_lcd();
            display_lcd();
            display_data_Control();
          }
          delay(600);
          if ((digitalRead(buttonPlus) == LOW) && (digitalRead(buttonMoins) == LOW)) {
            k = 4;
            goto loop_1;
          }
        }
      }
      delay(600);
      if ((digitalRead(buttonSet) == LOW) && BEGAIN && FINISH && k >= 4) {
        //            digitalWrite(LED_SET,LOW);
        k = 0;
        delay(1000);
        goto loop_0;
      }
    }
  }
}
boolean Tstate,Hstate,Coolstate,Co2state;
void compare_temperature(void) {

  if (TEMPERATURE < DHT.temperature){
    Tstate=LOW;
    digitalWrite(RELAY_T, Tstate);
  }
  
  if (TEMPERATURE > DHT.temperature){
    Tstate=HIGH;
    digitalWrite(RELAY_T, Tstate);
  }
  //********************************


  if (TEMPERATUREcool > DHT.temperature){
    Coolstate=LOW;
    digitalWrite(RELAY_cool, Coolstate);
  }

  if (TEMPERATUREcool < DHT.temperature){
    Coolstate=HIGH;
    digitalWrite(RELAY_cool, Coolstate);
  }


  //***********************************
  if (HUMIDITE < DHT.humidity)
  {
    Hstate=LOW;
    digitalWrite(RELAY_H, Hstate);
  }
  if (HUMIDITE > DHT.humidity)
  {
    Hstate=HIGH;
    digitalWrite(RELAY_H, Hstate);
  }
  //********************************

  if (CO2 < mqf)
  {
    Co2state=LOW;
    digitalWrite(RELAY_C, Co2state);
  }
  if (CO2 > mqf)
  {
    Co2state=HIGH;
    digitalWrite(RELAY_C, Co2state);
    delay(2000);
    digitalWrite(RELAY_C,LOW);
  }

  //***********************************
  /*
    if (TEMPERATURE1 > DHT.temperature)
    {
       digitalWrite(RELAY_4,LOW);
    }
    if (TEMPERATURE1 < DHT.temperature)
    {
    digitalWrite(RELAY_4,HIGH);
    }
  */
Serial.println(" ");
  Serial.print("Tr:");
  Serial.print(Tstate);
  Serial.print(" ** Coolr:");
  Serial.print(Coolstate);
   Serial.print(" ** Hr:");
  Serial.print(Hstate);
   Serial.print(" ** Co2r:");
  Serial.print(Co2state);
  Serial.println("");
  
  
  
}


void send_data(float t, float h, String mq) {
  String tempvalue, tempvalue2;
  int nodata = 1;
  int nogooddata = 1;
  int nodataloop= 1;
  while (nogooddata > 0) {
    nogooddata = 1;
    //data="http://www.thecloud.dx.am/apps/1232343/data.php?key=5552525&t=";
    //data+=t;
    data = "Start&t=";
    data += t;
    data += "&h=";
    data += h;
    data += "&mq=";
    data += mq;
    data += "&end=End";
  //  Serial.println(data);
    esp.println(data);

    while (nogooddata == 1) {
     // Serial.print("waiting");
      if (esp.available() != 0) {
        tempvalue = esp.readString();
       // Serial.println("recieved data:");
      //  Serial.print(tempvalue);
        tempvalue2 = getValue(tempvalue, ';', 0);
        if (tempvalue2.indexOf("art")>=0) {
          tempvalue2 = getValue(tempvalue, ';', 1);
          TEMPERATURE = tempvalue2.toFloat();


          tempvalue2 = getValue(tempvalue, ';', 2);
          TEMPERATUREcool = tempvalue2.toFloat();


          tempvalue2 = getValue(tempvalue, ';', 3);
          HUMIDITE = tempvalue2.toFloat();

          tempvalue2 = getValue(tempvalue, ';', 4);
          CO2 = tempvalue2.toFloat();

          tempvalue2 = getValue(tempvalue, ';', 4);
          CO2 = tempvalue2.toFloat();

       /*   Serial.println(" ");
          Serial.print("CO2:");
          Serial.print(CO2);

          Serial.print("--TEMPERATURE: ");
          Serial.print(TEMPERATURE);

          Serial.print("-- HUMIDITE:");
          Serial.print(HUMIDITE);
*/
          if (CO2 > 0.001 && CO2 < 50){
            Serial.println(" ");
            Serial.print("CO2 Rang OK:");
            Serial.println(CO2);
            }
          if (HUMIDITE > 1 && HUMIDITE < 100){
            Serial.print("HUMIDITy Rang OK:");
               Serial.println(HUMIDITE);
            }
          if (TEMPERATURE > 25 && TEMPERATURE < 50){
            Serial.print("TEMPERATURE Rang OK:");
            Serial.println(TEMPERATURE);
            }

          if (CO2 > 0.001 && CO2 < 50 && HUMIDITE > 1 && HUMIDITE < 100 && TEMPERATURE > 20 && TEMPERATURE < 50) {
            nogooddata = 0;
            nodata = 0;
            
            
            
          } else {
            Serial.print("Corrupt data!");
            delay(5000);
          }
        } else {
          nogooddata = 0;
        }
      }
      
      nodata++;
      nodataloop++;
      delay(1);
      if(nodataloop > 4000){
        Serial.println("WIFI ERROR!");
        nodata=0;
        nodataloop=0;
  return("0");

}
if(nodata > 1000){
  nodata=0;
  nogooddata=2;

}
    }

  }
}


String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
