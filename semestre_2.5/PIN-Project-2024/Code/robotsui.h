#ifndef ROBOTSUI_H
#define ROBOTSUI_H

#include <QDoubleSpinBox>
#include <QMainWindow>
#include <QTimer>
#include "State.h"

QT_BEGIN_NAMESPACE
namespace Ui { class RobotsUI; }
QT_END_NAMESPACE

class RobotsUI : public QMainWindow
{
    Q_OBJECT

public:
    RobotsUI(QWidget *parent = nullptr);
    ~RobotsUI();

public slots:
    void UpdateTimeDisplay();

private slots:
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionQuit_triggered();

    void on_OpenStateButton_clicked();

    void setState(State& state);
    void on_FirstStateButton_clicked();

    void on_PlayPauseButton_clicked();

    void on_TimeSpinBox_valueChanged(double arg1);

    void on_SpeedSpinBox_valueChanged(int arg1);

    void on_actionOpen_Timeline_triggered();

private:
    QDoubleSpinBox *TimeSpinBox;
    QSpinBox *SpeedSpinBox;
    Timeline timeline;
    QTimer *timer;
    Ui::RobotsUI *ui;

    void ShowScore(State state);
    void Change_UI_to_game();
    void OpenState();
    void SaveState();
    void setTimeline();
    void displayStateAtTime(Time targetTime);
    State makeStateAt(Time targetTime, State it);
    State makeStateAtRef(Time targetTime, State& it);
};
#endif // ROBOTSUI_H
