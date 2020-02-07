#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLCDNumber;
class QLabel;
class QPushButton;
class QCheckBox;
QT_END_NAMESPACE

class VulkanWindow;

class MainWindow : public QWidget
{
public:
    MainWindow(VulkanWindow *vulkanWindow);

private:
    QLabel *createLabel(const QString &text);

    QLabel *infoLabel;
    QCheckBox *meshSwitch;
    QLCDNumber *counterLcd;
    QPushButton *newButton;
    QPushButton *quitButton;
    QPushButton *pauseButton;

    int m_count = 128;
};


