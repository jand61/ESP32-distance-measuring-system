
/****************************************************************************************************************************************************************************
 
 Name: Jan Döllmann

 Infos zum Projekt:
  - Hardware: Mikrocontroller(ESPRESSIF ESP32-Wroom-32D)
              Ultraschallsensor(Ultrasonic HC-SR04)
              4 LEDs(blau, grün, gelb, rot)
              4x 220 Ohm Widerstand(als Vorwiderstände für die LEDs)
              4 zusammengesteckte 400 PIN Breadboards
              Jumper Kabel

  Mit diesem Projekt wird eine Abstandsmessung mithilfe eines Ultraschallsensors durchgeführt. Die zum Objekt gemessene Distanz über WiFi übertragen 
  und auf dem Handy in der App "Blynk" angezeigt. Zusätzlich werden vier farbige LEDs(blau, grün, gelb, rot) verwendet, die abhängig von der gemessenen 
  Distanz aufleuchten. Die jeweils aufleuchtende LED wird ebenfalls in Blynk per virtuellen PINs angezeigt.
 
/****************************************************************************************************************************************************************************/
        



// Einbinden der Bibliotheken
/****************************************************************************************************************************************************************************/

#include <SPI.h>                                                            
#include <Wire.h>                                                      
#include <WiFi.h>   
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>                                               

#define BLYNK_PRINT Serial  
                           
/****************************************************************************************************************************************************************************/




// Definitionen
/****************************************************************************************************************************************************************************/

long Messdauer;                                                             // definieren des Messintervalls, indem der Sensor Werte erfasst(100ms)
float Distanz;                                                              // verantwortlich für die Speicherung der vom Ultraschallsensor gelesenen 
                                                                            // Werte + Setzen des Anfangswerts auf 0.

const int PIN_LED_blau   = 27;                                              // Definieren der PIN-Einstellungen, die für die LEDs verwendet werden.
const int PIN_LED_gruen  = 26;
const int PIN_LED_gelb   = 25;                                       
const int PIN_LED_rot    = 33;

/****************************************************************************************************************************************************************************/

                                                  
                                                                          

// Sensorkonfiguration
/****************************************************************************************************************************************************************************/

const int TRIG_PIN = 18;                                                    // PIN-Anschlüsse für den Ultraschallsensor
const int ECHO_PIN = 19;

/****************************************************************************************************************************************************************************/




// WiFi-Einstellungen
/****************************************************************************************************************************************************************************/

char auth[] = "LYyiR2qPxEc_7JjJQLPKTDuJFpA1YfxC";

char ssid[] = "Jan_PC";
char pass[] = "InfoProjekt";
WidgetLCD lcd(V0);

/****************************************************************************************************************************************************************************/



// Setup
/****************************************************************************************************************************************************************************/

void setup() 
{
  Serial.begin(9600);
  Blynk.begin("LYyiR2qPxEc_7JjJQLPKTDuJFpA1YfxC", "Jan_PC", "InfoProjekt");

  PIN_Konfiguration();                                                       // Aufrufen der Funktion, welche die Konfiguration der PINs beinhaltet
  
}

/****************************************************************************************************************************************************************************/




// Konfigurieren der PINs(Setzen der PIN-Modi auf Output/Input)
/****************************************************************************************************************************************************************************/

void PIN_Konfiguration()                                                    // Einstellen der Modi für die PINs, die als Ausgabe verwendet werden
{
  pinMode(PIN_LED_blau,   OUTPUT);
  pinMode(PIN_LED_gruen,  OUTPUT);
  pinMode(PIN_LED_gelb,   OUTPUT);
  pinMode(PIN_LED_rot,    OUTPUT);

  pinMode(TRIG_PIN,       OUTPUT);
  pinMode(ECHO_PIN,        INPUT);    
    
}

/****************************************************************************************************************************************************************************/


void loop()
{

// Messen der Distanz bzw. Ausgeben des gemessenen Wertes auf dem seriellen Monitor
/****************************************************************************************************************************************************************************/
  
  digitalWrite(TRIG_PIN, LOW);                                               // Sicherstellen, dass der Trigger-PIN frei ist.
  delayMicroseconds(2);
  
  digitalWrite(TRIG_PIN, HIGH);                                              // Erzeugen der Ultraschallwelle(durch Setzen des Trigger-PINs auf HIGH 
  delayMicroseconds(10);                                                     // für 10 us).
  digitalWrite(TRIG_PIN, LOW);

  Messdauer = pulseIn(ECHO_PIN, HIGH);                                       // Zeitintervall wird ausgelesen und in die Variable "Distanz" geschrieben.
  Distanz = (Messdauer * 0.034) / 2;                                         // Mithilfe der Geschwindigkeit der Schallwellen und der Dauer wird die 
                                                                             // zurückgelegte Distanz gemessen.

/****************************************************************************************************************************************************************************/



// Ansteuerung der LEDs abhängig von der gemessenen Entfernung
/****************************************************************************************************************************************************************************/
  
  if( Distanz > 50 )                                                          // blaue LED          
  {                                                                         
    digitalWrite(PIN_LED_blau, HIGH);
    Blynk.virtualWrite(V4, 255);
    
  }

  else
  {
    digitalWrite(PIN_LED_blau, 0);
    Blynk.virtualWrite(V4, 0);
    
  }
  
 
  if(( Distanz <= 50 ) & ( Distanz > 20 ))                                    // grüne LED
  {                                                                         
    digitalWrite(PIN_LED_gruen, HIGH);
    Blynk.virtualWrite(V3, 255);
    
  }

  else
  {
    digitalWrite(PIN_LED_gruen, 0);
    Blynk.virtualWrite(V3, 0);
    
  }


  if(( Distanz <= 20 ) & ( Distanz > 5 ))                                     // gelbe LED
  {                                                                        
     digitalWrite(PIN_LED_gelb, HIGH);
     Blynk.virtualWrite(V2, 255);

  }

  else                                                                        
  {
    digitalWrite(PIN_LED_gelb, 0);
    Blynk.virtualWrite(V2, 0);
    
  }

  if( Distanz <= 5 )                                                          // rote LED                   
  {
     digitalWrite(PIN_LED_rot, HIGH);
     Blynk.virtualWrite(V1, 255);

  }

  else
  {
     digitalWrite(PIN_LED_rot, 0);
     Blynk.virtualWrite(V1, 0);

   
  }
 
/****************************************************************************************************************************************************************************/

  Serial.println(Distanz);

  lcd.print(1, 0, "   Distanz:");
  lcd.print(4, 1, Distanz);
  lcd.print(10, 1, "cm");
  delay(200);
  Blynk.run();

}

 





  
  
