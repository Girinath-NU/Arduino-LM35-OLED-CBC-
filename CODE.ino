#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>

// === OLED Setup ===
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// === LM35 Setup ===
#define LM35_PIN 34c:\Users\HP\OneDrive\Desktop\f
float previousTemp = 25.0;

// === Buzzer Setup ===
#define BUZZER_PIN 27  // GPIO pin connected to the buzzer

// === Wi-Fi Credentials ===
const char* ssid = "Asw_S";        // Your SSID
const char* password = "There is no password";  // Your Wi-Fi password

void setup() {
  Serial.begin(115200);
  
  // OLED init
  Wire.begin(21, 22);  // Ensure these pins are correct for your ESP32 wiring
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED initialization failed! Check wiring.");
    for (;;);  // Halt execution if OLED fails
  }

  Serial.println("OLED initialized.");
  
  // Initialize buzzer pin
  pinMode(BUZZER_PIN, OUTPUT);

  // Initialize Wi-Fi connection
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Print IP address to Serial Monitor
  Serial.println("\nWiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());  // Print IP address in serial monitor

  // Initial message on OLED
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Starting...");
  display.display();
  delay(1000);
}

void loop() {
  // === Read Temperature ===
  int adcValue = analogRead(LM35_PIN);
  float voltage = adcValue * (3.3 / 4095.0);
  float currentTemp = voltage * 100.0;

  // Filter glitches
  if (currentTemp > 0 && abs(currentTemp - previousTemp) < 10) {
    previousTemp = currentTemp;
  } else {
    currentTemp = previousTemp;
  }

  // === OLED Display (Formatted) ===
  display.clearDisplay();
  display.setTextSize(2);  // Larger font size for temperature
  display.setCursor(0, 10);
  display.print("Temp: ");
  display.print(currentTemp, 1);
  display.println(" C");

  // Display a message based on temperature threshold
  if (currentTemp > 26) {
    display.setTextSize(1);  // Smaller font size for warning
    display.setCursor(0, 40);
    display.println("Warning! High Temp!");

    // Activate buzzer
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    // Deactivate buzzer if temperature is below threshold
    digitalWrite(BUZZER_PIN, LOW);
  }

  // Display the update on OLED
  display.display();

  delay(1000);  // Update every second
}
