#ifndef EE_EDITOR_MAIN_WINDOW_HPP
#define EE_EDITOR_MAIN_WINDOW_HPP

#include <QMainWindow>

class QFileInfo;

namespace Ui {
class MainWindow;
} // namespace Ui

namespace ee {
class OpenGLWidget;
class SceneManager;

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    using Self = MainWindow;
    using Super = QMainWindow;

public:
    explicit MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow() override;

    OpenGLWidget* getOpenGLView();

    void createProject();
    void openProject();
    void closeProject(const QFileInfo& path);
    void openProjectSettings();
    void createInterface();
    void loadInterface(const QFileInfo& path);
    void saveInterface();

private:
    Ui::MainWindow* ui_;
    std::unique_ptr<SceneManager> sceneManager_;
};
} // namespace ee

#endif // EE_EDITOR_MAIN_WINDOW_HPP
