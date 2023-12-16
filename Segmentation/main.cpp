#include <dealimageparameter.h>
#include <dealwithimage.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DealWithImage::getStatic()->Init();
    /****启动处理界面****/
    DealImageParameter* dip_=new DealImageParameter();
    dip_->show();
    return a.exec();
}
