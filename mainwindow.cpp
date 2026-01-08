#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui -> lbContra->setEchoMode(QLineEdit::Password);
    connect(ui->btnIngresar, &QPushButton::clicked,
            this, &MainWindow::on_btnLogin_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnLogin_clicked()
{
    QString usuario = ui->lbUsuario->text();
    QString clave = ui->lbContra->text();

    if(usuario == "admin" && clave == "1234"){
        QMessageBox::information(this, "Login", "Acceso correcto");
    } else {
        QMessageBox::warning(this, "Error", "Usuario o clave incorrectos");
    }
}
