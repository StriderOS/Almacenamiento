String server = "";
 String ip = "192.168.8.2";
 String id_bd = "";

 const char *ssid = "HOME78";
 const char *password = "HOME789710";

 //Librerias necesarias
 
 #include <ArduinoJson.h>
 #include <ESP8266WiFi.h>
 #include <ESP8266HTTPClient.h>
 #include <WiFiClient.h>

//Definicion de puertos

#define D0   16 //GPIO16 - WAKE UP
#define D1   5  //GPIO5
#define D2   4  //GPIO4
#define D3   0  //GPIO0
#define D4   2  //GPIO2 - TXD1

#define D5   14 //GPIO14 - HSCLK
#define D6   12 //GPIO12 - HMISO
#define D7   13 //GPIO13 - HMOSI - RXD2
#define D8   15 //GPIO15 - HCS   - TXD2
#define RX   3  //GPIO3 - RXD0 
#define TX   1  //GPIO1 - TXD0

int switch_pin1 = D2; //Derecha
int switch_pin2 = D4; //Izquierda
String dato = "";

void setup() {
  Serial.begin(9600);
  pinMode(switch_pin1, INPUT);
  pinMode(switch_pin2, INPUT);

  //Conexión Wi-fi
  Serial.println("Wifi Conectado");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
  Serial.println(" ");
  Serial.println("WiFi Conectado");
  Serial.println("IP Address : ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED)
  {
    //Codigo del interruptor
    if((digitalRead(switch_pin1) == 1)&&(dato !="Derecha"))
    {
      Serial.println("Estado del switch Derecha");
      dato = "Derecha";
      post(dato);
    }
    if((digitalRead(switch_pin2) == 1)&&(dato != "Izquierda"))
    {
      Serial.println("Estado del switch Izquierda");
      dato = "Izquierda";
      post(dato);
    }
    delay(1000);
    //Codigo del interruptor
  }
}



void post(String est){
  Serial.println("Inicio Post");
  HTTPClient http;
  String json;
  //http://localhost:8080/PostDat
  server = "http://"+ip+":8080/PostDat/";

  StaticJsonDocument<256> doc;
  
  //Enviar datos
  
  doc["estado"] = est;
  serializeJson(doc, json);

  http.begin(server);
  http.addHeader("Content-Type", "application/json");
  http.POST(json);
  http.writeToStream(&Serial);
  http.end();
  Serial.println("\nTermino Post");
}
