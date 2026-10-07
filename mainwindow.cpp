#include "mainwindow.h"
#include <QIcon>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    /*Create Menubar*/
    QMenu *fileMenu = menuBar()->addMenu("File");

    QAction* newFile = new QAction("New",this);
    newFile->setIcon(QIcon(":/new.svg"));
    newFile->setToolTip("New");
    newFile->setShortcut(QKeySequence("Ctrl+N"));

    QAction* open = new QAction("Open",this);
    open->setIcon(QIcon(":/open.svg"));
    open->setToolTip("Open");
    open->setShortcut(QKeySequence("Ctrl+O"));

    QAction* save = new QAction("Save",this);
    save->setIcon(QIcon(":/save-solid.svg"));
    save->setToolTip("Save");
    save->setShortcut(QKeySequence("Ctrl+S"));

    QAction *saveAs = new QAction("Save As",this);
    saveAs->setIcon(QIcon(":/save-as.svg"));
    saveAs->setToolTip("Save As");
    saveAs->setShortcut(QKeySequence("Ctrl+Shift+S"));


    fileMenu->addAction(newFile);
    fileMenu->addAction(open); //filemenu add action open and save
    fileMenu->addAction(save);
    fileMenu->addAction(saveAs);

    /*Create widgets*/
    QWidget * mainWidget = new QWidget();
    /*Allcate memory for vertical and horizontal*/
    QVBoxLayout* vlayout = new QVBoxLayout();
    QHBoxLayout* hlayout = new QHBoxLayout();

    //allocate memory ok and cancel
    QPushButton* okButton = new QPushButton("Ok",this);
    QPushButton* cancelButton = new QPushButton("Cancel",this);

    textEditor = new QTextEdit(this);
    defaultFontSize = textEditor->font().pointSize();

    vlayout->addWidget(textEditor);

    hlayout->addWidget(okButton);
    hlayout->addWidget(cancelButton);

    vlayout->addLayout(hlayout);

    mainWidget->setLayout(vlayout);
    setCentralWidget(mainWidget);



    connect(okButton,&QPushButton::clicked,this,&MainWindow::saveFile);
    connect(cancelButton,&QPushButton::clicked,this,&MainWindow::close);

    connect(newFile,&QAction::triggered,this,&MainWindow::newFile);
    connect(open,&QAction::triggered,this,&MainWindow::openFile);
    connect(save,&QAction::triggered,this,&MainWindow::saveFile);
    connect(saveAs,&QAction::triggered,this,&MainWindow::saveasFile);





    QMenu *editMenu = menuBar()->addMenu("Edit");

    QAction *undo = new QAction("Undo",this);
    undo->setIcon(QIcon(":/undo.svg"));
    undo->setToolTip("Undo");
    undo->setShortcut(QKeySequence("Ctrl+Z"));

    QAction *redo = new QAction("Redo",this);
    redo->setIcon(QIcon(":/redo.svg"));
    redo->setToolTip("Redo");
    redo->setShortcut(QKeySequence("Ctrl+Y"));

    editMenu->addAction(undo);
    editMenu->addAction(redo);

    connect(undo,&QAction::triggered,textEditor,&QTextEdit::undo);
    connect(redo,&QAction::triggered,textEditor,&QTextEdit::redo);

    QAction *cut = new QAction("Cut",this);
    cut->setIcon(QIcon(":/cut.svg"));
    cut->setToolTip("Cut");
    cut->setShortcut(QKeySequence("Ctrl+X"));

    QAction *copy = new QAction("Copy",this);
    copy->setIcon(QIcon(":/copy.svg"));
    copy->setToolTip("Copy");
    copy->setShortcut(QKeySequence("Ctrl+C"));

    QAction *paste = new QAction("Paste",this);
    paste->setIcon(QIcon(":/paste.svg"));
    paste->setToolTip("Paste");
    paste->setShortcut(QKeySequence("Ctrl+V"));

    editMenu->addAction(cut);
    editMenu->addAction(copy);
    editMenu->addAction(paste);

    connect(cut,&QAction::triggered,textEditor,&QTextEdit::cut);
    connect(copy,&QAction::triggered,textEditor,&QTextEdit::copy);
    connect(paste,&QAction::triggered,textEditor,&QTextEdit::paste);

    QAction *selectall = new QAction("Select All",this);
    selectall->setIcon(QIcon(":/copy.svg"));
    selectall->setShortcut(QKeySequence("Ctrl+A"));
    editMenu->addAction(selectall);
    connect(selectall,&QAction::triggered,textEditor,&QTextEdit::selectAll);

    QAction *find = new QAction("Find",this);
    find->setIcon(QIcon(":/find.svg"));
    find->setToolTip("Find Text");
    editMenu->addAction(find);
    connect(find,&QAction::triggered,this,&MainWindow::findText);


    QMenu *FormatMenu = menuBar()->addMenu("Format");

    QAction *font = new QAction("Font",this);
    font->setIcon(QIcon(":/font.svg"));
    font->setToolTip("Change Font");
    FormatMenu->addAction(font);
    connect(font,&QAction::triggered,this,&MainWindow::changeFont);

    QAction *zoomIn =new QAction("Zoom In",this);
    zoomIn->setIcon(QIcon(":/zoom-in.svg"));
    zoomIn->setToolTip("Increase Font Size");
    zoomIn->setShortcut(QKeySequence("Ctrl++"));
    FormatMenu->addAction(zoomIn);
    connect(zoomIn,&QAction::triggered,this,&MainWindow::zoomIn);


    QAction *zoomOut =new QAction("Zoom Out",this);
    zoomOut->setIcon(QIcon(":/zoom-out.svg"));
    zoomOut->setToolTip("Decrease Font Size");
    zoomOut->setShortcut(QKeySequence("Ctrl+-"));
    FormatMenu->addAction(zoomOut);
    connect(zoomOut,&QAction::triggered,this,&MainWindow::zoomOut);


    QAction *color = new QAction("Text Color",this);
    color->setIcon(QIcon(":/text-color.svg"));
    color->setToolTip("Change Text Color");
    FormatMenu->addAction(color);
    connect(color,&QAction::triggered,this,&MainWindow::changeColor);



    QAction *highlight = new QAction("Highlight",this);
    highlight->setIcon(QIcon(":/highlight.svg"));
     highlight->setToolTip("Highlight Text");
    FormatMenu->addAction(highlight);
    connect(highlight,&QAction::triggered,this,&MainWindow::highlightColor);

    QMenu *viewMenu = menuBar()->addMenu("View");

    QAction *resetZoom = new QAction("Reset Zoom",this);
    resetZoom->setIcon(QIcon(":/reset-zoom.svg"));
    resetZoom->setToolTip("Reset Zoom");
    viewMenu->addAction(resetZoom);
    connect(resetZoom,&QAction::triggered,this,&MainWindow::resetZoom);

    QMenu *helpMenu = menuBar()->addMenu("Help");

    QAction *about = new QAction("About", this);
    about->setIcon(QIcon(":/about.svg"));
    about->setToolTip("About Plain Text Editor");
    helpMenu->addAction(about);
    connect(about, &QAction::triggered, this, &MainWindow::about);

}

MainWindow::~MainWindow() = default;

void MainWindow::newFile()
{
    textEditor->clear();
    currentFilename.clear();

    statusBar()->showMessage("New File",2000);

}

void MainWindow::openFile()
{
   // qDebug() <<"Open Method called";

  QString fileName = QFileDialog::getOpenFileName(this,
                                                   tr("Open Image"), " ", tr("Text Files (*.txt)"));

   if(!fileName.isEmpty())
  {
      QFile file(fileName);
       if(file.open(QIODevice::ReadOnly | QIODevice::Text))
       {
          QTextStream in(&file);
           textEditor->setPlainText(in.readAll());

          currentFilename = fileName;
          file.close();
       }
       else
       {
           QMessageBox::warning(this,"Error","Could not open file");
       }
   }

}

void MainWindow::saveFile()
{
  //qDebug() <<"Save Method called";

  if(currentFilename.isEmpty())
    {
      QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                      " ",
                                                      tr("Text Files (*.txt)"));

      if(!fileName.isEmpty())
      {
          QFile file(fileName);
          if(file.open(QIODevice::WriteOnly | QIODevice::Text))
          {
              QTextStream out(&file);
              out<< textEditor->toPlainText();
              //textEditor->clear();
              file.close();
              statusBar()->showMessage("File Saved Successfully",4000);
          }
          else
          {
               QMessageBox::warning(this,"Error","Could not save file");
          }
      }

   }

}

void MainWindow::saveasFile()
{
    if(currentFilename.isEmpty())
    {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                                                        " ",
                                                        tr("Text Files (*.txt)"));

        if(!fileName.isEmpty())
        {
            QFile file(fileName);
            if(file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QTextStream out(&file);
                out<< textEditor->toPlainText();
                //textEditor->clear();
                file.close();
                currentFilename = fileName;
                statusBar()->showMessage("File Saved Successfully",4000);
            }
            else
            {
                QMessageBox::warning(this,"Error","Could not save file");
            }
        }

    }
}

void MainWindow::changeFont()
{
    bool ok;
    QFont selectedFont = QFontDialog::getFont(&ok,textEditor->font(), this);
    if (ok)
    {
        textEditor->setFont(selectedFont);
    }
}

void MainWindow::zoomIn()
{
    textEditor->zoomIn();
}

void MainWindow::zoomOut()
{
    textEditor->zoomOut();
}

void MainWindow::resetZoom()
{
    QFont font = textEditor->font();
    font.setPointSize(defaultFontSize);
    textEditor->setFont(font);
}

void MainWindow::changeColor()
{
    QColor color = QColorDialog::getColor(Qt::black,this);

    if(color.isValid())
    {
        textEditor->setTextColor(color);
    }
}

void MainWindow::highlightColor()
{
    QColor color = QColorDialog::getColor(Qt::yellow,this);

    if(color.isValid())
    {
        textEditor->setTextBackgroundColor(color);
    }
}

void MainWindow::findText()
{
        bool ok;
        QString text = QInputDialog::getText(this, "Find", "Enter text:",
                                             QLineEdit::Normal, "", &ok);

        if (ok && !text.isEmpty())
        {
            QTextCursor cursor = textEditor->textCursor();
            cursor.setPosition(0);
            textEditor->setTextCursor(cursor);

            if (!textEditor->find(text))
            {
                QMessageBox::information(this, "Find", "Text not found.");
            }
        }
}

void MainWindow::about()
{
    QMessageBox::about(this,"About Plain Text Editor", "Plain Text Editor\n\n""A simple text editor created using Qt and C++.");
}
