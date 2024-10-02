#include "robotwidget.h"
#include "QtGui/qevent.h"

#include <QPainter>
#include <string>
#include "worldtoscreenconverter.h"


RobotWidget::RobotWidget(QWidget *parent)
    : QWidget{parent}
{
    setMinimumSize(200, 200);

    background = QBrush(QColor(200, 200, 200));
    robotBrush = QBrush(QColor(255, 255, 255));
    robotPen = QPen(Qt::black);
    robotPen.setWidth(1);
    mouthBrush = QBrush(QColor(128, 128, 128));
    particleBrush = QBrush(QColor(255, 100, 100));
    particlePen = QPen(Qt::black);
    particlePen.setWidth(1);
    textPen = QPen(Qt::black);
    textFont.setPixelSize(50);

}

void RobotWidget::setState(State const& state) {
    this->state = state;
    this->update();
}

void RobotWidget::updateParticles() {
    std::vector<ParticleInfo> newParticles;
    for (auto& particle : state.particles) {
        if (!particle.explosionTimes.empty() && particle.explosionTimes[0][0] <= state.time) {
            auto children = particle.disintegrate();
            for (auto& child : children) {
                child.explosionTimes.erase(child.explosionTimes.begin());
            }
            newParticles.insert(newParticles.end(), children.begin(), children.end());
        } else {
            newParticles.push_back(particle);
        }
    }
    state.particles = newParticles;

    // Vérifier la décontamination
    handleDecontamination(state);
}


void RobotWidget::paintEvent(QPaintEvent *event)
{
    WorldToScreenConverter w2s(state,event->rect());

    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(w2s.world(), background);
    painter.setClipRect(w2s.world());

    painter.save();

    double maxRobotRadius = state.robots.empty() ? 1000 : state.robots.front().radius;

    for(RobotInfo& robot : state.robots) {
        painter.setBrush(robotBrush);
        painter.setPen(robotPen);
        painter.drawEllipse(w2s.circle(robot.position,robot.radius));

        double startAngle = 16 * (-robot.angle - robot.captureAngle);
        double spanAngle = 16 * (2*robot.captureAngle);
        painter.setBrush(mouthBrush);
        painter.drawPie(w2s.circle(robot.position,robot.radius),(int)startAngle,(int)spanAngle);


        Position btn { robot.position.x + 0.7 * robot.radius * cos(M_PI*robot.angle/180),
                     robot.position.y +  0.7 * robot.radius * sin(M_PI*robot.angle/180)};
       painter.setBrush(robotBrush);
       painter.setPen(robotPen);
       painter.drawEllipse(w2s.circle(btn,robot.radius*0.15));


        painter.setPen(textPen);
        textFont.setPixelSize((int)w2s.r(robot.radius));
        maxRobotRadius = std::max(maxRobotRadius,w2s.r(robot.radius));
        painter.setFont(textFont);
        painter.drawText(w2s.circle(robot.position,robot.radius*0.8),
                         Qt::AlignCenter,
                         QString::fromStdString(std::to_string(robot.id))
                         );
    }

    for(ParticleInfo& particle : state.particles) {
        painter.setBrush(particleBrush);
        painter.setPen(particlePen);
        painter.drawEllipse(w2s.circle(particle.position,particle.radius));

        painter.setPen(textPen);
        textFont.setPixelSize((int)std::min(maxRobotRadius,w2s.r(particle.radius)));
        painter.setFont(textFont);
        painter.drawText(w2s.circle(particle.position,particle.radius*0.8),
                         Qt::AlignCenter,
                         QString::fromStdString(std::to_string(particle.id))
                         );
    }
    painter.restore();

    painter.end();
}

