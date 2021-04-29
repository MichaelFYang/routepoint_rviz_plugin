#ifndef ROUTEPOINT_RVIZ_PLUGIN_WAYPOINT_TOOL_H
#define ROUTEPOINT_RVIZ_PLUGIN_WAYPOINT_TOOL_H

#include <sstream>
#include <ros/ros.h>
#include <QObject>

#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PointStamped.h>

#include "rviz/display_context.h"
#include "rviz/properties/string_property.h"
#include "rviz/default_plugin/tools/pose_tool.h"

namespace rviz
{
class StringProperty;

class RoutePointTool : public PoseTool
{
  Q_OBJECT
public:
  RoutePointTool();
  virtual ~RoutePointTool()
  {
  }
  virtual void onInitialize();

protected:
  virtual void odomHandler(const nav_msgs::Odometry::ConstPtr& odom);
  virtual void onPoseSet(double x, double y, double theta);

private Q_SLOTS:
  void updateTopic();

private:
  float vehicle_z;

  ros::NodeHandle nh_;
  ros::Subscriber sub_;
  ros::Publisher pub_;

  StringProperty* topic_property_;
};
}

#endif  // ROUTEPOINT_RVIZ_PLUGIN_WAYPOINT_TOOL_H
