#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>

#define SS_PIN 10
#define RST_PIN 9

// MFRC522 인스턴스 생성
MFRC522 mfrc522(SS_PIN, RST_PIN);
// 소프트웨어 시리얼 포트 설정 (RX: 2, TX: 3)
SoftwareSerial esp8266(2, 3);

// 마지막 결과를 저장할 변수
String lastResult = "";

// 사전 정의된 UID 값
const String predefinedUID = "7316ab2f";

// 안드로이드 서버의 IP와 포트 번호 설정
const char* serverIP = "192.168.137.32"; // 안드로이드 서버 IP 주소
const int serverPort = 9000; // 안드로이드 서버 포트 번호

void setup() {
  // 시리얼 통신 초기화
  Serial.begin(9600);
  esp8266.begin(9600); // ESP8266의 보드레이트 설정

  // ESP8266 초기화 명령어 전송
  sendCommand("AT+RST", 5000, "OK");
  sendCommand("AT+CWMODE=1", 1000, "OK");
  if (sendCommand("AT+CWJAP=\"DESKTOP-Junho\",\"12345678\"", 10000, "OK"))// WiFi 연결
  {
      Serial.println("WiFi Connected");
  }
  else 
  {
      Serial.println("WiFi Connect Fail");
  }

  // SPI 및 MFRC522 초기화
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println(F("NFC를 태그해주세요."));
  delay(1000); // ESP-01S 초기화 시간 대기
}

void loop() {
  // 새로운 NFC 카드가 감지되었고 UID를 읽을 수 있을 때
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // UID를 문자열로 변환
    String uid = getUID();
    
    // 사전 정의된 UID 값 출력
    Serial.print("NFC Tag UID : ");
    Serial.println(predefinedUID);
    
    // 읽은 NFC 태그의 UID 출력
    Serial.print("NFC 태그 내용 : ");
    Serial.println(uid);

    // UID가 사전 정의된 값과 일치하는지 확인
    // bool isValid = (uid == predefinedUID);
    // Serial.print("일치함? : ");
    // Serial.println(isValid);

    // 일치 여부에 따라 결과를 저장
    lastResult = "true";
    // isValid ? "true" : "false";
    Serial.println("Response: " + lastResult); // 응답 값을 시리얼 모니터에 출력

    // 결과를 안드로이드 서버로 보내기
    sendResultToAndroid(lastResult);

    delay(1000); // 작은 지연 추가

    // 태그 상태를 초기화하여 새로운 태그를 인식할 수 있도록 함
    mfrc522.PICC_HaltA(); // 태그를 멈춤
    mfrc522.PCD_StopCrypto1(); // 암호화 중지
  }

  // ESP8266으로부터 데이터를 수신하는 부분 추가
  if (esp8266.available()) {
    String response = esp8266.readStringUntil('\n');
    Serial.println("Received from Android: " + response);
    // 필요한 경우 수신된 데이터 처리
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

void sendResultToAndroid(String result) {
    if (sendCommand("AT+CIPSTART=\"TCP\",\"" + String(serverIP) + "\"," + String(serverPort), 10000, "OK")) 
    {
      // String httpRequest = "GET /update?result=" + result + " HTTP/1.1\r\nHost: " + String(serverIP) + "\r\nConnection: close\r\n\r\n";
        String request = "GET /update?result=" + result + " HTTP/1.1\r\n\r\n";
      if (sendCommand("AT+CIPSEND=" + String(request.length()), 1000, ">")) {
          esp8266.print(request);
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
          }
          else 
          {
            Serial.println("reponse Error");
          }

    } else {
      Serial.println("Error: Failed to connect to server");
    }
  }
}

// NFC 태그의 UID를 문자열로 변환하여 반환
String getUID() {
  String uid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    uid += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
    uid += String(mfrc522.uid.uidByte[i], HEX);
  }
  uid.toLowerCase(); // 소문자로 변환하여 비교
  return uid;
}
