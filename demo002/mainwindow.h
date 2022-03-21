#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QVector>
#include <QMessageBox>
#include "chessitem.h"

#define CHESS_R 15
#define CHESS_C 15
#define MAX_X   40
#define MAX_Y   40

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent (QMouseEvent *event);
private:
    void InitUi();//初始化界面
    void Drawchess();//绘制棋局界面
    void DrawHandChess();//绘制鼠标上棋子的样式
    void DrawChessItem();
    void DrawChessAtPoint(QPainter &painter,QPoint &point);
    int CountNearItem(ChessItem item,QPoint pt);
    bool c_black;
    QVector<ChessItem> p_ChessItem;

};
#endif // MAINWINDOW_H
