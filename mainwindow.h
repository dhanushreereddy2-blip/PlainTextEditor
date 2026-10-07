#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QPushButton>  //pushbutton
#include <QVBoxLayout> //horizontal
#include <QHBoxLayout> //vertical
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox> //print file save successfully
#include <QDebug>
#include <QFontDialog>
#include <QColorDialog>
#include <QInputDialog>
#include <QLineEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;


    public slots:
        void newFile();
        void openFile();
        void saveFile();
        void saveasFile();
        void changeFont();
        void zoomIn();
        void zoomOut();
        void resetZoom();
        void changeColor();
        void highlightColor();
        void findText();
        void about();

private:
    QTextEdit *textEditor;
    QString currentFilename;
    int defaultFontSize;
};
#endif // MAINWINDOW_H
