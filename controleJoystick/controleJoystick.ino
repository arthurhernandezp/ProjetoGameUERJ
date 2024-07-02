const int xPin = A0; // Pino ADC para o eixo X
const int yPin = A1; // Pino ADC para o eixo Y
const int buttonPin = 2; // Pino digital para o botão

void setup() {
    Serial.begin(9600);
    pinMode(buttonPin, INPUT_PULLUP); // Configurando o pino do botão como entrada com pull-up interno
}

void loop() {
int xValue = analogRead(A0);  // Supondo que o eixo X está conectado ao pino A0
  int yValue = analogRead(A1);  // Supondo que o eixo Y está conectado ao pino A1
  int buttonState = digitalRead(2); // Supondo que o botão está conectado ao pino 2

  int xDirection = 0;
  int yDirection = 0;

  // Determina a direção do eixo X
  if (xValue < 400) {
    xDirection = -1;
  } else if (xValue > 600) {
    xDirection = 1;
  }

  // Determina a direção do eixo Y
  if (yValue < 400) {
    yDirection = -1;
  } else if (yValue > 600) {
    yDirection = 1;
  }

  // Envia os dados na formatação: xDirection,yDirection,buttonState
  Serial.print(xDirection);
  Serial.print(",");
  Serial.print(yDirection);
  Serial.print(",");
  Serial.println(buttonState);

  delay(100);  // Intervalo de 100 ms entre as leituras
}
