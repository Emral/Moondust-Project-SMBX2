#pragma once
#ifndef TESTING_SETTINGS_H
#define TESTING_SETTINGS_H

#include <QDialog>

namespace Ui {
class TestingSettings;
}

class TestingSettings : public QDialog
{
    Q_OBJECT

public:
    explicit TestingSettings(QWidget *parent = 0);
    ~TestingSettings();

private slots:
    void on_buttonBox_accepted();
    void reloadStates1(int index);
    void reloadStates2(int index);
signals:
    void windowShown();

protected:
    void showEvent(QShowEvent *event);

private:
    Ui::TestingSettings *ui;

    void refreshVehicleID();
    void refreshVehicleTypes();
};

#endif // TESTING_SETTINGS_H
