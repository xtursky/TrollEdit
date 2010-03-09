#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    documentTabs = new DocumentTabs(this);
    setCentralWidget(documentTabs);

    //readSettings();

    // single instance; scenes has only pointers set to this analyzer
    //cAnalyzer = new Analyzer("grammars/c_grammar.lua");

    createActions();
    createMenus();
    createToolBars();

    updateRecentFileActions();
}

void MainWindow::createActions()
{
    // new file
    newAction = new QAction(tr("&New"), this);
    newAction->setShortcut(tr("CTRL+N"));
    newAction->setToolTip(tr("Create a new file"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));
    addAction(newAction);

    // open
    openAction = new QAction(tr("&Open..."), this);
    openAction->setShortcut(tr("CTRL+O"));
    openAction->setToolTip(tr("Open an existing file"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    // save
    saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcut(tr("CTRL+S"));
    saveAction->setToolTip(tr("Save the file to disk"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    // save as
    saveAsAction = new QAction(tr("Save &As..."), this);
    saveAsAction->setShortcut(tr("CTRL+A"));
    saveAsAction->setToolTip(tr("Save the file as..."));
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

    // close
    closeAction = new QAction(tr("&Close"), this);
    closeAction->setToolTip(tr("Close the active file"));
    closeAction->setShortcut(tr("CTRL+W"));
    connect(closeAction, SIGNAL(triggered()), this, SLOT(closeTab()));

    // recent files
    for (int i = 0; i < MaxRecentFiles; ++i) {
         recentFileActions[i] = new QAction(this);
         recentFileActions[i]->setVisible(false);
         connect(recentFileActions[i], SIGNAL(triggered()),
            this, SLOT(openRecentFile()));
     }

    // exit
    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("CTRL+Q"));
    exitAction->setToolTip(tr("Quit the application. Prompts to save files"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    // cut
    cutAction = new QAction(tr("Cu&t"), this);
    cutAction->setShortcut(tr("CTRL+X"));
    cutAction->setToolTip(tr("Cut the selection to the clipboard"));
    // connect(cutAction, SIGNAL(triggered()), xxx, SLOT(yyy)); ???

    // copy
    copyAction = new QAction(tr("&Copy"), this);
    copyAction->setShortcut(tr("CTRL+C"));
    copyAction->setToolTip(tr("Copy the selection to the clipboard"));
    // connect(copyAction, SIGNAL(triggered()), xxx, SLOT(yyy)); ???

    // paste
    pasteAction = new QAction(tr("&Paste"), this);
    pasteAction->setShortcut(tr("CTRL+V"));
    pasteAction->setToolTip(tr("Insert clipboard contents"));
    // connect(pasteAction, SIGNAL(triggered()), xxx, SLOT(yyy)); ???

    // delete
    deleteAction = new QAction(tr("&Delete"), this);
    deleteAction->setShortcut(tr("Del"));
    deleteAction->setToolTip(tr("Erase the next character or the selection"));
    // connect(deleteAction, SIGNAL(triggered()), xxx, SLOT(yyy)); ???

    // styles settings
    stylesAction = new QAction(tr("Block &Settings"), this);
    stylesAction->setToolTip(tr("Set style for blocks"));
    connect(stylesAction, SIGNAL(triggered()), this, SLOT(settings()));

    // help
    helpAction = new QAction(tr("&Help"), this);
    helpAction->setToolTip(tr("Show application's help"));
    connect(helpAction, SIGNAL(triggered()), this, SLOT(help()));

    // about
    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setToolTip(tr("Show application's about box"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    // about Qt
    aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setStatusTip(tr("Show the Qt library�s About box"));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    // text bold
    textBoldAction = new QAction(QIcon(":/res/textbold.png"), tr("&Bold"), this);
    textBoldAction->setShortcut(tr("CTRL+B"));
    QFont bold;
    bold.setBold(true);
    textBoldAction->setFont(bold);
    connect(textBoldAction, SIGNAL(triggered()), this, SLOT(handleFontChange()));
    textBoldAction->setCheckable(true);

    // text italic
    textItalicAction = new QAction(QIcon(":/res/textitalic.png"), tr("&Italic"), this);
    textBoldAction->setShortcut(tr("CTRL+I"));
    QFont italic;
    italic.setItalic(true);
    textItalicAction->setFont(italic);
    connect(textItalicAction, SIGNAL(triggered()), this, SLOT(handleFontChange()));
    textItalicAction->setCheckable(true);

    // text underline
    textUnderlineAction = new QAction(QIcon(":/res/textunder.png"), tr("&Underline"), this);
    textBoldAction->setShortcut(tr("CTRL+U"));
    QFont underline;
    underline.setUnderline(true);
    textUnderlineAction->setFont(underline);
    connect(textUnderlineAction, SIGNAL(triggered()), this, SLOT(handleFontChange()));
    textUnderlineAction->setCheckable(true);

    // analyze text
    analyzeAction = new QAction(tr("Analyze"), this);
//    analyzeAction->setShortcut(tr("CTRL+Q"));
//    analyzeAction->setToolTip(tr("Quit the application. Prompts to save files"));
    connect(analyzeAction, SIGNAL(triggered()), this, SLOT(analyzeTab()));
}

void MainWindow::createMenus()
{
    // file menu
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(closeAction);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    separatorAction = fileMenu->addSeparator();
    for (int i = 0; i < MaxRecentFiles; ++i)
        fileMenu->addAction(recentFileActions[i]);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    // edit menu
    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addAction(deleteAction);

    // options menu
    optionsMenu = menuBar()->addMenu(tr("&Options"));
    optionsMenu->addAction(stylesAction);

    // help menu
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(helpAction);
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
}

void MainWindow::createToolBars()
{
    // format toolbar
    formatToolBar = addToolBar(tr("Format"));
    formatToolBar->addAction(textBoldAction);
    formatToolBar->addAction(textItalicAction);
    formatToolBar->addAction(textUnderlineAction);
    formatToolBar->addAction(analyzeAction);
}

void MainWindow::newFile()
{
    DocumentScene *scene = new DocumentScene();
    scene->setSceneRect(documentTabs->rect());
    //scene->analyzer = cAnalyzer;    // in future give scene appropriate analyzer when filetype is known
    QGraphicsView *view = new QGraphicsView(scene);
    documentTabs->addTab(view, tr("Untitled %1").arg(DocumentTabs::documentNumber)); // nejde nieco ako pri title bare, ze indikujeme hviezdickou neulozene zmeny?
    documentTabs->setCurrentIndex(documentTabs->count() - 1);    
    view->setFocus(Qt::MouseFocusReason);// focus on view and then focus on mainBlock is working
    DocumentTabs::documentNumber++;
    //connect(this, SIGNAL(apply(QBrush*,QPen*)), scene, SLOT(applyChanges(QBrush*,QPen*)));
    //applyChanges();
}

void MainWindow::open()
{
    QString fileFilters = tr("C Header file (*.h)\n" "C Source file (*.c)\n" "All files (*)");    // add support for other file types
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), ".", fileFilters);

    if (!fileName.isEmpty()) {
        QGraphicsView *view = static_cast<QGraphicsView*>(documentTabs->currentWidget());
        DocumentScene *scene = static_cast<DocumentScene*>(view->scene());

        if (scene->modified) {
            newFile();
            DocumentTabs::documentNumber--;
        }

        load(fileName);
    }
}

void MainWindow::load(QString fileName)
{
   /* QGraphicsView *view = static_cast<QGraphicsView*>(documentTabs->currentWidget());
    DocumentScene *scene = static_cast<DocumentScene*>(view->scene());
    view->setObjectName(fileName);
    documentTabs->setTabText(documentTabs->currentIndex(), strippedName(fileName));
    setCurrentFile(documentTabs->currentIndex());
    scene->loadFile(fileName);*/
}

bool MainWindow::save()
{
    /*QGraphicsView *view = static_cast<QGraphicsView*>(documentTabs->currentWidget());
    DocumentScene *scene = static_cast<DocumentScene*>(view->scene());
    if(currentFile.isEmpty())
      return saveAs();
    else
      scene->saveFile(currentFile);
    return true;*/
    return false;//temp
}

bool MainWindow::saveAs()
{
   /* QString fileFilters = tr("C Header file (*.h)\n" "C Source file (*.c)\n" "All files (*)");    // add support for other file types
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save file as..."), ".", fileFilters);
    QGraphicsView *view = static_cast<QGraphicsView*>(documentTabs->currentWidget());
    DocumentScene *scene = static_cast<DocumentScene*>(view->scene());

    if (!fileName.isEmpty())
    {
        scene->saveFile(fileName);
        return true;
    } else*/
        return false;
}

void MainWindow::openRecentFile()
{
  /*  QAction *action = qobject_cast<QAction *>(sender());
    if (action) {
        QGraphicsView *view = static_cast<QGraphicsView*>(documentTabs->currentWidget());
        DocumentScene *scene = static_cast<DocumentScene*>(view->scene());

        if (scene->modified) {
            newFile();
            DocumentTabs::documentNumber--;
        }

        load(action->data().toString());
  }*/
}

void MainWindow::about()
{
   /* QMessageBox::about(this, tr("About TrollText"),
        tr("<h2>TrollText 0.1</h2>"
        "<p/>Team 5 - UFOPAK"
        "<p/>This is just a prototype of text editor"
        "which is being developed for Team project course."));*/
}

void MainWindow::analyzeTab()
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (documentTabs->currentIndex() == -1)
        event->accept();

    int j = 0;
    int count = documentTabs->count();

    for (int i = 0; i < count; i++) {
        documentTabs->setCurrentIndex(j);
        if (!closeTab())
            j++;
    }

    if (documentTabs->currentIndex() == -1) {
        //writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::handleFontChange()
{
   /* QFont font;
    font.setWeight(textBoldAction->isChecked() ? QFont::Bold : QFont::Normal);
    font.setItalic(textItalicAction->isChecked());
    font.setUnderline(textUnderlineAction->isChecked());

    QGraphicsView *view = qobject_cast<QGraphicsView *>(documentTabs->currentWidget());
    DocumentScene *scene = qobject_cast<DocumentScene *>(view->scene());
    scene->setFont(font);*/
}

void MainWindow::updateRecentFileActions()
{
    /*QMutableStringListIterator i(recentFiles);
    while (i.hasNext()) {
        if (!QFile::exists(i.next()))
            i.remove();
    }

    for (int j = 0; j < MaxRecentFiles; ++j) {
        if (j < recentFiles.count()) {
            QString text = tr("&%1 %2").arg(j + 1).arg(strippedName(recentFiles[j]));
            recentFileActions[j]->setText(text);
            recentFileActions[j]->setData(recentFiles[j]);
            recentFileActions[j]->setVisible(true);
        } else {
            recentFileActions[j]->setVisible(false);
        }
    }

    separatorAction->setVisible(!recentFiles.isEmpty());*/
}

void MainWindow::setCurrentFile(int tabNumber)
{
    if (tabNumber != -1) {
        QString fileName = documentTabs->widget(tabNumber)->objectName();
        currentFile = fileName;
        QString shownName = tr("Untitled %1").arg(tabNumber + 1);

        if (!currentFile.isEmpty()) {
            shownName = strippedName(currentFile);
            recentFiles.removeAll(currentFile);
            recentFiles.prepend(currentFile);
            updateRecentFileActions();
        }

        setWindowTitle(tr("%1[*] - TrollText").arg(shownName));
    } else
        setWindowTitle(tr("TrollText"));
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void MainWindow::help()
{
    //HelpBrowser::showPage("index.html");
}

void MainWindow::settings()
{
   // settingsDialog->show();
   // settingsDialog->activateWindow();
}

bool MainWindow::closeTab()
{
   /* QGraphicsView *view = static_cast<QGraphicsView*>(documentTabs->currentWidget());
    DocumentScene *scene = static_cast<DocumentScene*>(view->scene());
    if (scene->modified) {
        int ret = QMessageBox::warning(this, QString(tr("TrollText")),
            QString(tr("Do you want to save file %1?").arg(documentTabs->tabText(documentTabs->currentIndex()))),
            QMessageBox::Yes, QMessageBox::No, QMessageBox::Cancel);
        if (ret == QMessageBox::Cancel)
            return false;
        else if (ret == QMessageBox::Yes)
            if (!save())
                return false;
    }
*/
    documentTabs->removeTab(documentTabs->currentIndex());
    return true;
}
void MainWindow::applyChanges()
{/*
    QPen *pen = new QPen;
    QBrush *brush = new QBrush;

    BrushPage *brushPage = qobject_cast<BrushPage*>(settingsDialog->pagesWidget->widget(0));
    brush->setColor(brushPage->color);
    brush->setStyle(brushPage->stylesMap.value(brushPage->styleCombo->currentText()));

    PenPage *penPage = qobject_cast<PenPage*>(settingsDialog->pagesWidget->widget(1));
    pen->setColor(penPage->color);
    pen->setCapStyle(penPage->capMap.value(penPage->capCombo->currentText()));
    pen->setJoinStyle(penPage->joinMap.value(penPage->joinCombo->currentText()));
    if (pen->joinStyle() == Qt::MiterJoin)
        pen->setMiterLimit(penPage->limitSpin->value());
    pen->setStyle(penPage->penMap.value(penPage->penCombo->currentText()));
    pen->setWidth(penPage->widthSpin->value());

    emit apply(brush, pen);*/
}

/*void MainWindow::writeSettings()
{
    QSettings settings("UFOPAK", "TrollEdit");
    BrushPage *brushPage = qobject_cast<BrushPage*>(settingsDialog->pagesWidget->widget(0));
    PenPage *penPage = qobject_cast<PenPage*>(settingsDialog->pagesWidget->widget(1));

    settings.setValue("recentFiles", recentFiles);

    settings.beginGroup("brush");
    settings.setValue("color", brushPage->color);
    settings.setValue("style",brushPage->styleCombo->currentText());
    settings.endGroup();

    settings.beginGroup("pen");
    settings.setValue("color", penPage->color);
    settings.setValue("capStyle", penPage->capCombo->currentText());
    settings.setValue("joinStyle", penPage->joinCombo->currentText());
    settings.setValue("miterLimit", penPage->limitSpin->value());
    settings.setValue("style", penPage->penCombo->currentText());
    settings.setValue("width", penPage->widthSpin->value());
    settings.endGroup();
}

void MainWindow::readSettings()
{
    QSettings settings("UFOPAK", "TrollEdit");
    settingsDialog = new SettingsDialog(this, settings);
    recentFiles = settings.value("recentFiles").toStringList();
}*/
