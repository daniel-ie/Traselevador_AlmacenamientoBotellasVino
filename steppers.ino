#include <Stepper.h>
#include "Arduino.h"


const int stepsPerRev = 300;

//driver uno
int dirPin = 8;
int var=0;
int stepperPin = 9;
int dirPin2 = 10;
int stepperPin2 = 13 ; //11;

//driver dos
int dirPin3 = 4;
int stepperPin3 = 5;
int dirPin4 = 6;
int stepperPin4 = 7;
//azul,amarillo,rojo,verde
//x01a
//y01A


//Stepper myStepperParam(stepsPerRev, dirPin2, stepperPin2);


class Morse{
public:
    // Constructor
    Morse(int pin) ;

    // Metodos
    void stepperEvent(int _speed, int steps, int dir, int dirPin, int stepperPin) ;

private:
    int _pin ;
    
} ;

/// Constructor
Morse::Morse(int pin){
  pinMode(pin, OUTPUT) ;
  pinMode(5, OUTPUT) ; // stepper3
  _pin = pin ;
}

/// Metodos

void Morse::stepperEvent(int _speed, int steps, int dir, int dirPin, int stepperPin){   
    Stepper myStepperParam(stepsPerRev, dirPin, stepperPin) ;

    myStepperParam.setSpeed(_speed) ;
    for(int i=0; i<steps; i++)
        myStepperParam.step(dir) ;

    delay(2000) ;
}

/*Stepper myStepperParam(stepsPerRev,dirPin2,stepperPin2);
Stepper myStepper(stepsPerRev,dirPin,stepperPin);
Stepper myStepper2(stepsPerRev,dirPin2,stepperPin2);
Stepper myStepper3(stepsPerRev,dirPin3,stepperPin3);
Stepper myStepper4(stepsPerRev,dirPin4,stepperPin4);
*/

Morse blynkMorse(13) ;


void setup() {

}

void loop(){
  blynkMorse.stepperEvent(1, 40, -1, dirPin3, stepperPin3) ;
//  blynkMorse.stepperEvent(5, 10, -1, dirPin2, stepperPin2) ;
//  blynkMorse.stepperEvent(15, 10, -1, dirPin2, stepperPin2) ;

  delay(1000) ;

  blynkMorse.stepperEvent(1, 40, -1, dirPin2, stepperPin2) ;
  delay(1000) ;
}

/*
if (var==0) {
//1. Se activa Motor 3 para hacer las uñas para adelante para meterse debajo de la tarima     
    myStepper3.setSpeed(3000);
    for(int i=0; i<34000; i++){
        myStepper3.step(-1);
    }
    delay(2000);
    var=1;
}

if (var==1) {
//2. Se activa Motores 1 y 2 para levantar la tarima por unos breves segundos
    myStepper.setSpeed(800);
    myStepper2.setSpeed(400);
    for(int i=0; i<8000; i++){
        myStepper.step(1);
        myStepper2.step(1);
    }
    delay(2000);
    var=2;
}


if (var==2) {
//3. Se activa Motor 3 para hacer la tarima hacia atrás (puede ser no todo el camino hacia atrás)
    myStepper3.setSpeed(400);
    for(int i=0; i<8000; i++){
        myStepper3.step(1);
    }
    delay(2000);
    var=3;
}

if (var==3) {
//4. Se activa Motor 4 para recorrer todo el riel hasta el otro extremo del sistema 
  myStepper4.setSpeed(400);
  for(int i=0; i<8000; i++){
  myStepper4.step(1);
  }
  delay(2000);
  var=4;
  }
if (var==4) {
//5. Se activa Motor 3 y se hace hacia adelante en el lugar de almacenamiento 
  myStepper3.setSpeed(400);
  for(int i=0; i<8000; i++){
  myStepper3.step(-1);
  }
  delay(2000);
  var=5;
  }

if (var==5) {
//6. Se activa Motores 1 y 2 para bajar el producto hasta el lugar de almacenamiento.
  myStepper.setSpeed(800);
  myStepper2.setSpeed(400);
  for(int i=0; i<8000; i++){
  myStepper.step(-1);
  myStepper2.step(-1);
  }
  delay(2000);
  var=6;
  }

if (var==6) {
//7. Se activa Motor 3 para hacerse para atrás.
  myStepper3.setSpeed(400);
  for(int i=0; i<8000; i++){
  myStepper3.step(1);
  }
  delay(2000);
  var=7;
  }
  
if (var==7) {
//8. Se activa Motor 1 y 2 para volver a la altura de la “posición cero”, activa final de carrera
  myStepper.setSpeed(800);
  myStepper2.setSpeed(400);
  for(int i=0; i<8000; i++){
  myStepper.step(1);
  myStepper2.step(1);
  }
  delay(2000);
  var=9;
  }
if (var==9) {
//9. Se activa Motor 4 y vuelve a “posición cero”, activa final de carrera
  myStepper4.setSpeed(400);
  for(int i=0; i<8000; i++){
  myStepper4.step(-1);
  }
  delay(2000);
  var=10;
  }

if (var==10) {
//10. Se activa Motor 3 para volver a “posición cero”, activa final de carrera
  myStepper3.setSpeed(400);
  for(int i=0; i<8000; i++){
  myStepper3.step(-1);
  }
  delay(2000);
  var=1;
  }

  }
  

*/
