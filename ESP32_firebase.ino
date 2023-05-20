#include <WiFi.h>
#include <FirebaseESP32.h>                    // Thư viện firebase cho ESP32

#define FIREBASE_HOST "lab2-3642c-default-rtdb.firebaseio.com"     // link google firebse host mà esp đọc dữ liệu vào 
#define FIREBASE_Authorization_key "apro8kEycmYZuEiQ7VGEsu9ew5NhrkxgAc5ZArLm"   // Khóa ủy quyền của host firebase

#define WIFI_SSID "ANH KIET" // Tên wifi mà esp32 kết nối
#define WIFI_PASSWORD "Kiet@2022"  // Mật khẩu wifi

FirebaseData fbdo;             //  Khởi tại biến đọc giá trị cho firebase
#define Pinanalog 32         // xác định chân 32  là chân đọc analog
#define Pindigital 4        // xác định chân 4  là chân đọc digital


void setup(){
  Serial.begin(115200);
  pinMode(Pindigital, INPUT);// thiết lập chân 4 là chân input 
  pinMode(Pinanalog, INPUT);// thiết lập chân 32 là chân input 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST,FIREBASE_Authorization_key);   //Kết nối ESP32 với google firebase                                                                

}

void loop() {
 int MQ2digi = digitalRead(Pindigital); // khởi tạo biến đọc giá trị digital
 int MQ2ana = analogRead(Pinanalog); // khởi tạo biến đọc giá trị analog
//  int MQ2digi = random(1,1); // khởi tạo biến đọc giá trị digital
//  int MQ2ana = random(1,100);(Pinanalog); // khởi tạo biến đọc giá trị analog
  Serial.print(" Output digital sensor = ");
  Serial.println(MQ2digi);        
  Serial.print(" Output analog sensor = ");
  Serial.println(MQ2ana);  
 
  Firebase.setFloat(fbdo, "/Output Digital", MQ2digi);   
  Firebase.setFloat(fbdo, "/Output Analog",  MQ2ana);   

    if( MQ2digi==1){
      // Bắt đầu đọc dữ liệu lên firebase
  
    Firebase.setString(fbdo, "/MQ2", "No gas");
  } else {
    Firebase.setString(fbdo, "/MQ2", "Gas");
  }
  
  
  delay(1000);
}
