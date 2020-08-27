#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#define USE_SERIAL Serial
ESP8266WiFiMulti WiFiMulti;

void setup() {
  USE_SERIAL.begin(9600);
  delay(5000);
  // USE_SERIAL.setDebugOutput(true);
USE_SERIAL.println("on");
  USE_SERIAL.println();
  USE_SERIAL.println();
  USE_SERIAL.println();
USE_SERIAL.println("on  ");
  for (uint8_t t = 4; t > 0; t--) {
    USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
    USE_SERIAL.flush();
    delay(1000);
  }
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("Wlan", "Mot de passe");
}
int endoffile=0;


void loop() {
 if (USE_SERIAL.available()) {
    String c = USE_SERIAL.readString();
    if(c.indexOf("Start")>=0){
      transferdata(c);
}
}
}
int length,httpCode;
String payload,link;
void transferdata(String data){
  

  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    HTTPClient http;
     link="http://thecloud.dx.am/apps/161118/data.php?blabla=";
    link+=data;
    length = link.length()-3;
    link.remove(length, 3);
    http.begin(link); //HTTP
    //Me
    //USE_SERIAL.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    httpCode = http.GET();
    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
     //Me
     //USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);
      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        payload = http.getString();
        //payload.remove(0,1);
        USE_SERIAL.println(payload);
      }
    } else {
      USE_SERIAL.println("error b2");
    }

    http.end();
  }
  
  }


