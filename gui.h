#ifndef GUI_H
#define GUI_H

#include <QWidget>

class QPushButton;
class Gui : public QWidget
{
    Q_OBJECT
    public:
        explicit Gui(QWidget *parent = 0);
        std::string selected_path;
    private slots:
        void dirSelectorClicked(bool checked);
        void analyzeDir(bool checked);
    private:
    QPushButton *m_button_dir;
    QPushButton *m_button_analyze;

};

#endif // GUI_H
