#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "settingsdialog.h"

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QLabel>
#include <iostream>
#include <fstream>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    SettingsDialog* mSettingsDialog;

    QVector<QWidget*> mVFullAnchorWidgets;
    QVector<QWidget*> mVWESAnchorWidgets;

    string mFileName = "";

    void resizeEvent(QResizeEvent* e) override;

    void newFile();
    void loadFile();
    void saveFile();
    void saveFileAs();
    void openSettingsWindow();
};
#endif // MAINWINDOW_H
