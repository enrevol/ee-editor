#include "inspectorfloat.hpp"
#include "ui_inspectorfloat.h"

namespace ee {
InspectorFloat::InspectorFloat(QWidget* parent)
    : Super(parent)
    , ui(new Ui::InspectorFloat) {
    ui->setupUi(this);
}

InspectorFloat::~InspectorFloat() {
    delete ui;
}
} // namespace ee
