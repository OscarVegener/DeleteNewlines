#include "deletenewlines.h"
#include "ui_deletenewlines.h"

DeleteNewlines::DeleteNewlines(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DeleteNewlines)
{
    ui->setupUi(this);
    clipboard = QGuiApplication::clipboard();
    connect(ui->originalText, &QTextEdit::textChanged, this, &DeleteNewlines::deleteNewLines_slot);
    connect(ui->copyButton, &QPushButton::clicked, this, &DeleteNewlines::status_copied_slot);
    connect(ui->clearButton, &QPushButton::clicked, this, &DeleteNewlines::status_cleared_slot);
}

DeleteNewlines::~DeleteNewlines()
{
    delete ui;
}


void DeleteNewlines::on_actionExit_triggered()
{
    QApplication::quit();
}

void DeleteNewlines::deleteNewLines_slot()
{
    QString text = ui->originalText->toPlainText();
    text.replace("\n", " ", Qt::CaseSensitivity::CaseSensitive);
    while (text.lastIndexOf("  ") != -1){
        text.replace("  ", " ");
    }
    ui->editedText->setText(text);
}

void DeleteNewlines::on_copyButton_clicked()
{
    clipboard->setText(ui->editedText->toPlainText());
}

void DeleteNewlines::on_clearButton_clicked()
{
    ui->originalText->clear();
}

void DeleteNewlines::status_cleared_slot()
{
    ui->statusbar->showMessage("Original text form cleared!", 1500);
}

void DeleteNewlines::status_copied_slot()
{
    ui->statusbar->showMessage("Edited text copied!", 1500);
}

void DeleteNewlines::on_actionAbout_triggered()
{
    About *window = new About(this);
    window->setWindowFlags(window->windowFlags() & ~Qt::WindowContextHelpButtonHint | Qt::MSWindowsFixedSizeDialogHint);
    window->setModal(true);
    window->setAttribute(Qt::WA_DeleteOnClose);
    window->show();
}

void DeleteNewlines::on_actionSave_edited_text_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save file"), QCoreApplication::applicationDirPath(), tr("Text file (*.txt)"));
    if (!filename.isEmpty()){
        if (filename.lastIndexOf(".txt") == -1){
            filename = filename + ".txt";
        }
        QFile file(filename);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream out(&file);
            out << ui->editedText->toPlainText();
            out.flush();
        }
        file.close();
        ui->statusbar->showMessage("File saved " + filename, 1500);
    }
}
