#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "PVPGame.h"
#include "SurvivalGame.h"

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

    void on_pvp_question_btn_clicked();

    void on_pvp_nextround_btn_clicked();

    void on_survival_btn_clicked();

    void on_survival_start_btn_clicked();

private:
    int clicked;
    PVPGame pvpgame;
    SurvivalGame survivalgame;
    Ui::MainWindow *ui;
    void set_options(const Question& question);
    void set_currentQuestion(const Question& question);
    bool get_answers(const Question& question);
    void options_visibility(bool visibility);
    void update_highscores();
};
#endif // MAINWINDOW_H
