#include <M5Atom.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <string>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// RC pin
#define LEFT_PIN 33
#define RIGHT_PIN 22
#define UP_PIN 19
#define DOWN_PIN 23

#define FREQ 5000
#define L_CHANNEL 0
#define R_CHANNEL 1
#define UP_CHANNEL 2
#define DOWN_CHANNEL 3
#define RESOLUTION 8

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

std::string command = "OP 0 0";

class MyCallbacks : public BLECharacteristicCallbacks
{
  void onRead(BLECharacteristic *pCharacteristic)
  {
    pCharacteristic->setValue("OP 0 0");
    Serial.println("onRead");
  }

  void onWrite(BLECharacteristic *pCharacteristic)
  {
    std::string value = pCharacteristic->getValue();
    if (!value.empty())
    {
      command = value;
    }
    //Serial.println(value.c_str());
    Serial.println("onWrite");
  }
};

float FBpower = 0.0;
float LRpower = 0.0;

void motorFB(int power)
{
  if (power > 0)
  {
    ledcWrite(DOWN_CHANNEL, power);
    ledcWrite(UP_CHANNEL, 0);
  }
  else
  {
    ledcWrite(UP_CHANNEL, abs(power));
    ledcWrite(DOWN_CHANNEL, 0);
  }
}

void motorLR(int power)
{
  if (power > 0)
  {
    ledcWrite(R_CHANNEL, power);
    ledcWrite(L_CHANNEL, 0);
  }
  else
  {
    ledcWrite(L_CHANNEL, abs(power));
    ledcWrite(R_CHANNEL, 0);
  }
}

void setup()
{
  M5.begin();
  Serial.println("Starting BLE work!");

  //PWM setup
  ledcSetup(L_CHANNEL, FREQ, RESOLUTION);
  ledcAttachPin(LEFT_PIN, L_CHANNEL);
  ledcSetup(R_CHANNEL, FREQ, RESOLUTION);
  ledcAttachPin(RIGHT_PIN, R_CHANNEL);
  ledcSetup(UP_CHANNEL, FREQ, RESOLUTION);
  ledcAttachPin(UP_PIN, UP_CHANNEL);
  ledcSetup(DOWN_CHANNEL, FREQ, RESOLUTION);
  ledcAttachPin(DOWN_PIN, DOWN_CHANNEL);

  // BLE setup
  BLEDevice::init("m5atom-rc");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ |
          BLECharacteristic::PROPERTY_WRITE);

  pCharacteristic->setCallbacks(new MyCallbacks());

  pService->start();
  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06); // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");
}

void loop()
{
  M5.update();

  sscanf(command.c_str(), "OP %f %f", &FBpower, &LRpower);
  motorFB(floor(FBpower * 5.0));
  motorLR(floor(LRpower * 5.0));

  FBpower = 0.0;
  LRpower = 0.0;
  delay(10);
}
