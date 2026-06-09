#include <DHT.h>

#define pinoDHT 2
#define modeloDHT DHT22

#define ledVerde 3
#define ledAmarelo 4
#define ledVermelho 5
#define buzzer 6

#define trig 9
#define echo 10

DHT sensor(pinoDHT, modeloDHT);

void setup() {

  Serial.begin(9600);

  sensor.begin();

  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);

  pinMode(buzzer, OUTPUT);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {

  // lê a temperatura
  float temp = sensor.readTemperature();

  // mede a distância
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long tempo = pulseIn(echo, HIGH);

  float dist = tempo * 0.034 / 2;

  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" C  ");

  Serial.print("Distancia: ");
  Serial.print(dist);
  Serial.println(" cm");

  if (temp < 30 && dist > 50) {

    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, LOW);

    noTone(buzzer);
  }

  else if (temp >= 30 && temp < 35) {

    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledVermelho, LOW);

    noTone(buzzer);
  }

  else {

    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, HIGH);

    tone(buzzer, 1000);
  }

  delay(1000);
}