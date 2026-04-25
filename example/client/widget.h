#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMultiMap>
#include <QPair>
#include <QSet>
#include <QByteArray>

#include "qrpcclient.h"

QRPC_USE_NAMESPACE



struct CustomizeData {
    QSet<QString> sets;
    QString     string;
    QMultiMap<int, double> mulMap;
    QPair<QByteArray, std::string> pair;

    friend inline QDataStream &operator<<(QDataStream &out, const CustomizeData &in)
    {
        out << in.sets << in.string << in.mulMap << in.pair;
        return out;
    }

    friend inline QDataStream &operator>>(QDataStream &in, CustomizeData &out)
    {
        in >> out.sets >> out.string >> out.mulMap >> out.pair;
        return in;
    }
};
Q_DECLARE_METATYPE(CustomizeData)


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    template<typename T>
    QString toQString(const T &v) {
        QString str;
        QDebug dbg(&str);
        dbg.noquote() << v;
        return str;
    }

private slots:
    void onConnectChanged(bool);

    void on_pushButton_conn_clicked();

    void on_pushButton_disconn_clicked();

    void on_pushButton_test_clicked();

    void on_pushButton_test_2_clicked();

    void on_pushButton_test_3_clicked();

    void on_pushButton_test_4_clicked();

    void on_pushButton_test_5_clicked();

    void on_pushButton_test_6_clicked();

    void on_pushButton_test_7_clicked();

    void on_pushButton_test_8_clicked();

    void on_pushButton_test_9_clicked();

    void on_pushButton_test_10_clicked();

    void on_pushButton_test_11_clicked();

    void on_pushButton_test_12_clicked();

    void on_pushButton_test_13_clicked();

    void on_pushButton_clicked();

private:
    Ui::Widget *ui;

    QRpcClient _cli;
};
#endif // WIDGET_H
