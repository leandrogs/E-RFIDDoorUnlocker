/* E-RFIDDoorUnlocker
*December, 2014 - Leandro Gomes da Silva, Pablo Antunes Silva, Lucas Cedro de Lima
*
*A simple solution to unlock the door using RFID tags and "authentication" over 
*Internet. Hardware in use is a Galileo board which is compatible with Arduino uno.
*
*This project is based on Omer Siar Baysal RFID project 
*https://github.com/omersiar/RFID522-Door-Unlock and also on Victor Hugo Montes 
*Aldir Santos project using aJSON parser https://bitbucket.org/victoraldir/ajson-aviseja
*
*Hardware
*We are using a Intel Galileo board. It already have Ethernet connection so we 
*decided to communicate with the server through it. This project also uses a RFID-RC522
*shield (Compatible with MIFARI tags) and a RGB LED to give some output for users.
*
*Web Interface
*This project allows an Administrator of the system to associate one UID for each
*user. As mentioned on Omer Siar Baysal project, it is still possible to create a 
*master tag, but only if there is no UID on DB and a ADMIN user is lready defined. 
*Web Interface was built using CakePHP and MYSql database.
*
*Security
*We still lack security. All we do is allow user to open the door only if his tag 
*UID is already associated to one user on database. It is also a problem whe the 
*server returns a response. The response is always 0 or 1 in a JSON format without 
*any encryption.
*
*Credits
*Main code based on: RFID522 Door Unlock - Omer Siar Baysal 
*https://github.com/omersiar/RFID522-Door-Unlock 
*aJSON AviseJá - Victor Hugo Montes Aldir Santos 
*https://bitbucket.org/victoraldir/ajson-aviseja
*
*aJSON Library https://github.com/interactive-matter/aJson
*
*MFRC522 Library https://github.com/miguelbalboa/rfid Based on code Dr.Leong 
*( WWW.B2CQSHOP.COM ) Created by Miguel Balboa (circuitito.com), Jan, 2012. 
*Rewritten by Søren Thing Andersen (access.thing.dk), fall of 2013 (Translation 
*to English, refactored, comments, anti collision, cascade levels.)
*
*A BIG thanks to iMobilis (laboratory of mobile computing) at UFOP/ICEA for 
*lending us the Galileo and the RFID shield. iMobilis http://www.decom.ufop.br/imobilis/ 
*UFOP http://www.ufop.br/ UFOP/ICEA http://www.icea.ufop.br/
*
*License
*Feel FREE to use this code as you want to. Just remember to give the correct credits.
*/

#include <SPI.h>      // RC522 Module uses SPI protocol
#include <MFRC522.h>   // Library for Mifare RC522 Devices
#include <Ethernet.h>
#include <aJSON.h>

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
#define buzzer 2 // Button pin for WipeMode

#define CHECK_ALL 0
#define CREATE_ONE 1
#define CHECK_ONE 2
#define CHECK_MASTER 3
#define CHECK_ONE_ASSOC 4
#define CREATE_MASTER 5

boolean programMode = false; // initialize programming mode to false

int successRead; // Variable integer to keep if we have Successful Read from Reader

byte readCard[4];// Stores scanned ID read from RFID Module
char cardUID[10];// Stores scanned ID read from RFID Module in text mode

/* We need to define MFRC522's pins and create instance
 * Pin layout should be as follows (on Arduino Uno):
 * MOSI   : Pin 11 / ICSP-4
 * MISO   : Pin 12 / ICSP-1
 * SCK    : Pin 13 / ICSP-3
 * SDA/SS : Pin 10 (Configurable)
 * RST    : Pin 9 (Configurable)
 * look MFRC522 Library for
 * pin configuration for other Arduinos.
 */

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.

byte mac[] = {0x98, 0x4F, 0xEE, 0x01, 0x10, 0xE2 };
char server[] = "192.168.2.31";
IPAddress ip(192,168,2,177);

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
  pinMode(buzzer, OUTPUT);
  digitalWrite(relay, LOW); // Make sure door is locked
  digitalWrite(redLed, LED_OFF); // Make sure led is off
  digitalWrite(greenLed, LED_OFF); // Make sure led is off
  digitalWrite(blueLed, LED_OFF); // Make sure led is off
  
  //Protocol Configuration
  Serial.begin(9600);    // Initialize serial communications with PC
  SPI.begin();           // MFRC522 Hardware uses SPI protocol
  mfrc522.PCD_Init();    // Initialize MFRC522 Hardware
  mfrc522.PCD_SetAntennaGain(mfroc522.RxGain_max); //Set Antenna Gain to Max- this will increase reading distance

  Ethernet.begin(mac,ip); // Connect the server

  Serial.print("IP Address        : ");
  Serial.println(Ethernet.localIP());
  Serial.print("Subnet Mask       : ");
  Serial.println(Ethernet.subnetMask());
  Serial.print("Default Gateway IP: ");
  Serial.println(Ethernet.gatewayIP());
  Serial.print("DNS Server IP     : ");
  Serial.println(Ethernet.dnsServerIP());
  Serial.println("");
  // give the Ethernet shield a second to initialize:
  delay(1000);
  
  responseInit();
  
  if (query(CHECK_ALL, "")) {  // Look DB if Master Card defined
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
    responseSuccess();
    //Next line convert byte tag ID to char tag ID
    sprintf(cardUID, "%02X%02X%02X%02X", readCard[0], readCard[1], readCard[2], readCard[3]);
    query(CREATE_ONE, cardUID); // Create tag in database
    query(CREATE_MASTER, cardUID); // Set first user and first tag as master
    Serial.println("Master Card Defined"); 
  }
  Serial.println("##### RFID Door Acces Control v2.0.8 #####"); //For debug purposes
  Serial.println("");
  Serial.println("Waiting PICCs to bo scanned :)");
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
    cardReaded();
    if ( isMaster(readCard) ) {  //If master card scanned again exit program mode
      Serial.println("This is Master Card"); 
      Serial.println("Exiting Program Mode");
      Serial.println("-----------------------------");
      responseSuccess();
      programMode = false;
      return;
    }
    else {  
      if ( findID(readCard, CHECK_ONE) ) { //If scanned card is known, do nothing
        responseFail();
        Serial.println("I know this PICC, so do nothing");
        Serial.println("-----------------------------");
      }
      else {                    // If scanned card is not known add it
        Serial.println("I do not know this PICC, adding...");
        writeID(readCard);
        responseSuccess();
        Serial.println("-----------------------------");
      }
    }
  }
  else {
    cardReaded();
    if ( isMaster(readCard) ) {  // If scanned card's ID matches Master Card's ID enter program mode
      programMode = true;
      responseSuccess();
      Serial.println("Hello");
      Serial.println("Scan a PICC to ADD");
      Serial.println("-----------------------------");
    }
    else {
      if ( findID(readCard, CHECK_ONE_ASSOC) ) { // If not, see if the card is in the database 
        Serial.println("Welcome, You shall pass");
        responseSuccess();
        openDoor(500);// Open the door lock for 300 ms
      }
      else {// If not, show that the ID was not valid
        Serial.println("You shall not pass");
        responseFail();
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

//////////////////////////////////////// Normal Mode Led  ///////////////////////////////////
void normalModeOn () {
  digitalWrite(blueLed, LED_ON); // Blue LED ON and ready to read card
  digitalWrite(redLed, LED_OFF); // Make sure Red LED is off
  digitalWrite(greenLed, LED_OFF); // Make sure Green LED is off
  digitalWrite(relay, LOW); // Make sure Door is Locked
}

///////////////////////////////////////// Add ID to database   ///////////////////////////////////
boolean writeID( byte a[] ) {
  sprintf(cardUID, "%02X%02X%02X%02X", a[0], a[1], a[2], a[3]);
  if(query(CREATE_ONE, cardUID)){
      return true;
  }
  return false;
}

///////////////////////////////////////// Find ID on database   ///////////////////////////////////
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
  digitalWrite(relay, HIGH); // Unlock door!
  delay(setDelay); // Hold door lock open for given seconds
  digitalWrite(relay, LOW); // Relock door
  delay(2000); // Hold green LED on for 2 more seconds
  digitalWrite(greenLed, LED_OFF);
  digitalWrite(blueLed, LED_ON);
}

String requestServer(int code, char uid[]) {

  Serial.println("conectando...");
  delay(1000);

  // Iniciando conexao com o servidor 
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.print("GET /nfc/operations.php?cod=");
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

void cardReaded() {
  digitalWrite(blueLed, LED_ON);
  delay(200);
  digitalWrite(blueLed, LED_OFF);
  tone(buzzer,500);
  delay(200);
  digitalWrite(blueLed, LED_ON);
  tone(buzzer,1500);
  delay(200);
  noTone(buzzer);
}

void responseInit() {
  digitalWrite(redLed, LED_OFF); // Make sure red LED is off
  digitalWrite(greenLed, LED_ON); // Make sure green LED is on
  digitalWrite(blueLed, LED_OFF); // Make sure blue LED is off
  tone(buzzer,500);   
  delay(200);
  noTone(buzzer);
  delay(200);
  digitalWrite(redLed, LED_OFF); // Make sure red LED is off
  digitalWrite(greenLed, LED_OFF); // Make sure green LED is off
  digitalWrite(blueLed, LED_ON); // Make sure blue LED is on
  tone(buzzer,1000);   
  delay(200);
  noTone(buzzer);
  delay(200);
  tone(buzzer,1500);   
  delay(200);
  digitalWrite(redLed, LED_ON); // Make sure red LED is on
  digitalWrite(greenLed, LED_OFF); // Make sure green LED is off
  digitalWrite(blueLed, LED_OFF); // Make sure blue LED is off
  tone(buzzer,2000);   
  delay(200);
  tone(buzzer,500);   
  delay(200);
  noTone(buzzer);
  digitalWrite(redLed, LED_OFF);
}

void responseFail() {
  digitalWrite(redLed, LED_ON); // Make sure red LED is on
  digitalWrite(greenLed, LED_OFF); // Make sure green LED is off
  digitalWrite(blueLed, LED_OFF); // Make sure blue LED is off
  tone(buzzer,500);   
  delay(1500);
  noTone(buzzer);
  digitalWrite(redLed, LED_OFF); // Make sure red LED is off
  digitalWrite(greenLed, LED_OFF); // Make sure green LED is off
  digitalWrite(blueLed, LED_ON); // Make sure blue LED is on
}

void responseSuccess() {
  digitalWrite(redLed, LED_OFF);
  digitalWrite(greenLed, LED_ON);
  digitalWrite(blueLed, LED_OFF);
  tone(buzzer,1500);   
  delay(200);
  noTone(buzzer);
  delay(200);
  tone(buzzer,1500);   
  delay(200);
  noTone(buzzer);
  digitalWrite(greenLed, LED_OFF);
}
