#include "gui.h"
#include "analysis.h"
#include "organsize.h"
#include <iostream>
#include <QPushButton>
#include <QFileDialog>

Gui::Gui(QWidget *parent) :
    QWidget(parent)
    {
    setGeometry(10,10,600, 400);

    m_button_dir = new QPushButton(" Select directory ", this);
    m_button_dir->setGeometry(150, 300, 150, 30);
    m_button_dir->setCheckable(true);

    m_button_analyze = new QPushButton(" Analyze ", this);
    m_button_analyze->setGeometry(330, 300, 80, 30);
    m_button_analyze->setCheckable(true);
    m_button_analyze->setEnabled(false);

    connect(m_button_dir, SIGNAL (clicked(bool)), this, SLOT (dirSelectorClicked(bool)));
    connect(m_button_analyze, SIGNAL (clicked(bool)), this, SLOT (analyzeDir(bool)));
}

void Gui::dirSelectorClicked(bool checked)
{
    if (checked) {
        QString path = QFileDialog::getExistingDirectory(this, tr("Choose catalog"), ".", QFileDialog::ReadOnly);
        //validate path?
        this->selected_path = path.toStdString();
        m_button_analyze->setEnabled(true);
        }
}

void Gui::analyzeDir(bool checked)
{
    Analysis USER(0);
    Organsize organize(this->selected_path, 0);
    std::cout << USER.machine_platform << '\n';
}
