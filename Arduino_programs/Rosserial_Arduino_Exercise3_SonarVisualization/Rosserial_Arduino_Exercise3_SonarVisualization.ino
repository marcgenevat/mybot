#include <BitbloqUS.h>
#include <ros.h>
#include <sensor_msgs/Range.h>

US mysonar(13, 12); //trigger(13) echo(12)
ros::NodeHandle  nh;

sensor_msgs::Range range_msg;
ros::Publisher pub_range( "/ultrasound", &range_msg);

char frameid[] = "/ultrasound_link";

void setup()
{
  nh.initNode();
  nh.advertise(pub_range);
  
  range_msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msg.header.frame_id =  frameid;
  range_msg.field_of_view = (20*3.1415)/180;  // 20 graus d'obertura
  range_msg.min_range = 0.02; //2cm
  range_msg.max_range = 4;    //400cm
}

void loop()
{
  
  //publish the sonar value every 50 milliseconds

    range_msg.range = mysonar.read()/100; //passem a m
    range_msg.header.stamp = nh.now();
    pub_range.publish(&range_msg);
    delay(50);
  
    nh.spinOnce();
}
