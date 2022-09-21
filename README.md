# Arduino-Testeur

## Code source testeur de batterie  : 
Code source documenté. Langage de programmation :  Arduino, C, C++
### Pour exécuter le programme  : 
- Le testeur doit être branché à la batterie et à l'ordinateur et il faut aussi vérifier la configuration dans IDE Arduino. 
Pour lancer l’injection du programme dans Arduino - Téléverser.

### Start.ino : 
- C’est le programme principal du testeur, permis d’initialiser toute la partie du testeur, LCD, Pin assignments, … 

### Batterie Fonction.ino : 
- Différentes fonctions selon le type de batteries, par exemple la première fonction prend en paramètre les deux valeurs voltage charge,voltage décharge récupérer de la batterie branché qu’on va les tester et afficher des résultats.
 
### Test.ino : 
- Tester les valeurs : 
      1- Fusible Décharge HS ou décharge port HS Si  D < 20 avec DCDC actif
      2- Fusible charge HS ou charge port HS Si C < 20 sans DCDC et C > 3750 avec DCDC
      3- Si les deux fonction précédents sont vrai, appareil non branché
      4- Surtension ou mauvais mode choisi Si C ou D Supérieur à 4200
      5- Décharge Profonde Si C entre 300 et 3100  avec DCDC actif
      6- Cellules détruites Si C entre 20 et 300 avec DCDC actif
      7- BMS HS Si Valeur C entre 3000 et 4200 et C > D+20 et Valeur D entre 20 et 3000
      8- BMS HS Si Valeur D entre 3000 et 4200 et valeur C entre 20 et < à D-20
      9- Déséquilibre Si Valeur C entre 3100 et 4100 et valeur D entre 20 et 3000
      10- Déséquilibre Si Valeur D entre 3100 et 4100 et valeur C < 3000 sans DCDC

### Menu.ino : 
- Cette partie est réservé au menu du testeur : Chaque constructeur de batterie à plusieurs type, Exemple : DLG - C8077708, BMZ - C8707437, ZEEWAY - 48V 10.4Ah, ETWOW - 36V 8.7Ah 
- MenuEntry : c’est un tableau de tableau : 
chaque case contient un tableau : menu_0..X, d'où X varie entre 0 le nombre de batterie de chaque constructeur exemple : 
 
  {menu_000, 6, 0, 0, 0, 0},                   
  {menu_001, 6, 5, 2, 7, 0},                  
  {menu_002, 6, 1, 3, 21, 0},                  
  {menu_003, 6, 2, 4, 48, 0},                  
  {menu_004, 6, 3, 5, 51, 0},                 
  {menu_005, 6, 4, 1, 64, 0},                 
colonne : 
1- menu_XXX
2- nombre d’élément dans le MenuEntry 
3- Up, 4- Down
5- Enter : Sélectionner un autre menu
6- Fonction à exécuter 

- dcdc () : pour envoyer une impulsion à la batterie
- charge () : retourne la charge de la batterie
- décharge() : retourne la décharge de la batterie 
- effacer () : effacer l’écran 
- show_menu() : affichage du menu, naviguer dans le menu 
- checkButton() : vérification des cliques des boutons avec analogRead
- proccessButton (buttonPressed) : exécuter la fonction associée 

### Base de données : 
- Niveau base de données on n’a les fichiers name.h ces fichiers contiennent les différentes informations de chaque constructeur de batteries - les différents type de batterie exemple : 

C8077708 36V 10.4Ah 374.4Wh .      - DLG1
C8707660 36V 10.4Ah 374.4Wh .      - DLG2
C8707678 36V 10.4Ah 374.4Wh        - DLG3
C8707704 36V 13Ah 468Wh .            - DLG4
C8707705 36V 8.7Ah 313.2Wh .        - DLG5
C8707706 36V 8.7Ah 313.2Wh .        - DLG6
C8707707 36V 13Ah 468Wh.             - DLG7
C8707708 36V 10.4Ah 374.4Wh .      - DLG8
C8707781-N 36V 10.4Ah 374.4Wh    - DLG9
C8707781-N2 36V 10.4Ah 374.4Wh  - DLG10
C8707783 36V 14Ah 504Wh .            - DLG11
C8707948-N 36V 12.8 Ah 460.8Wh   - DLG12
DLG D36145C2 36V 14.5 522H .       - DLG13
 
const int DLG1[5] = {0,32,39,32,39};
const int DLG2[5] = {0,32,39,32,39};
const int DLG3[5] = {0,32,39,32,39};
const int DLG4[5] = {0,32,39,32,39};
const int DLG5[5] = {0,32,39,32,39};
const int DLG6[5] = {0,32,39,32,39};
const int DLG7[5] = {0,32,39,32,39};
const int DLG8[5] = {0,32,39,32,39};
const int DLG9[5] = {0,32,39,32,39};
const int DLG10[5] = {0,32,39,32,39};
const int DLG11[5] = {0,32,39,32,39};
const int DLG12[5] = {0,32,39,32,39};
const int DLG13[5] = {0,32,39,32,39};
 
- Un tableau qui contient  -   DC DC : 0- Inactif 1-Actif, Tension Charge min, Tension Charge max, Tension De Décharge min, Tension De Décharge max
pareil pour les autres fichiers  nom_constructeur.h

### Site documentation Arduino : https://docs.arduino.cc/

### Installation: 
- Télécharger et installer Github Desktop : https://desktop.github.com/ 

- Créer un compte sur Github et importer (cloner) le repository sur l’ordinateur : https://github.com/ZineEddine25/Arduino-Testeur 

- Télécharger et installer Arduino IDE 2.X.Y : https://www.arduino.cc/en/software 



### Installer les mise à jour : 

Ouvrir le fichier Start.ino avec l’Arduino IDE, les onglets des fichiers du projet s’ouvrent
A l'initialisation (à ne faire que la première fois), sélectionner le modèle de la carte sur lequel le projet a été créé en cliquant sur …

Exécution : 
Screenshots pour montrer comment téléverser le logiciel et lister les actions à effectuer sur le Battery Tester 
Il faut tout d’abord vérifier le port de la carte arduino :  Outils -> Type de carte, le port, sinon si Arduino IDE ne détecte pas la carte on clique sur Récupérer les informations de la carte .

- Dès la fin de la configuration, on clique sur le Bouton téléverser pour injecter le programme 

### Questions / Réponses : 
En cas d'inversion de branchement ? la carte arduino affiche une erreur de branchement. 
Lister les noms des fabricants pour lesquels le Battery Tester a été testé et une autre liste pour ceux qui n’ont pas été testés - Aucune batterie pour le moment , L’alimentation stabilisée.  
Expliquer quelles sont les restrictions dûes à ce modèle d’Arduino (RAM, …) et pourquoi nous avons choisi ce HW - Niveau HW : afin d' éviter la surcharge de la RAM il faut déclarer toute les variables sous forme d’une const exemple : const int BFG1[5] = {0,38,47,38,47};  
Expliquer les fonctionnalités qui n’ont pas eu le temps d’être implémentées - DCDC  non implémenté 
Liste les améliorations potentielles pour se rapprocher du besoin utilisateur (ex : casing, alimentation interne ou externe, protection d’inversion polarité, …) - julien
Expliquer comment un codeur peut tester et déboguer le code, et documenter l’utilisation d’appareils électroniques (faire un schéma des branchements) pour tester les cas de figures - Utiliser l’écran de l’arduino pour déboguer sinon  Moniteur de série : 
Expliquer comment modifier le code pour restreindre les choix de marques de batteries - Pour modifier le code, les données de chaque batteries dans un fichier Nom-batterie.h tu peux juste modifier les valeurs et c’est tout bon. 
Écrire une notice d’utilisation (orientée utilisateur donc avec des photos) :
Affichage du numéro de version de Nowos Testeur pendant 3 s
Après le menu vas s’afficher 
Description de ce qu’il ne faut pas faire (ex : branchement à l’envers) - julien
Ecrire une documentation pour expliquer le montage HW - Julien
références des pièces (photos, coûts, liens pour acheter le HW, …)
ADS 115, Arduino UNO, LCD keypad, 2 diode zener, 4 résistances, plaque pour poser la carte.
schéma du/des montages électriques (PCB + composants + liens de soudure)
