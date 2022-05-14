#include "my_solution.h"

#include <fs/nvs.h>
#include <stdio.h>

#include <devicetree.h>
#include <drivers/gpio.h>
#include <stdio.h>
#include <stdlib.h> //for using the function sleep
#include <time.h>

#define CONFIG_LENGTH 8

// https://www.quora.com/How-do-I-get-the-function-name-from-a-variable-in-C-I-am-passing-a-function-A-into-function-B-How-can-I-print-out-functions-A-name-from-function-B

// momentalne iba 5 roznych instrukcii, mozno to je aj max dlzka bufferu idk

struct Logic_deciders {
  int logic_value;
  void *logic_name;
} first_byte[10];

struct Logic_deciderss {
  int logic_value;
  char *logic_name;
} sixth_bytee[5];

static int sixth_counter = 0;
static int first_counter = 0;
static bool config_has_been_written = false;

// akcia a reakcia su jedna funkcia (navrh referencia)

// sem mi pride napriklad measure(temperature)
void register_input(uint8_t hexvalue, char *information) {
  sixth_bytee[sixth_counter].logic_name = information;
  sixth_bytee[sixth_counter].logic_value = hexvalue;
  sixth_counter += 1;
}

// sem pride napriklad turn on led0
void register_reaction(uint8_t hexvalue, void (*f)()) {
  first_byte[first_counter].logic_name = f;
  first_byte[first_counter].logic_value = hexvalue;
  first_counter += 1;
}
// execute function which came here
void execute_function_named(void (*f)(void)) {
  f();
}

// toto bude stale volane v maine
// sem mi pride zakodovany (0x01, namerana_teplota );
//  vlastne to 0x01 mi povie ze ide o tepotu a nie humiditu
// teraz
// precitaj a konaj podla zapisanej konfiguracie
// int namerana_hodnota, int namerana_hodnota_coho,
void resolve(char *value_incoming, int value_incoming_length) {

  if (config_has_been_written == false) {
    printf("No config written yet!\n");
    return;
  }
  printf("SOM V MOJOM RESOLVE\n");
  for (int i = 0; i < value_incoming_length; i++) {
    printf("..!!.. value_incoming[%d] = ", i);
    printf("%" PRIx32 "\n", value_incoming[i]);
  }

  int number_of_configs;
  if (value_incoming_length < CONFIG_LENGTH) {
    number_of_configs = 1;
  } else {
    number_of_configs = value_incoming_length / CONFIG_LENGTH;

    if (value_incoming_length % CONFIG_LENGTH != 0) {
      
      printf("number_of_configs % CONFIG_LENGTH = %d / %d = %d\n", value_incoming_length, CONFIG_LENGTH, number_of_configs);
      number_of_configs += 1;
    }
  }

  printf("Number of configs = %d / %d = %d\n", value_incoming_length, CONFIG_LENGTH, number_of_configs);

  // id of first bye
  int always_first_byte = 0;

  // reading config after config
  for (int iteration = 0; iteration < number_of_configs; iteration++) {
    for (int i = 0; i < first_counter; i++) {
      if (first_byte[i].logic_value == value_incoming[always_first_byte + 0]) {
        printf("ZHODA %d %d\n", value_incoming[always_first_byte + 0], first_byte[i].logic_value);
        void (*execute_this_function)() = first_byte[i].logic_name;
        // how many times function should be executed
        if (always_first_byte + 1 > value_incoming_length) {
          break;
        } else {
          for (int repetition = 0; repetition < value_incoming[always_first_byte + 1]; repetition++) {
            execute_this_function();
            printf("Opakujem vykonanie funkcie\n");
          }
        }
      }
    }

    // when we need time between executing configs
    if (always_first_byte + 2 > value_incoming_length) {
      break;
    } else {
      printf("value_incoming[%d]: sleep time: %d decisecond)\n", always_first_byte + 2, value_incoming[always_first_byte + 2] * 10000);
      k_msleep((value_incoming[always_first_byte + 2] * 10000));
    }
    if (always_first_byte + 3 > value_incoming_length) {
      break;
    } else {
      printf("value_incoming[%d]: sleep time: %d miliseconds\n", always_first_byte + 3, value_incoming[always_first_byte + 3] * 100);
      k_msleep((value_incoming[always_first_byte + 3] * 100));
    }

    always_first_byte += CONFIG_LENGTH;
  }

  // 0 zapni
  // 1 led0
  // 2 blik 5x
  // 3
  // 4 kazdu sekundu
  // 5 dajme tomu ze senzor nameral vsetky hodnoty, preto tu vieme, ze
  // ci riesime teplotu alebo humiditu

  // 6 zlomovy bod
  // 7 +/-
  // 8 <>=

  // tu sa budu diat vsetky tie pravidla ostatne
  // tu potrebujem komplet konfiguraciu
}

int measure() {
  // podla 6teho bajtu sa rozhodujes, ci je to teplota alebo humidita
  // teda porovnas to co doslo na inpute s tym aka je value
  // value[6] == 01{
  // meraj teplotu}
  return 0;
}

int temperature_value() {
  return 0;
}

int humidity_value() {
  return 0;
}

void led_handler(int led_index, bool activation) {

  // const struct device *dev_t;
  // bool led_is_on_t = activation;
  // int ret_t;

  // dev_t = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led0), gpios));
  // ret_t = gpio_pin_configure(dev_t, DT_GPIO_PIN(DT_ALIAS(led0), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led0), gpios));
  // gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led0), gpios), (int)led_is_on_t);
}

void turn_on_led0() {
  // led_handler(0, true);
  printf("\n\nHAHAHAHAHAHA som v turn_on_led0/n/n/n/");
  const struct device *dev_t;
  bool led_is_on_t = true;
  int ret_t;

  dev_t = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led0), gpios));
  ret_t = gpio_pin_configure(dev_t, DT_GPIO_PIN(DT_ALIAS(led0), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led0), gpios));
  gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led0), gpios), (int)led_is_on_t);
}

void turn_on_led1() {
  printf("\n\nHAHAHAHAHAHA som v turn_on_led1/n/n/n/");
  const struct device *dev_t;
  bool led_is_on_t = true;
  int ret_t;

  dev_t = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led1), gpios));
  ret_t = gpio_pin_configure(dev_t, DT_GPIO_PIN(DT_ALIAS(led1), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led1), gpios));
  gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led1), gpios), (int)led_is_on_t);
}

void turn_on_led2() {
  printf("\n\nHAHAHAHAHAHA som v turn_on_led2/n/n/n/");
  const struct device *dev_t;
  bool led_is_on_t = true;
  int ret_t;

  dev_t = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led2), gpios));
  ret_t = gpio_pin_configure(dev_t, DT_GPIO_PIN(DT_ALIAS(led2), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led2), gpios));
  gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led2), gpios), (int)led_is_on_t);
}

void turn_off_led0() {
  const struct device *dev_t;
  bool led_is_on_t = false;
  int ret_t;

  dev_t = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led0), gpios));
  ret_t = gpio_pin_configure(dev_t, DT_GPIO_PIN(DT_ALIAS(led0), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led0), gpios));
  gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led0), gpios), (int)led_is_on_t);
}

void turn_off_led1() {
  const struct device *dev_t;
  bool led_is_on_t = false;
  int ret_t;

  dev_t = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led1), gpios));
  ret_t = gpio_pin_configure(dev_t, DT_GPIO_PIN(DT_ALIAS(led1), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led1), gpios));
  gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led1), gpios), (int)led_is_on_t);
}

void turn_off_led2() {
  const struct device *dev_t;
  bool led_is_on_t = true;
  int ret_t;

  dev_t = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led2), gpios));
  ret_t = gpio_pin_configure(dev_t, DT_GPIO_PIN(DT_ALIAS(led2), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led2), gpios));
  gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led2), gpios), (int)led_is_on_t);
}