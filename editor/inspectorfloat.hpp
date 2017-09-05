#ifndef INSPECTORFLOAT_HPP
#define INSPECTORFLOAT_HPP

#include <QWidget>

namespace Ui {
class InspectorFloat;
}

class InspectorFloat : public QWidget
{
    Q_OBJECT

public:
    explicit InspectorFloat(QWidget *parent = 0);
    ~InspectorFloat();

private:
    Ui::InspectorFloat *ui;
};

#endif // INSPECTORFLOAT_HPP
