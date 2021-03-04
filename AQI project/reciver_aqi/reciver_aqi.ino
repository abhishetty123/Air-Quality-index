/*
   Boady can write multiple times in Html
   aswll as style aslo..
   can refresh the webpage
   can import the rectangule
*///--------------Electronics-project-hub-------------//
#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
const char ssid[] = "Your_Wifi_Name";  // your network SSID (name)
const char pass[] = "password";   // your network password
WiFiClient  client;
// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

//---------Channel Details---------//
unsigned long counterChannelNumber = ******;            // Channel ID
const char * myCounterReadAPIKey = " ********** ;   // Read API Key

unsigned long counterChannelNumber1 = ********;            // Channel ID
const char * myCounterReadAPIKey1 = " ******** ";   // Read API Key


const int FieldNumber1 = 1;  // The field you wish to read
const int FieldNumber2 = 2;  // The field you wish to read
const int FieldNumber3 = 3;  // The field you wish to read
const int FieldNumber11 = 1;  // The field you wish to read

//-------------------------------//

void setup()
{

  Serial.begin(115200);
  //----------------- Network -----------------//
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Connecting to ");
    Serial.print(ssid);
    Serial.println(" ....");
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);
      delay(5000);
    }
    Serial.println("Connected to Wi-Fi Succesfully.");
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

  }
  //--------- End of Network connection--------//

  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  server.begin();
}

void loop()
{
  //---------------- Channel 1 ----------------//
  long temp = ThingSpeak.readLongField(counterChannelNumber, FieldNumber1, myCounterReadAPIKey);
  long humidity = ThingSpeak.readLongField(counterChannelNumber, FieldNumber2, myCounterReadAPIKey);
  long park = ThingSpeak.readLongField(counterChannelNumber, FieldNumber3, myCounterReadAPIKey); //canteen
  long canteen = ThingSpeak.readLongField(counterChannelNumber1, FieldNumber11, myCounterReadAPIKey1);

  int statusCode = ThingSpeak.getLastReadStatus();
  if (statusCode == 200)
  {
    Serial.print("Temperature: ");
    Serial.println(temp);
    Serial.print("Humidity: ");
    Serial.println(humidity);
    Serial.print("parking: ");
    Serial.println(park);
    Serial.print("canteen: ");
    Serial.println(canteen);

  }
  else
  {
    Serial.println("Unable to read channel / No internet connection");
  }
  delay(10000);
  //-------------- End of Channel 1 -------------//

  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client

    while (client.connected()) { // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta http-equiv=\"refresh\" content=\"10\">");//<meta http-equiv="refresh" content="1">
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons

            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<title>Sahyadri AQI</title><style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}</style>");
            client.println("<style>.dot {height: 50px;width: 50px;background-color: #E5FABF;border-radius: 50%;display: inline-block;}");


            client.print(".rcorners4 {border-radius: 15px ;background: #4464F7;padding: 20px; width: 100px;height: 100px;}");
            client.print(".rcorners5 {border-radius: 15px ;background: #FCB214;padding: 20px; width: 100px;height: 100px;}");
            client.print(".p3 {font-family: \"Lucida Console\", \"Courier New\", monospace;color : white;}");
            client.print(".p2 {font-family: \"Lucida Handwriting\", \"Courier New\", monospace;color : white;}</style>");


            client.println("<style>table {border-collapse:separate;border:solid black 1px;border-radius:6px;-moz-border-radius:6px;} body{background-image:linear-gradient(#191473,#82CBF9);}");
            client.print(".rcorners3 {border-radius: 15px ;background: #109908;padding: 20px; width: 100px;height: 100px;}");
            client.print(".rcorners1 {border-radius: 15px ;background: #109908;padding: 20px; width: 100px;height: 100px;}");
            client.print(".statuscolor {color:#F0F767;}");
            client.print(".statuscolor1 {color:#F0F767;}");

            if ((canteen > 550) || (canteen < 50)) {
              client.print(".rcorners3 {border-radius: 15px ;background: #FC3414;padding: 20px; width: 100px;height: 100px;}");
              client.print(".statuscolor {color:#96FBEA;}");
            }
            if ((park > 550) || (park < 50)) {
              client.print(".rcorners1 {border-radius: 15px ;background: #FC3414;padding: 20px; width: 100px;height: 100px;}");
              client.print(".statuscolor1 {color:#96FBEA;}");
            }

            client.print("</style></head>");


            // Web Page Heading
            client.println("<body ><h1><p class=\"p2\"><i>College Campus AQI</i></p></h1><hr>");
            //bgcolor=\"#97B365\"

            client.println("<center><span class=\"p3\"><b> Air Quality Index </span><table border=0 height=150 bgcolor=\"#F3F57A\" width =450><tr><td>");
            client.print("<center><br><p class = \"rcorners1\"><span class=\"p3\"><b>Parking Area</span><br><br>");
            //            client.print("<span class = \"dot\"><br><br><br>");
            client.print("PPM:");
            client.println(park);
            client.println("<br><br>");
            if ((park > 400) && (park < 600)) {
              client.print("<span class=\"statuscolor1\">Good</span>");
            }
            if ((park < 400) && (park > 50)) {
              client.print("<span class=\"statuscolor1\">Very Good</span>");
            }
            if ((park > 600) && (park < 1000)) {
              client.print("<span class=\"statuscolor1\">Critical</span>");
            }
            if ((park > 1000) || (park < 50)) {
              client.print("<span class=\"statuscolor1\">Sensor Fault</span>");

            }
            client.print("</p></center> &nbsp; &nbsp; &nbsp; &nbsp;");
            client.print("</td><td>");
            client.print("<center><p class = \"rcorners3\"><span class=\"p3\"><b>Canteen Area</span><br><br>");
            client.print("PPM:");
            client.print(canteen);
            client.print("<br><br>");
            if ((canteen > 400) && (canteen < 600)) {
              client.print("<span class=\"statuscolor\">Good</span>");
            }
            if ((canteen < 400) && (canteen > 50)) {
              client.print("<span class=\"statuscolor\">Very Good</span>");
            }
            if ((canteen > 600) && (canteen < 1000)) {
              client.print("<span class=\"statuscolor\">Critical</span>");
            }
            if ((canteen > 1000) || (canteen < 50)) {
              client.print("<span class=\"statuscolor\">Sensor Fault</span>");
            }
            client.print("</center></td></tr></table><br><span class=\"p3\"><b> Weather Detail </span><table border=0 height=150 bgcolor=\"#F3F57A \"width =450><tr><td>");

            client.print("<center><p class = \"rcorners5\"><span class=\"p3\"><b>Temperature</span><br><br><br>");
            //            client.print("<span class = \"dot\"><br><br><br>");
            client.print("<span class = \"dot\"><br>");
            client.print("<b><i>");
            client.print(temp);
            client.print("*C</i> </b>");
            client.print("</span></p></center>");
            client.print("</td><td>");
            client.print("<center><p class = \"rcorners4\"><span class=\"p3\"><b>Humidity</span><br><br><br>");
            client.print("<span class = \"dot\"><br>");
            client.print("<b><i>");
            client.print(humidity);
            client.print("%</i> </b>");
            client.print("</span></p></center></td></tr></table></center>");
            client.println(" <br> <marquee> 2020.Sahyadri Campus, Mangalore</marquee><br><br><br><br><br><br><br><br></body></html>");


            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
