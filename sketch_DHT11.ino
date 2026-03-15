// 引入所需库
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
// OLED屏幕设置（0.96寸I2C版本，分辨率128x64）
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// 温湿度传感器设置
#define DHTPIN 2          // 传感器DATA引脚接Arduino数字2
#define DHTTYPE DHT11     // 传感器类型，DHT22可改为DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  
  // 初始化OLED屏幕
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // I2C地址通常为0x3C或0x3D
    Serial.println(F("OLED初始化失败"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(F("温湿度监测启动..."));
  display.display();
  delay(2000);

  // 初始化温湿度传感器
  dht.begin();
}

void loop() {
  // 读取温湿度数据（DHT传感器建议间隔2秒以上读取）
  delay(3000);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // 检查数据是否有效
  if (isnan(humidity) || isnan(temperature)) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println(F("读取传感器失败!"));
    display.display();
    return;
  }

  // 在OLED上显示数据
  display.clearDisplay();
  // 显示温度
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print(F("Temp: "));
  display.print(temperature);
  display.print(F("°C"));
  // 显示湿度
  display.setCursor(0, 32);
  display.print(F("Humi: "));
  display.print(humidity);
  display.print(F("%"));
  
  display.display(); // 刷新屏幕显示
}
