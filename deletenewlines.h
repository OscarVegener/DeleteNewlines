#ifndef DELETENEWLINES_H
#define DELETENEWLINES_H

#include <QMainWindow>
#include <QClipboard>
#include <QFileDialog>
#include <QTextStream>
#include "about.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DeleteNewlines; }
QT_END_NAMESPACE

class DeleteNewlines : public QMainWindow
{
    Q_OBJECT

public:
    DeleteNewlines(QWidget *parent = nullptr);
    ~DeleteNewlines();

private slots:
    void on_actionExit_triggered();

    void deleteNewLines_slot();

    void on_copyButton_clicked();

    void on_clearButton_clicked();

    void status_cleared_slot();

    void status_copied_slot();

    void on_actionAbout_triggered();

    void on_actionSave_edited_text_triggered();

private:
    Ui::DeleteNewlines *ui;
    QClipboard *clipboard;
};
#endif // DELETENEWLINES_H
