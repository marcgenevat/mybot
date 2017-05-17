#include <Servo.h> 
#include <ros.h>
#include <geometry_msgs/Twist.h>


Servo myservo;
ros::NodeHandle nh;

void teleop(const geometry_msgs::Twist& teleop_msg) {
  float servo_direction = teleop_msg.linear.x;
  
  if (servo_direction > 0) {
    myservo.write(0);
  }
  else if (servo_direction < 0) {
    myservo.write(180);
  }
  else {
    myservo.write(90);
  }
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &teleop);

void setup() {
  myservo.attach(2);
  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  
  nh.spinOnce();
  delay(1);
}
