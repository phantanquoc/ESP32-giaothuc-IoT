// 3 dòng dưới là để lấy thông tin từ template của ta đã tạo trên BLYNK 
//và cho phép truy cập vào device để sử dụng 
#define BLYNK_TEMPLATE_ID "TMPLEmBBb3BJ"
#define BLYNK_DEVICE_NAME "temp"
#define BLYNK_AUTH_TOKEN "j4KPg8imC1B_vcH8eR7dXRXmXMGktlgl"

#define DHTTYPE DHT11           // Đặt mặc định của ic là DHT11

// Define button1_vpin là trạng thái của button trên app blynk và có PIN của nó là V1 được cài đặt trên web
#define button1_vpin V2
     
// Define humi giá trị độ ẩm trên app blynk và có PIN của nó là V2 được cài đặt trên web
#define humi V1

// Define temp giá trị nhiệt độ trên app blynk và có PIN của nó là V3 được cài đặt trên web
#define temp V0

#define relay1_pin 2          // define chân GPIO 23 để hiển thị led
#define DHTPIN 4               // Đặt chân 4 là chân lấy dữ liệu từ DHT11
#define BLYNK_PRINT Serial     // Khai báo hàm BLYNK_PRINT là Serial để tiết kiệm dung lượng

// Khai báo sử dụng thư viện BLYNK, WIFI để kết nối với mạng Internet và thư viện DHT để đọc dữ liệu từ sensor
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
WiFiClient client;
 
char auth[] = BLYNK_AUTH_TOKEN;                // Gán mã token của app blynk vào biến auth
char ssid[] = "ANH KIET";          // Khai báo tên wifi kết nối và gán vào biến ssid
char pass[] = "Kiet@2022";                      // Khai báo mật khẩu wifi và gán vào biến pass

BlynkTimer timer;
DHT dht(DHTPIN, DHTTYPE);      // Khai báo chân và kiểu DHT cho hàm dht để điều khiển 

int relay1_state = 0;          // Đặt biến relay1_state là trạng thái ban đầu của led và bằng 0

// Hàm này được gọi mỗi khi thiết bị được kết nối với Blynk.Cloud
// Yêu cầu trạng thái mới nhất từ ​​máy chủ
BLYNK_CONNECTED() {
  Blynk.syncVirtual(button1_vpin);
  Blynk.syncVirtual(humi);
  Blynk.syncVirtual(temp);
}

// Hàm này được gọi mỗi khi trạng thái Virtual Pin thay đổi
// Có nghĩa là khi ta nhấn chuyển trạng thái switch từ trên web hoặc app 
//thì sẽ gọi hàm write để cập nhật trạng thái trên mạch chính.
BLYNK_WRITE(button1_vpin) {
  relay1_state = param.asInt();
  digitalWrite(relay1_pin, relay1_state);
}

void setup()
{
  // Debug console
  dht.begin();
  Serial.begin(115200);
  // cài đặt các chân input và output của sensor và led
  pinMode(DHTPIN, INPUT);
  pinMode(relay1_pin, OUTPUT);
  //Trong quá trình khởi động thì led phải tắt nên ta dùng lệnh này để setup trạng thái tắt cho led
  digitalWrite(relay1_pin, LOW);
  Blynk.begin(auth, ssid, pass); // Chạy blynk với các thông tin ta đã cung cấp

}

void loop()
{
  // Chương trình chính ta chỉ cần khai báo cho blynk chạy thì esp của ta sẽ được kết nối với blynk.
  Blynk.run();
  timer.run();

//float t = random(0,20);
//float h = random(20,70);

  float h = dht.readHumidity();              // khởi tạo biến h nhận dữ liệu độ ẩm từ sensor DHT11
  float t = dht.readTemperature();           // Khởi tạo biến t nhận dữ liệu nhiệt độ từ sensor DHT11
              if (isnan(h) || isnan(t))      // Nếu Sensor không trả dữ liệu về thì in ra dòng Failed và chạy lại
                 {
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }
// Quá trình này lặp lại cho đến khi nào sensor nhận được dữ liệu thì sẽ in dữ liệu đó ra và gửi lên blynk.
  Serial.println(t);
  Serial.println(h); 
  Blynk.virtualWrite(humi, h);
  Blynk.virtualWrite(temp, t);

  delay(100);
}
