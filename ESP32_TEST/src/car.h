#include <stdio.h>
#include "Arduino.h"

#ifndef car_h
#define car_h

enum Color{blue, red, white, green, yellow};

class Car{
    public:
      Car(String car_make, String car_model, int car_year_model);
      String make;
      String model;
      int year_model;

      String getcolour();
      String registration_number;

      void print_chassis_id();
      void set_chassis_id(String chassis_id);
      void print_car_attributes();

      Color color;


    private:
      String _chassis_id;
};

#endif