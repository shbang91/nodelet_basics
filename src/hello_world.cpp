/*
Author: Addison Sears-Collins

This ROS nodelet will subscribe to a topic (/ros_in).
It will then receive a message via that topic and then
republish that message to another topic (/ros_out).

Date: 6/19/2020

ROS Version: ROS Noetic Ninjemys
*/

// Add the necessary includes
#include "controller/draco_controller/draco_interface.hpp"
#include <nodelet/nodelet.h>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <stdio.h>

namespace nodelet_basics {
/*********
 * Nodelet
 **********/

// This code here means the class needs to inherit from
// nodelet::Nodelet
class Hello_World : public nodelet::Nodelet {

public:
  Hello_World() { rpc_interface_ = new DracoInterface(); }
  ~Hello_World() { delete rpc_interface_; }

private:
  // The onInit method is called by nodelet manager.
  // It is responsible for initializing the nodelet.
  virtual void onInit() {
    // Create a NodeHandle object
    ros::NodeHandle &private_nh = getPrivateNodeHandle();
    NODELET_DEBUG("Initializing nodelet...");

    // Create a publisher topic
    pub = private_nh.advertise<std_msgs::String>("ros_out", 10);

    // Create a subscriber topic
    sub = private_nh.subscribe("ros_in", 10, &Hello_World::callback, this);
  }

  ros::Publisher pub;
  ros::Subscriber sub;

  DracoInterface *rpc_interface_;

  // Display messages from /ros_in topic to the terminal window.
  // Publish to /ros_out topic
  void callback(const std_msgs::String::ConstPtr &input) {

    std_msgs::String output;
    output.data = input->data;
    NODELET_DEBUG("msg data = %s", output.data.c_str());
    ROS_INFO("msg data = %s", output.data.c_str());
    pub.publish(output);
  }
  // Export the Hello_World class as a plugin using the
  // PLUGINLIB_EXPORT_CLASS macro.
};
} // namespace nodelet_basics

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(nodelet_basics::Hello_World, nodelet::Nodelet);
