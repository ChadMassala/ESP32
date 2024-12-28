#include <Arduino.h>
#include "TFT_eSPI.h"
#include "car.h"

// put function declarations here:
int myFunction(int, int);
int myFunction1(int *localPointer);
int myFunction2(int localVar);
void myFunction3(TFT_eSPI *localTFTPointer);
void myFunction4(TFT_eSPI localTFT);
int myDelay = 1000;

namespace car{
  int engine_capacity;
  int color;
}

namespace MotorCycle{
  int engine_capacity;
  int color;
}

void setup() {
  //Serial Baudrate
  Serial.begin(9600);

  while(!Serial){
    ; //Wait for serial port to connect
  }
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
  pinMode(2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Experiment 1: Find the Storage address of a Variable
  Serial.println("Experiment #1");
  Serial.print("VariableSize: ");
  Serial.println(myDelay);
  Serial.print("My Variable Location: ");
  Serial.println((int)&myDelay, HEX);     //Dereference to get the variable memory location, cast it to it and convert to HEX
  Serial.println(" ");
  
  //Experiment 2: Access the Value of a Variable using a Pointer
  Serial.println("Experiment #2");
  int *myDelay_pointer1 = &myDelay;
  Serial.print("Value at Location: ");
  Serial.print((int)&myDelay, HEX);
  Serial.print(" is ");
  Serial.println(*myDelay_pointer1);
  Serial.println(" ");

  //Experiment 3:Change the Value of a Variable using a Pointer
  Serial.println("Experiment #3");
  *myDelay_pointer1 = 500;
  Serial.print("Value at Location: ");
  Serial.print((int)&myDelay, HEX);
  Serial.print(" is ");
  Serial.println(*myDelay_pointer1);
  Serial.println("The new value is " + String(myDelay));
  Serial.println(" ");

  //Experiment 4: Using another pointer to access the same Variable
  Serial.println("Experiment #4");
  int *myDelay_pointer2 = &myDelay;
  *myDelay_pointer2 = 250;
  Serial.print("Value at Location: ");
  Serial.print((int)&myDelay, HEX);
  Serial.print(" is Pointer2: ");
  Serial.println(*myDelay_pointer2);
  Serial.println("The value of Pointer1:" + String(*myDelay_pointer1));
  Serial.println(" ");


  digitalWrite(2, HIGH);
  //Serial.println("ON");
  delay(myDelay);

  digitalWrite(2, LOW);
  //Serial.println("OFF");
  delay(myDelay);

 //Experiment 5:Pass a primitive to a function using a pointer or a reference
  Serial.println("Experiment #5");
  myFunction1(&myDelay);
  Serial.print("Value From Function1 is: ");
  Serial.println(myDelay);
  myFunction2(myDelay);
  Serial.println(" ");

  //Experiment 6: Pass an object to a function via a pointer or reference
  Serial.println("Experiment #6");
  TFT_eSPI TFT = TFT_eSPI();
  Serial.print("TFT Object Location: ");
  Serial.println((int)&TFT, HEX);
  myFunction3(&TFT);
  myFunction4(TFT);
  Serial.println(" ");


  Car myCar("Opel", "Corsa", 2007);
  myCar.color = green;
  myCar.registration_number = "CJ95105";
  myCar.set_chassis_id("ABSS45T006981");
  myCar.print_car_attributes();

  //Car Specs
  car:: color = 1;
  car::engine_capacity = 2000;
  Serial.println("My car's specs:");
  Serial.println("Color: " + String(car::color));
  Serial.println("Engine Capacity: " + String(car::engine_capacity));
  Serial.println(" ");
  //Motor Specs
  MotorCycle:: color = 2;
  MotorCycle::engine_capacity = 1500;
  Serial.println("My Motor's specs");
  Serial.println("Color: " + String(MotorCycle::color));
  Serial.println("Engine Capacity: " + String(MotorCycle::engine_capacity));
  Serial.println(" ");
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}

int myFunction1(int *localPointer){
   Serial.print("Function1 Local pointer location: ");
   Serial.println((int)localPointer, HEX);
   *localPointer = 1000;
   return 0;
}

int myFunction2(int localVar){
   Serial.print("Function2 Local pointer location: ");
   Serial.println((int)&localVar, HEX);
   return 0;
}

void myFunction3(TFT_eSPI *localTFTPointer){
   Serial.print("Function3 localTFTPointer location: ");
   Serial.println((int)localTFTPointer, HEX);
}

void myFunction4(TFT_eSPI localTFT){
   Serial.print("Function4 LocalTFT location: ");
   Serial.println((int)&localTFT, HEX);
  
}