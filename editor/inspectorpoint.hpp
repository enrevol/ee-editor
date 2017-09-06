#ifndef INSPECTORPOINT_HPP
#define INSPECTORPOINT_HPP

#include <QWidget>

namespace Ui {
class InspectorPoint;
}

class InspectorPoint : public QWidget
{
    Q_OBJECT

public:
    explicit InspectorPoint(QWidget *parent = 0);
    ~InspectorPoint();

private:
    Ui::InspectorPoint *ui;
};

#endif // INSPECTORPOINT_HPP
