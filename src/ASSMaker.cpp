#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

using namespace std;

void addLineEditLayout(QVBoxLayout* vBoxLayout, const QString& labelText, const QString& defaultText = "", bool enabled = true) {
    auto layout = new QHBoxLayout();
    vBoxLayout->addLayout(layout);

    layout->addWidget(new QLabel(labelText, vBoxLayout->parentWidget()));

    auto lineEdit = new QLineEdit(defaultText, vBoxLayout->parentWidget());
    lineEdit->setEnabled(enabled);
    layout->addWidget(lineEdit);
}

void addComboBoxLayout(QVBoxLayout* vBoxLayout, const QString& labelText, const QStringList& items, int currentIndex = -1) {
    auto layout = new QHBoxLayout();
    vBoxLayout->addLayout(layout);

    layout->addWidget(new QLabel(labelText, vBoxLayout->parentWidget()));

    auto comboBox = new QComboBox(vBoxLayout->parentWidget());
    comboBox->addItems(items);
    comboBox->setCurrentIndex(currentIndex);
    layout->addWidget(comboBox);
}

void initCentralWidget(QMainWindow* mainWindow) {
    auto centralWidget = new QWidget(mainWindow);
    mainWindow->setCentralWidget(centralWidget);

    auto layout = new QVBoxLayout();
    centralWidget->setLayout(layout);

    addLineEditLayout(layout, "Title");
    addLineEditLayout(layout, "Original Script");
    addLineEditLayout(layout, "Update Details");
    addLineEditLayout(layout, "Script Type", "V4.00+", false);
    addComboBoxLayout(layout, "Collisions", {"Normal", "Reverse"}, 0);
    addComboBoxLayout(layout, "PalyRes", { "480P", "720P", "1080P/1080i", "2K", "4K" }, 2);
    addComboBoxLayout(layout, "PlayDepth", { "8", "16", "24", "32" }, 2);
    addLineEditLayout(layout, "Timer", "100.0000");
    addComboBoxLayout(layout, "WrapStyle", { "0", "1", "2", "3" }, 0);
}

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    QMainWindow mainWindow;
    initCentralWidget(&mainWindow);
    mainWindow.show();
    return QApplication::exec();
}
