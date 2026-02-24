#include <LiquidCrystal.h>
#include <HX711.h>

// ================= LCD =================
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// ================= HX711 =================
#define DT   A0
#define SCK  A1
HX711 scale;

// ================= BUTTON =================
#define sw 8

// ================= VARIABLES =================
float weight = 0.0;
float maxWeight = 100.0;     // Maximum safe boat load (kg)
bool systemOn = false;

void setup() {

  pinMode(sw, INPUT_PULLUP);

  // -------- LCD INIT --------
  lcd.begin(16, 2);
  lcd.print("Boat Load System");
  lcd.setCursor(0, 1);
  lcd.print("Press Start");

  // -------- HX711 INIT --------
  scale.begin(DT, SCK);
  scale.set_scale(-2280);
  scale.tare();

  delay(2000);
  lcd.clear();
}

void loop() {

  // ========= START SYSTEM =========
  if (digitalRead(sw) == LOW && !systemOn) {
    systemOn = true;

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
    } else {
      lcd.print("Status: SAFE    ");
    }

    delay(500);
  }
}
