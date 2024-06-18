#pragma once
#include <QListWidgetItem>
#include <QString>

#include "bs_common.h"



class BSListWidgetItem : public QListWidgetItem
{
public:
    BSListWidgetItem(const Pose &pose, QListWidget *parent = nullptr)
        : QListWidgetItem(parent), pt_pose(pose)
    {
        auto text = QString::asprintf(
            "%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f", 
            pt_pose.px,
            pt_pose.py,
            pt_pose.pz,
            pt_pose.qw,
            pt_pose.qx,
            pt_pose.qz,
            pt_pose.qy
        );
        setText(text);
    };

    Pose getPose() const { return pt_pose; }

private:
    Pose pt_pose;
};

