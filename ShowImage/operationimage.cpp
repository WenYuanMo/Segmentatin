#include "operationimage.h"

operationimage::operationimage(QWidget *parent) : QWidget(parent)
{
    _scale=1;
    _dy=0;
    _dx=0;
    _start_x=0;
    _start_y=0;
    _mouse_down=false;
//    _board_width=this->width();
//    _board_height=this->height();

    _board_width=DealWithImage::getStatic()->_combine_image_width;
    _board_height=DealWithImage::getStatic()->_combine_image_height;

    _font.setFamily("Microsoft YaHei");
    _font.setPointSize(20);
    _font.setBold(true);
    _font.setLetterSpacing(QFont::AbsoluteSpacing, 3);
    _pen.setBrush(Qt::green);
    _pen.setWidth(10);
    this->setMouseTracking(true);
    _labBoardCoor=new QLabel(this);
    _labBoardCoor->setGeometry(10,0,300,30);
    _labBoardCoor->setText("0,0");
    _ope_image_type._ope_image=OpeImageEnum::_mover_board;
    _ope_image_type._move_roi_type=MoveRoiEnum::_none;
    _ope_image_type._ope_roi_index=-1;
}

void operationimage::fitWindow()
{
    /***获取当前的长度****/
    qreal win_width_=this->width();
    qreal win_height_=this->height();

    if(DealWithImage::getStatic()->_qimage.width()>0&&DealWithImage::getStatic()->_qimage.height()>0)
    {
        _board_width=DealWithImage::getStatic()->_qimage.width();
        _board_height=DealWithImage::getStatic()->_qimage.height();
    }
//    else
//    {
//        _board_width=win_width_;
//        _board_height=win_height_;
//    }

    /****获取窗口与画板比例***/
    qreal width_scale_=win_width_/_board_width;
    qreal height_scale_=win_height_/_board_height;

    /***计算缩放****/
    if(width_scale_<height_scale_)
    {
        _scale=width_scale_;
    }
    else
    {
        _scale=height_scale_;
    }

    /***偏移为零****/
    _dx=0;
    _dy=0;

    /****计算适合的长宽*****/
    qreal fitWidth_=_board_width*_scale;
    qreal fitHeight_=_board_height*_scale;

    /******计算开始坐标*******/
    _start_x=(win_width_-fitWidth_)/2;
    _start_y=(win_height_-fitHeight_)/2;
    /*****更新图片*****/
    this->update();
}

void operationimage::setMove(qreal dx_, qreal dy_)
{
    _dx=dx_;
    _dy=dy_;
    this->update();
}

void operationimage::refleshShow()
{
    this->update();
}

void operationimage::setScale(qreal scale_)
{
    _scale*=scale_;
    this->update();
}

void operationimage::setBoardSize(qreal width_, qreal height_)
{
    _board_width=width_;
    _board_height=height_;
}

QPointF operationimage::getPointInBoard(QPointF point_)
{
    QPointF po_=point_;
    po_.setX((point_.x()-this->_start_x-this->_dx)/_scale);
    po_.setY((point_.y()-this->_start_y-this->_dy)/_scale);
    return  po_;
}

bool operationimage::getPointInBoard(double x_,double y_,QPointF* point_)
{
    point_->setX((x_-this->_start_x-this->_dx)/_scale);
    point_->setY((y_-this->_start_y-this->_dy)/_scale);
    return  true;
}

QPointF operationimage::getPointInWin(QPointF point_)
{
    QPointF po_=point_;
    po_.setX(point_.x()*_scale+this->_start_x+this->_dx);
    po_.setY(point_.y()*_scale+this->_start_y+this->_dy);
    return  po_;
}

bool operationimage::getPointInWin(double x_,double y_,QPointF* point_)
{
    point_->setX(x_*_scale+this->_start_x+this->_dx);
    point_->setY(y_*_scale+this->_start_y+this->_dy);
    return  true;
}

void operationimage::addRoi()
{
    if(DealWithImage::getStatic()->_qimage.width()==0&&DealWithImage::getStatic()->_qimage.height()==0)
    {
        return;
    }

    SegmentationRoi sr_;
    sr_._r=100;
    sr_._y_row=100;
    sr_._x_column=100;
    sr_._id=DealWithImage::getStatic()->_segmentation_rois.size();
    DealWithImage::getStatic()->_segmentation_rois.append(sr_);
    this->update();
}

void operationimage::setOperationType(OpeImageEnum ope_type_)
{
    _ope_image_type._ope_image=ope_type_;
}

void operationimage::wheelEvent(QWheelEvent *event)
{
    if(DealWithImage::getStatic()->_qimage.width()==0
            && DealWithImage::getStatic()->_qimage.height()==0)
    {
        return;
    }

    /******获取鼠标窗口坐标****/
    QPointF win_point1_=event->position();
    /****鼠标点在画板中没有缩放的坐标****/
    qreal original_x_=(win_point1_.x()-this->_start_x-this->_dx)/_scale;
    qreal original_y_=(win_point1_.y()-this->_start_y-this->_dy)/_scale;

    if(event->angleDelta().y()>0)//缩放
    {
        _scale*=1.2;
    }
    else
    {
        _scale*=0.8;
    }

    QPointF win_point2_;
    /******缩放后鼠标原来画板中的坐标对应窗口坐标******/
    win_point2_.setX(original_x_*_scale+this->_start_x+this->_dx);
    win_point2_.setY(original_y_*_scale+this->_start_y+this->_dy);
    /****更新开始坐标*****/
    _start_x=_start_x+((win_point1_.x()-win_point2_.x()));
    _start_y=_start_y+((win_point1_.y()-win_point2_.y()));

    this->update();
}

void operationimage::mousePressEvent(QMouseEvent *event)
{
    if(DealWithImage::getStatic()->_qimage.width()==0
            && DealWithImage::getStatic()->_qimage.height()==0)
    {
        return;
    }
    /*****判断鼠标是不是左键是的话返回******/
    if ( event->button() == Qt::LeftButton )
    {
        _mouse_down=true;
        _down_point=event->pos();
        _last_point=event->pos();

        switch (_ope_image_type._ope_image)
        {
        case OpeImageEnum::_mover_board:
            break;
        case OpeImageEnum::_move_roi:
        {
            _ope_image_type._move_roi_type=MoveRoiEnum::_none;
            _ope_image_type._ope_roi_index=-1;

            /***转换这个坐标点****/
            QPointF po_= getPointInBoard(_down_point);
            for(int i=0;i<DealWithImage::getStatic()->_segmentation_rois.size();i++)
            {
                double dx_=abs(po_.x()-DealWithImage::getStatic()->_segmentation_rois[i]._x_column);
                double dy_=abs(po_.y()-DealWithImage::getStatic()->_segmentation_rois[i]._y_row);
                /***开平方***/
                double distance_=sqrt((dx_*dx_)+(dy_*dy_));
                /***选择在边缘***/
                /***选择移动***/
                if(distance_<DealWithImage::getStatic()->_segmentation_rois[i]._r-10)
                {
                    _ope_image_type._move_roi_type=MoveRoiEnum::_move_position;
                    _ope_image_type._ope_roi_index=i;
                    i=DealWithImage::getStatic()->_segmentation_rois.size();
                }
                else
                {
                    if(distance_<DealWithImage::getStatic()->_segmentation_rois[i]._r+10
                            &&distance_>DealWithImage::getStatic()->_segmentation_rois[i]._r-10)
                    {
                        _ope_image_type._move_roi_type=MoveRoiEnum::_move_edge;
                         _ope_image_type._ope_roi_index=i;
                        i=DealWithImage::getStatic()->_segmentation_rois.size();
                    }
                }
            }
        }
            break;
        case OpeImageEnum::_delete_roi:
        {
            _ope_image_type._move_roi_type=MoveRoiEnum::_none;
            _ope_image_type._ope_roi_index=-1;

            QPointF po_= getPointInBoard(_down_point);
            for(int i=0;i<DealWithImage::getStatic()->_segmentation_rois.size();i++)
            {
                double dx_=abs(po_.x()-DealWithImage::getStatic()->_segmentation_rois[i]._x_column);
                double dy_=abs(po_.y()-DealWithImage::getStatic()->_segmentation_rois[i]._y_row);
                /***开平方***/
                double distance_=sqrt((dx_*dx_)+(dy_*dy_));
                /***确定要删除的roi***/
                if(distance_<DealWithImage::getStatic()->_segmentation_rois[i]._r-10)
                {
                    DealWithImage::getStatic()->_segmentation_rois.removeAt(i);
                    i=DealWithImage::getStatic()->_segmentation_rois.size();
                }
            }
            this->update();
        }
            break;
        }
    }
}

void operationimage::mouseMoveEvent(QMouseEvent *event)
{
    if(DealWithImage::getStatic()->_qimage.width()==0
            && DealWithImage::getStatic()->_qimage.height()==0)
    {
        return;
    }

    if(_mouse_down==true)
    {
        _last_point=event->pos();

        switch (_ope_image_type._ope_image)
        {
        case OpeImageEnum::_mover_board:
        {
            _dx+=_last_point.x()-_down_point.x();
            _dy+=_last_point.y()-_down_point.y();
        }
            break;

        case OpeImageEnum::_move_roi:
        {
            switch (_ope_image_type._move_roi_type)
            {
            case MoveRoiEnum::_move_edge:
            {
                QPointF down_po_=getPointInBoard(_down_point);
                QPointF last_po_=getPointInBoard(_last_point);

                double dx_=abs(last_po_.x()-DealWithImage::getStatic()->_segmentation_rois[_ope_image_type._ope_roi_index]._x_column);
                double dy_=abs(last_po_.y()-DealWithImage::getStatic()->_segmentation_rois[_ope_image_type._ope_roi_index]._y_row);
                /***开平方***/
                double distance_=sqrt((dx_*dx_)+(dy_*dy_));

                qreal new_center_x_=DealWithImage::getStatic()->_segmentation_rois[_ope_image_type._ope_roi_index]._x_column;
                qreal new_center_y_=DealWithImage::getStatic()->_segmentation_rois[_ope_image_type._ope_roi_index]._y_row;

                /***防止超出范围***/
                if(new_center_x_-distance_>0
                    &&new_center_y_-distance_>0
                    &&new_center_x_+distance_<_board_width
                    &&new_center_y_+distance_<_board_height)
                {
                    DealWithImage::getStatic()->_segmentation_rois[_ope_image_type._ope_roi_index]._r=distance_;
                }
            }
                break;

            case MoveRoiEnum::_move_position:
            {
                QPointF down_po_=getPointInBoard(_down_point);
                QPointF last_po_=getPointInBoard(_last_point);

                qreal dx_=last_po_.x()-down_po_.x();
                qreal dy_=last_po_.y()-down_po_.y();

                qreal new_center_x_=DealWithImage::getStatic()->_segmentation_rois[_ope_image_type._ope_roi_index]._x_column+dx_;
                qreal new_center_y_=DealWithImage::getStatic()->_segmentation_rois[_ope_image_type._ope_roi_index]._y_row+dy_;
                /***防止超出范围***/
                if(new_center_x_-DealWithImage::getStatic()->_segmentation_rois[_ope_image_type._ope_roi_index]._r>0
                    &&new_center_y_-DealWithImage::getStatic()->_segmentation_rois[_ope_image_type._ope_roi_index]._r>0
                    &&new_center_x_+DealWithImage::getStatic()->_segmentation_rois[_ope_image_type._ope_roi_index]._r<_board_width
                    &&new_center_y_+DealWithImage::getStatic()->_segmentation_rois[_ope_image_type._ope_roi_index]._r<_board_height)
                {
                    DealWithImage::getStatic()->_segmentation_rois[_ope_image_type._ope_roi_index]._x_column=new_center_x_;
                    DealWithImage::getStatic()->_segmentation_rois[_ope_image_type._ope_roi_index]._y_row=new_center_y_;
                }
            }
            break;
            }
        }
            break;

        case OpeImageEnum::_delete_roi:
            break;
        }

         _down_point=_last_point;
        this->update();
    }
    else
    {
        QPointF point_=event->pos();
        qreal x_=(point_.x()-this->_start_x-this->_dx)/_scale;
        qreal y_=(point_.y()-this->_start_y-this->_dy)/_scale;

        if(x_<0||x_>_board_width
                ||y_<0||y_>_board_height)
        {
            x_=0;
            y_=0;
        }

        QColor rgb_=DealWithImage::getStatic()->_qimage.pixel(x_,y_);

        _labBoardCoor->setText(QString::number(x_)
                               +QString::fromStdString(",")
                               +QString::number(y_)
                               +QString::fromStdString("-Rgb:")
                               +QString::number(rgb_.red())
                               +QString::fromStdString(",")
                               +QString::number(rgb_.green())
                               +QString::fromStdString(",")
                               +QString::number(rgb_.blue()));
    }
}

void operationimage::mouseReleaseEvent(QMouseEvent *event)
{
    /****去掉警告**/
    Q_UNUSED(event);

    if(DealWithImage::getStatic()->_qimage.width()==0
            && DealWithImage::getStatic()->_qimage.height()==0)
    {
        return;
    }

    if(_mouse_down==true)
    {
        _mouse_down=false;
    }
}

void operationimage::paintEvent(QPaintEvent *event)
{
    if(DealWithImage::getStatic()->_qimage.width()==0&&DealWithImage::getStatic()->_qimage.height()==0)
    {
        return;
    }
    QPainter painter(this);
    QRect blackboard_=event->rect();
    painter.fillRect(blackboard_,Qt::black);
    qreal moveX_=this->_start_x+this->_dx;
    qreal moveY_=this->_start_y+this->_dy;

    /***根据参数创建坐标系****/
    painter.translate(moveX_,moveY_);
    painter.scale(_scale,_scale);

    painter.drawImage(0,0,DealWithImage::getStatic()->_qimage);

    if(DealWithImage::getStatic()->_show_result_image==true)
    {
        if(DealWithImage::getStatic()->_result_image.width()!=0
            &&DealWithImage::getStatic()->_result_image.height()!=0)
        {
            painter.drawImage(0,0,DealWithImage::getStatic()->_result_image);
        }
    }

    painter.setFont(_font);
    painter.setPen(_pen);

    int stuff_number_=0;

    /****显示roi****/
    for(int i=0;i<DealWithImage::getStatic()->_segmentation_rois.size();i++)
    {
        painter.drawEllipse(DealWithImage::getStatic()->_segmentation_rois[i]._x_column
                                -DealWithImage::getStatic()->_segmentation_rois[i]._r,
                            DealWithImage::getStatic()->_segmentation_rois[i]._y_row
                                -DealWithImage::getStatic()->_segmentation_rois[i]._r,
                            DealWithImage::getStatic()->_segmentation_rois[i]._r*2,
                            DealWithImage::getStatic()->_segmentation_rois[i]._r*2);

        painter.drawText(DealWithImage::getStatic()->_segmentation_rois[i]._x_column,
                         DealWithImage::getStatic()->_segmentation_rois[i]._y_row,
                         QString::number( DealWithImage::getStatic()->_segmentation_rois[i]._id));

        stuff_number_+=DealWithImage::getStatic()->_segmentation_rois[i]._segmentation_results.size();
        /*****显示点****/
        for(int j=0;j<DealWithImage::getStatic()->_segmentation_rois[i]._segmentation_results.size();j++)
        {
            painter.drawPoint(DealWithImage::getStatic()->_segmentation_rois[i]._segmentation_results[j]._x,
                              DealWithImage::getStatic()->_segmentation_rois[i]._segmentation_results[j]._y);

            QString mes_=QString::number(DealWithImage::getStatic()->_segmentation_rois[i]._segmentation_results[j]._number);

            if(DealWithImage::getStatic()->_show_segmentation_result_area==true)
            {
                mes_+=" A:"+QString::number(DealWithImage::getStatic()->_segmentation_rois[i]._segmentation_results[j]._area);
            }

            if(DealWithImage::getStatic()->_show_segmentation_result_width==true)
            {
                mes_+=" W:"+QString::number(DealWithImage::getStatic()->_segmentation_rois[i]._segmentation_results[j]._width);
            }

            if(DealWithImage::getStatic()->_show_segmentation_result_height==true)
            {
                mes_+=" H:"+QString::number(DealWithImage::getStatic()->_segmentation_rois[i]._segmentation_results[j]._height);
            }

            if(DealWithImage::getStatic()->_show_segmentation_result_roundness==true)
            {
                mes_+=" R:"+QString::number(DealWithImage::getStatic()->_segmentation_rois[i]._segmentation_results[j]._round);
            }

            if(DealWithImage::getStatic()->_show_segmentation_result_convexity==true)
            {
                mes_+=" C:"+QString::number(DealWithImage::getStatic()->_segmentation_rois[i]._segmentation_results[j]._convexity);
            }

            if(DealWithImage::getStatic()->_show_segmentation_result_mean==true)
            {
                mes_+=" M:"+QString::number(DealWithImage::getStatic()->_segmentation_rois[i]._segmentation_results[j]._mean);
            }

            painter.drawText(DealWithImage::getStatic()->_segmentation_rois[i]._segmentation_results[j]._x,
                             DealWithImage::getStatic()->_segmentation_rois[i]._segmentation_results[j]._y,
                             mes_);
        }
    }

    /***显示处理的图片***/
    if(DealWithImage::getStatic()->_show_use_image==true
        ||DealWithImage::getStatic()->_show_mean_image_one==true
        ||DealWithImage::getStatic()->_show_mean_image_two==true)
    {
        /***显示图片的坐标*****/
        int show_image_x=_board_width+10;
        int show_image_y=0;

        if(DealWithImage::getStatic()->_show_use_image==true)
        {
            if(DealWithImage::getStatic()->_use_image.width()!=0
                &&DealWithImage::getStatic()->_use_image.height()!=0)
            {
                painter.drawImage(show_image_x,show_image_y,DealWithImage::getStatic()->_use_image);
                show_image_x+=_board_width+10;
            }
        }

        if(DealWithImage::getStatic()->_show_mean_image_one==true)
        {
            if(DealWithImage::getStatic()->_mean_image_one.width()!=0
                &&DealWithImage::getStatic()->_mean_image_one.height()!=0)
            {
                painter.drawImage(show_image_x,show_image_y,DealWithImage::getStatic()->_mean_image_one);
                show_image_x+=_board_width+10;
            }
        }

        if(DealWithImage::getStatic()->_show_mean_image_two==true)
        {
            if(DealWithImage::getStatic()->_mean_image_two.width()!=0
                &&DealWithImage::getStatic()->_mean_image_two.height()!=0)
            {
                painter.drawImage(show_image_x,show_image_y,DealWithImage::getStatic()->_mean_image_two);
                show_image_x+=_board_width+10;
            }
        }
    }

    /***显示当前分析个数***/
    _font.setPointSize(100);
    painter.setFont(_font);
    painter.drawText(0,0,QString("当前分割物体数:")+QString::number(stuff_number_));

    _font.setPointSize(20);
    painter.setFont(_font);

    painter.end();
}
