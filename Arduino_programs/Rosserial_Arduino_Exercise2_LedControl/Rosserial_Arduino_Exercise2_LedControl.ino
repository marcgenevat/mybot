#include <ArduinoHardware.h>
#include <ros.h>
#include <std_msgs/Empty.h>

ros::NodeHandle nh;
int estat = 0;

void messageCb(const std_msgs::Empty &toggle_msg) {
  if (estat == 1) {
    digitalWrite(13, LOW);  //Blink the led
    estat = 0;
  }
  else {
    digitalWrite(13, HIGH);  //Blink the led
    estat = 1;
  }
}

ros::Subscriber <std_msgs::Empty> sub("toggle_led", &messageCb);

void setup()
{
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{
  nh.spinOnce();
  delay(1);
}
