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

private:
    QToolButton *toolBtnRect;        // 矩形
    QToolButton *toolBtnEllipse;     // 椭圆
    QToolButton *toolBtnLine;        // 线
    QToolButton *toolBtnArrow;       // 箭头
    QToolButton *toolBtnPen;         // 笔
    QToolButton *toolBtnText;        // 文字
    QToolButton *toolBtnBlurry;      // 马赛克
    QToolButton *toolBtnRevoke;      // 撤销
    QToolButton *toolBtnUpload;      // 上传图床
    QToolButton *toolBtnSave;        // 保存本地
    QToolButton *toolBtnQuit;        // 推出截图
    QToolButton *toolBtnOk;          // 完成，图片暂存在剪切板

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // TOOLBOXWINDOW_H
