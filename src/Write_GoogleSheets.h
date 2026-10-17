// Version de la librairie (source UNIQUE — agrégée par liste_lib.h)
#define __WRITE_GOOGLESHEETS_H_VERSION__ "1.0.0"

// #define à définir dans le programme principal :
//#define PRINT_DEBUG_MESSAGES_Write_GoogleSheets

// ⚠️ SÉCURITÉ : ne JAMAIS coder en dur un identifiant de feuille ni une clé API
// dans la librairie (le dépôt est public). Définissez-les dans le programme
// principal, idéalement dans un fichier de secrets non versionné.
//
//   const char* spreadsheetId = "YOUR_SPREADSHEET_ID";
//   const char* apiKey        = "YOUR_API_KEY";
//
// La librairie les référence en `extern` (voir plus bas) : elle ne les possède pas.
extern const char* spreadsheetId;
extern const char* apiKey;

/*
Il est possible d'utiliser l'ESP8266 avec Arduino pour écrire des données dans un feuille de calcul Google en utilisant l'API Google Sheets. 
Voici les étapes générales pour y parvenir :

Créez un projet Google Sheets et obtenez son ID. Pour ce faire, ouvrez le classeur dans votre navigateur et copiez l'ID de l'URL. 
Par exemple, si l'URL est "https://docs.google.com/spreadsheets/d/1FgP8lFJtQ9XtGJXtGvf8EZWQZaTUw7WWiZvTcKkVuDk/edit#gid=0", 
l'ID de classeur est "1FgP8lFJtQ9XtGJXtGvf8EZWQZaTUw7WWiZvTcKkVuDk".

Créez une clé API pour votre projet Google Sheets. Pour ce faire, rendez-vous sur la console de développement de Google et créez un nouveau projet. 
Activez l'API Google Sheets et créez une clé API.

Installez les bibliothèques Arduino nécessaires pour utiliser l'API Google Sheets. Vous aurez besoin de la bibliothèque "ArduinoJSON" 
pour parser les réponses JSON de l'API et de la bibliothèque "ESP8266WiFi" pour vous connecter à Internet avec l'ESP8266.

Écrivez du code Arduino pour envoyer une requête HTTP POST à l'API Google Sheets en utilisant l'ESP8266. Vous devrez inclure votre ID 
de classeur et votre clé API dans l'URL de l'API. Vous devrez également inclure les données à écrire dans le corps de la requête.

La suite du code qui illustre comment envoyer une requête HTTP POST à l'API Google Sheets pour écrire des données dans une feuille de calcul.
Ce code envoie une requête HTTP POST à l'API Google Sheets avec les données à écrire dans le corps de la requête. 
L'API renvoie une réponse qui est imprimée dans la console Arduino.

Notez que ce code est un exemple simple qui ne prend pas en compte tous les cas d'erreur possibles. 
Il conviendrait de gérer les erreurs de manière plus robuste dans un projet réel.
*/

void Write_GoogleSheets(String caseSheet, String data)
{
  WiFiClient client_Write_GoogleSheets;
  //String data = "Test data";
  //String range = "Sheet1!A1";
  String range = "Sheet1!" + caseSheet;
  String url = "https://sheets.googleapis.com/v4/spreadsheets/" + String(spreadsheetId) + "/values/" + String(range) + "?key=" + String(apiKey);
  Serial.println("url: " + url);

  HTTPClient http;
  http.begin(client_Write_GoogleSheets, url);  // Envoi de la requête HTTP

  http.addHeader("Content-Type", "application/json");
  String payload = "{\"values\":[[\"" + data + "\"]]}";
  Serial.println("payload: " + payload);

  int httpResponseCode = http.POST(payload);
  Serial.println("httpResponseCode: " + httpResponseCode);

  if (httpResponseCode > 0) 
  {
    String response = http.getString();
    Serial.println(httpResponseCode);
    Serial.println(response);
  } 
  else 
  {
    Serial.println("Error: " + httpResponseCode);
  }
  http.end();
}
/*
Ce code envoie une requête HTTP POST à l'API Google Sheets avec les données à écrire dans le corps de la requête. 
L'API renvoie une réponse qui est imprimée dans la console Arduino.

Notez que ce code est un exemple simple qui ne prend pas en compte tous les cas d'erreur possibles. 
Il conviendrait de gérer les erreurs de manière plus robuste dans un projet réel.
*/