/*
 * 虚拟引脚事件程序集
 *     V0 学习
 * V1~V16 红外按钮
 */
BLYNK_WRITE(V0)//学习模式
{
	int pinValue = param.asInt(); //读取虚拟引脚V0的值
	ReadIR_EN = pinValue;
	Serial1.println("Info - Pin change V0");
	if (ReadIR_EN)
		Serial.println("Info - Start learning");
	else
		Serial.println("Info - Start learning end");
}

BLYNK_WRITE(V1)//红外按钮
{
	virtual_value [1] = param.asInt(); // 读取虚拟引脚V1的值
	if (!virtual_value [1])
		return;
	Serial1.println("Info - Pin change V1");
	if (!ReadIR_EN)
		SendIR("V1");
}
BLYNK_WRITE(V2)//红外按钮
{
	virtual_value [2] = param.asInt(); // 读取虚拟引脚V2的值
	if (!virtual_value [2])
		return;
	Serial1.println("Info - Pin change V2");
	if (!ReadIR_EN)
		SendIR("V2");
}
BLYNK_WRITE(V3)//红外按钮
{
	virtual_value [3] = param.asInt(); // 读取虚拟引脚V3的值
	if (!virtual_value [3])
		return;
	Serial1.println("Info - Pin change V3");
	if (!ReadIR_EN)
		SendIR("V3");
}
BLYNK_WRITE(V4)//红外按钮
{
	virtual_value [4] = param.asInt(); // 读取虚拟引脚V4的值
	if (!virtual_value [4])
		return;
	Serial1.println("Info - Pin change V4");
	if (!ReadIR_EN)
		SendIR("V4");
}
BLYNK_WRITE(V5)//红外按钮
{
	virtual_value [5] = param.asInt(); // 读取虚拟引脚V5的值
	if (!virtual_value [5])
		return;
	Serial1.println("Info - Pin change V5");
	if (!ReadIR_EN)
		SendIR("V5");
}
BLYNK_WRITE(V6)//红外按钮
{
	virtual_value [6] = param.asInt(); // 读取虚拟引脚V6的值
	if (!virtual_value [6])
		return;
	Serial1.println("Info - Pin change V6");
	if (!ReadIR_EN)
		SendIR("V6");
}
BLYNK_WRITE(V7)//红外按钮
{
	virtual_value [7] = param.asInt(); // 读取虚拟引脚V7的值
	if (!virtual_value [7])
		return;
	Serial1.println("Info - Pin change V7");
	if (!ReadIR_EN)
		SendIR("V7");
}
BLYNK_WRITE(V8)//红外按钮
{
	virtual_value [8] = param.asInt(); // 读取虚拟引脚V8的值
	if (!virtual_value [8])
		return;
	Serial1.println("Info - Pin change V8");
	if (!ReadIR_EN)
		SendIR("V8");
}
BLYNK_WRITE(V9)//红外按钮
{
	virtual_value [9] = param.asInt(); // 读取虚拟引脚V9的值
	if (!virtual_value [9])
		return;
	Serial1.println("Info - Pin change V9");
	if (!ReadIR_EN)
		SendIR("V9");
}
BLYNK_WRITE(V10)//红外按钮
{
	virtual_value [10] = param.asInt(); // 读取虚拟引脚V10的值
	if (!virtual_value [10])
		return;
	Serial1.println("Info - Pin change V10");
	if (!ReadIR_EN)
		SendIR("V10");
}
BLYNK_WRITE(V11)//红外按钮
{
	virtual_value [11] = param.asInt(); // 读取虚拟引脚V11的值
	if (!virtual_value [11])
		return;
	Serial1.println("Info - Pin change V11");
	if (!ReadIR_EN)
		SendIR("V11");
}
BLYNK_WRITE(V12)//红外按钮
{
	virtual_value [12] = param.asInt(); // 读取虚拟引脚V12的值
	if (!virtual_value [12])
		return;
	Serial1.println("Info - Pin change V12");
	if (!ReadIR_EN)
		SendIR("V12");
}
BLYNK_WRITE(V13)//红外按钮
{
	virtual_value [13] = param.asInt(); // 读取虚拟引脚V13的值
	if (!virtual_value [13])
		return;
	Serial1.println("Info - Pin change V13");
	if (!ReadIR_EN)
		SendIR("V13");
}
BLYNK_WRITE(V14)//红外按钮
{
	virtual_value [14] = param.asInt(); // 读取虚拟引脚V14的值
	if (!virtual_value [14])
		return;
	Serial1.println("Info - Pin change V14");
	if (!ReadIR_EN)
		SendIR("V14");
}
BLYNK_WRITE(V15)//红外按钮
{
	virtual_value [15] = param.asInt(); // 读取虚拟引脚V15的值
	if (!virtual_value [15])
		return;
	Serial1.println("Info - Pin change V15");
	if (!ReadIR_EN)
		SendIR("V15");
}
BLYNK_WRITE(V16)//红外按钮
{
	virtual_value [16] = param.asInt(); // 读取虚拟引脚V16的值
	if (!virtual_value [16])
		return;
	Serial1.println("Info - Pin change V16");
	if (!ReadIR_EN)
		SendIR("V16");
}
