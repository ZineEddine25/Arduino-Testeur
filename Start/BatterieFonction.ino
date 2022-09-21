// Fonctions test des différents types de batteries  
// Déclaration voltage charge et voltage decharge 
int voltage_charge;
int voltage_decharge;

void Dlg() {
  effacer();
  lcd.setCursor (0, 0);
  lcd.print("Testing DLG...");
  delay(2000);
  // Appelle de la fonction test avec les params
   voltage_charge = charge();
   voltage_decharge = decharge();
   test(voltage_charge*-1,voltage_decharge*-1);
  
}
void Bmz() {
  effacer();
  lcd.setCursor (0, 0);
  lcd.print("Testing BMZ...");
  delay(2000);
  // Appelle de la fonction test avec les params
   voltage_charge = charge();
   voltage_decharge = decharge();
   test(voltage_charge*-1,voltage_decharge*-1);
  
}
void Zeeway() {
  effacer();
  lcd.setCursor (0, 0);
  lcd.print("Testing Zeeway...");
  delay(2000);
  // Appelle de la fonction test avec les params
   voltage_charge = charge();
   voltage_decharge = decharge();
   test(voltage_charge*-1,voltage_decharge*-1);
}

void Phylion() {
  effacer();
  lcd.setCursor (0, 0);
  lcd.print("Testing Phylion...");
  delay(2000);
  // Appelle de la fonction test avec les params
   voltage_charge = charge();
   voltage_decharge = decharge();
   test(voltage_charge*-1,voltage_decharge*-1); 
}
void Etwow(){
  effacer();
  lcd.setCursor (0, 0);
  lcd.print("Testing Etwow...");
  delay(2000);
  // Appelle de la fonction test avec les params
   voltage_charge = charge();
   voltage_decharge = decharge();
   test(voltage_charge*-1,voltage_decharge*-1);
}
void Bafang(){
  effacer();
  lcd.setCursor (0, 0);
  lcd.print("Testing Bafang...");
  delay(2000);
  // Appelle de la fonction test avec les params
   voltage_charge = charge();
   voltage_decharge = decharge();
   test(voltage_charge*-1,voltage_decharge*-1);
}
