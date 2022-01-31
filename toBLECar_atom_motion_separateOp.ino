#include <M5Atom.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <string>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// RC pin
#define SERVO_CH 1
#define MOTOR_CH 1

AtomMotion Atom;

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

std::string command = "OP NO 0 0";

class MyCallbacks : public BLECharacteristicCallbacks
{
  void onRead(BLECharacteristic *pCharacteristic)
  {
    pCharacteristic->setValue("OP NO 0 0");
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
char operation[3];

void motorFB(float raw_power)
{
  float normal_power = raw_power*127*2/50;
  if(normal_power > 127)
    normal_power = 127;
  else if(normal_power < -127)
    normal_power = -127;

  Atom.SetMotorSpeed(MOTOR_CH, normal_power);
}

void motorLR(float raw_angle)
{
  const float normal_angle = (raw_angle + 50.0)*180.0/100.0;
  Atom.SetServoAngle(SERVO_CH, normal_angle);
}

void setup()
{
  M5.begin(true, false, true);
  Atom.Init();
  Serial.println("Starting BLE work!");

  // BLE setup
  BLEDevice::init("m5-atom-motion-rc");
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

  sscanf(command.c_str(), "OP %s %f %f",operation, &FBpower, &LRpower);
  //Serial.printf("receive FBPower:%f LRPower%f\n",FBpower,LRpower);
  if(strcmp(operation,"FB")==0)
    motorFB(FBpower);
  if(strcmp(operation,"LR")==0)
    motorLR(LRpower);

  FBpower = 0.0;
  LRpower = 0.0;
  delay(10);
}
