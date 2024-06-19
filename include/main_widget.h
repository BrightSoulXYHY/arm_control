#pragma once

#include <QWidget>
#include <QTimer>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QStringList>


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

public slots:
  void ros_timer_update();
  void pt_target_update();
  void pt_target_remove();
  void sim_plan_traj();
//   void switch_rviz();
//   void switch_vehicle();


private:

    void init_qt_connection();


    Ui::MainWidget *ui;
    QTimer *ros_timer = new QTimer(this);

    QRandomGenerator random_gen = QRandomGenerator();


    ros::NodeHandlePtr nh_;
    ros::Subscriber goal_sub_;

};

