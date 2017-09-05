#include "inspectorfloat.hpp"
#include "ui_inspectorfloat.h"

InspectorFloat::InspectorFloat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InspectorFloat)
{
    ui->setupUi(this);
}

InspectorFloat::~InspectorFloat()
{
    delete ui;
}
