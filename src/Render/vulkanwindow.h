#pragma once

#include <QVulkanWindow>

class Renderer;

class VulkanWindow : public QVulkanWindow
{
public:
    VulkanWindow(bool dbg);

    QVulkanWindowRenderer *createRenderer() override;

    bool isDebugEnabled() const { return m_debug; }
    int instanceCount() const;

public slots:
    void addNew();
    void togglePaused();
    void meshSwitched(bool enable);

private:
    void mousePressEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void keyPressEvent(QKeyEvent *) override;

    bool m_debug;
    Renderer *m_renderer;
    bool m_pressed = false;
    QPoint m_lastPos;
};
