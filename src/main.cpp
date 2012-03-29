#include <QApplication>
#include <QAction>
#include "main_window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName("Ufopak");
    app.setApplicationName("TrollEdit");
    app.setStartDragDistance(app.startDragDistance() * 2);

    // find the directory of the program
    QFileInfo program(argv[0]);
    QString path = program.absoluteDir().path();

    try {
    
        MainWindow w(path);
        w.show();
    
    //    w.newFile();
    //    w.open("../input/in.c"); // TEMP
    
        // open all files given as parameters
        for (int i = 1; i < argc; i++)
            w.open(argv[i]);
        
        return app.exec();
    }
    catch( char *str ) {
        qDebug() << "Caught exception on main function: " << str;
    } catch (...) {
        qDebug() << "Unknown error catch in main function";
    }
}
