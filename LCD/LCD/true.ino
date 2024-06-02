
// #include <SoftwareSerial.h>
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>

// SoftwareSerial esp8266(2, 3); // RX, TX
// LiquidCrystal_I2C lcd(0x27, 16, 2);

// const char* ssid = "DESKTOP-Junho";
// const char* password = "12345678";
// const char* serverIp = "192.168.137.32"; // 실제 안드로이드 장치의 IP 주소
// const int serverPort = 8080;

// void setup() {
//   // LCD 초기화
//   lcd.begin(16, 2);
//   lcd.backlight();
//   lcd.setCursor(0, 0);
//   lcd.print("Connecting...");

//   // 시리얼 모니터와 ESP8266 초기화
//   Serial.begin(9600);
//   esp8266.begin(9600);

//   // WiFi 연결
//   connectToWiFi();
// }

// void connectToWiFi() {
//   sendCommand("AT+RST", 5000, "OK");
//   sendCommand("AT+CWMODE=1", 1000, "OK");

//   String connectCommand = "AT+CWJAP=\"" + String(ssid) + "\",\"" + String(password) + "\"";
//   Serial.println("Sending WiFi Connect Command: " + connectCommand);
  
//   if (sendCommand(connectCommand, 15000, "OK")) {
//     lcd.clear();
//     lcd.setCursor(0, 0);
//     lcd.print("WiFi Connected");
//     Serial.println("WiFi Connected");

//     // HTTP 요청 보내기
//     sendHttpRequest();
//   } else {
//     lcd.clear();
//     lcd.setCursor(0, 0);
//     lcd.print("WiFi Connect Fail");
//     Serial.println("WiFi Connect Fail");
//   }
// }

// void sendHttpRequest() {
//   if (sendCommand("AT+CIPSTART=\"TCP\",\"" + String(serverIp) + "\"," + String(serverPort), 10000, "OK")) {
//     String httpRequest = "GET /?message=hello%20java HTTP/1.1\r\nHost: " + String(serverIp) + "\r\nConnection: close\r\n\r\n";
//     if (sendCommand("AT+CIPSEND=" + String(httpRequest.length()), 1000, ">")) {
//       esp8266.print(httpRequest);

//       delay(5000);

//       // 데이터 수신을 위한 개선된 코드
//       String response = "";
//       long timeout = millis() + 10000;  // 5초 타임아웃
//       while (millis() < timeout) {
//         while (esp8266.available()) {
//           char c = esp8266.read();
//           response += c;
//         }
//       }

//       if (response.length() > 0) {
//         Serial.println("server " + response);
//         lcd.clear();
//         lcd.setCursor(0, 0);
//         lcd.print("Response:");
//         lcd.setCursor(0, 1);
//         lcd.print(response.substring(0, 16)); // LCD는 16x2이므로 첫 16자만 표시
//       } else {
//         lcd.clear();
//         lcd.setCursor(0, 0);
//         lcd.print("HTTP Error");
//       }

// //       if (esp8266.available()) 
// //       {
// //           Serial.println("HERE1");
// //         String response = esp8266.readString();
// //         Serial.println("server : " + response);
// //         lcd.clear();
// //         lcd.setCursor(0, 0);
// //         lcd.print("Response:");
// //         lcd.setCursor(0, 1);
// //         lcd.print(response.substring(0, 16)); // LCD는 16x2이므로 첫 16자만 표시
// // \
// //       } else {
// //           Serial.println("HERE2");
// //         lcd.clear();
// //         lcd.setCursor(0, 0);
// //         lcd.print("HTTP Error");
// //       }

//       // 연결이 열려 있는지 확인하고 닫기
//       if (sendCommand("AT+CIPCLOSE", 1000, "OK") || sendCommand("AT+CIPCLOSE", 1000, "ERROR")) {
//         Serial.println("Connection closed");
//       } else {
//         Serial.println("Failed to close connection");
//       }
//     } else {
//       lcd.clear();
//       lcd.setCursor(0, 0);
//       lcd.print("CIPSEND Error");
//     }
//   } else {
//     lcd.clear();
//     lcd.setCursor(0, 0);
//     lcd.print("CIPSTART Error");
//   }
// }

// bool sendCommand(String command, int timeout, String expectedResponse) {
//   String response = "";
//   esp8266.println(command);
//   long int time = millis();
//   while ((time + timeout) > millis()) {
//     while (esp8266.available()) {
//       char c = esp8266.read();
//       response += c;
//     }
//     if (response.indexOf(expectedResponse) != -1) {
//       Serial.println(response);
//       return true;
//     }
//   }
//   Serial.println(response);
//   return false;
// }

// void loop() {
//   // 반복할 필요가 없기 때문에 아무 코드도 넣지 않습니다.
// }





// #include <SoftwareSerial.h>
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>

// SoftwareSerial esp8266(2, 3); // RX, TX
// LiquidCrystal_I2C lcd(0x27, 16, 2);

// const char* ssid = "DESKTOP-Junho";
// const char* password = "12345678";
// const char* serverIp = "192.168.137.32"; // 실제 안드로이드 장치의 IP 주소
// const int serverPort = 8080;

// void setup() {
//   // LCD 초기화
//   lcd.begin(16, 2);
//   lcd.backlight();
//   lcd.setCursor(0, 0);
//   lcd.print("Connecting...");

//   // 시리얼 모니터와 ESP8266 초기화
//   Serial.begin(9600);
//   esp8266.begin(9600);

//   // WiFi 연결
//   connectToWiFi();
// }

// void connectToWiFi() {
//   sendCommand("AT+RST", 5000, "OK");
//   sendCommand("AT+CWMODE=1", 1000, "OK");

//   String connectCommand = "AT+CWJAP=\"" + String(ssid) + "\",\"" + String(password) + "\"";
//   Serial.println("Sending WiFi Connect Command: " + connectCommand);
  
//   if (sendCommand(connectCommand, 15000, "OK")) {
//     lcd.clear();
//     lcd.setCursor(0, 0);
//     lcd.print("WiFi Connected");
//     Serial.println("WiFi Connected");

//     // HTTP 요청 보내기
//     sendHttpRequest();
//   } else {
//     lcd.clear();
//     lcd.setCursor(0, 0);
//     lcd.print("WiFi Connect Fail");
//     Serial.println("WiFi Connect Fail");
//   }
// }

// void sendHttpRequest() {
//   if (sendCommand("AT+CIPSTART=\"TCP\",\"" + String(serverIp) + "\"," + String(serverPort), 10000, "OK")) {
//     String httpRequest = "GET /?message=hello%20java HTTP/1.1\r\nHost: " + String(serverIp) + "\r\n\r\n";
//     // String httpRequest = "GET /?message=hello%20java HTTP/1.1\r\nHost: " + String(serverIp) + "\r\nConnection: close\r\n\r\n";
//     if (sendCommand("AT+CIPSEND=" + String(httpRequest.length()), 1000, ">")) {
//       esp8266.print(httpRequest);

//       delay(5000);

//       // 데이터 수신을 위한 개선된 코드
//       String response = "";
//       long timeout = millis() + 10000;  // 10초 타임아웃
//       while (millis() < timeout) {
//         while (esp8266.available()) {
//           char c = esp8266.read();
//           response += c;
//           timeout = millis() + 500;  // 데이터가 수신될 때마다 타임아웃 갱신
//         }
//       }

//       if (response.length() > 0) {
//  // 특정한 문자열로 끝나는 경우 검사하여 "Connection: close\r\n\r\n"을 붙여줌
//         // if (response.startsWith("GET /?message=hello%20java HTTP/1.1") && response.indexOf("Host: ") != -1 && response.endsWith("Connec")) {
//         //   response += "tion: close\r\n\r\n";
//         // }
//         // if (!response.endsWith("Connection: close\r\n\r\n")) {
//         //   response += "Connection: close\r\n\r\n";
//         // }

//         Serial.println("server: " + response);
//         lcd.clear();
//         lcd.setCursor(0, 0);
//         lcd.print("Response:");
//         lcd.setCursor(0, 1);
//         lcd.print(response.substring(0, 16)); // LCD는 16x2이므로 첫 16자만 표시
//       } else {
//         lcd.clear();
//         lcd.setCursor(0, 0);
//         lcd.print("HTTP Error");
//       }

//       // // 연결이 열려 있는지 확인하고 닫기
//       // if (sendCommand("AT+CIPCLOSE", 1000, "OK") || sendCommand("AT+CIPCLOSE", 1000, "ERROR")) {
//       //   Serial.println("Connection closed");
//       // } else {
//       //   Serial.println("Failed to close connection");
//       // }
//             // 연결이 열려 있는지 확인하고 닫기
//       // if (sendCommand("AT+CIPCLOSE", 1000, "OK")) {
//       //   Serial.println("Connection closed");
//       // } else 
//       // {
//       //   Serial.println("First AT+CIPCLOSE failed, retrying...");
//       //   if (sendCommand("AT+CIPCLOSE", 1000, "OK") || sendCommand("AT+CIPCLOSE", 1000, "ERROR12")) {
//       //     Serial.println("Connection closed after retry");
//       //   } else {
//       //     Serial.println("Failed to close connection after retry");
//       //   }
//       // }
//     } else {
//       lcd.clear();
//       lcd.setCursor(0, 0);
//       lcd.print("CIPSEND Error");
//     }
//   } else {
//     lcd.clear();
//     lcd.setCursor(0, 0);
//     lcd.print("CIPSTART Error");
//   }
// }

// bool sendCommand(String command, int timeout, String expectedResponse) {
//   String response = "";
//   esp8266.println(command);
//   long int time = millis();
//   while ((time + timeout) > millis()) {
//     while (esp8266.available()) {
//       char c = esp8266.read();
//       response += c;
//     }
//     if (response.indexOf(expectedResponse) != -1) {
//       Serial.println(response);
//       return true;
//     }
//   }
//   Serial.println(response);
//   return false;
// }

// void loop() {
//   // 반복할 필요가 없기 때문에 아무 코드도 넣지 않습니다.
// }


// #include <SoftwareSerial.h>
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>

// SoftwareSerial esp8266(2, 3); // RX, TX
// LiquidCrystal_I2C lcd(0x27, 16, 2);

// const char* ssid = "DESKTOP-Junho";
// const char* password = "12345678";
// const char* serverIp = "192.168.137.32"; // 실제 안드로이드 장치의 IP 주소
// const int serverPort = 8080;

// String clientIp = "";
// String response = "";
// void setup() {
//   // LCD 초기화
//   lcd.begin(16, 2);
//   lcd.backlight();
//   lcd.setCursor(0, 0);
//   lcd.print("Connecting...");

//   // 시리얼 모니터와 ESP8266 초기화
//   Serial.begin(9600);
//   esp8266.begin(9600);

//   // WiFi 연결
//   connectToWiFi();
//   // 클라이언트 IP 주소 얻기
//   getClientIp();
// }

// void connectToWiFi() {
//   sendCommand("AT+RST", 5000, "OK");
//   sendCommand("AT+CWMODE=1", 1000, "OK");

//   String connectCommand = "AT+CWJAP=\"" + String(ssid) + "\",\"" + String(password) + "\"";
//   Serial.println("Sending WiFi Connect Command: " + connectCommand);
  
//   if (sendCommand(connectCommand, 15000, "OK")) {
//     lcd.clear();
//     lcd.setCursor(0, 0);
//     lcd.print("WiFi Connected");
//     Serial.println("WiFi Connected");

//     // HTTP 요청 보내기
//     sendHttpRequest();
//   } else {
//     lcd.clear();
//     lcd.setCursor(0, 0);
//     lcd.print("WiFi Connect Fail");
//     Serial.println("WiFi Connect Fail");
//   }
// }

// void getClientIp() {
//   if (sendCommand("AT+CIFSR", 1000, ".")) { // 성공적으로 IP 주소를 받아오면
//     int index = response.indexOf("STAIP,\"") + 7;
//     clientIp = response.substring(index, response.indexOf("\"", index));
//     Serial.println("Client IP: " + clientIp);
//   } else {
//     Serial.println("Failed to get IP");
//   }
// }

// void sendHttpRequest() {
//   if (sendCommand("AT+CIPSTART=\"TCP\",\"" + String(serverIp) + "\"," + String(serverPort), 10000, "OK")) {
//     // 클라이언트 IP 주소를 포함한 HTTP 요청 생성
//     String httpRequest = "GET /?message=hello%20java HTTP/1.1\r\nHost: " + clientIp + "\r\nConnection: close\r\n\r\n";
//     if (sendCommand("AT+CIPSEND=" + String(httpRequest.length()), 1000, ">")) {
//       esp8266.print(httpRequest);

//       delay(5000);

//       // 데이터 수신을 위한 개선된 코드
//       String response = "";
//       long timeout = millis() + 10000;  // 10초 타임아웃
//       while (millis() < timeout) {
//         while (esp8266.available()) {
//           char c = esp8266.read();
//           response += c;
//           timeout = millis() + 500;  // 데이터가 수신될 때마다 타임아웃 갱신
//         }
//       }

//       if (response.length() > 0) {
//         Serial.println("server: " + response);
//         lcd.clear();
//         lcd.setCursor(0, 0);
//         lcd.print("Response:");
//         lcd.setCursor(0, 1);
//         lcd.print(response.substring(0, 16)); // LCD는 16x2이므로 첫 16자만 표시
//       } else {
//         lcd.clear();
//         lcd.setCursor(0, 0);
//         lcd.print("HTTP Error");
//       }

//       // AT+CIPCLOSE 명령을 생략하고 자동으로 연결이 닫히도록 함
//     } else {
//       lcd.clear();
//       lcd.setCursor(0, 0);
//       lcd.print("CIPSEND Error");
//     }
//   } else {
//     lcd.clear();
//     lcd.setCursor(0, 0);
//     lcd.print("CIPSTART Error");
//   }
// }

// bool sendCommand(String command, int timeout, String expectedResponse) {
//   response = "";  // response 변수를 전역으로 선언
//   esp8266.println(command);
//   long int time = millis();
//   while ((time + timeout) > millis()) {
//     while (esp8266.available()) {
//       char c = esp8266.read();
//       response += c;
//     }
//     if (response.indexOf(expectedResponse) != -1) {
//       Serial.println(response);
//       return true;
//     }
//   }
//   Serial.println(response);
//   return false;
// }

// void loop() {
//   // 반복할 필요가 없기 때문에 아무 코드도 넣지 않습니다.
// }






#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

SoftwareSerial esp8266(2, 3); // RX, TX
LiquidCrystal_I2C lcd(0x27, 16, 2);

const char* ssid = "DESKTOP-Junho";
const char* password = "12345678";
const char* serverIp = "192.168.137.32"; // 실제 안드로이드 장치의 IP 주소
const int serverPort = 8080;

void setup() {
  // LCD 초기화
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Connecting...");

  // 시리얼 모니터와 ESP8266 초기화
  Serial.begin(9600);
  esp8266.begin(9600);

  // WiFi 연결
  connectToWiFi();
}

void connectToWiFi() {
  sendCommand("AT+RST", 5000, "OK");
  sendCommand("AT+CWMODE=1", 1000, "OK");

  String connectCommand = "AT+CWJAP=\"" + String(ssid) + "\",\"" + String(password) + "\"";
  Serial.println("Sending WiFi Connect Command: " + connectCommand);
  
  if (sendCommand(connectCommand, 15000, "OK")) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WiFi Connected");
    Serial.println("WiFi Connected");

    // HTTP 요청 보내기
    sendHttpRequest();
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WiFi Connect Fail");
    Serial.println("WiFi Connect Fail");
  }
}

void sendHttpRequest() {
  if (sendCommand("AT+CIPSTART=\"TCP\",\"" + String(serverIp) + "\"," + String(serverPort), 10000, "OK")) {
    // HTTP 요청 생성
    String httpRequest = "GET /?message=hello%20java HTTP/1.1\r\nHost: " + String(serverIp) + "\r\nConnection: close\r\n\r\n";
    if (sendCommand("AT+CIPSEND=" + String(httpRequest.length()), 1000, ">")) {
      esp8266.print(httpRequest);

      delay(5000);

      // 데이터 수신을 위한 개선된 코드
      String response = "";
      long timeout = millis() + 10000;  // 10초 타임아웃
      while (millis() < timeout) {
        while (esp8266.available()) {
          char c = esp8266.read();
          response += c;
          timeout = millis() + 500;  // 데이터가 수신될 때마다 타임아웃 갱신
        }
      }

  
      if (response.length() > 0) {
        Serial.println("server: " + response);
      
        if (response.indexOf("") != -1) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Response:");
          lcd.setCursor(0, 1);
          lcd.print("hello");
        } else {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Unexpected Resp");
          lcd.setCursor(0, 1);
          lcd.print(response.substring(0, 16));
        }
      } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("HTTP Error");
      }

      // AT+CIPCLOSE 명령을 생략하고 자동으로 연결이 닫히도록 함
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("CIPSEND Error");
    }
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("CIPSTART Error");
  }
}

bool sendCommand(String command, int timeout, String expectedResponse) {
  String response = "";
  esp8266.println(command);
  long int time = millis();
  while ((time + timeout) > millis()) {
    while (esp8266.available()) {
      char c = esp8266.read();
      response += c;
    }
    if (response.indexOf(expectedResponse) != -1) {
      Serial.println(response);
      return true;
    }
  }
  Serial.println(response);
  return false;
}

void loop() {
  // 반복할 필요가 없기 때문에 아무 코드도 넣지 않습니다.
}




