#include "text.h"
#include "ui_text.h"

text::text(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::text)
{
    ui->setupUi(this);
    setWindowTitle("游戏须知");
}

text::~text()
{
    delete ui;
}

void text::on_pushButton_clicked()
{
    this->close();
}
