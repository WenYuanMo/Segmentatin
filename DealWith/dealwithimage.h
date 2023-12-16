
#ifndef DEALWITHIMAGE_H
#define DEALWITHIMAGE_H

#include <QObject>
#include <QList>
#include <QApplication>
#include <QString>
#include <QFile>
#include <QDebug>
#include <QImage>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <windows.h>
using namespace std;
//using namespace dnn;
//using namespace cv;

/****分割结果的结构****/
class ResultStructure
{
public:
    /****编号***/
    int _number;
    /***面积*****/
    double _area;
    /***高***/
    double _height;
    /****宽****/
    double _width;
    /***平均灰度****/
    double _mean;
    /******圆度*****/
    double _round;
    /***凸度****/
    double _convexity;
    /***角度****/
    double _angle;
    /****坐标****/
    double _x;
    /***坐标*****/
    double _y;
};

/***分割的roi***/
class SegmentationRoi
{
public:
    double _id;
    double _x_column;
    double _y_row;
    double _r;

    /****结果****/
    QList<ResultStructure> _segmentation_results;
};

/***图片处理类****/
class DealWithImage : public QObject
{
    Q_OBJECT
public:
    explicit DealWithImage(QObject *parent = nullptr);
    ~DealWithImage();

    static DealWithImage* getStatic()
    {
        if(_deal_with_image==nullptr)
        {
            _deal_with_image=new  DealWithImage();
        }
        return _deal_with_image;
    }

    static void deletStatic()
    {
        if(_deal_with_image!=nullptr)
        {
            delete _deal_with_image;
        }
    }

    /****初始化*****/
    void Init();
    /****读取roi配置******/
    bool ReadRoiConfig(QString path_);
    /***读取配置文件****/
    bool ReadParameterConfig(QString path_);
    /*****保存配置******/
    void WriteConfig();
    /*****保存roi*****/
    bool WriteRoiConfig(QString path_);
    /****保存数据*****/
    bool WriteParameterConfig(QString path_);

    /***获取qimage*****/
    QImage GetImage(cv::Mat);
    /****获取mat***/
    cv::Mat GetMat(QImage);
    /***清空结果***/
    void ClearSegmentationResult();
    /****分割*****/
    void SegmentationStuff();
    /****检测roi是否超出图片****/
    void  checkRoiBiggerBoard();

signals:

public:

    /***qt控件显示的图片******/
    QImage _qimage;
    /***结果图片***/
    QImage _result_image;
    /****使用的图片***/
    QImage _use_image;
    /***平滑的图片one***/
    QImage _mean_image_one;
    /***平滑的图片two***/
    QImage _mean_image_two;

    /*****最大面积****/
    double _max_area=-1;    
    /******最小面积*****/
    double _min_area=-1;

    /***最大宽*****/
    double _max_width=-1;
    /****最小宽*****/
    double _min_width=-1;

    /****最大高*****/
    double _max_height=-1;
    /*****最小高****/
    double _min_heigth=-1;

    /***最小圆度***/
    double _min_roundness=0;
    /****最大圆度****/
    double _max_roundness=1;

    /***最小凸度***/
    double _min_convexity=0;
    /***最大凸度***/
    double _max_convexity=1;

    /***使用的通道0:gray 1:r 2:g 3:b 4:h 5:s 6:v***/
    int _use_image_channle=0;

    /***动态阈值的方式 0:明 1:暗 2:等于 3:不等于***/
    int _dyn_threshold_type=-1;
    /***动态阈值***/
    double _dyn_threshold_=30;

    /***动态分割是,第一张图片平滑值***/
    double _image_mean_number_dyn_one=10;
    /****动态分割是,第二张图片平滑值***/
    double _image_mean_number_dyn_two=60;

    /***距离因子 认为相邻多小个像素是一个物体,闭运算先膨胀后腐蚀***/
    double _segmentation_stuff_closing_memenlt=0;

    /***相加增益***/
    double _camer_gain=1;
    /***相机曝光***/
    double _camer_expource=100;

    /***拼接图片的宽***/
    double _combine_image_width=0;
    /***拼接图片的高***/
    double _combine_image_height=0;

    /***是否使用面积过滤***/
    double _use_area_filtration=0;
    /***是否使用宽过滤***/
    double _use_width_filtration=0;
    /***是否使用高过滤***/
    double _use_height_filtration=0;
    /***是否使用圆度过滤***/
    double _use_roundness_filtration=0;
    /***是否使用凸度过滤***/
    double _use_convexity_filtration=0;

    /***显示结果图片***/
    bool _show_result_image=false;
    /***显示使用处理的图片***/
    bool _show_use_image=false;
    /***显示平滑的图片1***/
    bool _show_mean_image_one=false;
    /***显示平滑的图片2***/
    bool _show_mean_image_two=false;

    /***显示面积***/
    bool _show_segmentation_result_area=false;
    /***显示宽***/
    bool _show_segmentation_result_width=false;
    /***显示高***/
    bool _show_segmentation_result_height=false;
    /***显示圆度***/
    bool _show_segmentation_result_roundness=false;
    /***凸度***/
    bool _show_segmentation_result_convexity=false;
    /***显示平均值***/
    bool _show_segmentation_result_mean=false;

    /*****分割的roi*****/
    QList<SegmentationRoi> _segmentation_rois;

private:
   static DealWithImage* _deal_with_image;

};

#endif // DEALWITHIMAGE_H
