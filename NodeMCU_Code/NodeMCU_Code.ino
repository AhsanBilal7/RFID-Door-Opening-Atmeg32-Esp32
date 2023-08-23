//ESP Code for Sending Email using Atmega16


/* Sending Email using Atmega16 and NodeMCU

 *  Circuit Digest(www.circuitdigest.com) */


#include <ESP8266WiFi.h>

const char* ssid = "xxxxxxxxx";         // Enter the SSID of your WiFi Network. *******************

const char* password = "xxxxxxxxxx";    // Enter the Password of your WiFi Network. ********************

char server[] = "mail.smtp2go.com";    // write SMTP server address ******************


WiFiClient Client;              //define wifi client as client


void setup() {

  delay(1000);

  Serial.begin(9600);         // set baudrate as 9600 similar to Atmega16

  Serial.println("");

  Serial.print("Connecting To: ");

  Serial.println(ssid);

  WiFi.begin(ssid, password);     // connect to WIFI


  while (WiFi.status() != WL_CONNECTED)

  {

    delay(500);

    Serial.print(".");

  }

  Serial.println("");

  Serial.println("WiFi Connected.");

  Serial.print("IP address: ");

  Serial.println(WiFi.localIP());


}


void loop() {

  char inChar = 0;          

  char inData[6] = "";        // data length of 6 characters

  String variable = "";

  String variable1 = "";

  int index1 = 0;

 

  if ( Serial.available() > 0 ) {                      // Read from Rx from atmega16

    while (Serial.available() > 0 && index1 < 6)     // read till 6th character

    {

      delay(100);

      inChar = Serial.read();      // start reading serilly and save to variable

      inData[index1] = inChar;

      index1++;

      inData[index1] = '\0';         // Add a null at the end

    }

    variable.toUpperCase();       // convert to uppercase

    for (byte  i = 0 ; i < 6 ; i++) {

      variable.concat(String(inData[i]));    // concat strings

    }

    Serial.print("Variable = "); Serial.println(variable);  // debug and print incoming data

    delay(20);

  }

  String  string = String(variable);                          // string used to compare

  

   if (string == "SEND") {                      // if received data is "SEND" then send email


    sendEmail();                              // send email by calling function

    Serial.print("Mail sent to:"); Serial.println(" The recipient");        // debug if sent

    Serial.println("");


  }

}


byte sendEmail()

{

  if (Client.connect(server, 2525) == 1)        // connect to smtp server with port address 2525

  {

    Serial.println(F("connected to server"));

  } 

  else 

  {

    Serial.println(F("connection failed"));

    return 0;

  }

  if (!emailResp())         // if connection failed return now

    return 0;

  //

  Serial.println(F("Sending EHLO"));

  Client.println("EHLO www.example.com");      // Send command EHLO previosly it was HELO********************

  if (!emailResp()) 

    return 0;

    

  Serial.println(F("Sending auth login"));

  Client.println("AUTH LOGIN");

  if (!emailResp()) 

    return 0;

  //  

  Serial.println(F("Sending User"));

  // Change this to your base64, ASCII encoded SMTP username.

  //For example, the email address dummy@gmail.com encoded as djfdBDBEDEJD545616vfbSJHB=

 

  Client.println("Y2lyY3VpdGRxxxxxxxxxxxxxdtYWlsLmNvbQ=="); //base64, ASCII encoded SMTP Username    ********************

  if (!emailResp()) 

    return 0;


  Serial.println(F("Sending Password"));

  // change to your base64, ASCII encoded SMTP password

 // For example, the the password "password" encoded as IBjbjHUInOUi4654==

 

  Client.println("Y2lyY3VpdxxxxxxzdA==");   //base64, ASCII encoded SMTP Password               ********************

  

  if (!emailResp()) 

    return 0;

  //

  Serial.println(F("Sending From"));

  // change to sender email address

  Client.println(F("MAIL From: dummy@gmail.com"));       //  ********************

  if (!emailResp())  

    return 0;

  // change to recipient address

  Serial.println(F("Sending To"));

  Client.println(F("RCPT To: test@gmail.com"));    // ********************

  

  if (!emailResp()) 

    return 0;

  //

  Serial.println(F("Sending DATA"));

  Client.println(F("DATA"));

  if (!emailResp()) 

    return 0;

  Serial.println(F("Sending email"));

  // change to recipient address

  Client.println(F("To:  test@gmail.com"));                //  ********************

  // change to your address 

  Client.println(F("From: dummy@gmail.com"));                 //********************

  Client.println(F("Subject: ESP8266 test e-mail\r\n"));

  Client.println(F("This is is a test e-mail sent from ESP8266.\n"));

  Client.println(F("Second line of the test e-mail."));

  Client.println(F("Third line of the test e-mail."));

  //

  Client.println(F("."));

  if (!emailResp()) 

    return 0;

  //

  Serial.println(F("Sending QUIT"));

  Client.println(F("QUIT"));

  if (!emailResp()) 

    return 0;

  //

  Client.stop();

  Serial.println(F("disconnected"));

  return 1;

}


byte emailResp()

{

  byte responseCode;

  byte readByte;

  int loopCount = 0;


  while (!Client.available()) 

  {

    delay(1);

    loopCount++;

    // Wait for 20 seconds and if nothing is received, stop.

    if (loopCount > 20000) 

    {

      Client.stop();

      Serial.println(F("\r\nTimeout"));

      return 0;

    }

  }


  responseCode = Client.peek();

  while (Client.available())

  {

    readByte = Client.read();

    Serial.write(readByte);

  }


  if (responseCode >= '4')

  {

    //  efail();

    return 0;

  }

  return 1;

}
