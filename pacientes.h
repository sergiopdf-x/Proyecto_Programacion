#ifndef PACIENTES_H
#define PACIENTES_H

#include <QMainWindow>
#include <QLineEdit>
#include <QSpinBox>
#include <QDateEdit>
#include <QTimeEdit>
#include <QTableWidget>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class Pacientes;
}
QT_END_NAMESPACE

class Pacientes : public QMainWindow
{
    Q_OBJECT

public:
    explicit Pacientes(QWidget *parent = nullptr);
    ~Pacientes();

private slots:
    void on_btnLogin_clicked();
    void agregarPaciente();
    void mostrarPaciente();
    void actualizarPaciente();
    void eliminarPaciente();
    void cargarArchivo();
    void guardarArchivo();
    void limpiarCampos();

private:
    Ui::Pacientes *ui;

    QLineEdit *txtId;
    QLineEdit *txtCedula;
    QLineEdit *txtNombrePaciente;
    QSpinBox *spinEdad;
    QLineEdit *txtEspecialidad;
    QLineEdit *txtDoctor;
    QDateEdit *dateFecha;
    QTimeEdit *timeHora;
    QLineEdit *txtMotivo;

    QPushButton *btnGuardar;
    QPushButton *btnMostrar;
    QPushButton *btnActualizar;
    QPushButton *btnEliminar;
    QPushButton *btnLimpiar;

    QTableWidget *tabla;

    void crearCrud();
};
#endif
