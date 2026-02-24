#include <LiquidCrystal.h>
#include <HX711.h>
#include <SoftwareSerial.h>

// ================= LCD =================
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// ================= HX711 =================
#define DT   A0
#define SCK  A1
HX711 scale;

// ================= BUTTON =================
#define sw 8

// ================= PIEZO BUZZER =================
#define BUZZER 11

// ================= GSM =================
#define GSM_TX 10   // Arduino TX -> GSM RXD
#define GSM_RX 9    // Arduino RX <- GSM TXD
SoftwareSerial gsm(GSM_RX, GSM_TX);

// ================= VARIABLES =================
float weight = 0.0;
float maxWeight = 100.0;     // Maximum safe boat load (kg)
bool systemOn = false;
bool smsSent = false;       // GSM flag

void sendSMS();

void setup() {

  pinMode(sw, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);

  // -------- LCD INIT --------
  lcd.begin(16, 2);
  lcd.print("Boat Load System");
  lcd.setCursor(0, 1);
  lcd.print("Press Start");

  // -------- HX711 INIT --------
  scale.begin(DT, SCK);
  scale.set_scale(-2280);
  scale.tare();

  // -------- GSM INIT --------
  gsm.begin(9600);
  delay(2000);

  delay(2000);
  lcd.clear();
}

void loop() {

  // ========= START SYSTEM =========
  if (digitalRead(sw) == LOW && !systemOn) {
    systemOn = true;
    smsSent = false;

    lcd.clear();
    lcd.print("Taring Scale");
    lcd.setCursor(0, 1);
    lcd.print("Please Wait");

    scale.tare();
    delay(1500);

    lcd.clear();
    lcd.print("System Ready");
    delay(1000);
    lcd.clear();
  }

  // ========= MAIN SYSTEM =========
  if (systemOn) {

    weight = scale.get_units(5);
    if (weight < 0) weight = 0;

    lcd.setCursor(0, 0);
    lcd.print("Weight: ");
    lcd.print(weight, 1);
    lcd.print("kg   ");

    lcd.setCursor(0, 1);

    // -------- OVERLOAD CHECK --------
    if (weight > maxWeight) {
      lcd.print("!! OVERLOAD !!");
      tone(BUZZER, 2000);

      if (!smsSent) {
        sendSMS();
        smsSent = true;
      }

    } else {
      lcd.print("Status: SAFE    ");
      noTone(BUZZER);
      smsSent = false;
    }

    delay(500);
  }
}

// ================= GSM SMS FUNCTION =================
void sendSMS() {

  gsm.println("AT");
  delay(1000);

  gsm.println("AT+CMGF=1");
  delay(1000);

  gsm.println("AT+CMGS=\"0752889195\"");
  delay(1000);

  gsm.print("ALERT! Boat Overloaded. ");
  gsm.print("Current load: ");
  gsm.print(weight, 1);
  gsm.println(" kg. Reduce load immediately.");

  delay(500);
  gsm.write(26);   // CTRL+Z
  delay(3000);
}
