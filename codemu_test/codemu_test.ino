#include <SoftwareSerial.h>

// Khai báo SoftwareSerial, chân RX của Arduino nối với TX của SIM và ngược lại
SoftwareSerial SIM(A2, A3); // Chân 7 là TX, chân 8 là RX

String SDT = "+84842966969"; // Số điện thoại người nhận (phải có mã quốc gia)

void setup() {
  Serial.begin(115200);       // Khởi tạo Serial Monitor
  SIM.begin(115200);          // Tốc độ giao tiếp với module SIM

  Serial.println("Kiểm tra kết nối với SIM...");

  // Kiểm tra kết nối với module SIM
  if (testATCommand()) {
    Serial.println("Module SIM sẵn sàng.");
    delay(200);
  } else {
    Serial.println("Không thể kết nối với module SIM.");
  }
}

void loop() {
  // Nếu có dữ liệu nhập từ Serial Monitor
  if (Serial.available()) {
    String message = Serial.readStringUntil('\n'); // Đọc tin nhắn từ Serial Monitor
    message.trim();  // Loại bỏ khoảng trắng thừa

    if (message.length() > 0) {
      // Gửi tin nhắn
      SendSMS(SDT, message);
    }
  }
}

// Hàm kiểm tra kết nối với module SIM
bool testATCommand() {
  SIM.println("AT"); // Gửi lệnh AT
  delay(1000);
  if (SIM.available()) {
    String response = SIM.readString();
    Serial.println("Phản hồi từ SIM: " + response);
    return response.indexOf("OK") != -1; // Kiểm tra phản hồi có chứa "OK" không
  }
  return false;
}

// Hàm gửi tin nhắn SMS
void SendSMS(String phoneNumber, String message) {
  Serial.println("Đang gửi tin nhắn...");

  // Gửi lệnh chuyển sang chế độ text
  SIM.println("AT+CMGF=1");
  delay(1000);
  if (SIM.available()) {
    Serial.println("Phản hồi CMGF: " + SIM.readString());
  }

  // Thiết lập số điện thoại nhận tin nhắn
  SIM.println("AT+CMGS=\"" + phoneNumber + "\"");
  delay(1000);
  if (SIM.available()) {
    Serial.println("Phản hồi CMGS: " + SIM.readString());
  }

  // Gửi nội dung tin nhắn
  SIM.print(message);
  delay(500);

  // Gửi Ctrl+Z để kết thúc tin nhắn
  SIM.write(26);  // ASCII 26 là Ctrl+Z
  delay(5000);

  // Kiểm tra phản hồi sau khi gửi tin nhắn
  if (SIM.available()) {
    Serial.println("Phản hồi gửi tin nhắn: " + SIM.readString());
  } else {
    Serial.println("Không nhận được phản hồi sau khi gửi tin nhắn.");
  }
}
