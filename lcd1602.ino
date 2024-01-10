#include <LiquidCrystal.h>


LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

#define TRIG_PIN_1 2
#define ECHO_PIN_1 4
#define TRIG_PIN_2 5
#define ECHO_PIN_2 6

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); // Inicializa la pantalla LCD 16x2
  
  pinMode(TRIG_PIN_1, OUTPUT);
  pinMode(ECHO_PIN_1, INPUT);
  pinMode(TRIG_PIN_2, OUTPUT);
  pinMode(ECHO_PIN_2, INPUT);
}

void loop() {
  long duration, distance1, distance2;
  long totalDistance = 0;
  int numReadings = 0;

  // Realizar múltiples mediciones y obtener la suma de las distancias de ambos sensores
  for (int i = 0; i < 5; i++) { // Realizar 5 mediciones
    digitalWrite(TRIG_PIN_1, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN_1, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN_1, LOW);
    duration = pulseIn(ECHO_PIN_1, HIGH);
    distance1 = duration * 0.03425 / 2;  // Convertir a distancia en cm
    
    digitalWrite(TRIG_PIN_2, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN_2, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN_2, LOW);
    duration = pulseIn(ECHO_PIN_2, HIGH);
    distance2 = duration * 0.03425 / 2;  // Convertir a distancia en cm

    // Calcular la suma total de las distancias medidas
    totalDistance += (distance1 + distance2);
    numReadings += 2; // Añadir 2 lecturas (una por cada sensor)
    delay(50); // Esperar un breve momento entre mediciones
  }

  // Calcular la media (promedio) de las distancias
  float averageDistance = (float)totalDistance / numReadings;

  // Convertir el valor float a una cadena de caracteres con dos decimales
  char buffer[10];
  dtostrf(averageDistance, 5, 2, buffer); // 5 -> longitud total, 2 -> decimales
  
  // Mostrar la media con dos decimales en la pantalla LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distancia media:");
  lcd.setCursor(0, 1);
  lcd.print(buffer); // Muestra la media con 2 decimales
  lcd.print(" cm");

  // Mostrar la media con dos decimales en el monitor serial
  Serial.print("Distancia media: ");
  Serial.print(buffer); // Muestra la media con 2 decimales
  Serial.println(" cm");

  delay(1000); // Esperar un segundo antes de tomar nuevas mediciones
}
