#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define BOARD_LED_PIN 0
#define WHITE_BUTTON_PIN 12
#define WHITE_LED_PIN 14
#define RED_BUTTON_PIN 13
#define RED_LED_PIN 15
#define GREEN_BUTTON_PIN 16
#define GREEN_LED_PIN 2
#define YELLOW_BUTTON_PIN 5
#define YELLOW_LED_PIN 4

const char* ssid = "your_ssid";//Replace with your WiFi network name
const char* password = "your_password";//Replace with your WiFi network password
String rokuHost = "192.168.0.10";//Replace with your Roku's IP address

HTTPClient http;
WiFiClient client;

// button state
bool button_press_current = false;
bool button_press_last = false;

int turn_phase = 0;
String answerer = "";

void setup() {

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  // set board LED as output
  pinMode(BOARD_LED_PIN, OUTPUT);

  // set button pins as an input
  pinMode(WHITE_BUTTON_PIN, INPUT);
  pinMode(RED_BUTTON_PIN, INPUT);
  pinMode(GREEN_BUTTON_PIN, INPUT);
  pinMode(YELLOW_BUTTON_PIN, INPUT);

  // set button LED pins as an output
  pinMode(WHITE_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);

  digitalWrite(WHITE_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(YELLOW_LED_PIN, LOW);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  blink();
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

void blink() {
  digitalWrite(BOARD_LED_PIN, LOW);
  delay(100);
  digitalWrite(BOARD_LED_PIN, HIGH);
}

void loop() {

  while (turn_phase == 0){
    
    if(digitalRead(WHITE_BUTTON_PIN) == LOW){
      Serial.println("white");
      sendCommand("Play");
      delay(500);
      answerer = "white";
      turn_phase = 1;      
      button_press_current = true;
      continue;
      digitalWrite(WHITE_LED_PIN, HIGH);
    }

    if(digitalRead(RED_BUTTON_PIN) == LOW){
      Serial.println("red");
      sendCommand("Play");
      delay(500);
      answerer = "red";
      turn_phase = 1;
      continue;
      button_press_current = true;
      digitalWrite(RED_LED_PIN, HIGH);
    }

    if(digitalRead(GREEN_BUTTON_PIN) == LOW){
      Serial.println("green");
      sendCommand("Play");
      delay(500);
      answerer = "green";
      turn_phase = 1;
      continue;
      button_press_current = true;
      digitalWrite(GREEN_LED_PIN, HIGH);
    }

    if(digitalRead(YELLOW_BUTTON_PIN) == LOW){
      Serial.println("yellow");
      sendCommand("Play");
      delay(500);
      answerer = "yellow";
      turn_phase = 1;
      continue;
      button_press_current = true;
      digitalWrite(YELLOW_LED_PIN, HIGH);
    }

    // return if the value hasn't changed
    if(button_press_current == button_press_last)
      return;
      
    Serial.println(button_press_current);
  
    // store last button state
    button_press_last = button_press_current;
  }

  while (turn_phase == 1){
    int button_LED = 0;
    int button_pin = 0;
    if (answerer == "white"){
      button_LED = WHITE_LED_PIN;
      button_pin = WHITE_BUTTON_PIN;
    }
    if (answerer == "red"){
      button_LED = RED_LED_PIN;
      button_pin = RED_BUTTON_PIN;
    }
    if (answerer == "green"){
      button_LED = GREEN_LED_PIN;
      button_pin = GREEN_BUTTON_PIN;
    }
    if (answerer == "yellow"){
      button_LED = YELLOW_LED_PIN;
      button_pin = YELLOW_BUTTON_PIN;
    }
    digitalWrite(button_LED, HIGH);
    delay(500);
    digitalWrite(button_LED, LOW);
    delay(500);
    digitalWrite(button_LED, HIGH);
    delay(500);
    digitalWrite(button_LED, LOW);
    delay(500);
    if (digitalRead(button_pin) == LOW){
      sendCommand("Play");
      delay(3000);
      turn_phase = 0;
      continue;
    }
    digitalWrite(button_LED, HIGH);
    delay(250);
    digitalWrite(button_LED, LOW);
    delay(250);
    digitalWrite(button_LED, HIGH);
    delay(250);
    digitalWrite(button_LED, LOW);
    delay(250);
    if (digitalRead(button_pin) == LOW){
      sendCommand("Play");
      delay(3000);
      turn_phase = 0;
      continue;
    }
    digitalWrite(button_LED, HIGH);
    delay(250);
    digitalWrite(button_LED, LOW);
    delay(250);
    digitalWrite(button_LED, HIGH);
    delay(250);
    digitalWrite(button_LED, LOW);
    delay(250);
    if (digitalRead(button_pin) == LOW){
      sendCommand("Play");
      delay(3000);
      turn_phase = 0;
      continue;
    }
    digitalWrite(button_LED, HIGH);
    delay(125);
    digitalWrite(button_LED, LOW);
    delay(125);
    digitalWrite(button_LED, HIGH);
    delay(125);
    digitalWrite(button_LED, LOW);
    delay(125);
    digitalWrite(button_LED, HIGH);
    delay(125);
    digitalWrite(button_LED, LOW);
    delay(125);
    digitalWrite(button_LED, HIGH);
    delay(125);
    digitalWrite(button_LED, LOW);
    delay(125);
    if (digitalRead(button_pin) == LOW){
      sendCommand("Play");
      delay(3000);
      turn_phase = 0;
      continue;
    }
    digitalWrite(button_LED, HIGH);
    delay(125);
    digitalWrite(button_LED, LOW);
    delay(125);
    digitalWrite(button_LED, HIGH);
    delay(125);
    digitalWrite(button_LED, LOW);
    delay(125);
    digitalWrite(button_LED, HIGH);
    delay(125);
    digitalWrite(button_LED, LOW);
    delay(125);
    digitalWrite(button_LED, HIGH);
    delay(125);
    digitalWrite(button_LED, LOW);
    delay(125);
    sendCommand("Play");
    delay(1000);
    answerer = "";
    turn_phase = 0;
  }
}

void sendCommand(String command) {
   Serial.println("Sending command " + command);
   blink();
   
   String url = "http://" + rokuHost + ":8060/keypress/" + command;
   http.begin(client, url);
   http.POST("");
   http.end();
   Serial.println("finished sendCommand");
}