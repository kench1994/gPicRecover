#include "picrecover.h"
#include "ui_picrecover.h"
#include <QDebug>
#include <QPoint>
#include <QPainter>
QPoint p_slicePos[] = {QPoint(-157, -58), QPoint(-145, -58), QPoint(-265, -58), QPoint(-277, -58), \
                       QPoint(-181, -58), QPoint(-169, -58), QPoint(-241, -58), QPoint(-253, -58), \
                       QPoint(-109, -58), QPoint(-97, -58), QPoint(-289, -58), QPoint(-301, -58), \
                       QPoint(-85, -58), QPoint(-73, -58), QPoint(-25, -58), QPoint(-37, -58), \
                       QPoint(-13, -58), QPoint(-1, -58), QPoint(-121, -58), QPoint(-133, -58), \
                       QPoint(-61, -58), QPoint(-49, -58), QPoint(-217, -58), QPoint(-229, -58), \
                       QPoint(-205, -58), QPoint(-193, -58), QPoint(-145, 0), QPoint(-157, 0), \
                       QPoint(-277, 0), QPoint(-265, 0), QPoint(-169, 0), QPoint(-181, 0), \
                       QPoint(-253, 0), QPoint(-241, 0), QPoint(-97, 0), QPoint(-109, 0), \
                       QPoint(-301, 0), QPoint(-289, 0), QPoint(-73, 0), QPoint(-85, 0), \
                       QPoint(-37, 0), QPoint(-25, 0), QPoint(-1, 0), QPoint(-13, 0), \
                       QPoint(-133, 0), QPoint(-121, 0), QPoint(-49, 0), QPoint(-61, 0), \
                       QPoint(-229, 0), QPoint(-217, 0), QPoint(-193, 0), QPoint(-205, 0) };
QSize pixelSize(10,58);

PicRecover::PicRecover(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PicRecover)
{
    ui->setupUi(this);
    //show original pic
    QImage* oriImg = new QImage("../gPicRecover/toFix.jpg");
    QGraphicsScene* sceneOriImg = new QGraphicsScene();
    sceneOriImg->addPixmap(QPixmap::fromImage(*oriImg));
    ui->originalImg->setScene(sceneOriImg);
    ui->originalImg->show();
    delete oriImg;

    //pic recover
    QGraphicsScene* sceneImg  = PicReSort("../gPicRecover/toFix.jpg");
    ui->resultImg->setScene(sceneImg);
    ui->resultImg->show();

    //    test("../QPicRecover/toFix.jpg");




//    //invert intensity
//    unsigned char* data = img->bits();//获取图像像素字节数据的首地址
//    int height = img->height();
//    int width = img->width();
//    int bytesPerLine = img->bytesPerLine();//width * 4, 与OpenCV中区分

//    qDebug()<<"height:"<<height<<"whidth:"<<width<<"bytesPerline:"<<bytesPerLine;

//    unsigned char* data2 = img->bits();//获取图像像素字节数据的首地址
//    int height2 = img2->height();
//    int width2 = img2->width();
//    int bytesPerLine2 = img2->bytesPerLine();//width * 4, 与OpenCV中区分
//    qDebug()<<"height:"<<height2<<"whidth:"<<width2<<"bytesPerline:"<<bytesPerLine2;

//    for (int row = 0; row<2; row++)
//        for (int column = 0; column<26; column++)
//        {
////            int offsetX = n[row * columns + column] % 26 * 12 + 1;
////            int offsetY = n[row * columns + column] > 25 ? 116 / 2 : 0;

//        }






//    QPainter painter;
//    painter.drawImage(
//    for(int y = 0; y < height; y++)
//        for(int x = 0; x < width; x++){
////            if(data[y * bytesPerLine + x * 4] == 0){
////                outdata[y * bytesPerLine + x * 4 ] = 255;//B
////                outdata[y * bytesPerLine + x * 4 + 1] = 255;//G
////                outdata[y * bytesPerLine + x * 4 + 2] = 255;//R
////                //A, 该分量保持不变
////                outdata[y * bytesPerLine + x * 4 + 3] = data[y * bytesPerLine + x * 4 + 3];
////            }
////            else{
////                outdata[y * bytesPerLine + x * 4 ] = 0;
////                outdata[y * bytesPerLine + x * 4 + 1] = 0;
////                outdata[y * bytesPerLine + x * 4 + 2] = 0;
////                outdata[y * bytesPerLine + x * 4 + 3] = data[y * bytesPerLine + x * 4 + 3];
////            }
//        }

       //QImage::Format_RGB32, 有多种格式，选择合适的格式很重要
//       QImage* outImg = new QImage(outdata,width,height,bytesPerLine,QImage::Format_RGB32);
//        //初始图，结果图要对应不同的 QGraphicsScene*
//        QGraphicsScene* sceneOutImg = new QGraphicsScene();
//        sceneOutImg->addPixmap(QPixmap::fromImage(*outImg));
//        ui->resultImg->setScene(sceneOutImg);
//        ui->resultImg->show();


}

PicRecover::~PicRecover()
{
    delete ui;
}

QGraphicsScene* PicRecover::PicReSort(const QString &srcPic){
    QImage *srcImg = new QImage(srcPic);
    QPixmap *painterImg = new QPixmap(312,116);
    painterImg->fill(Qt::transparent);//用透明色填充
    QPainter* painter = new QPainter(painterImg);
    for (int i = 0; i<52; i++){
        QPoint cur_pos = QPoint((i%26)*10, ((i/26))*58);
        QRect target(cur_pos,pixelSize);
        QRect source(-p_slicePos[i],pixelSize);
        painter->drawImage(target, *srcImg, source);
    }
    painter->end();
    delete painter;
    delete srcImg;
    QGraphicsScene* sceneImg = new QGraphicsScene();
//    painterImg->save()//这边到时候多一个参destPos
    sceneImg->addPixmap(*painterImg);
    delete painterImg;
    return sceneImg;

}

void PicRecover::test(const QString &srcPic){
    QImage *srcImg = new QImage(srcPic);
    //经过验证，应该处理为bmp透明画板，所以下面是错的
    QImage  *painterImg = new QImage(312,116,QImage::Format_RGBA8888);

    QPainter* painter = new QPainter(painterImg);
    for (int i = 0; i<52; i++){
        QPoint cur_pos = QPoint((i%26)*10, ((i/26))*58);
        QRect target(cur_pos,pixelSize);
        QRect source(-p_slicePos[i],pixelSize);
        painter->drawImage(target, *srcImg, source);
    }
    painter->end();
    delete painter;
    delete srcImg;
    QGraphicsScene* sceneImg = new QGraphicsScene();
    sceneImg->addPixmap(QPixmap::fromImage(*painterImg));
    delete painterImg;
    ui->resultImg->setScene(sceneImg);
    ui->resultImg->show();
}
