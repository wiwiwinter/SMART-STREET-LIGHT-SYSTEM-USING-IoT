#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <NewPing.h>

// OLED SETTINGS
#define SCREEN_WIDTH 128   // OLED display width, in pixels
#define SCREEN_HEIGHT 32   // OLED display height, in pixels
#define OLED_RESET -1      // Reset pin # (or -1 if sharing Arduino reset pin)

// HC-SR04 PINS
#define TRIGGER_PIN 6
#define ECHO_PIN 7
#define MAX_DISTANCE 400   // Maximum distance we want to ping for (in centimeters)
#define HIGH_THRESHOLD 15  // High light threshold distance in centimeters

// RGB LED PINS
#define RED_PIN 9    // Red pin of RGB LED
#define GREEN_PIN 10 // Green pin of RGB LED
#define BLUE_PIN 11  // Blue pin of RGB LED

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // OLED display object
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // Ultrasonic sensor object
Adafruit_MLX90614 mlx = Adafruit_MLX90614(); // Infrared thermometer object

#define SSID "PLDTHOMEFIBR611a8"
#define PASS "PLDTWIFIkuus6"
#define IP "184.106.153.149"
String msg = "GET /update?key=BZ5IOPCZGDDE4FCU"; // Replace with your actual API key

float temp;
float distance;
int error;
int redValue = 0;
int greenValue = 0;
int blueValue = 0;
String ledColor;
boolean displayNeedsUpdate = false;

unsigned long previousMillis = 0;
const long interval = 500; // Interval between updates in milliseconds
unsigned long previousThingSpeakMillis = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("AT");
  if (Serial.find("OK")) {
    connectWiFi();
  }
  mlx.begin();

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Start the OLED display
  display.clearDisplay();
  display.display();
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    readData();
    updateLed();
    if (displayNeedsUpdate) {
      updateDisplay();
      displayNeedsUpdate = false;
    }
  }

  // Check if 5 seconds have elapsed since the last ThingSpeak update
  if (currentMillis - previousThingSpeakMillis >= 5000) {
    previousThingSpeakMillis = currentMillis;
    updateThingSpeak();
  }
}

void readData() {
  temp = mlx.readObjectTempC();
  distance = readDistance();
}

void updateLed() {
 // Determine brightness of LED based on distance
  int brightness;
  if (distance <= HIGH_THRESHOLD) {
    brightness = map(distance, 0, HIGH_THRESHOLD, 255, 250); // High brightness
  } else {
    brightness = map(distance, HIGH_THRESHOLD, MAX_DISTANCE, 30, 10); // Low brightness
  }

  // Default LED color values
  redValue = 0;
  greenValue = 0;
  blueValue = 0;
  
  // Determine color of LED based on object temperature
  if (temp >= 42) { // Warm temperature
    ledColor = "Red";
    redValue = brightness;
  } else if (temp >= 38) { // Cold temperature
    ledColor = "Blue";
    blueValue = brightness;
  } else if (temp >= 32) {
    ledColor = "White";
    redValue = brightness;
    greenValue = brightness;
    blueValue = brightness;
  } else if (temp >= 25) {
    ledColor = "Orange";
    redValue = brightness / 2;
    greenValue = brightness;
  }

  displayNeedsUpdate = true; // Flag to indicate OLED display needs updating
}

void updateDisplay() {
  // Determine light emission strength based on distance
  String lightStrength;
  if (distance <= HIGH_THRESHOLD) {
    lightStrength = "High";
  } else {
    lightStrength = "Low";
  }

  setColor(redValue, greenValue, blueValue);

  // Display light strength, object temperature, and LED color on OLED display
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Light: ");
  display.println(lightStrength);

  display.print("LED Color: ");
  display.println(ledColor);

  display.print("Object Temp: ");
  display.print(temp); // Changed from objectTemperature to temp
  display.println(" C");

  display.print("Distance: ");
  display.print(distance);
  display.println(" cm");
  display.display();
}

void updateThingSpeak() {
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += IP;
  cmd += "\",80";
  Serial.println(cmd);
  if (Serial.find("Error")) {
    return;
  }
  cmd = msg;
  cmd += "&field1=";
  cmd += String(temp);
  cmd += "&field2=";
  cmd += String(distance);
  cmd += "\r\n";
  Serial.print("AT+CIPSEND=");
  Serial.println(cmd.length());
  if (Serial.find(">")) {
    Serial.print(cmd);
  } else {
    Serial.println("AT+CIPCLOSE");
    error = 1;
  }
}

boolean connectWiFi() {
  Serial.println("AT+CWMODE=1");
  delay(200);
  String cmd = "AT+CWJAP=\"";
  cmd += SSID;
  cmd += "\",\"";
  cmd += PASS;
  cmd += "\"";
  Serial.println(cmd);
  delay(500);
  if (Serial.find("OK")) {
    return true;
  } else {
    return false;
  }
}

float readDistance() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  float duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2; // Convert to centimeters
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(RED_PIN, redValue);
  analogWrite(GREEN_PIN, greenValue);
  analogWrite(BLUE_PIN, blueValue);
}