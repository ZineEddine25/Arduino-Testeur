// MENU & ADS CONFIG & DCDC
bool isKeyDisabled = false;
#include "ADS1X15.h"
ADS1115 ADS(0x48);   
const int Dcdc = 5;
unsigned char selected = 1;
unsigned char prev_key; 
char buttonPressed = '0';
char lastButtonState = '0';
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 100; 
// ##################################################################################### Config menu 
unsigned long checkButtonTaskTimer = 0;
const unsigned long checkButtonTaskInterval = 300;
unsigned long updateLCDTaskTimer = 0;
const unsigned long updateLCDTaskInterval = 400;
unsigned long blinkLEDTaskTimer = 0;
const unsigned long blinkLEDTaskInterval = 500;
// ##################################################################################### Config menu 
typedef const struct MenuStructure
{
  const char *text;
  unsigned char num_menupoints;
  unsigned char up;
  unsigned char down;
  unsigned char enter;
  void (*fp) (void);
} MenuEntry;
char myChar;
// #####################################################################################
const PROGMEM char menu_000[] = "Menu:                      "; // 0
const PROGMEM char menu_001[] = "  1 DLG       ";              // 1
const PROGMEM char menu_002[] = "  2 BMZ       ";              // 2 
const PROGMEM char menu_003[] = "  3 ZEEWAY    ";              // 3
const PROGMEM char menu_004[] = "  4 ETWOW     ";              // 4
const PROGMEM char menu_005[] = "  5 PHYLION     ";            // 5
// #####################################################################################
const PROGMEM char menu_100[] = " DLG            ";            // 10
const PROGMEM char menu_101[] = " 1. C8077708    ";            // 11
const PROGMEM char menu_102[] = " 2. C8707660    ";            // 12
const PROGMEM char menu_103[] = " 3. C8707678    ";            // 13
const PROGMEM char menu_104[] = " 4. C8707704    ";            // 14
const PROGMEM char menu_105[] = " 5. C8707705    ";            // 15
const PROGMEM char menu_106[] = " 6. C8707706    ";            // 16
const PROGMEM char menu_107[] = " 7. C8707707    ";            // 17
const PROGMEM char menu_108[] = " 8. C8707708    ";            // 18
const PROGMEM char menu_109[] = " 9. C8707781-N  ";            // 19
const PROGMEM char menu_110[] = " 10. C8707781-N2";            // 20
const PROGMEM char menu_111[] = " 11. C8707948-N ";            // 21
const PROGMEM char menu_112[] = " 12. D36145C2   ";            // 21
const PROGMEM char menu_113[] = "  Return        ";            // 22
// #####################################################################################
const PROGMEM char menu_200[] = "  BMZ             ";   // 23
const PROGMEM char menu_201[] = " 1. C8707437      ";   // 24
const PROGMEM char menu_202[] = " 2. C8707468      ";   // 25
const PROGMEM char menu_203[] = " 3. C8707471      ";   // 26
const PROGMEM char menu_204[] = " 4. C8707543      ";   // 27
const PROGMEM char menu_205[] = " 5. C8707554      ";   // 28
const PROGMEM char menu_206[] = " 6. C8707555      ";   // 29
const PROGMEM char menu_207[] = " 7. C8707575      ";   // 30
const PROGMEM char menu_208[] = " 8. C8707586      ";   // 31
const PROGMEM char menu_209[] = " 9. C8707587      ";   // 32
const PROGMEM char menu_210[] = " 10. C8707588     ";   // 33
const PROGMEM char menu_211[] = " 11. C8707589     ";   // 34
const PROGMEM char menu_212[] = " 12. C8707590     ";   // 35
const PROGMEM char menu_213[] = " 13. C8707591     ";   // 36
const PROGMEM char menu_214[] = " 14. C8707616     ";   // 37
const PROGMEM char menu_215[] = " 15. C8707628     ";   // 38
const PROGMEM char menu_216[] = " 16. C8707662     ";   // 39
const PROGMEM char menu_217[] = " 17. C8707663     ";   // 40
const PROGMEM char menu_218[] = " 18. C8707664     ";   // 41
const PROGMEM char menu_219[] = " 19. C8707688     ";   // 42
const PROGMEM char menu_220[] = " 20. C8707689     ";   // 43
const PROGMEM char menu_221[] = " 21. C8707690     ";   // 44
const PROGMEM char menu_222[] = " 22. C8707691     ";   // 45
const PROGMEM char menu_223[] = " 23. C8707692     ";   // 46
const PROGMEM char menu_224[] = " 24. C8707695     ";   // 47
const PROGMEM char menu_225[] = " 25. C8707697     ";   // 48
const PROGMEM char menu_226[] = "  Return          ";   // 49
// #####################################################################################
const PROGMEM char menu_300[] = "ZEEWAY             ";   // 50
const PROGMEM char menu_301[] = " 1. ZE722301       ";   // 51
const PROGMEM char menu_302[] = "  Return           ";   // 52
// #####################################################################################
const PROGMEM char menu_400[] = "ETWOW               ";       // 53 -> 50
const PROGMEM char menu_401[] = " 1. 48V 10.4Ah      ";       // 54
const PROGMEM char menu_402[] = " 2. 36V 8.7Ah       ";       // 55
const PROGMEM char menu_403[] = " 3. 52V 13Ah        ";       // 56
const PROGMEM char menu_404[] = " 4. 36V 10,5Ah      ";       // 57
const PROGMEM char menu_405[] = " 5. 24V 6,5Ah       ";       // 58
const PROGMEM char menu_406[] = " 6. 33V 8,5Ah       ";       // 59
const PROGMEM char menu_407[] = " 7. 36V 7,5Ah       ";       // 60
const PROGMEM char menu_408[] = " 8. 36V 7,5Ah       ";       // 61
const PROGMEM char menu_409[] = " 9. Poli 33V 6.5Ah       ";  // 62
const PROGMEM char menu_410[] = " 10.33V 6.5Ah       ";       // 63
const PROGMEM char menu_411[] = " 11.36V 7.5Ah      ";        // 64
const PROGMEM char menu_412[] = "  Return            ";       // 67
// #####################################################################################
const PROGMEM char menu_500[] = "PHYLION                  ";       // 53 -> 50
const PROGMEM char menu_501[] = " 1. BN-11 36V 14Ah       ";       // 54
const PROGMEM char menu_502[] = " 2. Condor 36V 5,8Ah     ";       // 55
const PROGMEM char menu_503[] = " 3. Falcon 36V 2,5Ah     ";       // 56
const PROGMEM char menu_504[] = " 4. C8707724             ";       // 57
const PROGMEM char menu_505[] = " 5. JCEB360              ";       // 58
const PROGMEM char menu_506[] = " 6. DT-12 CANBUS         ";       // 59
const PROGMEM char menu_507[] = " 7. SR-11 CAN            ";       // 60
const PROGMEM char menu_508[] = " 8. SR-20                ";       // 61
const PROGMEM char menu_509[] = " 9. SF-03                ";       // 62
const PROGMEM char menu_510[] = " 10.SR-20                ";       // 63
const PROGMEM char menu_511[] = " 11.BN-18                ";       // 64
const PROGMEM char menu_512[] = " 12.SF-03                ";       // 67
const PROGMEM char menu_513[] = " 13.BN-18                ";       // 68
const PROGMEM char menu_514[] = " 14.DT-12-UART           ";       // 69
const PROGMEM char menu_515[] = " 15.DT-12 CANBUS         ";       // 70
const PROGMEM char menu_516[] = "  Return            ";            // 71
// #####################################################################################

/*
const PROGMEM char menu_517[] = "Ninebot                            ";    // 72  
const PROGMEM char menu_518[] = " 1. Tube ES2 36V 5.2Ah 187Wh       ";    // 73
const PROGMEM char menu_519[] = " 2. Xiaomi M365 36V 7.8Ah 280Wh    ";    // 74
const PROGMEM char menu_519[] = " 3. NEB1002-H 36V 5.2 187Wh    ";        // 75
const PROGMEM char menu_519[] = " 4. NEE1006-M1 36V 15.3Ah 551Wh    ";    // 76
const PROGMEM char menu_520[] = "  Return          ";                     // 77*/
/*
// #####################################################################################
  
const PROGMEM char menu_521[] = "Greenway          ";                         // 76
const PROGMEM char menu_522[] = " 1. ZZ6501005 CAN ";                         // 77
const PROGMEM char menu_523[] = " 2. ZZ6501005 UART";                         // 78
const PROGMEM char menu_524[] = " 3. Greenway Li-ion 36V ";                   // 79
const PROGMEM char menu_525[] = " 4. Li-ion 36V 19.2Ah";                      // 80
const PROGMEM char menu_526[] = " 5. Greenway Li-ion 36V.17,4Ah ";            // 81    
const PROGMEM char menu_527[] = " 6. ZZ1221004 36V 14.5Ah 374.4Wh";           // 82
const PROGMEM char menu_528[] = " 7. ZZ1221004 36V 14.5Ah 374.4Wh";           // 83
const PROGMEM char menu_529[] = " 8. ZZ1221004 36V 14.5Ah 374.4Wh";           // 84
const PROGMEM char menu_530[] = " 9. ZZ1221004 36V 14.5Ah 374.4Wh";           // 85
const PROGMEM char menu_531[] = " 10. ZZ1221004 36V 14.5Ah 374.4Wh";          // 86
const PROGMEM char menu_532[] = " 11. ZZ1221004 36V 14.5Ah 374.4Wh";          // 87
const PROGMEM char menu_533[] = " 12. ZZ1221004 36V 14.5Ah 374.4Wh";          // 88
const PROGMEM char menu_534[] = " 13. ZZ1221004 36V 14.5Ah 374.4Wh";          // 89
const PROGMEM char menu_535[] = " 14. YJ391006 Enviado 36V 17.4Ah 626.4";     // 90
const PROGMEM char menu_536[] = " 15. ZZ3031004 36V 10.4Ah 374.4Wh";          // 91
const PROGMEM char menu_537[] = " 15. C8707694 36V 14.5Ah 522Wh";             // 92
const PROGMEM char menu_538[] = " 16. C8707693 36V 10.4Ah 374.4Wh";           // 93
const PROGMEM char menu_539[] = " 16. C8707694 36V 14.5Ah 522Wh";             // 94
const PROGMEM char menu_540[] = " 17. C8707694 36V 14.5Ah 522Wh";             // 95
const PROGMEM char menu_541[] = "  Return          ";                         // 96
*/
// #####################################################################################
/*   
const PROGMEM char menu_521[] = "NIU          ";                              // 76
const PROGMEM char menu_522[] = " 1. NQisport 60V 29Ah 1740Wh ";              // 77
const PROGMEM char menu_523[] = " 2. NiuEnergy 60v 26ah 1560 Wh ";            // 78
const PROGMEM char menu_524[] = " 3. 17101SR18/35T-32 60V 32Ah 1920Wh ";      // 79
const PROGMEM char menu_525[] = " 4. NIU energy 7201 26ah 72v 1872wh";        // 80
const PROGMEM char menu_526[] = " 5. MQi GT 48V 31Ah 1488Wh ";                // 81    
const PROGMEM char menu_527[] = " 6. NGT 60V 35Ah 2100Wh";                    // 82
const PROGMEM char menu_528[] = " 7. Mpro 48V 26Ah 1248Wh";                   // 83
const PROGMEM char menu_529[] = " 8. NiuEnergy 60v 26ah 1560 Wh ";            // 84
const PROGMEM char menu_530[] = " 9. 17101SR18/65A-29 60V 29Ah 1740Wh";       // 85
const PROGMEM char menu_531[] = " 10. NiuEnergy 60v 26ah 1560 wh";            // 86
const PROGMEM char menu_532[] = " 11. NCargo 60V 35Ah 2100Wh";                // 87
const PROGMEM char menu_533[] = " 12. NCargo 60V 35Ah 2100Wh";                // 88
const PROGMEM char menu_534[] = " 13. Mpro 48V 32Ah 1536Wh";                  // 89
const PROGMEM char menu_535[] = " 14. YJ391006 Enviado 36V 17.4Ah 626.4";     // 90
const PROGMEM char menu_536[] = " 15. NGT 60V 35Ah 2100Wh";                   // 91
const PROGMEM char menu_537[] = " 15. M-Series 48V 42Ah 2100Wh ";             // 92
const PROGMEM char menu_538[] = " 16. Mpro 48V 32Ah 1536Wh";                  // 93
const PROGMEM char menu_541[] = "  Return          ";                         // 96
*/
// #####################################################################################
/*
const PROGMEM char menu_521[] = "TWS          ";                                  // 76
const PROGMEM char menu_522[] = " 1. TWS 14 INR22/71-7 50.8V 35ah 1778wh ";       // 77
const PROGMEM char menu_541[] = "  Return          ";                             // 96
*/
// #####################################################################################
/*
const PROGMEM char menu_521[] = "ZERO          ";                                 // 76
const PROGMEM char menu_522[] = " 1. Z 48V 10.4Ah 499Wh  ";                       // 77
const PROGMEM char menu_541[] = " 2. Z 60V 21Ah 1260Wh   ";                       // 96
const PROGMEM char menu_521[] = " 3. Z 48V 16Ah 768Wh    ";                       // 76
const PROGMEM char menu_522[] = " 4. Z 48V 10.4Ah 499Wh  ";                       // 77
const PROGMEM char menu_541[] = " 5. Z 52V 23Ah 1196Wh   ";                       // 96
const PROGMEM char menu_521[] = " 6. Z 52V 13Ah 676Wh    ";                       // 76
const PROGMEM char menu_521[] = " 7. Z 52V 12.8Ah 666Wh  ";                       // 76
const PROGMEM char menu_521[] = " 6. Z 52V 13Ah 676Wh    ";                       // 76
const PROGMEM char menu_522[] = " 7. Z 52V 18.2Ah 946.4Wh";                       // 77
const PROGMEM char menu_541[] = "  Return          ";                             // 96
*/

// #####################################################################################
/*
const PROGMEM char menu_521[] = "E-Scape+          ";                             // 76
const PROGMEM char menu_522[] = " 1. E-Scape+ 400203 36V 13Ah 468Wh  ";           // 77
const PROGMEM char menu_541[] = " 2. E-Scape 400200 36V 10.4Ah 374.4Wh   ";       // 96
const PROGMEM char menu_521[] = " 3. E-Nik 36V 7.8Ah 280.8Wh    ";                // 76
const PROGMEM char menu_522[] = " 4. Z 48V 10.4Ah 499Wh  ";                       // 77
const PROGMEM char menu_541[] = " 5. Z 52V 23Ah 1196Wh   ";                       // 96
const PROGMEM char menu_521[] = " 6. Z 52V 13Ah 676Wh    ";                       // 76
const PROGMEM char menu_521[] = " 7. Z 52V 12.8Ah 666Wh  ";                       // 76
const PROGMEM char menu_521[] = " 6. Z 52V 13Ah 676Wh    ";                       // 76
const PROGMEM char menu_522[] = " 7. Z 52V 18.2Ah 946.4Wh";                       // 77
const PROGMEM char menu_541[] = "  Return          ";                             // 96
*/

// #####################################################################################
/*
const PROGMEM char menu_521[] = "Ecooter                    ";                     // 76
const PROGMEM char menu_522[] = " 1. Ecooter 64V 20Ah 1280Wh  ";                   // 77
const PROGMEM char menu_541[] = " 2. Ecooter 60V 32Ah 1920Wh   ";                  // 96
const PROGMEM char menu_521[] = " 3. E-Nik 36V 7.8Ah 280.8Wh    ";                 // 7
const PROGMEM char menu_522[] = " 4. Ecooter 64V 42Ah 2688Wh  ";                   // 77
const PROGMEM char menu_541[] = "  Return          ";                              // 96
*/
// #####################################################################################

/*
const PROGMEM char menu_521[] = "Bosch                    ";                                    // 97
const PROGMEM char menu_522[] = " 1. Bosch Powerpack 500 36V-13.4Ah-500Wh   ";                  // 98
const PROGMEM char menu_541[] = " 2. Bosch PowerTube 400 36V 11Ah 400Wh     ";                  // 99
const PROGMEM char menu_521[] = " 3. Bosch PowerTube 625 36V 16.7Ah 625Wh   ";                  // 100
const PROGMEM char menu_522[] = " 4. Bosch Powerpack 400 36V 11Ah 400Wh     ";                  // 101
const PROGMEM char menu_522[] = " 5. Bosch Powerpack 400 (Short)      ";                        // 102
const PROGMEM char menu_522[] = " 6. Bosch Powerpack 400 (Long)     ";                          // 103
const PROGMEM char menu_522[] = " 7. Bosch Powerpack 500 (Short)      ";                        // 104
const PROGMEM char menu_541[] = "  Return          ";                                           // 105
*/
// #####################################################################################
void start(void); 
void show_menu(void);
void checkButton();
void Dlg();
void Bmz();
void Zeeway();
void Phylion();
void Etwow();
int buttonStartState = 0;
int sensorValue = 0;

// Menu 
const MenuEntry menu[] =
{
  // text, num_menupoints, up, down, enter, *fp
  {menu_000, 6, 0, 0, 0, 0},                  // 0
  {menu_001, 6, 5, 2, 7, 0},                  // 1
  {menu_002, 6, 1, 3, 21, 0},                 // 2
  {menu_003, 6, 2, 4, 48, 0},                 // 3
  {menu_004, 6, 3, 5, 51, 0},                 // 4
  {menu_005, 6, 4, 1, 64, 0},                 // 5

  // text, num_menupoints, up, down, enter, *fp
  {menu_100, 14, 0, 0, 0, 0},               // 6
  {menu_101, 14, 19, 8, 0, Dlg},            // 7
  {menu_102, 14, 7, 9, 0,  Dlg},            // 8
  {menu_103, 14, 8, 10, 0, Dlg},            // 9
  {menu_104, 14, 9, 11, 0, Dlg},            // 10
  {menu_105, 14, 10, 12, 0,Dlg},            // 11
  {menu_106, 14, 11, 13, 0,Dlg},            // 12
  {menu_107, 14, 12, 14, 0,Dlg},            // 13
  {menu_108, 14, 13, 15, 0,Dlg},            // 14
  {menu_109, 14, 14, 16, 0,Dlg},            // 15
  {menu_110, 14, 15, 17, 0,Dlg},            // 16
  {menu_111, 14, 16, 18, 0,Dlg},            // 17
  {menu_112, 14, 17, 19, 0,Dlg},            // 18
  {menu_113, 14, 18, 7,1,0},                // 19

  // text, num_menupoints, up, down, enter, *fp
  {menu_200, 27, 0, 0, 0, 0},                   // 20
  {menu_201, 27, 46, 22, 0, Bmz},               // 21
  {menu_202, 27, 21, 23, 0, Bmz},               // 22
  {menu_203, 27, 22, 24, 0, Bmz},               // 23
  {menu_204, 27, 23, 25, 0, Bmz},               // 24
  {menu_205, 27, 24, 26, 0, Bmz},               // 25
  {menu_206, 27, 25, 27, 0, Bmz},               // 26
  {menu_207, 27, 26, 28, 0, Bmz},               // 27
  {menu_208, 27, 27, 29, 0, Bmz},               // 28
  {menu_209, 27, 28, 30, 0, Bmz},               // 29
  {menu_210, 27, 29, 31, 0, Bmz},               // 30
  {menu_211, 27, 30, 32, 0, Bmz},               // 31
  {menu_212, 27, 31, 33, 0, Bmz},               // 32
  {menu_213, 27, 32, 34, 0, Bmz},               // 33
  {menu_214, 27, 33, 35, 0, Bmz},               // 34
  {menu_215, 27, 34, 36, 0, Bmz},               // 35
  {menu_216, 27, 35, 37, 0, Bmz},               // 36
  {menu_217, 27, 36, 38, 0, Bmz},               // 37
  {menu_218, 27, 37, 39, 0, Bmz},               // 38
  {menu_219, 27, 38, 40, 0, Bmz},               // 39
  {menu_220, 27, 39, 41, 0, Bmz},               // 40
  {menu_221, 27, 40, 42, 0, Bmz},               // 41
  {menu_222, 27, 41, 43, 0, Bmz},               // 42
  {menu_223, 27, 42, 44, 0, Bmz},               // 43
  {menu_224, 27, 43, 45, 0, Bmz},               // 44
  {menu_225, 27, 44, 46, 0, Bmz},               // 45
  {menu_226, 27, 45, 21, 1, 0},                 // 46
 
  // text, num_menupoints, up, down, enter, *fp
  
  {menu_300, 3, 0, 0, 0, 0},                    // 47
  {menu_301, 3, 49, 49, 0, Zeeway},             // 48
  {menu_302, 3, 48, 48, 1, 0},                  // 49
  
  // text, num_menupoints, up, down, enter, *fp

  {menu_400, 13, 0, 0, 0, 0},                        // 50
  {menu_401, 13, 62, 52, 0, Etwow},                  // 51
  {menu_402, 13, 51, 53, 0, Etwow},                  // 52
  {menu_403, 13, 52, 54, 0, Etwow},                  // 53
  {menu_404, 13, 53, 55, 0, Etwow},                  // 54
  {menu_405, 13, 54, 56, 0, Etwow},                  // 55
  {menu_406, 13, 55, 57, 0, Etwow},                  // 56
  {menu_407, 13, 56, 58, 0, Etwow},                  // 57
  {menu_408, 13, 57, 59, 0, Etwow},                  // 58
  {menu_409, 13, 58, 60, 0, Etwow},                  // 59
  {menu_410, 13, 59, 61, 0, Etwow},                  // 60
  {menu_411, 13, 60, 62, 0, Etwow},                  // 61
  {menu_412, 13, 61, 51, 1, 0},                      // 62

    // text, num_menupoints, up, down, enter, *fp

  {menu_500, 17, 0, 0, 0, 0},                          // 63
  {menu_501, 17, 79, 65, 0, Phylion},                  // 64
  {menu_502, 17, 64, 66, 0, Phylion},                  // 65
  {menu_503, 17, 65, 67, 0, Phylion},                  // 66
  {menu_504, 17, 66, 68, 0, Phylion},                  // 67
  {menu_505, 17, 67, 69, 0, Phylion},                  // 68
  {menu_506, 17, 68, 70, 0, Phylion},                  // 69
  {menu_507, 17, 69, 71, 0, Phylion},                  // 70
  {menu_508, 17, 70, 72, 0, Phylion},                  // 71
  {menu_509, 17, 71, 73, 0, Phylion},                  // 72
  {menu_510, 17, 72, 74, 0, Phylion},                  // 73
  {menu_511, 17, 73, 75, 0, Phylion},                  // 74
  {menu_512, 17, 74, 76, 0, Phylion},                  // 75
  {menu_513, 17, 75, 77, 0, Phylion},                  // 76
  {menu_514, 17, 76, 78, 0, Phylion},                  // 77
  {menu_515, 17, 77, 79, 0, Phylion},                  // 78
  {menu_516, 17, 78, 64, 1, 0},                        // 79
 
};
void setup() {
  lcd.clear();
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  lcd.setCursor (0, 0);
  lcd.print("NOWOS V-0.1");
  delay(4000);
  effacer();
  show_menu();
  // Serial.println(BMZ1[0]);
  // ADS1115 partie a tester après installation de l'ADS
  ADS.begin();         // Initialisation du module ADS1115
  ADS.setGain(0);      // On prend le gain le plus bas (index 0), pour avoir la plus grande plage de mesure (6.144 volt)
  ADS.setMode(1);      // On indique à l'ADC qu'on fera des mesures à la demande, et non en continu (0 = CONTINUOUS, 1 = SINGLE)
  ADS.setDataRate(0);  // On spécifie la vitesse de mesure de tension qu'on souhaite, allant de 0 à 7 (7 étant le plus rapide, soit 860 échantillons par seconde)
 }
void loop() {
  // Pour la partie Button si c'est boutton UP DOWN LEFT RIGHT. 
  if(millis() >= checkButtonTaskTimer + checkButtonTaskInterval){
    checkButtonTaskTimer += checkButtonTaskInterval;
     checkButton();
  }
  // L'affichage du menu. 
  if(millis() >= updateLCDTaskTimer + updateLCDTaskInterval){
    updateLCDTaskTimer += updateLCDTaskInterval;
     //show_menu();
  } 
}
// Fonction pour envoyer une impulsion
void dcdc(){
    Serial.println("DCDC Activé");
    digitalWrite(Dcdc, LOW);                      // Activation DCDC
    delay(1500);
    digitalWrite(Dcdc, HIGH);                     // Desactivation DCDC
    delay(10);
}
// Fonction Charge retourn le voltage de charge
int charge(){
    ADS.readADC(0);  
    int16_t charge = ADS.readADC_Differential_0_1();
    voltage_charge = charge / 3.033; 
    Serial.println(voltage_charge);
    return voltage_charge;
}
// Fonction Charge retourn le voltage decharge
int decharge(){
    ADS.readADC(0);  
    int16_t decharge = ADS.readADC_Differential_2_3();
    voltage_decharge = decharge / 3.033; 
    return  voltage_decharge;
}
// Fonction pour effacer l'écran 
void effacer(){
     for (int t=0; t<2; t++)
      {
        lcd.setCursor (0, t);
        for (int i = 0; i < 16; ++i)
          {
             lcd.print(" ");
          }
       }
}


void show_menu(void)
{
  unsigned char line_cnt = 0;
  unsigned char from = 0;
  unsigned char till = 0;
  unsigned char temp = 0;

  while (till <= selected)
  {
    till += menu[till].num_menupoints;   

  }   
  from = till - menu[selected].num_menupoints;  
  till--;                     
  temp = from;                


  
  // browsing somewhere in the middle
  if ((selected >= (from+PER_SPACE)) && (selected <= till ))
  {
    from = selected-PER_SPACE;
    till = from + (DISPLAY_ROWS-1);
    
    for (from; from<=till; from++)
    {
      
      lcd.setCursor(0, line_cnt);
      for (byte k = 0; k < strlen_P(menu[from].text); k++) {
       myChar = pgm_read_byte_near(menu[from].text + k);
             lcd.print(myChar);
         }
      line_cnt = line_cnt + 1;
    }
  }
  
  // browsing somewhere in the top or the bottom
  else
  {
    // top of the menu
    if (selected < (from+PER_SPACE))  // 2 lines
    {
      //till = from + 3;
      till = from + (DISPLAY_ROWS-1); // 2 lines

      for (from; from<=till; from++)
      {
        lcd.setCursor(0, line_cnt);
        lcd.print(menu[from].text);
        line_cnt = line_cnt + 1;
      }
    }

    // bottom of the menu
    if (selected == till)
    {
      from = till - (DISPLAY_ROWS-1); // 2 lines
      
      for (from; from<=till; from++)
      {
        lcd.setCursor(0, line_cnt);
        lcd.print(menu[from].text);
        line_cnt = line_cnt + 1;     
      }
     
    }
  }
  lcd.setCursor(0, 2);
  lcd.print(">");
}

// Fonction qui permet de vérifier si c'est un button left right up down 
void checkButton() {
  
  int x = analogRead (0);
 
  if (x < 60) {
    buttonPressed = 'R';
 }
 else if (x < 200) {
      buttonPressed = 'U';
 }
 else if (x < 400){
    buttonPressed = 'D';
 }
 else if (x < 600){
    buttonPressed = 'L';
 }
 else if (x < 800){
    buttonPressed = 'S';
 }else {
    buttonPressed = '0';
  }
 
 
  processButton(buttonPressed);

}
// Fonction qui permet d'éxécuter la fonction choisie 
void processButton(char buttonPressed) {
  switch ( buttonPressed ) {
    case 'R': 
    //test si c'est Right Alors exécuter la fonction associé.c'est la partie .fp tu peux regarder dans le 1 tableau déclarer tu vas comprendre ;) 
        if (menu[selected].fp != 0)
        {
          menu[selected].fp();
         }
        if(selected == 6 || selected == 7 || selected == 8 || selected == 9 || selected == 6 || selected == 7 || selected == 8 || selected == 9 || selected == 10 
        || selected == 11 || selected == 14 || selected == 15      || selected == 20 || selected == 22 || selected == 23 || selected == 24 || selected == 25 || selected == 28 || selected == 29 ) {
        // exit the loop 
        exit(0);  
        //0 is required to prevent error 
         }else{
        prev_key = selected;
        selected = menu[selected].enter;
        show_menu();
        }
      break;
    case 'U': // U
        prev_key = selected;
        selected = menu[selected].up; 
        show_menu();
     
      break;
    case 'D': // D
        prev_key = selected;
        selected = menu[selected].down; 
        show_menu();
      
      break;
    case 'L': // L
       
       break;
    case 'S': // S
    
    break;
    
    default:

    break;
  }  
}
 
 

 
 
