#include <FastLED.h>
#define NUM_LEDS 30           //  从后往前12 个灯珠
#define DATA_PIN 3              // Arduino输出控制信号引脚
#define LED_TYPE WS2813        // LED灯带型号
#define COLOR_ORDER GRB         // RGB灯珠中红色、绿色、蓝色LED的排列顺序

uint8_t max_bright = 30;       // LED亮度控制变量，可使用数值为 0 ～ 255， 数值越大则光带亮度越高

CRGB leds[NUM_LEDS];            // 建立光带leds

int LDR1 = A0; // potentiometer wiper (middle terminal) connected to analog pin 3
int LDR2 = A1;                 // outside leads to ground and +5V
int Leftoutput = 6;
int Rightoutput = 7;
int val1 = 0;  // variable to store the value read
int val2 = 0;
//bool Leftoutput = 0;
//bool Rightoutput = 0;
void setup() {
  pinMode(Leftoutput, OUTPUT);
  pinMode(Rightoutput, OUTPUT);
  Serial.begin(9600);           //  setup serial
  LEDS.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);  // 初始化光带
  FastLED.setBrightness(30);// 设置光带亮度
}

void loop() {
  val1 = analogRead(LDR1);  // read the input pin
  val2 = analogRead(LDR2);
  int diff = abs(val1 - val2);
  if (val1 < 550 && diff > 170) {
    fill_solid(leds + 18, 6, CRGB::Red);
    FastLED.show();
    fadeToBlackBy(leds + 24, 6, 255);
    FastLED.show();//only right red
    Serial.println("1");
    /*digitalWrite(Leftoutput, HIGH);
      digitalWrite(Rightoutput, LOW);
      FastLED.setBrightness(0);
      fill_solid(leds, 30, CRGB::White);
      FastLED.show();*/


  }
  else if (val2 < 450 && diff > 450) {
    fill_solid(leds + 24, 6, CRGB::Red);
    FastLED.show();
    fadeToBlackBy(leds + 18, 6, 255);
    FastLED.show();//only left red
    Serial.println("2");
    /*digitalWrite(Rightoutput, HIGH);
      digitalWrite(Leftoutput, LOW);
      FastLED.setBrightness(0);
      fill_solid(leds, 30, CRGB::White);
      FastLED.show();*/


  }
  else if (val2 < 440 && val1 < 540) {

    fill_solid(leds + 18, 12, CRGB::Red);
    FastLED.show();// all Red
    Serial.println("3");
    /*digitalWrite(Rightoutput, HIGH);
      digitalWrite(Leftoutput, HIGH);
      FastLED.setBrightness(0);
      fill_solid(leds, 30, CRGB::White);
      FastLED.show();*/


  }
  else if (val2 > 710 && val1 > 910) {

    fill_solid(leds + 18, 12, CRGB::White);
    FastLED.show();// all white
    Serial.println("4");
  }
  else {
    fadeToBlackBy(leds + 18, 12, 255);
    FastLED.show();//turn off
    Serial.println("0");
    /*digitalWrite(Leftoutput, LOW);
      digitalWrite(Rightoutput, LOW);
      FastLED.setBrightness(0);
      fill_solid(leds, 30, CRGB::White);
      FastLED.show();*/

  }
  Serial.print("val1 = ");
  Serial.println(val1);
  Serial.print("val2 = ");
  Serial.println(val2);
  Serial.print("diff = ");
  Serial.println(diff);

}
