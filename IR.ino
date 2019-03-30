/*
 函数：发射红外线
*/
void SendIR(String path) {
	String FileName = "/ir/" + path + ".o";//文件名

	//从FS中读取红外编码文件
	File file = SPIFFS.open(FileName, "r");//以只读方式打开文件

	if (!file) {
		//文件打开失败返回错误
		Serial.println("Warn - file open failed"); Serial1.println("Warn - file open failed");
	} else {
		//串口输出文件名
		Serial.print("Info - IR Send "); Serial.print(FileName);
		Serial1.print("Info - IR Send "); Serial1.print(FileName);

		//将文件读入string
		String str;
		while (file.available()) str = file.readString();//循环读入文本
		file.close();//关闭文件

		uint16_t *code_array;//代码缓冲区
		int16_t index;//当前项
		uint16_t count;//总项目

		/*
		 * 读取到的红外线编码文件实际是以','分隔的16位int数组
		*/

		//查找一共多少项
		index = -1;
		count = 1;
		do {
			/*
			 * 循环从str中寻找逗号(",")
			 * 每寻找到一个逗号便进行计数(count +1)
			 * 并将逗号出现的位置(下标)写入index
			 * 在下一次寻找中以index为起始位置继续寻找
			 * 直到寻找不到逗号(即,index = -1)
			 */
			index = str.indexOf(',', index + 1);//从index + 1开始查找','
			count++;//计数
		} while (index != -1);//只要index != -1就一直运行do

		/*
		 * 因为空调码长度不一,所以这里使用申请动态内存
		 * 申请一个连续内存区域
		 * 长度为 count * sizeof(uint16_t)
		 * 的通用类型的指针
		 * 并使用reinterpret_cast函数,强行转换为uint16_t类型
		 */
		code_array = reinterpret_cast<uint16_t*>(malloc(count * sizeof(uint16_t)));//申请内存

		//检查内存是否申请成功
		if (code_array == NULL) {
			//内存申请失败
			Serial.println("\nError - reboot.");
			ESP.restart();//重启
			return;
		}

		//将文本转换为16位数组
		count = 0;
		uint16_t start_from = 0;
		do {
			index = str.indexOf(',', start_from);//从start_from开始查找','
			code_array[count] = str.substring(start_from, index).toInt();//截取start_from到index之间的字符,并转换为int型
			start_from = index + 1;//赋值为,刚才找到的','下一个位置
			count ++;//计数
		} while (index != -1);

		//串口输出这个红外编码的长度
		Serial.print (" ("); Serial.print (count);Serial.println (")");
		Serial1.print(" ("); Serial1.print(count);Serial1.println(")");

		//发射红外线
		irsend.sendRaw(code_array, count, 38);//以38MHZ发射code_array

		//释放内存
		free(code_array);//释放刚才申请的内存,否则会一直占用RAM
		return;
	}
}

/*
 函数：学习红外线编码
*/
void StudyIR () {
	//读取红外线
	if (irrecv.decode(&results)) {
		//红外读取成功,并将结果赋值到results类

		//串口打印
		Serial.println("Info - Read to infrared coding");

		//将读取到的红外线结果转换为string
		String para = resultToSourceCode2(&results);

		//保存的文件名
		String FileName = "/ir/";
		if (virtual_value [1])  FileName += "V1";
		if (virtual_value [2])  FileName += "V2";
		if (virtual_value [3])  FileName += "V3";
		if (virtual_value [4])  FileName += "V4";
		if (virtual_value [5])  FileName += "V5";
		if (virtual_value [6])  FileName += "V6";
		if (virtual_value [7])  FileName += "V7";
		if (virtual_value [8])  FileName += "V8";
		if (virtual_value [9])  FileName += "V9";
		if (virtual_value [10]) FileName += "V10";
		if (virtual_value [11]) FileName += "V11";
		if (virtual_value [12]) FileName += "V12";
		if (virtual_value [13]) FileName += "V13";
		if (virtual_value [14]) FileName += "V14";
		if (virtual_value [15]) FileName += "V15";
		if (virtual_value [16]) FileName += "V16";
		FileName += ".o";

		//打开文件,若不存在则创建该文件
		File f = SPIFFS.open(FileName, "w+");

		//将红外线文本(para)保存到FS
		f.print(para);

		//关闭文件
		f.close();

		//串口输出
		Serial.print ("Info - Save to "); Serial.println (FileName);
		Serial1.print("Info - Save to "); Serial1.println(FileName);

		//关闭学习红外开关
		ReadIR_EN = false;
		Blynk.virtualWrite(V0, 0);//Blynk虚拟引脚V0写0

		//喂狗(看门狗)
		yield();
	}
}
