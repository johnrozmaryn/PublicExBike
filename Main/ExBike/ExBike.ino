
#include <WiFi.h>
#include <ESPmDNS.h>
const char* MyHostName = "bike";
const char* ssid = "NunYa";
const char* password = "NunYa";

// set webserver port
WiFiServer server(80);

//HTTP request variable
String header;

int targetMotorPos = 1;

//Time variables
unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;

//Motor Output Stuff
const int motorPlusPin = 23;
const int motorMinusPin = 13;
const int sensorPin = 34;

const int positionTolerance = 1;   
//Looks like the highest I want to go is 440
//Lowest might be 50 or so? 80? Dunno. It reads zero for a long time, but not so stable.


int posArray[21] = {50, 60, 80, 100, 120, 140, 160, 180, 200, 220, 240, 260, 280, 300, 320, 340, 360, 380, 400, 420, 440};


//Sensor Input Stuff
const int potPin = 34;
const int readDelay = 5;
int reportedPos = 0;
int potValue1 = 0;
int potValue2 = 0;
int potValue3 = 0;
int potValue4 = 0;
int potValue5 = 0;
const int motorDelay = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
  WiFi.setHostname(MyHostName);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  MDNS.begin("ExBike");
  Serial.println("gave it a name");

  server.begin();
  Serial.println("started a server");

  //motor and sensor stuff
  analogReadResolution(9);
  pinMode(motorPlusPin, OUTPUT);
  pinMode(motorMinusPin, OUTPUT);
  digitalWrite(motorPlusPin, LOW);
  digitalWrite(motorMinusPin, LOW);
  Serial.println("moving to zero");
  moveToPos(posArray[0]);

}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = server.available(); // Listen for incoming clients

  if (client) {                 //if a new client connects
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client");
    String currentline = "";  //make a string to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();
      if (client.available()){
        char c = client.read();
        Serial.write(c);
        header += c;
        if (c == '\n') {
          if (currentline.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            if (header.indexOf("GET /01") >= 0 ){
              targetMotorPos = 1;
            } else if (header.indexOf("GET /02") >= 0 ){
              targetMotorPos = 2;
            } else if (header.indexOf("GET /03") >= 0 ){
              targetMotorPos = 3;
            } else if (header.indexOf("GET /04") >= 0 ){
              targetMotorPos = 4;
            } else if (header.indexOf("GET /05") >= 0 ){
              targetMotorPos = 5;
            } else if (header.indexOf("GET /06") >= 0 ){
              targetMotorPos = 6;
            } else if (header.indexOf("GET /07") >= 0 ){
              targetMotorPos = 7;
            } else if (header.indexOf("GET /08") >= 0 ){
              targetMotorPos = 8;
            } else if (header.indexOf("GET /09") >= 0 ){
              targetMotorPos = 9;
            } else if (header.indexOf("GET /10") >= 0 ){
              targetMotorPos = 10;
            } else if (header.indexOf("GET /11") >= 0 ){
              targetMotorPos = 11;
            } else if (header.indexOf("GET /12") >= 0 ){
              targetMotorPos = 12;
            } else if (header.indexOf("GET /13") >= 0 ){
              targetMotorPos = 13;
            } else if (header.indexOf("GET /14") >= 0 ){
              targetMotorPos = 14;
            } else if (header.indexOf("GET /15") >= 0 ){
              targetMotorPos = 15;
            } else if (header.indexOf("GET /16") >= 0 ){
              targetMotorPos = 16;
            } else if (header.indexOf("GET /17") >= 0 ){
              targetMotorPos = 17;
            } else if (header.indexOf("GET /18") >= 0 ){
              targetMotorPos = 18;
            } else if (header.indexOf("GET /19") >= 0 ){
              targetMotorPos = 19;
            } else if (header.indexOf("GET /20") >= 0 ){
              targetMotorPos = 20;
            }
            moveToPos(posArray[targetMotorPos]);  


    
            client.println("<!DOCTYPE html><html>");
            client.println("<head>");
            client.println("  <title>4x5 Grid of Buttons</title>");
            client.println("  <style>");
            client.println("    button {");
            client.println("      width: 100px;");
            client.println("      height: 100px;");
            client.println("      margin: 5px;");
            client.println("      font-size: 30px;");
            client.println("    }");
            client.println("  </style>");
            client.println("</head>");
            client.print("<h2> Current Resistance:  ");
            client.print(String(targetMotorPos));
            client.println("</h2>");
            client.println("  <div>");
            client.println("    <button><a href=\"/01\"> 1</button>");
            client.println("    <button><a href=\"/02\">2</button>");
            client.println("    <button><a href=\"/03\">3</button>");
            client.println("    <button><a href=\"/04\">4</button>");
            client.println("  </div>");
            client.println("  <div>");
            client.println("<button><a href=\"/05\">5</button>");
            client.println("    <button><a href=\"/06\">6</button>");
            client.println("    <button><a href=\"/07\">7</button>");
            client.println("    <button><a href=\"/08\">8</button>");
            client.println("  </div>");
            client.println("  <div>");
            client.println("    <button><a href=\"/09\">9</button>");
            client.println("    <button><a href=\"/10\">10</button>");
            client.println("    <button><a href=\"/11\">11</button>");
            client.println("    <button><a href=\"/12\">12</button>");
            client.println("  </div>");
            client.println("  <div>");
            client.println("    <button><a href=\"/13\">13</button>");
            client.println("    <button><a href=\"/14\">14</button>");
            client.println("    <button><a href=\"/15\">15</button> ");
            client.println("<button><a href=\"/16\">16</button>");
            client.println("  </div>");
            client.println("  <div>");
            client.println("    <button><a href=\"/17\">17</button>");
            client.println("    <button><a href=\"/18\">18</button>");
            client.println("    <button><a href=\"/19\">19</button>");
            client.println("    <button><a href=\"/20\">20</button>");
            client.println("  </div>");
            client.println("</body>");
            client.println("</html>");
            client.println();

            break;
          } else {  //if you got a newline, then clear currentLine
            currentline = "";
          }
        } else if (c != '\r') {    // if you got anything but a carriage return
          currentline += c;        //add it to the end of the currentLine  
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

int readPos() {
  potValue1 = analogRead(potPin);
  delay(readDelay);
  potValue2 = analogRead(potPin);
  delay(readDelay);
  potValue3 = analogRead(potPin);
  delay(readDelay);
  potValue4 = analogRead(potPin);
  delay(readDelay);
  potValue5 = analogRead(potPin);

  reportedPos = potValue1 + potValue2 + potValue3 + potValue4 + potValue5;
  reportedPos = reportedPos / 5;
  Serial.print("Reported Pos: ");
  Serial.println(reportedPos);
  return reportedPos;

}
void moveToPos(int targetPosition) {
  Serial.print("Moving to:");
  Serial.println(targetPosition);
  int currentPos = 0;
  bool atPos = false;
  while(!atPos){
    currentPos = readPos();
    if (abs(currentPos - targetPosition) <= positionTolerance) {
     //We're where we want to be, so pulse both high momentarily then turn off
      digitalWrite(motorPlusPin, HIGH);
      digitalWrite(motorMinusPin, HIGH);
      delay(2);
      digitalWrite(motorPlusPin, LOW);
      digitalWrite(motorMinusPin, LOW);
      atPos = true;  
      Serial.println("made it");
    }
    else {
      if (currentPos < targetPosition) {
        digitalWrite(motorMinusPin, LOW);
        digitalWrite(motorPlusPin, HIGH);
        Serial.println("adding");
        delay(motorDelay);
      }
      else {
        digitalWrite(motorPlusPin, LOW);
        digitalWrite(motorMinusPin, HIGH);
        Serial.println("subtracting");
        delay(motorDelay);
      }
    }
  }

}
