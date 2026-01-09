#ifndef PACIENTE_H
#define PACIENTE_H

#include <QString>
#include <QDate>
#include <QTime>

struct Paciente {
    int id;
    QString cedula;
    QString nombrePaciente;
    int edad;
    QString especialidad;
    QString doctor;
    QDate fecha;
    QTime hora;
    QString motivo;
};

#endif // PACIENTE_H
