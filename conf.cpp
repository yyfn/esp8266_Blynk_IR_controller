#include "conf.h"


/*
 类函数：加载配置
*/
void conf::load() {
	//初始化EEPROM
	EEPROM.begin(4096);//初始化EEPROM 
	Serial.println("Info - EEPROM begin");

	//读取数据
	con = (bool)EEPROM.read(conAdr);//读取是否连接wifi
	//如果连接符(con)为真,则从EEPROM中读取wifi设置
	if (con) {
		//读取wifi设置
		ssidLen = EEPROM.read(ssidLenAdr);//读取ssid长度
		passwordLen = EEPROM.read(passwordLenAdr);//读取密码长度

		ssid = "";
		password = "";
		//循环读取SSID/PASS
		for (int i = 0; i < ssidLen; i++) 
			ssid += (char)EEPROM.read(ssidAdr + i);
		for (int i = 0; i < passwordLen; i++) 
			password += (char)EEPROM.read(passwordAdr + i);
	}
}
/*
 类函数：重置配置
*/
void conf::reset() {
	con = false;
	save();
}

/*
 类函数：保存配置
*/
void conf::save() {
	//保存是否连接过网络
	EEPROM.write(conAdr, con);

	//保存wifi信息
	ssidLen = ssid.length();//读取SSID的字符长度
	passwordLen = password.length();//读取密码的字符长度
	EEPROM.write(ssidLenAdr, ssidLen);//写入SSID长度
	EEPROM.write(passwordLenAdr, passwordLen);//写入PASS长度
	for (int i = 0; i < ssidLen; i++) 
		EEPROM.write(ssidAdr + i, ssid[i]);
	for (int i = 0; i < passwordLen; i++) 
		EEPROM.write(passwordAdr + i, password[i]);

	//由于ESP8266为FLASH模拟的EEPROM,所以需要这个指令使写入生效
	EEPROM.commit();
	Serial.println("Info - settings saved,EEPROM commit");
}
/*
 类函数：输出配置信息
*/
void conf::info() {
	if (con) {
		Serial.println("Info - Wi-Fi connection information");
		Serial.println("     - SSID: " + ssid);
		Serial.println("     - PSWD: " + password);
	}
}

