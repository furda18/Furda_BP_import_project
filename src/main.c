/* main.c - Application main entry point */
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

// my solution
#include "my_solution.c"

/*Flashing Preamle*/
#include <zephyr.h>
#include <sys/reboot.h>
#include <device.h>
#include <string.h>
#include <drivers/flash.h>
#include <storage/flash_map.h>
#include <fs/nvs.h>

/*LED Preamble*/

#include <devicetree.h>
#include <drivers/gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS 1000


#include <stdlib.h> //for using the function sleep
#include <stdio.h>
#include <time.h>




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





static const struct bt_uuid_128 vnd_long_uuid = BT_UUID_INIT_128(
	BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef3));

static struct bt_gatt_cep vnd_long_cep = {
	.properties = BT_GATT_CEP_RELIABLE_WRITE,
};

static int signed_value;
static int signed_value1;
static long signed_value2;
static int len_of_value;

typedef void (*some_random_function)();
static char *value_written;
int value_written_length = 0;

char my_value_ok[100];




static ssize_t read_char2(struct bt_conn *conn, const struct bt_gatt_attr *attr,
			   void *buf, uint16_t len, uint16_t offset)
{         
        /* originally const char, t*/
	char *value = attr->user_data;
       
        int counter = 0;

        //printk("value_written_length: %d\n", value_written_length);

        for (int i = 0; i < len; i++){
          printf("value[%d] = ", i);
          printf("%" PRIx32 "\n", value[i]);   
          if(value[i] == 0){
            counter++;
          }
        }

        
    
        rc = nvs_read(&fs, KEY_ID, &key, sizeof(key));
        if (rc > 0) { /* item was found, show it */
		printk("Id: %d, THE Key is: ", KEY_ID);
		for (int n = 0; n < len; n++) {
			printk("%x ", key[n]);
		}
		printk("\n");
        }

       

        // if input is 000000, all bytes are reseted to 0
        if(counter == 3){
           printk("00-00-00 configuration, rewriting for key! \n");
           for (int i = 0; i < len; i++){           
              value[i] = key[i];
              printk("%x to %x ", value[i], key[i]);
           }
        }    
	return bt_gatt_attr_read(conn, attr, buf, len, offset, value,
				 strlen(value));
       
}


static ssize_t write_char2(struct bt_conn *conn, const struct bt_gatt_attr *attr,
			    const void *buf, uint16_t len, uint16_t offset,
			    uint16_t flags)
{         
        uint8_t *value = attr->user_data;
        uint8_t *stable_value = value;
        

        LOG_INF("Dlzka prijatych dat: %d\n", len);
        value_written = value;
        value_written_length = len;

	memcpy(value + offset, buf, len);     
        
        len_of_value = len;
	/* KEY_ID is used to store a key, lets see if we can read it from flash */
	rc = nvs_read(&fs, KEY_ID, &key, sizeof(key));

        //printk("SIZEOF KEY: %d", sizeof(key));
        rc = 1;
        if (rc > 0) { /* item was found, show it */
		
                for (int n = 0; n < len; n++) {
			//printk("%x ", key[n]);
                        key[n] = value[n];
                        my_value_ok[n] = value[n];
		}
                (void)nvs_write(&fs, KEY_ID, &key, sizeof(key));
                printf("-.-.->\n");
		for (int n = 0; n < len; n++) {
			printk("%d. %x \n", n, key[n]);  
                        printk("%d. %x \n", n, my_value_ok[n]);            
		}
		printk("\n");
	} else   {/* item was not found, add it */
		for (int n = 0; n < len; n++) {
			my_value_ok[n] = value[n];
                        key[n] = value[n];
		}
		(void)nvs_write(&fs, KEY_ID, &key, sizeof(key));
                printf("--->\n");
                for (int n = 0; n < len; n++) {
			printk("%d. %x \n", n, key[n]);  
                        printk("%d. %x \n", n, my_value_ok[n]);             
		}
	}
        
       
        
        //value_written_length = len;
        //printk("value_written_length: %d\n", value_written_length);
        
        //must be true to execute resolve
        config_has_been_written = true;
     
	return len;
}




static const struct bt_uuid_128 char2_signed_uuid = BT_UUID_INIT_128(
	BT_UUID_128_ENCODE(0x11111111, 0x1234, 0x5678, 0x1334, 0x56789abcdef7));



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
        //Charakteristika 2
        BT_GATT_CHARACTERISTIC(&char2_signed_uuid.uuid, BT_GATT_CHRC_READ |
			       BT_GATT_CHRC_WRITE | BT_GATT_CHRC_AUTH,
			       BT_GATT_PERM_READ | BT_GATT_PERM_WRITE,
			       read_char2, write_char2, &signed_value2),
	
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
        len_of_value = 0;
        //TU si pouzivatel definuje funkcie a bajtove oznacenie, podla ktoreho zariadenie ma reagovat
        int (*measure_temerature)() = &get_temperature_value;
        int (*measure_humidity)() = &get_humidity_value;

        register_input(1, measure_temerature);
        register_input(2, measure_humidity);


        void (*led0_on)() = &turn_on_led0;
        void (*led1_on)() = &turn_on_led1;
        void (*led2_on)() = &turn_on_led2;

        void (*led0_off)() = &turn_off_led0;
        void (*led1_off)() = &turn_off_led1;
        void (*led2_off)() = &turn_off_led2;

        register_reaction(1, led0_on);
        register_reaction(2, led1_on);
        register_reaction(3, led2_on);

        register_reaction(4, led0_off);
        register_reaction(5, led1_off);
        register_reaction(6, led2_off);


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
        
      
        //scenar 1
        //int value_written_length_1 = 14;
        //unsigned char my_value_ok[] = {02,00,10,02,35, 00,01, 03, 00,10,02, 35, 00, 02};

        //scenar 2
         int value_written_length_1 = 28;
        unsigned char my_value_ok[] = {03,00,00,02,47,00,02,06,00,16,02,47,00,01,02,00,00,02,47,00,01,05,00,00,02,47,00,02};
          //unsigned char my_value_ok = {0x02,0x00,0x10,0x02,0x35, 0x00,0x01, 0x03, 0x00,0x10,0x02, 0x35, 0x00, 0x02};
	while (1) {
		k_sleep(K_SECONDS(2));

		
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
                
                //printf("VALUE WRITTEN LENGTH: %d\n", value_written_length_1);
                //for(int i=0; i<value_written_length_1; i++){
                //  printf("MAIN: %d\n", my_value_ok[i]);
                //}
                //resolve(my_value_ok, value_written_length_1);


	}


}

