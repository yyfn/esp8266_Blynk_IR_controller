/*
	虚拟引脚配置:
		V0 学习模式
		V1-V16 红外发射模式
		V25 调试输出

	GPIO：
		GPIO 15 用户按钮（下载按钮）
		GPIO 13 红外发射
		GPIO 14 红外接收
*/

bool debug = true;//调试模式(会输出额外的信息)
#include <string>
//ESP8266
#include <ESP8266WiFi.h>

//Blynk
char auth[] = "";//Blynk通讯秘钥
#define BLYNK_PRINT Serial//Blynk调试信息输出位置
#include <BlynkSimpleEsp8266.h>

//OTA
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

//红外
#include <FS.h>//FS文件系统
#include <IRremoteESP8266.h>//IR基础库
#include <IRsend.h>//IR发射库
#define IR_LED 13//红外LED
IRsend irsend(IR_LED);//定义13为IR发射脚

#include <IRrecv.h>//IR接收解析库
#define RECV_PIN 14//红外接收1838B
#define CAPTURE_BUFFER_SIZE 1024// 缓冲区大小
#define TIMEOUT 50U//超时时间
#define MIN_UNKNOWN_SIZE 12//最小未知红外线编码尺寸
IRrecv irrecv(RECV_PIN, CAPTURE_BUFFER_SIZE, TIMEOUT, true);//定义接收
decode_results results;  // Somewhere to store the results

//程序设置
#include "conf.h"
conf conf;

//程序状态储存
bool ReadIR_EN = false;//学习模式
bool virtual_value [17];//红外发射按钮是否按下

/*
   函数 : 系统初始化函数（相当于main）
*/
void setup()
{
  //初始化串口,波特率9600
  Serial.begin(9600); Serial1.begin(9600);//串口1初始化
  Serial.println("\n\nInfo - System startup");
  Serial1.println("\n\nInfo - System startup");

  SPIFFS.begin();//FS文件系统初始化

  conf.load();//读取配置项

  conf.info();//串口0输出配置项

  //配置用户按钮 GPIO0 为输入模式,并开启中断，
  pinMode (0, INPUT);

  //根据是否连接wifi选择启动类型
  if (conf.con)
    wifi_client_setup();
  else
    wifi_ap_setup();
}

long reset_time = 0;//标记第一次按下gpio15（用户按钮）的时间
void scan_key () {
  if (digitalRead(0) == LOW) {
    delay(10);
    if (digitalRead(0) == LOW) {
      if (reset_time == 0) {//如果第一次按，就把当前运行时间写入变量
        reset_time = millis();
        Serial1.println("Reset button down");
      }
      if (millis() - reset_time >= 5 * 1000) {//按下时间超过5S
        Serial1.println("System reset");
        conf.reset();//删掉以前的配置信息
        ESP.restart();//SOC重启
      }
    }
  } else
    reset_time = 0;//松开按钮将按下时间变量置零
}


/*
   函数 : 系统循环函数（相当于While 1）
*/
void loop()
{
  scan_key ();
  //根据是否连接wifi决定循环类型
  if (conf.con) wifi_client_loop ();
  else wifi_ap_loop ();
}

/*
   函数 : 整数型(uint64) 转 文本型(string)
   参数:
       uint64_t input 64位int数据
*/
String uint64ToString2(uint64_t input) {
  String result = "";

  //循环此函数,直至input为0
  do {
    //取出最小的数字
    char c = input % 10;//对input除以基数,返回余数
    input /= 10;//对input除以基数,剩下整数部分

    //将数字结果转换为ascii码
    c += '0';//0为48

    //将临时的结果插到result的最前端
    result = c + result;
  } while (input);

  //返回文本(string)
  return result;
}

/*
   函数 : 红外编码(decode_results) 转 文本型(string)
   参数:
       const decode_results *results 红外编码
*/
String resultToSourceCode2(const decode_results *results)  {
  
  String output = "";

  /*
     results为一个class
     results->rawlen 为 这个红外编码的长度
     results->rawbuf[i] 为 这个红外编码的矩阵编码(数组)
  */

  //转储数据
  for (uint16_t i = 1; i < results->rawlen; i++) {
    uint32_t usecs = results->rawbuf[i] * 2;
    output += uint64ToString2(usecs);//整数转文本

    //增加分隔符','
    if (i < results->rawlen - 1)
      output += ",";  //最后一个数据不需要','
  }
  return output;
}
