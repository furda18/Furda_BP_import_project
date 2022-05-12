/* main.c - Application main entry point */

/*
 * Copyright (c) 2015-2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */



#include <zephyr/types.h>
#include <stddef.h>
#include <errno.h>
#include <sys/printk.h>
#include <sys/byteorder.h>


#include <settings/settings.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/conn.h>
#include <bluetooth/uuid.h>
#include <bluetooth/gatt.h>
#include <bluetooth/services/bas.h>
#include <bluetooth/services/hrs.h>

#include "cts.h"


#include "my_solution.c"



/*Flashing Preamle*/
#include <zephyr.h>
#include <sys/reboot.h>
#include <device.h>
#include <string.h>
#include <drivers/flash.h>
#include <storage/flash_map.h>
#include <fs/nvs.h>






static struct nvs_fs fs;

#define STORAGE_NODE_LABEL storage


#define KEY_ID 2


/*definovanie pamate, este navyse su tie reboot countery*/
int rc = 0, cnt = 0, cnt_his = 0;
uint8_t *key;
uint32_t reboot_counter = 0U, reboot_counter_his;
struct flash_pages_info info;
const struct device *flash_dev;

/*LED Preamble*/

#include <devicetree.h>
#include <drivers/gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS 1000


#include <stdlib.h> //for using the function sleep
#include <stdio.h>
#include <time.h>

/*Temperature and Humidity*/

#include <drivers/sensor.h>
#include <stdio.h>
#include <sys/util.h>

//maybe for humidity
#include <inttypes.h>


//#include <drivers/gpio.h>
#include <logging/log.h>

LOG_MODULE_REGISTER(app, CONFIG_LOG_DEFAULT_LEVEL);

static void process_sample(const struct device *dev)
{
	static unsigned int obs;
	struct sensor_value temp, hum;
	if (sensor_sample_fetch(dev) < 0) {
		LOG_INF("Sensor sample update error\n");
		return;
	}

	if (sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &temp) < 0) {
		LOG_INF("Cannot read HTS221 temperature channel\n");
		return;
	}

	if (sensor_channel_get(dev, SENSOR_CHAN_HUMIDITY, &hum) < 0) {
		LOG_INF("Cannot read HTS221 humidity channel\n");
		return;
	}

	++obs;
	LOG_INF("Observation:%u\n", obs);

	/* display temperature */
	LOG_INF("Temperature:%d C\n", temp.val1);

	/* display humidity */
	LOG_INF("Relative Humidity:%d %%\n",
	       hum.val1);
}

static void hts221_handler(const struct device *dev,
			   const struct sensor_trigger *trig)
{
	process_sample(dev);
}



/* Custom Service Variables */
#define BT_UUID_CUSTOM_SERVICE_VAL \
	BT_UUID_128_ENCODE(0x00000000, 0x1234, 0x5678, 0x1234, 0x56789abcdef0)

static struct bt_uuid_128 vnd_uuid = BT_UUID_INIT_128(
	BT_UUID_CUSTOM_SERVICE_VAL);

static struct bt_uuid_128 vnd_enc_uuid = BT_UUID_INIT_128(
	BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef1));

static struct bt_uuid_128 vnd_auth_uuid = BT_UUID_INIT_128(
	BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef2));

#define VND_MAX_LEN 20


static uint8_t simulate_vnd;
static uint8_t indicating;
static struct bt_gatt_indicate_params ind_params;

static void vnd_ccc_cfg_changed(const struct bt_gatt_attr *attr, uint16_t value)
{
	simulate_vnd = (value == BT_GATT_CCC_INDICATE) ? 1 : 0;
}

static void indicate_cb(struct bt_conn *conn,
			struct bt_gatt_indicate_params *params, uint8_t err)
{
	printk("Indication %s\n", err != 0U ? "fail" : "success");
}

static void indicate_destroy(struct bt_gatt_indicate_params *params)
{
	printk("Indication complete\n");
	indicating = 0U;
}





static const struct bt_uuid_128 vnd_long_uuid = BT_UUID_INIT_128(
	BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef3));

static struct bt_gatt_cep vnd_long_cep = {
	.properties = BT_GATT_CEP_RELIABLE_WRITE,
};

static int signed_value;
static int signed_value1;
static int signed_value2;
static int len_of_value;



static ssize_t read_char2(struct bt_conn *conn, const struct bt_gatt_attr *attr,
			   void *buf, uint16_t len, uint16_t offset)
{         
        /* bolo const char, ale idk*/
	char *value = attr->user_data;
       

       
        LOG_INF("len_of_value vs len: %d %d\n",len_of_value, len );
        /*ak by som dal, ze vsetky value su 0, tak by mi to zapisalo za value key*/
        int counter = 0;

        for (int i = 0; i < len_of_value; i++){
          printf("value[%d] = ", i);
          printf("%" PRIx32 "\n", value[i]);   
          if(value[i] == 0){
            counter++;
          }
        }
    
        rc = nvs_read(&fs, KEY_ID, &key, sizeof(key));
        if (rc > 0) { /* item was found, show it */
		LOG_INF("Id: %d, THE Key is: ", KEY_ID);
		for (int n = 0; n < key; n++) {
			printk("%x ", key[n]);
		}
		printk("\n");
        }

        if(counter == 3){
           printk("00-00-00 configuration, rewriting for key! \n");
           for (int i = 0; i < len; i++){           
              value[i] = key[i];
              printk("%x to %x ", value[i], key[i]);
           }
        }    
	return bt_gatt_attr_read(conn, attr, buf, len, offset, value,
				 len_of_value);
       
}

// important part, user can define functions on his bytes
struct Logic_deciderss{
          int logic_value;
          char* logic_name;        
}first_byte[3], second_byte[3], sixth_byte[3];
//define dame nech je kto krajsie


//decider[20]

//void asddsa(struct Logic_deciderss *dd){

//    LOG_INF("FFFFFFFFFFF...%d %d\n", dd[0].a, dd[0].b);
//}

static ssize_t write_char2(struct bt_conn *conn, const struct bt_gatt_attr *attr,
			    const void *buf, uint16_t len, uint16_t offset,
			    uint16_t flags)
{         
        
        //LOG_INF("Len co dosla dako do funkcie: %d\n", len);
        //LOG_INF("Offset? : %d\n", offset);
        //len = 9;
	//uint8_t *value = attr->user_data;
        uint8_t *value = attr->user_data;
        uint8_t *stable_value = value;
        
        
       
        //mc.do_something();
        LOG_INF("\nDOLEZITE!!! %d\\n \n", foo());
        //manualne obmedzenie na dlzku
	//if (offset + len > sizeof(signed_value2)) {
 //               LOG_INF("BT_ATT_ERR_INVALID_OFFSET\n");
	//	return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);

	//}

	memcpy(value + offset, buf, len);
        
        
        //int lenlen = sizeof(value)/sizeof(value[0]);
        //LOG_INF("Length of written data is max: %d \n", lenlen);

        //for (int i = 0; i < len; i++){
          
        //  LOG_INF("value[%d] = ", i);
        //  LOG_INF("%" PRIx32 "\n", value[i]);   
        
        //}
        LOG_INF("DLZKA: %d\n", len);
        len_of_value = len;
	/* KEY_ID is used to store a key, lets see if we can read it from flash
	 */
	rc = nvs_read(&fs, KEY_ID, &key, sizeof(key));
        if (rc > 0) { /* item was found, show it */
		//LOG_INF("Id: %d, OLD Key: ", KEY_ID);
		for (int n = 0; n < len; n++) {
			//printk("%x ", key[n]);
                        key[n] = value[n];
		}
		//LOG_INF("\n");

                /*new key*/
                //LOG_INF("NEW Key: ");
		//key[0] = value[0];
		//key[1] = value[1];
		//key[2] = value[2];
		//key[3] = value[3];

		(void)nvs_write(&fs, KEY_ID, &key, sizeof(key));
		for (int n = 0; n < len; n++) {
			printk("%d %x ", n, key[n]);

                        if(n==8 || n==17 || n==26){
                          printk("\n");
                        }
		}
		printk("\n");
	} else   {/* item was not found, add it */
		//LOG_INF("No key found, adding it at id %d\n", KEY_ID);
                for (int n = 0; n < len; n++) {
			
                        key[n] = value[n];
		}
		//key[0] = value[0];
		//key[1] = value[1];
		//key[2] = value[2];
		//key[3] = value[3];
		(void)nvs_write(&fs, KEY_ID, &key, sizeof(key));
	}
        

       // //OPAKOVANIA CONFIGOV ZACINAJU
       // int pocet_configov = (int)(len/9);
       // //alebo budem po 9 priratavat, ale ak sa to rovna, konci, ak nie ide aj s nedokoncenymi datami
        
       // LOG_INF("pocet_configov: %d\n", pocet_configov);
        


      
       // for(int ddd=0; ddd<pocet_configov; ddd++){

       //   LOG_INF("Prva value cofigu %d je: %d\n", ddd, stable_value[ddd*9]);

       //   //aby som nemusel komplet prepisovat, ulo?il som si value na jedno miesto a takto s tym pracujem
       //   for(int cc=0; cc<9; cc++){
       //       value[cc]=stable_value[(ddd*9)+cc];
       //       LOG_INF("%d. new_value: %d\n", cc, value[cc]);

  
       //   }

       //   ///*Thingy kod*/
       //   const struct device *dev_t;
       //   bool led_is_on_t = true;
       //   int ret_t;
        
       //   bool led_verification_t = false;
       //   int led_options_t[] = {0,1,2};

       //   for(int i=0; i<3; i++){
       //     if(value[0] == led_options_t[i]){
       //       led_verification_t = true;
       //     }
       //   }
    
  
       //    int position_in_byte = -1;

       //    //Vzorova = 
       //    if(led_verification_t == true){
       //       //total reset 00-00-00 config. ale presne v tejto dlzke
       //       if(value[0] == 0 && value[1] == 0 && value[2] == 0){
       //         led_is_on_t = false;
       //         dev_t = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led0), gpios));
       //         ret_t = gpio_pin_configure(dev_t, DT_GPIO_PIN(DT_ALIAS(led0), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led0), gpios));
       //         gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led0), gpios), (int)led_is_on_t);

       //         dev_t = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led1), gpios));
       //         ret_t = gpio_pin_configure(dev_t, DT_GPIO_PIN(DT_ALIAS(led1), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led1), gpios));       
       //         gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led1), gpios), (int)led_is_on_t);
              
       //         dev_t = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led2), gpios));
       //         ret_t = gpio_pin_configure(dev_t, DT_GPIO_PIN(DT_ALIAS(led2), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led2), gpios));
       //         gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led2), gpios), (int)led_is_on_t);
       //       }else{
              
       //         bool execute = true;
                
       //         LOG_INF("1Sixth_byte %d %s\n", sixth_byte[1].logic_value, sixth_byte[1].logic_name); 
       //         LOG_INF("2Sixth_byte %d %s\n", sixth_byte[2].logic_value, sixth_byte[2].logic_name);
       //         LOG_INF("3Sixth_byte %d %s\n", sixth_byte[0].logic_value, sixth_byte[0].logic_name); 
       //         //char* pokus60 = sixth_byte[0].logic_name;
       //         //char* pokus61 = sixth_byte[1].logic_name;
       //         //int pokus60_int, pokus61_int;
                
       //         //pokus60_int = sixth_byte[0].logic_value;
       //         //pokus61_int = sixth_byte[1].logic_value;

       //         //LOG_INF("5sixth %s -- %d\n", pokus60, pokus60_int); 
       //         //LOG_INF("4sixth %s -- %d\n", pokus61, pokus61_int); 

       //         LOG_INF("Siesty cyklus dlzka: %d\n", sizeof(sixth_byte)/sizeof(sixth_byte[0]));
       //         for(int ii=0; ii<sizeof(sixth_byte)/sizeof(sixth_byte[0]); ii++){
       //             //najdeme ci sa value zhoduje s niecim v sixth_byte
       //             //ak ano riesime s cim a co je vystup

       //           if(sixth_byte[ii].logic_value == value[5]){
       //               position_in_byte = ii;
       //               LOG_INF("value[5] was: %d... Position in byte: %d ->>> %s\n", value[5], position_in_byte, sixth_byte[position_in_byte].logic_name);

       //             }                       
       //         }
       //         char* vystup6 = sixth_byte[position_in_byte].logic_name;
                
       //         LOG_INF("Position: %d Sixth_byte %d %d\n", position_in_byte, sixth_byte[0].logic_name, sixth_byte[0].logic_name); 

       //         ////meraj teplotu = 1, humiditu = 2
       //         if(vystup6 == "temperature_sensor" || vystup6 == "humidity_sensor"){

       //           LOG_INF("okej ideme merat teplotu/humiditu\n");
                
       //           execute = false;
       //           //led_is_on_t = true; 
       //           const struct device *dev_sensor = device_get_binding("HTS221");
       //           //const struct device *dev_t = device_get_binding(DT_LABEL(DT_INST(0, st_hts221)));

       //           if (dev_sensor == NULL) {
       //                   LOG_INF("Could not get HTS221 device\n");
       //                   return;
       //           }

       //           if (IS_ENABLED(CONFIG_HTS221_TRIGGER)) {
       //                   struct sensor_trigger trig = {
       //                           .type = SENSOR_TRIG_DATA_READY,
       //                           .chan = SENSOR_CHAN_ALL,
       //                   };
       //                   if (sensor_trigger_set(dev_sensor, &trig, hts221_handler) < 0) {
       //                           LOG_INF("Cannot configure trigger\n");
       //                           return;
       //                   }
       //           }
              
       //           static unsigned int obs;

       //           struct sensor_value temp, hum;
       //           if (sensor_sample_fetch(dev_sensor) < 0) {
       //                   LOG_INF("Sensor sample update error\n");
       //                   return;
       //           }

       //           if (sensor_channel_get(dev_sensor, SENSOR_CHAN_AMBIENT_TEMP, &temp) < 0) {
       //                   LOG_INF("Cannot read HTS221 temperature channel\n");
       //                   return;
       //           }

       //           if (sensor_channel_get(dev_sensor, SENSOR_CHAN_HUMIDITY, &hum) < 0) {
       //                   LOG_INF("Cannot read HTS221 humidity channel\n");
       //                   return;
       //           }
              
       //           ++obs;
       //           LOG_INF("Observation:%u\n", obs);
              
       //           int sensor_value;
       //           if(vystup6 == "temperature_sensor"){
       //             /* display temperature */
       //             LOG_INF("1Temperature:%d C\n", temp.val1);
       //             sensor_value = temp.val1;
       //           }
              
       //            if(vystup6 == "humidity_sensor"){
       //             /* display humidity */
       //             LOG_INF("1Relative Humidity:%d %%\n", hum.val1);
       //             sensor_value = hum.val1;
       //           }

              
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
              
          
       //           //same
       //           if(reaction_is == 0){
       //             LOG_INF("0ROVNAKO\n");
       //             if(sensor_value == break_point){
       //               execute = true;
       //               LOG_INF("ROVNAKO\n");
       //             }
       //           }
       //           //more
       //           if(reaction_is == 1){
       //             LOG_INF("0VIAC\n");
       //             if(sensor_value > break_point){
       //               execute = true;
       //               LOG_INF("VIAC\n");
       //             }
       //           }
       //           //less
       //           if(reaction_is == 2){
       //             LOG_INF("0MENEJ\n");
       //             if(sensor_value < break_point){
       //               execute = true;
       //               LOG_INF("MENEJ\n");
       //             }
       //           }
       //           LOG_INF("Same{0)/More(1)/Less(2): %d\n", reaction_is);
       //         }
              

              
       //         if(execute == true){       
       //           //led_is_on_t = false;
       //           //urcenie: led0,1,2 - RGB     
       //           // zistim ktoru ledku chceme zapalit a zapametam si to
       //           LOG_INF("Prvy cyklus dlzka: %d\n", sizeof(second_byte)/sizeof(second_byte[0]));
       //           for(int ii=0; ii<sizeof(second_byte)/sizeof(second_byte[0]); ii++){
       //             //najdeme ci sa value zhoduje s niecim v second_byte
       //             //ak ano riesime s cim a co je vystup

       //           if(second_byte[ii].logic_value == value[1]){
       //               position_in_byte = ii;
       //               LOG_INF("Position in byte: %d\n", position_in_byte);
       //             }                       
       //           }
          
       //           char* vystup = second_byte[position_in_byte].logic_name;

       //           LOG_INF("Pravidlo sa naslo: %s\n", vystup);

       //           if(position_in_byte == -1){
       //               LOG_ERR("Ziadna zhoda v 2. bajte (value[1])\n");
       //           }

       //           if(vystup == "set_led0"){
       //             printk("config 1, led 0\n");
       //             dev_t = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led0), gpios));
       //             ret_t = gpio_pin_configure(dev_t, DT_GPIO_PIN(DT_ALIAS(led0), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led0), gpios));
       //             gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led0), gpios), (int)led_is_on_t);
       //           }
       //           if(vystup == "set_led1"){
       //             printk("config 2, led 1\n");
       //             dev_t = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led1), gpios));
       //             ret_t = gpio_pin_configure(dev_t, DT_GPIO_PIN(DT_ALIAS(led1), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led1), gpios));       
       //             gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led1), gpios), (int)led_is_on_t);
       //           }
       //           if(vystup == "set_led2"){               
       //             printk("config 3, led 2\n");
       //             dev_t = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led2), gpios));
       //             ret_t = gpio_pin_configure(dev_t, DT_GPIO_PIN(DT_ALIAS(led2), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led2), gpios));
       //             gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led2), gpios), (int)led_is_on_t);
       //           }
            

       //           if (dev_t == NULL){return;}
      
       //           if (ret_t < 0){return;}
            
       //           //teraz testujeme prvy bajt, kde sa riesi zap/vypnutie/blikanie
       //           int position_in_byte0 = -1;

       //           LOG_INF("Druhy cyklus dlzka: %d\n", sizeof(first_byte)/sizeof(first_byte[0]));
              
       //           for(int ii=0; ii<sizeof(first_byte)/sizeof(first_byte[0]); ii++){
       //             if(first_byte[ii].logic_value == value[0]){
       //                 position_in_byte0 = ii;
       //                 LOG_INF("position_in_byte0: %d\n", position_in_byte0);
       //               }
       //           }

       //           if(position_in_byte0 == -1){
       //                 LOG_ERR("Ziadna zhoda v 1. bajte (value[0])\n");
       //            }
       //           char* vystup0 = first_byte[position_in_byte0].logic_name;

       //           if(vystup0 == "turn_off"){
       //             led_is_on_t = false;
       //             LOG_INF("turning led off\n");                                     
       //           }

       //           //zapni
       //           if(vystup0 == "turn_on"){
       //             led_is_on_t = true;
       //             LOG_INF("turning led on\n");                                             
       //           }
       //            //blikaj
       //           if(vystup0 == "blink_led"){

       //                 LOG_INF("Bliknut ma %d krat\n", value[2]);
       //                 int counter = 0;
                  
       //                 while(counter < value[2]){
       //                   led_is_on_t = !led_is_on_t;
       //                   LOG_INF("sleep time: %d decisecond)\n", value[3]*10000);
       //                   LOG_INF("sleep time: %d miliseconds\n", value[4]*100);

       //                   k_msleep((value[4]*100));
       //                   k_msleep((value[3]*10000));

       //                   if(vystup == "set_led0"){
       //                    gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led0), gpios), (int)led_is_on_t);
       //                   }
       //                   if(vystup == "set_led1"){
       //                    gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led1), gpios), (int)led_is_on_t);
       //                   }
       //                   if(vystup == "set_led2"){               
       //                     gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led2), gpios), (int)led_is_on_t);
       //                   }
       //                   counter++;
       //                 }
       //                 //gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led2), gpios), (int)led_is_on_t);
       //           }

       //        //execute if
       //         }
       //     //else not 00-00-00                
       //     }
       //   //led verific
       //   }
       ////mulitople configs
       //}

        
        
	return len;
}



static ssize_t read_char1(struct bt_conn *conn, const struct bt_gatt_attr *attr,
			   void *buf, uint16_t len, uint16_t offset)
{         
        /* bolo const char, ale idk*/
	char *value = attr->user_data;
        /*ak by som dal, ze vsetky value su 0, tak by mi to zapisalo za value key*/
        int counter = 0;
        for (int i = 0; i < 4; i++){
          printf("value[%d] = ", i);
          printf("%" PRIx32 "\n", value[i]);   
          if(value[i] == 0){
            counter++;
          }
        }
    
        rc = nvs_read(&fs, KEY_ID, &key, sizeof(key));
        if (rc > 0) { /* item was found, show it */
		printk("Id: %d, THE Key is: ", KEY_ID);
		for (int n = 0; n < 4; n++) {
			printk("%x ", key[n]);
		}
		printk("\n");
        }

        if(counter == 4){
           printk("00-00-00-00 configuration, rewriting for key! \n");
           for (int i = 0; i < 4; i++){           
              value[i] = key[i];
              printk("%x to %x ", value[i], key[i]);
           }
        }    
	return bt_gatt_attr_read(conn, attr, buf, len, offset, value,
				 sizeof(signed_value1));
       
}



static ssize_t write_char1(struct bt_conn *conn, const struct bt_gatt_attr *attr,
			    const void *buf, uint16_t len, uint16_t offset,
			    uint8_t flags)
{
	uint8_t *value = attr->user_data;
        

	if (offset + len > sizeof(signed_value1)) {
		return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
	}

	memcpy(value + offset, buf, len);
        
        
        int lenlen = sizeof(value)/sizeof(value[0]);
        printk("Length of written data is max: %d \n", lenlen);

        for (int i = 0; i < 4; i++){
          
          printf("value[%d] = ", i);
          printf("%" PRIx32 "\n", value[i]);   
        
        }

	/* KEY_ID is used to store a key, lets see if we can read it from flash
	 */
	rc = nvs_read(&fs, KEY_ID, &key, sizeof(key));
        if (rc > 0) { /* item was found, show it */
		printk("Id: %d, OLD Key: ", KEY_ID);
		for (int n = 0; n < 4; n++) {
			printk("%x ", key[n]);
		}
		printk("\n");

                /*new key*/
                printk("NEW Key: ");
		key[0] = value[0];
		key[1] = value[1];
		key[2] = value[2];
		key[3] = value[3];

		(void)nvs_write(&fs, KEY_ID, &key, sizeof(key));
		for (int n = 0; n < 4; n++) {
			printk("%x ", key[n]);
		}
		printk("\n");
	} else   {/* item was not found, add it */
		printk("No key found, adding it at id %d\n", KEY_ID);
		key[0] = value[0];
		key[1] = value[1];
		key[2] = value[2];
		key[3] = value[3];
		(void)nvs_write(&fs, KEY_ID, &key, sizeof(key));
	}
        
        /*Thingy kod*/
        const struct device *dev_t;
        bool led_is_on_t = true;
        int ret_t;
        
        bool led_verification_t = false;
        int led_options_t[] = {0,1,2};

        for(int i=0; i<3; i++){
          if(value[0] == led_options_t[i]){
            led_verification_t = true;
          }
        }
        
        //#define LED2_t DT_GPIO_LABEL(LED2_NODE_t, gpios)
        //#define PIN_t DT_GPIO_PIN(LED2_NODE_t, gpios)
        //#define FLAGS_t DT_GPIO_FLAGS(LED2_NODE_t, gpios)

        //#define LED0_NODE_t DT_ALIAS(led0) //red
        //#define LED1_NODE_t DT_ALIAS(led1) //green
        //#define LED2_NODE_t DT_ALIAS(led2) //blue

        //#define LED0_t DT_GPIO_LABEL(LED0_NODE_t, gpios)
        //#define PIN_t DT_GPIO_PIN(LED0_NODE_t, gpios)
        //#define FLAGS_t DT_GPIO_FLAGS(LED0_NODE_t, gpios)

        if(led_verification_t == true){
            if(value[0] == 0 && value[1] == 0){
              led_is_on_t = false;
              dev_t = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led0), gpios));
              ret_t = gpio_pin_configure(dev_t, DT_GPIO_PIN(DT_ALIAS(led0), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led0), gpios));
              gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led0), gpios), (int)led_is_on_t);

              dev_t = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led1), gpios));
              ret_t = gpio_pin_configure(dev_t, DT_GPIO_PIN(DT_ALIAS(led1), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led1), gpios));       
              gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led1), gpios), (int)led_is_on_t);
              
              dev_t = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led2), gpios));
              ret_t = gpio_pin_configure(dev_t, DT_GPIO_PIN(DT_ALIAS(led2), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led2), gpios));
              gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led2), gpios), (int)led_is_on_t);
            }
            else{
                         
            //zhasni, zapni, blikaj         
              //led_is_on_t = false;
              //led0,1,2 - RGB
              if(value[1] == 1){
                printk("config 1, led 0\n");
                dev_t = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led0), gpios));
                ret_t = gpio_pin_configure(dev_t, DT_GPIO_PIN(DT_ALIAS(led0), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led0), gpios));
                gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led0), gpios), (int)led_is_on_t);
              }
              if(value[1] == 2){
                printk("config 2, led 1\n");
                dev_t = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led1), gpios));
                ret_t = gpio_pin_configure(dev_t, DT_GPIO_PIN(DT_ALIAS(led1), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led1), gpios));       
                gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led1), gpios), (int)led_is_on_t);
              }
              if(value[1] == 3){
                
                printk("config 3, led 2\n");
                dev_t = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led2), gpios));
                ret_t = gpio_pin_configure(dev_t, DT_GPIO_PIN(DT_ALIAS(led2), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led2), gpios));
                gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led2), gpios), (int)led_is_on_t);
              }
            }

             if (dev_t == NULL)
            {
                return;
            }
      
           if (ret_t < 0)
            {
                return;
            }

            if(value[0] == 0){
              led_is_on_t = false;
            
            }
            if(value[0] == 1){
              led_is_on_t = true;
            
            }
            if(value[0] == 2){

                  // okej funguje to pre led 2
                  int counter = 0;
                  while(counter < value[2]){
                    led_is_on_t = !led_is_on_t;
                    int navyse_sleep_time = 
                    k_msleep((value[3]*100));

                    if(value[1] == 1){
                      gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led0), gpios), (int)led_is_on_t);
                    }
                    if(value[1] == 2){
                     gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led1), gpios), (int)led_is_on_t);
                    }
                    if(value[1] == 3){
                     gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led2), gpios), (int)led_is_on_t);
                    }
                    counter++;
                  }
                  //gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led2), gpios), (int)led_is_on_t);
            } 
          
       
        }

        
 //        /*nRF58382 kod*/
 //       /*LED ktore chceme zapnut na doske*/
 //       const struct device *dev;
	//bool led_is_on = true;
	//int ret;
         

 //       bool led_verification = false;
 //       int led_options[] = {1,2,3,4};

 //       for(int i=0; i<4; i++){
 //         if(value[0] == led_options[i]){
 //           led_verification = true;
 //         }
 //       }

 //       if(led_verification == true){
 //         /*tieto definitions som pouzil na tie siahodlhe funkcie aby mi to neprepisovalo iba na poslednu hodnotu*/
 //         //#define LED0_NODE DT_ALIAS(led0)
 //         //#define LED0 DT_GPIO_LABEL(LED0_NODE, gpios)
 //         //#define PIN DT_GPIO_PIN(LED0_NODE, gpios)          
 //         //#define FLAGS DT_GPIO_FLAGS(LED0_NODE, gpios)

 //         if(value[0] == 1){
 //           printk("config 1, led 0\n");

 //           dev = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led0), gpios)); 
 //           ret = gpio_pin_configure(dev, DT_GPIO_PIN(DT_ALIAS(led0), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led0), gpios));
 //           gpio_pin_set(dev, DT_GPIO_PIN(DT_ALIAS(led0), gpios), (int)led_is_on);
            
 //         }
 //         if(value[0] == 2){
 //           printk("config 2, led 1\n");
                      
 //           dev = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led1), gpios)); 
 //           ret = gpio_pin_configure(dev, DT_GPIO_PIN(DT_ALIAS(led1), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led1), gpios));
 //           gpio_pin_set(dev, DT_GPIO_PIN(DT_ALIAS(led1), gpios), (int)led_is_on);
 //         }
 //         if(value[0] == 3){
 //           printk("config 3, led 2\n");

 //           dev = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led2), gpios)); 
 //           ret = gpio_pin_configure(dev, DT_GPIO_PIN(DT_ALIAS(led2), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led2), gpios));
 //           gpio_pin_set(dev, DT_GPIO_PIN(DT_ALIAS(led2), gpios), (int)led_is_on);
            
 //         }
 //         if(value[0] == 4){
 //           printk("config 4, led 3\n");

 //           dev = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led3), gpios)); 
 //           ret = gpio_pin_configure(dev, DT_GPIO_PIN(DT_ALIAS(led3), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led3), gpios));
 //           gpio_pin_set(dev, DT_GPIO_PIN(DT_ALIAS(led3), gpios), (int)led_is_on);
            
 //         }

 //         if (dev == NULL) {
 //             return;
 //         }

          
 //         led_is_on = !led_is_on;
          
 //         if(value[1] == 0){
 //           if(value[0]==1){
 //             led_is_on = false;
 //             gpio_pin_set(dev, DT_GPIO_PIN(DT_ALIAS(led0), gpios),  (int)led_is_on);
 //             printk("led0"); 
 //           }
 //           if(value[0]==2){
 //             led_is_on = false;
 //             gpio_pin_set(dev, DT_GPIO_PIN(DT_ALIAS(led1), gpios), (int)led_is_on);
 //             printk("led1"); 
 //           }
 //           if(value[0]==3){
 //             led_is_on = false;
 //             gpio_pin_set(dev, DT_GPIO_PIN(DT_ALIAS(led2), gpios), (int)led_is_on);
 //             printk("led2"); 
 //           }
 //           if(value[0]==4){
 //             led_is_on = false;
 //             gpio_pin_set(dev, DT_GPIO_PIN(DT_ALIAS(led3), gpios), (int)led_is_on);
 //             printk("led3"); 
 //           }
 //         }  
 //       }
     
        
	return len;
}


static const struct bt_uuid_128 vnd_signed_uuid = BT_UUID_INIT_128(
	BT_UUID_128_ENCODE(0x13345678, 0x1234, 0x5678, 0x1334, 0x56789abcdef9));

static const struct bt_uuid_128 char1_signed_uuid = BT_UUID_INIT_128(
	BT_UUID_128_ENCODE(0x13345678, 0x1234, 0x5678, 0x1334, 0x56789abcdef8));

static const struct bt_uuid_128 char2_signed_uuid = BT_UUID_INIT_128(
	BT_UUID_128_ENCODE(0x11111111, 0x1234, 0x5678, 0x1334, 0x56789abcdef7));

static const struct bt_uuid_128 vnd_write_cmd_uuid = BT_UUID_INIT_128(
	BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef4));

static ssize_t write_without_rsp_vnd(struct bt_conn *conn,
				     const struct bt_gatt_attr *attr,
				     const void *buf, uint16_t len, uint16_t offset,
				     uint8_t flags)
{
	uint8_t *value = attr->user_data;

	if (!(flags & BT_GATT_WRITE_FLAG_CMD)) {
		/* Write Request received. Reject it since this Characteristic
		 * only accepts Write Without Response.
		 */
		return BT_GATT_ERR(BT_ATT_ERR_WRITE_REQ_REJECTED);
	}

	if (offset + len > VND_MAX_LEN) {
		return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
	}

	memcpy(value + offset, buf, len);
	value[offset + len] = 0;
	return len;
}

/* Vendor Primary Service Declaration */
BT_GATT_SERVICE_DEFINE(vnd_svc,
	BT_GATT_PRIMARY_SERVICE(&vnd_uuid),
	//BT_GATT_CHARACTERISTIC(&vnd_enc_uuid.uuid,
	//		       BT_GATT_CHRC_READ | BT_GATT_CHRC_WRITE |
	//		       BT_GATT_CHRC_INDICATE,
	//		       BT_GATT_PERM_READ_ENCRYPT |
	//		       BT_GATT_PERM_WRITE_ENCRYPT,
	//		       read_vnd, write_vnd, vnd_value),
	//BT_GATT_CCC(vnd_ccc_cfg_changed,
	//	    BT_GATT_PERM_READ | BT_GATT_PERM_WRITE_ENCRYPT),
	//BT_GATT_CHARACTERISTIC(&vnd_auth_uuid.uuid,
	//		       BT_GATT_CHRC_READ | BT_GATT_CHRC_WRITE,
	//		       BT_GATT_PERM_READ_AUTHEN |
	//		       BT_GATT_PERM_WRITE_AUTHEN,
	//		       read_vnd, write_vnd, vnd_auth_value),
	//BT_GATT_CHARACTERISTIC(&vnd_long_uuid.uuid, BT_GATT_CHRC_READ |
	//		       BT_GATT_CHRC_WRITE | BT_GATT_CHRC_EXT_PROP,
	//		       BT_GATT_PERM_READ | BT_GATT_PERM_WRITE |
	//		       BT_GATT_PERM_PREPARE_WRITE,
	//		       read_vnd, write_long_vnd, &vnd_long_value),
	//BT_GATT_CEP(&vnd_long_cep),

	//BT_GATT_CHARACTERISTIC(&vnd_signed_uuid.uuid, BT_GATT_CHRC_READ |
	//		       BT_GATT_CHRC_WRITE | BT_GATT_CHRC_AUTH,
	//		       BT_GATT_PERM_READ | BT_GATT_PERM_WRITE,
	//		       read_signed, write_signed, &signed_value),
        //Charakteristika 1
        //BT_GATT_CHARACTERISTIC(&char1_signed_uuid.uuid, BT_GATT_CHRC_READ |
			     //  BT_GATT_CHRC_WRITE | BT_GATT_CHRC_AUTH,
			     //  BT_GATT_PERM_READ | BT_GATT_PERM_WRITE,
			     //  read_char1, write_char1, &signed_value1),
        //Charakteristika 2
        BT_GATT_CHARACTERISTIC(&char2_signed_uuid.uuid, BT_GATT_CHRC_READ |
			       BT_GATT_CHRC_WRITE | BT_GATT_CHRC_AUTH,
			       BT_GATT_PERM_READ | BT_GATT_PERM_WRITE,
			       read_char2, write_char2, &signed_value2),
	//BT_GATT_CHARACTERISTIC(&vnd_write_cmd_uuid.uuid,
	//		       BT_GATT_CHRC_WRITE_WITHOUT_RESP,
	//		       BT_GATT_PERM_WRITE, NULL,
	//		       write_without_rsp_vnd, &vnd_wwr_value),
);

static const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
	BT_DATA_BYTES(BT_DATA_UUID16_ALL,
		      BT_UUID_16_ENCODE(BT_UUID_HRS_VAL),
		      BT_UUID_16_ENCODE(BT_UUID_BAS_VAL),
		      BT_UUID_16_ENCODE(BT_UUID_CTS_VAL)),
	BT_DATA_BYTES(BT_DATA_UUID128_ALL, BT_UUID_CUSTOM_SERVICE_VAL),
};

void mtu_updated(struct bt_conn *conn, uint16_t tx, uint16_t rx)
{
	printk("Updated MTU: TX: %d RX: %d bytes\n", tx, rx);
}

static struct bt_gatt_cb gatt_callbacks = {
	.att_mtu_updated = mtu_updated
};

static void connected(struct bt_conn *conn, uint8_t err)
{
	if (err) {
		printk("Connection failed (err 0x%02x)\n", err);
	} else {
		printk("Connected\n");
	}
}

static void disconnected(struct bt_conn *conn, uint8_t reason)
{
	printk("Disconnected (reason 0x%02x)\n", reason);
}

BT_CONN_CB_DEFINE(conn_callbacks) = {
	.connected = connected,
	.disconnected = disconnected,
};

static void bt_ready(void)
{
	int err;

	printk("Bluetooth initialized\n");

	cts_init();

	if (IS_ENABLED(CONFIG_SETTINGS)) {
		settings_load();
	}

	err = bt_le_adv_start(BT_LE_ADV_CONN_NAME, ad, ARRAY_SIZE(ad), NULL, 0);
	if (err) {
		printk("Advertising failed to start (err %d)\n", err);
		return;
	}

	printk("Advertising successfully started\n");
}

static void auth_passkey_display(struct bt_conn *conn, unsigned int passkey)
{
	char addr[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

	printk("Passkey for %s: %06u\n", addr, passkey);
}

static void auth_cancel(struct bt_conn *conn)
{
	char addr[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

	printk("Pairing cancelled: %s\n", addr);
}

static struct bt_conn_auth_cb auth_cb_display = {
	.passkey_display = auth_passkey_display,
	.passkey_entry = NULL,
	.cancel = auth_cancel,
};






void main(void)
{         
        
        //Vseobecne zadefinovanie miesta vstupu a co predstavuje
        
          
        first_byte[0].logic_name = "turn_off";
        first_byte[0].logic_value = 0;

        first_byte[1].logic_name = "turn_on";
        first_byte[1].logic_value = 1;

        first_byte[2].logic_name = "blink_led";
        first_byte[2].logic_value = 2;


        second_byte[0].logic_name = "set_led0";
        second_byte[0].logic_value = 1;

        second_byte[1].logic_name = "set_led1";
        second_byte[1].logic_value = 2;

        second_byte[2].logic_name = "set_led2";
        second_byte[2].logic_value = 3;


        sixth_byte[0].logic_name = "no_sensor_action";
        sixth_byte[0].logic_value = 0;

        sixth_byte[1].logic_name = "temperature_sensor";
        sixth_byte[1].logic_value = 1;

        sixth_byte[2].logic_name = "humidity_sensor";
        sixth_byte[2].logic_value = 2;

        //asddsa(decider);


        //register_input(0, 0, "turn_off_light");
        //register_input(1, "turn_on_light");



        flash_dev = FLASH_AREA_DEVICE(STORAGE_NODE_LABEL);
	if (!device_is_ready(flash_dev)) {
		printk("Flash device %s is not ready\n", flash_dev->name);
		return;
	}
	fs.offset = FLASH_AREA_OFFSET(storage);
	rc = flash_get_page_info_by_offs(flash_dev, fs.offset, &info);
	if (rc) {
		printk("Unable to get page info\n");
		return;
	}
	fs.sector_size = info.size;
	fs.sector_count = 3U;

	rc = nvs_init(&fs, flash_dev->name);
	if (rc) {
		printk("Flash Init failed\n");
		return;
	} 

	/*BLE*/ 
	struct bt_gatt_attr *vnd_ind_attr;
	char str[BT_UUID_STR_LEN];
	int err;

	err = bt_enable(NULL);
	if (err) {
		printk("Bluetooth init failed (err %d)\n", err);
		return;
	}

	bt_ready();

	bt_gatt_cb_register(&gatt_callbacks);
	bt_conn_auth_cb_register(&auth_cb_display);

	vnd_ind_attr = bt_gatt_find_by_uuid(vnd_svc.attrs, vnd_svc.attr_count,
					    &vnd_enc_uuid.uuid);
	bt_uuid_to_str(&vnd_enc_uuid.uuid, str, sizeof(str));
	printk("Indicate VND attr %p (UUID %s)\n", vnd_ind_attr, str);





	/* Implement notification. At the moment there is no suitable way
	 * of starting delayed work so we do it here
	 */
	while (1) {
		k_sleep(K_SECONDS(1));

		/* Current Time Service updates only when time is changed */
		//cts_notify();

		///* Heartrate measurements simulation */
		//hrs_notify();

		///* Battery level simulation */
		//bas_notify();

		/* Vendor indication simulation */
		if (simulate_vnd && vnd_ind_attr) {
			if (indicating) {
				continue;
			}

			ind_params.attr = vnd_ind_attr;
			ind_params.func = indicate_cb;
			ind_params.destroy = indicate_destroy;
			ind_params.data = &indicating;
			ind_params.len = sizeof(indicating);

			if (bt_gatt_indicate(NULL, &ind_params) == 0) {
				indicating = 1U;
			}
		}


	}


}


