#include "arduino_secrets.h"
#include "thingProperties.h"

void setup() {
  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(21, OUTPUT);
}

void loop() {
  ArduinoCloud.update();
}

void ledSetColor(r,b,g) {
  analogWrite(18, 255-r);
  analogWrite(19, 255-b);
  analogWrite(21, 255-g);
}

void ledOFF() {
  analogWrite(18, 255);
  analogWrite(19, 255);
  analogWrite(21, 255);
}

void onLightChange()  {
  if (light.getSwitch() == true) {
    uint8_t r, g, b;
    light.getValue().getRGB(r, g, b);
    ledSetColor(r,b,g);
  } else {
    ledOFF();
  }
}
