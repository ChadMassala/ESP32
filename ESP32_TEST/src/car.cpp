#include "car.h"

void Car:: print_chassis_id(){
    Serial.print("Vehicle Chassis ID");
    Serial.println(Car::_chassis_id);
    Serial.println(" ");
}


void Car::set_chassis_id(String chassis_id){
    Car::_chassis_id = chassis_id;
}

String Car::getcolour(){
    switch(Car::color){
        case blue: 
           return "Blue";
        case red:
           return "Red";
        case white:
           return "White";
        case green:
           return "Green";
        case yellow:
           return "Yellow";
    }
}

Car::Car(String car_make, String car_model, int car_year_model){
    Car::make       = car_make;
    Car::model      = car_model;
    Car::year_model = car_year_model;
}

void Car::print_car_attributes(){
    Serial.println("Vehicle make: " + String(Car::make));
    Serial.println("Vehicle Model: " + String(Car::model));
    Serial.println("Vehicle Year: " + String(Car::year_model));

    Serial.println("Vehicle Color: " + (Car::getcolour()));
    Serial.println("Vehicle Registration Number : " + (Car::registration_number));

    Car::print_chassis_id();
}
