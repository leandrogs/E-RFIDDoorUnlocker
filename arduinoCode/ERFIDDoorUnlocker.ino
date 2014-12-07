/* Arduino RC522 RFID Door Unlocker
 * July/2014 Omer Siar Baysal
 * 
 * Unlocks a Door (controls a relay actually)
 * using a RC522 RFID reader with SPI interface on your Arduino
 * You define a Master Card which is act as Programmer
 * then you can able to choose card holders who able to unlock
 * the door or not.
 * 
 * Easy User Interface
 *
 * Just one RFID tag needed whether Delete or Add Tags
 * You can choose to use Leds for output or
 * Serial LCD module to inform users. Or you can use both
 *
 * Stores Information on EEPROM
 *
 * Information stored on non volatile Arduino's EEPROM 
 * memory to preserve Users' tag and Master Card
 * No Information lost if power lost. 
 * EEPROM has unlimited Read cycle but 100,000 limited Write cycle. 
 * 
 * Security
 * 
 * To keep it simple we are going to use Tag's Unique IDs
 * It's simple, a bit secure, but not hacker proof.
 *
 * MFRC522 Library also lets us to use some authentication
 * mechanism, writing blocks and reading back
 * and there is great example piece of code
 * about reading and writing PICCs
 * here > http://makecourse.weebly.com/week10segment1.html
 *
 * If you rely on heavy security, figure it out how RFID system
 * can be secure yourself (personally very curious about it)
 * 
 * Credits
 *
 * Omer Siar Baysal who put together this project
 *
 * Idea and most of code from Brett Martin's project
 * http://www.instructables.com/id/Arduino-RFID-Door-Lock/
 * www.pcmofo.com
 *
 * MFRC522 Library
 * https://github.com/miguelbalboa/rfid
 * Based on code Dr.Leong   ( WWW.B2CQSHOP.COM )
 * Created by Miguel Balboa (circuitito.com), Jan, 2012.
 * Rewritten by Søren Thing Andersen (access.thing.dk), fall of 2013 
 * (Translation to English, refactored, comments, anti collision, cascade levels.)
 *
 * Arduino Forum Member luisilva for His Massive Code Correction
 * http://forum.arduino.cc/index.php?topic=257036.0
 * http://forum.arduino.cc/index.php?action=profile;u=198897
 *
 * License
 *
 * You are FREE what to do with this code
 * Just give credits who put effort on this code
 *
 * "PICC" short for Proximity Integrated Circuit Card (RFID Tags)
 */

#include <EEPROM.h>  // We are going to read and write PICC's UIDs from/to EEPROM
#include <SPI.h>      // RC522 Module uses SPI protocol
#include <MFRC522.h>   // Library for Mifare RC522 Devices
#include <Ethernet.h>
#include <aJSON.h>

/* Instead of a Relay maybe you want to use a servo
 * Servos can lock and unlock door locks too
 * There are examples out there.
 */

// #include <Servo.h>

/* For visualizing whats going on hardware
 * we need some leds and
 * to control door lock a relay and a wipe button
 * (or some other hardware)
 * Used common anode led,digitalWriting HIGH turns OFF led
 * Mind that if you are going to use common cathode led or
 * just seperate leds, simply comment out #define COMMON_ANODE,
 */

// #define COMMON_ANODE

#ifdef COMMON_ANODE
#define LED_ON LOW
#define LED_OFF HIGH
#else
#define LED_ON HIGH
#define LED_OFF LOW
#endif

#define redLed 7
#define greenLed 6
#define blueLed 5
#define relay 4
#define wipeB 3 // Button pin for WipeMode

#define CHECK_ALL 0
#define CREATE_ONE 1
#define CHECK_ONE 2
#define CHECK_MASTER 3
#define CHECK_ONE_ASSOC 4
#define CREATE_MASTER 5

boolean match = false; // initialize card match to false
boolean programMode = false; // initialize programming mode to false

int successRead; // Variable integer to keep if we have Successful Read from Reader

byte storedCard[4];   // Stores an ID read from EEPROM
byte readCard[4];           // Stores scanned ID read from RFID Module
char cardUID[10];
byte masterCard[4]; // Stores master card's ID read from EEPROM

/* We need to define MFRC522's pins and create instance
 * Pin layout should be as follows (on Arduino Uno):
 * MOSI: Pin 11 / ICSP-4
 * MISO: Pin 12 / ICSP-1
 * SCK : Pin 13 / ICSP-3
 * SS : Pin 10 (Configurable)
 * RST : Pin 9 (Configurable)
 * look MFRC522 Library for
 * pin configuration for other Arduinos.
 */

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.

byte mac[] = {0x98, 0x4F, 0xEE, 0x01, 0x10, 0xE2 };
char server[] = "192.168.1.70";
IPAddress ip(192,168,1,177);

EthernetClient client;

boolean startRead = false;
String jsonString = "";
String jsonStringCurr = "";

///////////////////////////////////////// Setup ///////////////////////////////////
void setup() {
  //Arduino Pin Configuration
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH); // Make sure door is locked
  digitalWrite(redLed, LED_OFF); // Make sure led is off
  digitalWrite(greenLed, LED_OFF); // Make sure led is off
  digitalWrite(blueLed, LED_OFF); // Make sure led is off
  
  //Protocol Configuration
  Serial.begin(9600);    // Initialize serial communications with PC
  SPI.begin();           // MFRC522 Hardware uses SPI protocol
  mfrc522.PCD_Init();    // Initialize MFRC522 Hardware
  mfrc522.PCD_SetAntennaGain(mfrc522.RxGain_max); //Set Antenna Gain to Max- this will increase reading distance

  // start the Ethernet connection:
  // if (Ethernet.begin(mac) == 1) {
  //   Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    Ethernet.begin(mac,ip);
  // }

  Serial.print("IP Address        : ");
  Serial.println(Ethernet.localIP());
  Serial.print("Subnet Mask       : ");
  Serial.println(Ethernet.subnetMask());
  Serial.print("Default Gateway IP: ");
  Serial.println(Ethernet.gatewayIP());
  Serial.print("DNS Server IP     : ");
  Serial.println(Ethernet.dnsServerIP());
  // give the Ethernet shield a second to initialize:
  delay(1000);
  
  //TODO: Verificar se tem algúma tag no banco de dados. Se não tiver, cadastra a primeira como MASTER
  if (query(CHECK_ALL, "")) {  // Look EEPROM if Master Card defined, EEPROM address 1 holds if defined
    Serial.println("No Master Card Defined");
    Serial.println("Scan A PICC to Define as Master Card");
    do {
      successRead = getID(); // sets successRead to 1 when we get read from reader otherwise 0
      digitalWrite(blueLed, LED_ON); // Visualize Master Card need to be defined
      delay(200);
      digitalWrite(blueLed, LED_OFF);
      delay(200);
    }
    while (!successRead); //the program will not go further while you not get a successful read

    sprintf(cardUID, "%02X%02X%02X%02X", readCard[0], readCard[1], readCard[2], readCard[3]);
    query(CREATE_ONE, cardUID);
    query(CREATE_MASTER, cardUID);
    Serial.println("Master Card Defined"); 
  }
  Serial.println("##### RFID Door Acces Control v2.0.8 #####"); //For debug purposes
  Serial.println("");
  Serial.println("Waiting PICCs to bo scanned :)");
  cycleLeds();    // Everything ready lets give user some feedback by cycling leds
}


///////////////////////////////////////// Main Loop ///////////////////////////////////
void loop () {
  do {
    successRead = getID(); // sets successRead to 1 when we get read from reader otherwise 0
    if (programMode) {
      cycleLeds(); // Program Mode cycles through RGB waiting to read a new card
    }
    else {
      normalModeOn(); // Normal mode, blue Power LED is on, all others are off
    }
  }
  while (!successRead); //the program will not go further while you not get a successful read
  if (programMode) {
    Serial.println("Cheking if is master on programMode");
    if ( isMaster(readCard) ) {  //If master card scanned again exit program mode
      Serial.println("This is Master Card"); 
      Serial.println("Exiting Program Mode");
      Serial.println("-----------------------------");
      programMode = false;
      return;
    }
    else {  
      if ( findID(readCard, CHECK_ONE) ) { //If scanned card is known delete it
        Serial.println("I know this PICC, so do nothing");
        // deleteID(readCard);
        Serial.println("-----------------------------");
      }
      else {                    // If scanned card is not known add it
        Serial.println("I do not know this PICC, adding...");
        writeID(readCard);
        Serial.println("-----------------------------");
      }
    }
  }
  else {
    Serial.println("Cheking if is master");
    if ( isMaster(readCard) ) {  // If scanned card's ID matches Master Card's ID enter program mode
      programMode = true;
      Serial.println("Hello");
      Serial.println("Scan a PICC to ADD");
      Serial.println("-----------------------------");
    }
    else {
      if ( findID(readCard, CHECK_ONE_ASSOC) ) {        // If not, see if the card is in the EEPROM 
        Serial.println("Welcome, You shall pass");
        openDoor(300);                // Open the door lock for 300 ms
      }
      else {                // If not, show that the ID was not valid
        Serial.println("You shall not pass");
        failed(); 
      }
    }
  }
}

///////////////////////////////////////// Get PICC's UID ///////////////////////////////////
int getID() {
  // Getting ready for Reading PICCs
  if ( ! mfrc522.PICC_IsNewCardPresent()) { //If a new PICC placed to RFID reader continue
    return 0;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) { //Since a PICC placed get Serial and continue
    return 0;
  }
  // There are Mifare PICCs which have 4 byte or 7 byte UID care if you use 7 byte PICC
  // I think we should assume every PICC as they have 4 byte UID
  // Until we support 7 byte PICCs
  Serial.println("Scanned PICC's UID:");
  for (int i = 0; i < 4; i++) {  // 
    readCard[i] = mfrc522.uid.uidByte[i];
    Serial.print(readCard[i], HEX);
  }
  Serial.println("");
  mfrc522.PICC_HaltA(); // Stop reading
  return 1;
}

///////////////////////////////////////// Cycle Leds (Program Mode) ///////////////////////////////////
void cycleLeds() {
  digitalWrite(redLed, LED_OFF); // Make sure red LED is off
  digitalWrite(greenLed, LED_ON); // Make sure green LED is on
  digitalWrite(blueLed, LED_OFF); // Make sure blue LED is off
  delay(200);
  digitalWrite(redLed, LED_OFF); // Make sure red LED is off
  digitalWrite(greenLed, LED_OFF); // Make sure green LED is off
  digitalWrite(blueLed, LED_ON); // Make sure blue LED is on
  delay(200);
  digitalWrite(redLed, LED_ON); // Make sure red LED is on
  digitalWrite(greenLed, LED_OFF); // Make sure green LED is off
  digitalWrite(blueLed, LED_OFF); // Make sure blue LED is off
  delay(200);
}

//////////////////////////////////////// Normal Mode Led  ///////////////////////////////////
void normalModeOn () {
  digitalWrite(blueLed, LED_ON); // Blue LED ON and ready to read card
  digitalWrite(redLed, LED_OFF); // Make sure Red LED is off
  digitalWrite(greenLed, LED_OFF); // Make sure Green LED is off
  digitalWrite(relay, HIGH); // Make sure Door is Locked
}

///////////////////////////////////////// Add ID to EEPROM   ///////////////////////////////////
boolean writeID( byte a[] ) {
  sprintf(cardUID, "%02X%02X%02X%02X", a[0], a[1], a[2], a[3]);
  if(query(CREATE_ONE, cardUID)){
      return true;
  }
  return false;
}

///////////////////////////////////////// Find ID From EEPROM   ///////////////////////////////////
boolean findID(byte find[], int op) {
  sprintf(cardUID, "%02X%02X%02X%02X", find[0], find[1], find[2], find[3]);

  switch (op) {
      case 2:
        if(query(CHECK_ONE, cardUID)) {
          return true;
        }
        break;
      case 4:
        if(query(CHECK_ONE_ASSOC, cardUID)) {
          return true;
        }
        break;
  }

  return false;
}

///////////////////////////////////////// Write Success to EEPROM   ///////////////////////////////////
// Flashes the green LED 3 times to indicate a successful write to EEPROM
void successWrite() {
  digitalWrite(blueLed, LED_OFF); // Make sure blue LED is off
  digitalWrite(redLed, LED_OFF); // Make sure red LED is off
  digitalWrite(greenLed, LED_OFF); // Make sure green LED is on
  delay(200);
  digitalWrite(greenLed, LED_ON); // Make sure green LED is on
  delay(200);
  digitalWrite(greenLed, LED_OFF); // Make sure green LED is off
  delay(200);
  digitalWrite(greenLed, LED_ON); // Make sure green LED is on
  delay(200);
  digitalWrite(greenLed, LED_OFF); // Make sure green LED is off
  delay(200);
  digitalWrite(greenLed, LED_ON); // Make sure green LED is on
  delay(200);
  Serial.println("Succesfully added ID record to EEPROM");
}

///////////////////////////////////////// Write Failed to EEPROM   ///////////////////////////////////
// Flashes the red LED 3 times to indicate a failed write to EEPROM
void failedWrite() {
  digitalWrite(blueLed, LED_OFF); // Make sure blue LED is off
  digitalWrite(redLed, LED_OFF); // Make sure red LED is off
  digitalWrite(greenLed, LED_OFF); // Make sure green LED is off
  delay(200);
  digitalWrite(redLed, LED_ON); // Make sure red LED is on
  delay(200);
  digitalWrite(redLed, LED_OFF); // Make sure red LED is off
  delay(200);
  digitalWrite(redLed, LED_ON); // Make sure red LED is on
  delay(200);
  digitalWrite(redLed, LED_OFF); // Make sure red LED is off
  delay(200);
  digitalWrite(redLed, LED_ON); // Make sure red LED is on
  delay(200);
  Serial.println("Failed! There is something wrong with ID or bad EEPROM");
}

///////////////////////////////////////// Success Remove UID From EEPROM  ///////////////////////////////////
// Flashes the blue LED 3 times to indicate a success delete to EEPROM
void successDelete() {
  digitalWrite(blueLed, LED_OFF); // Make sure blue LED is off
  digitalWrite(redLed, LED_OFF); // Make sure red LED is off
  digitalWrite(greenLed, LED_OFF); // Make sure green LED is off
  delay(200);
  digitalWrite(blueLed, LED_ON); // Make sure blue LED is on
  delay(200);
  digitalWrite(blueLed, LED_OFF); // Make sure blue LED is off
  delay(200);
  digitalWrite(blueLed, LED_ON); // Make sure blue LED is on
  delay(200);
  digitalWrite(blueLed, LED_OFF); // Make sure blue LED is off
  delay(200);
  digitalWrite(blueLed, LED_ON); // Make sure blue LED is on
  delay(200);
  Serial.println("Succesfully removed ID record from EEPROM");
}

////////////////////// Check readCard IF is masterCard   ///////////////////////////////////
// Check to see if the ID passed is the master programing card
boolean isMaster( byte test[] ) {
  sprintf(cardUID, "%02X%02X%02X%02X", test[0], test[1], test[2], test[3]);
  if (query(CHECK_MASTER,cardUID)) {
    return true;
  } else {
    return false;
  }
}

///////////////////////////////////////// Unlock Door   ///////////////////////////////////
void openDoor( int setDelay ) {
  digitalWrite(blueLed, LED_OFF); // Turn off blue LED
  digitalWrite(redLed, LED_OFF); // Turn off red LED    
  digitalWrite(greenLed, LED_ON); // Turn on green LED
  digitalWrite(relay, LOW); // Unlock door!
  delay(setDelay); // Hold door lock open for given seconds
  digitalWrite(relay, HIGH); // Relock door
  delay(2000); // Hold green LED on for 2 more seconds
}

///////////////////////////////////////// Failed Access  ///////////////////////////////////
void failed() {
  digitalWrite(greenLed, LED_OFF); // Make sure green LED is off
  digitalWrite(blueLed, LED_OFF); // Make sure blue LED is off
  digitalWrite(redLed, LED_ON); // Turn on red LED
  delay(1200);
}

String requestServer(int code, char uid[]) {

  Serial.println("conectando...");
  delay(1000);

  // Iniciando conexao com o servidor 
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.print("GET /secdoorlock/operations.php?cod=");
    client.print(code);
    client.print("&tag=");
    client.print(uid);
    client.println(" HTTP/1.0");
    client.println();

    //Aguardando conexao
    while(!client.available()){
      delay(1);
    }

    //Percorre os caracteres do envelope HTTP do servidor e armazena na String apenas o conteudo JSON
    while (client.available()) {
      char c = client.read();
      Serial.print(c);
      if( c == '{' ) { 
        startRead = true; 
      }
      if ( startRead ) { 
        jsonString += c; 
      }
      if (c == '}') {
        startRead = false;
      }
    }
    //Reseta a flag de leitura de conteudo JSON
    startRead = false;
  } 
  else {
    // Caso nao ocorra conexao
    Serial.println("conexao falhou");
  }

  client.stop();

  return jsonString;
}

boolean parseJson(char *jsonString) {
  //Inicializa o objeto Pai
  aJsonObject* root = aJson.parse(jsonString);


  if (root != NULL) {
    //Caputura o objeto adesaoDia
    aJsonObject* status = aJson.getObjectItem(root, "stat");
    int stat = status->valueint;
    Serial.print("Status: ");
    Serial.println(stat);
    if(stat){
      aJson.deleteItem(root);
      return true;
    }
  }

  //Deleta o objeto apos a utilizacao para liberacao de memoria
  aJson.deleteItem(root);
  return false;
}

boolean query(int code, char uid[]) {
  bool status = false;
  jsonString = requestServer(code, uid);
  if(!jsonString.equals("")){

      char jsonChar[jsonString.length()];
      jsonString.toCharArray(jsonChar, jsonString.length() + 1);
      status = parseJson(jsonChar);
      jsonString = "";
  }
  return status;
}