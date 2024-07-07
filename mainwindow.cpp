#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include "TriviaAPI.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pvp_btn_clicked()
{
    int currentIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(currentIndex + 1);
}


void MainWindow::on_pvp_submit_btn_clicked()
{
    Player player1(ui->player1_name->text());
    Player player2(ui->player2_name->text());
    this->pvpgame.set_players(player1, player2);
    ui->pvp_turn_showcase->setText(pvpgame.get_currentPlayer()->get_name());
    int currentIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(currentIndex + 1);
}


void MainWindow::on_pvp_start_btn_clicked()
{
    int currentIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(currentIndex + 1);
    TriviaAPI api;
    Category category = api.category_identifier(ui->pvp_category_selection->currentText());
    QString difficulty;
    if (ui->pvp_easy_btn->isChecked()){
        difficulty = "easy";
    } else if (ui->pvp_medium_btn->isChecked()){
        difficulty = "medium";
    } else if (ui->pvp_hard_btn->isChecked()){
        difficulty = "hard";
    }
    api.get_questions(category, difficulty);
}
