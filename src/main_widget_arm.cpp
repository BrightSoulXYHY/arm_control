#include "main_widget.h"



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
            pt_pose.qy,
            pt_pose.qz
        );
    }
    
}