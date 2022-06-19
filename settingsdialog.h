#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QPlainTextEdit>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

    void setReferenceTextEdit(QPlainTextEdit* w);
    void setEditorTextFont(const QFont font);

private:
    Ui::SettingsDialog *ui;

    void fontChanged(const QFont &f);
    void resetTickLabel();
};

#endif // SETTINGSDIALOG_H
