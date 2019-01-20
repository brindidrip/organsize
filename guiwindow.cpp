#include "guiwindow.h"
#include "ui_guiwindow.h"
#include "analysis.h"
#include "organsize.h"
#include <iostream>
#include <QFileDialog>
#include <experimental/filesystem>

GuiWindow::GuiWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GuiWindow)
{
    ui->setupUi(this);

    textEditBoxInit();

    ui->m_button_file->setCheckable(true);
    ui->m_button_file->setEnabled(true);

    ui->m_button_dir->setCheckable(true);
    ui->m_button_dir->setEnabled(false);
    // Set default pwd as path
    this->selected_opath = std::experimental::filesystem::current_path();

    ui->m_button_organsize->setCheckable(true);
    ui->m_button_organsize->setEnabled(false);

    ui->m_button_segment->setCheckable(true);
    ui->m_button_segment->setEnabled(true);
    // Set default segment size
    this->selected_size = 1500;

    ui->m_button_reconstruct->setCheckable(true);
    ui->m_button_reconstruct->setEnabled(false);

    connect(ui->m_button_file, SIGNAL (clicked(bool)), this, SLOT (fileSelector(bool)));
    connect(ui->m_button_dir, SIGNAL (clicked(bool)), this, SLOT (dirSelector(bool)));
    connect(ui->m_button_segment, SIGNAL (clicked(bool)), this, SLOT (segmentSelector(bool)));
    connect(ui->m_button_organsize, SIGNAL (clicked(bool)), this, SLOT (organsizeFile(bool)));
    connect(ui->m_button_reconstruct, SIGNAL (clicked(bool)), this, SLOT (reconstructFile(bool)));


    ui->verticalSlider->setRange(1, 1024);
    ui->verticalSlider->setSingleStep(100);
    // Set default unit size
    this->selected_unitStr = QString::fromStdString("byte");

    connect(ui->verticalSlider, SIGNAL(valueChanged(int)), this, SLOT(comboBoxValue(int)));
    // TODO 
    // change mfilesize to long long in organize
    // change bytes size reconstruct  
}

GuiWindow::~GuiWindow()
{
    delete ui;
}

void GuiWindow::textEditBoxInit()
{
    ui->textEdit->setFont(QFont("Monospace", 10));
    ui->textEdit->append("  ------------------------------------------------------------------------------");
    ui->textEdit->append("  -.d88888b.----------------------------------------------d8b-------------------");
    ui->textEdit->append("  d88P---Y88b---------------------------------------------Y8P-------------------");
    ui->textEdit->append("  888-----888-------------------------------------------------------------------");
    ui->textEdit->append("  888-----888-888d888--.d88b.---8888b.--88888b.--.d8888b--888-88888888--.d88b.--");
    ui->textEdit->append("  888-----888-888P----d88P-88b------88b-888--88b-88K------888----d88P--d8P--Y8b-");
    ui->textEdit->append("  888-----888-888-----888--888-.d888888-888--888--Y8888b.-888---d88P---88888888-");
    ui->textEdit->append("  Y88b.-.d88P-888-----Y88b-888-888--888-888--888------X88-888--d88P----Y8b.-----");
    ui->textEdit->append("  --Y88888P---888-------Y88888--Y888888-888--888--88888P'-888-88888888---Y8888--");
    ui->textEdit->append("  -------------------------888--------------------------------------------------");
    ui->textEdit->append("  --------------------Y8b-d88P--------------------------------------------------");
    ui->textEdit->append("  ----------------------Y88P----------------------------------------------------");
    ui->textEdit->append("  ------------------------------------------------------------------------------");
    ui->textEdit->append("  ------------------------------------------------------------------------------");
    ui->textEdit->append("  ------------------------------------------------------------------------------");
    ui->textEdit->append("  ==============================================================================");

    ui->textEdit->append("\n\nMIT License\n");
    ui->textEdit->append("Copyright (c) 2019 Domenico Martinelli\n\n\\Permission is hereby granted, free of charge, to any person obtaining a copy"
                         "of this software and associated documentation files (the \"Software\"), to deal "
                         "in the Software without restriction, including without limitation the rights "
                         "to use, copy, modify, merge, publish, distribute, sublicense, and/or sell "
                         "copies of the Software, and to permit persons to whom the Software is "
                         "furnished to do so, subject to the following conditions:\n\n"
                         "The above copyright notice and this permission notice shall be included in all "
                         "copies or substantial portions of the Software.\n\n"
                         "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR "
                         "IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, "
                         "FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE "
                         "AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER"
                         "LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.");
    ui->textEdit->moveCursor(QTextCursor::Start);
    ui->textEdit->setReadOnly(true);
}

void GuiWindow::dirSelector(bool checked)
{
    if (checked) {
        QString path = QFileDialog::getExistingDirectory(this, tr("Choose catalog"), ".", QFileDialog::ReadOnly);
        //validate path?
        this->selected_opath = path.toStdString();
        ui->textEdit->append("New output path: " + QString::fromStdString(this->selected_opath));
        }
}

void GuiWindow::fileSelector(bool checked)
{
    if (checked) {
        ui->textEdit->setText("Selecting file to segment...\n");

        QString file = QFileDialog::getOpenFileName(this, tr("Choose a file to organsize"), tr("."));
        this->selected_file = file.toStdString();

        ui->textEdit->append("File: '" + file + "'");
        ui->textEdit->append("Current output path: " + QString::fromStdString(this->selected_opath));

        ui->m_button_organsize->setEnabled(true);
        ui->m_button_dir->setEnabled(true);
        ui->m_button_reconstruct->setEnabled(false);
        ui->m_button_segment->setEnabled(false);
    }
}

void GuiWindow::segmentSelector(bool checked)
{
    if (checked) {
        ui->textEdit->setText("Selecting initial segment to reconstruct...\n");

        QString file = QFileDialog::getOpenFileName(this, tr("Choose initial segment to reconstruct original file."), tr("."));
        this->selected_file = file.toStdString();

        QFileInfo fi(file);
        this->selected_fileDir = fi.dir().path().toStdString();

        ui->textEdit->append("File: '" + file + "'");
        ui->textEdit->append("Current output path: " + QString::fromStdString(this->selected_opath));
        ui->textEdit->setTextColor(Qt::red);
        ui->textEdit->append("Please ensure that all segments are within the specified directory.");
        ui->textEdit->setTextColor(Qt::black);

        ui->m_button_organsize->setEnabled(false);
        ui->m_button_dir->setEnabled(true);
        ui->m_button_file->setEnabled(false);
        ui->m_button_reconstruct->setEnabled(true);
    }
}

void GuiWindow::organsizeFile(bool checked)
{
    if(checked)
    {
        Analysis analysis(this->selected_file, this->selected_size, this->selected_unit);
        
        if(!analysis.validSelection)
        {   
            ui->textEdit->setText("*********** ERROR ***********");
            ui->textEdit->append(QString::fromStdString(analysis.errorString));
        }
        else
        {
            ui->textEdit->append("File selected: " + QString::fromStdString(this->selected_file)
            + "\nSelected segment size: " + QString::number(this->selected_size) + " " + this->selected_unitStr
            + "s.\nSelected file size: " + QString::number(analysis.mFileSize) + " bytes.");

            //std::cout << analysis.machinePlatform << std::endl;
            Organsize organize(this->selected_file, this->selected_fileDir, this->selected_opath, analysis.mFileSize, analysis.mSegments, analysis.mSegSize, analysis.mRemainderSegSize, analysis.mTotalSegments);
            organize.segmentFile();
            
            ui->textEdit->append("=================================================\n\nA total of " + QString::number(analysis.mTotalSegments)
            + " segments were created in directory: " + QString::fromStdString(this->selected_opath) + "\nSegmentation complete.");

            ui->m_button_reconstruct->setEnabled(true);
        }
    }
}

void GuiWindow::reconstructFile(bool checked)
{
    if(checked)
    {
        Analysis analysis(this->selected_file, this->selected_size, this->selected_unit);

        
        if(!analysis.validSelection)
        {   
            ui->textEdit->setText("*********** ERROR ***********");
            ui->textEdit->append(QString::fromStdString(analysis.errorString));
        }
        else
        {
            ui->textEdit->append("File selected: " + QString::fromStdString(this->selected_file));

            //std::cout << analysis.machinePlatform << std::endl;

            Organsize organize(this->selected_file, this->selected_fileDir, this->selected_opath, analysis.mFileSize, analysis.mSegments, analysis.mSegSize, analysis.mRemainderSegSize, analysis.mTotalSegments);
            organize.reconstructFile();

            ui->textEdit->append("=================================================\nReconstruction complete.");
            ui->m_button_reconstruct->setEnabled(true);
        }
    }
}

void GuiWindow::comboBoxValue (int k) {
    ui->segmentSizeLabel->setText(QString::number(k) + "  " + ui->segmentUnitComboBox->currentText());
    this->selected_size = k;
    this->selected_unit = ui->segmentUnitComboBox->currentIndex();
    this->selected_unitStr = ui->segmentUnitComboBox->currentText();
}
