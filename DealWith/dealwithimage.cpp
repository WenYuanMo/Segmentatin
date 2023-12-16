#include "dealwithimage.h"

DealWithImage* DealWithImage::_deal_with_image=nullptr;

DealWithImage::DealWithImage(QObject *parent) : QObject(parent)
{

}

DealWithImage::~DealWithImage()
{
}

void DealWithImage::Init()
{
    QString path_parameter_config_=QCoreApplication::applicationDirPath()+ "/ImageConfig/DealWithParameterConfig.csv";
    ReadParameterConfig(path_parameter_config_);

    QString path_roi_config_=QCoreApplication::applicationDirPath()+ "/ImageConfig/DealWithRoiConfig.csv";
    ReadRoiConfig(path_roi_config_);

}

bool DealWithImage::ReadRoiConfig(QString path_)
{
    _segmentation_rois.clear();
    QFile file_roi_(path_);
    if(!file_roi_.exists(path_))
    {
        qDebug()<<"文件不存在:"+path_;
        return false;
    }
    if(!file_roi_.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"加载数据出错:"+path_;
        return false;
    }
    QStringList roi_list_;
    QTextStream in_list_(&file_roi_);
    /*****这行的目的是支持读取中文信息*********/
    //in_list_.setEncoding("GB2312");
    QString roi_data_all_=in_list_.readAll().toUtf8();
    /*****分割出数据******/
    roi_list_=roi_data_all_.split("\n");
    int count_=roi_list_.size();
    for(int i=1;i<count_;i++)
    {
        QStringList roi_one_=roi_list_[i].split(",");
        if(roi_one_.size()>=4)
        {
            SegmentationRoi sr_;
            sr_._id=roi_one_[0].toDouble();
            sr_._x_column=roi_one_[1].toDouble();
            sr_._y_row=roi_one_[2].toDouble();
            sr_._r=roi_one_[3].toDouble();
            _segmentation_rois.append(sr_);
        }
    }
    return  true;
}

bool DealWithImage::ReadParameterConfig(QString path_)
{
    QFile file_parameter_(path_);
    if(!file_parameter_.exists(path_))
    {
        qDebug()<<"文件不存在:"+path_;
        return false;
    }
    if(!file_parameter_.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"加载数据出错:"+path_;
        return false;
    }

    QStringList parameter_list_;
    QTextStream in_parameter_list_(&file_parameter_);
    /*****这行的目的是支持读取中文信息******/
    //in_parameter_list_.setCodec("GB2312");
    QString parameter_data_all_=in_parameter_list_.readAll().toUtf8();
    /***分割出数据****/
    parameter_list_=parameter_data_all_.split("\n");

    if(parameter_list_.size()>26)
    {
        _max_area=parameter_list_[1].split(",")[1].toDouble();
        _min_area=parameter_list_[2].split(",")[1].toDouble();

        _max_width=parameter_list_[3].split(",")[1].toDouble();
        _min_width=parameter_list_[4].split(",")[1].toDouble();

        _max_height=parameter_list_[5].split(",")[1].toDouble();
        _min_heigth=parameter_list_[6].split(",")[1].toDouble();

        _min_roundness=parameter_list_[7].split(",")[1].toDouble();
        _max_roundness=parameter_list_[8].split(",")[1].toDouble();

        _min_convexity=parameter_list_[9].split(",")[1].toDouble();
        _max_convexity=parameter_list_[10].split(",")[1].toDouble();

        _use_image_channle=parameter_list_[11].split(",")[1].toInt();
        _dyn_threshold_type=parameter_list_[12].split(",")[1].toInt();

        _dyn_threshold_=parameter_list_[13].split(",")[1].toDouble();
        _image_mean_number_dyn_one=parameter_list_[14].split(",")[1].toDouble();
        _image_mean_number_dyn_two=parameter_list_[15].split(",")[1].toDouble();

        _segmentation_stuff_closing_memenlt=parameter_list_[16].split(",")[1].toDouble();

        _camer_gain=parameter_list_[17].split(",")[1].toDouble();
        _camer_expource=parameter_list_[18].split(",")[1].toDouble();

        _combine_image_width=parameter_list_[19].split(",")[1].toDouble();
        _combine_image_height=parameter_list_[20].split(",")[1].toDouble();

        _use_area_filtration=parameter_list_[21].split(",")[1].toDouble();
        _use_width_filtration=parameter_list_[22].split(",")[1].toDouble();
        _use_height_filtration=parameter_list_[23].split(",")[1].toDouble();
        _use_roundness_filtration=parameter_list_[24].split(",")[1].toDouble();
        _use_convexity_filtration=parameter_list_[25].split(",")[1].toDouble();

    }
    return true;
}

void DealWithImage::WriteConfig()
{
    QString path_parameter_config_=QCoreApplication::applicationDirPath()+ "/ImageConfig/DealWithParameterConfig.csv";
    WriteParameterConfig(path_parameter_config_);

    QString path_roi_config_=QCoreApplication::applicationDirPath()+ "/ImageConfig/DealWithRoiConfig.csv";
    WriteRoiConfig(path_roi_config_);

}

bool DealWithImage::WriteRoiConfig(QString path_)
{
    QFile file_config_(path_);
    file_config_.setFileName(path_);
    QString config_data_=QString::fromUtf8("id,x,y,r\n");
    int count_=_segmentation_rois.count();
    for(int i=0;i<count_;i++)
    {
        config_data_+=QString::number(_segmentation_rois[i]._id)+","
                +QString::number(_segmentation_rois[i]._x_column)+","
                +QString::number(_segmentation_rois[i]._y_row)+","
                +QString::number(_segmentation_rois[i]._r)+"\n";
    }

    if(file_config_.open(QIODevice::WriteOnly))
    {
        file_config_.write(config_data_.toStdString().c_str());
    }
    file_config_.close();

    return true;
}

bool DealWithImage::WriteParameterConfig(QString path_)
{
    QFile file_parameter_(path_);
    file_parameter_.setFileName(path_);
    /*****同一用utf8*****/
    QString parameter_data_=QString::fromUtf8("name,value,mean\n");

    parameter_data_+=QString::fromUtf8("MaxArea,")+
            QString::number(_max_area)+
            QString::fromUtf8(",最大面积\n");

    parameter_data_+=QString::fromUtf8("MinArea,")+
            QString::number(_min_area)+
            QString::fromUtf8(",最小面积\n");

    parameter_data_+=QString::fromUtf8("MaXWidth,")+
            QString::number(_max_width)+
            QString::fromUtf8(",最大宽\n");

    parameter_data_+=QString::fromUtf8("MinWidth,")+
            QString::number(_min_width)+
            QString::fromUtf8(",最小宽\n");

    parameter_data_+=QString::fromUtf8("MaxHeight,")+
            QString::number(_max_height)+
            QString::fromUtf8(",最大高\n");

    parameter_data_+=QString::fromUtf8("MinHeight,")+
            QString::number(_min_heigth)+
            QString::fromUtf8(",最小高\n");

    parameter_data_+=QString::fromUtf8("MinRoundness,")+
            QString::number(_min_roundness)+
            QString::fromUtf8(",细胞最小圆度\n");

    parameter_data_+=QString::fromUtf8("MaxRoundness,")+
            QString::number(_max_roundness)+
            QString::fromUtf8(",细胞最大圆度\n");

    parameter_data_+=QString::fromUtf8("MinConvexity,")+
            QString::number(_min_convexity)+
            QString::fromUtf8(",最小凸度\n");

    parameter_data_+=QString::fromUtf8("MaxConvexity,")+
            QString::number(_max_convexity)+
            QString::fromUtf8(",最大凸度\n");

    parameter_data_+=QString::fromUtf8("UseImageChannle,")+
            QString::number(_use_image_channle)+
            QString::fromUtf8(",使用的通道0:gray 1:r 2:g 3:b 4:s 5:h 6:v\n");

    parameter_data_+=QString::fromLocal8Bit("DynThresholdType,")+
            QString::number(_dyn_threshold_type)+
            QString::fromUtf8(",动态阈值的方式 0:明 1:暗 2:等于 3:不等于\n");

    parameter_data_+=QString::fromUtf8("DynThreshold,")+
            QString::number(_dyn_threshold_)+
            QString::fromUtf8(",动态阈值\n");

    parameter_data_+=QString::fromUtf8("ImageMeanNumberDynOne,")+
            QString::number(_image_mean_number_dyn_one)+
            QString::fromUtf8(",动态分割时第一张图片平滑值\n");

    parameter_data_+=QString::fromUtf8("ImageMeanNumberDynTwo,")+
            QString::number(_image_mean_number_dyn_two)+
            QString::fromUtf8(",动态分割时第二张图片平滑值\n");

    parameter_data_+=QString::fromUtf8("SegmentationStuffClosingMemenlt,")+
            QString::number(_segmentation_stuff_closing_memenlt)+
            QString::fromUtf8(",距离因子认为相邻多小个像素是一个物体\n");

    parameter_data_+=QString::fromUtf8("CamerGain,")+
            QString::number(_camer_gain)+
            QString::fromUtf8(",相加增益\n");

    parameter_data_+=QString::fromUtf8("CamerExpource,")+
            QString::number(_camer_expource)+
            QString::fromUtf8(",相机曝光\n");

    parameter_data_+=QString::fromUtf8("CombineImageWidth,")+
            QString::number(_combine_image_width)+
            QString::fromUtf8(",拼接图片的宽\n");

    parameter_data_+=QString::fromUtf8("CombineImageHeight,")+
            QString::number(_combine_image_height)+
            QString::fromUtf8(",拼接图片的高\n");

    parameter_data_+=QString::fromUtf8("UseAreaFiltration,")+
                       QString::number(_use_area_filtration)+
                       QString::fromUtf8(",使用面积过滤细胞\n");

    parameter_data_+=QString::fromUtf8("UseWidthFiltration,")+
                       QString::number(_use_width_filtration)+
                       QString::fromUtf8(",使用宽过滤细胞\n");

    parameter_data_+=QString::fromUtf8("UseHeightFiltration,")+
                       QString::number(_use_height_filtration)+
                       QString::fromUtf8(",使用高过滤细胞\n");

    parameter_data_+=QString::fromUtf8("UseRoundnessFiltration,")+
                       QString::number(_use_roundness_filtration)+
                       QString::fromUtf8(",使用圆度过滤细胞\n");

    parameter_data_+=QString::fromUtf8("UseConvexityFiltration,")+
                       QString::number(_use_convexity_filtration)+
                       QString::fromUtf8(",使用凸度过滤细胞\n");

    if(file_parameter_.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file_parameter_);
        // out.setCodec("UTF-8");
        out << parameter_data_;
    }
    file_parameter_.close();
    return true;
}

QImage DealWithImage::GetImage(cv::Mat source_)
{
    //判断m的类型，可能是CV_8UC1  CV_8UC2  CV_8UC3  CV_8UC4
    switch(source_.type())
    {
    //QIamge 构造函数, ((const uchar *data, 宽(列),高(行), 一行共多少个（字节）通道，宽度*字节数，宏参数)
    case CV_8UC1:
    {
        QImage img((uchar *)source_.data,source_.cols,source_.rows,source_.cols * 1,QImage::Format_Grayscale8);
        return img;
    }
        break;
    case CV_8UC3:   //一个像素点由三个字节组成
    {
        //cvtColor(m,m,COLOR_BGR2RGB); BGR转RGB
        QImage img((uchar *)source_.data,source_.cols,source_.rows,source_.cols * 3,QImage::Format_RGB888);
        return img.rgbSwapped(); //opencv是BGR  Qt默认是RGB  所以RGB顺序转换
    }
        break;
    case CV_8UC4:
    {
        //QImage img((uchar *)_target_image.data,_target_image.cols,_target_image.rows,_target_image.cols * 4,QImage::Format_RGBA8888);
        QImage img((uchar *)source_.data,source_.cols,source_.rows,source_.cols * 4,QImage::Format_RGB32);
        return img;
    }
        break;
    default:
    {
        QImage img; //如果遇到一个图片均不属于这三种，返回一个空的图片
        return img;
    }
    }
}

cv::Mat DealWithImage::GetMat(QImage source_)
{
    /***初始化Mat****/
    cv::Mat mat = cv::Mat::zeros(source_.height(), source_.width(),source_.format());

    /****判断image的类型*****/
    switch(source_.format())
    {
    case QImage::Format_Grayscale8:
        /****灰度图***/
        mat = cv::Mat(source_.height(), source_.width(),
                      CV_8UC1,(void*)source_.constBits(),source_.bytesPerLine());
        break;
    case QImage::Format_RGB888:
        mat = cv::Mat(source_.height(), source_.width(),
                      CV_8UC3,(void*)source_.constBits(),source_.bytesPerLine());
        break;
    case QImage::Format_RGB32:
        mat = cv::Mat(source_.height(), source_.width(),
                      CV_8UC4,(void*)source_.constBits(),source_.bytesPerLine());
        break;

    case QImage::Format_ARGB32: ///4通道彩色 a通道为透明通道
        mat =cv::Mat(source_.height(), source_.width(),
                     CV_8UC4,(void*)source_.constBits(),source_.bytesPerLine());
        break;

    case QImage::Format_Indexed8:///单通道
        mat = cv::Mat(source_.height(), source_.width(),
                      CV_8UC1, (void*)source_.bits(), source_.bytesPerLine());
        break;

    default:
        ;
    }
    return mat;
}

void DealWithImage::SegmentationStuff()
{   
    if(_qimage.width()==0&&_qimage.height()==0)
    {
        return;
    }

    // cv::namedWindow("test",cv::WINDOW_NORMAL);

    cv::Mat source_image_;
    GetMat(_qimage).copyTo(source_image_);

    if(source_image_.rows>0&&source_image_.cols>0)
    {
        for(int i=0;i<_segmentation_rois.count();i++)
        {
            cv::Mat deal_with_image_;
            cv::Mat mask_image_;
            cv::Mat image_mean_one_;
            cv::Mat image_mean_two_;
            cv::Mat image_dyn_;
            cv::Mat image_operate_rect_roi_;

            cv::Range rows_y_rect_roi_;
            cv::Range columns_x_rect_roi_;

            /***创建处理的rect roi***/
            rows_y_rect_roi_=cv::Range(_segmentation_rois[i]._y_row
                                       - _segmentation_rois[i]._r,
                                       _segmentation_rois[i]._y_row
                                       + _segmentation_rois[i]._r);

            columns_x_rect_roi_=cv::Range(_segmentation_rois[i]._x_column
                                          - _segmentation_rois[i]._r,
                                          _segmentation_rois[i]._x_column
                                          + _segmentation_rois[i]._r);

            /*******把图片转成灰度图片*******/
            if(source_image_.channels()>1)
            {
                if(_use_image_channle<=3)
                {
                    vector<cv::Mat> rgb_images_;
                    cv::split(source_image_,rgb_images_);

                    switch (_use_image_channle)
                    {
                    /***灰度图片***/
                    case 0:
                        cv::cvtColor(source_image_,deal_with_image_,cv::COLOR_BGR2GRAY);
                        break;

                        /****r通道****/
                    case 1:
                        rgb_images_[0].copyTo(deal_with_image_);
                        break;

                        /***g通道****/
                    case 2:
                        rgb_images_[1].copyTo(deal_with_image_);
                        break;

                        /***b通道****/
                    case 3:
                        rgb_images_[2].copyTo(deal_with_image_);
                        break;
                    }
                    rgb_images_.clear();
                }
                else
                {
                    cv::Mat hsv_image_;
                    /***转成饱和图片***/
                    cv::cvtColor(source_image_,hsv_image_,cv::COLOR_BGR2HSV);
                    vector<cv::Mat> hsv_images_;
                    cv::split(hsv_image_,hsv_images_);

                    switch (_use_image_channle)
                    {
                    /***h通道***/
                    case 4:
                        hsv_images_[0].copyTo(deal_with_image_);
                        break;
                        /***s通道***/
                    case 5:
                        hsv_images_[1].copyTo(deal_with_image_);
                        break;
                        /***6 v通道***/
                    default:
                        hsv_images_[2].copyTo(deal_with_image_);
                        break;
                    }

                    hsv_image_.release();
                    hsv_images_.clear();
                }
            }
            else
            {
                cv::cvtColor(source_image_,deal_with_image_,cv::COLOR_BGR2GRAY);
            }

            /****记录使用的图片***/
            int w_deal_with_image_=deal_with_image_.cols;
            int h_deal_with_image_=deal_with_image_.rows;
            _use_image=GetImage(deal_with_image_).copy(0,
                                                       0,
                                                       w_deal_with_image_,
                                                       h_deal_with_image_);
            /****截取处理roi的正方型***/
            image_operate_rect_roi_=deal_with_image_(rows_y_rect_roi_,columns_x_rect_roi_);

            if(_image_mean_number_dyn_one>0)
            {
                cv::blur(image_operate_rect_roi_,
                         image_mean_one_,
                         cv::Size(_image_mean_number_dyn_one,_image_mean_number_dyn_one));
            }
            else
            {
                image_operate_rect_roi_.copyTo(image_mean_one_);
            }

            if(_image_mean_number_dyn_two>0)
            {
                cv::blur(image_operate_rect_roi_,
                         image_mean_two_,
                         cv::Size(_image_mean_number_dyn_two,_image_mean_number_dyn_two));
            }
            else
            {
                image_operate_rect_roi_.copyTo(image_mean_two_);
            }

            /***记录平滑的第一张图片***/
            int w_mean_image_one_=image_mean_one_.cols;
            int h_mean_image_one_=image_mean_one_.rows;
            _mean_image_one=GetImage(image_mean_one_).copy(0,
                                                           0,
                                                           w_mean_image_one_,
                                                           h_mean_image_one_);
            /***记录平滑的第二张图片***/
            int w_mean_image_two_=image_mean_two_.cols;
            int h_mean_image_two_=image_mean_two_.rows;
            _mean_image_two=GetImage(image_mean_two_).copy(0,
                                                           0,
                                                           w_mean_image_two_,
                                                           h_mean_image_two_);

            /****动态阈值分割****/
            image_dyn_ =cv::Mat(image_mean_two_.size(),CV_8UC1, cv::Scalar(0));

            int pixelsCount = image_mean_two_.rows * image_mean_two_.cols;
            for(int i = 0;i < pixelsCount; i++)
            {
                int g_src = image_mean_one_.data[i];
                int g_pre = image_mean_two_.data[i];

                switch(_dyn_threshold_type)
                {
                /***平滑图片1比平滑图片2亮***/
                case 0:
                    if (g_src >= g_pre + _dyn_threshold_)
                    {
                        image_dyn_.data[i] = 255;
                    }
                    break;
                    /***平滑图片1比平滑图片暗***/
                case 1:
                    if (g_src <= g_pre - _dyn_threshold_)
                    {
                        image_dyn_.data[i] = 255;
                    }
                    break;

                    /***平滑图片1与平滑图片相等***/
                case 2:
                    if (g_src >= g_pre - _dyn_threshold_ && g_src <= g_pre + _dyn_threshold_)
                    {
                        image_dyn_.data[i] = 255;
                    }
                    break;

                    /***平滑图片1与平滑图片2不相等***/
                case 3:
                    if (g_src < g_pre - _dyn_threshold_ || g_src > g_pre + _dyn_threshold_)
                    {
                        image_dyn_.data[i] = 255;
                    }
                    break;
                }
            }

            //            cv::imshow("test",image_dyn_);
            //            cv::waitKey(0);

            /***进行闭运算***/
            if(_segmentation_stuff_closing_memenlt>0)
            {
                cv::Mat element_closeing_;
                element_closeing_=cv::getStructuringElement(cv::MORPH_ELLIPSE,
                                                            cv::Size(_segmentation_stuff_closing_memenlt,_segmentation_stuff_closing_memenlt));
                cv::morphologyEx(image_dyn_,image_dyn_,cv::MORPH_CLOSE,element_closeing_);
                element_closeing_.release();
            }

            /****创建感兴趣区域****/
            mask_image_=cv::Mat::zeros(image_dyn_.size(),CV_8UC1);

            cv::circle(mask_image_,
                       cv::Point( _segmentation_rois[i]._r, _segmentation_rois[i]._r),
                       _segmentation_rois[i]._r,
                       cv::Scalar(255),
                       -1,/***小于零填满****/
                       8,
                       0);

            cv::bitwise_and(mask_image_,image_dyn_,image_dyn_);

            /****轮廓查找***/
            vector<vector<cv::Point>> contours_;
            vector<cv::Vec4i> hierarchy_;
            cv::findContours(image_dyn_,
                             contours_,
                             hierarchy_,
                             cv::RETR_EXTERNAL,
                             cv::CHAIN_APPROX_SIMPLE);

            int count_=contours_.size();

            if(count_>0)
            {
                /****找到的轮廓画到****/
                cv::drawContours(source_image_(rows_y_rect_roi_,columns_x_rect_roi_),
                                 contours_,
                                 -1,cv::Scalar(0, 0, 255),
                                 3);
                for(int n_=0;n_<count_;n_++)
                {
                    cv::RotatedRect re_;
                    re_=cv::minAreaRect(contours_[n_]);
                    bool ok_=true;

                    /***是否在宽范围里面***/
                    if(_use_width_filtration>0)
                    {
                        if(re_.size.width<_max_width&&re_.size.width>_min_width)
                        {
                        }
                        else
                        {
                            ok_=false;
                        }
                    }

                    /***是否在高范围里面***/
                    if(_use_height_filtration>0)
                    {
                        if(re_.size.height<_max_height
                            &&re_.size.height>_min_heigth
                            &&ok_==true)
                        {
                        }
                        else
                        {
                            ok_=false;
                        }
                    }

                    /***是否在面积范围里面***/
                    if(_use_area_filtration>0)
                    {
                        if(re_.size.area()<_max_area&&re_.size.area()>_min_area&&ok_==true)
                        {
                        }
                        else
                        {
                            ok_=false;
                        }
                    }

                    /***是否在圆度范围里面***/
                    double area_ = contourArea(contours_[n_]);
                    double perimeter_ =cv::arcLength(contours_[n_],true);/***计算轮廓周长***/
                    double circularity_ = 4 * CV_PI * area_ / (perimeter_ * perimeter_);

                    if(_use_roundness_filtration>0)
                    {
                        if(circularity_<_max_roundness&&circularity_>_min_roundness&&ok_==true)
                        {
                        }
                        else
                        {
                            ok_=false;
                        }
                    }

                    double convexity_ = perimeter_ * perimeter_ / area_;
                    if(_use_convexity_filtration>0)
                    {
                        if(convexity_<_max_convexity&&convexity_>_min_convexity&&ok_==true)
                        {
                        }
                        else
                        {
                            ok_=false;
                        }
                    }

                    if(ok_==true)
                    {
                        ResultStructure result_s_;
                        result_s_._number=n_;
                        result_s_._area=re_.size.area();
                        result_s_._width=re_.size.width;
                        result_s_._height=re_.size.height;
                        result_s_._x=re_.center.x+columns_x_rect_roi_.start;
                        result_s_._y=re_.center.y+rows_y_rect_roi_.start;
                        result_s_._angle=re_.angle;
                        /****计算圆度***/
                        result_s_._round=circularity_;
                        /****计算凸度***/
                        result_s_._convexity=convexity_;

                        /****获取平均灰度***/
                        cv::Rect rect_ = boundingRect(contours_[n_]);
                        cv::Mat roi_ = image_operate_rect_roi_(rect_);
                        cv::Scalar mean_image = cv::mean(roi_);
                        double average_gray = mean_image.val[0];
                        result_s_._mean=average_gray;
                        roi_.release();
                        _segmentation_rois[i]._segmentation_results.append(result_s_);
                    }
                }
            }

            contours_.clear();
            hierarchy_.clear();

            deal_with_image_.release();
            image_operate_rect_roi_.release();
            image_mean_one_.release();
            image_mean_two_.release();
            mask_image_.release();
            image_dyn_.release();
        }
    }

    int w_source_=source_image_.cols;
    int h_source_=source_image_.rows;
    _result_image=GetImage(source_image_).copy(0,0,w_source_,h_source_);
    source_image_.release();
}

void DealWithImage::ClearSegmentationResult()
{
    if(_result_image.isNull()==false)
    {
        _result_image=QImage();
    }

    if(_use_image.isNull()==false)
    {
        _use_image=QImage();
    }

    if(_mean_image_one.isNull()==false)
    {
        _mean_image_one=QImage();
    }

    if(_mean_image_two.isNull()==false)
    {
        _mean_image_two=QImage();
    }

    for(int i=0;i<_segmentation_rois.size();i++)
    {
        _segmentation_rois[i]._segmentation_results.clear();;
    }
}

void DealWithImage::checkRoiBiggerBoard()
{
    if(DealWithImage::getStatic()->_qimage.width()>0
            && DealWithImage::getStatic()->_qimage.height()>0)
    {

        qreal image_width_=DealWithImage::getStatic()->_qimage.width();
        qreal image_height_=DealWithImage::getStatic()->_qimage.height();

        for(int i=0;i<DealWithImage::getStatic()->_segmentation_rois.size();i++)
        {
            double r_=DealWithImage::getStatic()->_segmentation_rois[i]._r;
            double x_=DealWithImage::getStatic()->_segmentation_rois[i]._x_column;
            double y_=DealWithImage::getStatic()->_segmentation_rois[i]._y_row;
            if(x_-r_<0)
            {
                DealWithImage::getStatic()->_segmentation_rois[i]._x_column-=r_-x_;
                x_=DealWithImage::getStatic()->_segmentation_rois[i]._x_column;
            }
            if(y_-r_<0)
            {
                DealWithImage::getStatic()->_segmentation_rois[i]._y_row-=r_-y_;
                y_=DealWithImage::getStatic()->_segmentation_rois[i]._y_row;
            }

            if(x_+r_>image_width_)
            {
                r_-=x_+r_-image_width_;
            }

            if(y_+r_>image_height_)
            {
                r_-=y_+r_-image_height_;
            }
            DealWithImage::getStatic()->_segmentation_rois[i]._r=r_;
        }
    }
}
