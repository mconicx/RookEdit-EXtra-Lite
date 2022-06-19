#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QTimer>

QPlainTextEdit* g_mReferenceTextEdit;
QTimer* g_mTimerTick;

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); // Remove question mark button.

    connect(ui->CBoxEditorTextFont, &QFontComboBox::currentFontChanged, this, &SettingsDialog::fontChanged);

    resetTickLabel();

    g_mTimerTick = new QTimer();
    g_mTimerTick->setInterval(1500);
    g_mTimerTick->setSingleShot(true);
    connect(g_mTimerTick, &QTimer::timeout, this, QOverload<>::of(&SettingsDialog::resetTickLabel));
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::setEditorTextFont(const QFont font) {

    ui->CBoxEditorTextFont->setCurrentFont(font);
}

void SettingsDialog::fontChanged(const QFont &f) {

    if (!g_mReferenceTextEdit) return;

    if (g_mTimerTick->isActive())
        g_mTimerTick->stop();

    g_mReferenceTextEdit->setFont(f);
    ui->TickLabelFont->setVisible(true);

    g_mTimerTick->start();
}

void SettingsDialog::setReferenceTextEdit(QPlainTextEdit* w) {

    g_mReferenceTextEdit = w;
}

void SettingsDialog::resetTickLabel() {

    ui->TickLabelFont->setVisible(false);
}
