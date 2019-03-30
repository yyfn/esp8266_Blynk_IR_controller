#ifndef conf_h
#define conf_h

#include <EEPROM.h>
#include <ESP8266WebServer.h>

/*
 *******EEPROM设置*******
 *定义每一个配置项的首地址
*/
#define conAdr          1   //是否连接wifi的连接符地址
#define ssidLenAdr      128 //SSID长度地址
#define ssidAdr         129 //SSID首位地址
#define passwordLenAdr  161 //密码长度地址
#define passwordAdr     162 //密码首位地址

//类 conf
class conf
{
	//公开类
	public:
		void load();//从EEPROM中读取数据
		void reset();//销毁原有数据,重置系统
		void save();//保存配置
		void info();//串口打印保存的信息


		bool con = false; //true已连接过 false未连接过
		String version = "1.0.0.0";//系统版本信息

		int ssidLen ;//ssid长度
		String ssid = "";//ssid
		int passwordLen  ;//密码长度
		String password = "";//密码
};
#endif
