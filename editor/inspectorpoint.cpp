#include "inspectorpoint.hpp"
#include "ui_inspectorpoint.h"

InspectorPoint::InspectorPoint(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InspectorPoint)
{
    ui->setupUi(this);
}

InspectorPoint::~InspectorPoint()
{
    delete ui;
}
