#ifndef CHESSITEM_H
#define CHESSITEM_H

#include <QPoint>

class ChessItem
{
public:
    ChessItem(void);
    ChessItem(QPoint point, bool isBlack);
    bool operator == (const ChessItem &t1)const {
        return ((_pt == t1._pt) && (_black == t1._black));
    }

    QPoint _pt;
    bool _black;
};

#endif // CHESSITEM_H
