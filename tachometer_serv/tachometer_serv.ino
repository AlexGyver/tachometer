/*
Created 2016
by AlexGyver
AlexGyver Home Labs Inc.
*/

#include <Servo.h> //библиотека серво (стандартная)
Servo servo;  //объявить серво назвать servo

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
}

void sens() {
	RPM=60/((float)(micros()-lastflash)/1000000);  //расчет
	lastflash=micros();  //запомнить время последнего оборота
}

void loop() {
	pos=map(RPM, min_pos, max_pos, 0, 180); //перевести значение от минимума до максимума в угол поворота сервы (от 0 до 180)
	servo.write(pos);  //повернуть серву
	Serial.println(RPM);  //послать в порт

	if ((micros()-lastflash)>1000000){ //если сигнала нет больше секунды
		RPM=0;  //считаем что RPM 0
	}
}
