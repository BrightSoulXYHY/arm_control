#include "main_widget.h"

#include <QDebug>

MainWidget::MainWidget(QWidget *parent) 
    : QWidget(parent) , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    init_qt_connection();



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
            // qDebug() << "item:" << item->text();

            // item->setText(QString::asprintf("%.4f",0));
        }
    }



    // load_config();


    // ros_timer = new QTimer(this);

    // std::map<std::string,std::string> remappings;
	// remappings["__master"] = yaml_cfg["master_url"].as<std::string>();
	// remappings["__hostname"] = yaml_cfg["ros_ip"].as<std::string>();
	// ros::init(remappings,"bs_arm_control_ros_node");
     

}

MainWidget::~MainWidget(){delete ui;}


void MainWidget::init_qt_connection()
{
    connect(ui->ptAddButton, SIGNAL(clicked()), this, SLOT(pt_target_update()));
    connect(ui->ptDelButton, SIGNAL(clicked()), this, SLOT(pt_target_remove()));
    connect(ui->simPlanButton, SIGNAL(clicked()), this, SLOT(sim_plan_traj()));
    // connect(ui->mapSwitchBtn, SIGNAL(clicked()), this, SLOT(switch_rviz()));
    // connect(ui->vehicleSwitchBtn, SIGNAL(clicked()), this, SLOT(switch_vehicle()));

}


// void MainWidget::show_no_master()
// {
//     QMessageBox msgBox;
// 	msgBox.setText("Couldn't find the ros master.");
// 	msgBox.exec();
//     close();
// }



void MainWidget::pt_target_update()
{
    Pose pose;
    pose.px = random_gen.generateDouble();
    pose.py = random_gen.generateDouble();
    pose.pz = random_gen.generateDouble();
    auto* item = new BSListWidgetItem(pose);
    ui->ptListWidget->addItem(item);
}



void MainWidget::pt_target_remove()
{
    QListWidgetItem* item = ui->ptListWidget->currentItem();
    ui->ptListWidget->removeItemWidget(item);
    delete item;
}


void MainWidget::sim_plan_traj()
{
    std::vector<Pose> pt_poses;
    for (int i = 0; i < ui->ptListWidget->count(); ++i) 
    {
        auto *cnt_item = ui->ptListWidget->item(i);
        auto *bs_item = dynamic_cast<BSListWidgetItem *>(cnt_item);

        pt_poses.push_back(bs_item->getPose());
    }
    

    for ( auto pt_pose:pt_poses )
    {
       qDebug() << QString::asprintf(
            "%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f", 
            pt_pose.px,
            pt_pose.py,
            pt_pose.pz,
            pt_pose.qw,
            pt_pose.qx,
            pt_pose.qz,
            pt_pose.qy
        );
    }
    
}
