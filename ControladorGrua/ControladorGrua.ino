#define UP 1
#define DOWN 1
#define LEFT 1
#define RIGHT 1
#define PICK 1

#define SUP 1
#define SDOWN 1
#define P1 1
#define P2 1
#define P3 1

#define DISCONECTED 0
#define STOPPED 1
#define RUNNING 2

byte state = 0;

byte actual = 0, last = 0;

void setup() {
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
}

void loop() {
  // put your main code here, to run repeatedly:

}

void updateTo1() {
  last = actual;
  actual = 1;
}

void updateTo2() {
  last = actual;
  actual = 2;
}

void updateTo3() {
  last = actual;
  actual = 3;
}

void processRequest() {
  
}

void moveLeft() {
  digitalWrite(UP, 0);
  digitalWrite(DOWN, 0);
  digitalWrite(LEFT, 1);
  digitalWrite(RIGHT, 0);
}

void moveRight() {
  digitalWrite(UP, 0);
  digitalWrite(DOWN, 0);
  digitalWrite(LEFT, 0);
  digitalWrite(RIGHT, 1);
}

void moveUp() {
  digitalWrite(UP, 1);
  digitalWrite(DOWN, 0);
  digitalWrite(LEFT, 0);
  digitalWrite(RIGHT, 0);
}

void moveDown() {
  digitalWrite(UP, 0);
  digitalWrite(DOWN, 1);
  digitalWrite(LEFT, 0);
  digitalWrite(RIGHT, 0);
}

void stopMove() {
  digitalWrite(UP, 0);
  digitalWrite(DOWN, 0);
  digitalWrite(LEFT, 0);
  digitalWrite(RIGHT, 0);
}

void initMove() {
  moveUp();
  while(!digitalRead(SUP));
  moveRigth();
  for(int i = 0; i < 100; i++) {
    //if(lastState != 0) break;
    delay(2);
  }
  moveLeft();
  for(int i = 0; i < 100; i++) {
    //if(lastState != 0) break;
    delay(2);
  }
  //while(lastState == 0);
  stopMove(); 
}

void magnetOn() {
  digitalWrite(PICK, 1);
}

void magnetOff() {
  digitalWrite(PICK, 0);
}

void pick() {
  moveDown();
  for(int i = 0; i < 1000 || digitalRead(SDOWN); i++) delay(2);
  magnetOn();
  stopMove();
  delay(10);
  moveUp();
  while(!digitalRead(SUP));
  stopMove();
}

void place() {
  moveDown();
  while(!digitalRead(SDOWN));
  stopMove();
  magnetOff();
  moveUp();
  while(!digitalRead(SUP));
  stopMove();
}

void goTo(byte destination) {
  moveUp();
  while(!digitalRead(SUP));
  stopMove();
  if(destination < actual) moveLeft();
  else if(destination > actual) moveRigth();
  else {
    if(destination < last) moveLeft();
    else if(destination > last) moveRigth();
  }
  while(destination != lastState);
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

byte getRemaining(byte a, byte b) {
  if((a == 1 || b == 1) && (a == 2 || b == 2)) return 3;
  if((a == 1 || b == 1) && (a == 3 || b == 3)) return 2;
  if((a == 2 || b == 2) && (a == 3 || b == 3)) return 1;
}

void hanoi(byte origin, byte destination) {
  hanoiAux();
}

void hanoiAux(byte n, byte origin, byte destination, byte aux) {
  if(n == 1) translate(origin, dest);
  else {
    hanoiAux(n-1, origin, aux, destination);
    translate(origin, dest);
    hanoiAux(n-1, aux, destination, origin);
  }
}
