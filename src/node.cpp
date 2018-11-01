#include "../include/node_mesh.h"

int main(int argc, char** argv)
{
  ros::init(argc, argv, "node");
  nodeMesh node_mesh(new ros::NodeHandle);

  ros::spin();
  ros::Rate loop(1);
  while (ros::ok())
  {
    ros::spinOnce();
    loop.sleep();
  }
  return 0;
}
