/*
Created 2016
by AlexGyver
AlexGyver Home Labs Inc.
*/

#include <Servo.h> //библиотека серво (стандартная)
Servo servo;  //объявить серво назвать servo

//-----------дисплей-----------
#include <TM74HC595Display.h>
int SCLK = 7;
int RCLK = 6;
int DIO = 5;
TM74HC595Display disp(SCLK, RCLK, DIO);
unsigned char LED_0F[29];
//--------дисплей-------

unsigned long lastflash;
int RPM, pos;
unsigned int min_pos=0;  //минимальная частота оборотов 
unsigned int max_pos=1500; //максимальная частота оборотов

void setup() {
	Serial.begin(9600);  //открыть порт
	attachInterrupt(0,sens,RISING); //подключить прерывание на 2 пин при повышении сигнала
	pinMode(3, OUTPUT);   //3 пин как выход
	digitalWrite(3, HIGH);  //подать 5 вольт на 3 пин
	servo.attach(4);  //серво на 4 порту 
	//для дисплея цифры
	LED_0F[0] = 0xC0; //0
	LED_0F[1] = 0xF9; //1
	LED_0F[2] = 0xA4; //2
	LED_0F[3] = 0xB0; //3
	LED_0F[4] = 0x99; //4
	LED_0F[5] = 0x92; //5
	LED_0F[6] = 0x82; //6
	LED_0F[7] = 0xF8; //7
	LED_0F[8] = 0x80; //8
	LED_0F[9] = 0x90; //9
}

void sens() {
	RPM=60/((float)(micros()-lastflash)/1000000);  //расчет
	lastflash=micros();  //запомнить время последнего оборота
}

void loop() {
	pos=map(RPM, min_pos, max_pos, 0, 180); //перевести значение от минимума до максимума в угол поворота сервы (от 0 до 180)
	servo.write(pos);  //повернуть серву
	Serial.println(RPM);  //послать в порт

	disp.digit4(RPM,50);  //вывод на дисплей

	if ((micros()-lastflash)>1000000){ //если сигнала нет больше секунды
		RPM=0;  //считаем что RPM 0
	}
}
