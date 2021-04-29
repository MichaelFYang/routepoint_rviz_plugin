#include "routepoint_tool.h"

namespace rviz
{
RoutePointTool::RoutePointTool()
{
  shortcut_key_ = 'w';

  topic_property_ = new StringProperty("Topic", "routepoint", "The topic on which to publish route waypionts for dynamic route planner.",
                                       getPropertyContainer(), SLOT(updateTopic()), this);
}

void RoutePointTool::onInitialize()
{
  PoseTool::onInitialize();
  setName("Routepoint");
  updateTopic();
  vehicle_z = 0;
}

void RoutePointTool::updateTopic()
{
  sub_ = nh_.subscribe<nav_msgs::Odometry> ("/state_estimation", 5, &RoutePointTool::odomHandler, this);
  pub_ = nh_.advertise<geometry_msgs::PointStamped>("/route_point", 5);
}

void RoutePointTool::odomHandler(const nav_msgs::Odometry::ConstPtr& odom)
{
  vehicle_z = odom->pose.pose.position.z;
}

void RoutePointTool::onPoseSet(double x, double y, double theta)
{
  geometry_msgs::PointStamped waypoint;
  waypoint.header.frame_id = "map";
  waypoint.header.stamp = ros::Time::now();
  waypoint.point.x = x;
  waypoint.point.y = y;
  waypoint.point.z = vehicle_z;

  pub_.publish(waypoint);
  usleep(10000);
  pub_.publish(waypoint);
}
}  // end namespace rviz

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(rviz::RoutePointTool, rviz::Tool)
