#include "main_widget.h"

#include <QApplication>
#include <QFile>
// #include <QIcon>



const char version_text[8+1] =
{
   // YY year
   __DATE__[7], __DATE__[8],
   __DATE__[9], __DATE__[10],

   // First month letter, Oct Nov Dec = '1' otherwise '0'
   (__DATE__[0] == 'O' || __DATE__[0] == 'N' || __DATE__[0] == 'D') ? '1' : '0',
   
   // Second month letter
   (__DATE__[0] == 'J') ? ( (__DATE__[1] == 'a') ? '1' :       // Jan, Jun or Jul
                            ((__DATE__[2] == 'n') ? '6' : '7') ) :
   (__DATE__[0] == 'F') ? '2' :                                // Feb 
   (__DATE__[0] == 'M') ? (__DATE__[2] == 'r') ? '3' : '5' :   // Mar or May
   (__DATE__[0] == 'A') ? (__DATE__[1] == 'p') ? '4' : '8' :   // Apr or Aug
   (__DATE__[0] == 'S') ? '9' :                                // Sep
   (__DATE__[0] == 'O') ? '0' :                                // Oct
   (__DATE__[0] == 'N') ? '1' :                                // Nov
   (__DATE__[0] == 'D') ? '2' :                                // Dec
   0,

   // First day letter, replace space with digit
   __DATE__[4]==' ' ? '0' : __DATE__[4],

   // Second day letter
   __DATE__[5],

  '\0'
};



int main(int argc, char *argv[])
{
    std::cout << "build_date: " << version_text << std::endl;
    
    QApplication a(argc, argv);
    
    QFile qss(":/res/style.qss");
	qss.open(QFile::ReadOnly);
	a.setStyleSheet(qss.readAll());
	qss.close();

     
    // ros::NodeHandle nh_;

    MainWidget w;
    
    // QIcon icon(":/res/icon.png");
    // w.setWindowIcon(icon);
    
    w.show();
    // if ( !ros::master::check() ) 
    // {   
    //     w.show_no_master();
    //     return -1;
	// }
    // std::cout << "ros master ok!" << std::endl;
    // w.init_ros();
    // w.init_rviz_show();
    return a.exec();
}
