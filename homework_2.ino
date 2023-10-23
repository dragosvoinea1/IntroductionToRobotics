int pinRosu = 11;
int pinAlbastru = 10;
int pinVerde = 9;

int valRosu, valAlbastru, valVerde;


void setup() {
  pinMode(pinRosu, OUTPUT);
  pinMode(pinAlbastru, OUTPUT);
  pinMode(pinVerde, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
}

void loop() {
  int pot_val1 = analogRead(A0);
  int pot_val2 = analogRead(A1);
  int pot_val3 = analogRead(A2);

  valAlbastru = map(pot_val2, 0, 1023, 0, 255);
  valVerde = map(pot_val3, 0, 1023, 0, 255);
  valRosu = map(pot_val1, 0, 1023, 0, 255);
  

  analogWrite(pinAlbastru, valAlbastru);
  analogWrite(pinVerde, valVerde);
  analogWrite(pinRosu, valRosu);
  
  delay(10);
}
