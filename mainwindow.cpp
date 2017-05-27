#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cinstance.h"
#include "cinput.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

QString fileName;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    fileName = "";
    ui->textEdit->clear();
}

void MainWindow::on_actionOpen_triggered()
{
    QString fno(QFileDialog::getOpenFileName(this, tr("Open File"), "/input.txt", tr("Text files (*.txt)")));
    if(!fno.isEmpty())
    {
        fileName = fno;
        QFile file(fileName);
        file.open(QFile::ReadOnly);
        QTextStream in(&file);
        ui->textEdit->setText(in.readAll());
        file.close();
    }
}

void MainWindow::on_actionSave_triggered()
{
    if(fileName.isEmpty())
    {
        on_actionSave_As_triggered();
    }
    else
    {
        QFile file(fileName);
        file.open(QFile::WriteOnly);
        QTextStream out(&file);
        out<<ui->textEdit->toPlainText();
        file.close();
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    QString fn = QFileDialog::getSaveFileName(this, tr("Save File"), "/input.txt", tr("Text files (*.txt)"));
    if (!fn.isEmpty())
    {
        if(!fn.endsWith(".txt", Qt::CaseInsensitive))
            fileName = fn + ".txt";
        else
            fileName = fn;
        on_actionSave_triggered();
    }
}


void MainWindow::on_actionRun_triggered()
{
    on_actionSave_triggered();
    CInput input(ui->textEdit->toPlainText());
    //Form an instance and calculate the displacement
    CInstance instance(input.inode().size()*2, input.ielement(), input.iload(), input.iconstraint());
    //Output the result
    QString text("Node Disp=\n");
    for (int i = 0; i != instance.u().rows()/2; ++i)
        text = text + QString::number(i + 1) + "," + QString::number(instance.u()(i*2, 0)) + "," + QString::number(instance.u()(i*2 + 1, 0)) + "\n";
    text = text + "-\n";
    ui->textEdit_2->setText(text);
}

void MainWindow::on_actionOutput_triggered()
{
    QString op = QFileDialog::getSaveFileName(this, tr("Output"), "/output.txt", tr("Text files (*.txt)"));
    if (!op.isEmpty())
    {
        if(!op.endsWith(".txt", Qt::CaseInsensitive))
            op = op + ".txt";
        QFile fileop(op);
        fileop.open(QFile::WriteOnly);
        QTextStream out(&fileop);
        out<<ui->textEdit_2->toPlainText();
        fileop.close();
    }
}

void MainWindow::on_actionHelp_triggered()
{
    QMessageBox::about(NULL,"Help",
                       "Input Form:\n"
                       "\n"
                       "Node=\n"
                       "No.,x,y\n"
                       "......\n"
                       "-\n"
                       "Material=\n"
                       "No.,Density,Elastic Modulus,Possion Ratio\n"
                       "......\n"
                       "-\n"
                       "Element=\n"
                       "No.,Node 1;Node 2;......;Node n,Element Type\n"
                       "......\n"
                       "-\n"
                       "Load=\n"
                       "No.,Node,Fx,Fy\n"
                       "......\n"
                       "-\n"
                       "Constraint=\n"
                       "No.,Node,Constraint x,Constraint y (*Fix:1 Free:0)\n"
                       "......\n"
                       "-");
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(NULL,"About",
                       "The program:\n"
                       "Writen by Yankun Qiu\n"
                       "Finished in Feb. 2 2016\n"
                       "\n"
                       "Contact information:\n"
                       "Jimkwan.Yau@Gmail.com");
}
