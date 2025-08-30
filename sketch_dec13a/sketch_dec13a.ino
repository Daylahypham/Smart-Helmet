#define A A0                                //Khai báo chân A0
#define B A1                                //Khai báo chân A1
#define buzz 13                             //Khai báo chân 13
#define relay A4                            //Khai báo chân A4
int bt1,bt2,bt3,bt4;
#include <SoftwareSerial.h>
SoftwareSerial SIM(A2,A3);
String SDT="0842966969";                    //Khai báo số điện thoại 
char *noidung = {                           //Khai báo nội dung 
  " Nguoi nha bi nga - Nguy hiem ! "
};
void setup() {
  SIM.begin(9600);
  pinMode(A,INPUT); 
  pinMode(B,INPUT);
  pinMode(buzz,OUTPUT);
  pinMode(relay,OUTPUT);
  digitalWrite(buzz,LOW);
  digitalWrite(relay,LOW);
  beep();
}
void beep(){                               //Còi
  digitalWrite(buzz,HIGH);
  delay(200);
  digitalWrite(buzz,LOW);
  delay(200);
}
void khoa(){                              //Khóa
  digitalWrite(relay,HIGH);  
}
void tat(){
  digitalWrite(relay,LOW);
}
void loop() {
thoat: 
  tat();
  digitalWrite(buzz,LOW); 
  bt1=digitalRead(A);
  bt2=digitalRead(B);
  if(bt1 == 1) {
  khoa();
   while(1){
  t: khoa();
  bt1=digitalRead(A);
  bt2=digitalRead(B);
 if(bt2 == 1){
  khoa();
  beep();
  for(int i = 1; i<=10; i++){
    bt2=digitalRead(B);
    delay(500);
    khoa();
    if(bt2 == 0) goto t;
  }
  
   for(int k= 1; k<=15; k++){
    beep();
    khoa();
    delay(200);
  }
  khoa();
  call();
  SendSMS();
  bt2=digitalRead(B);
  if(bt2 == 1){
    beep();
    bt2=digitalRead(B);
  }
   digitalWrite(buzz,LOW);
}
if((bt1 ==0 ) && (bt2 ==0)){
  for(int l =1; l<=15;l++){
    bt1=digitalRead(A);
   bt2=digitalRead(B);
   delay(500);
   khoa();
    if((bt1 == 1)|| (bt2==1)) goto t;
  }
   tat();
   digitalWrite(buzz,LOW);
   goto thoat;
} 
   }
  }
}
 void call(){                            //Gọi
  digitalWrite(buzz,HIGH);       
  at("AT",500);
  at("ATD"+SDT+";",10000);
  at("ATH",15000);
  digitalWrite(buzz,LOW);
}
void at(String _atcm,unsigned long _dl){
  SIM.print(_atcm+"\r\n");
  delay(_dl);
}
void SendSMS()                           //Gửi tin nhắn
{
  digitalWrite(buzz,HIGH);
  at("AT",1000);
  at("AT+CMGF=1",1000);
  at("AT+CSCS=\"GSM\"",1000);
  at("AT+CMGS=\"" + SDT +"\"",2000);
  at(noidung,3000);
  SIM.write(26);  
digitalWrite(buzz,LOW);  
}