#ifndef TOOLBOXWINDOW_H
#define TOOLBOXWINDOW_H

#include <QFrame>
#include <QWidget>

class QToolButton;

class ToolBoxWindow : public QFrame
{
    Q_OBJECT
public:
    ToolBoxWindow();
    void init();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QPoint        m_topLeftPos;
    QPoint        m_staPos;
    QPoint        m_endPos;
    QToolButton   *m_toolBtnRect;        // 矩形
    QToolButton   *m_toolBtnEllipse;     // 椭圆
    QToolButton   *m_toolBtnLine;        // 线
    QToolButton   *m_toolBtnArrow;       // 箭头
    QToolButton   *m_toolBtnPen;         // 笔
    QToolButton   *m_toolBtnText;        // 文字
    QToolButton   *m_toolBtnMosaic;      // 马赛克
    QToolButton   *m_toolBtnRevoke;      // 撤销
    QToolButton   *m_toolBtnUpload;      // 上传图床
    QToolButton   *m_toolBtnDownload;    // 保存本地
    QToolButton   *m_toolBtnExit;        // 推出截图
    QToolButton   *m_toolBtnCopy;        // 完成，图片暂存在剪切板
    ToolBoxWindow *m_toolBox;
};

#endif // TOOLBOXWINDOW_H
