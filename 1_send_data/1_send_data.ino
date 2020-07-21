/******************************************************************************
   DEFAULT VALUES
 ******************************************************************************/

// Set MQTT security:
// comment the line to disable security (MQTT),
// uncomment to activate TLS security (MQTTS).
#define MQTT_TLS


/******************************************************************************
   INCLUDES
 ******************************************************************************/
#include "LiveObjects.h"

/******************************************************************************
   USER VARIABLES
 ******************************************************************************/
LiveObjects& lo = LiveObjects::get();
uint32_t messageRate = 60000;   // stores the current data message rate in Milliseconds
unsigned long uptime;   // stores the device uptime (sent as fake sensor data)
unsigned long lastMessageTime = 0;   // stores the time when last data message was sent


/******************************************************************************
   USER PROGRAM
 ******************************************************************************/

void setup() {
  Serial.begin(115200);
  Serial.print("\n*** Live Objects on Arduino MKR NB 1500, revision ");
  Serial.print(SW_REVISION);
  Serial.println("***");
  lo.connect();                          // connects to the network + Live Objects
}

void loop() {
  if (millis() - lastMessageTime > messageRate) {
    // collect data periodically
    Serial.println("Sampling data");
    uptime = millis();
    lo.addToPayload("uptime", uptime);               // adding 'uptime' value to the current payload

    Serial.println("Sending data to Live Objects");
    lo.sendData();                                   // send the data to Live Objects
    lastMessageTime = millis();
  }
  lo.loop();                             // don't forget to keep this in your main loop
}
