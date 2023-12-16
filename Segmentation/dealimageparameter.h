#ifndef DEALIMAGEPARAMETER_H
#define DEALIMAGEPARAMETER_H

#include <QDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QImageReader>

namespace Ui {
class DealImageParameter;
}

class DealImageParameter : public QDialog
{
    Q_OBJECT

public:
    explicit DealImageParameter(QWidget *parent = nullptr);
    ~DealImageParameter();

private slots:
    void on_rbtn_move_board_clicked();
    void on_rbtn_move_roi_clicked();
    void on_rbtn_delete_roi_clicked();
    void on_pbtn_add_roi_clicked();
    void on_pbtn_read_image_clicked();
    void on_pbtn_fit_image_clicked();

    void on_dsb_width_min_valueChanged(double arg1);
    void on_dsb_width_max_valueChanged(double arg1);

    void on_dsb_height_min_valueChanged(double arg1);
    void on_dsb_height_max_valueChanged(double arg1);

    void on_dsb_area_min_valueChanged(double arg1);
    void on_dsb_area_max_valueChanged(double arg1);

    void on_dsb_roundness_min_valueChanged(double arg1);
    void on_dsb_roundness_max_valueChanged(double arg1);

    void on_dsb_convexity_min_valueChanged(double arg1);
    void on_dsb_convexity_max_valueChanged(double arg1);

    void on_spinbox_mean_one_image_value_valueChanged(int arg1);
    void on_spinbox_mean_two_image_value_valueChanged(int arg1);
    void on_spinbox_dyn_number_valueChanged(int arg1);
    void on_spinbox_segmentation_stuff_min_distance_valueChanged(int arg1);

    void on_combobox_dyn_orientation_currentTextChanged1(const QString &arg1);
    void on_combobox_check_channle_type_currentTextChanged1(const QString &arg1);

    void on_pbtn_deal_with_clicked();
    void on_pbtn_clear_result_clicked();

    void on_checkBox_show_result_image_clicked(bool checked);
    void on_checkBox_show_use_image_clicked(bool checked);
    void on_checkBox_show_mean_image_one_clicked(bool checked);
    void on_checkBox_show_mean_image_two_clicked(bool checked);
    void on_checkBox_show_image_area_clicked(bool checked);
    void on_checkBox_show_image_width_clicked(bool checked);
    void on_checkBox_show_image_height_clicked(bool checked);
    void on_checkBox_show_image_roundness_clicked(bool checked);
    void on_checkBox_show_image_convexity_clicked(bool checked);
    void on_checkBox_show_image_mean_clicked(bool checked);

    void on_pbtn_save_parameter_clicked();
    void on_pbtn_close_clicked();


    void on_checkbox_use_area_filtration_clicked(bool checked);

    void on_checkbox_use_width_filtration_clicked(bool checked);

    void on_checkbox_use_height_filtration_clicked(bool checked);

    void on_checkbox_use_roundness_filtration_clicked(bool checked);

    void on_checkbox_use_convexity_filtration_clicked(bool checked);

private:
//    /***把细胞数据写到报表里面***/
//    void writer_cell_result_to_tablewidget();
    Ui::DealImageParameter *ui;
};

#endif // DEALIMAGEPARAMETER_H
