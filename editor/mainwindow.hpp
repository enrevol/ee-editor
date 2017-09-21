#ifndef EE_EDITOR_MAIN_WINDOW_HPP
#define EE_EDITOR_MAIN_WINDOW_HPP

#include <QMainWindow>

namespace Ui {
class MainWindow;
} // namespace Ui

namespace ee {
class OpenGLWidget;

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    using Self = MainWindow;
    using Super = QMainWindow;

public:
    explicit MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow() override;

    OpenGLWidget* getOpenGLView();

protected Q_SLOTS:
    void onProjectSettingsButtonPressed();

private:
    Ui::MainWindow* ui_;
};
} // namespace ee

#endif // EE_EDITOR_MAIN_WINDOW_HPP
