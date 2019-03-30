/*
	函数：wifi客户端模式初始化
*/
void wifi_client_setup () {
	//string转char
	char ssid_char[conf.ssid.length() + 1];
	conf.ssid.toCharArray(ssid_char, conf.ssid.length() + 1);
	char pass_char[conf.password.length() + 1];
	conf.password.toCharArray(pass_char, conf.password.length() + 1);

	//初始化ESP8266的WIFI客户端(Client)模式
	WiFi.mode(WIFI_STA);

	//连接wifi
	WiFi.begin(ssid_char, pass_char);

	//循环等待连接,无超时
	while (WiFi.status() != WL_CONNECTED) {
		delay(250);
		Serial.print(".");
		Serial1.print(".");
	}

	//串口打印连接成功信息
	Serial.println ("\nInfo - WiFi connection success");
	Serial1.println("\nInfo - WiFi connection success");

	//配置Blynk服务器
	Blynk.config(auth);

	//初始化红外线库
	irsend.begin();//初始化红外线发射库
	irrecv.setUnknownThreshold(MIN_UNKNOWN_SIZE);//初始化红外线接收库
	irrecv.enableIRIn(); //开启红外线接收

	//启用OTA下载
	ArduinoOTA.setHostname("ESP8266 IR");//在arduino ide中显示的名字
	ArduinoOTA.onStart([]() {});//OTA下载开始函数
	ArduinoOTA.onEnd([]() {});//OTA下载结束函数
	ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {});//OTA下载进度函数
	ArduinoOTA.onError([](ota_error_t error) {ESP.restart();});//OTA下载错误函数
	ArduinoOTA.begin();//开启OTA

	Blynk.virtualWrite(V0, 0);//Blynk虚拟引脚V0写0
}
/*
	函数：wifi客户端模式循环
*/
void wifi_client_loop () {
	Blynk.run();//Blynk循环函数
	ArduinoOTA.handle();//OTA循环函数

	//红外学习
	if (ReadIR_EN)
		StudyIR ();//学习红外函数
}
