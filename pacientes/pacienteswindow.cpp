#include "pacienteswindow.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QHeaderView>
#include <QFile>
#include <QTextStream>

PacientesWindow::PacientesWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *central = new QWidget(this);
    this->setCentralWidget(central);


    QLabel *lblId = new QLabel("ID:");
    txtId = new QLineEdit;

    QLabel *lblCedula = new QLabel("Cédula:");
    txtCedula = new QLineEdit;

    QLabel *lblNombre = new QLabel("Nombre Paciente:");
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

    // Botones
    btnGuardar = new QPushButton("Agregar");
    btnEliminar = new QPushButton("Mostrar");
    btnActualizar = new QPushButton("Editar");
    btnLimpiar = new QPushButton("Limpiar");

    // Tabla
    tabla = new QTableWidget;
    tabla->setColumnCount(9);
    tabla->setHorizontalHeaderLabels({"ID","Cédula","Nombre Paciente","Edad","Especialidad","Doctor","Fecha","Hora","Motivo"});
    tabla->horizontalHeader()->setStretchLastSection(true);
    tabla->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Layout formulario
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

    // Layout botones
    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addWidget(btnGuardar);
    btnLayout->addWidget(btnMostrar);
    btnLayout->addWidget(btnActualizar);
    btnLayout->addWidget(btnLimpiar);

    // Layout principal
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(btnLayout);
    mainLayout->addWidget(tabla);

    central->setLayout(mainLayout);

    // Conexiones
    connect(btnGuardar, &QPushButton::clicked, this, &PacientesWindow::agregarPaciente);
    connect(btnEliminar, &QPushButton::clicked, this, &PacientesWindow::mostrarPaciente);
    connect(btnActualizar, &QPushButton::clicked, this, &PacientesWindow::editarPaciente);
    connect(tabla, &QTableWidget::cellClicked, this, &PacientesWindow::cargarPaciente);
    connect(btnLimpiar, &QPushButton::clicked, this, &PacientesWindow::limpiarCampos);

    cargarPacientesDesdeArchivo();
}

// Función agregar paciente
void PacientesWindow::agregarPaciente() {
    int row = tabla->rowCount();
    tabla->insertRow(row);

    tabla->setItem(row, 0, new QTableWidgetItem(txtId->text()));
    tabla->setItem(row, 1, new QTableWidgetItem(txtCedula->text()));
    tabla->setItem(row, 2, new QTableWidgetItem(txtNombrePaciente->text()));
    tabla->setItem(row, 3, new QTableWidgetItem(QString::number(spinEdad->value())));
    tabla->setItem(row, 4, new QTableWidgetItem(txtEspecialidad->text()));
    tabla->setItem(row, 5, new QTableWidgetItem(txtDoctor->text()));
    tabla->setItem(row, 6, new QTableWidgetItem(dateFecha->date().toString("yyyy-MM-dd")));
    tabla->setItem(row, 7, new QTableWidgetItem(timeHora->time().toString("HH:mm")));
    tabla->setItem(row, 8, new QTableWidgetItem(txtMotivo->text()));

    guardarPacientes();
    QMessageBox::information(this, "Mensaje", "Paciente ingresado correctamente");
    limpiarCampos();
}

void PacientesWindow::mostrarPaciente() {
    int row = tabla->currentRow();
    if (row >= 0) {
        QString info;
        info += "ID: " + tabla->item(row, 0)->text() + "\n";
        info += "Cédula: " + tabla->item(row, 1)->text() + "\n";
        info += "Nombre Paciente: " + tabla->item(row, 2)->text() + "\n";
        info += "Edad: " + tabla->item(row, 3)->text() + "\n";
        info += "Especialidad: " + tabla->item(row, 4)->text() + "\n";
        info += "Doctor: " + tabla->item(row, 5)->text() + "\n";
        info += "Fecha: " + tabla->item(row, 6)->text() + "\n";
        info += "Hora: " + tabla->item(row, 7)->text() + "\n";
        info += "Motivo: " + tabla->item(row, 8)->text();

        QMessageBox::information(this, "Datos del Paciente", info);
    } else {
        QMessageBox::warning(this, "Error", "Seleccione un paciente de la tabla para mostrar");
    }
}
