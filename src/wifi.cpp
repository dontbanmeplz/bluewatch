#include <Arduino.h>
#include <WiFi.h>
#include <SPIFFS.h>
#include "event.h"
#include "setting.h"
#include "wifi_.h"
#include <vector>

using std::vector;

vector<WifiNetwork> wifiNetwork;
WifiSetting wifiSetting;

bool wifiConnecting;

void registerEventHandlers()
{
	esp_event_handler_register(BLUEWATCH_EVENTS, BLUEWATCH_EVENT_WIFI_CONNECTING, [](void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *event_data) {
		wifiConnecting = true;
	}, nullptr);

	WiFi.onEvent([=](arduino_event_id_t id, arduino_event_info_t info) {
		switch (id) {
			case ARDUINO_EVENT_WIFI_STA_CONNECTED:
			case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
			case ARDUINO_EVENT_WIFI_STA_GOT_IP:
			case ARDUINO_EVENT_WIFI_STA_GOT_IP6:
			case ARDUINO_EVENT_WIFI_STA_LOST_IP:
				wifiConnecting = false;
				break;
		}
	});
}

void setupWifi()
{
	registerEventHandlers();

	if (SPIFFS.exists("/wifi-network.json")) {
		auto network = wifiNetworkSetting.get("");
		Serial.println("wifi network count: " + String(network.length()));
		for (auto i = 0; i < network.length(); i++) {
			Serial.println("got network " + String(i));
			auto n = network[i];
			Serial.println("1");
			wifiNetwork.push_back(
				WifiNetwork{
					.ssid = (String)n["ssid"],
					.password = (String)n["password"]
				}
			);
			Serial.println("2");
		}
	}
	Serial.println("got networks");
	auto wifi = setting.get(".wifi");
	wifiSetting.network = (String)wifi["network"];
	wifiSetting.enabled = (bool)wifi["enabled"];
	Serial.println("wifi enabled: " + String(wifiSetting.enabled));
	if (wifiSetting.enabled) {
		Serial.println("Connecting to WiFi network: " + wifiSetting.network);
		for (auto &network : wifiNetwork) {
			Serial.println("Network: " + String(network.ssid));
			if (network.ssid == wifiSetting.network) {
				Serial.println("Network found: " + String(network.ssid));
				WiFi.begin(network.ssid, network.password);
				esp_event_post(BLUEWATCH_EVENTS, BLUEWATCH_EVENT_WIFI_CONNECTING, nullptr, 0, 0);
				break;
			}
		}
		/*Serial.println("Network found: " + String(network->ssid));
		WiFi.begin(network->ssid, network->password);
		esp_event_post(BLUEWATCH_EVENTS, BLUEWATCH_EVENT_WIFI_CONNECTING, nullptr, 0, 0);*/

	}
}
