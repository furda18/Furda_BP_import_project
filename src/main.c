///* main.c - Application main entry point */

///*
// * Copyright (c) 2015-2016 Intel Corporation
// *
// * SPDX-License-Identifier: Apache-2.0
// */

//#include <zephyr/types.h>
//#include <stddef.h>
//#include <string.h>
//#include <errno.h>
//#include <sys/printk.h>
//#include <sys/byteorder.h>
//#include <zephyr.h>


//#include <settings/settings.h>

//#include <bluetooth/bluetooth.h>
//#include <bluetooth/hci.h>
//#include <bluetooth/conn.h>
//#include <bluetooth/uuid.h>
//#include <bluetooth/gatt.h>
//#include <bluetooth/services/bas.h>
//#include <bluetooth/services/hrs.h>

//#include "cts.h"


///*Flashing Preamle*/
//#include <zephyr.h>
//#include <sys/reboot.h>
//#include <device.h>
//#include <string.h>
//#include <drivers/flash.h>
//#include <storage/flash_map.h>
//#include <fs/nvs.h>

//static struct nvs_fs fs;

//#define STORAGE_NODE_LABEL storage

///* 1000 msec = 1 sec */
//#define SLEEP_TIME      100
///* maximum reboot counts, make high enough to trigger sector change (buffer */
///* rotation). */
//#define MAX_REBOOT 400

//#define ADDRESS_ID 1
//#define KEY_ID 2
//#define RBT_CNT_ID 3
//#define STRING_ID 4
//#define LONG_ID 5

///*definovanie pamate, este navyse su tie reboot countery*/
//int rc = 0, cnt = 0, cnt_his = 0;
//uint8_t key[4];
//uint32_t reboot_counter = 0U, reboot_counter_his;
//struct flash_pages_info info;
//const struct device *flash_dev;

///*LED Preamble*/

//#include <zephyr.h>
//#include <device.h>
//#include <devicetree.h>
//#include <drivers/gpio.h>

///* 1000 msec = 1 sec */
//#define SLEEP_TIME_MS 0

///* The devicetree node identifier for the "led0" alias. */
////#define LED0_NODE DT_ALIAS(led0)
////#define LED1_NODE DT_ALIAS(led1)
////#define LED2_NODE DT_ALIAS(led2)
////#define LED3_NODE DT_ALIAS(led3)

////#if (DT_NODE_HAS_STATUS(LED0_NODE, okay))

////#define LED0	
//////DT_GPIO_LABEL(LED0_NODE, gpios)
////#define PIN	
//////DT_GPIO_PIN(LED0_NODE, gpios)
////#define FLAGS	
//////DT_GPIO_FLAGS(LED0_NODE, gpios)

////#define LED1	
//////DT_GPIO_LABEL(LED1_NODE, gpios)
//////#define FLAGS	DT_GPIO_FLAGS(LED1_NODE, gpios)
////#define LED2	
//////DT_GPIO_LABEL(LED2_NODE, gpios)


////#define LED3	
//////DT_GPIO_LABEL(LED3_NODE, gpios)

//#include <zephyr.h>
//#include <device.h>
//#include <drivers/sensor.h>
//#include <stdio.h>
//#include <sys/util.h>


////#include <devicetree.h>
////#include <drivers/gpio.h>
//#include <logging/log.h>

//LOG_MODULE_REGISTER(app, CONFIG_LOG_DEFAULT_LEVEL);



///* Custom Service Variables */
//#define BT_UUID_CUSTOM_SERVICE_VAL \
//	BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef0)

//static struct bt_uuid_128 vnd_uuid = BT_UUID_INIT_128(
//	BT_UUID_CUSTOM_SERVICE_VAL);

//static struct bt_uuid_128 vnd_enc_uuid = BT_UUID_INIT_128(
//	BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef1));

//static struct bt_uuid_128 vnd_auth_uuid = BT_UUID_INIT_128(
//	BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef2));

//#define VND_MAX_LEN 20

//static uint8_t vnd_value[VND_MAX_LEN + 1] = { 'V', 'e', 'n', 'd', 'o', 'r'};
//static uint8_t vnd_auth_value[VND_MAX_LEN + 1] = { 'V', 'e', 'n', 'd', 'o', 'r'};
//static uint8_t vnd_wwr_value[VND_MAX_LEN + 1] = { 'V', 'e', 'n', 'd', 'o', 'r' };

//static ssize_t read_vnd(struct bt_conn *conn, const struct bt_gatt_attr *attr,
//			void *buf, uint16_t len, uint16_t offset)
//{
//	const char *value = attr->user_data;

//	return bt_gatt_attr_read(conn, attr, buf, len, offset, value,
//				 strlen(value));
//}

//static ssize_t write_vnd(struct bt_conn *conn, const struct bt_gatt_attr *attr,
//			 const void *buf, uint16_t len, uint16_t offset,
//			 uint8_t flags)
//{
//	uint8_t *value = attr->user_data;

//	if (offset + len > VND_MAX_LEN) {
//		return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
//	}

//	memcpy(value + offset, buf, len);
//	value[offset + len] = 0;

//	return len;
//}

//static uint8_t simulate_vnd;
//static uint8_t indicating;
//static struct bt_gatt_indicate_params ind_params;

//static void vnd_ccc_cfg_changed(const struct bt_gatt_attr *attr, uint16_t value)
//{
//	simulate_vnd = (value == BT_GATT_CCC_INDICATE) ? 1 : 0;
//}

//static void indicate_cb(struct bt_conn *conn,
//			struct bt_gatt_indicate_params *params, uint8_t err)
//{
//	printk("Indication %s\n", err != 0U ? "fail" : "success");
//}

//static void indicate_destroy(struct bt_gatt_indicate_params *params)
//{
//	printk("Indication complete\n");
//	indicating = 0U;
//}

//#define VND_LONG_MAX_LEN 74
//static uint8_t vnd_long_value[VND_LONG_MAX_LEN + 1] = {
//		  'V', 'e', 'n', 'd', 'o', 'r', ' ', 'd', 'a', 't', 'a', '1',
//		  'V', 'e', 'n', 'd', 'o', 'r', ' ', 'd', 'a', 't', 'a', '2',
//		  'V', 'e', 'n', 'd', 'o', 'r', ' ', 'd', 'a', 't', 'a', '3',
//		  'V', 'e', 'n', 'd', 'o', 'r', ' ', 'd', 'a', 't', 'a', '4',
//		  'V', 'e', 'n', 'd', 'o', 'r', ' ', 'd', 'a', 't', 'a', '5',
//		  'V', 'e', 'n', 'd', 'o', 'r', ' ', 'd', 'a', 't', 'a', '6',
//		  '.', ' ' };

//static ssize_t write_long_vnd(struct bt_conn *conn,
//			      const struct bt_gatt_attr *attr, const void *buf,
//			      uint16_t len, uint16_t offset, uint8_t flags)
//{
//	uint8_t *value = attr->user_data;

//	if (flags & BT_GATT_WRITE_FLAG_PREPARE) {
//		return 0;
//	}

//	if (offset + len > VND_LONG_MAX_LEN) {
//		return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
//	}

//	memcpy(value + offset, buf, len);
//	value[offset + len] = 0;

//	return len;
//}

//static const struct bt_uuid_128 vnd_long_uuid = BT_UUID_INIT_128(
//	BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef3));

//static struct bt_gatt_cep vnd_long_cep = {
//	.properties = BT_GATT_CEP_RELIABLE_WRITE,
//};

//static int signed_value;
//static int signed_value1;


////Moja char 2 - pre thingy a zbieranie dat
////
////
//static void process_sample(const struct device *dev)
//{
//	static unsigned int obs;
//	struct sensor_value temp, hum;
//	if (sensor_sample_fetch(dev) < 0) {
//		LOG_DBG("Sensor sample update error\n");
//		return;
//	}

//	if (sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &temp) < 0) {
//		LOG_DBG("Cannot read HTS221 temperature channel\n");
//		return;
//	}

//	if (sensor_channel_get(dev, SENSOR_CHAN_HUMIDITY, &hum) < 0) {
//		LOG_DBG("Cannot read HTS221 humidity channel\n");
//		return;
//	}

//	++obs;
//	LOG_DBG("Observation:%u\n", obs);

//	/* display temperature */
//	LOG_DBG("Temperature:%d C\n", temp.val1);

//	/* display humidity */
//	LOG_DBG("Relative Humidity:%d %%\n",
//	       hum.val1);
//}

//static void hts221_handler(const struct device *dev,
//			   const struct sensor_trigger *trig)
//{
//	process_sample(dev);
//}


//static int signed_value2;

//static ssize_t read_char2(struct bt_conn *conn, const struct bt_gatt_attr *attr,
//			   void *buf, uint16_t len, uint16_t offset)
//{         
//        /* bolo const char, ale idk*/
//	char *value = attr->user_data;
//        /*ak by som dal, ze vsetky value su 0, tak by mi to zapisalo za value key*/
//        int counter = 0;
//        for (int i = 0; i < 4; i++){
//          printf("value[%d] = ", i);
//          printf("%" PRIx32 "\n", value[i]);   
//          if(value[i] == 0){
//            counter++;
//          }
//        }
    
//        rc = nvs_read(&fs, KEY_ID, &key, sizeof(key));
//        if (rc > 0) { /* item was found, show it */
//		printk("Id: %d, THE Key is: ", KEY_ID);
//		for (int n = 0; n < 4; n++) {
//			printk("%x ", key[n]);
//		}
//		printk("\n");
//        }

//        if(counter == 4){
//           printk("00-00-00-00 configuration, rewriting for key! \n");
//           for (int i = 0; i < 4; i++){           
//              value[i] = key[i];
//              printk("%x to %x ", value[i], key[i]);
//           }
//        }    
//	return bt_gatt_attr_read(conn, attr, buf, len, offset, value,
//				 sizeof(signed_value2));
       
//}

//static ssize_t write_char2(struct bt_conn *conn, const struct bt_gatt_attr *attr,
//			    const void *buf, uint16_t len, uint16_t offset,
//			    uint8_t flags)
//{
//	uint8_t *value = attr->user_data;
        

//	if (offset + len > sizeof(signed_value2)) {
//		return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
//	}

//	memcpy(value + offset, buf, len);
        
        
//        int lenlen = sizeof(value)/sizeof(value[0]);
//        printk("Length of written data is max: %d \n", lenlen);

//        for (int i = 0; i < 4; i++){
          
//          printf("value[%d] = ", i);
//          printf("%" PRIx32 "\n", value[i]);   
        
//        }

//	/* KEY_ID is used to store a key, lets see if we can read it from flash
//	 */
//	rc = nvs_read(&fs, KEY_ID, &key, sizeof(key));
//        if (rc > 0) { /* item was found, show it */
//		printk("Id: %d, OLD Key: ", KEY_ID);
//		for (int n = 0; n < 4; n++) {
//			printk("%x ", key[n]);
//		}
//		printk("\n");

//                /*new key*/
//                printk("NEW Key: ");
//		key[0] = value[0];
//		key[1] = value[1];
//		key[2] = value[2];
//		key[3] = value[3];

//		(void)nvs_write(&fs, KEY_ID, &key, sizeof(key));
//		for (int n = 0; n < 4; n++) {
//			printk("%x ", key[n]);
//		}
//		printk("\n");
//	} else   {/* item was not found, add it */
//		printk("No key found, adding it at id %d\n", KEY_ID);
//		key[0] = value[0];
//		key[1] = value[1];
//		key[2] = value[2];
//		key[3] = value[3];
//		(void)nvs_write(&fs, KEY_ID, &key, sizeof(key));
//	}
        
//        /*Tak toto bude teplota a humidity servis*/
        
//        const struct device *dev = device_get_binding("HTS221");

//        if (dev == NULL) {
//		LOG_DBG("Could not get HTS221 device\n");
//		return;
//	}

//	if (IS_ENABLED(CONFIG_HTS221_TRIGGER)) {
//		struct sensor_trigger trig = {
//			.type = SENSOR_TRIG_DATA_READY,
//			.chan = SENSOR_CHAN_ALL,
//		};
//		if (sensor_trigger_set(dev, &trig, hts221_handler) < 0) {
//			LOG_DBG("Cannot configure trigger\n");
//			return;
//		}
//        }
        
//        while (!IS_ENABLED(CONFIG_HTS221_TRIGGER)) {
//		process_sample(dev);
//		k_sleep(K_MSEC(2000));
//                //LOG_INF("\nOlala!\n");
//	}
//	k_sleep(K_FOREVER);


//        /*LED ktore chceme zapnut*/
// //       const struct device *dev;
//	//bool led_is_on = true;
//	//int ret;
         

// //       bool led_verification = false;
// //       int led_options[] = {1,2,3,4};

// //       for(int i=0; i<4; i++){
// //         if(value[0] == led_options[i]){
// //           led_verification = true;
// //         }
// //       }

// //       if(led_verification == true){
// //         /*tieto definitions som pouzil na tie siahodlhe funkcie aby mi to neprepisovalo iba na poslednu hodnotu*/
// //         //#define LED0_NODE DT_ALIAS(led0)
// //         //#define LED0 DT_GPIO_LABEL(LED0_NODE, gpios)
// //         //#define PIN DT_GPIO_PIN(LED0_NODE, gpios)          
// //         //#define FLAGS DT_GPIO_FLAGS(LED0_NODE, gpios)

// //         if(value[0] == 1){
// //           printk("config 1, led 0\n");

// //           dev = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led0), gpios)); 
// //           ret = gpio_pin_configure(dev, DT_GPIO_PIN(DT_ALIAS(led0), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led0), gpios));
// //           gpio_pin_set(dev, DT_GPIO_PIN(DT_ALIAS(led0), gpios), (int)led_is_on);
            
// //         }
// //         if(value[0] == 2){
// //           printk("config 2, led 1\n");
                      
// //           dev = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led1), gpios)); 
// //           ret = gpio_pin_configure(dev, DT_GPIO_PIN(DT_ALIAS(led1), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led1), gpios));
// //           gpio_pin_set(dev, DT_GPIO_PIN(DT_ALIAS(led1), gpios), (int)led_is_on);
// //         }
// //         if(value[0] == 3){
// //           printk("config 3, led 2\n");

// //           dev = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led2), gpios)); 
// //           ret = gpio_pin_configure(dev, DT_GPIO_PIN(DT_ALIAS(led2), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led2), gpios));
// //           gpio_pin_set(dev, DT_GPIO_PIN(DT_ALIAS(led2), gpios), (int)led_is_on);
            
// //         }
// //         if(value[0] == 4){
// //           printk("config 4, led 3\n");

// //           dev = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led3), gpios)); 
// //           ret = gpio_pin_configure(dev, DT_GPIO_PIN(DT_ALIAS(led3), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led3), gpios));
// //           gpio_pin_set(dev, DT_GPIO_PIN(DT_ALIAS(led3), gpios), (int)led_is_on);
            
// //         }

// //         if (dev == NULL) {
// //             return;
// //         }

          
// //         led_is_on = !led_is_on;
          
// //         if(value[1] == 0){
// //           if(value[0]==1){
// //             led_is_on = false;
// //             gpio_pin_set(dev, DT_GPIO_PIN(DT_ALIAS(led0), gpios),  (int)led_is_on);
// //             printk("led0"); 
// //           }
// //           if(value[0]==2){
// //             led_is_on = false;
// //             gpio_pin_set(dev, DT_GPIO_PIN(DT_ALIAS(led1), gpios), (int)led_is_on);
// //             printk("led1"); 
// //           }
// //           if(value[0]==3){
// //             led_is_on = false;
// //             gpio_pin_set(dev, DT_GPIO_PIN(DT_ALIAS(led2), gpios), (int)led_is_on);
// //             printk("led2"); 
// //           }
// //           if(value[0]==4){
// //             led_is_on = false;
// //             gpio_pin_set(dev, DT_GPIO_PIN(DT_ALIAS(led3), gpios), (int)led_is_on);
// //             printk("led3"); 
// //           }
// //         }  
// //       }
     
        
//	return len;
//}



//static ssize_t read_char1(struct bt_conn *conn, const struct bt_gatt_attr *attr,
//			   void *buf, uint16_t len, uint16_t offset)
//{         
//        /* bolo const char, ale idk*/
//	char *value = attr->user_data;
//        /*ak by som dal, ze vsetky value su 0, tak by mi to zapisalo za value key*/
//        int counter = 0;
//        for (int i = 0; i < 4; i++){
//          printf("value[%d] = ", i);
//          printf("%" PRIx32 "\n", value[i]);   
//          if(value[i] == 0){
//            counter++;
//          }
//        }
    
//        rc = nvs_read(&fs, KEY_ID, &key, sizeof(key));
//        if (rc > 0) { /* item was found, show it */
//		printk("Id: %d, THE Key is: ", KEY_ID);
//		for (int n = 0; n < 4; n++) {
//			printk("%x ", key[n]);
//		}
//		printk("\n");
//        }

//        if(counter == 4){
//           printk("00-00-00-00 configuration, rewriting for key! \n");
//           for (int i = 0; i < 4; i++){           
//              value[i] = key[i];
//              printk("%x to %x ", value[i], key[i]);
//           }
//        }    
//	return bt_gatt_attr_read(conn, attr, buf, len, offset, value,
//				 sizeof(signed_value1));
       
//}



//static ssize_t write_char1(struct bt_conn *conn, const struct bt_gatt_attr *attr,
//			    const void *buf, uint16_t len, uint16_t offset,
//			    uint8_t flags)
//{
//	uint8_t *value = attr->user_data;
        

//	if (offset + len > sizeof(signed_value1)) {
//		return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
//	}

//	memcpy(value + offset, buf, len);
        
        
//        int lenlen = sizeof(value)/sizeof(value[0]);
//        printk("Length of written data is max: %d \n", lenlen);

//        for (int i = 0; i < 4; i++){
          
//          printf("value[%d] = ", i);
//          printf("%" PRIx32 "\n", value[i]);   
        
//        }

//	/* KEY_ID is used to store a key, lets see if we can read it from flash
//	 */
//	rc = nvs_read(&fs, KEY_ID, &key, sizeof(key));
//        if (rc > 0) { /* item was found, show it */
//		printk("Id: %d, OLD Key: ", KEY_ID);
//		for (int n = 0; n < 4; n++) {
//			printk("%x ", key[n]);
//		}
//		printk("\n");

//                /*new key*/
//                printk("NEW Key: ");
//		key[0] = value[0];
//		key[1] = value[1];
//		key[2] = value[2];
//		key[3] = value[3];

//		(void)nvs_write(&fs, KEY_ID, &key, sizeof(key));
//		for (int n = 0; n < 4; n++) {
//			printk("%x ", key[n]);
//		}
//		printk("\n");
//	} else   {/* item was not found, add it */
//		printk("No key found, adding it at id %d\n", KEY_ID);
//		key[0] = value[0];
//		key[1] = value[1];
//		key[2] = value[2];
//		key[3] = value[3];
//		(void)nvs_write(&fs, KEY_ID, &key, sizeof(key));
//	}
        

        
// //       /*LED ktore chceme zapnut*/
// //       const struct device *dev;
//	//bool led_is_on = true;
//	//int ret;
         

// //       bool led_verification = false;
// //       int led_options[] = {1,2,3,4};

// //       for(int i=0; i<4; i++){
// //         if(value[0] == led_options[i]){
// //           led_verification = true;
// //         }
// //       }

// //       if(led_verification == true){
// //         /*tieto definitions som pouzil na tie siahodlhe funkcie aby mi to neprepisovalo iba na poslednu hodnotu*/
// //         //#define LED0_NODE DT_ALIAS(led0)
// //         //#define LED0 DT_GPIO_LABEL(LED0_NODE, gpios)
// //         //#define PIN DT_GPIO_PIN(LED0_NODE, gpios)          
// //         //#define FLAGS DT_GPIO_FLAGS(LED0_NODE, gpios)

// //         if(value[0] == 1){
// //           printk("config 1, led 0\n");

// //           dev = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led0), gpios)); 
// //           ret = gpio_pin_configure(dev, DT_GPIO_PIN(DT_ALIAS(led0), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led0), gpios));
// //           gpio_pin_set(dev, DT_GPIO_PIN(DT_ALIAS(led0), gpios), (int)led_is_on);
            
// //         }
// //         if(value[0] == 2){
// //           printk("config 2, led 1\n");
                      
// //           dev = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led1), gpios)); 
// //           ret = gpio_pin_configure(dev, DT_GPIO_PIN(DT_ALIAS(led1), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led1), gpios));
// //           gpio_pin_set(dev, DT_GPIO_PIN(DT_ALIAS(led1), gpios), (int)led_is_on);
// //         }
// //         if(value[0] == 3){
// //           printk("config 3, led 2\n");

// //           dev = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led2), gpios)); 
// //           ret = gpio_pin_configure(dev, DT_GPIO_PIN(DT_ALIAS(led2), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led2), gpios));
// //           gpio_pin_set(dev, DT_GPIO_PIN(DT_ALIAS(led2), gpios), (int)led_is_on);
            
// //         }
// //         if(value[0] == 4){
// //           printk("config 4, led 3\n");

// //           dev = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(led3), gpios)); 
// //           ret = gpio_pin_configure(dev, DT_GPIO_PIN(DT_ALIAS(led3), gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led3), gpios));
// //           gpio_pin_set(dev, DT_GPIO_PIN(DT_ALIAS(led3), gpios), (int)led_is_on);
            
// //         }

// //         if (dev == NULL) {
// //             return;
// //         }

          
// //         led_is_on = !led_is_on;
          
// //         if(value[1] == 0){
// //           if(value[0]==1){
// //             led_is_on = false;
// //             gpio_pin_set(dev, DT_GPIO_PIN(DT_ALIAS(led0), gpios),  (int)led_is_on);
// //             printk("led0"); 
// //           }
// //           if(value[0]==2){
// //             led_is_on = false;
// //             gpio_pin_set(dev, DT_GPIO_PIN(DT_ALIAS(led1), gpios), (int)led_is_on);
// //             printk("led1"); 
// //           }
// //           if(value[0]==3){
// //             led_is_on = false;
// //             gpio_pin_set(dev, DT_GPIO_PIN(DT_ALIAS(led2), gpios), (int)led_is_on);
// //             printk("led2"); 
// //           }
// //           if(value[0]==4){
// //             led_is_on = false;
// //             gpio_pin_set(dev, DT_GPIO_PIN(DT_ALIAS(led3), gpios), (int)led_is_on);
// //             printk("led3"); 
// //           }
// //         }  
// //       }
     
        
//	return len;
//}


//static ssize_t read_signed(struct bt_conn *conn, const struct bt_gatt_attr *attr,
//			   void *buf, uint16_t len, uint16_t offset)
//{         
//        /* bolo const char, ale idk*/
//	char *value = attr->user_data;
               
//        /*cele definovanie som dal do globalu hore*/         


//        /*ak by som dal, ze vsetky value su 0, tak by mi to zapisalo za value key*/
//        int counter = 0;
//        for (int i = 0; i < 4; i++){
          
//          printf("value[%d] = ", i);
//          printf("%" PRIx32 "\n", value[i]);   
//          if(value[i] == 0){
//            counter++;
//          }
        
//        }
    

//        rc = nvs_read(&fs, KEY_ID, &key, sizeof(key));
//        if (rc > 0) { /* item was found, show it */
//		printk("Id: %d, THE Key is: ", KEY_ID);
//		for (int n = 0; n < 4; n++) {
//			printk("%x ", key[n]);
//		}
//		printk("\n");

//        }

//        if(counter == 4){
//           printk("00-00-00-00 configuration, rewriting for key! \n");
//           for (int i = 0; i < 4; i++){
                
//              value[i] = key[i];
//              printk("%x to %x ", value[i], key[i]);
//           }

//        }
          
//	return bt_gatt_attr_read(conn, attr, buf, len, offset, value,
//				 sizeof(signed_value));

        
//}

//static ssize_t write_signed(struct bt_conn *conn, const struct bt_gatt_attr *attr,
//			    const void *buf, uint16_t len, uint16_t offset,
//			    uint8_t flags)
//{
//	uint8_t *value = attr->user_data;
   

//	if (offset + len > sizeof(signed_value)) {
//		return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
//	}

//	memcpy(value + offset, buf, len);
        
        
//        int lenlen = sizeof(value)/sizeof(value[0]);
//        printk("Length of written data is max: %d \n", lenlen);

//        for (int i = 0; i < 4; i++){
          
//          printf("value[%d] = ", i);
//          printf("%" PRIx32 "\n", value[i]);   
        
//        }

//	//flash_dev = FLASH_AREA_DEVICE(STORAGE_NODE_LABEL);
//	//if (!device_is_ready(flash_dev)) {
//	//	printk("Flash device %s is not ready\n", flash_dev->name);
//	//	return;
//	//}
//	//fs.offset = FLASH_AREA_OFFSET(storage);
//	//rc = flash_get_page_info_by_offs(flash_dev, fs.offset, &info);
//	//if (rc) {
//	//	printk("Unable to get page info\n");
//	//	return;
//	//}
//	//fs.sector_size = info.size;
//	//fs.sector_count = 3U;

//	//rc = nvs_init(&fs, flash_dev->name);
//	//if (rc) {
//	//	printk("Flash Init failed\n");
//	//	return;
//	//}
//	/* KEY_ID is used to store a key, lets see if we can read it from flash
//	 */
//	rc = nvs_read(&fs, KEY_ID, &key, sizeof(key));
//        if (rc > 0) { /* item was found, show it */
//		printk("Id: %d, OLD Key: ", KEY_ID);
//		for (int n = 0; n < 4; n++) {
//			printk("%x ", key[n]);
//		}
//		printk("\n");

//                /*new key*/
//                printk("NEW Key: ");
//		key[0] = value[0];
//		key[1] = value[1];
//		key[2] = value[2];
//		key[3] = value[3];

//		(void)nvs_write(&fs, KEY_ID, &key, sizeof(key));
//		for (int n = 0; n < 4; n++) {
//			printk("%x ", key[n]);
//		}
//		printk("\n");
//	} else   {/* item was not found, add it */
//		printk("No key found, adding it at id %d\n", KEY_ID);
//		key[0] = value[0];
//		key[1] = value[1];
//		key[2] = value[2];
//		key[3] = value[3];
//		(void)nvs_write(&fs, KEY_ID, &key, sizeof(key));
//	}
         
//	return len;
//}

//static const struct bt_uuid_128 vnd_signed_uuid = BT_UUID_INIT_128(
//	BT_UUID_128_ENCODE(0x13345678, 0x1234, 0x5678, 0x1334, 0x56789abcdef9));

///*Moja char 1*/
//static const struct bt_uuid_128 char1_signed_uuid = BT_UUID_INIT_128(
//	BT_UUID_128_ENCODE(0x13345678, 0x1234, 0x5678, 0x1334, 0x56789abcdef8));

///*Moja char 2*/
//static const struct bt_uuid_128 char2_signed_uuid = BT_UUID_INIT_128(
//	BT_UUID_128_ENCODE(0x13345678, 0x1234, 0x5678, 0x1334, 0x56789abcdef7));

//static const struct bt_uuid_128 vnd_write_cmd_uuid = BT_UUID_INIT_128(
//	BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef4));

//static ssize_t write_without_rsp_vnd(struct bt_conn *conn,
//				     const struct bt_gatt_attr *attr,
//				     const void *buf, uint16_t len, uint16_t offset,
//				     uint8_t flags)
//{
//	uint8_t *value = attr->user_data;

//	if (!(flags & BT_GATT_WRITE_FLAG_CMD)) {
//		/* Write Request received. Reject it since this Characteristic
//		 * only accepts Write Without Response.
//		 */
//		return BT_GATT_ERR(BT_ATT_ERR_WRITE_REQ_REJECTED);
//	}

//	if (offset + len > VND_MAX_LEN) {
//		return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
//	}

//	memcpy(value + offset, buf, len);
//	value[offset + len] = 0;
//	return len;
//}

///* Vendor Primary Service Declaration */
//BT_GATT_SERVICE_DEFINE(vnd_svc,
//	BT_GATT_PRIMARY_SERVICE(&vnd_uuid),
//	BT_GATT_CHARACTERISTIC(&vnd_enc_uuid.uuid,
//			       BT_GATT_CHRC_READ | BT_GATT_CHRC_WRITE |
//			       BT_GATT_CHRC_INDICATE,
//			       BT_GATT_PERM_READ_ENCRYPT |
//			       BT_GATT_PERM_WRITE_ENCRYPT,
//			       read_vnd, write_vnd, vnd_value),
//	BT_GATT_CCC(vnd_ccc_cfg_changed,
//		    BT_GATT_PERM_READ | BT_GATT_PERM_WRITE_ENCRYPT),
//	BT_GATT_CHARACTERISTIC(&vnd_auth_uuid.uuid,
//			       BT_GATT_CHRC_READ | BT_GATT_CHRC_WRITE,
//			       BT_GATT_PERM_READ_AUTHEN |
//			       BT_GATT_PERM_WRITE_AUTHEN,
//			       read_vnd, write_vnd, vnd_auth_value),
//	BT_GATT_CHARACTERISTIC(&vnd_long_uuid.uuid, BT_GATT_CHRC_READ |
//			       BT_GATT_CHRC_WRITE | BT_GATT_CHRC_EXT_PROP,
//			       BT_GATT_PERM_READ | BT_GATT_PERM_WRITE |
//			       BT_GATT_PERM_PREPARE_WRITE,
//			       read_vnd, write_long_vnd, &vnd_long_value),
//	BT_GATT_CEP(&vnd_long_cep),
//	BT_GATT_CHARACTERISTIC(&vnd_signed_uuid.uuid, BT_GATT_CHRC_READ |
//			       BT_GATT_CHRC_WRITE | BT_GATT_CHRC_AUTH,
//			       BT_GATT_PERM_READ | BT_GATT_PERM_WRITE,
//			       read_signed, write_signed, &signed_value),
//        //Moja char 1
//        BT_GATT_CHARACTERISTIC(&char1_signed_uuid.uuid, BT_GATT_CHRC_READ |
//			       BT_GATT_CHRC_WRITE | BT_GATT_CHRC_AUTH,
//			       BT_GATT_PERM_READ | BT_GATT_PERM_WRITE,
//			       read_char1, write_char1, &signed_value1),
//        //Moja char 2
//        BT_GATT_CHARACTERISTIC(&char2_signed_uuid.uuid, BT_GATT_CHRC_READ |
//			       BT_GATT_CHRC_WRITE | BT_GATT_CHRC_AUTH,
//			       BT_GATT_PERM_READ | BT_GATT_PERM_WRITE,
//			       read_char2, write_char2, &signed_value2),
//	//BT_GATT_CHARACTERISTIC(&vnd_write_cmd_uuid.uuid,
//	//		       BT_GATT_CHRC_WRITE_WITHOUT_RESP,
//	//		       BT_GATT_PERM_WRITE, NULL,
//	//		       write_without_rsp_vnd, &vnd_wwr_value),
//);

//static const struct bt_data ad[] = {
//	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
//	BT_DATA_BYTES(BT_DATA_UUID16_ALL,
//		      BT_UUID_16_ENCODE(BT_UUID_HRS_VAL),
//		      BT_UUID_16_ENCODE(BT_UUID_BAS_VAL),
//		      BT_UUID_16_ENCODE(BT_UUID_CTS_VAL)),
//	BT_DATA_BYTES(BT_DATA_UUID128_ALL, BT_UUID_CUSTOM_SERVICE_VAL),
//};

//void mtu_updated(struct bt_conn *conn, uint16_t tx, uint16_t rx)
//{
//	printk("Updated MTU: TX: %d RX: %d bytes\n", tx, rx);
//}

//static struct bt_gatt_cb gatt_callbacks = {
//	.att_mtu_updated = mtu_updated
//};

//static void connected(struct bt_conn *conn, uint8_t err)
//{
//	if (err) {
//		printk("Connection failed (err 0x%02x)\n", err);
//	} else {
//		printk("Connected\n");
//	}
//}

//static void disconnected(struct bt_conn *conn, uint8_t reason)
//{
//	printk("Disconnected (reason 0x%02x)\n", reason);
//}

//BT_CONN_CB_DEFINE(conn_callbacks) = {
//	.connected = connected,
//	.disconnected = disconnected,
//};

//static void bt_ready(void)
//{
//	int err;

//	printk("Bluetooth initialized\n");

//	cts_init();

//	if (IS_ENABLED(CONFIG_SETTINGS)) {
//		settings_load();
//	}

//	err = bt_le_adv_start(BT_LE_ADV_CONN_NAME, ad, ARRAY_SIZE(ad), NULL, 0);
//	if (err) {
//		printk("Advertising failed to start (err %d)\n", err);
//		return;
//	}

//	printk("Advertising successfully started\n");
//}

//static void auth_passkey_display(struct bt_conn *conn, unsigned int passkey)
//{
//	char addr[BT_ADDR_LE_STR_LEN];

//	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

//	printk("Passkey for %s: %06u\n", addr, passkey);
//}

//static void auth_cancel(struct bt_conn *conn)
//{
//	char addr[BT_ADDR_LE_STR_LEN];

//	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

//	printk("Pairing cancelled: %s\n", addr);
//}

//static struct bt_conn_auth_cb auth_cb_display = {
//	.passkey_display = auth_passkey_display,
//	.passkey_entry = NULL,
//	.cancel = auth_cancel,
//};

//static void bas_notify(void)
//{
//	uint8_t battery_level = bt_bas_get_battery_level();

//	battery_level--;

//	if (!battery_level) {
//		battery_level = 100U;
//	}

//	bt_bas_set_battery_level(battery_level);
//}

//static void hrs_notify(void)
//{
//	static uint8_t heartrate = 90U;

//	/* Heartrate measurements simulation */
//	heartrate++;
//	if (heartrate == 101U) {
//		heartrate = 90U;
//                //printk("Heartrate exceeded 100bpm\n");
//	}
        

//	bt_hrs_notify(heartrate);
//}

//void main(void)
//{         
      
        
//        /*new*/

//        const struct device *dev = device_get_binding("HTS221");
//        LOG_INF("\nOlala!\n");
//	if (dev == NULL) {
//		LOG_DBG("Could not get HTS221 device\n");
//		return;
//	}
        
//	if (IS_ENABLED(CONFIG_HTS221_TRIGGER)) {
//		struct sensor_trigger trig = {
//			.type = SENSOR_TRIG_DATA_READY,
//			.chan = SENSOR_CHAN_ALL,
//		};
//		if (sensor_trigger_set(dev, &trig, hts221_handler) < 0) {
//			LOG_DBG("Cannot configure trigger\n");
//			return;
//		}
//	}
//        while (!IS_ENABLED(CONFIG_HTS221_TRIGGER)) {
//		process_sample(dev);
//		k_sleep(K_MSEC(2000));
//                LOG_INF("\nOlala!\n");
//	}
//	k_sleep(K_FOREVER);


//        /*OLD*/
        
// //       flash_dev = FLASH_AREA_DEVICE(STORAGE_NODE_LABEL);
//	//if (!device_is_ready(flash_dev)) {
//	//	printk("Flash device %s is not ready\n", flash_dev->name);
//	//	return;
//	//}
//	//fs.offset = FLASH_AREA_OFFSET(storage);
//	//rc = flash_get_page_info_by_offs(flash_dev, fs.offset, &info);
//	//if (rc) {
//	//	printk("Unable to get page info\n");
//	//	return;
//	//}
//	//fs.sector_size = info.size;
//	//fs.sector_count = 3U;

//	//rc = nvs_init(&fs, flash_dev->name);
//	//if (rc) {
//	//	printk("Flash Init failed\n");
//	//	return;
//	//} 

//	///*BLE*/ 
//	//struct bt_gatt_attr *vnd_ind_attr;
//	//char str[BT_UUID_STR_LEN];
//	//int err;

//	//err = bt_enable(NULL);
//	//if (err) {
//	//	printk("Bluetooth init failed (err %d)\n", err);
//	//	return;
//	//}

//	//bt_ready();

//	//bt_gatt_cb_register(&gatt_callbacks);
//	//bt_conn_auth_cb_register(&auth_cb_display);

//	//vnd_ind_attr = bt_gatt_find_by_uuid(vnd_svc.attrs, vnd_svc.attr_count,
//	//				    &vnd_enc_uuid.uuid);
//	//bt_uuid_to_str(&vnd_enc_uuid.uuid, str, sizeof(str));
//	//printk("Indicate VND attr %p (UUID %s)\n", vnd_ind_attr, str);

//	///* Implement notification. At the moment there is no suitable way
//	// * of starting delayed work so we do it here
//	// */
//	//while (1) {
//	//	k_sleep(K_SECONDS(1));

//	//	/* Current Time Service updates only when time is changed */
//	//	cts_notify();

//	//	/* Heartrate measurements simulation */
//	//	hrs_notify();

//	//	/* Battery level simulation */
//	//	bas_notify();

//	//	/* Vendor indication simulation */
//	//	if (simulate_vnd && vnd_ind_attr) {
//	//		if (indicating) {
//	//			continue;
//	//		}

//	//		ind_params.attr = vnd_ind_attr;
//	//		ind_params.func = indicate_cb;
//	//		ind_params.destroy = indicate_destroy;
//	//		ind_params.data = &indicating;
//	//		ind_params.len = sizeof(indicating);

//	//		if (bt_gatt_indicate(NULL, &ind_params) == 0) {
//	//			indicating = 1U;
//	//		}
//	//	}
//	//}
//}

/* main.c - Application main entry point */

/*
 * Copyright (c) 2015-2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/types.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <sys/printk.h>
#include <sys/byteorder.h>
#include <zephyr.h>

#include <settings/settings.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/conn.h>
#include <bluetooth/uuid.h>
#include <bluetooth/gatt.h>
#include <bluetooth/services/bas.h>
#include <bluetooth/services/hrs.h>

#include "cts.h"


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

/* 1000 msec = 1 sec */
#define SLEEP_TIME      100
/* maximum reboot counts, make high enough to trigger sector change (buffer */
/* rotation). */
#define MAX_REBOOT 400

#define ADDRESS_ID 1
#define KEY_ID 2
#define RBT_CNT_ID 3
#define STRING_ID 4
#define LONG_ID 5

/*definovanie pamate, este navyse su tie reboot countery*/
int rc = 0, cnt = 0, cnt_his = 0;
uint8_t key[4];
uint32_t reboot_counter = 0U, reboot_counter_his;
struct flash_pages_info info;
const struct device *flash_dev;

/*LED Preamble*/

#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS 1000


#include <stdlib.h> //for using the function sleep
#include <stdio.h>
#include <time.h>

/*Temperature and Humidity*/
#include <zephyr.h>
#include <device.h>
#include <drivers/sensor.h>
#include <stdio.h>
#include <sys/util.h>

//maybe for humidity
#include <inttypes.h>



//#include <devicetree.h>
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

static uint8_t vnd_value[VND_MAX_LEN + 1] = { 'V', 'e', 'n', 'd', 'o', 'r'};
static uint8_t vnd_auth_value[VND_MAX_LEN + 1] = { 'V', 'e', 'n', 'd', 'o', 'r'};
static uint8_t vnd_wwr_value[VND_MAX_LEN + 1] = { 'V', 'e', 'n', 'd', 'o', 'r' };

static ssize_t read_vnd(struct bt_conn *conn, const struct bt_gatt_attr *attr,
			void *buf, uint16_t len, uint16_t offset)
{
	const char *value = attr->user_data;

	return bt_gatt_attr_read(conn, attr, buf, len, offset, value,
				 strlen(value));
}

static ssize_t write_vnd(struct bt_conn *conn, const struct bt_gatt_attr *attr,
			 const void *buf, uint16_t len, uint16_t offset,
			 uint8_t flags)
{
	uint8_t *value = attr->user_data;

	if (offset + len > VND_MAX_LEN) {
		return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
	}

	memcpy(value + offset, buf, len);
	value[offset + len] = 0;

	return len;
}

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

#define VND_LONG_MAX_LEN 74
static uint8_t vnd_long_value[VND_LONG_MAX_LEN + 1] = {
		  'V', 'e', 'n', 'd', 'o', 'r', ' ', 'd', 'a', 't', 'a', '1',
		  'V', 'e', 'n', 'd', 'o', 'r', ' ', 'd', 'a', 't', 'a', '2',
		  'V', 'e', 'n', 'd', 'o', 'r', ' ', 'd', 'a', 't', 'a', '3',
		  'V', 'e', 'n', 'd', 'o', 'r', ' ', 'd', 'a', 't', 'a', '4',
		  'V', 'e', 'n', 'd', 'o', 'r', ' ', 'd', 'a', 't', 'a', '5',
		  'V', 'e', 'n', 'd', 'o', 'r', ' ', 'd', 'a', 't', 'a', '6',
		  '.', ' ' };

static ssize_t write_long_vnd(struct bt_conn *conn,
			      const struct bt_gatt_attr *attr, const void *buf,
			      uint16_t len, uint16_t offset, uint8_t flags)
{
	uint8_t *value = attr->user_data;

	if (flags & BT_GATT_WRITE_FLAG_PREPARE) {
		return 0;
	}

	if (offset + len > VND_LONG_MAX_LEN) {
		return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
	}

	memcpy(value + offset, buf, len);
	value[offset + len] = 0;

	return len;
}

static const struct bt_uuid_128 vnd_long_uuid = BT_UUID_INIT_128(
	BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef3));

static struct bt_gatt_cep vnd_long_cep = {
	.properties = BT_GATT_CEP_RELIABLE_WRITE,
};

static int signed_value;
static int signed_value1;
static int signed_value2;



static ssize_t read_char2(struct bt_conn *conn, const struct bt_gatt_attr *attr,
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
				 sizeof(signed_value2));
       
}



static ssize_t write_char2(struct bt_conn *conn, const struct bt_gatt_attr *attr,
			    const void *buf, uint16_t len, uint16_t offset,
			    uint8_t flags)
{
	uint8_t *value = attr->user_data;
        

	if (offset + len > sizeof(signed_value2)) {
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
        
        ///*Thingy kod*/
        const struct device *dev_t;
        bool led_is_on_t = true;
        int ret_t;
        
        bool led_verification_t = false;
        int led_options_t[] = {0,1,2,3,4,5};

        for(int i=0; i<6; i++){
          if(value[0] == led_options_t[i]){
            led_verification_t = true;
          }
        }
        
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
              //LOG_INF("AHAHAHA 2\n");
                                    
            }
          
            if(value[0] == 5){
              
              //led_is_on_t = true; 

              //const struct device *dev_t = device_get_binding("HTS221");
          
      
              if (dev_t == NULL) {
                      LOG_INF("Could not get HTS221 device\n");
                      return;
              }

              if (IS_ENABLED(CONFIG_HTS221_TRIGGER)) {
                      struct sensor_trigger trig = {
                              .type = SENSOR_TRIG_DATA_READY,
                              .chan = SENSOR_CHAN_ALL,
                      };
                      if (sensor_trigger_set(dev_t, &trig, hts221_handler) < 0) {
                              LOG_INF("Cannot configure trigger\n");
                              return;
                      }
              }
              
              static unsigned int obs;

              struct sensor_value temp, hum;
              if (sensor_sample_fetch(dev_t) < 0) {
                      LOG_INF("Sensor sample update error\n");
                      return;
              }

              if (sensor_channel_get(dev_t, SENSOR_CHAN_AMBIENT_TEMP, &temp) < 0) {
                      LOG_INF("Cannot read HTS221 temperature channel\n");
                      return;
              }

              if (sensor_channel_get(dev_t, SENSOR_CHAN_HUMIDITY, &hum) < 0) {
                      LOG_INF("Cannot read HTS221 humidity channel\n");
                      return;
              }

              ++obs;
              LOG_INF("Observation:%u\n", obs);

              /* display temperature */
              //LOG_INF("Temperature:%d C\n", temp.val1);
              LOG_INF("1Temperature:%d C\n", temp.val2);
              //LOG_INF("%" PRId32 " C ..a...\n", temp.val1);
              //LOG_INF("Temperature:%d C\n", temp);

              //if(temp.val1 > 0){
              //  led_is_on_t = true; 
              //}

              /* display humidity */
              //LOG_INF("Relative Humidity:%d %%\n",
              //       hum.val1);
              //LOG_INF("%03" PRId32 " C ..a...\n", hum.val1);

              //LOG_INF("Relative Humidity:%d %%\n",
              //       hum.val2);
              //LOG_INF("%03" PRId32 " C ..a...\n", hum.val2);
              LOG_INF("1Relative Humidity:%d %%\n", hum.val1);
              LOG_INF("2Relative Humidity:%d %%\n", hum.val2);

              LOG_INF("%03" PRId32 " ---\n", hum.val1);
              printf("%" PRId32 " ***\n", hum.val2);
              LOG_INF("%03" PRId32 " ---\n", hum.val2);
              printf("%" PRId32 " ***\n", hum.val1);


              //LOG_INF("idk:%d %\n", hum, hum);

              if(hum.val1 > 56){
                led_is_on_t = true; 
                LOG_INF("MORE THAN 56, turing on");
              }
              if(hum.val1 < 56){
                LOG_INF("less, led off");
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


            }
            //if(value[0] == 2){

            //      // okej funguje to pre led 2
            //      int counter = 0;
            //      while(counter < value[2]){
            //        led_is_on_t = !led_is_on_t;
            //        int navyse_sleep_time = 
            //        k_msleep((value[3]*100));

            //        if(value[1] == 1){
            //          gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led0), gpios), (int)led_is_on_t);
            //        }
            //        if(value[1] == 2){
            //         gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led1), gpios), (int)led_is_on_t);
            //        }
            //        if(value[1] == 3){
            //         gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led2), gpios), (int)led_is_on_t);
            //        }
            //        counter++;
            //      }
            //      //gpio_pin_set(dev_t, DT_GPIO_PIN(DT_ALIAS(led2), gpios), (int)led_is_on_t);
            //} 
          
       
        }

         
        
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


static ssize_t read_signed(struct bt_conn *conn, const struct bt_gatt_attr *attr,
			   void *buf, uint16_t len, uint16_t offset)
{         
        /* bolo const char, ale idk*/
	char *value = attr->user_data;
               
        /*cele definovanie som dal do globalu hore*/         


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
				 sizeof(signed_value));

        
}

static ssize_t write_signed(struct bt_conn *conn, const struct bt_gatt_attr *attr,
			    const void *buf, uint16_t len, uint16_t offset,
			    uint8_t flags)
{
	uint8_t *value = attr->user_data;
   

	if (offset + len > sizeof(signed_value)) {
		return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
	}

	memcpy(value + offset, buf, len);
        
        
        int lenlen = sizeof(value)/sizeof(value[0]);
        printk("Length of written data is max: %d \n", lenlen);

        for (int i = 0; i < 4; i++){
          
          printf("value[%d] = ", i);
          printf("%" PRIx32 "\n", value[i]);   
        
        }

	//flash_dev = FLASH_AREA_DEVICE(STORAGE_NODE_LABEL);
	//if (!device_is_ready(flash_dev)) {
	//	printk("Flash device %s is not ready\n", flash_dev->name);
	//	return;
	//}
	//fs.offset = FLASH_AREA_OFFSET(storage);
	//rc = flash_get_page_info_by_offs(flash_dev, fs.offset, &info);
	//if (rc) {
	//	printk("Unable to get page info\n");
	//	return;
	//}
	//fs.sector_size = info.size;
	//fs.sector_count = 3U;

	//rc = nvs_init(&fs, flash_dev->name);
	//if (rc) {
	//	printk("Flash Init failed\n");
	//	return;
	//}
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

static void bas_notify(void)
{
	uint8_t battery_level = bt_bas_get_battery_level();

	battery_level--;

	if (!battery_level) {
		battery_level = 100U;
	}

	bt_bas_set_battery_level(battery_level);
}

static void hrs_notify(void)
{
	static uint8_t heartrate = 90U;

	/* Heartrate measurements simulation */
	heartrate++;
	if (heartrate == 101U) {
		heartrate = 90U;
                //printk("Heartrate exceeded 100bpm\n");
	}
        

	bt_hrs_notify(heartrate);
}

void main(void)
{         
        
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
		cts_notify();

		/* Heartrate measurements simulation */
		hrs_notify();

		/* Battery level simulation */
		bas_notify();

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



