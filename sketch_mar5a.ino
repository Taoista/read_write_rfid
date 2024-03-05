#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN     9     // Configura el pin RST del lector RFID
#define SS_PIN      10    // Configura el pin SS del lector RFID

MFRC522 lector(SS_PIN, RST_PIN);  // Inicializa el lector RFID

void setup() {
  Serial.begin(9600);
  SPI.begin();
  lector.PCD_Init(); // Inicializa el lector RFID
  Serial.println("Lector RFID listo para leer...");
}

void loop() {
  Serial.print("esat corriendo el software desde el inicio");
  // Verificar si se detecta una tarjeta RFID
  if (lector.PICC_IsNewCardPresent() && lector.PICC_ReadCardSerial()) {
    Serial.print("Tarjeta detectada, UID: ");

    // Obtener el UID de la tarjeta
    String uid = "";
    for (byte i = 0; i < lector.uid.size; i++) {
      uid += String(lector.uid.uidByte[i] < 0x10 ? " 0" : " ");
      uid += String(lector.uid.uidByte[i], HEX);
    }
    uid.toUpperCase(); // Convierte a mayúsculas
    
    // Imprimir el UID en la consola
    Serial.println(uid);

    lector.PICC_HaltA(); // Detener la comunicación con la tarjeta actual
  }
}
