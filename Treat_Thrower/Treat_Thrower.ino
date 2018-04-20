#include <Servo.h>

// h-bridge motor control pins
const int control1 = 2;
const int control2 = 3;

// h-bridge motor enabler
const int enabler = 5;

// bumber switches
const int collider = 7;

//button input and light control
const int button = 13;
const int buttonLight = 12;

const int servoPin = 9;
Servo servo;

void setup() {
  pinMode(control1, OUTPUT);
  pinMode(control2, OUTPUT);
  pinMode(enabler, OUTPUT);

  pinMode(collider, INPUT);

  pinMode(button, INPUT);
  pinMode(buttonLight, OUTPUT);

  servo.attach(servoPin);

  Serial.begin(9600);

  servo.write(0);
}

void loop() {
  if(digitalRead(button) != 0) {
     Serial.println("Button pushed");
     digitalWrite(buttonLight, LOW);

     load();
     delay(500);
     shoot();
     
     delay(100);
  }
  
  digitalWrite(buttonLight, HIGH);
}

void shoot() {
  Serial.println("shooting ...");

  // begin moving arm forward
  forward();
  analogWrite(enabler, 255);
  Serial.println("going forward");

  delay(250);

  // continue moving forward until bumper contact
  while(digitalRead(collider) == 0) {
    Serial.println("... forward");
    delay(10);
  }

  // stop and wait
  analogWrite(enabler, 0);
  delay(100);

  // begin moving arm backward
  backward();
  analogWrite(enabler, 75);
  Serial.println("going backward");

  delay(250);

  // continue moving backward until bumper contact
  while(digitalRead(collider) == 0) {
    Serial.println("... backward");
    delay(10);
  }

  // stop
  analogWrite(enabler, 0);
  delay(100);
  Serial.println("End shooting procedure");
}

void load() {
  Serial.println("loading ...");

  // move servo forward to release treat
  servo.write(90);
  delay(300);

  // return servo to starting position
  servo.write(0);
  delay(300);
}

// sets the h-brdge to power the motors in reverse
void backward() {
  digitalWrite(control1, LOW);
  digitalWrite(control2, HIGH);
}

//sets the h-bridge to power the motors forward
void forward() {
  digitalWrite(control1, HIGH);
  digitalWrite(control2, LOW);
}
