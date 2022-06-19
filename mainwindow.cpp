#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include <fstream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);

    // Dialogs
    mSettingsDialog = new SettingsDialog(this);
    mSettingsDialog->setReferenceTextEdit(ui->codeEdit);

    // Menu bar actions
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::newFile);
    connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::loadFile);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveFile);
    connect(ui->actionSave_as, &QAction::triggered, this, &MainWindow::saveFileAs);
    connect(ui->actionSettings, &QAction::triggered, this, &MainWindow::openSettingsWindow);

    // Button actions
    connect(ui->BtnNewfile, &QPushButton::clicked, this, &MainWindow::newFile);
    connect(ui->BtnLoadfile, &QPushButton::clicked, this, &MainWindow::loadFile);
    connect(ui->BtnSave, &QPushButton::clicked, this, &MainWindow::saveFile);
    connect(ui->BtnSaveAs, &QPushButton::clicked, this, &MainWindow::saveFileAs);
    connect(ui->BtnSettings, &QPushButton::clicked, this, &MainWindow::openSettingsWindow);

    // Anchor widgets
    mVFullAnchorWidgets.push_back(ui->codeEdit);
    mVWESAnchorWidgets.push_back(ui->Label);
}

MainWindow::~MainWindow() {

    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* e) {

    QMainWindow::resizeEvent(e);

    static QSize previous_size;

    // Do not do anything on first resize call.
    static bool first_resize = true;
    if (first_resize) {

        first_resize = false;
        previous_size = size(); // But do save the fresh size of the main window for next resize.
        return;
    }

    // Anchoring
    // Calculate difference in main window resize and anchor all widgets assigned for anchoring.
    QSize diff_size = size() - previous_size;

    for (QWidget*& awidget : mVFullAnchorWidgets)
        awidget->resize(awidget->size() + diff_size);

    for (QWidget*& awidget : mVWESAnchorWidgets) {

        QSize newsize = awidget->size();
        newsize = QSize(newsize.width() + diff_size.width(), newsize.height());
        awidget->move(awidget->x(), awidget->y() + diff_size.height());
        awidget->resize(newsize);
    }

    previous_size = size();
}

void MainWindow::newFile() {

    mFileName = "";
    ui->Label->setText("No file");
    ui->codeEdit->clear();
}

void MainWindow::loadFile() {

    QString filename = QFileDialog::getOpenFileName(this,
        tr("Open file"), "",
        tr("All Files (*)"));

    if (filename.isEmpty())
        return;
    else {

        ifstream file(filename.toLocal8Bit().constData());
        if (!file) {

            QMessageBox::information(this, tr("Error"), tr("File not found."));
            return;
        }

        string read = string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        ui->codeEdit->clear();
        ui->codeEdit->document()->setPlainText(QString::fromLocal8Bit(read.c_str()));

        mFileName = filename.toLocal8Bit().constData();
        ui->Label->setText(QString::fromLocal8Bit(mFileName.c_str()));
    }
}

void MainWindow::saveFile() {

    string code = ui->codeEdit->toPlainText().toLocal8Bit().constData();

    if (!mFileName.empty()) {

        ofstream file(mFileName, fstream::out | fstream::trunc);
        if (!file) {

            QMessageBox::information(this, tr("Error"), tr("Unable to save file."));
            QApplication::quit();
        }
        file << code;
    }
    else {

        QString filename = QFileDialog::getSaveFileName(this,
            tr("Save to file"), "",
            tr("All Files (*)"));

        if (filename.isEmpty())
            return;
        else {

            fstream file(filename.toLocal8Bit().constData(), fstream::out);
            if (!file) {

                QMessageBox::information(this, tr("Error"), tr("Unable to save file."));
                return;
            }

            file << code;

            mFileName = filename.toLocal8Bit().constData();
            ui->Label->setText(QString::fromLocal8Bit(mFileName.c_str()));
        }
    }
}

void MainWindow::saveFileAs() {

    string code = ui->codeEdit->toPlainText().toLocal8Bit().constData();

    QString filename = QFileDialog::getSaveFileName(this,
        tr("Save to file"), "",
        tr("All Files (*)"));

    if (filename.isEmpty())
        return;
    else {

        fstream file(filename.toLocal8Bit().constData(), fstream::out);
        if (!file) {

            QMessageBox::information(this, tr("Error"), tr("Unable to save file."));
            return;
        }

        file << code;

        mFileName = filename.toLocal8Bit().constData();
        ui->Label->setText(QString::fromLocal8Bit(mFileName.c_str()));
    }
}

void MainWindow::openSettingsWindow() {

    mSettingsDialog->setEditorTextFont(ui->codeEdit->font());
    mSettingsDialog->show();
}
