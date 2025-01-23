#include <LilyGoLib.h>
#include <LV_Helper.h>
#include "ui.h"
#include "sleep.h"
#include "battery.h"
#include "wifi_.h"
#include "js.h"
#include "watchface.h"
#include "webServer_.h"
#include "filesystem.h"
#include <SPIFFS.h>
//#include "bluetooth.h"

const char *ntpServer1 = "pool.ntp.org";
const char *ntpServer2 = "time.nist.gov";
const int timezone = -5;

SET_LOOP_TASK_STACK_SIZE(16 * 1024);	// Duktape compile may use up default (8K) stack space

void setup()
{
	Serial.begin(115200);
	watch.begin();
	beginLvglHelper();
	if(!SPIFFS.begin()){
        Serial.println("SPIFFS Mount Failed");
    }
	setupFILESYSTEM();
	setupUi();

	configTime(timezone * 3600, 0, ntpServer1, ntpServer2);
	WiFi.begin("IU PublicNet", "");

	setupJs();
	setupWebServer();
	File root = SPIFFS.open("/");
 
	File file = root.openNextFile();
	
	while(file){
	
		Serial.print("FILE: ");
		Serial.println(file.name());
	
		file = root.openNextFile();
	}
	//initBluetooth();
}

void loop()
{
	lv_task_handler();
	//if (lv_disp_get_inactive_time(NULL) >= 15000)
		//enterLightSleep();
	sleepHandler();
	batteryHandler();
	watchfaceHandler();
	webServer.handleClient();

	delay(5);
}
