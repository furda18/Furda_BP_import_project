#include "my_solution.h"

#include <fs/nvs.h>
#include <stdio.h>

#include <devicetree.h>
#include <drivers/gpio.h>
#include <stdio.h>
#include <stdlib.h> //for using the function sleep
#include <time.h>

/*Temperature and Humidity*/

#include <drivers/sensor.h>
#include <stdio.h>
#include <sys/util.h>

// maybe for humidity
#include <inttypes.h>

//#include <drivers/gpio.h>
#include <logging/log.h>

LOG_MODULE_REGISTER(app, CONFIG_LOG_DEFAULT_LEVEL);

#define CONFIG_LENGTH 7

/*Flashing Preamle*/
#include <device.h>
#include <drivers/flash.h>
#include <fs/nvs.h>
#include <storage/flash_map.h>
#include <string.h>
#include <sys/reboot.h>
#include <zephyr.h>

static struct nvs_fs fs;

#define STORAGE_NODE_LABEL storage

#define KEY_ID 2

/*definovanie pamate, este navyse su tie reboot countery*/
int rc = 0;
uint8_t *key;
struct flash_pages_info info;
const struct device *flash_dev;

// https://www.quora.com/How-do-I-get-the-function-name-from-a-variable-in-C-I-am-passing-a-function-A-into-function-B-How-can-I-print-out-functions-A-name-from-function-B

// momentalne iba 5 roznych instrukcii, mozno to je aj max dlzka bufferu idk

struct Logic_deciders {
  int logic_value;
  void *logic_name;
} first_byte[10];

struct Logic_deciderss {
  int logic_value;
  char *logic_name;
} fourth_byte[5];

static int fourth_counter = 0;
static int first_counter = 0;
static bool config_has_been_written = false;

static int measured_value;

// akcia a reakcia su jedna funkcia (navrh referencia)

// sem mi pride napriklad measure(temperature)
void register_input(uint8_t hexvalue, char *information) {
  fourth_byte[fourth_counter].logic_name = information;
  fourth_byte[fourth_counter].logic_value = hexvalue;
  fourth_counter += 1;
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

  // printf("RESOLVE: %s\n", value_incoming);

  if (config_has_been_written == false) {
    printf("No config written yet!\n");
    return;
  }

  printf("SOM V MOJOM RESOLVE\n");
  for (int i = 0; i < value_incoming_length; i++) {
    printf("..!!.. value_incoming[%d] = ", i);
    printf("%" PRIx32 "\n", value_incoming[i]);
    printf("or: %d\n", value_incoming[i]);
  }

  int number_of_configs = 0;
  if (value_incoming_length < CONFIG_LENGTH) {
    number_of_configs = 1;
  } else {
    number_of_configs = value_incoming_length / CONFIG_LENGTH;

    if (value_incoming_length % CONFIG_LENGTH != 0) {

      // printf("number_of_configs % CONFIG_LENGTH = %d / %d = %d\n", value_incoming_length, CONFIG_LENGTH, number_of_configs);
      number_of_configs += 1;
    }
  }

  printf("Number of configs = %d / %d = %d\n", value_incoming_length, CONFIG_LENGTH, number_of_configs);

  // id of first bye
  int always_first_byte = 0;

  // action+reaction
  for (int iteration = 0; iteration < number_of_configs; iteration++) {
    
    void (*execute_action)();
    int (*execute_input)();


    for (int i = 0; i < first_counter; i++) {
      if (first_byte[i].logic_value == value_incoming[always_first_byte + 0]) {
        printf("ZHODA v 0tom: %d %d\n", value_incoming[always_first_byte + 0], first_byte[i].logic_value);
        execute_action = first_byte[i].logic_name;
     }
    }

    //input
    for (int i = 0; i < fourth_counter; i++) {
      if (always_first_byte + 3 > value_incoming_length) {
        continue;
      } else {
        if (fourth_byte[i].logic_value == value_incoming[always_first_byte + 3]) {
          printf("ZHODA v 3tom: %d %d\n", value_incoming[always_first_byte + 3], fourth_byte[i].logic_value);

          execute_input = fourth_byte[i].logic_name;
          
        }
      }
    }

    
    int breaking_point = 0;

    if (always_first_byte + 4 > value_incoming_length) {
      continue;
    } else {
      breaking_point = value_incoming[always_first_byte + 4];
    }
    
    
     if (always_first_byte + 5 > value_incoming_length) {
      continue;
    } else {
      if(value_incoming[always_first_byte + 5] == 2){
        breaking_point *= (-1);
        printf("Breaking point is negated *(-1)\n");
      }
    }

    printf("BREAKING POINT: %d\n", breaking_point);

    // more/less/same
    if (always_first_byte + 6 > value_incoming_length) {
      continue;
    } else {
      //same
      if(value_incoming[always_first_byte + 6] == 0){
        if( execute_input() ==  breaking_point){
        execute_action();
        }
        
      }

      //more
      if(value_incoming[always_first_byte + 6] == 1){
        if( execute_input() >  breaking_point){
        execute_action();
        }
        
      }

      //less
      if(value_incoming[always_first_byte + 6] == 2){
        if( execute_input() <  breaking_point){
        execute_action();
        }
      }



    }


     // when we need time between executing configs,
    if (always_first_byte + 1 > value_incoming_length) {
      continue;
    } else {
      printf("value_incoming[%d]: sleep time: %d decisecond)\n", always_first_byte + 1, value_incoming[always_first_byte + 1] * 10000);
      k_msleep((value_incoming[always_first_byte + 1] * 10000));
    }
    if (always_first_byte + 2 > value_incoming_length) {
      continue;
    } else {
      printf("value_incoming[%d]: sleep time: %d miliseconds\n", always_first_byte + 2, value_incoming[always_first_byte + 2] * 100);
      k_msleep((value_incoming[always_first_byte + 2] * 100));
    }

    


   

    always_first_byte += CONFIG_LENGTH;

  //end of iteration
  }

  //// 5 dajme tomu ze senzor nameral vsetky hodnoty, preto tu vieme, ze
  //// ci riesime teplotu alebo humiditu

  //// 6 zlomovy bod
  //// 7 +/-
  //// 8 <>=

  //// tu sa budu diat vsetky tie pravidla ostatne
  // tu potrebujem komplet konfiguraciu
}

static void process_sample(const struct device *dev) {
  static unsigned int obs;
  struct sensor_value temp, hum;
  if (sensor_sample_fetch(dev) < 0) {
    printf("Sensor sample update error\n");
    return;
  }

  if (sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &temp) < 0) {
    printf("Cannot read HTS221 temperature channel\n");
    return;
  }

  if (sensor_channel_get(dev, SENSOR_CHAN_HUMIDITY, &hum) < 0) {
    printf("Cannot read HTS221 humidity channel\n");
    return;
  }
}

static void hts221_handler(const struct device *dev,
    const struct sensor_trigger *trig) {
  process_sample(dev);
}

int measure(char *get_value) {

  const struct device *dev_sensor = device_get_binding("HTS221");

  if (dev_sensor == NULL) {
    printf("Could not get HTS221 device\n");
    return;
  }

  if (IS_ENABLED(CONFIG_HTS221_TRIGGER)) {
    struct sensor_trigger trig = {
        .type = SENSOR_TRIG_DATA_READY,
        .chan = SENSOR_CHAN_ALL,
    };
    if (sensor_trigger_set(dev_sensor, &trig, hts221_handler) < 0) {
      printf("Cannot configure trigger\n");
      return;
    }
  }

  struct sensor_value temp, hum;

  if (sensor_sample_fetch(dev_sensor) < 0) {
    printf("Sensor sample update error\n");
    return;
  }

  if (sensor_channel_get(dev_sensor, SENSOR_CHAN_AMBIENT_TEMP, &temp) < 0) {
    printf("Cannot read HTS221 temperature channel\n");
    return;
  }

  if (sensor_channel_get(dev_sensor, SENSOR_CHAN_HUMIDITY, &hum) < 0) {
    printf("Cannot read HTS221 humidity channel\n");
    return;
  }

  int sensor_value;
  if (get_value == "temp") {
    /* display temperature */
    printf("\n 1. Temperature:%d C\n", temp.val1);
    sensor_value = temp.val1;
  }

  if (get_value == "hum") {
    /* display humidity */
    printf("\n 2. Humidity:%d %%\n", hum.val1);
    sensor_value = hum.val1;
  }

  return sensor_value;
}

int get_temperature_value() {
  return measure("temp");
}

int get_humidity_value() {
  return measure("hum");
}

void turn_on_led0() {
  const struct device *dev_t;
  bool led_is_on_t = true;
  int ret_t;

  dev_t = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led0), gpios));
  ret_t = gpio_pin_configure(dev_t, DT_GPIO_PIN(DT_ALIAS(led0), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led0), gpios));
  gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led0), gpios), (int)led_is_on_t);
}

void turn_on_led1() {
  const struct device *dev_t;
  bool led_is_on_t = true;
  int ret_t;

  dev_t = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led1), gpios));
  ret_t = gpio_pin_configure(dev_t, DT_GPIO_PIN(DT_ALIAS(led1), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led1), gpios));
  gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led1), gpios), (int)led_is_on_t);
}

void turn_on_led2() {
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
  bool led_is_on_t = false;
  int ret_t;

  dev_t = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led2), gpios));
  ret_t = gpio_pin_configure(dev_t, DT_GPIO_PIN(DT_ALIAS(led2), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led2), gpios));
  gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led2), gpios), (int)led_is_on_t);
}