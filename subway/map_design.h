#ifndef MAP_DESIGN_H
#define MAP_DESIGN_H

#include <QWidget>

namespace Ui {
class map_design;
}

class map_design : public QWidget
{
    Q_OBJECT

public:
    explicit map_design(QWidget *parent = nullptr);
    ~map_design();

private:
    Ui::map_design *ui;
};

#endif // MAP_DESIGN_H
