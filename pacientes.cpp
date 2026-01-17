#include "pacientes.h"
#include "./ui_pacientes.h"
#include "ui_pacientes.h"

#include <QPushButton>
#include <QMessageBox>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QDateEdit>
#include <QTimeEdit>
#include <QSpinBox>
#include <QTableWidgetItem>
#include <QLineEdit>

Pacientes::Pacientes(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Pacientes)
{
    ui->setupUi(this);

    ui->leContra->setEchoMode(QLineEdit::Password);

    connect(ui->btnIng, &QPushButton::clicked,
            this, &Pacientes::on_btnLogin_clicked);
}

Pacientes::~Pacientes()
{
    delete ui;
}

void Pacientes::on_btnLogin_clicked()
{
    QString usuario = ui->leUsuario->text();
    QString clave   = ui->leContra->text();

    if (usuario.isEmpty() || clave.isEmpty()) {
        QMessageBox::warning(this, "Campos vacíos",
                             "Complete usuario y contraseña");
        return;
    }

    if (usuario == "admin" && clave == "1234") {
        QMessageBox::information(this, "Login", "Acceso correcto");
        crearCrud();
    } else {
        QMessageBox::warning(this, "Error",
                             "Usuario o clave incorrectos");
    }
}

void Pacientes::crearCrud()
{
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QLabel *lblId = new QLabel("ID:");
    txtId = new QLineEdit;

    QLabel *lblCedula = new QLabel("Cédula:");
    txtCedula = new QLineEdit;

    QLabel *lblNombre = new QLabel("Nombre:");
    txtNombrePaciente = new QLineEdit;

    QLabel *lblEdad = new QLabel("Edad:");
    spinEdad = new QSpinBox;
    spinEdad->setRange(0, 120);

    QLabel *lblEspecialidad = new QLabel("Especialidad:");
    txtEspecialidad = new QLineEdit;

    QLabel *lblDoctor = new QLabel("Doctor:");
    txtDoctor = new QLineEdit;

    QLabel *lblFecha = new QLabel("Fecha:");
    dateFecha = new QDateEdit(QDate::currentDate());
    dateFecha->setCalendarPopup(true);

    QLabel *lblHora = new QLabel("Hora:");
    timeHora = new QTimeEdit(QTime::currentTime());

    QLabel *lblMotivo = new QLabel("Motivo:");
    txtMotivo = new QLineEdit;

    btnGuardar   = new QPushButton("Agregar");
    btnMostrar   = new QPushButton("Mostrar");
    btnActualizar= new QPushButton("Actualizar");
    btnEliminar  = new QPushButton("Eliminar");
    btnLimpiar   = new QPushButton("Limpiar");

    tabla = new QTableWidget;
    tabla->setColumnCount(9);
    tabla->setHorizontalHeaderLabels({
        "ID","Cédula","Nombre","Edad","Especialidad",
        "Doctor","Fecha","Hora","Motivo"
    });

    QVBoxLayout *formLayout = new QVBoxLayout;
    formLayout->addWidget(lblId); formLayout->addWidget(txtId);
    formLayout->addWidget(lblCedula); formLayout->addWidget(txtCedula);
    formLayout->addWidget(lblNombre); formLayout->addWidget(txtNombrePaciente);
    formLayout->addWidget(lblEdad); formLayout->addWidget(spinEdad);
    formLayout->addWidget(lblEspecialidad); formLayout->addWidget(txtEspecialidad);
    formLayout->addWidget(lblDoctor); formLayout->addWidget(txtDoctor);
    formLayout->addWidget(lblFecha); formLayout->addWidget(dateFecha);
    formLayout->addWidget(lblHora); formLayout->addWidget(timeHora);
    formLayout->addWidget(lblMotivo); formLayout->addWidget(txtMotivo);

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addWidget(btnGuardar);
    btnLayout->addWidget(btnMostrar);
    btnLayout->addWidget(btnActualizar);
    btnLayout->addWidget(btnEliminar);
    btnLayout->addWidget(btnLimpiar);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(btnLayout);
    mainLayout->addWidget(tabla);

    central->setLayout(mainLayout);

    connect(btnGuardar, &QPushButton::clicked, this, &Pacientes::agregarPaciente);
    connect(btnMostrar, &QPushButton::clicked, this, &Pacientes::mostrarPaciente);
    connect(btnActualizar, &QPushButton::clicked, this, &Pacientes::actualizarPaciente);
    connect(btnEliminar, &QPushButton::clicked, this, &Pacientes::eliminarPaciente);
    connect(btnLimpiar, &QPushButton::clicked, this, &Pacientes::limpiarCampos);

    cargarArchivo();
}

void Pacientes::agregarPaciente()
{
    if (txtId->text().isEmpty() || txtCedula->text().isEmpty() ||
        txtNombrePaciente->text().isEmpty() || txtEspecialidad->text().isEmpty() ||
        txtDoctor->text().isEmpty() || txtMotivo->text().isEmpty()) {

        QMessageBox::warning(this,"Campos vacíos",
                             "Complete todos los campos");
        return;
    }

    int row = tabla->rowCount();
    tabla->insertRow(row);

    tabla->setItem(row,0,new QTableWidgetItem(txtId->text()));
    tabla->setItem(row,1,new QTableWidgetItem(txtCedula->text()));
    tabla->setItem(row,2,new QTableWidgetItem(txtNombrePaciente->text()));
    tabla->setItem(row,3,new QTableWidgetItem(QString::number(spinEdad->value())));
    tabla->setItem(row,4,new QTableWidgetItem(txtEspecialidad->text()));
    tabla->setItem(row,5,new QTableWidgetItem(txtDoctor->text()));
    tabla->setItem(row,6,new QTableWidgetItem(dateFecha->date().toString("yyyy-MM-dd")));
    tabla->setItem(row,7,new QTableWidgetItem(timeHora->time().toString("HH:mm")));
    tabla->setItem(row,8,new QTableWidgetItem(txtMotivo->text()));

    guardarArchivo();
    QMessageBox::information(this,"Correcto","Paciente agregado correctamente.");
}

void Pacientes::mostrarPaciente()
{
    int row = tabla->currentRow();
    if (row < 0) {
        QMessageBox::warning(this,"Error","Seleccione un registro");
        return;
    }

    QString info;
    for (int i=0;i<9;i++) {
        info += tabla->horizontalHeaderItem(i)->text() + ": "
                + tabla->item(row,i)->text() + "\n";
    }

    QMessageBox::information(this,"Paciente",info);
}

void Pacientes::actualizarPaciente()
{
    int row = tabla->currentRow();
    if (row < 0) return;

    tabla->item(row,0)->setText(txtId->text());
    tabla->item(row,1)->setText(txtCedula->text());
    tabla->item(row,2)->setText(txtNombrePaciente->text());
    tabla->item(row,3)->setText(QString::number(spinEdad->value()));
    tabla->item(row,4)->setText(txtEspecialidad->text());
    tabla->item(row,5)->setText(txtDoctor->text());
    tabla->item(row,6)->setText(dateFecha->date().toString("yyyy-MM-dd"));
    tabla->item(row,7)->setText(timeHora->time().toString("HH:mm"));
    tabla->item(row,8)->setText(txtMotivo->text());

    guardarArchivo();
}

void Pacientes::eliminarPaciente()
{
    int row = tabla->currentRow();
    if (row < 0) return;

    tabla->removeRow(row);
    guardarArchivo();
}

void Pacientes::guardarArchivo()
{
    QFile file("pacientes.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    QTextStream out(&file);

    for (int i=0;i<tabla->rowCount();i++) {
        for (int j=0;j<tabla->columnCount();j++) {
            out << tabla->item(i,j)->text();
            if (j < tabla->columnCount()-1) out << ";";
        }
        out << "\n";
    }
    file.close();
}

void Pacientes::cargarArchivo()
{
    QFile file("pacientes.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    tabla->setRowCount(0);

    QTextStream in(&file);
    while (!in.atEnd()) {
        QStringList datos = in.readLine().split(";");
        int row = tabla->rowCount();
        tabla->insertRow(row);

        for (int i=0;i<datos.size();i++)
            tabla->setItem(row,i,new QTableWidgetItem(datos[i]));
    }
    file.close();
}

void Pacientes::limpiarCampos()
{
    txtId->clear();
    txtCedula->clear();
    txtNombrePaciente->clear();
    spinEdad->setValue(0);
    txtEspecialidad->clear();
    txtDoctor->clear();
    txtMotivo->clear();
}
