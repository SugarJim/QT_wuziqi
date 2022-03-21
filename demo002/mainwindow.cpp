#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)

{
    InitUi();
}

MainWindow::~MainWindow()
{

}

void MainWindow::paintEvent(QPaintEvent *event){
    Drawchess();
    DrawHandChess();
    DrawChessItem();

    update();
}

//初始化棋盘
void MainWindow:: InitUi(){
    this->resize((CHESS_C + 1)*MAX_X, (CHESS_R + 1)*MAX_Y);//加一设置边框
    //固定窗口大小setMaximumSize
    this->setMaximumSize((CHESS_C + 1)*MAX_X, (CHESS_R + 1)*MAX_Y);
    this->setMinimumSize((CHESS_C + 1)*MAX_X, (CHESS_R + 1)*MAX_Y);
    this->setWindowTitle("五子棋");
    this->setWindowIcon(QIcon("img/title.PNG"));//设置窗口图标
    //setWindowIcon（QIcon（“图片路径”））设置小窗口图标
    c_black = false;
}

//画棋盘格子
void MainWindow::Drawchess(){
    QPainter painter(this);
    painter.setRenderHint(QPainter::HighQualityAntialiasing,true);
    painter.setPen(QPen(QColor(Qt::black),2));//格子粗细
    painter.setBrush(Qt::gray);//格子灰色
    for (int i = 0;i < CHESS_C;i++) {
        for (int j = 0;j < CHESS_R;j++) {
            //边框一共加1，每边0.5
            painter.drawRect((i+0.5)*MAX_X,(j+0.5)*MAX_Y,MAX_X,MAX_Y);
            //一格一格绘制格子
        }

    }
}

//绘制鼠标上棋子的样式
void MainWindow::DrawHandChess(){
    QPainter painter(this);
    painter.setPen(QPen(QColor(Qt::transparent)));
    if (c_black){
        painter.setBrush(Qt::black);
    }else{
        painter.setBrush(Qt::white);
    }
    painter.drawEllipse(mapFromGlobal(QCursor::pos()),MAX_X/3,MAX_Y/3);
}


//绘制棋子
void MainWindow::DrawChessItem(){
    QPainter painter(this);
    painter.setPen(QPen(QColor(Qt::transparent)));
    for (int i = 0;i < p_ChessItem.size();i++) {
        ChessItem item = p_ChessItem[i];
        if (item._black){
            painter.setBrush(Qt::black);
        }else{
            painter.setBrush(Qt::white);
        }
        DrawChessAtPoint(painter,item._pt);
    }
}

void MainWindow::DrawChessAtPoint(QPainter &painter,QPoint &point){
    QPoint ptCenter((point.x() + 0.5) * MAX_X, (point.y() + 0.5) * MAX_Y);
    painter.drawEllipse(ptCenter, MAX_X/3, MAX_Y/3);
}

//鼠标点击判断是否连五
void MainWindow::mousePressEvent (QMouseEvent *event){
    QPoint pt;
    pt.setX((event->pos().x())/MAX_X);
    pt.setY((event->pos().y())/MAX_Y);

    //判断当前的点位是否有棋子
    for (int i = 0;i < p_ChessItem.size();i++) {
        ChessItem item = p_ChessItem[i];
        if (item._pt == pt){
            return;
        }

    }

    //判断五子连接
    ChessItem item(pt, c_black);
    p_ChessItem.append(item);

    int nUp        = CountNearItem(item,QPoint(0, -1));
    int nUpRight   = CountNearItem(item,QPoint(1, -1));
    int nRight     = CountNearItem(item,QPoint(1, 0));
    int nRightDown = CountNearItem(item,QPoint(1, 1));
    int nDown      = CountNearItem(item,QPoint(0, 1));
    int nLeftDown  = CountNearItem(item,QPoint(-1, 1));
    int nLeft      = CountNearItem(item,QPoint(-1, 0));
    int nLeftUp    = CountNearItem(item,QPoint(-1, -1));

    if ((nUp + nDown) >= 4 ||
        (nLeft + nRight) >= 4 ||
        (nUpRight + nLeftDown) >= 4||
        (nLeftUp + nRightDown) >= 4
            ){
        QString str = c_black ? "Black Win": "White Win";
        QMessageBox::information(NULL,"Game Over",str,QMessageBox::Yes);
        p_ChessItem.clear();
        return;
    }
    c_black = !c_black;
}

int MainWindow::CountNearItem(ChessItem item,QPoint pt){
    int nCount = 0;
    item._pt += pt;
    while (p_ChessItem.contains(item)){
        nCount++;
        item._pt += pt;
    }
    return nCount;
}
