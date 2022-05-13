#include "my_solution.h"    

#include <stdio.h>

#include <fs/nvs.h>





#define KEY_IDs 1
static struct nvs_fs fss;

/*definovanie pamate, este navyse su tie reboot countery*/
int rc = 0, cnt = 0, cnt_his = 0;
uint8_t *key;
uint32_t reboot_counter = 0U, reboot_counter_his;
struct flash_pages_info info;
const struct device *flash_dev;


//https://www.quora.com/How-do-I-get-the-function-name-from-a-variable-in-C-I-am-passing-a-function-A-into-function-B-How-can-I-print-out-functions-A-name-from-function-B


//momentalne iba 5 roznych instrukcii, mozno to je aj max dlzka bufferu idk


struct Logic_deciderss{
          int logic_value;
          char* logic_name;        
}first_byte[5], second_byte[5], sixth_byte[5];

static int sixth_counter = 0;


                       
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


//sem mi pride napriklad measure(temperature)
void register_input(uint8_t hexvalue, char* information){
  
    sixth_byte[sixth_counter].logic_name = information;
    sixth_byte[sixth_counter].logic_value = hexvalue;
    sixth_counter += 1;

    
}


//sem pride napriklad turn on led0
void register_reaction(uint8_t hexvalue, void (*f)(void)){
  //execute function which came here
  f();
  
}

//toto bude stale volane v maine
//sem mi pride zakodovany (0x01, namerana_teplota );
// vlastne to 0x01 mi povie ze ide o tepotu a nie humiditu
//teraz 
//precitaj a konaj podla zapisanej konfiguracie
void resolve(*data, int namerana_hodnota, int namerana_hodnota_coho){
  
  0 zapni
  1 led0
  2 blik 5x
  3
  4 kazdu sekundu
  5 dajme tomu ze senzor nameral vsetky hodnoty, preto tu vieme, ze
  ci riesime teplotu alebo humiditu

  6 zlomovy bod
  7 +/-
  8 <>=
  
 // tu sa budu diat vsetky tie pravidla ostatne
  //tu potrebujem komplet konfiguraciu
  //           //zlomovy bod - osetri
       //           int break_point = value[6];
       //           LOG_INF("Breaking point: %d\n", break_point); 
       //           //kladny=1 zaporny=2
       //           int positivity = value[7];
       //           LOG_INF("Plus(1)/Minus(2): %d\n", positivity); 
       //           if(positivity == 2){
       //             sensor_value = sensor_value*(-1);
       //           }
              
       //           int reaction_is = value[8];
       //           LOG_INF("Sensor value: %d vs\n",sensor_value);
  
}

int measure(){
  //podla 6teho bajtu sa rozhodujes, ci je to teplota alebo humidita
  //teda porovnas to co doslo na inpute s tym aka je value
  value[6] == 01{
  meraj teplotu}
  return 0;
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