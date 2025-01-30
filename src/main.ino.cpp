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
#include <duktape.h>
#include "event.h"
#include "settingPanel.h"
#include <duktape.h>
#include "setting.h"
#include "json.h"
#include "sensor.h"
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
	Serial.println("setup filesystem done");

	configTime(timezone * 3600, 0, ntpServer1, ntpServer2);
	//WiFi.begin("IU PublicNet", "");
	setupWifi();
	Serial.println("setup wifi done");
	setupJs();
	Serial.println("setup js done");
	setupUi(jsContext);
	Serial.println("setup ui done");
	setupWebServer();
	Serial.println("setup web done");
	setupSettingPanel();
	Serial.println("setup setting done");
	SetupSensor();
	//initBluetooth();
}

void loop()
{
	if (sleepMode){
		uint32_t wakeup_reason = esp_sleep_get_wakeup_cause();
		if (wakeup_reason == 7) {
			sleepMode = false;
			uint32_t now = millis();
        	lastTouchTime = now;
		}
	}
	lv_task_handler();
	//if (lv_disp_get_inactive_time(NULL) >= 15000)
		//enterLightSleep();
	sleepHandler();
	batteryHandler();
	watchfaceHandler();
	webServer.handleClient();

	delay(5);
}
