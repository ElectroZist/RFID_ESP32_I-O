
#include <rfid.h>
#include <softspi.h>

RFID rfid;        //create a variable type of RFID
uchar serNum[5];  // array to store your ID
int ser;
int a, b, c, d, e, f;

int buzzer = D12;


void setup() {

  Serial.begin(115200);
  while(!Serial);
  Serial.println("RFID NANO ESP32 v1.0");
  delay(300);

  pinMode(buzzer, OUTPUT);

}


void loop() {

  a = checkRFID(0);
  b = checkRFID(1);
  c = checkRFID(2);
  d = checkRFID(3);
  e = checkRFID(4);
  f = checkRFID(5);



  delay(50);
}


int checkRFID(int i) {

  if (i == 0) {
    rfid.begin(2, D6, D4, A7, D5, D3);
  }
  if (i == 1) {
    rfid.begin(2, D6, D4, A6, D5, D3);
  }
  if (i == 2) {
    rfid.begin(2, D6, D4, A3, D5, D3);
  }
  if (i == 3) {
    rfid.begin(2, D6, D4, A2, D5, D3);
  }
  if (i == 4) {
    rfid.begin(2, D6, D4, A1, D5, D3);
  }
  if (i == 5) {
    rfid.begin(2, D6, D4, A0, D5, D3);
  }

  delay(100);

  rfid.init();
  uchar status;

  uchar str[MAX_LEN];
  // Search card, return card types
  status = rfid.request(PICC_REQIDL, str);
  if (status != MI_OK) {
    return 0;
  }
  // Show card type
  //rfid.showCardType(str);
  //Prevent conflict, return the 4 bytes Serial number of the card
  status = rfid.anticoll(str);
  if (status == MI_OK) {
    memcpy(serNum, str, 5);
  }
  delay(100);
  rfid.halt();  //command the card into sleep mode
  ser = serNum[3] + serNum[2] + serNum[1];
  Serial.print("Sensor No: ");
  Serial.print(i);
  Serial.print("  ");
  Serial.print("Card ID: ");
  Serial.println(ser);
  return ser;
}
