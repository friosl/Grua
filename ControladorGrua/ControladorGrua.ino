//Actuadores de la grúa
#define UP 23
#define DOWN 22
#define LEFT 25
#define RIGHT 26
#define PICK 24

//Sensores de la grúa
#define SUP 18
#define SDOWN 29
#define P1 21
#define P2 20
#define P3 19

//Últimas 2 estaciones por las que pasó la grua
byte actual = 0, last = 0;

//Setup del arduino
void setup() {
  Serial.begin(9600);       //Inicilaización del puerto serial 0. 
  
  //Declaración actuadores como salidas del arduino
  pinMode(UP, OUTPUT);
  pinMode(DOWN, OUTPUT);
  pinMode(LEFT, OUTPUT);
  pinMode(RIGHT, OUTPUT);
  pinMode(PICK, OUTPUT);

  //Declaración sensores como entradas del arduino
  pinMode(SUP, INPUT);
  pinMode(SDOWN, INPUT);
  pinMode(P1, INPUT);
  pinMode(P2, INPUT);
  pinMode(P3, INPUT);

  //Interrupciones en cada sensor para actualizar las estaciones.
  attachInterrupt(2, updateTo1, RISING);
  attachInterrupt(3, updateTo2, RISING);
  attachInterrupt(4, updateTo3, RISING);

  //Inicializar movimiento
  initMove();
}

//Loop vacío
void loop() {

}

//Actualizar ultima estación a 1
void updateTo1() {
  last = actual;
  actual = 1;
}

//Actualizar ultima estación a 2
void updateTo2() {
  last = actual;
  actual = 2;
}

//Actualizar ultima estación a 3
void updateTo3() {
  last = actual;
  actual = 3;
}

//Revisa si la grua se encuentra en una estación p
boolean readTower(byte p) {
  if(p == 1) return digitalRead(P1);
  if(p == 2) return digitalRead(P2);
  if(p == 3) return digitalRead(P3);
  return false;
}

//Decodifica la orden enviada por la interfaz a travez del serial.
void processRequest() {
  int req = Serial.parseInt();
  //Serial.println(req);
  byte order1 = req % 10,
  order2 = (req % 100) / 10,
  order3= req/100;
  
  switch(order1) {
    case 1:
      switch(order2) {
        case 1:
          stepUp();
          break;
        case 2:
          stepDown();
          break;
        case 3:
          stepLeft();
          break;
        case 4:
          stepRight();
          break;
      }
      break;
    case 2:
      switch(order2) {
        case 1:
          magnetOn();
          break;
        case 0:
          magnetOff();
          break;
      }
      break;
    case 3:
      switch(order2) {
        case 1:
          pick();
          break;
        case 0:
          place();
          break;
      }
      break;
    case 4:
      goTo(order2);
      break;
    case 5:
      switch(order2) {
        case 1:
          pickFrom(order3);
          break;
        case 0:
          placeIn(order3);
          break;
      }
      break;
    case 6:
      translate(order3, order2);
      break;
    case 7:
      hanoi(order3, order2);
      break;
    default:
      stopMove();
      break;
  }
}

//Cuando se recibe una orden
void serialEvent() {
  processRequest();
}

//Ir a izquierda infinitamente
void moveLeft() {
  digitalWrite(UP, 0);
  digitalWrite(DOWN, 0);
  digitalWrite(LEFT, 1);
  digitalWrite(RIGHT, 0);
}

//Ir a derecha infinitamente
void moveRight() {
  digitalWrite(UP, 0);
  digitalWrite(DOWN, 0);
  digitalWrite(LEFT, 0);
  digitalWrite(RIGHT, 1);
}

//Ir arriba infinitamente
void moveUp() {
  digitalWrite(UP, 1);
  digitalWrite(DOWN, 0);
  digitalWrite(LEFT, 0);
  digitalWrite(RIGHT, 0);
}

//Ir abajo infinitamente
void moveDown() {
  //Serial.println("abajo");
  digitalWrite(UP, 0);
  digitalWrite(DOWN, 1);
  digitalWrite(LEFT, 0);
  digitalWrite(RIGHT, 0);
}

//Parar el movimiento
void stopMove() {
  //Serial.println("parado");
  digitalWrite(UP, 0);
  digitalWrite(DOWN, 0);
  digitalWrite(LEFT, 0);
  digitalWrite(RIGHT, 0);
}

//Hacia arriba por 150ms y luego parar
void stepUp() {
  moveUp();
  delay(150);
  stopMove();
}

//Hacia abajo por 150ms y luego parar
void stepDown() {
  moveDown();
  delay(150);
  stopMove();
}

//Hacia izquierda por 150ms y luego parar
void stepLeft() {
  moveLeft();
  delay(150);
  stopMove();
}

//Hacia derecha por 150ms y luego parar
void stepRight() {
  moveRight();
  delay(150);
  stopMove();
}

//5s hacia la derecha y luego 5s hacia la izquierda
void initMove() {
  moveUp();
  while(!digitalRead(SUP));
  moveRight();
  for(int i = 0; i < 500; i++) {
    delay(10);
  }
  moveLeft();
  for(int i = 0; i < 500; i++) {
    delay(10);
  }
  stopMove(); 
}

//Magnetizar
void magnetOn() {
  digitalWrite(PICK, 1);
}

//Desmagnetizar
void magnetOff() {
  //Serial.println("off");
  digitalWrite(PICK, 0);
}

//Baja por 2s o hasta que encuentra algo, magetiza, y luego sube.
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

//Baja hasta que encuentra el fondo, desmagnetiza, y luego sube
void place() {
  moveDown();
  while(!digitalRead(SDOWN));
  stopMove();
  magnetOff();
  moveUp();
  while(!digitalRead(SUP));
  stopMove();
}

//Va hasta una estación en específico
void goTo(byte destination) {
  moveUp();
  while(!digitalRead(SUP));
  stopMove();
  if(destination < actual) moveLeft();
  else if(destination > actual) moveRight();
  else {
    if(destination < last) moveLeft();
    else moveRight();
  }
  while(!readTower(destination));
  stopMove(); 
}

//Va hasta una estación y recoge una pieza(suponiendo que la hay)
void pickFrom(byte origin) {
  goTo(origin);
  pick();
}

//Va hasta una estación y suelta una pieza(suponiendo que está agarrada)
void placeIn(byte destination) {
  goTo(destination);
  place();
}

//Transporta una pieza de una estación a otra(suponiendo que la hay)
void translate(byte origin, byte destination) {
  pickFrom(origin);
  placeIn(destination);
}

//método interfaz para hanoi
void hanoi(byte origin, byte destination) {
  byte rem = origin ^ destination;
  hanoiAux(3, origin, destination, rem);
}

//funcion para hanoi(algoritmo sacado de: https://medium.freecodecamp.org) 
void hanoiAux(byte n, byte origin, byte destination, byte aux) {
  if(n == 1) translate(origin, destination);
  else {
    hanoiAux(n-1, origin, aux, destination);
    translate(origin, destination);
    hanoiAux(n-1, aux, destination, origin);
  }
}
