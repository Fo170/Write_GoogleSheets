# Write_GoogleSheets

Librairie **header-only** Arduino / ESP8266 / ESP32 pour **écrire des valeurs dans
une feuille Google Sheets** via l'API Google Sheets v4.

## ⚠️ Sécurité — à lire avant utilisation

La librairie **ne contient aucun identifiant** : ni ID de feuille, ni clé API.
Vous devez les fournir **dans votre programme**, jamais dans la librairie
(le dépôt est public) :

```cpp
const char* spreadsheetId = "YOUR_SPREADSHEET_ID";
const char* apiKey        = "YOUR_API_KEY";
```

La librairie les référence en `extern`. Pour un projet réel, placez-les dans un
fichier `secrets.h` **ajouté au `.gitignore`**.

> Une clé API Google est un **secret** : si elle a été exposée, révoquez-la dans
> la console Google Cloud et générez-en une nouvelle.

## Installation (PlatformIO)

```ini
lib_deps =
    https://github.com/Fo170/Write_GoogleSheets.git#v1.0.0
```

Dépendances : `ArduinoJson` (v7).

## Utilisation

```cpp
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

const char* ssid          = "YOUR_SSID";
const char* password      = "YOUR_PASSWORD";
const char* spreadsheetId = "YOUR_SPREADSHEET_ID";
const char* apiKey        = "YOUR_API_KEY";

#include <Write_GoogleSheets.h>

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
}

void loop() {
  Write_GoogleSheets("A1", String(millis() / 1000));
  Write_GoogleSheets("A2", String(21.5, 2));
  delay(60000);
}
```

Un exemple complet est fourni dans `examples/Exemple_Write_GoogleSheets/`.

## Obtenir l'ID de feuille et la clé API

1. Ouvrez le classeur dans le navigateur : l'ID est la partie entre
   `/d/` et `/edit` de l'URL.
2. Dans la **console Google Cloud** : créez un projet, activez l'**API Google
   Sheets**, puis créez une **clé API**.
3. La feuille doit être partagée en lecture/écriture selon le mode d'accès utilisé.

## Réglages compile-time

| Macro | Effet |
|---|---|
| `PRINT_DEBUG_MESSAGES_Write_GoogleSheets` | Active les traces série de la librairie |

## Version

La version est déclarée dans `src/Write_GoogleSheets.h` :

```c
#define __WRITE_GOOGLESHEETS_H_VERSION__ "1.0.0"
```

Source **unique** : un projet hôte peut l'agréger (ex. page `/version`) plutôt
que de recopier le numéro.

## Licence

GPL-3.0-only — Olivier FOURNET.
