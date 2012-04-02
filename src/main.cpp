/**
 * @Title main.cpp
 * ---------------------------------------------------------------------------
 * @Description Contains the defintion of class Main.
 * @Author Team 04 Ufopak + Team 10 Innovators
 */

#include <QApplication>
#include <QAction>
#include "main_window.h"
#include <QString>

extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
    int luaopen_lpeg (lua_State *L);
}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName("Innovators");
    app.setApplicationName("TrollEdit");
    app.setStartDragDistance(app.startDragDistance() * 2);

    // set splashScreen
    QPixmap pixmap(":/splash");
    QSplashScreen splashScreen(pixmap,Qt::WindowStaysOnTopHint);

    // find the directory of the program
    QFileInfo program(argv[0]);
    QString path = program.absoluteDir().path();

    MainWindow w(path);
    w.setWindowOpacity(0);
    
    splashScreen.show();
    w.show();

    QTimer::singleShot(1000, &splashScreen, SLOT(close()));
    QTimer::singleShot(1000, &w, SLOT(wInit()));
    
    // open all files given as parameters

    //    w.newFile();
    //    w.open("../input/in.c"); // TEMP
    // open all files given as parameters
    for (int i = 1; i < argc; i++)
        w.open(argv[i]);

    return app.exec();
}

void MainWindow::wInit()
 {
    setWindowOpacity(1);
 }
