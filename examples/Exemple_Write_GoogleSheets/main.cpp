// ============================================================
// Exemple — écriture dans une feuille Google Sheets (ESP8266)
//
// ⚠️ SÉCURITÉ : ce fichier ne doit contenir AUCUN secret. Renseignez vos
//    propres valeurs ci-dessous (ou, mieux, dans un fichier non versionné
//    type `secrets.h` ajouté au .gitignore).
// ============================================================
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>   // https://arduinojson.org
#include <OneWire.h>
#include <DallasTemperature.h>

// ---- À RENSEIGNER (ne pas committer de vraies valeurs) ----
const char* ssid          = "YOUR_SSID";
const char* password      = "YOUR_PASSWORD";
const char* spreadsheetId = "YOUR_SPREADSHEET_ID";
const char* apiKey        = "YOUR_API_KEY";
// ----------------------------------------------------------

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
