#pragma once

#include <QWidget>
#include <QTimer>
// #include <QStringListModel>
#include <QMessageBox>


#include <QRandomGenerator>


#include <iostream>
#include <vector>



#include "ui_main.h"

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



public slots:
  void pt_target_update();
  void pt_target_remove();
  void sim_plan_traj();
//   void switch_rviz();
//   void switch_vehicle();


private:

    void init_qt_connection();


    Ui::MainWidget *ui;

    QRandomGenerator random_gen = QRandomGenerator();

    // QStringListModel logging_model;

};

