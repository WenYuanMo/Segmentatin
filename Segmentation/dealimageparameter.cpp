#include "dealimageparameter.h"
#include "ui_dealimageparameter.h"

DealImageParameter::DealImageParameter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DealImageParameter)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window);
    this->setWindowTitle("分割");

    /*****加载参数****/
    ui->dsb_area_max->setValue(DealWithImage::getStatic()->_max_area);
    ui->dsb_area_min->setValue(DealWithImage::getStatic()->_min_area);

    ui->dsb_width_max->setValue(DealWithImage::getStatic()->_max_width);
    ui->dsb_width_min->setValue(DealWithImage::getStatic()->_min_width);

    ui->dsb_height_max->setValue(DealWithImage::getStatic()->_max_height);
    ui->dsb_height_min->setValue(DealWithImage::getStatic()->_min_heigth);

    ui->dsb_roundness_min->setValue(DealWithImage::getStatic()->_min_roundness);
    ui->dsb_roundness_max->setValue(DealWithImage::getStatic()->_max_roundness);

    ui->dsb_convexity_min->setValue(DealWithImage::getStatic()->_min_convexity);
    ui->dsb_convexity_max->setValue(DealWithImage::getStatic()->_max_convexity);

    ui->combobox_dyn_orientation->addItem(QString("Light"));
    ui->combobox_dyn_orientation->addItem(QString("Dark"));

    if(DealWithImage::getStatic()->_dyn_threshold_type==0)
    {
        ui->combobox_dyn_orientation->setCurrentIndex(0);
    }
    else
    {
        ui->combobox_dyn_orientation->setCurrentIndex(1);
    }
    QObject::connect(ui->combobox_dyn_orientation,
                     &QComboBox::currentTextChanged,
                     this,
                     &DealImageParameter::on_combobox_dyn_orientation_currentTextChanged1);

    ui->combobox_check_channle_type->addItem(QString("Gray"));

    ui->combobox_check_channle_type->addItem(QString("R"));
    ui->combobox_check_channle_type->addItem(QString("G"));
    ui->combobox_check_channle_type->addItem(QString("B"));

    ui->combobox_check_channle_type->addItem(QString("H"));
    ui->combobox_check_channle_type->addItem(QString("S"));
    ui->combobox_check_channle_type->addItem(QString("V"));

    switch(DealWithImage::getStatic()->_use_image_channle)
    {
    case 0:
        ui->combobox_check_channle_type->setCurrentText("Gray");
        break;

    case 1:
        ui->combobox_check_channle_type->setCurrentText("R");
        break;

    case 2:
        ui->combobox_check_channle_type->setCurrentText("G");
        break;

    case 3:
        ui->combobox_check_channle_type->setCurrentText("B");
        break;

    case 4:
        ui->combobox_check_channle_type->setCurrentText("H");
        break;

    case 5:
        ui->combobox_check_channle_type->setCurrentText("S");
        break;

    case 6:
        ui->combobox_check_channle_type->setCurrentText("V");
        break;
    }

    QObject::connect(ui->combobox_check_channle_type,
                     &QComboBox::currentTextChanged,
                     this,
                     &DealImageParameter::on_combobox_check_channle_type_currentTextChanged1);

    ui->spinbox_dyn_number->setValue(DealWithImage::getStatic()->_dyn_threshold_);
    ui->spinbox_mean_one_image_value->setValue(DealWithImage::getStatic()->_image_mean_number_dyn_one);
    ui->spinbox_mean_two_image_value->setValue(DealWithImage::getStatic()->_image_mean_number_dyn_two);
    ui->spinbox_segmentation_stuff_min_distance->setValue(DealWithImage::getStatic()->_segmentation_stuff_closing_memenlt);

    if(DealWithImage::getStatic()->_use_area_filtration>0)
    {
        ui->checkbox_use_area_filtration->setChecked(true);
    }
    else
    {
        ui->checkbox_use_area_filtration->setChecked(false);
    }

    if(DealWithImage::getStatic()->_use_width_filtration>0)
    {
        ui->checkbox_use_width_filtration->setChecked(true);
    }
    else
    {
        ui->checkbox_use_width_filtration->setChecked(false);
    }

    if(DealWithImage::getStatic()->_use_height_filtration>0)
    {
        ui->checkbox_use_height_filtration->setChecked(true);
    }
    else
    {
        ui->checkbox_use_height_filtration->setChecked(false);
    }

    if(DealWithImage::getStatic()->_use_roundness_filtration>0)
    {
        ui->checkbox_use_roundness_filtration->setChecked(true);
    }
    else
    {
        ui->checkbox_use_roundness_filtration->setChecked(false);
    }

    if(DealWithImage::getStatic()->_use_convexity_filtration>0)
    {
        ui->checkbox_use_convexity_filtration->setChecked(true);
    }
    else
    {
        ui->checkbox_use_convexity_filtration->setChecked(false);
    }

    if(DealWithImage::getStatic()->_show_result_image)
    {
        ui->checkBox_show_result_image->setChecked(true);
    }
    else
    {
        ui->checkBox_show_result_image->setChecked(false);
    }

    if(DealWithImage::getStatic()->_show_use_image)
    {
        ui->checkBox_show_use_image->setChecked(true);
    }
    else
    {
        ui->checkBox_show_use_image->setChecked(false);
    }

    if(DealWithImage::getStatic()->_show_mean_image_one)
    {
        ui->checkBox_show_mean_image_one->setChecked(true);
    }
    else
    {
        ui->checkBox_show_mean_image_one->setChecked(false);
    }

    if(DealWithImage::getStatic()->_show_mean_image_two)
    {
        ui->checkBox_show_mean_image_two->setChecked(true);
    }
    else
    {
        ui->checkBox_show_mean_image_two->setChecked(false);
    }

    if(DealWithImage::getStatic()->_show_segmentation_result_area)
    {
        ui->checkBox_show_image_area->setChecked(true);
    }
    else
    {
        ui->checkBox_show_image_area->setChecked(false);
    }

    if(DealWithImage::getStatic()->_show_segmentation_result_width)
    {
        ui->checkBox_show_image_width->setChecked(true);
    }
    else
    {
        ui->checkBox_show_image_width->setChecked(false);
    }

    if(DealWithImage::getStatic()->_show_segmentation_result_height)
    {
        ui->checkBox_show_image_height->setChecked(true);
    }
    else
    {
        ui->checkBox_show_image_height->setChecked(false);
    }

    if(DealWithImage::getStatic()->_show_segmentation_result_roundness)
    {
        ui->checkBox_show_image_roundness->setChecked(true);
    }
    else
    {
        ui->checkBox_show_image_roundness->setChecked(false);
    }

    if(DealWithImage::getStatic()->_show_segmentation_result_convexity)
    {
        ui->checkBox_show_image_convexity->setChecked(true);
    }
    else
    {
        ui->checkBox_show_image_convexity->setChecked(false);
    }

    if(DealWithImage::getStatic()->_show_segmentation_result_mean)
    {
        ui->checkBox_show_image_mean->setChecked(true);
    }
    else
    {
        ui->checkBox_show_image_mean->setChecked(false);
    }

    /****创建表格*****/
//    QStringList headText_;
//    headText_.push_back("id");
//    headText_.push_back("number");
//    headText_.push_back("x");
//    headText_.push_back("y");
//    headText_.push_back("area");
//    headText_.push_back("angle");
//    headText_.push_back("width");
//    headText_.push_back("height");
//    headText_.push_back("mean");
//    headText_.push_back("circular");
//    headText_.push_back("convexity");

//    QList<int> headWidth_;
//    headWidth_.push_back(50);
//    headWidth_.push_back(80);
//    headWidth_.push_back(150);
//    headWidth_.push_back(150);
//    headWidth_.push_back(150);
//    headWidth_.push_back(150);
//    headWidth_.push_back(150);
//    headWidth_.push_back(150);
//    headWidth_.push_back(150);
//    headWidth_.push_back(150);
//    headWidth_.push_back(150);

//    int headcount_ = headText_.size();
//    ui->table_widget_cell_result->setColumnCount(headcount_);
//    ui->table_widget_cell_result->setHorizontalHeaderLabels(headText_);
//    for(int i=0;i<headWidth_.size();i++)
//    {
//        ui->table_widget_cell_result->setColumnWidth(i,headWidth_[i]);
//    }
//    ui->table_widget_cell_result->setSelectionBehavior(QAbstractItemView::SelectRows);
//    ui->table_widget_cell_result->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    ui->table_widget_cell_result->setSelectionMode(QAbstractItemView::SingleSelection);
//    ui->table_widget_cell_result->verticalHeader()->setVisible(false);
//    ui->table_widget_cell_result->horizontalHeader()->setStretchLastSection(true);
//    ui->table_widget_cell_result->horizontalHeader()->setHighlightSections(false);
//    ui->table_widget_cell_result->verticalHeader()->setDefaultSectionSize(20);
//    ui->table_widget_cell_result->verticalHeader()->setHighlightSections(false);
}

DealImageParameter::~DealImageParameter()
{
    delete ui;
}


void DealImageParameter::on_rbtn_move_board_clicked()
{
    ui->widget_operation_image->setOperationType(OpeImageEnum::_mover_board);
}

void DealImageParameter::on_rbtn_move_roi_clicked()
{
     ui->widget_operation_image->setOperationType(OpeImageEnum::_move_roi);
}

void DealImageParameter::on_rbtn_delete_roi_clicked()
{
     ui->widget_operation_image->setOperationType(OpeImageEnum::_delete_roi);
}

void DealImageParameter::on_pbtn_add_roi_clicked()
{
    ui->widget_operation_image->addRoi();
}

void DealImageParameter::on_pbtn_read_image_clicked()
{
    QString filename;
    filename=QFileDialog::getOpenFileName(this, tr("选择图像"), "", tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
    if(filename.isEmpty())
    {
        return;
    }
    else
    {
        QImageReader qir_(filename);
        DealWithImage::getStatic()->_qimage=qir_.read();
        if(DealWithImage::getStatic()->_qimage.width()>0
            &&DealWithImage::getStatic()->_qimage.height()>0)
        {
            DealWithImage::getStatic()->ClearSegmentationResult();
            ui->widget_operation_image->fitWindow();
            ui->widget_operation_image->refleshShow();
            QMessageBox::information(this, tr("提示"), tr("打开图像成功!"));
        }
        else
        {
            QMessageBox::information(this, tr("打开图像失败"), tr("打开图像失败!"));
        }
    }
}

void DealImageParameter::on_pbtn_fit_image_clicked()
{
    ui->widget_operation_image->fitWindow();
}


/*******************************参数设置函数*******************************************/

void DealImageParameter::on_dsb_area_min_valueChanged(double arg1)
{
    double min_=(double)arg1;
    double max_=(double)ui->dsb_area_max->value();

    if(min_>=max_)
    {
        min_=max_-1;
        ui->dsb_area_min->setValue(min_);
    }

    DealWithImage::getStatic()->_min_area=min_;
}

void DealImageParameter::on_dsb_area_max_valueChanged(double arg1)
{
    double min_=(double)ui->dsb_area_min->value();
    double max_=(double)arg1;

    if(max_<=min_)
    {
        max_=min_+1;
        ui->dsb_area_max->setValue(max_);
    }

    DealWithImage::getStatic()->_max_area=max_;

}

void DealImageParameter::on_dsb_width_min_valueChanged(double arg1)
{
    double min_=(double)arg1;

    double max_=(double)ui->dsb_width_max->value();

    if(min_>=max_)
    {
        min_=max_-1;
        ui->dsb_width_min->setValue(min_);
    }

    DealWithImage::getStatic()->_min_width=min_;

}

void DealImageParameter::on_dsb_width_max_valueChanged(double arg1)
{
    double min_=(double)ui->dsb_width_min->value();

    double max_=(double)arg1;

    if(max_<=min_)
    {
        max_=min_+1;
        ui->dsb_width_max->setValue(max_);
    }

    DealWithImage::getStatic()->_max_width=max_;

}

void DealImageParameter::on_dsb_height_min_valueChanged(double arg1)
{
    double min_=(double)arg1;
    double max_=(double)ui->dsb_height_max->value();

    if(min_>=max_)
    {
        min_=max_-1;
        ui->dsb_height_min->setValue(min_);
    }

    DealWithImage::getStatic()->_min_heigth=min_;

}

void DealImageParameter::on_dsb_height_max_valueChanged(double arg1)
{
    double min_=(double)ui->dsb_height_min->value();
    double max_=(double)arg1;

    if(max_<=min_)
    {
        max_=min_+1;
        ui->dsb_height_max->setValue(min_+1);
    }

    DealWithImage::getStatic()->_max_height=max_;

}

void DealImageParameter::on_dsb_roundness_min_valueChanged(double arg1)
{
    double min_=arg1;
    double max_=ui->dsb_roundness_max->value();

    if(min_>=max_)
    {
        min_=max_-0.1;
        ui->dsb_roundness_min->setValue(min_);
    }

    DealWithImage::getStatic()->_min_roundness=min_;

}


void DealImageParameter::on_dsb_roundness_max_valueChanged(double arg1)
{
    double min_=ui->dsb_roundness_min->value();
    double max_=arg1;

    if(max_<=min_)
    {
        max_=min_+0.1;
        ui->dsb_roundness_max->setValue(max_);
    }

    DealWithImage::getStatic()->_max_roundness=max_;

}


void DealImageParameter::on_dsb_convexity_min_valueChanged(double arg1)
{
    double min_=arg1;
    double max_=ui->dsb_convexity_max->value();

    if(min_>=max_)
    {
        min_=max_-0.1;
        ui->dsb_convexity_min->setValue(min_);
    }
    DealWithImage::getStatic()->_min_convexity=min_;
}

void DealImageParameter::on_dsb_convexity_max_valueChanged(double arg1)
{
    double min_=ui->dsb_convexity_min->value();
    double max_=arg1;

    if(max_<=min_)
    {
        max_=min_+0.1;
        ui->dsb_convexity_max->setValue(max_);
    }
    DealWithImage::getStatic()->_max_convexity=max_;
}


void DealImageParameter::on_spinbox_mean_one_image_value_valueChanged(int arg1)
{
    DealWithImage::getStatic()->_image_mean_number_dyn_one=arg1;
}

void DealImageParameter::on_spinbox_mean_two_image_value_valueChanged(int arg1)
{
    DealWithImage::getStatic()->_image_mean_number_dyn_two=arg1;
}


void DealImageParameter::on_spinbox_dyn_number_valueChanged(int arg1)
{
    DealWithImage::getStatic()->_dyn_threshold_=arg1;
}

void DealImageParameter::on_spinbox_segmentation_stuff_min_distance_valueChanged(int arg1)
{
    DealWithImage::getStatic()->_segmentation_stuff_closing_memenlt=arg1;
}

//void DealImageParameter::writer_cell_result_to_tablewidget()
//{
//    ui->table_widget_cell_result->clearContents();
//    int rowcount_=0;

//    for(int i=0;i<DealWithImage::getStatic()->_cell_rois.size();i++)
//    {
//        rowcount_+=DealWithImage::getStatic()->_cell_rois[i]._cell_results.size();
//    }

//    ui->table_widget_cell_result->setRowCount(rowcount_);

//    int row_number_=0;
//    for(int i=0;i<DealWithImage::getStatic()->_cell_rois.size();i++)
//    {
//        for(int j=0;j<DealWithImage::getStatic()->_cell_rois[i]._cell_results.size();j++)
//        {
//          QTableWidgetItem* id_=new QTableWidgetItem();
//          id_->setTextAlignment(Qt::AlignCenter);
//          id_->setText(QString::number(DealWithImage::getStatic()->_cell_rois[i]._id));
//          ui->table_widget_cell_result->setItem(row_number_,0,id_);

//          QTableWidgetItem* number_=new QTableWidgetItem();
//          number_->setTextAlignment(Qt::AlignCenter);
//          number_->setText(QString::number(DealWithImage::getStatic()->_cell_rois[i]._cell_results[j]._number));
//          ui->table_widget_cell_result->setItem(row_number_,1,number_);

//          QTableWidgetItem* x_=new QTableWidgetItem();
//          x_->setTextAlignment(Qt::AlignCenter);
//          x_->setText(QString::number(DealWithImage::getStatic()->_cell_rois[i]._cell_results[j]._x));
//          ui->table_widget_cell_result->setItem(i,2,x_);

//          QTableWidgetItem* y_=new QTableWidgetItem();
//          y_->setTextAlignment(Qt::AlignCenter);
//          y_->setText(QString::number(DealWithImage::getStatic()->_cell_rois[i]._cell_results[j]._y));
//          ui->table_widget_cell_result->setItem(row_number_,3,y_);

//          QTableWidgetItem* area_=new QTableWidgetItem();
//          area_->setTextAlignment(Qt::AlignCenter);
//          area_->setText(QString::number(DealWithImage::getStatic()->_cell_rois[i]._cell_results[j]._area));
//          ui->table_widget_cell_result->setItem(row_number_,4,area_);

//          QTableWidgetItem* angle_=new QTableWidgetItem();
//          angle_->setTextAlignment(Qt::AlignCenter);
//          angle_->setText(QString::number(DealWithImage::getStatic()->_cell_rois[i]._cell_results[j]._angle));
//          ui->table_widget_cell_result->setItem(row_number_,5,angle_);

//          QTableWidgetItem* width_=new QTableWidgetItem();
//          width_->setTextAlignment(Qt::AlignCenter);
//          width_->setText(QString::number(DealWithImage::getStatic()->_cell_rois[i]._cell_results[j]._width));
//          ui->table_widget_cell_result->setItem(row_number_,6,width_);

//          QTableWidgetItem* height_=new QTableWidgetItem();
//          height_->setTextAlignment(Qt::AlignCenter);
//          height_->setText(QString::number(DealWithImage::getStatic()->_cell_rois[i]._cell_results[j]._height));
//          ui->table_widget_cell_result->setItem(row_number_,7,height_);

//          QTableWidgetItem* mean_=new QTableWidgetItem();
//          mean_->setTextAlignment(Qt::AlignCenter);
//          mean_->setText(QString::number(DealWithImage::getStatic()->_cell_rois[i]._cell_results[j]._mean));
//          ui->table_widget_cell_result->setItem(row_number_,8,mean_);

//          QTableWidgetItem* circular_=new QTableWidgetItem();
//          circular_->setTextAlignment(Qt::AlignCenter);
//          circular_->setText(QString::number(DealWithImage::getStatic()->_cell_rois[i]._cell_results[j]._round));
//          ui->table_widget_cell_result->setItem(row_number_,9,circular_);

//          QTableWidgetItem* convexity_=new QTableWidgetItem();
//          convexity_->setTextAlignment(Qt::AlignCenter);
//          convexity_->setText(QString::number(DealWithImage::getStatic()->_cell_rois[i]._cell_results[j]._convexity));
//          ui->table_widget_cell_result->setItem(row_number_,10,convexity_);
//          row_number_++;
//        }
//    }
//}

void DealImageParameter::on_combobox_dyn_orientation_currentTextChanged1(const QString &arg1)
{
    if(arg1=="Light")
    {
        DealWithImage::getStatic()->_dyn_threshold_type=0;
    }

    if(arg1=="Dark")
    {
        DealWithImage::getStatic()->_dyn_threshold_type=1;
    }
}

void DealImageParameter::on_combobox_check_channle_type_currentTextChanged1(const QString &arg1)
{

    if(arg1=="Gray")
    {
        DealWithImage::getStatic()->_use_image_channle=0;
    }

    if(arg1=="R")
    {
        DealWithImage::getStatic()->_use_image_channle=1;
    }

    if(arg1=="G")
    {
        DealWithImage::getStatic()->_use_image_channle=2;
    }

    if(arg1=="B")
    {
        DealWithImage::getStatic()->_use_image_channle=3;
    }

    if(arg1=="H")
    {
        DealWithImage::getStatic()->_use_image_channle=4;
    }

    if(arg1=="S")
    {
        DealWithImage::getStatic()->_use_image_channle=5;
    }

    if(arg1=="V")
    {
        DealWithImage::getStatic()->_use_image_channle=6;
    }
}

/********************************************显示函数****************************************/
void DealImageParameter::on_checkBox_show_result_image_clicked(bool checked)
{
    DealWithImage::getStatic()->_show_result_image=checked;
}

void DealImageParameter::on_checkBox_show_use_image_clicked(bool checked)
{
    DealWithImage::getStatic()->_show_use_image=checked;
}

void DealImageParameter::on_checkBox_show_mean_image_one_clicked(bool checked)
{
    DealWithImage::getStatic()->_show_mean_image_one=checked;
}

void DealImageParameter::on_checkBox_show_mean_image_two_clicked(bool checked)
{
    DealWithImage::getStatic()->_show_mean_image_two=checked;
}

void DealImageParameter::on_checkBox_show_image_area_clicked(bool checked)
{
    DealWithImage::getStatic()->_show_segmentation_result_area=checked;
}

void DealImageParameter::on_checkBox_show_image_width_clicked(bool checked)
{
    DealWithImage::getStatic()->_show_segmentation_result_width=checked;
}

void DealImageParameter::on_checkBox_show_image_height_clicked(bool checked)
{
    DealWithImage::getStatic()->_show_segmentation_result_height=checked;
}

void DealImageParameter::on_checkBox_show_image_roundness_clicked(bool checked)
{
    DealWithImage::getStatic()->_show_segmentation_result_roundness=checked;
}

void DealImageParameter::on_checkBox_show_image_convexity_clicked(bool checked)
{
    DealWithImage::getStatic()->_show_segmentation_result_convexity=checked;
}

void DealImageParameter::on_checkBox_show_image_mean_clicked(bool checked)
{
    DealWithImage::getStatic()->_show_segmentation_result_mean=checked;
}

/********************************************其他按钮***********************************************/
void DealImageParameter::on_pbtn_deal_with_clicked()
{
    DealWithImage::getStatic()->SegmentationStuff();
    ui->widget_operation_image->refleshShow();
    //writer_cell_result_to_tablewidget();
    QMessageBox::information(this, tr("提示"), tr("图片处理完成!"));
}

void DealImageParameter::on_pbtn_clear_result_clicked()
{
    DealWithImage::getStatic()->ClearSegmentationResult();
    ui->widget_operation_image->refleshShow();
}

void DealImageParameter::on_pbtn_save_parameter_clicked()
{
    DealWithImage::getStatic()->WriteConfig();
    QMessageBox::information(this, tr("提示"), tr("保存数据成功"));
}

void DealImageParameter::on_pbtn_close_clicked()
{
    this->close();
}

/********************************************过滤使用*******************************************************/
void DealImageParameter::on_checkbox_use_area_filtration_clicked(bool checked)
{
    if(checked)
    {
        DealWithImage::getStatic()->_use_area_filtration=1;
    }
    else
    {
        DealWithImage::getStatic()->_use_area_filtration=0;
    }
}

void DealImageParameter::on_checkbox_use_width_filtration_clicked(bool checked)
{
    if(checked)
    {
        DealWithImage::getStatic()->_use_width_filtration=1;
    }
    else
    {
        DealWithImage::getStatic()->_use_width_filtration=0;
    }
}

void DealImageParameter::on_checkbox_use_height_filtration_clicked(bool checked)
{
    if(checked)
    {
        DealWithImage::getStatic()->_use_height_filtration=1;
    }
    else
    {
        DealWithImage::getStatic()->_use_height_filtration=0;
    }
}

void DealImageParameter::on_checkbox_use_roundness_filtration_clicked(bool checked)
{
    if(checked)
    {
        DealWithImage::getStatic()->_use_roundness_filtration=1;
    }
    else
    {
        DealWithImage::getStatic()->_use_roundness_filtration=0;
    }
}

void DealImageParameter::on_checkbox_use_convexity_filtration_clicked(bool checked)
{
    if(checked)
    {
        DealWithImage::getStatic()->_use_convexity_filtration=1;
    }
    else
    {
        DealWithImage::getStatic()->_use_convexity_filtration=0;
    }
}

