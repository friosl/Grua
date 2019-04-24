#define UP 
#define DOWN 
#define LEFT 
#define RIGHT 
#define PICK 

#define SUP 
#define SDOWN 
#define P1 
#define P2 
#define P3 

byte lastState = 0;

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
  lastState = 1;
}

void updateTo2() {
  lastState = 3;
}

void updateTo3() {
  lastState = 3;
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

void electrify() {
  
}
