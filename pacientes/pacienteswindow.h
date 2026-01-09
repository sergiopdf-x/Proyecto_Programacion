#ifndef PACIENTESWINDOW_H
#define PACIENTESWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QDateEdit>
#include <QTimeEdit>
#include <QPushButton>

class PacientesWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit PacientesWindow(QWidget *parent = nullptr);

private:
    // Campos del formulario
    QLineEdit *txtId;
    QLineEdit *txtCedula;
    QLineEdit *txtNombrePaciente;
    QSpinBox  *spinEdad;
    QLineEdit *txtEspecialidad;
    QLineEdit *txtDoctor;
    QDateEdit *dateFecha;
    QTimeEdit *timeHora;
    QLineEdit *txtMotivo;

    // Botones
    QPushButton *btnAgregar;
    QPushButton *btnMostrar;

    // Tabla
    QTableWidget *tabla;

    // Funciones auxiliares
    void limpiarCampos();
    void guardarPacientes();
    void cargarPacientesDesdeArchivo();

private slots:
    void agregarPaciente();
    void mostrarPaciente();
};

#endif // PACIENTESWINDOW_H
