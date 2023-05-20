#include <AdafruitIO.h> // tiến hành thêm thư viện AdafruitIO.h vào
#include <AdafruitIO_WiFi.h>  // Khai báo thư viện AdafruitIO_WiFi.h để kết nối đến server.

#define IO_USERNAME  "phantanquoc"
#define IO_KEY       "aio_vTNR68vg37uq7BisHSUgJ4ILeYNW"

#define WIFI_SSID "ANH KIET" // Tên wifi để ESP 32 kết nối vào và truy cập đến server.
#define WIFI_PASS "Kiet@2022"  // Pass wifi

#define LED_PIN 2 // LED on Board là GPIO 2.

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);  // Gọi hàm kết nối đến server.
AdafruitIO_Feed *digital = io.feed("digital"); // khai báo con trỏ digital
                                               //để chứ dữ liệu lấy từ feed của server.

void setup() {
  pinMode(LED_PIN, OUTPUT); // Khai báo output.
  pinMode(button, INPUT); //button ở chế độ input
  Serial.begin(115200); 
  while(! Serial);
 
  // kết nối tới io.adafruit.com
  Serial.print("Connecting to Adafruit IO"); 
  io.connect(); // Gọi hàm kết nối
 
  // chờ kết nối
  while(io.status() < AIO_CONNECTED) {
    Serial.print("."); // Nếu chưa kết nối được đến server sẽ tiến hành xuất ra màn hình đấu "."
    delay(500);
  }
 
  // sau khi đã kết nối thành công
  Serial.println();
  Serial.println(io.statusText()); // Xuất trạng thái ra màn hình.
  digital->get(); // lấy dữ liệu từ feed 'digital' của server.
  digital->onMessage(handleMessage); // Gọi hàm đọc dữ liệu và tiến hành điều khiển led và xuất
                                     //ra trạng thái trên màn hình.
}

void loop() {
  io.run(); // gọi hàm Run.
}

// hàm handleMessage để đọc dữ liệu.
void handleMessage(AdafruitIO_Data *data) {
 // xuất ra màn hình trạng thái của nút nhấn trên feed vừa đọc được.
  Serial.print("received <- ");
 
  if(data->toPinLevel() == HIGH)
    Serial.println("HIGH");
  else
    Serial.println("LOW");

 // cài đặt trạng thái bật tắt led on board tương ứng với nút nhấn.
  // write the current state to the led
  digitalWrite(LED_PIN, data->toPinLevel());
  

}
