#define UP 23
#define DOWN 22
#define LEFT 25
#define RIGHT 26
#define PICK 24

#define SUP 18
#define SDOWN 29
#define P1 21
#define P2 20
#define P3 19

#define DISCONECTED 0
#define STOPPED 1
#define RUNNING 2

byte state = 0;

byte actual = 0, last = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(UP, OUTPUT);
  pinMode(DOWN, OUTPUT);
  pinMode(LEFT, OUTPUT);
  pinMode(RIGHT, OUTPUT);
  pinMode(PICK, OUTPUT);

  pinMode(SUP, INPUT);
  pinMode(SDOWN, INPUT);
  pinMode(P1, INPUT);
  pinMode(P2, INPUT);
  pinMode(P3, INPUT);

  attachInterrupt(2, updateTo1, RISING);
  attachInterrupt(3, updateTo2, RISING);
  attachInterrupt(4, updateTo3, RISING);

  initMove();
  hanoi(3, 2);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void updateTo1() {
  last = actual;
  actual = 1;
  Serial.println(actual);
}

void updateTo2() {
  last = actual;
  actual = 2;
  Serial.println(actual);
}

void updateTo3() {
  last = actual;
  actual = 3;
  Serial.println(actual);
}

boolean readTower(byte p) {
  if(p == 1) return digitalRead(P1);
  if(p == 2) return digitalRead(P2);
  if(p == 3) return digitalRead(P3);
  return false;
}

void processRequest() {
  int req = Serial.parseInt();
  byte order1 = req % 10,
  order2 = (req % 100) / 10,
  order3= req/100;
  
  switch(order1) {
    case 1:
      switch(order2) {
        case 1:
          moveUp();
          break;
        case 2:
          moveUp();
          break;
        case 3:
          moveLeft();
          break;
        case 4:
          moveRight();
          break;
      }
      break;
    case 2:

      break;
    case 3:

      break;
    case 4:

      break;
    case 5:

      break;
    case 6:

      break;
    case 7:

      break;
  }
  
}

void moveLeft() {
  //Serial.println("izquierda");
  digitalWrite(UP, 0);
  digitalWrite(DOWN, 0);
  digitalWrite(LEFT, 1);
  digitalWrite(RIGHT, 0);
}

void moveRight() {
  //Serial.println("derecha");
  digitalWrite(UP, 0);
  digitalWrite(DOWN, 0);
  digitalWrite(LEFT, 0);
  digitalWrite(RIGHT, 1);
}

void moveUp() {
  //Serial.println("arriba");
  digitalWrite(UP, 1);
  digitalWrite(DOWN, 0);
  digitalWrite(LEFT, 0);
  digitalWrite(RIGHT, 0);
}

void moveDown() {
  //Serial.println("abajo");
  digitalWrite(UP, 0);
  digitalWrite(DOWN, 1);
  digitalWrite(LEFT, 0);
  digitalWrite(RIGHT, 0);
}

void stopMove() {
  //Serial.println("parado");
  digitalWrite(UP, 0);
  digitalWrite(DOWN, 0);
  digitalWrite(LEFT, 0);
  digitalWrite(RIGHT, 0);
}

void initMove() {
  //Serial.println("movimiento iniciado");
  moveUp();
  while(!digitalRead(SUP));
  moveRight();
  for(int i = 0; i < 500; i++) {
    //if(lastState != 0) break;
    delay(10);
  }
  moveLeft();
  for(int i = 0; i < 500; i++) {
    //if(lastState != 0) break;
    delay(10);
  }
  //while(lastState == 0);
  stopMove(); 
}

void magnetOn() {
  //Serial.println("on");
  digitalWrite(PICK, 1);
}

void magnetOff() {
  //Serial.println("off");
  digitalWrite(PICK, 0);
}

void pick() {
  //Serial.println("cogiendo");
  moveDown();
  for(int i = 0; i < 1000 || !digitalRead(SDOWN); i++) delay(2);
  magnetOn();
  stopMove();
  delay(10);
  moveUp();
  while(!digitalRead(SUP));
  stopMove();
}

void place() {
  //Serial.println("poniendo");
  moveDown();
  while(!digitalRead(SDOWN));
  stopMove();
  magnetOff();
  moveUp();
  while(!digitalRead(SUP));
  stopMove();
}

void goTo(byte destination) {
  Serial.print("yendo a ");
  Serial.println(destination);
  moveUp();
  while(!digitalRead(SUP));
  stopMove();
  if(destination < actual) moveLeft();
  else if(destination > actual) moveRight();
//  else if(){
//    if(destination < last) moveLeft();
//    else moveRight();
//  }
  while(!readTower(destination));
  stopMove(); 
}

void pickFrom(byte origin) {
  goTo(origin);
  pick();
}

void placeIn(byte destination) {
  goTo(destination);
  place();
}

void translate(byte origin, byte destination) {
  pickFrom(origin);
  placeIn(destination);
}

void hanoi(byte origin, byte destination) {
  byte rem = origin ^ destination;
  hanoiAux(3, origin, destination, rem);
  Serial.println("Hanoi acabado");
}

void hanoiAux(byte n, byte origin, byte destination, byte aux) {
  if(n == 1) translate(origin, destination);
  else {
    hanoiAux(n-1, origin, aux, destination);
    translate(origin, destination);
    hanoiAux(n-1, aux, destination, origin);
  }
}
