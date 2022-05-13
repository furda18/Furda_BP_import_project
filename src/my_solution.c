#include "my_solution.h"    

#include <stdio.h>

//https://www.quora.com/How-do-I-get-the-function-name-from-a-variable-in-C-I-am-passing-a-function-A-into-function-B-How-can-I-print-out-functions-A-name-from-function-B


//momentalne iba 5 roznych instrukcii, mozno to je aj max dlzka bufferu idk


struct Logic_deciderss{
          int logic_value;
          char* logic_name;        
}first_byte[5], second_byte[5], sixth_byte[5];


                       
//akcia a reakcia su jedna funkcia (navrh referencia)


int foo()
{
    int cislo = 999;
    return cislo;
}

//void print_name_and_call(const char *name, void (*f)(void)) { 
//  printf("Calling %s()\n", name); 
//  f(); 
//} 

void register_input(unit8_t hexvalue, char* information){
}

void register_reaction(unit8_t hexvalue, void (*f)(void)){
  //execute function which came here
  f();
}

void resolve(uint8_t hexvalue_of_input, int value){

 // tu sa budu diat vsetky tie pravidla ostatne
  //tu potrebujem komplet konfiguraciu
  
}

int temperature_value(){
  return 0;
}

int humidity_value(){
  return 0;
}

void led_handler(int led_index, bool activation){
 
}


void turn_on_led0(){
  led_handler(0, true);
}

void turn_on_led1(){
  led_handler(1, true);
}

void turn_on_led2(){
  led_handler(2, true);
}



void turn_off_led0(){
  led_handler(0, false);
} 

void turn_off_led1(){
  led_handler(1, false);
}

void turn_off_led2(){
  led_handler(2, false);
}