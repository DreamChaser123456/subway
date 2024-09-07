#include "map_design.h"
#include "ui_map_design.h"

map_design::map_design(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::map_design)
{
    ui->setupUi(this);
}

map_design::~map_design()
{
    delete ui;
}
