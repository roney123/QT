#ifndef TEXT_H
#define TEXT_H

#include <QDialog>

namespace Ui {
class text;
}

class text : public QDialog
{
    Q_OBJECT

public:
    explicit text(QWidget *parent = 0);
    ~text();

private slots:
    void on_pushButton_clicked();

private:
    Ui::text *ui;
};

#endif // TEXT_H
