#include <LilyGoLib.h>
#include <lvgl.h>
#include "event.h"
#include "setting.h"
#include <LV_Helper.h>
#include "ui.h"
#include "sensor.h"

const uint32_t screenTimeout = 10000;
bool disableSleep;
bool sleepMode = false;
void setDisableSleep(bool value) {
	Serial.printf("Disable sleep: %d\n", value);
	disableSleep = value;
	if (!value)
		lv_disp_trig_activity(NULL);
	esp_event_post(BLUEWATCH_EVENTS, BLUEWATCH_EVENT_DISABLE_SLEEP_CHANGE, nullptr, 0, 0);
	setting.set(".disableSleep", Json(disableSleep));
}

void setupSleep() {
	setDisableSleep(false);
}

void sleepHandler() {
	void enterLightSleep();
	if (!disableSleep) {
		//Serial.printf("Inactive time: %d\n", lv_disp_get_inactive_time(NULL));
			//Serial.printf("Inactive time: %d\n", difftime(mktime(&timeinfo), mktime(&lastTouchTime)));

		if (millis() - lastTouchTime >= screenTimeout) {
			sleepMode = true;
			enterLightSleep();
		}
	}
		//if (lv_disp_get_inactive_time(NULL) >= screenTimeout)
			//enterLightSleep();
}

void enterLightSleep() {
	lv_obj_set_tile_id(tileview, 0,0,LV_ANIM_OFF);
	Serial.println("Enter light sleep mode.");

	auto brightness = watch.getBrightness();
	watch.decrementBrightness(0);
	//wait for touch
	//watch.clearPMU();

    accel.enableTiltIRQ();
	//accel.disablePedometerIRQ();
	esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);
	gpio_wakeup_enable((gpio_num_t)BOARD_TOUCH_INT, GPIO_INTR_LOW_LEVEL);
	//esp_sleep_enable_ext1_wakeup(_BV(14), ESP_EXT1_WAKEUP_ANY_HIGH);
	gpio_wakeup_enable ((gpio_num_t)14, GPIO_INTR_HIGH_LEVEL);
	esp_sleep_enable_gpio_wakeup();

	esp_light_sleep_start();
	Serial.println("wake up");
	accel.disableTiltIRQ();
	//accel.enablePedometerIRQ();

	watch.incrementalBrightness(brightness);
}

/*

void enterLightSleep() {
	Serial.println("Enter light sleep mode.");

	auto brightness = watch.getBrightness();
	watch.decrementBrightness(0);

	esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);
	gpio_wakeup_enable((gpio_num_t)BOARD_TOUCH_INT, GPIO_INTR_LOW_LEVEL);
	esp_sleep_enable_gpio_wakeup();

	esp_light_sleep_start();

	lv_disp_trig_activity(NULL);

	watch.incrementalBrightness(brightness);
}
*/