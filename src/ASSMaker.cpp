#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QMainWindow mainWindow;
    mainWindow.show();
    return QApplication::exec();
}
