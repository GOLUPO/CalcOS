#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Keypad.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <math.h>

// ================== Configuration ==================

// Wi-Fi Credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// OpenAI API Configuration
const String openai_api_key = "YOUR_OPENAI_API_KEY"; // Replace with your OpenAI API key
const String openai_endpoint = "https://api.openai.com/v1/chat/completions";

// OLED Display Configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Keypad Configuration
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {4, 16, 17, 5}; // GPIO pins connected to the rows
byte colPins[COLS] = {18, 19, 23, 22}; // GPIO pins connected to the columns
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// LED and Buzzer Configuration
const int ledPin = 25;
const int buzzerPin = 26;

// ================== Enums and Variables ==================

// Operating Modes
enum Mode { CALC, APP, STANDBY };
Mode currentMode = CALC;

// Available Apps
enum App { CHATGPT, UNIT_CONVERTER, PRIME_CHECKER, NUM_APPS };
App currentApp = CHATGPT;

// Standby Variables
bool isStandby = false;
unsigned long lastActivity = 0;
const unsigned long standbyDelay = 300000; // 5 minutes in milliseconds

// Calculator Variables
String inputExpression = "";
double calcResult = 0.0;

// ChatGPT Variables
String chatInput = "";
String chatResponse = "";

// Unit Converter Variables
String unitInput = "";
double unitResult = 0.0;

// Prime Checker Variables
String primeInput = "";

// Available Models
String models[] = {"gpt-4", "gpt-3.5-turbo"};
int currentModelIndex = 0;
String selectedModel = models[currentModelIndex];

// ================== Function Declarations ==================

void setupWiFi();
String sendToChatGPT(String question, String model);
void showStandby();
void enterStandby();
void exitStandby();
double evalExpression(String expr);
void handleCalculator(char key);
void handleAppMode(char key);
void handleChatGPTApp(char key);
void handleUnitConverterApp(char key);
void handlePrimeCheckerApp(char key);

// ================== Setup Function ==================

void setup(){
  // Initialize LED and Buzzer
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  digitalWrite(buzzerPin, LOW);
  
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Initialize OLED Display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  // Display Boot Message
  display.setCursor(0,0);
  display.print("CalcOS v1.0");
  display.display();
  delay(2000);
  display.clearDisplay();
  
  // Connect to Wi-Fi
  setupWiFi();
  
  // Display Home Menu
  currentMode = CALC;
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Scientific Calc");
  display.setCursor(0,10);
  display.print("Press 'A' for Apps");
  display.display();
  
  // Initialize Standby Timer
  lastActivity = millis();
}

// ================== Loop Function ==================

void loop(){
  // Check for Standby
  if(currentMode != STANDBY){
    if((millis() - lastActivity) > standbyDelay){
      enterStandby();
    }
  }

  // Read Key Press
  char key = keypad.getKey();
  if(key){
    lastActivity = millis(); // Reset Standby Timer
    
    // Feedback: LED and Buzzer
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, LOW);
    
    if(currentMode == CALC){
      handleCalculator(key);
    }
    else if(currentMode == APP){
      handleAppMode(key);
    }
    else if(currentMode == STANDBY){
      // Wake up from standby
      exitStandby();
      currentMode = CALC;
      display.clearDisplay();
      display.setCursor(0,0);
      display.print("Scientific Calc");
      display.setCursor(0,10);
      display.print("Press 'A' for Apps");
      display.display();
    }
  }
}

// ================== Wi-Fi Setup ==================

void setupWiFi(){
  WiFi.begin(ssid, password);
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Connecting to WiFi");
  display.display();
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    display.print(".");
    display.display();
  }
  
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("WiFi Connected");
  display.setCursor(0,10);
  display.print(WiFi.localIP());
  display.display();
  delay(2000);
  
  // Clear Display after connection
  display.clearDisplay();
}

// ================== ChatGPT Integration ==================

String sendToChatGPT(String question, String model){
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    http.begin(openai_endpoint);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", "Bearer " + openai_api_key);
    
    // Create JSON Payload
    String payload = "{";
    payload += "\"model\": \"" + model + "\",";
    payload += "\"messages\": [{\"role\": \"user\", \"content\": \"" + question + "\"}]";
    payload += "}";
    
    // Send POST Request
    int httpResponseCode = http.POST(payload);
    
    String responseBody = "";
    if(httpResponseCode > 0){
      responseBody = http.getString();
    }
    else{
      responseBody = "Error: " + String(httpResponseCode);
    }
    http.end();
    
    // Parse JSON Response
    DynamicJsonDocument doc(2048);
    DeserializationError error = deserializeJson(doc, responseBody);
    if(error){
      return "JSON Parsing Error";
    }
    String reply = doc["choices"][0]["message"]["content"];
    return reply;
  }
  return "WiFi Not Connected";
}

// ================== Standby Mode Functions ==================

void showStandby(){
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Standby Mode");
  display.display();
}

void enterStandby(){
  currentMode = STANDBY;
  isStandby = true;
  showStandby();
  // Turn off OLED to save power
  display.ssd1306_command(SSD1306_DISPLAYOFF);
}

void exitStandby(){
  isStandby = false;
  // Turn on OLED
  display.ssd1306_command(SSD1306_DISPLAYON);
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Scientific Calc");
  display.setCursor(0,10);
  display.print("Press 'A' for Apps");
  display.display();
}

// ================== Calculator Functions ==================

// Simple expression evaluator supporting + and -
double evalExpression(String expr){
  double result = 0.0;
  int lastOp = 1; // 1 for addition, -1 for subtraction
  String number = "";
  for(char c : expr){
    if(isDigit(c) || c == '.'){
      number += c;
    }
    else{
      if(number.length() > 0){
        result += lastOp * number.toFloat();
        number = "";
      }
      if(c == '+') lastOp = 1;
      if(c == '-') lastOp = -1;
      // Extend with more operations as needed
    }
  }
  if(number.length() > 0){
    result += lastOp * number.toFloat();
  }
  return result;
}

void handleCalculator(char key){
  if(key == '#'){ // Execute calculation
    if(inputExpression.length() > 0){
      calcResult = evalExpression(inputExpression);
      display.clearDisplay();
      display.setCursor(0,0);
      display.print("Result:");
      display.setCursor(0,10);
      display.print(calcResult);
      display.display();
      inputExpression = "";
    }
  }
  else if(key == 'A'){ // Switch to App Mode
    currentMode = APP;
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("App Mode");
    display.setCursor(0,10);
    display.print("Press 'A' to Select");
    display.display();
  }
  else if(key == '*'){ // Clear input
    inputExpression = "";
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("Scientific Calc");
    display.setCursor(0,10);
    display.print("Enter Expression");
    display.display();
  }
  else { // Add character to expression
    inputExpression += key;
    display.setCursor(0,0);
    display.print("Expr: " + inputExpression);
    display.display();
  }
}

// ================== App Mode Functions ==================

void handleAppMode(char key){
  // Static variables to maintain state within app mode
  static int selectedApp = 0;
  static bool inMenu = true;
  
  if(inMenu){
    if(key == 'A'){ // Select App
      inMenu = false;
      currentApp = static_cast<App>(selectedApp);
      display.clearDisplay();
      display.setCursor(0,0);
      switch(currentApp){
        case CHATGPT:
          display.print("ChatGPT");
          break;
        case UNIT_CONVERTER:
          display.print("Unit Converter");
          break;
        case PRIME_CHECKER:
          display.print("Prime Checker");
          break;
        // Add cases for additional apps here
        default:
          display.print("App");
          break;
      }
      display.setCursor(0,10);
      display.print("Press 'A' to Use");
      display.display();
    }
    else if(key == 'B'){ // Enter Standby
      enterStandby();
    }
    else{
      // Navigate Menu
      if(key >= '1' && key <= '3'){ // Assuming 3 apps for v1.0
        selectedApp = key - '1';
        display.clearDisplay();
        display.setCursor(0,0);
        display.print("Selected App:");
        display.setCursor(0,10);
        display.print(keys[0][selectedApp]); // Display app number
        display.display();
      }
    }
  }
  else{
    // Handle specific app interactions
    switch(currentApp){
      case CHATGPT:
        handleChatGPTApp(key);
        break;
      case UNIT_CONVERTER:
        handleUnitConverterApp(key);
        break;
      case PRIME_CHECKER:
        handlePrimeCheckerApp(key);
        break;
      // Add cases for additional apps here
      default:
        break;
    }
  }
}

// ================== ChatGPT App ==================

void handleChatGPTApp(char key){
  if(key == '*'){ // Return to App Menu
    currentMode = APP;
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("App Mode");
    display.setCursor(0,10);
    display.print("Press 'A' to Select");
    display.display();
    return;
  }
  else if(key == '#'){ // Send Query to ChatGPT
    if(chatInput.length() > 0){
      display.clearDisplay();
      display.setCursor(0,0);
      display.print("Sending Query...");
      display.display();
      
      // Send query to ChatGPT
      chatResponse = sendToChatGPT(chatInput, selectedModel);
      
      // Display response (truncate if too long)
      display.clearDisplay();
      display.setCursor(0,0);
      display.print("GPT:");
      display.setCursor(0,10);
      if(chatResponse.length() > 16){
        display.print(chatResponse.substring(0,16));
      }
      else{
        display.print(chatResponse);
      }
      display.display();
      chatInput = "";
    }
  }
  else { // Add character to ChatGPT input
    chatInput += key;
    display.setCursor(0,0);
    display.print("Q: " + chatInput);
    display.display();
  }
}

// ================== Unit Converter App ==================

void handleUnitConverterApp(char key){
  if(key == '*'){ // Return to App Menu
    currentMode = APP;
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("App Mode");
    display.setCursor(0,10);
    display.print("Press 'A' to Select");
    display.display();
    return;
  }
  else if(key == '#'){ // Execute Conversion
    if(unitInput.length() > 0){
      // Simple example: meters to kilometers
      double value = unitInput.toFloat();
      unitResult = value / 1000.0; // meters to kilometers
      
      display.clearDisplay();
      display.setCursor(0,0);
      display.print("Result:");
      display.setCursor(0,10);
      display.print(unitResult);
      display.print(" km");
      display.display();
      unitInput = "";
    }
  }
  else { // Add character to unit input
    unitInput += key;
    display.setCursor(0,0);
    display.print("Meters: " + unitInput);
    display.display();
  }
}

// ================== Prime Checker App ==================

void handlePrimeCheckerApp(char key){
  if(key == '*'){ // Return to App Menu
    currentMode = APP;
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("App Mode");
    display.setCursor(0,10);
    display.print("Press 'A' to Select");
    display.display();
    return;
  }
  else if(key == '#'){ // Check Prime
    if(primeInput.length() > 0){
      long num = primeInput.toInt();
      bool isPrime = true;
      
      if(num <= 1){
        isPrime = false;
      }
      else{
        for(long i = 2; i <= sqrt(num); i++){
          if(num % i == 0){
            isPrime = false;
            break;
          }
        }
      }
      
      display.clearDisplay();
      display.setCursor(0,0);
      display.print(num);
      display.setCursor(0,10);
      if(isPrime){
        display.print("is Prime");
      }
      else{
        display.print("Not Prime");
      }
      display.display();
      primeInput = "";
    }
  }
  else { // Add character to prime input
    primeInput += key;
    display.setCursor(0,0);
    display.print("Number: " + primeInput);
    display.display();
  }
}

// ================== Additional Helper Functions ==================

// You can add more functions here for additional apps, such as currency converter, matrix calculator, etc.

// Example: Add a delay to save power, handle more complex expressions, etc.

