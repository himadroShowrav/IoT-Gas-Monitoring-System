#define BLYNK_TEMPLATE_ID "TMPL6Sa5FQqdr"
#define BLYNK_TEMPLATE_NAME "Gas Level Monitoring System"
#define BLYNK_AUTH_TOKEN "S7ZpA-3skanVQzFbrQz_UBT37QAKug4S"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>

// Initialize LCD (Try lcd.init() if lcd.begin() does not work for your library)
LiquidCrystal_I2C lcd(0x27, 16, 2);

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "POCO X3 Pro";   // Ensure this matches your hotspot exactly
char pass[] = "0987654321";

BlynkTimer timer;

// --- PIN DEFINITIONS ---
int GasSensor1 = 39; // VN
int GasSensor2 = 36; // VP
int GasSensor3 = 34; // D34

#define GreenLED 15   // D15
#define RedLED 2      // D2
#define Buzzer 4      // D4
#define RelayPin 18   // ADDED: Relay for Exhaust Fan (GPIO 18)

// --- THRESHOLDS (Matched to Report) ---
int sensorThreshold1 = 1400;
int sensorThreshold2 = 350;  // Changed from 400 to match report [cite: 181]
int sensorThreshold3 = 1600;

void sendSensor()
{
  int gasValue1 = analogRead(GasSensor1);
  int gasValue2 = analogRead(GasSensor2);
  int gasValue3 = analogRead(GasSensor3);

  // Send raw data to Blynk Gauges
  Blynk.virtualWrite(V0, gasValue1);
  Blynk.virtualWrite(V1, gasValue2);
  Blynk.virtualWrite(V2, gasValue3);

  Serial.print("S1: "); Serial.print(gasValue1);
  Serial.print(" | S2: "); Serial.print(gasValue2);
  Serial.print(" | S3: "); Serial.println(gasValue3);

  bool alert = false;
  String sensorsHigh = "";

  // Check Sensor 1
  if(gasValue1 > sensorThreshold1) {
    sensorsHigh += "S1 ";
    alert = true;
    Blynk.logEvent("gas_alert", "Sensor 1: Gas High");
  }
  // Check Sensor 2
  if(gasValue2 > sensorThreshold2) {
    sensorsHigh += "S2 ";
    alert = true;
    Blynk.logEvent("gas_alert", "Sensor 2: Gas High");
  }
  // Check Sensor 3
  if(gasValue3 > sensorThreshold3) {
    sensorsHigh += "S3 ";
    alert = true;
    Blynk.logEvent("gas_alert", "Sensor 3: Gas High");
  }

  // --- ALARM LOGIC ---
  if (alert) {
    // 1. Update Hardware
    digitalWrite(GreenLED, LOW);
    digitalWrite(RedLED, HIGH);
    digitalWrite(Buzzer, HIGH);
    digitalWrite(RelayPin, LOW); // Fan ON (Active LOW) [cite: 99]

    // 2. Update LCD
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("High: " + sensorsHigh);
    lcd.setCursor(0,1);
    lcd.print("Fan ON! Risk!");

    // 3. Update Blynk Widgets
    Blynk.virtualWrite(V3, "High: " + sensorsHigh);
    Blynk.virtualWrite(V4, "Exhaust Fan ON");
    Blynk.virtualWrite(V5, 0);   // Green LED Widget OFF
    Blynk.virtualWrite(V6, 255); // Red LED Widget ON
    Blynk.virtualWrite(V7, 255); // Buzzer Widget ON
    Blynk.virtualWrite(V8, 255); // Fan Widget ON

  } else {
    // 1. Update Hardware
    digitalWrite(GreenLED, HIGH);
    digitalWrite(RedLED, LOW);
    digitalWrite(Buzzer, LOW);
    digitalWrite(RelayPin, HIGH); // Fan OFF (Active LOW)

    // 2. Update LCD
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("All Normal");
    lcd.setCursor(0,1);
    // Rotating display of values since they fit better this way
    lcd.print("S1:"); lcd.print(gasValue1);
    lcd.print(" S2:"); lcd.print(gasValue2);

    // 3. Update Blynk Widgets
    Blynk.virtualWrite(V3, "All Normal");
    Blynk.virtualWrite(V4, "Exhaust Fan OFF");
    Blynk.virtualWrite(V5, 255); // Green LED Widget ON
    Blynk.virtualWrite(V6, 0);   // Red LED Widget OFF
    Blynk.virtualWrite(V7, 0);   // Buzzer Widget OFF
    Blynk.virtualWrite(V8, 0);   // Fan Widget OFF
  }
}

void setup()
{
  Serial.begin(115200);

  // Initialize Sensors
  pinMode(GasSensor1, INPUT);
  pinMode(GasSensor2, INPUT);
  pinMode(GasSensor3, INPUT);

  // Initialize Outputs
  pinMode(GreenLED, OUTPUT);
  pinMode(RedLED, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(RelayPin, OUTPUT);
  digitalWrite(RelayPin, HIGH); // Keep Fan OFF initially (Active LOW)

  // Initialize Blynk
  Blynk.begin(auth, ssid, pass);

  // Initialize LCD
  lcd.begin(); // Note: If LCD is blank, try lcd.init();
  lcd.backlight(); // Make sure backlight is on
  lcd.setCursor(3,0);
  lcd.print("Gas System");
  lcd.setCursor(3,1);
  lcd.print("Starting...");
  delay(2000); // Only acceptable delay is here in setup
  lcd.clear();

  // Run function every 1 second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
