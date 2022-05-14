#include "my_solution.h"    

#include <stdio.h>
#include <fs/nvs.h>



//https://www.quora.com/How-do-I-get-the-function-name-from-a-variable-in-C-I-am-passing-a-function-A-into-function-B-How-can-I-print-out-functions-A-name-from-function-B


//momentalne iba 5 roznych instrukcii, mozno to je aj max dlzka bufferu idk


struct Logic_deciders{
         int logic_value;
         void* logic_name;
}first_byte[10];


struct Logic_deciderss{
         int logic_value;
         char* logic_name;
}sixth_bytee[5];

static int sixth_counter = 0;
static int first_counter = 0;

                       
//akcia a reakcia su jedna funkcia (navrh referencia)


//sem mi pride napriklad measure(temperature)
void register_input(uint8_t hexvalue, char* information){
    sixth_bytee[sixth_counter].logic_name = information;
    sixth_bytee[sixth_counter].logic_value = hexvalue;
    sixth_counter+=1;
}

//sem pride napriklad turn on led0
void register_reaction(uint8_t hexvalue, void (*f)()){
    first_byte[first_counter].logic_name = f;
    first_byte[first_counter].logic_value = hexvalue;
    first_counter+=1;
}
//execute function which came here
void execute_function_named(void (*f)(void)){
    f();
}

//toto bude stale volane v maine
//sem mi pride zakodovany (0x01, namerana_teplota );
// vlastne to 0x01 mi povie ze ide o tepotu a nie humiditu
//teraz 
//precitaj a konaj podla zapisanej konfiguracie
//int namerana_hodnota, int namerana_hodnota_coho,
void resolve(char *value_incoming){
  
  printf("SOM V MOJOM RESOLVE\n");
  for (int i = 0; i < 2; i++)
    {
        printf("..!!.. value_incoming[%d] = ", i);
        printf("%" PRIx32 "\n", value_incoming[i]);
        
    }
  //precitaj co je napisane v pamati

  
  /////*Thingy kod*/
  //const struct device *dev_t;
  //bool led_is_on_t = true;
  //int ret_t;

  //bool led_verification_t = false;

  //if(vystup == "set_led0"){
  //  printk("config 1, led 0\n");
  //  dev_t = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led0), gpios));
  //  ret_t = gpio_pin_configure(dev_t, DT_GPIO_PIN(DT_ALIAS(led0), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led0), gpios));
  //  gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led0), gpios), (int)led_is_on_t);
  //}
  //     //           if(vystup == "set_led1"){
  //     //             printk("config 2, led 1\n");
  //     //             dev_t = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led1), gpios));
  //     //             ret_t = gpio_pin_configure(dev_t, DT_GPIO_PIN(DT_ALIAS(led1), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led1), gpios));       
  //     //             gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led1), gpios), (int)led_is_on_t);
  //     //           }
  //     //           if(vystup == "set_led2"){               
  //     //             printk("config 3, led 2\n");
  //     //             dev_t = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led2), gpios));
  //     //             ret_t = gpio_pin_configure(dev_t, DT_GPIO_PIN(DT_ALIAS(led2), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led2), gpios));
  //     //             gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led2), gpios), (int)led_is_on_t);
  //     //           }

  //     //if(vystup0 == "turn_off"){
  //     //             led_is_on_t = false;
  //     //             LOG_INF("turning led off\n");                                     
  //     //           }

  //    //zapni
  //    if(vystup0 == "turn_on"){
  //      led_is_on_t = true;
  //      LOG_INF("turning led on\n");                                             
  //    }


  //0 zapni
  //1 led0
  //2 blik 5x
  //3
  //4 kazdu sekundu
  //5 dajme tomu ze senzor nameral vsetky hodnoty, preto tu vieme, ze
  //ci riesime teplotu alebo humiditu

  //6 zlomovy bod
  //7 +/-
  //8 <>=
  
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
  //value[6] == 01{
  //meraj teplotu}
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
  //led_handler(0, true);
  printf("\n\nHAHAHAHAHAHA som v turn_on_led0/n/n/n/");
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



///
//#include <stdio.h>
//#include <stdlib.h>
//#include <stdint.h>

//struct Logic_deciderss{
//          int logic_value;
//          void* logic_name;

//}first_byte[5], sixth_bytee[5];

//static int first_counter = 0;

//void register_reaction(uint8_t hexvalue, void (*f)()){
//  //execute function which came here+
//    first_byte[first_counter].logic_name = f;
//    first_byte[first_counter].logic_value = hexvalue;
//    first_counter++;
//}

//void turn_on_led0(){
//    printf("TURNING led0 on");
//}


//int main()
//{

//    void (*fun_ptr)() = &turn_on_led0;



//    register_reaction(1, fun_ptr);

//    register_reaction(2, fun_ptr);


//    for(int a=0; a<2; a++){
//          printf("!!! \n %d. REACTION: %d \ !!!\n ", a, first_byte[a].logic_value);

//          void (*fun_ptrr)() = first_byte[a].logic_name;
//          fun_ptrr();
//          //function_ole();
//    }


//    printf("Hello world!\n");
//    return 0;
//}
///