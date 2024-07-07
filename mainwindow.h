#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "PVPGame.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pvp_btn_clicked();

    void on_pvp_submit_btn_clicked();

    void on_pvp_start_btn_clicked();

private:
    PVPGame pvpgame;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
