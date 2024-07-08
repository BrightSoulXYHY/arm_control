#include "main_widget.h"

#include <QDebug>

MainWidget::MainWidget(QWidget *parent) 
    : QWidget(parent) , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    init_qt_connection();


    // 初始化表格的
    int rowCount = ui->dataTable->rowCount();
    int columnCount = ui->dataTable->columnCount();
    qDebug() << "rowCount:" << rowCount;
    qDebug() << "columnCount:" << columnCount;
    for (int row = 0; row < rowCount; ++row) 
    {
        for (int column = 0; column < columnCount; ++column) 
        {
            // ui->dataTable->item(row,column)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            auto* item = new QTableWidgetItem(QString::asprintf("%.4f",0));
            item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            ui->dataTable->setItem(row, column, item);
        }
    }




    // std::map<std::string,std::string> remappings;
	// remappings["__master"] = "http://127.0.0.1:11311/";
	// remappings["__hostname"] = "127.0.0.1";

    int argc = 0; char **argv = NULL;
	ros::init(argc, argv, "bs_arm_control_node");
     

}

MainWidget::~MainWidget(){delete ui;}


void MainWidget::init_qt_connection()
{
    connect(ros_timer, SIGNAL(timeout()), this, SLOT(ros_timer_update()));

    connect(ui->ptAddButton, SIGNAL(clicked()), this, SLOT(pt_target_update()));
    connect(ui->ptDelButton, SIGNAL(clicked()), this, SLOT(pt_target_remove()));

    connect(ui->simAddRvizButton, SIGNAL(clicked()), this, SLOT(rviz_pt_update()));
    connect(ui->simAddMcsButton, SIGNAL(clicked()), this, SLOT(mcs_pt_update()));


    connect(ui->simPlanButton, SIGNAL(clicked()), this, SLOT(sim_plan_traj()));
    // connect(ui->mapSwitchBtn, SIGNAL(clicked()), this, SLOT(switch_rviz()));
    // connect(ui->vehicleSwitchBtn, SIGNAL(clicked()), this, SLOT(switch_vehicle()));

}






void MainWidget::pt_target_update()
{
    // float px,py,pz;
    // float qw,qx,qy,qz;
    std::vector<float> numbers;

    auto input_text = ui->ptLineEdit->text();
    QStringList input_parts = input_text.split(",", QString::SkipEmptyParts);
    if(input_parts.size() != 7)
    {
        show_pt_target_update_error();
        return;
    }
    else
    {
        for(auto input_part:input_parts)
        {
            bool input_valid;
            float number = input_part.trimmed().toFloat(&input_valid);
            if(!input_valid)
            {
                show_pt_target_update_error();
                break;
            }
            numbers.push_back(number);
        }
    }

    Pose pose;
    pose.px = numbers[0];
    pose.py = numbers[1];
    pose.pz = numbers[2];
    pose.qw = numbers[3];
    pose.qx = numbers[4];
    pose.qy = numbers[5];
    pose.qz = numbers[6];

    auto* item = new BSListWidgetItem(pose);
    ui->ptListWidget->addItem(item);
}

void MainWidget::show_pt_target_update_error()
{
    QMessageBox msgBox;
	msgBox.setText("输入格式不正确！");
	msgBox.exec();
}


void MainWidget::pt_target_remove()
{
    QListWidgetItem* item = ui->ptListWidget->currentItem();
    ui->ptListWidget->removeItemWidget(item);
    delete item;
}


void MainWidget::rviz_pt_update()
{
    // 添加来自rviz的路点
    auto* item = new BSListWidgetItem(rviz_pose_tgt_);
    ui->ptListWidget->addItem(item);
}


void MainWidget::mcs_pt_update()
{
    // 添加来自mcs的路点
    auto* item = new BSListWidgetItem(mcs_pose_tgt_);
    ui->ptListWidget->addItem(item);
}


