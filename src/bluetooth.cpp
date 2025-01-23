#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <LilyGoLib.h>
#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

BLECharacteristic *pCharacteristic;
char title[160] = {"Undefined"};

//void avrc_metadata_callback(uint8_t id, const uint8_t *text) {
  //Serial.printf("==> AVRC metadata rsp: attribute id 0x%x, %s\n", id, text);
  //if (id == ESP_AVRC_MD_ATTR_TITLE) {
    //strncpy(title, (const char *)text, 160);
    //pCharacteristic->setValue(title);
  //}
//}

void initBluetooth() {

  // start BLE
  BLEDevice::init("MyMusic");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ);

  pCharacteristic->setValue(title);
  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(
      0x06); // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");
}
