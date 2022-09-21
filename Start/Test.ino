  /*
    Tableau
      Fusible Décharge HS ou décharge port HS = D < 20 avec DCDC actif
      Fusible charge HS ou charge port HS = C < 20 sans DCDC et C > 3750 avec DCDC
      SI les deux fonction précédents sont vrai, appareil non branché
      Surtension ou mauvais mode choisi = C ou D Supérieur à 4200
      Décharge Profonde = C entre 300 et 3100  avec DCDC actif
      Cellules détruites = C entre 20 et 300 avec DCDC actif
      BMS HS = Valeur C entre 3000 et 4200 et C > D+20 et Valeur D entre 20 et 3000
      BMS HS = Valeur D entre 3000 et 4200 et valeur C entre 20 et < à D-20
      Déséquilibre = Valeur C entre 3100 et 4100 et valeur D entre 20 et 3000
      Déséquilibre = Valeur D entre 3100 et 4100 et valeur C < 3000 sans DCDC
  */
int VCellDechargeDCDC=0;
int VCellChargeDCDC=0;
// Fonction test 
void test(int charge,  int decharge){


  if (VCellDechargeDCDC < 20 && charge < 20 && VCellChargeDCDC > 3750) { // Appareil non branche
    a = 1;
  }
  if (a == 0 && VCellDechargeDCDC < 20) { // Fusible decharge HS ou decharge port HS
    b = 1;
  }
  if (a == 0 && charge < 20 && VCellChargeDCDC > 3750 && decharge > 300) { // Fusible charge HS ou charge port HS
    c = 1;
  }
  if (charge > 4200 || decharge > 4200) { // Surtension ou mauvais mode choisi
    d = 1;
  }

  if ((VCellChargeDCDC >= 300) && (VCellChargeDCDC <= 3100)) { // Decharge profonde
    e = 1;
  }
  if ((VCellChargeDCDC >= 20) && (VCellChargeDCDC <= 300)) { // Cellules detruites
    f = 1;
  }
  if (((charge >= 3000) && (charge <= 4200)) && (charge > decharge + 20) && ((decharge >= 20) && (decharge <= 3000))) { // BMS HS
    g = 1;
  }
  if (((decharge >= 3000) && (decharge <= 4200)) && ((charge >= 20) && (charge <= decharge - 20))) { // BMS HS
    g = 1;
  }
  if (((charge >= 3100) && (charge <= 4100)) && ((decharge >= 20) && (decharge <= 3000))) { // Desiquilibre
    h = 1;
  }


  if (a == 0 && b==0 && c==0 && d==0 && e==0 && f==0 && g==0 && h==0) {
      effacer();
      lcd.setCursor (0, 0);
      lcd.print("Possible");
      lcd.setCursor(0,1);
      lcd.print("Desequilibre");
      delay(1000);
      effacer();
      lcd.setCursor (0, 0);
      lcd.print("Ou manque");
      lcd.setCursor(0,1);
      lcd.print("Capacite ou");
      delay(1000);
      effacer();
      lcd.setCursor (0, 0);
      lcd.print("BMS");
      lcd.setCursor(0,1);
      lcd.print("HS");
      delay(1000);
   }
      if (a == 1) {
      effacer();
      lcd.setCursor (0, 0);
      lcd.print("Appareil non");
      lcd.setCursor(0,1);
      lcd.print("Branche");
      delay(1000);
    }
 
    if (b == 1) {
      effacer();
      lcd.setCursor (0, 0);
      lcd.print("Fusible");
      lcd.setCursor(0,1);
      lcd.print("Decharge");
      delay(1000);
    }

     if (c == 1) {
      effacer();
      lcd.setCursor (0, 0);
      lcd.print("Fusible");
      lcd.setCursor(0,1);
      lcd.print("Decharge");
      delay(1000); 
    }
    
    if (c == 1) {
      effacer();
      lcd.setCursor (0, 0);
      lcd.print("Charge");
      lcd.setCursor(0,1);
      lcd.print("Port");
      delay(1000);
    }
    
     if (d == 1) {
      effacer();
      lcd.setCursor (0, 0);
      lcd.print("Surtension ou");
      lcd.setCursor(0,1);
      lcd.print("Mauvais mode choisi");
      delay(1000);
    }

     if (e == 1) {
      effacer();
      lcd.setCursor (0, 0);
      lcd.print("Decharge");
      lcd.setCursor(0,1);
      lcd.print("Profonde");
      delay(1000);
    }

     if (f == 1) {
      effacer();
      lcd.setCursor (0, 0);
      lcd.print("Cellule");
      lcd.setCursor(0,1);
      lcd.print("Detruite");
      delay(1000);
     
     }
      if (g == 1) {
      effacer();
      lcd.setCursor (0, 0);
      lcd.print("BMS");
      lcd.setCursor(0,1);
      lcd.print("HS");
      delay(1000);
       
    }
    if (h == 1) {
      effacer();
      lcd.setCursor (0, 0);
      lcd.print("Desiquilibre");
      delay(1000);
 
    }

    
 
}
