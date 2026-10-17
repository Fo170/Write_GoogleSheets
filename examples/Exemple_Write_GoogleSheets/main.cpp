// ============================================================
// Exemple — écriture dans une feuille Google Sheets (ESP8266)
//
// ⚠️ SÉCURITÉ : ce fichier est PUBLIÉ — il ne doit contenir AUCUN secret.
//    Les valeurs réelles vont dans `secrets.h`, à côté de ce fichier.
//    `secrets.h` est exclu par .gitignore → jamais publié.
//
//    Sans secrets.h, l'exemple compile avec des placeholders (non fonctionnel).
// ============================================================
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>   // https://arduinojson.org
#include <OneWire.h>
#include <DallasTemperature.h>

// ---- Identifiants : secrets.h (local, non versionné) ou placeholders ----
#if __has_include("secrets.h")
  #include "secrets.h"
  #define HAVE_SECRETS 1
#else
  #define SECRET_SPREADSHEET_ID "YOUR_SPREADSHEET_ID"
  #define SECRET_API_KEY        "YOUR_API_KEY"
  #define SECRET_WIFI_SSID      "YOUR_SSID"
  #define SECRET_WIFI_PASSWORD  "YOUR_PASSWORD"
  #define HAVE_SECRETS 0
#endif

const char* ssid          = SECRET_WIFI_SSID;
const char* password      = SECRET_WIFI_PASSWORD;
const char* spreadsheetId = SECRET_SPREADSHEET_ID;
const char* apiKey        = SECRET_API_KEY;
// -----------------------------------------------------------------------

#define ONE_WIRE_BUS D4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

WiFiClient client;
float secondes = 0.0;

#define PRINT_DEBUG_MESSAGES_Write_GoogleSheets
#include <Write_GoogleSheets.h>

void setup()
{
    Serial.begin(115200);

#if !HAVE_SECRETS
    Serial.println("\n[!] secrets.h absent : identifiants fictifs.");
    Serial.println("    Copiez secrets.h.example -> secrets.h et renseignez vos valeurs.");
#endif

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
    Serial.println("\nWiFi connected");

    sensors.begin();
    sensors.setResolution(12);
}

void loop()
{
    sensors.requestTemperatures();
    float temperature = sensors.getTempCByIndex(0);

    if (temperature == DEVICE_DISCONNECTED_C) {
        Serial.println("Erreur: lecture DS18B20 impossible");
    } else {
        Serial.printf("T = %.2f C\n", temperature);
        Write_GoogleSheets("A1", String(secondes));
        Write_GoogleSheets("A2", String(temperature));
    }

    secondes += 60.0;
    delay(60 * 1000);   // 1 mesure / minute
}
