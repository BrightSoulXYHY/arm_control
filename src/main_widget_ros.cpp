#include "main_widget.h"


void MainWidget::show_no_master()
{
    QMessageBox msgBox;
	msgBox.setText("Couldn't find the ros master.");
	msgBox.exec();
    close();
}

void MainWidget::init_ros()
{
    ros::start();
    // ROS相关的函数和变量
    
    nh_.reset(new ros::NodeHandle("~"));
    // goal_sub_ = nh_->subscribe<std_msgs::String>("/chatter", 10, &MainWidget::goalCallback, this);
    // goal_sub_ = nh_->subscribe<std_msgs::String>("chatter", 10, &MainWidget::goalCallback, this);
    goal_sub_ = nh_->subscribe<moveit_msgs::MoveGroupActionGoal>("/move_group/goal", 10, &MainWidget::goalCallback, this);

    // 10ms for 100Hz 
    ros_timer->start(10);
}

void MainWidget::ros_timer_update()
{
    // std::cout << "ros_timer_update" << std::endl;
    if(ros::ok())
    {
        ros::spinOnce();
        // std::cout << "ros::spinOnce()" << std::endl;

        // update_vehicle();
    }
    else
    {
        QApplication::quit();
    }
}




// void MainWidget::goalCallback(const std_msgs::String::ConstPtr& msg)
// {
//     ROS_INFO("I heard: [%s]", msg->data.c_str());
// }


void MainWidget::goalCallback(const moveit_msgs::MoveGroupActionGoal::ConstPtr& msg)
{
    std::map<std::string,float> joint_map;
    auto joint_constraints = msg->goal.request.goal_constraints[0].joint_constraints;
    for (auto joint_constraint:joint_constraints)
    {
        joint_map[joint_constraint.joint_name] = joint_constraint.position;
    }
    // [ INFO] [1718673795.899137168]: [shoulder_pan_joint]: -2.7559
    // [ INFO] [1718673795.899189810]: [shoulder_lift_joint]: -2.5845
    // [ INFO] [1718673795.899201810]: [elbow_joint]: -0.6878
    // [ INFO] [1718673795.899210310]: [wrist_1_joint]: 0.1308
    // [ INFO] [1718673795.899217995]: [wrist_2_joint]: 1.3140
    // [ INFO] [1718673795.899236324]: [wrist_3_joint]: 3.1418


    ROS_INFO("[%s]: %.4f", "shoulder_pan_joint", joint_map["shoulder_pan_joint"]); 
    ROS_INFO("[%s]: %.4f", "shoulder_lift_joint", joint_map["shoulder_lift_joint"]); 


    // TODO:需要一个将关节数据转换为xyz,quat形式的路点

    Pose pose;
    pose.px = random_gen.generateDouble();
    pose.py = random_gen.generateDouble();
    pose.pz = random_gen.generateDouble();
    auto* item = new BSListWidgetItem(pose);
    ui->ptListWidget->addItem(item);
    
}
