#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

void imageCallback1(const sensor_msgs::ImageConstPtr& msg)
{
  try
  {
    cv::imshow("view1", cv_bridge::toCvShare(msg, "bgr8")->image);
    cv::waitKey(30);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
}

void imageCallback2(const sensor_msgs::ImageConstPtr& msg)
{
  try
  {
    cv::imshow("view2", cv_bridge::toCvShare(msg, "bgr8")->image);
    cv::waitKey(30);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "image_listener");
  ros::NodeHandle nh;
  cv::namedWindow("view1");
  cv::namedWindow("view2");

  image_transport::ImageTransport it(nh);
  image_transport::Subscriber sub1 = it.subscribe("camera1/image_raw", 1, imageCallback1);
  image_transport::Subscriber sub2 = it.subscribe("camera2/image_raw", 1, imageCallback2);
  ros::spin();
  cv::destroyWindow("view1");
  cv::destroyWindow("view2");
}