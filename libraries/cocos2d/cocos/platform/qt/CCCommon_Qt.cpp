#include "platform/CCCommon.h"

#include <QMessageBox>

NS_CC_BEGIN
void LuaLog(const char* format) {
    CC_UNUSED_PARAM(format);
}

void MessageBox(const char* msg, const char* title) {
    QMessageBox::warning(nullptr, title, msg, QMessageBox::Ok,
                         QMessageBox::NoButton);
}
NS_CC_END
