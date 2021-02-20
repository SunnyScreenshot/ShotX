#include "about.h"
#include "ui_about.h"

#include <QIcon>

About::About(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/icons/logo.svg"));
    setWindowTitle("ShotX");
}

About::~About()
{
    delete ui;
}
