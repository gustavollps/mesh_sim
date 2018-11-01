#include "../../include/node_mesh.h"

nodeMesh::nodeMesh(ros::NodeHandle* nh)
{
  nh_ = nh;
  bus_sub_ = nh_->subscribe<mesh_sim::msg>("bus", 100, &nodeMesh::callBack, this);
  bus_pub_ = nh_->advertise<mesh_sim::msg>("bus", 100);
  //timer_ = nh_->createTimer(ros::Duration(0.1),&nodeMesh::timerCallBack,this, true);

  std::string node_name = ros::this_node::getName();
  node_name = (node_name.substr(5, node_name.length() - 1));
  std::string::size_type sz;
  id_ = std::stoi(node_name, &sz);
  std::cout << id_ << std::endl;
  std::string str("/msgRequest" + std::to_string(id_));
  msg_srv_ = nh_->advertiseService(str.c_str(), &nodeMesh::serviceCallBack, this);
  readParameters();
}

nodeMesh::~nodeMesh()
{
}

void nodeMesh::readParameters()
{
  std::string policy_str("policy" + std::to_string(id_));
  nh_->getParam(policy_str, policy_);

  std::string prob_str("prob" + std::to_string(id_));
  nh_->getParam(prob_str, prob_);

  std::string delay_str("ping" + std::to_string(id_));
  nh_->getParam(delay_str, delay_);
}

void nodeMesh::callBack(mesh_sim::msg msg)
{
  ROS_DEBUG("callback on %d type %d sender %d",id_,msg.type,msg.sender);
  if (msg.type == 0)  // real msg
  {
    if (msg.id == id_)
    {
      usleep(12000);
      mesh_sim::msg msg_new = msg;
      mesh_sim::msg res_msg = msg;
      if (msg.goal == id_)
      {
        ros::Duration ping = ros::Time::now() - msg.time_stamp;
        ROS_INFO("I got the message!\nNODE: %d\t PING: %f", id_, ping.toSec());
      }
      else
      {
        ROS_INFO("on node %d to %d (goal %d)", id_, policy_[msg.goal - 1], msg.goal);        
        msg_new.id = policy_[msg.goal - 1];        
        msg_new.sender = id_;        
        bus_pub_.publish(msg_new);
      }
#ifndef RESP
        res_msg.type = 1; //send confirmation
        res_msg.sender = id_;
        res_msg.id = msg.sender;
        ROS_ERROR("Response sent. Node %d to %d", id_, msg.sender);
        if(msg.goal != id_){
          timer_ = nh_->createTimer(ros::Duration(0.1),&nodeMesh::timerCallBack,this, true);
        }
        bus_pub_.publish(res_msg);
#endif
    }
  }
  else if (msg.type == 1)  // receive confirmation
  {
    if(msg.id == policy_[msg.goal-1] && id_ != msg.goal){
      //receive confirmation
      ROS_WARN("CONFIRMED on %d - msg %d %d %d",id_, msg.id, msg.sender, msg.goal);
      timer_.stop();
    }else
    {
      //ROS_WARN("CONFIRMATION MSG from %d on node %d",msg.sender, id_);
    }
  }
}

void nodeMesh::timerCallBack(const ros::TimerEvent& event)
{
  ROS_FATAL("NO CONFIRMATION on %d",id_);

}

bool nodeMesh::serviceCallBack(mesh_sim::msg_request::Request& req, mesh_sim::msg_request::Response& res)
{
  mesh_sim::msg msg;
  msg.data = req.data;
  msg.goal = req.goal;
  msg.time_stamp = ros::Time::now();
  msg.id = policy_[msg.goal-1];
  msg.sender = id_;
  msg.type = 0;
  ROS_INFO("on node %d to %d (goal %d)", id_, policy_[msg.goal - 1], msg.goal);
  bus_pub_.publish(msg);
  return true;
}
