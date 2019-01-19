/********************************************************************************
** Form generated from reading UI file 'guiwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUIWINDOW_H
#define UI_GUIWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GuiWindow
{
public:
    QWidget *centralwidget;
    QTextEdit *textEdit;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_3;
    QPushButton *m_button_segment;
    QPushButton *m_button_dir;
    QPushButton *m_button_reconstruct;
    QPushButton *m_button_organsize;
    QPushButton *m_button_file;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_4;
    QLabel *label_2;
    QLabel *segmentSizeLabel;
    QComboBox *segmentUnitComboBox;
    QSlider *verticalSlider;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *GuiWindow)
    {
        if (GuiWindow->objectName().isEmpty())
            GuiWindow->setObjectName(QStringLiteral("GuiWindow"));
        GuiWindow->resize(800, 600);
        GuiWindow->setMinimumSize(QSize(799, 0));
        centralwidget = new QWidget(GuiWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(20, 30, 761, 351));
        textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(50, 400, 431, 141));
        gridLayout_3 = new QGridLayout(gridLayoutWidget);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        m_button_segment = new QPushButton(gridLayoutWidget);
        m_button_segment->setObjectName(QStringLiteral("m_button_segment"));

        gridLayout_3->addWidget(m_button_segment, 0, 1, 1, 1);

        m_button_dir = new QPushButton(gridLayoutWidget);
        m_button_dir->setObjectName(QStringLiteral("m_button_dir"));

        gridLayout_3->addWidget(m_button_dir, 1, 0, 1, 2);

        m_button_reconstruct = new QPushButton(gridLayoutWidget);
        m_button_reconstruct->setObjectName(QStringLiteral("m_button_reconstruct"));

        gridLayout_3->addWidget(m_button_reconstruct, 2, 1, 1, 1);

        m_button_organsize = new QPushButton(gridLayoutWidget);
        m_button_organsize->setObjectName(QStringLiteral("m_button_organsize"));

        gridLayout_3->addWidget(m_button_organsize, 2, 0, 1, 1);

        m_button_file = new QPushButton(gridLayoutWidget);
        m_button_file->setObjectName(QStringLiteral("m_button_file"));

        gridLayout_3->addWidget(m_button_file, 0, 0, 1, 1);

        gridLayoutWidget_2 = new QWidget(centralwidget);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(520, 400, 231, 131));
        gridLayout_4 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(gridLayoutWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_4->addWidget(label_2, 0, 1, 1, 1);

        segmentSizeLabel = new QLabel(gridLayoutWidget_2);
        segmentSizeLabel->setObjectName(QStringLiteral("segmentSizeLabel"));

        gridLayout_4->addWidget(segmentSizeLabel, 1, 1, 1, 1);

        segmentUnitComboBox = new QComboBox(gridLayoutWidget_2);
        segmentUnitComboBox->setObjectName(QStringLiteral("segmentUnitComboBox"));

        gridLayout_4->addWidget(segmentUnitComboBox, 2, 1, 1, 1);

        verticalSlider = new QSlider(gridLayoutWidget_2);
        verticalSlider->setObjectName(QStringLiteral("verticalSlider"));
        verticalSlider->setOrientation(Qt::Vertical);

        gridLayout_4->addWidget(verticalSlider, 0, 2, 3, 1);

        GuiWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(GuiWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        GuiWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(GuiWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        GuiWindow->setStatusBar(statusbar);

        retranslateUi(GuiWindow);

        QMetaObject::connectSlotsByName(GuiWindow);
    } // setupUi

    void retranslateUi(QMainWindow *GuiWindow)
    {
        GuiWindow->setWindowTitle(QApplication::translate("GuiWindow", "Organsize", 0));
        m_button_segment->setText(QApplication::translate("GuiWindow", "Select initial segment", 0));
        m_button_dir->setText(QApplication::translate("GuiWindow", "Select output directory", 0));
        m_button_reconstruct->setText(QApplication::translate("GuiWindow", "Reconstruct", 0));
        m_button_organsize->setText(QApplication::translate("GuiWindow", "Organsize", 0));
        m_button_file->setText(QApplication::translate("GuiWindow", "Select file to segment", 0));
        label_2->setText(QApplication::translate("GuiWindow", "Segment Size:", 0));
        segmentSizeLabel->setText(QString());
        segmentUnitComboBox->clear();
        segmentUnitComboBox->insertItems(0, QStringList()
         << QApplication::translate("GuiWindow", "byte", 0)
         << QApplication::translate("GuiWindow", "KB", 0)
         << QApplication::translate("GuiWindow", "MB", 0)
         << QApplication::translate("GuiWindow", "GB", 0)
         << QApplication::translate("GuiWindow", "TB", 0)
        );
    } // retranslateUi

};

namespace Ui {
    class GuiWindow: public Ui_GuiWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUIWINDOW_H
