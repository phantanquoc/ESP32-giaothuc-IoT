#include <WiFi.h>  // Thư viện WiFi 
#define WIFI_SSID "ANH KIET"// Tên Wifi esp kết nối
#define WIFI_PASSWORD "Kiet@2022"// Mật khẩu Wifi
#define THING_SPEAK_ADDRESS "api.thingspeak.com"  
String writeAPIKey="18YEFBGJHU3ZHYYA";// API key của Channel thingspeak 
unsigned long lastTime = 0;
unsigned long delayTime = 15000; // khoảng thời gian thiết lập để gửi dữ liệu 

#define Pindigital 32        // xác định chân 32 là chân nhận tín hiệu sensor
//Khởi tạo đối tượng thư viện client
WiFiClient client;
void setup()
{
  Serial.begin(115200);  
  Serial.println();
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); // Kết nối Wifi

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());    // Xuất ra địa chỉ IP mạng nếu kết nối thành công
  Serial.println();
  delay(1000);
}

void loop() {
    // thiết lập chu kỳ cập nhật dữ liệu 
  if ((millis() - lastTime) > delayTime) {   // milis() thời gian từ khi chạy chương trình
    HTTPGet();
    lastTime = millis();
  }
  
}
// Dùng phương thức http get  
void HTTPGet() {
 
  if (client.connect(THING_SPEAK_ADDRESS, 80)) { // Kiểm tra kết nối tới Thingspeak
      Serial.println("Server connected");
 int MQ2sensor = digitalRead(Pindigital); // khởi tạo biến đọc giá trị digital
//  int MQ2sensor = random(0,1000); // khởi tạo biến đọc giá trị digital
       Serial.println("Gas level:\t");
       Serial.println(MQ2sensor );
      delay(200); 
      // Dùng  HTTP GET request
      Serial.print("Requesting URL: ");
      // Tạo link  GET url 
      String getUrl = "/update?api_key=" + writeAPIKey + "&field1=" + String(MQ2sensor) ;
      Serial.println(getUrl);
     
      // Tạo một  HTTP request:
      client.println("GET " + getUrl + " HTTP/1.1");
      client.println("Host: api.thingspeak.com");
      client.println("Connection: close");
      client.println();
  }
// Thiết lập thời gian nhận lại request từ sever
  unsigned long timeout = millis(); 
  while (client.available() == 0) {
    if (millis() - timeout > 5000){
      Serial.println(">>> Client Timeout !");  
      client.stop(); return;
      }
  }
}
