function updateFirebaseData() {
  var sheet = SpreadsheetApp.getActiveSpreadsheet().getActiveSheet();
  var url = "https://esp32-data-xxxxxxxxxxxxxxxxxxxxxxxxxx.firebasedatabase.app/data.json";  // ⚠️ Remplace avec ton URL Firebase

  try {
    var response = UrlFetchApp.fetch(url);
    var json = JSON.parse(response.getContentText());

    var temp = json.temperature;
    var hum = json.humidity;
    var date = new Date();

    // 🔹 Calcul de l'humidité absolue
    var ah = (6.112 * Math.exp((17.67 * temp) / (temp + 243.5)) * hum * 2.1674) / (273.15 + temp);

    // 🔹 Ajouter une nouvelle ligne avec les valeurs formatées
    sheet.appendRow([date, temp, hum, ah]);

    Logger.log("✅ Données mises à jour !");
  } catch (e) {
    Logger.log("❌ Erreur : " + e.toString());
  }
}
