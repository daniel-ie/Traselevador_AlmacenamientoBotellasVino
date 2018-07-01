#include <Stepper.h>
#include "Arduino.h"


const int stepsPerRev = 300;
int var=0 ;
boolean once = true ;

int dirPin, stepperPin ;

//driver uno
int dirPin1 = 8, stepperPin1 = 9 ;
int dirPin2 = 10, stepperPin2 = 11 ;

//driver dos
int dirPin3 = 4, stepperPin3 = 5;
int dirPin4 = 6, stepperPin4 = 7;



class Transelevador{
public:
    // Constructor
    Transelevador(){} ;

    // Metodos
    int getStepper(char stepper) ;
    void stepperEvent(char stepper, int _speed, int steps, int dir) ;
    void stepperEvent(char stepperI, int _speedI, int stepsI, int dirI, 
                      char stepperII, int _speedII, int stepsII, int dirII) ;    
} ;

// ---------------------------------- Cuerpo de los metodos ---------------------------------- //
// Ejecucion de 1 Stepper  
void Transelevador::stepperEvent(char stepper, int _speed, int steps, int dir){
    getStepper(stepper) ;
    Stepper myStepper(stepsPerRev, dirPin, stepperPin) ;

    myStepper.setSpeed(_speed) ;
    for(int i=0; i<steps; i++)
        myStepper.step(dir) ;
         
    Serial.print("Ejecucion de stepper (") ; Serial.print(stepper) ;
    Serial.print(") a (") ;                  Serial.print(_speed) ; 
    Serial.println(") rpm") ;
    
    delay(2000) ;
}
// Ejecucion de 2 Stepper
void Transelevador::stepperEvent(char stepperI, int _speedI, int stepsI, int dirI, 
                                 char stepperII, int _speedII, int stepsII, int dirII){
    getStepper(stepperI) ;
    Stepper myStepperI(stepsPerRev, dirPin, stepperPin) ;

    getStepper(stepperII) ;
    Stepper myStepperII(stepsPerRev, dirPin, stepperPin) ;

    myStepperI.setSpeed(_speedI) ;
    myStepperII.setSpeed(_speedII) ;    
    for(int i=0; i<stepsI; i++){
        myStepperI.step(dirI) ;
        myStepperII.step(dirII) ;
    }
    
    Serial.print("Ejecucion de steppers (") ; Serial.print(stepperI) ;
    Serial.print(" y ") ;                     Serial.print(stepperII) ;
    Serial.print(") a (") ;                   Serial.print(_speedI) ;
    Serial.print(" y ") ;                     Serial.print(_speedII) ;
    Serial.println(") rpm") ;

    delay(2000) ;
}
// Setea los pines para el stepper en ejecucion
int Transelevador::getStepper(char stepper){
  switch(stepper){
    case '1':
      dirPin = dirPin1 ;
      stepperPin = stepperPin1 ;
      break ;
    case '2':
      dirPin = dirPin2 ;
      stepperPin = stepperPin2 ;
      break ;
    case '3':
      dirPin = dirPin3 ;
      stepperPin = stepperPin3 ;
      break ;
    case '4':
      dirPin = dirPin4 ;
      stepperPin = stepperPin4 ;
      break ;
  } 
}
// ------------------------------------------------------------------------------------------- //


// Crea el objeto transelevador!
Transelevador transelevador ;

void setup(){
  Serial.begin(9600) ;
}



void loop(){
  rutina1() ;
  
  Serial.println("\n\n\n") ;
  delay(3000) ;
}

void rutina1(){
///////////////////////// Un solo motor en funcionamiento a la vez /////////////////////////
//------ transelevador.stepperEvent(char stepper, int _speed, int steps, int dir)

////////////////////////// Dos motores en funcionamiento a la vez //////////////////////////
//------ transelevador.stepperEvent(char stepperI, int _speedI, int stepsI, int dirI, 
//                                  char stepperII, int _speedII, int stepsII, int dirII) 

//1. Se activa Motor 3 para hacer las uñas para adelante para meterse debajo de la tarima
  if(once == true){
    transelevador.stepperEvent('3', 3000, 34000, -1) ;
    once = false ;  
  }
  
//2. Se activa Motores 1 y 2 para levantar la tarima por unos breves segundos 
  transelevador.stepperEvent('1', 800, 8000, 1, '2', 400, 8000, 1) ;

//3. Se activa Motor 3 para hacer la tarima hacia atrás (puede ser no todo el camino hacia atrás)
  transelevador.stepperEvent('3', 400, 8000, 1) ;

//4. Se activa Motor 4 para recorrer todo el riel hasta el otro extremo del sistema 
  transelevador.stepperEvent('4', 400, 8000, 1) ;

//5. Se activa Motor 3 y se hace hacia adelante en el lugar de almacenamiento 
  transelevador.stepperEvent('3', 400, 8000, -1) ;

//6. Se activa Motores 1 y 2 para bajar el producto hasta el lugar de almacenamiento.
  transelevador.stepperEvent('1', 800, 8000, -1, '2', 400, 8000, -1) ;

//7. Se activa Motor 3 para hacerse para atrás.
  transelevador.stepperEvent('3', 400, 8000, 1) ;

//8. Se activa Motor 1 y 2 para volver a la altura de la “posición cero”, activa final de carrera
  transelevador.stepperEvent('1', 800, 8000, 1, '2', 400, 8000, 1) ;

//9. Se activa Motor 4 y vuelve a “posición cero”, activa final de carrera
  transelevador.stepperEvent('4', 400, 8000, -1) ;

//10. Se activa Motor 3 para volver a “posición cero”, activa final de carrera
  transelevador.stepperEvent('3', 400, 8000, -1) ;
  
}
