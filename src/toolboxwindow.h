#ifndef TOOLBOXWINDOW_H
#define TOOLBOXWINDOW_H

#include <QFrame>
#include <QVector>

class QStringList;
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
    void paintEvent(QPaintEvent *event) override;

private:
    void updateToolBtnIcon();

private:
    QPoint         m_topLeftPos;
    QPoint         m_staPos;
    QPoint         m_endPos;
    QStringList    m_listName;
    ToolBoxWindow *m_toolBox;
    QVector<QToolButton *> var;
//    QToolButton   *m_toolBtnRect;        // 矩形
//    QToolButton   *m_toolBtnEllipse;     // 椭圆
//    QToolButton   *m_toolBtnLine;        // 线
//    QToolButton   *m_toolBtnArrow;       // 箭头
//    QToolButton   *m_toolBtnPen;         // 笔
//    QToolButton   *m_toolBtnText;        // 文字
//    QToolButton   *m_toolBtnMosaic;      // 马赛克
//    QToolButton   *m_toolBtnRevoke;      // 撤销
//    QToolButton   *m_toolBtnUpload;      // 上传图床
//    QToolButton   *m_toolBtnDownload;    // 保存本地
//    QToolButton   *m_toolBtnCopy;        // 完成，图片暂存在剪切板
};

#endif // TOOLBOXWINDOW_H
