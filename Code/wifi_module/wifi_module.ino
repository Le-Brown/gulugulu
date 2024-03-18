#include<Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>   //用于搜索多个Wifi，连接信号最强的那个
#include <ESP8266WebServer.h>   //用于在8266上建立网络服务器
#include"String.h"

ESP8266WiFiMulti wifiMulti;           //建立一个ESP8266WiFiMulti对象
ESP8266WebServer esp8266_server(80);  //建立ESP8266WebServer对象，用于响应http请求，监听端口（80）

int type=1;
int ximi=1;
int bobo=1;
int mango=1;
int peach=1;
int sugar=1;
int heat=0;

String int_to_str(int Type, int Sago,int Bobo, int Mango, int Peach,int Syrup ,int Tempe)
{
  String info = "#";
  char temp = Type + '0';  //int转为char
  info+=temp;
  temp = Sago + '0';  //2,西米
  info+=temp;
  temp = Bobo + '0';  //3,啵啵
  info+=temp;
  temp = Mango + '0'; //4,芒果
  info+=temp;
  temp = Peach + '0'; //5，桃子
  info+=temp;
  temp = Syrup + '0'; //6，糖浆
  info+=temp;
  temp = Tempe + '0'; //7，温度
  info+=temp;
  return info;
}

void setup() {
  Serial.begin(9600);
  pinMode(D4,OUTPUT);
  //wifiMulti.addAP("Tsinghua","");    //通过addAP存储WiFi名称和密码
  wifiMulti.addAP("uFi-CABC","1234567890");

  Serial.println("正在连接WIFI...");
  int i=0;
  while(wifiMulti.run()!=WL_CONNECTED){           //连接WiFi
    delay(1000);
    Serial.print(i++);
    Serial.print(' ');
  }
  Serial.print('\n');
  Serial.print("Connected to");
  Serial.println(WiFi.SSID());
  Serial.print("IP address:  ");
  Serial.println(WiFi.localIP());         //输出ESP8266网络服务器的IP

  esp8266_server.begin();                 //启用网站服务
  esp8266_server.on("/",HTTP_GET,handleRoot);     //设置服务器根目录（即'/'）的函数handleRoot
  esp8266_server.on("/yangzhiganlu",HTTP_POST,handleyang);  //设置处理LED控制请求的函数handleLED
  esp8266_server.on("/taotaoganlu",HTTP_POST,handletao);
  esp8266_server.on("/m0",HTTP_POST,handlem0);
  esp8266_server.on("/m1",HTTP_POST,handlem1);
  esp8266_server.on("/m2",HTTP_POST,handlem2);
  esp8266_server.on("/p0",HTTP_POST,handlep0);
  esp8266_server.on("/p1",HTTP_POST,handlep1);
  esp8266_server.on("/p2",HTTP_POST,handlep2);
  esp8266_server.on("/x0",HTTP_POST,handlex0);
  esp8266_server.on("/x1",HTTP_POST,handlex1);
  esp8266_server.on("/x2",HTTP_POST,handlex2);
  esp8266_server.on("/b0",HTTP_POST,handleb0);
  esp8266_server.on("/b1",HTTP_POST,handleb1);
  esp8266_server.on("/b2",HTTP_POST,handleb2);
  esp8266_server.on("/s0",HTTP_POST,handles0);
  esp8266_server.on("/s1",HTTP_POST,handles1);
  esp8266_server.on("/s2",HTTP_POST,handles2);
  esp8266_server.on("/h0",HTTP_POST,handleh0);
  esp8266_server.on("/h1",HTTP_POST,handleh1);
  esp8266_server.onNotFound(handleNotFound);      //设置处理404情况的函数handleNotFound

  Serial.println("HTTP Server started");

  // put your setup code here, to run once:

}

void loop() {
  esp8266_server.handleClient();        //检查是否有http服务器访问请求
  // put your main code here, to run repeatedly:

}

void handleRoot(){
  esp8266_server.send(200,"text/html","<!DOCTYPE html><html><head><meta charset=\"UTF-8\"></meta><title>gulugulu饮料机点单</title></head><body><h2 align=\"center\">  </h2><br><br><br><br><br><br><h2 align=\"center\"><font size=\"10\">^_^ gulugulu饮料机点单界面 ^_^</font></h2><br><h3 align=\"center\"><font size=\"6\">请选择您的饮品</font></h3><form method=\"post\" action=/yangzhiganlu><table align=\"center\"><tr><td></td><td><button name=\"yangzhiganlu\" type=\"submit\" value=\"1\"><font size=\"5\">杨枝甘露</font></button></td></tr></table></form><form method=\"post\" action=/taotaoganlu><table align=\"center\"><tr><td>  </td><td><button name=\"taotaoganlu\" type=\"submit\" value=\"1\"><font size=\"5\">桃桃甘露</font></button></td></tr></table></form></body></html>");
 
}
void handleLED(){
  digitalWrite(D4,!digitalRead(D4));
  esp8266_server.sendHeader("Location","/");
  esp8266_server.send(303);
}
void handleyang(){
  //Serial.print("1");
  peach=0;
  type=1;
  esp8266_server.send(200,"text/html","<!DOCTYPE html><html><head><meta charset=\"UTF-8\"></meta><title>gulugulu饮料机点单</title></head><body><h2 align=\"center\">  </h2><br><br><br><br><br><br><h2 align=\"center\"><font size=\"10\">^_^ gulugulu饮料机点单界面 ^_^</font></h2><br><h3 align=\"center\"><font size=\"6\">请选择芒果份数</font></h3><form method=\"post\" action=/m0><table align=\"center\"><tr><td>  </td><td><button name=\"0\" type=\"submit\" value=\"1\"><font size=\"5\">0</font></button></td></tr></table></form><form method=\"post\" action=/m1><table align=\"center\"><tr><td>  </td><td><button name=\"1\" type=\"submit\" value=\"1\"><font size=\"5\">1</font></button></td></tr></table></form><form method=\"post\" action=/m2><table align=\"center\"><tr><td>  </td><td><button name=\"2\" type=\"submit\" value=\"1\"><font size=\"5\">2</font></button></td></tr></table></form></body></html>");
}
void handletao(){
  mango=0;
  type=2;
  esp8266_server.send(200,"text/html","<!DOCTYPE html><html><head><meta charset=\"UTF-8\"></meta><title>gulugulu饮料机点单</title></head><body><h2 align=\"center\">  </h2><br><br><br><br><br><br><h2 align=\"center\"><font size=\"10\">^_^ gulugulu饮料机点单界面 ^_^</font></h2><br><h3 align=\"center\"><font size=\"6\">请选择桃子份数</font></h3><form method=\"post\" action=/p0><table align=\"center\"><tr><td>  </td><td><button name=\"0\" type=\"submit\" value=\"1\"><font size=\"5\">0</font></button></td></tr></table></form><form method=\"post\" action=/p1><table align=\"center\"><tr><td>  </td><td><button name=\"1\" type=\"submit\" value=\"1\"><font size=\"5\">1</font></button></td></tr></table></form><form method=\"post\" action=/p2><table align=\"center\"><tr><td>  </td><td><button name=\"2\" type=\"submit\" value=\"1\"><font size=\"5\">2</font></button></td></tr></table></form></body></html>");
}
void handlem0(){
  mango=0;
  esp8266_server.send(200,"text/html","<!DOCTYPE html><html><head><meta charset=\"UTF-8\"></meta><title>gulugulu饮料机点单</title></head><body><h2 align=\"center\">  </h2><br><br><br><br><br><br><h2 align=\"center\"><font size=\"10\">^_^ gulugulu饮料机点单界面 ^_^</font></h2><br><h3 align=\"center\"><font size=\"6\">请选择西米份数</font></h3><form method=\"post\" action=/x0><table align=\"center\"><tr><td>  </td><td><button name=\"0\" type=\"submit\" value=\"1\"><font size=\"5\">0</font></button></td></tr></table></form><form method=\"post\" action=/x1><table align=\"center\"><tr><td>  </td><td><button name=\"1\" type=\"submit\" value=\"1\"><font size=\"5\">1</font></button></td></tr></table></form><form method=\"post\" action=/x2><table align=\"center\"><tr><td>  </td><td><button name=\"2\" type=\"submit\" value=\"1\"><font size=\"5\">2</font></button></td></tr></table></form></body></html>");
}
void handlem1(){
  mango=1;
  esp8266_server.send(200,"text/html","<!DOCTYPE html><html><head><meta charset=\"UTF-8\"></meta><title>gulugulu饮料机点单</title></head><body><h2 align=\"center\">  </h2><br><br><br><br><br><br><h2 align=\"center\"><font size=\"10\">^_^ gulugulu饮料机点单界面 ^_^</font></h2><br><h3 align=\"center\"><font size=\"6\">请选择西米份数</font></h3><form method=\"post\" action=/x0><table align=\"center\"><tr><td>  </td><td><button name=\"0\" type=\"submit\" value=\"1\"><font size=\"5\">0</font></button></td></tr></table></form><form method=\"post\" action=/x1><table align=\"center\"><tr><td>  </td><td><button name=\"1\" type=\"submit\" value=\"1\"><font size=\"5\">1</font></button></td></tr></table></form><form method=\"post\" action=/x2><table align=\"center\"><tr><td>  </td><td><button name=\"2\" type=\"submit\" value=\"1\"><font size=\"5\">2</font></button></td></tr></table></form></body></html>");
}
void handlem2(){
  mango=2;
  esp8266_server.send(200,"text/html","<!DOCTYPE html><html><head><meta charset=\"UTF-8\"></meta><title>gulugulu饮料机点单</title></head><body><h2 align=\"center\">  </h2><br><br><br><br><br><br><h2 align=\"center\"><font size=\"10\">^_^ gulugulu饮料机点单界面 ^_^</font></h2><br><h3 align=\"center\"><font size=\"6\">请选择西米份数</font></h3><form method=\"post\" action=/x0><table align=\"center\"><tr><td>  </td><td><button name=\"0\" type=\"submit\" value=\"1\"><font size=\"5\">0</font></button></td></tr></table></form><form method=\"post\" action=/x1><table align=\"center\"><tr><td>  </td><td><button name=\"1\" type=\"submit\" value=\"1\"><font size=\"5\">1</font></button></td></tr></table></form><form method=\"post\" action=/x2><table align=\"center\"><tr><td>  </td><td><button name=\"2\" type=\"submit\" value=\"1\"><font size=\"5\">2</font></button></td></tr></table></form></body></html>");
}
void handlep0(){
  peach=0;
  esp8266_server.send(200,"text/html","<!DOCTYPE html><html><head><meta charset=\"UTF-8\"></meta><title>gulugulu饮料机点单</title></head><body><h2 align=\"center\">  </h2><br><br><br><br><br><br><h2 align=\"center\"><font size=\"10\">^_^ gulugulu饮料机点单界面 ^_^</font></h2><br><h3 align=\"center\"><font size=\"6\">请选择西米份数</font></h3><form method=\"post\" action=/x0><table align=\"center\"><tr><td>  </td><td><button name=\"0\" type=\"submit\" value=\"1\"><font size=\"5\">0</font></button></td></tr></table></form><form method=\"post\" action=/x1><table align=\"center\"><tr><td>  </td><td><button name=\"1\" type=\"submit\" value=\"1\"><font size=\"5\">1</font></button></td></tr></table></form><form method=\"post\" action=/x2><table align=\"center\"><tr><td>  </td><td><button name=\"2\" type=\"submit\" value=\"1\"><font size=\"5\">2</font></button></td></tr></table></form></body></html>");
}
void handlep1(){
  peach=1;
  esp8266_server.send(200,"text/html","<!DOCTYPE html><html><head><meta charset=\"UTF-8\"></meta><title>gulugulu饮料机点单</title></head><body><h2 align=\"center\">  </h2><br><br><br><br><br><br><h2 align=\"center\"><font size=\"10\">^_^ gulugulu饮料机点单界面 ^_^</font></h2><br><h3 align=\"center\"><font size=\"6\">请选择西米份数</font></h3><form method=\"post\" action=/x0><table align=\"center\"><tr><td>  </td><td><button name=\"0\" type=\"submit\" value=\"1\"><font size=\"5\">0</font></button></td></tr></table></form><form method=\"post\" action=/x1><table align=\"center\"><tr><td>  </td><td><button name=\"1\" type=\"submit\" value=\"1\"><font size=\"5\">1</font></button></td></tr></table></form><form method=\"post\" action=/x2><table align=\"center\"><tr><td>  </td><td><button name=\"2\" type=\"submit\" value=\"1\"><font size=\"5\">2</font></button></td></tr></table></form></body></html>");
}
void handlep2(){
  peach=2;
  esp8266_server.send(200,"text/html","<!DOCTYPE html><html><head><meta charset=\"UTF-8\"></meta><title>gulugulu饮料机点单</title></head><body><h2 align=\"center\">  </h2><br><br><br><br><br><br><h2 align=\"center\"><font size=\"10\">^_^ gulugulu饮料机点单界面 ^_^</font></h2><br><h3 align=\"center\"><font size=\"6\">请选择西米份数</font></h3><form method=\"post\" action=/x0><table align=\"center\"><tr><td>  </td><td><button name=\"0\" type=\"submit\" value=\"1\"><font size=\"5\">0</font></button></td></tr></table></form><form method=\"post\" action=/x1><table align=\"center\"><tr><td>  </td><td><button name=\"1\" type=\"submit\" value=\"1\"><font size=\"5\">1</font></button></td></tr></table></form><form method=\"post\" action=/x2><table align=\"center\"><tr><td>  </td><td><button name=\"2\" type=\"submit\" value=\"1\"><font size=\"5\">2</font></button></td></tr></table></form></body></html>");
}
void handlex0(){
  ximi=0;
  esp8266_server.send(200,"text/html","<!DOCTYPE html><html><head><meta charset=\"UTF-8\"></meta><title>gulugulu饮料机点单</title></head><body><h2 align=\"center\">  </h2><br><br><br><br><br><br><h2 align=\"center\"><font size=\"10\">^_^ gulugulu饮料机点单界面 ^_^</font></h2><br><h3 align=\"center\"><font size=\"6\">请选择啵啵份数</font></h3><form method=\"post\" action=/b0><table align=\"center\"><tr><td>  </td><td><button name=\"0\" type=\"submit\" value=\"1\"><font size=\"5\">0</font></button></td></tr></table></form><form method=\"post\" action=/b1><table align=\"center\"><tr><td>  </td><td><button name=\"1\" type=\"submit\" value=\"1\"><font size=\"5\">1</font></button></td></tr></table></form><form method=\"post\" action=/b2><table align=\"center\"><tr><td>  </td><td><button name=\"2\" type=\"submit\" value=\"1\"><font size=\"5\">2</font></button></td></tr></table></form></body></html>");
}
void handlex1(){
  ximi=1;
  esp8266_server.send(200,"text/html","<!DOCTYPE html><html><head><meta charset=\"UTF-8\"></meta><title>gulugulu饮料机点单</title></head><body><h2 align=\"center\">  </h2><br><br><br><br><br><br><h2 align=\"center\"><font size=\"10\">^_^ gulugulu饮料机点单界面 ^_^</font></h2><br><h3 align=\"center\"><font size=\"6\">请选择啵啵份数</font></h3><form method=\"post\" action=/b0><table align=\"center\"><tr><td>  </td><td><button name=\"0\" type=\"submit\" value=\"1\"><font size=\"5\">0</font></button></td></tr></table></form><form method=\"post\" action=/b1><table align=\"center\"><tr><td>  </td><td><button name=\"1\" type=\"submit\" value=\"1\"><font size=\"5\">1</font></button></td></tr></table></form><form method=\"post\" action=/b2><table align=\"center\"><tr><td>  </td><td><button name=\"2\" type=\"submit\" value=\"1\"><font size=\"5\">2</font></button></td></tr></table></form></body></html>");
}
void handlex2(){
  ximi=2;
  esp8266_server.send(200,"text/html","<!DOCTYPE html><html><head><meta charset=\"UTF-8\"></meta><title>gulugulu饮料机点单</title></head><body><h2 align=\"center\">  </h2><br><br><br><br><br><br><h2 align=\"center\"><font size=\"10\">^_^ gulugulu饮料机点单界面 ^_^</font></h2><br><h3 align=\"center\"><font size=\"6\">请选择啵啵份数</font></h3><form method=\"post\" action=/b0><table align=\"center\"><tr><td>  </td><td><button name=\"0\" type=\"submit\" value=\"1\"><font size=\"5\">0</font></button></td></tr></table></form><form method=\"post\" action=/b1><table align=\"center\"><tr><td>  </td><td><button name=\"1\" type=\"submit\" value=\"1\"><font size=\"5\">1</font></button></td></tr></table></form><form method=\"post\" action=/b2><table align=\"center\"><tr><td>  </td><td><button name=\"2\" type=\"submit\" value=\"1\"><font size=\"5\">2</font></button></td></tr></table></form></body></html>");
}
void handleb0(){
  bobo=0;
  esp8266_server.send(200,"text/html","<!DOCTYPE html><html><head><meta charset=\"UTF-8\"></meta><title>gulugulu饮料机点单</title></head><body><h2 align=\"center\">  </h2><br><br><br><br><br><br><h2 align=\"center\"><font size=\"10\">^_^ gulugulu饮料机点单界面 ^_^</font></h2><br><h3 align=\"center\"><font size=\"6\">请选择糖度</font></h3><form method=\"post\" action=/s0><table align=\"center\"><tr><td>  </td><td><button name=\"0\" type=\"submit\" value=\"1\"><font size=\"5\">无糖</font></button></td></tr></table></form><form method=\"post\" action=/s1><table align=\"center\"><tr><td>  </td><td><button name=\"1\" type=\"submit\" value=\"1\"><font size=\"5\">半糖</font></button></td></tr></table></form><form method=\"post\" action=/s2><table align=\"center\"><tr><td>  </td><td><button name=\"2\" type=\"submit\" value=\"1\"><font size=\"5\">全糖</font></button></td></tr></table></form></body></html>");
}
void handleb1(){
  bobo=1;
  esp8266_server.send(200,"text/html","<!DOCTYPE html><html><head><meta charset=\"UTF-8\"></meta><title>gulugulu饮料机点单</title></head><body><h2 align=\"center\">  </h2><br><br><br><br><br><br><h2 align=\"center\"><font size=\"10\">^_^ gulugulu饮料机点单界面 ^_^</font></h2><br><h3 align=\"center\"><font size=\"6\">请选择糖度</font></h3><form method=\"post\" action=/s0><table align=\"center\"><tr><td>  </td><td><button name=\"0\" type=\"submit\" value=\"1\"><font size=\"5\">无糖</font></button></td></tr></table></form><form method=\"post\" action=/s1><table align=\"center\"><tr><td>  </td><td><button name=\"1\" type=\"submit\" value=\"1\"><font size=\"5\">半糖</font></button></td></tr></table></form><form method=\"post\" action=/s2><table align=\"center\"><tr><td>  </td><td><button name=\"2\" type=\"submit\" value=\"1\"><font size=\"5\">全糖</font></button></td></tr></table></form></body></html>");
}
void handleb2(){
  bobo=2;
  esp8266_server.send(200,"text/html","<!DOCTYPE html><html><head><meta charset=\"UTF-8\"></meta><title>gulugulu饮料机点单</title></head><body><h2 align=\"center\">  </h2><br><br><br><br><br><br><h2 align=\"center\"><font size=\"10\">^_^ gulugulu饮料机点单界面 ^_^</font></h2><br><h3 align=\"center\"><font size=\"6\">请选择糖度</font></h3><form method=\"post\" action=/s0><table align=\"center\"><tr><td>  </td><td><button name=\"0\" type=\"submit\" value=\"1\"><font size=\"5\">无糖</font></button></td></tr></table></form><form method=\"post\" action=/s1><table align=\"center\"><tr><td>  </td><td><button name=\"1\" type=\"submit\" value=\"1\"><font size=\"5\">半糖</font></button></td></tr></table></form><form method=\"post\" action=/s2><table align=\"center\"><tr><td>  </td><td><button name=\"2\" type=\"submit\" value=\"1\"><font size=\"5\">全糖</font></button></td></tr></table></form></body></html>");
}
void handles0(){
  sugar=0;
  esp8266_server.send(200,"text/html","<!DOCTYPE html><html><head><meta charset=\"UTF-8\"></meta><title>gulugulu饮料机点单</title></head><body><h2 align=\"center\">  </h2><br><br><br><br><br><br><h2 align=\"center\"><font size=\"10\">^_^ gulugulu饮料机点单界面 ^_^</font></h2><br><h3 align=\"center\"><font size=\"6\">请选择饮品温度</font></h3><form method=\"post\" action=/h0><table align=\"center\"><tr><td>  </td><td><button name=\"0\" type=\"submit\" value=\"1\"><font size=\"5\">常温</font></button></td></tr></table></form><form method=\"post\" action=/h1><table align=\"center\"><tr><td>  </td><td><button name=\"1\" type=\"submit\" value=\"1\"><font size=\"5\">热</font></button></td></tr></table></form></body></html>");
}
void handles1(){
  sugar=1;
  esp8266_server.send(200,"text/html","<!DOCTYPE html><html><head><meta charset=\"UTF-8\"></meta><title>gulugulu饮料机点单</title></head><body><h2 align=\"center\">  </h2><br><br><br><br><br><br><h2 align=\"center\"><font size=\"10\">^_^ gulugulu饮料机点单界面 ^_^</font></h2><br><h3 align=\"center\"><font size=\"6\">请选择饮品温度</font></h3><form method=\"post\" action=/h0><table align=\"center\"><tr><td>  </td><td><button name=\"0\" type=\"submit\" value=\"1\"><font size=\"5\">常温</font></button></td></tr></table></form><form method=\"post\" action=/h1><table align=\"center\"><tr><td>  </td><td><button name=\"1\" type=\"submit\" value=\"1\"><font size=\"5\">热</font></button></td></tr></table></form></body></html>");
}
void handles2(){
  sugar=2;
  esp8266_server.send(200,"text/html","<!DOCTYPE html><html><head><meta charset=\"UTF-8\"></meta><title>gulugulu饮料机点单</title></head><body><h2 align=\"center\">  </h2><br><br><br><br><br><br><h2 align=\"center\"><font size=\"10\">^_^ gulugulu饮料机点单界面 ^_^</font></h2><br><h3 align=\"center\"><font size=\"6\">请选择饮品温度</font></h3><form method=\"post\" action=/h0><table align=\"center\"><tr><td>  </td><td><button name=\"0\" type=\"submit\" value=\"1\"><font size=\"5\">常温</font></button></td></tr></table></form><form method=\"post\" action=/h1><table align=\"center\"><tr><td>  </td><td><button name=\"1\" type=\"submit\" value=\"1\"><font size=\"5\">热</font></button></td></tr></table></form></body></html>");
}
void handleh0(){
  heat=0;
  esp8266_server.send(200,"text/html","<!DOCTYPE html><html><head><meta charset=\"UTF-8\"></meta><title>gulugulu饮料机点单</title></head><body><h2 align=\"center\">  </h2><br><br><br><br><br><br><h2 align=\"center\"><font size=\"10\">^_^ gulugulu饮料机点单界面 ^_^</font></h2><br><h3 align=\"center\"><font size=\"6\">饮品制作中，请耐心等待</font></h3></body></html>");
  Serial.println(int_to_str(type,ximi,bobo,mango,peach,sugar,heat));
}
void handleh1(){
  heat=1;
  esp8266_server.send(200,"text/html","<!DOCTYPE html><html><head><meta charset=\"UTF-8\"></meta><title>gulugulu饮料机点单</title></head><body><h2 align=\"center\">  </h2><br><br><br><br><br><br><h2 align=\"center\"><font size=\"10\">^_^ gulugulu饮料机点单界面 ^_^</font></h2><br><h3 align=\"center\">饮品制作中，请耐心等待</h3></body></html>");
  Serial.println(int_to_str(type,ximi,bobo,mango,peach,sugar,heat));
}
void handleNotFound(){
  esp8266_server.send(404,"text/plain","404:Not Found");
}
