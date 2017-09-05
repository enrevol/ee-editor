#include "inspectortexture.hpp"
#include "ui_inspectortexture.h"

namespace ee {
InspectorTexture::InspectorTexture(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::InspectorTexture) {
    ui->setupUi(this);
}

InspectorTexture::~InspectorTexture() {
    delete ui;
}
} // namespace ee
