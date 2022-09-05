//** START   
 
#include "LiquidCrystal.h"
#include "DLG.h"
#include "BMZ.h"
#include "MICRO.h"
#include "ZEEWAY.h"
#include "PHYLION.h"
#define DISPLAY_ROWS      2
#define PER_SPACE         1
#define KEYPAD_ROWS       4
#define KEYPAD_COLS       4
int a, b, c, d, e, f, g, h, i, j;
// Pin assignments tests :
#define LED_PIN           11
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
void start()
{
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 0);
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    digitalWrite(LED_PIN, LOW);
}
