#ifndef NODE_MESH_H
#define NODE_MESH_H

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "time.h"
#include "mesh_sim/msg.h"
#include "mesh_sim/msg_request.h"

class nodeMesh
{
public:
  nodeMesh(ros::NodeHandle* nh);
  ~nodeMesh();

private:
  ros::NodeHandle *nh_;
  ros::Publisher bus_pub_;
  ros::Subscriber bus_sub_;
  ros::ServiceServer msg_srv_;
  ros::Timer timer_;

  void readParameters();
  void callBack(mesh_sim::msg msg);
  void timerCallBack(const ros::TimerEvent& event);
  bool serviceCallBack(mesh_sim::msg_request::Request &req, mesh_sim::msg_request::Response &res);

  std::vector<int> policy_;
  std::vector<float> delay_;
  std::vector<float> prob_;
  int id_;

};

#endif
