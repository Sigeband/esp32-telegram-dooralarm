
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>



const int reedSwitch = 5; //set 


const char* ssid = "yourwifissid"; // add your wifi ssid
const char* password = "yourwifipassword";  //add your wifi password


#define BOTtoken "yourtoken"  // add bot token (get from botfather)

#define CHAT_ID "chatid" //chat id of the person or group chat that is receiving the message (get from myidbot)

//initialize the telgram bot
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

void setup() {

  Serial.begin(115200);  //open serial port

pinMode(reedSwitch, INPUT_PULLUP); //set pinmode

 // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);  //set wifi to station mode
  WiFi.begin(ssid,password); //connect to wifi
  WiFi.mode(WIFI_STA); 
  delay(5000); 
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // add certificate for api.telegram.org
  while (WiFi.status() != WL_CONNECTED) { //debugging
    delay(500);
    Serial.print(".");
    WiFi.status();
  }
  Serial.println("");
  Serial.println("WiFi connected");  

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
