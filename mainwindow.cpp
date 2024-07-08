#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include "TriviaAPI.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->clicked = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_options(const Question& question) {
    QVector<QString> random_options = question.get_random_answers();
    ui->pvp_op1_btn->setText(random_options[0]);
    ui->pvp_op2_btn->setText(random_options[1]);
    ui->pvp_op3_btn->setText(random_options[2]);
    ui->pvp_op4_btn->setText(random_options[3]);
}

void MainWindow::set_currentQuestion(const Question& question) {
    ui->pvp_question_showcase->setText(question.get_question());
    ui->pvp_category_showcase->setText(question.get_category().get_name());
    ui->pvp_difficulty_showcase->setText(question.get_difficulty());
    set_options(question);
}

bool MainWindow::get_answers(const Question& question) {
    QString correct_answer = question.get_correct_answer();
    if (ui->pvp_op1_btn->isChecked()){
        if (ui->pvp_op1_btn->text() == correct_answer){
            return true;
        }
    }
    else if (ui->pvp_op2_btn->isChecked()) {
        if(ui->pvp_op2_btn->text() == correct_answer) {
            return true;
        }
    }
    else if (ui->pvp_op3_btn->isChecked()) {
        if (ui->pvp_op3_btn->text() == correct_answer) {
            return true;
        }
    }
    else if (ui->pvp_op4_btn->isChecked()) {
        if (ui->pvp_op4_btn->text() == correct_answer) {
            return true;
        }
    }
    else {
        return false;
    }
}

void MainWindow::options_visibility(bool visibility) {
    if (visibility) {
        ui->pvp_op1_btn->show();
        ui->pvp_op2_btn->show();
        ui->pvp_op3_btn->show();
        ui->pvp_op4_btn->show();
    }
    else {
        ui->pvp_op1_btn->hide();
        ui->pvp_op2_btn->hide();
        ui->pvp_op3_btn->hide();
        ui->pvp_op4_btn->hide();
    }
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
    Category category = pvpgame.api.category_identifier(ui->pvp_category_selection->currentText());
    QString difficulty;
    if (ui->pvp_easy_btn->isChecked()){
        difficulty = "easy";
    } else if (ui->pvp_medium_btn->isChecked()){
        difficulty = "medium";
    } else if (ui->pvp_hard_btn->isChecked()){
        difficulty = "hard";
    }
    pvpgame.api.get_questions(category, difficulty);

    pvpgame.load_questions();

    QString text = "It's " + pvpgame.get_currentPlayer()->get_name() + "'s Turn ...\nIf you are ready click the Start button!";
    ui->pvp_question_showcase->setText(text);
    ui->pvp_turn_showcase2->setText(pvpgame.get_currentPlayer()->get_name());
    ui->pvp_category_showcase->setText("");
    ui->pvp_difficulty_showcase->setText("");
    options_visibility(false);
}

void MainWindow::on_pvp_question_btn_clicked()
{
    clicked++;
    if (clicked == 1) {
        options_visibility(true);
        Question currentQuestion = pvpgame.get_currentQuestions()[clicked - 1];
        set_currentQuestion(currentQuestion);
        ui->pvp_question_btn->setText("Next");
    }
    else if (clicked == 6) {
        Question lastQuestion = pvpgame.get_currentQuestions()[clicked - 2];
        pvpgame.turn_score_calculator(get_answers(lastQuestion));
        clicked = 0;
        if (pvpgame.is_endRound()){
            Player winner = pvpgame.get_round_winner();
            ui->RoundWinner->setText(winner.get_name());
            ui->Player1_label->setText(pvpgame.get_player1().get_name());
            ui->Player2_label->setText(pvpgame.get_player2().get_name());
            ui->player1_score->setText(QString::number(pvpgame.get_player1().get_score()));
            ui->player2_score->setText(QString::number(pvpgame.get_player2().get_score()));
            int currentIndex = ui->stackedWidget->currentIndex();
            ui->stackedWidget->setCurrentIndex(currentIndex + 1);
            if (pvpgame.is_endGame()) {
                ui->winner_label->setText("Winner of the game: ");
                Player game_winner = pvpgame.get_game_winner();
                ui->RoundWinner->setText(game_winner.get_name());
                ui->pvp_nextround_btn->setText("Finish");
                QMessageBox::information(this, "Game is finished!", "Game is finished and we have a winner !!");
            }
        } else {
            QString text = "It's " + pvpgame.get_currentPlayer()->get_name() + "'s Turn ...\nIf you are ready click the Start button!";
            ui->pvp_question_showcase->setText(text);
            options_visibility(false);
            ui->pvp_turn_showcase2->setText(pvpgame.get_currentPlayer()->get_name());
            QMessageBox::information(this, "End Turn", "End of the turn ...\nNow it is " + pvpgame.get_currentPlayer()->get_name() + "'s turn!");
        }

    }
    else {
        Question currentQuestion = pvpgame.get_currentQuestions()[clicked - 1];
        Question lastQuestion = pvpgame.get_currentQuestions()[clicked - 2];
        pvpgame.turn_score_calculator(get_answers(lastQuestion));
        set_currentQuestion(currentQuestion);
    }
}


void MainWindow::on_pvp_nextround_btn_clicked()
{
    if (pvpgame.is_endGame()) {
        int currentIndex = ui->stackedWidget->currentIndex();
        ui->stackedWidget->setCurrentIndex(currentIndex - 4);
    }
    else if (pvpgame.is_goldenRound()) {
        pvpgame.api.get_questions();
        pvpgame.load_questions();
        QMessageBox::information(this, "Golden Round", "We have Golden Round now!\nDifficulty and Category of questions have been randomly selected!");
        QString text = "It's " + pvpgame.get_currentPlayer()->get_name() + "'s Turn ...\nIf you are ready click the Start button!";
        ui->pvp_question_showcase->setText(text);
        ui->pvp_turn_showcase2->setText(pvpgame.get_currentPlayer()->get_name());
        int currentIndex = ui->stackedWidget->currentIndex();
        ui->stackedWidget->setCurrentIndex(currentIndex - 1);
    }
    else {
        int currentIndex = ui->stackedWidget->currentIndex();
        ui->stackedWidget->setCurrentIndex(currentIndex - 2);
        ui->pvp_turn_showcase->setText(pvpgame.get_currentPlayer()->get_name());
    }
}

