
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <WiFiManager.h>


const int reedSwitch = 5; //set reedswitch pin




#define BOTtoken "bottoken"  // add bot token (get from botfather)

#define CHAT_ID "chatid" //chat id of the person or group chat that is receiving the message (get from myidbot)

//initialize the telgram bot
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

void setup() {

  Serial.begin(115200);  //open serial port
  
WiFiManager wm;


pinMode(reedSwitch, INPUT_PULLUP); //set pinmode


  client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // add certificate for api.telegram.org
 bool res;


res = wm.autoConnect("AutoConnectAP","password"); // password protected ap, you can replace the password and ssid

  bot.sendMessage(CHAT_ID, "Bot started up", ""); //send a startup message



}

void loop() {  //sets the value of  the reedSwitch pin at the start as base, and  then checks if anything changed, then acts acordingly
  static int lastval = !digitalRead(reedSwitch);
  int val = digitalRead(reedSwitch);

  if (val != lastval)
  {
    if (val == LOW)
    {
      
      Serial.println("door open");
      bot.sendMessage(CHAT_ID, "The door is open");


    }
    else
    {
      
      Serial.println("door closed");
      bot.sendMessage(CHAT_ID, "The door is closed");
      
    }
    lastval = val;
  }
}
