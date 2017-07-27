#ifndef PICRECOVER_H
#define PICRECOVER_H

#include <QMainWindow>
#include <QGraphicsScene>

namespace Ui {
class PicRecover;
}

class PicRecover : public QMainWindow
{
    Q_OBJECT

public:
    explicit PicRecover(QWidget *parent = 0);
    ~PicRecover();
    QGraphicsScene* PicReSort(const QString &srcPic);
    void test(const QString &srcPic);
private:
    Ui::PicRecover *ui;
};

#endif // PICRECOVER_H
