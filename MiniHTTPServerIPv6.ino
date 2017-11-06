
#include <EtherSia.h>

/** W5100 Ethernet Interface */
EtherSia_W5100 ether;

/** Define HTTP server */
HTTPServer http(ether);

int pin = 8;
int pin2 = 9; 
boolean ligado = true;

void setup() {
  pinMode(pin, OUTPUT);
  pinMode(pin2, OUTPUT);
  digitalWrite(pin, HIGH);
  digitalWrite(pin2, HIGH);
    MACAddress macAddress("9e:b3:19:c7:1b:10");

    // Setup serial port
    Serial.begin(115200);
    Serial.println("[EtherSia MiniHTTPServer]");
    macAddress.println();

    // Start Ethernet
    if (ether.begin(macAddress) == false) {
        Serial.println("Failed to configure Ethernet");
    }

    Serial.print("Our link-local address is: ");
    ether.linkLocalAddress().println();
    Serial.print("Our global address is: ");
    ether.globalAddress().println();

    Serial.println("Ready.");
}

void loop() {
    ether.receivePacket();

    if (http.isGet(F("/"))) {
        http.printHeaders(http.typeHtml);
        http.println(F("<h1>Ola, esta e minha aplicacao de teste do arduino com IPv6</h1>"));
        http.sendReply();

    } else if (http.isGet(F("/on"))) {
        http.printHeaders(http.typeHtml);
        http.println(F("<h2>APP de teste arduino com IPv6</h2>"));
        http.println(F("Status Luz: <h1>ligado</h1>"));
        http.sendReply();
        {
            digitalWrite(pin, LOW);    // set pin 8 high
            Serial.println("On");
            //ligado = false;
          }

    } else if (http.isGet(F("/off"))) {
        http.printHeaders(http.typeHtml);
        http.println(F("<h2>APP de teste arduino com IPv6 </h2>"));
        http.println(F("Status Luz: <h1>desligado</h1>"));
        http.sendReply();
        {
            digitalWrite(pin, HIGH);    // set pin 8 low
            Serial.println("Off");
            //ligado = true;
          }

    } else if (http.isGet(F("/on2"))) {
        http.printHeaders(http.typeHtml);
        http.println(F("<h2>APP de teste arduino com IPv6</h2>"));
        http.println(F("Status liquidificador: <h1>ligado</h1>"));
        http.sendReply();
        {
            digitalWrite(pin2, LOW);    // set pin 9 high
            Serial.println("On2");
            //ligado = false;
          }

    } else if (http.isGet(F("/off2"))) {
        http.printHeaders(http.typeHtml);
        http.println(F("<h2>APP de teste arduino com IPv6 </h2>"));
        http.println(F("Status liquidificador: <h1>desligado</h1>"));
        http.sendReply();
        {
            digitalWrite(pin2, HIGH);    // set pin 9 low
            Serial.println("Off2");
            //ligado = true;
          }

    

    } else if (http.havePacket()) {
        // Some other HTTP request, return 404
        http.notFound();

    } else {
        // Some other packet, reply with rejection
        ether.rejectPacket();

    }
}
