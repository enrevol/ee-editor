#ifndef EE_EDITOR_CLICKABLE_WIDGET_HPP
#define EE_EDITOR_CLICKABLE_WIDGET_HPP

#include <QWidget>

namespace ee {
class ClickableWidget : public QWidget {
    Q_OBJECT

private:
    using Self = ClickableWidget;
    using Super = QWidget;

public:
    explicit ClickableWidget(QWidget* parent = nullptr);

    virtual ~ClickableWidget() override;

Q_SIGNALS:
    void clicked();

protected:
    virtual void mousePressEvent(QMouseEvent* event) override;

private:
};
} // namespace ee

#endif // EE_EDITOR_CLICKABLE_WIDGET_HPP
