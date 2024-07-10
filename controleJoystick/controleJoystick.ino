const int xPin = A0;
const int yPin = A1;
const int buttonPin = 2;

const int PIN_botaoEsq = 8;
const int PIN_botaoMeio = 9;
const int PIN_botaoDir = 10;

int botaoEsq,botaoMeio,botaoDir = 0;
int xDirection = 0;
int yDirection = 0;

void setup() {
    Serial.begin(9600);
    pinMode(buttonPin, INPUT_PULLUP); 
    pinMode(PIN_botaoEsq,INPUT_PULLUP);
    pinMode(PIN_botaoMeio,INPUT_PULLUP);
    pinMode(PIN_botaoDir,INPUT_PULLUP);
}

void loop() {
  int xValue = analogRead(A0);  
  int yValue = analogRead(A1); 
  int buttonState = (!digitalRead(2));

  xDirection = map(xValue,0,1023,-4,5);
  yDirection = map(yValue,0,1023,-4,5);
  
  botaoEsq = (!digitalRead(PIN_botaoEsq));
  botaoMeio = (!digitalRead(PIN_botaoMeio));
  botaoDir = (!digitalRead(PIN_botaoDir));
  
  // Envia os dados na formatação: xDirection,yDirection,buttonState,botaoEsq,botaoMeio,botaoDir
  Serial.print(xDirection);
  Serial.print(",");
  Serial.print(yDirection);
  Serial.print(",");
  Serial.print(buttonState);
  Serial.print(",");
  Serial.print(botaoEsq);
  Serial.print(",");
  Serial.print(botaoMeio);
  Serial.print(",");
  Serial.println(botaoDir);
  
  delay(100);  // Intervalo de 100 ms entre as leituras
}
