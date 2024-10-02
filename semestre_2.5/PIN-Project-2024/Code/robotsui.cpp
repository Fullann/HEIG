#include <QFileDialog>
#include <fstream>

#include "robotsui.h"
#include "./ui_robotsui.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
using namespace std;


void RobotsUI::ShowScore(State state){
    int score = 0;
    int scoreTotal = 0;

    for (RobotInfo robot : state.robots){
        score += robot.score;
    }

    for (ParticleInfo particle : state.particles){
        scoreTotal += particle.radius *particle.radius * M_PI;
    }

    QString text = QString("Score: %1 / %2").arg(score).arg(scoreTotal);
    this->findChild<QLabel *>("ScoreLabel")->setText(text);
}

RobotsUI::RobotsUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RobotsUI)
{
    ui->setupUi(this);

    TimeSpinBox = this->findChild<QDoubleSpinBox *>("TimeSpinBox");
    SpeedSpinBox = this->findChild<QSpinBox *>("SpeedSpinBox");

    this->findChild<QPushButton *>("FirstStateButton")->setVisible(false);
    this->findChild<QPushButton *>("PlayPauseButton")->setVisible(false);
    this->findChild<QLabel *>("TimeLabel")->setVisible(false);
    TimeSpinBox->setVisible(false);
    this->findChild<QLabel *>("SpeedLabel")->setVisible(false);
    SpeedSpinBox->setVisible(false);
    this->findChild<QLabel *>("ScoreLabel")->setVisible(false);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(UpdateTimeDisplay()));
}

RobotsUI::~RobotsUI()
{
    delete ui;
}


void RobotsUI::OpenState()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                             tr("Open State File"), "", tr("Json Files (*.stat)"));
    if(fileName.isNull()){
        qApp->beep();
        cout << "Error while charging file";
        return;
    }

    ifstream ifs(fileName.toStdString());
    State state;
    ifs >> state;
    setState(state);
    fileName = fileName.mid(fileName.lastIndexOf("/")+1);
    this->setWindowTitle(fileName);

    if (!timeline.states.empty()){
        timeline.states.clear();
    }

    timeline.states.push_back(state);
    setState(timeline.states[0]);
    timeline.tmpState = timeline.states[0];

    this->Change_UI_to_game();

}

void RobotsUI::Change_UI_to_game()
{
    QPushButton *button = this->findChild<QPushButton *>("OpenStateButton");
    button->setVisible(false);
    this->findChild<QPushButton *>("FirstStateButton")->setVisible(true);
    this->findChild<QPushButton *>("PlayPauseButton")->setVisible(true);
    this->findChild<QLabel *>("TimeLabel")->setVisible(true);
    this->findChild<QDoubleSpinBox *>("TimeSpinBox")->setVisible(true);
    this->findChild<QLabel *>("SpeedLabel")->setVisible(true);
    this->findChild<QSpinBox *>("SpeedSpinBox")->setVisible(true);
    this->findChild<QLabel *>("ScoreLabel")->setVisible(true);
}

void RobotsUI::setState(State& state) {
   ui->widget->setState(state);

}
void RobotsUI::SaveState()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save State File"), "", tr("Json Files (*.stat)"));
    if(fileName.isNull()){
        return;
    }

    ofstream ofs(fileName.toStdString());
    ofs << setw(4) << ui->widget->getState();
}

void RobotsUI::setTimeline(){
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Timeline File"), "", tr("Json Files (*.tlin)"));
    if(fileName.isNull()){;
        qApp->beep();
        cout << "Error while loading .tlin file";
        return;
    }
    ifstream ifs(fileName.toStdString());
    ifs >> timeline;
    setState(timeline.states[0]);
    fileName = fileName.mid(std::max(fileName.lastIndexOf("/")+1, fileName.lastIndexOf("\\")+1));
    this->setWindowTitle(fileName);
    this->Change_UI_to_game();
}

void RobotsUI::on_actionOpen_triggered() {
    this->OpenState();
}

void RobotsUI::on_actionSave_triggered() {
    this->SaveState();
}

void RobotsUI::on_actionQuit_triggered()
{
    qApp->exit(0);
}

void RobotsUI::on_OpenStateButton_clicked()
{
    this->OpenState();
}



void RobotsUI::on_PlayPauseButton_clicked()
{
    if(timer->isActive()){
        timer->stop();
    } else {
        timer->start(10);
    }
}

void RobotsUI::on_SpeedSpinBox_valueChanged(int arg1)
{

}

void RobotsUI::on_actionOpen_Timeline_triggered()
{
    this->setTimeline();
}

void RobotsUI::on_FirstStateButton_clicked()
{
    TimeSpinBox->setValue(0.0);
    ui->widget->setState(timeline.states[0]); // Affiche l'état au temps 0.0
    timeline.tmpState = timeline.states[0];
}

void RobotsUI::on_TimeSpinBox_valueChanged(double arg1)
{
    displayStateAtTime(arg1);
}

void RobotsUI::UpdateTimeDisplay()
{
    double newTime = TimeSpinBox->value() + (0.01 * SpeedSpinBox->value());
    TimeSpinBox->setValue(newTime);

    displayStateAtTime(newTime);
}



void RobotsUI::displayStateAtTime(Time targetTime)
{
    auto it = std::lower_bound(timeline.states.begin(), timeline.states.end(), targetTime,
                               [](const State& state, Time time) {
                                   return state.time < time;
                               });

    if (!timeline.states.empty()) {
        if (it != timeline.states.begin() && it->time != targetTime) {
            //Interpolate
            auto prevIt = std::prev(it);
            ui->widget->setState(makeStateAt(targetTime, *prevIt));
        } else {
            // Use directly the state
            ui->widget->setState(*it);

        }
    }
}

State RobotsUI::makeStateAt(Time targetTime, State it){
    Time diferencialTime = targetTime - it.time;
    it.time = targetTime;
    Position pos;
    for(RobotInfo &robot : it.robots){
        pos = robot.findPotentialMove(diferencialTime);
        robot.move(diferencialTime);
    }
    ShowScore(it);
    return it;
}
