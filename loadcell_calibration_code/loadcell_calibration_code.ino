#include <Arduino.h>
#include "HX711.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <FirebaseESP32.h>

// WiFi credentials
const char* ssid = "Karthick";
const char* password = "12345678";

// Firebase credentials
#define FIREBASE_HOST "https://peanutapp-10c6d-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "AIzaSyBJJ3P7o4o23UemANxWT0jA3cLRWp4zJLw"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;  // DT pin connected to GPIO 4
const int LOADCELL_SCK_PIN = 4;   // SCK pin connected to GPIO 2

// LCD I2C wiring
const int I2C_SDA_PIN = 21;       // SDA pin connected to GPIO 21
const int I2C_SCL_PIN = 22;       // SCL pin connected to GPIO 22
const int I2C_ADDR = 0x26;        // I2C address of the LCD
const int LCD_COLUMNS = 16;       // Number of columns on the LCD
const int LCD_ROWS = 2;           // Number of rows on the LCD

HX711 scale;
LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_ROWS);

// Create a Firebase Data object
FirebaseData firebaseData;

// Create Firebase config and auth objects
FirebaseConfig config;
FirebaseAuth auth;

void setup() {
  Serial.begin(9600);
  Serial.println("HX711 and I2C LCD Demo");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Set Firebase config
  config.host = FIREBASE_HOST;
  config.api_key = FIREBASE_AUTH;

  // Set Firebase authentication
  auth.user.email = "techcrusaders@gmail.com";
  auth.user.password = "12345678";

  // Initialize Firebase
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  // Initialize the HX711
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_offset(82969);  // Set calibration offset
  scale.set_scale(2042.432617);  // Set calibration scale

  // Initialize the LCD
  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
  lcd.init();
  lcd.backlight();

  // Display initial message
  lcd.setCursor(0, 0);
  lcd.print("weight (gram)");
  delay(3000);  // Display welcome message for 2 seconds
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Weight");
}

void loop() {
  // Read weight from the load cell
  float weight = scale.get_units(10);

  // Ensure weight is non-negative
  if (weight < 0) {
    weight = 0.00;
  }

  // Print weight to the serial monitor
  Serial.print("Weight: ");
  Serial.print(weight, 2);
  Serial.println(" grams");

  // Display weight on the LCD
  lcd.setCursor(0, 1);
  lcd.print("                "); // Clear previous value
  lcd.setCursor(0, 1);
  lcd.print(weight, 2);
  lcd.print(" grams");

  // Prepare JSON data
  String path = "/demo";
  FirebaseJson json;
  json.set("weight2", weight);

  // Send data to Firebase
  if (Firebase.updateNode(firebaseData, path, json)) {
    Serial.println("Data updated successfully");
  } else {
    Serial.println("Failed to update data");
    Serial.println("REASON: " + firebaseData.errorReason());
  }

  delay(1000);  // Read every second
}
