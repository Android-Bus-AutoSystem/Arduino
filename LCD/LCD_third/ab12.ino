#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ESP8266과 시리얼 통신을 설정합니다.
SoftwareSerial esp8266(2, 3); // RX, TX

// I2C LCD 설정
LiquidCrystal_I2C lcd(0x27, 16, 2);

// WiFi 네트워크 정보
const char * ssid = "DESKTOP-Junho";
const char * password = "12345678";

// 안드로이드 서버 정보
const char * androidServerIp = "192.168.137.32"; // 안드로이드 장치의 IP 주소
const int androidServerPort = 8080;

// 버튼 핀 설정
const int buttonBoardingpin1 = 7;
const int buttonNotBoardingpin2 = 8;

int buttonState1 = 0;       // 첫 번째 버튼 상태를 저장할 변수
int buttonState2 = 0;       // 두 번째 버튼 상태를 저장할 변수

// 상태 변수
bool waitingForResponse = false;
String busStopName = "";

void setup() {
  // LCD 초기화
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Connecting...");

  // 시리얼 모니터와 ESP8266 초기화
  Serial.begin(9600);
  esp8266.begin(9600);
  
  // 버튼 핀을 입력으로 설정 
  pinMode(buttonBoardingpin1, INPUT);
  pinMode(buttonNotBoardingpin2, INPUT);

  // WiFi 연결
  connectToWiFi();

  // 서버 시작
  startServer();
}

// WiFi에 연결하는 함수
void connectToWiFi() {
  sendCommand("AT+RST", 5000, "OK"); // ESP8266 리셋
  sendCommand("AT+CWMODE=1", 1000, "OK"); // 클라이언트 모드 설정

  // WiFi 네트워크에 연결
  String connectCommand = "AT+CWJAP=\"" + String(ssid) + "\",\"" + String(password) + "\"";
  Serial.println("Sending WiFi Connect Command: " + connectCommand);
  
  if (sendCommand(connectCommand, 15000, "OK")) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WiFi Connected");
    Serial.println("WiFi Connected");

    // IP 주소 확인
    sendCommand("AT+CIFSR", 1000, "OK");
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WiFi Connect Fail");
    Serial.println("WiFi Connect Fail");
  }
}

// 서버를 시작하는 함수
void startServer() {
  sendCommand("AT+CIPMUX=1", 1000, "OK");  // 다중 연결 허용
  String startServerCmd = "AT+CIPSERVER=1,80";  // 포트 80에서 서버 시작
  if (sendCommand(startServerCmd, 1000, "OK")) {
    Serial.println("Server started");
  } else {
    Serial.println("Server failed to start");
  }
}

// 메인 루프
void loop() {
  // ESP8266으로부터 요청을 수신
  if (esp8266.available()) {
    String request = esp8266.readString();
    Serial.println("Received Request: " + request);

    // 요청에서 버스 정류장 이름 추출
    if (request.indexOf("GET /?stop=") != -1) {
      int startIndex = request.indexOf("=") + 1;
      int endIndex = request.indexOf(" ", startIndex);
      busStopName = urlDecode(request.substring(startIndex, endIndex));
      Serial.println("Name: " + busStopName);
      
      // LCD에 버스 정류장 이름 표시
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Stop:");
      lcd.setCursor(0, 1);
      lcd.print(busStopName);

      // 안드로이드 장치로 응답
      respondToClient("Bus stop name received");

      // 응답 상태 플래그 설정
      waitingForResponse = true;
    }
  }

  buttonState1 = digitalRead(buttonBoardingpin1); // 첫 번째 버튼 상태를 읽습니다.
  buttonState2 = digitalRead(buttonNotBoardingpin2); // 두 번째 버튼 상태를 읽습니다.

  // 버튼 입력 처리
  if (waitingForResponse) {
    // 탑승 버튼이 눌렸는지 확인
    if (buttonState1 == HIGH) {
      sendBoardingStatus("TRUE"); // 탑승 상태 전송
      Serial.println("Boarding");
      delay(500);                          // 디바운싱을 위해 잠시 대기합니다.

      waitingForResponse = true; // 상태 플래그 초기화
    }
    // 미탑승 버튼이 눌렸는지 확인
    if (buttonState2 == HIGH) {
      sendBoardingStatus("FALSE"); // 미탑승 상태 전송
      Serial.println("NotBoarding");
      delay(500);                          // 디바운싱을 위해 잠시 대기합니다.
      waitingForResponse = true; // 상태 플래그 초기화
    }
  }
}

void respondToClient(String message) {
  // HTTP 응답 생성
  String httpResponse = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/html\r\n"
                        "Connection: close\r\n"
                        "Content-Length: " + String(message.length()) + "\r\n\r\n" +
                        message + "\r\n";
  
  if (sendCommandWithRetry("AT+CIPSEND=0," + String(httpResponse.length()), 1000, ">", 3)) { // 데이터 전송 준비
    esp8266.print(httpResponse); // 응답 전송
    delay(100); // 추가 지연
    sendCommandWithRetry("AT+CIPCLOSE=0", 5000, "OK", 3); // 연결 닫기
  } else {
    Serial.println("Error sending HTTP response");
  }
}

void sendBoardingStatus(String status) {
  // HTTP 요청 생성
  String httpRequest = "GET /?status=" + status + "&stop=" + busStopName + " HTTP/1.1\r\nHost: " + String(androidServerIp) + "\r\nConnection: close\r\n\r\n";

  // 서버에 연결하고 요청 전송
  if (sendCommandWithRetry("AT+CIPCLOSE", 10000, "OK", 1)) { // 이전 연결 닫기
    delay(1000); // 지연 추가
  }
  
  if (sendCommandWithRetry("AT+CIPSTART=\"TCP\",\"" + String(androidServerIp) + "\"," + String(androidServerPort), 10000, "OK", 3)) {
    delay(1000); // 지연 추가
    if (sendCommandWithRetry("AT+CIPSEND=" + String(httpRequest.length()), 1000, ">", 3)) {
      esp8266.print(httpRequest);
      delay(100); // 추가 지연
      sendCommandWithRetry("AT+CIPCLOSE", 1000, "OK", 3); // 연결 닫기
    } else {
      Serial.println("Error sending boarding status");
    }
  } else {
    Serial.println("Error connecting to server");
  }
}

bool sendCommandWithRetry(String command, int timeout, String expectedResponse, int retryCount) {
  for (int i = 0; i < retryCount; i++) {
    if (sendCommand(command, timeout, expectedResponse)) {
      return true;
    }
    delay(2000); // 재시도 전 대기 시간 증가
  }
  return false;
}

bool sendCommand(String command, int timeout, String expectedResponse) {
  String response = "";
  esp8266.println(command); // 명령 전송
  long int time = millis();
  while ((time + timeout) > millis()) {
    while (esp8266.available()) {
      char c = esp8266.read();
      response += c;
    }
    if (response.indexOf(expectedResponse) != -1) {
      Serial.println(response); // 응답 출력
      return true;
    }
  }
  Serial.println(response); // 응답 출력
  return false;
}

String urlDecode(String input) {
    String decoded = "";  // 디코딩된 문자열을 저장할 String 객체
    char temp[] = "0x00"; // 임시 배열로, 16진수 문자를 저장하는 데 사용
    unsigned int len = input.length(); // 입력 문자열의 길이
    unsigned int i = 0; // 현재 위치를 나타내는 인덱스 변수
    
    while (i < len) { // 문자열의 끝에 도달할 때까지 반복
        char c = input.charAt(i); // 현재 문자를 가져옴
        if (c == '%') { // 현재 문자가 '%'이면, URL 인코딩된 문자임을 의미
            if (i + 2 < len) { // '%' 다음에 두 개의 문자가 더 있는지 확인
                temp[2] = input.charAt(i + 1); // 첫 번째 16진수 문자
                temp[3] = input.charAt(i + 2); // 두 번째 16진수 문자
                decoded += (char)strtol(temp, NULL, 16); // 16진수 문자열을 정수로 변환하고, 이를 문자로 변환하여 decoded에 추가
                i += 3; // 세 개의 문자를 처리했으므로 인덱스를 세 칸 이동
            } else {
                decoded += c; // '%xx' 형식이 아닌 경우 현재 문자를 그대로 추가
                break; // 입력 문자열의 끝에 도달했으므로 루프 종료
            }
        } else if (c == '+') { // 현재 문자가 '+'이면, 이는 공백을 의미
            decoded += ' '; // 공백으로 변환하여 추가
            i++;
        } else {
            decoded += c; // 다른 경우에는 현재 문자를 그대로 추가
            i++;
        }
    }
    return decoded; // 디코딩된 문자열 반환
}

