#include <ESP8266WebServer.h>
ESP8266WebServer server(80);

//拦截DNS库
#include <DNSServer.h>
DNSServer dnsServer;

/*
 函数：载入index
*/
void handle_html_index() {
	Serial.print  ("Info - Load index.html .");
	Serial1.print ("Info - Load index.html .");
	//从FS读取index文件
	File file = SPIFFS.open("/index.html.gz", "r");
	Serial.print  (".");
	Serial1.print (".");

	server.streamFile(file, "text/html");

	Serial.print  (".");
	Serial1.print (".");

	file.close();
	Serial.println  (" Done");
	Serial1.println (" Done");
}
/*
 函数：跳转Captive Portal   hotspot-detect.html
*/
void handle_Captive_Portal () {
	Serial.println  ("Info - Captive Portal");
	Serial1.println ("Info - Captive Portal");
	server.sendHeader("Location", "http://10.0.0.1/index.html");//重定向到本机
	server.sendHeader("Cache-Control", "no-cache");//忽略缓存模式
	server.send(302, "text/plain", "");//发送302跳转

}
/*
 函数：连接wifi
*/
void handle_action_login_html() {
	//从POST参数获取SSID和密码
	String wifi_ssid = server.arg("SSID");
	String wifi_pass = server.arg("PASS");

	//串口打印即将连接wifi的信息
	Serial.println ("Info - Test WiFi connections " + wifi_ssid + "(" + wifi_pass + ")");
	Serial1.println("Info - Test WiFi connections " + wifi_ssid + "(" + wifi_pass + ")");
	
	//将string转换为char
	char ssid_char[wifi_ssid.length() + 1];
	wifi_ssid.toCharArray(ssid_char, wifi_ssid.length() + 1);
	char pass_char[wifi_pass.length() + 1];
	wifi_pass.toCharArray(pass_char, wifi_pass.length() + 1);

	//连接wifi
	WiFi.begin(ssid_char, pass_char);
	uint32 time = millis() + 15000;  //设置30s超时时间

	while (WiFi.status() != WL_CONNECTED && millis() < time) {
		delay(250);
		Serial.print(".");
		Serial1.println(".");
	}

	if (WiFi.status() == WL_CONNECT_FAILED || millis() >=  time)  //连接超时 即 连接失败
	{
		//串口输出wifi连接失败的信息
		Serial.println("\nError - WiFi error");

		//发送无法连接(-1)
		String message = "-1";
		server.send ( 200, "text/plain", message );
		return;
	} else {
		//串口输出wifi连接完成的信息
		Serial.println ("Info - WiFi connection success");
		Serial1.println("Info - WiFi connection success");

		//将收到的wifi信息保存到eeprom
		conf.con = true;
		conf.ssid = wifi_ssid;
		conf.password = wifi_pass;
		conf.save();

		//发送完成信息
		String message = "1";
		server.send ( 200, "text/plain", message );

		//将SOC重启
		ESP.restart();
		return;
	}
	
}

/*
 函数：wifi热点模式初始化
*/
void wifi_ap_setup() {
	Serial.println("Info - Create WiFi AP : Universal Remote");
	//初始化ESP8266的WIFI热点(AP)模式

    WiFi.mode(WIFI_OFF);

	WiFi.mode(WIFI_AP_STA);//AP+Client模式
	IPAddress softLocal(10, 0, 0, 1);//路由地址
	IPAddress softGateway(10, 0, 0, 1);//网关地址
	IPAddress softSubnet(255, 255, 255, 0);//子掩码
	WiFi.softAPConfig(softLocal, softGateway, softSubnet);//设置AP的信息


	//创建一个热点
	WiFi.softAP("Universal Remote", "");//创建一个WIFI

	//创建内网DNS服务器,所有域名重定向到本机
	dnsServer.start(53, "*", softLocal);

	//绑定WEB服务器的文件响应
	server.on ("/", handle_html_index);//首页(wifi连接)
	server.on ("/index.html", handle_html_index);//首页(wifi连接)
	server.on ("/Link_wifi.x", HTTP_POST, handle_action_login_html);//wifi连接的提交页面
	server.on ("/hotspot-detect.html", handle_Captive_Portal);//IOS Captive Portal
	server.on ("/generate_204", handle_Captive_Portal);//安卓 Captive Portal

	//开启WEB服务器
	server.begin();
}
/*
 函数：wifi热点模式循环
*/
void wifi_ap_loop () {
	server.handleClient();
	dnsServer.processNextRequest();
}
