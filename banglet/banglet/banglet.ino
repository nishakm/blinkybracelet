#include <bluefruit.h>

// create GATT service
// creating a generic attribute service: https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.service.generic_attribute.xml
BLEService talkToMeService = BLEService(0x1801);
// creating a string characteristic: https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.characteristic.string.xml
BLECharacteristic talkToMeLevel = BLECharacteristic(0x2A3D);

void setup() {
  Serial.begin(115200);
  Serial.println("Banglet Setup");
  Serial.println("--------------");
  Serial.println("Initialize nrf52 module");
  Bluefruit.begin();
  Bluefruit.setTxPower(4); // set TX power to maximum
  Bluefruit.setName("503Banglet");

  // Set the device connect/disconnect callback handlers - these get called when the device is connected/disconnected
  Bluefruit.setConnectCallback(connect_callback);
  Bluefruit.setDisconnectCallback(disconnect_callback);
  
  // start GATT service
  Serial.println("Setting up GATT service");
  setupGATT();

  // start advertising
  Serial.println("Advertize");
  startAdv();
}

void setupGATT(void){

  // start the service first
  talkToMeService.begin();

  // set up characteristic properties
  // write without response
  talkToMeLevel.setProperties(CHR_PROPS_INDICATE);
  talkToMeLevel.setProperties(CHR_PROPS_WRITE);
  talkToMeLevel.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  talkToMeLevel.setFixedLen(2);

  // start characteristic
  talkToMeLevel.begin();
  talkToMeLevel.write(0x00);
}

void startAdv(void){
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addService(talkToMeService);
  Bluefruit.Advertising.addName();

  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds
}

void connect_callback(uint16_t conn_handle)
{
  char central_name[32] = { 0 };
  Bluefruit.Gap.getPeerName(conn_handle, central_name, sizeof(central_name));

  Serial.print("Connected to ");
  Serial.println(central_name);
}

void disconnect_callback(uint16_t conn_handle, uint8_t reason)
{
  (void) conn_handle;
  (void) reason;

  Serial.println("Disconnected");
  Serial.println("Advertising!");
}

void loop() {


}
