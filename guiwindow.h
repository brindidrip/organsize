#ifndef GUIWINDOW_H
#define GUIWINDOW_H

#include <QMainWindow>
#include "ui_guiwindow.h"

namespace Ui {
class GuiWindow;
}

class GuiWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GuiWindow( QWidget *parent = 0);
    ~GuiWindow();
    void textEditBoxInit();
    std::string selected_opath;
    std::string selected_file;
    std::string selected_fileDir;
    QString selected_unitStr;
    int selected_unit;
    int selected_size;

private slots:
    void dirSelector( bool checked );
    void fileSelector( bool checked );
    void segmentSelector( bool checked );
    void organsizeFile( bool checked );
    void reconstructFile( bool checked );
    void comboBoxValue ( int );

private:
    Ui::GuiWindow *ui;
};

#endif // GUIWINDOW_H
