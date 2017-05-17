#include <Servo.h> 
#include <ros.h>
#include <geometry_msgs/Twist.h>


Servo servo_dreta;
Servo servo_esquerra;
ros::NodeHandle nh;

int CW = 180;
int CCW = 0;
int STOP = 90;

void endavant() {
  servo_dreta.write(CW);
  servo_esquerra.write(CCW);
}

void enrere() {
  servo_dreta.write(CCW);
  servo_esquerra.write(CW);
}

void gir_dreta() {
  servo_dreta.write(CCW);
  servo_esquerra.write(CCW);
}

void gir_esquerra() {
  servo_dreta.write(CW);
  servo_esquerra.write(CW);
}

void Stop() {
  servo_dreta.write(STOP);
  servo_esquerra.write(STOP);
}

void teleop(const geometry_msgs::Twist& teleop_msg) {
  float robot_linear = teleop_msg.linear.x;
  float robot_angular = teleop_msg.angular.z;
  
  if (robot_linear > 0) {
    endavant();
  }
  else if (robot_linear < 0) {
    enrere();
  }
  else if (robot_angular > 0) {
    gir_esquerra();
  }
  else if (robot_angular < 0) {
    gir_dreta();
  }
  else {
    Stop();
  }
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &teleop);

void setup() {
  servo_dreta.attach(2);
  servo_esquerra.attach(3);
  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  
  nh.spinOnce();
  delay(1);
}
