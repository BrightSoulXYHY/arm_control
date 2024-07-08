#pragma once

#include <QWidget>
#include <QTimer>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QStringList>
#include <QDebug>

#include "ui_main.h"


#include <iostream>
#include <vector>
#include <map>


#include <ros/ros.h>
#include <moveit_msgs/MoveGroupActionGoal.h>

#include <std_msgs/String.h>


#include "bs_list_item.h"





QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

    void show_no_master();
    void show_pt_target_update_error();

    void init_ros();

    // void goalCallback(const std_msgs::String::ConstPtr& msg);
    void goalCallback(const moveit_msgs::MoveGroupActionGoal::ConstPtr& msg);
    void mcsTcpPoseCallback(const geometry_msgs::PoseStamped::ConstPtr& msg);
    void mcsRdPoseCallback(const geometry_msgs::PoseStamped::ConstPtr& msg);

public slots:
  void ros_timer_update();

  void pt_target_update();
  void pt_target_remove();

  void rviz_pt_update();
  void mcs_pt_update();

  void sim_plan_traj();
//   void switch_rviz();
//   void switch_vehicle();


private:

    void init_qt_connection();
    void taele_line_update(Pose pose);

    Ui::MainWidget *ui;
    QTimer *ros_timer = new QTimer(this);

    QRandomGenerator random_gen = QRandomGenerator();


    ros::NodeHandlePtr nh_;
    ros::Subscriber goal_sub_;
    ros::Subscriber rviz_pose_sub_;
    ros::Subscriber mcs_tcp_pose_sub_;
    ros::Subscriber mcs_rd_pose_sub_;

    Pose rviz_pose_tgt_;
    Pose mcs_pose_tgt_;

};

