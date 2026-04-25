#include "widget.h"
#include "ui_widget.h"

#include <QIntValidator>

#include <QDateTime>
#include <QSize>
#include <QChar>
#include <QVariantMap>
#include <QSet>
#include <QStack>
#include <QVector>
#include <QMultiMap>
#include <QLinkedList>
#include <QQueue>

using namespace std;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QIntValidator *validator = new QIntValidator(this);
    validator->setRange(0, 65535);
    ui->lineEdit_port->setValidator(validator);

    _cli.setReconnectInterval(3000);
    connect(&_cli, &QRpcClient::signalConnectChanged, this, &Widget::onConnectChanged);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onConnectChanged(bool isValid)
{
    ui->label_conn_status->setText(isValid ? "connect" : "disconnect");
}

void Widget::on_pushButton_conn_clicked()
{
    const QString ip = ui->lineEdit_ip->text().trimmed();
    quint16 port = ui->lineEdit_port->text().toUShort();
    _cli.connectToServer(ip.toStdString().c_str(), port, true);
}

void Widget::on_pushButton_disconn_clicked()
{
    _cli.disconnectFromServer();
}

void Widget::on_pushButton_test_clicked()
{
    QRpcCall call;
    call.setModuleName("TestService");
    call.setMethodName("testFun1");
    QRpcResult<void> result = _cli.invokeMethod(call);
    const QString strRet = QString("invokeMethod \"void testFun1()\": call result: error:%1,errorString:%2")
            .arg(result.error()).arg(result.errorString());

    ui->textEdit->append(strRet + "\n");
}

void Widget::on_pushButton_test_2_clicked()
{
    QRpcCall call;
    call.setModuleName("TestService");
    call.setMethodName("testFun2");
    QRpcResult<void> result = _cli.invokeMethod(call, 666);
    const QString strRet = QString("invokeMethod \"void testFun2(int)\": call result: error:%1,errorString:%2")
            .arg(result.error()).arg(result.errorString());

    ui->textEdit->append(strRet + "\n");
}


void Widget::on_pushButton_test_3_clicked()
{
    QRpcCall call;
    call.setModuleName("TestService");
    call.setMethodName("testFun3");
    QRpcResult<int> result = _cli.invokeMethod(call, 10, 100);
    const QString strRet = QString("invokeMethod \"int testFun3(int, int)\": call result: error:%1,errorString:%2---return result:%3")
            .arg(result.error())
            .arg(result.errorString())
            .arg(result);

    ui->textEdit->append(strRet + "\n");
}


void Widget::on_pushButton_test_4_clicked()
{
    const QString qString = "test qstring";
    const QByteArray qByteArray = "test qByteArray";
    double dValue = 100.1234567890;
    float fValue = 66.123456f;
    quint64 uIntValue = 199999999997;
    bool bValue = true;
    std::string cString = "test std::string";
    QDateTime dateTime = QDateTime::currentDateTime();
    QSize size = QSize(111,222);

    QRpcCall call;
    call.setModuleName("TestService");
    call.setMethodName("testFun4");
    QRpcResult<QChar> result = _cli.invokeMethod(call, qString, qByteArray, dValue, fValue, uIntValue, bValue, cString, dateTime, size);


    const QString invokeMethod = "invokeMethod \"QChar testFun4(const QString &, const QByteArray & ,double,float,quint64,bool,std::string,QDateTime,QSize)\":";
    ui->textEdit->append(invokeMethod);
    const QString strRet = QString("\tcall result: error:%1,errorString:%2---return result:%3")
                            .arg(result.error())
                            .arg(result.errorString())
                            .arg(result);
    ui->textEdit->append(strRet + "\n");
}


void Widget::on_pushButton_test_5_clicked()
{
    QList<int> list;
    list << 1 <<2 <<3 <<4 << 5 << 6;
    QVector<QString> vec;
    vec << "qstring1" << "qstring2" << "qstring3" << "qstring4" << "qstring5" << "qstring6" << "qstring7";
    QSet<QByteArray> set;
    set << "byteArray1" << "byteArray2" << "byteArray3" << "byteArray4" << "byteArray5";
    QStack<std::string> stack;
    stack << "cstring1" <<"cstring2" << "cstring3" << "cstring4"<< "cstring5";
    QQueue<QSize> queue;
    queue << QSize(1,10) << QSize(2,20) << QSize(3,30) << QSize(4,40) << QSize(5,50);

    QMap<quint64, std::vector<int>> map;
    std::vector<int> v1 = {1,11,111,1111,11111};
    std::vector<int> v2 = {2,22,222,2222,22222};
    std::vector<int> v3 = {3,33,333,3333,33333};
    map.insert(100, v1);
    map.insert(200, v2);
    map.insert(300, v3);

    QHash<int, QString> hash;
    hash.insert(1,"qstring1");
    hash.insert(2,"qstring2");
    hash.insert(3,"qstring3");


    QLinkedList<double> linkeList;
    linkeList << 1.01 << 2.01 << 3.02 << 4.03;

    QMultiHash<int, QString> mulHash;
    mulHash.insert(1,"this1");
    mulHash.insert(1,"this11");
    mulHash.insert(1,"this111");

    mulHash.insert(2,"this2");
    mulHash.insert(2,"this22");
    mulHash.insert(2,"this222");

    QMultiMap<QByteArray, double> mulMap;
    mulMap.insert("byte1", 1.02);
    mulMap.insert("byte1", 1.03);
    mulMap.insert("byte2", 2.02);
    mulMap.insert("byte2", 2.03);

    QRpcCall call;
    call.setModuleName("TestService");
    call.setMethodName("testFun5");
    QRpcResult<bool> result = _cli.invokeMethod(call, list, vec, set, stack, queue, map, hash, linkeList,mulHash,mulMap);
    const QString invokeMethod = QString("invokeMethod \"bool testFun5("
                                   "const QList<int>, "
                                   "const QVector<QString> ,"
                                   "const QSet<QByteArray>,"
                                   "const QStack<std::string>,"
                                   "const QQueue<QSize>,"
                                   "const QMap<quint64, std::vector<int>>,"
                                   "const QHash<int, QString>,"
                                   "const QLinkedList<double>,"
                                   "const QMultiHash<int, QString>,"
                                   "const QMultiMap<QByteArray, double>)\":");
    ui->textEdit->append(invokeMethod);


    const QString strRet = QString("\tcall result: error:%1,errorString:%2---return result:%3")
                            .arg(result.error())
                            .arg(result.errorString())
                            .arg(result ? "true" : "false");
    ui->textEdit->append(strRet + "\n");
}


void Widget::on_pushButton_test_6_clicked()
{
    list<int> list = {1, 2, 3 ,4, 5, 6};
    vector<std::string> vec = { "cstring1" , "cstring2", "cstring3" };
    set<double> set;
    set.insert(1.11);
    set.insert(2.22);
    set.insert(3.33);
    deque<QSize> deque;
    deque.push_back(QSize(1,10));
    deque.push_back(QSize(2,20));

    std::map<quint64, QVector<int>> map;
    QVector<int> v1 = {1,11,111,1111,11111};
    QVector<int> v2 = {2,22,222,2222,22222};
    QVector<int> v3 = {3,33,333,3333,33333};
    map.insert(std::pair<quint64, QVector<int>>(100,v1));
    map.insert(std::pair<quint64, QVector<int>>(200,v2));
    map.insert(std::pair<quint64, QVector<int>>(300,v3));

    std::multimap<int, QString> mulMap;
    mulMap.insert(std::pair<int,QString>(10, "10"));
    mulMap.insert(std::pair<int,QString>(10, "100"));
    mulMap.insert(std::pair<int,QString>(20, "20"));
    mulMap.insert(std::pair<int,QString>(20, "200"));

    std::unordered_map<int, QString> unMap;
    unMap.insert(std::pair<int,QString>(77, "77"));
    unMap.insert(std::pair<int,QString>(99, "99"));

    QRpcCall call;
    call.setModuleName("TestService");
    call.setMethodName("testFun6");
    QRpcResult<CustomizeData> result = _cli.invokeMethod(call, list, vec, set, deque, map, mulMap, unMap);

    const QString invokeMethod = QString("invokeMethod \"CustomizeData testFun6("
                                   "const std::list<int>, "
                                   "const std::vector<std::string> ,"
                                   "const std::set<double>,"
                                   "const std::deque<QSize>,"
                                   "const std::map<quint64, QVector<int>>,"
                                   "const std::multimap<int, QString>,"
                                   "const std::unordered_map<int, QString>)\":");
    ui->textEdit->append(invokeMethod);


    CustomizeData cData = result;
    QString rSet;
    for (auto v : cData.sets) {
        rSet.append(v);
        rSet.append(';');
    }
    QString rMap;
    for (auto it = cData.mulMap.constBegin(); it != cData.mulMap.constEnd(); ++it)
    {
        rMap += QString("key=%1,value=%2;").arg(it.key()).arg(it.value());
    }

    QString strResult;
    strResult.append("sets:(");
    strResult.append(rSet);
    strResult.append(");");
    strResult.append("string:(");
    strResult.append(cData.string);
    strResult.append(");");
    strResult.append("mulMap:(");
    strResult.append(rMap);
    strResult.append(");");

    QString strPar = QString("first=%1,second=%2")
                    .arg(cData.pair.first.constData())
                    .arg(cData.pair.second.c_str());
    strResult.append("pair:(");
    strResult.append(strPar);
    strResult.append(")");

    const QString strRet = QString("\tcall result: error:%1,errorString:%2---return result:%3")
                            .arg(result.error())
                            .arg(result.errorString())
                            .arg(strResult);
    ui->textEdit->append(strRet + "\n");
}


void Widget::on_pushButton_test_7_clicked()
{
    CustomizeData cData;

    cData.sets.insert("aaa");
    cData.sets.insert("bbb");
    cData.sets.insert("ccc");
    cData.string = "MainWnd";
    cData.mulMap.insert(1,11.123);
    cData.mulMap.insert(1,12.123);
    cData.mulMap.insert(2,21.123);
    cData.mulMap.insert(2,22.123);
    cData.pair.first =   "123";
    cData.pair.second = "rrrrrr";


    QRpcCall call;
    call.setModuleName("TestService");
    call.setMethodName("testFun7");

    QRpcResult<QByteArray> result = _cli.invokeMethod(call, cData);

    const QString invokeMethod = QString("invokeMethod \"QByteArray testFun7(CustomizeData data)\":");
    ui->textEdit->append(invokeMethod);


    QByteArray b = result;
    const QString strRet = QString("\tcall result: error:%1,errorString:%2---return result:%3")
                            .arg(result.error())
                            .arg(result.errorString())
                            .arg(b.constData());
    ui->textEdit->append(strRet + "\n");
}


void Widget::on_pushButton_test_8_clicked()
{
    QRpcCall call;
    call.setModuleName("TestService");
    call.setMethodName("testReference1");

    CustomizeData data;
    QRpcResult<bool> result = _cli.invokeMethod(call, qReference(data));


    const QString invokeMethod = QString("invokeMethod \"bool testReference(""CustomizeData &)\":");
    ui->textEdit->append(invokeMethod);


    QString rSet;
    for (auto v : data.sets) {
        rSet.append(v);
        rSet.append(';');
    }
    QString rMap;
    for (auto it = data.mulMap.constBegin(); it != data.mulMap.constEnd(); ++it)
    {
        rMap += QString("key=%1,value=%2;").arg(it.key()).arg(it.value());
    }

    QString strResult;
    strResult.append("sets:(");
    strResult.append(rSet);
    strResult.append(");");
    strResult.append("string:(");
    strResult.append(data.string);
    strResult.append(");");
    strResult.append("mulMap:(");
    strResult.append(rMap);
    strResult.append(");");

    QString strPar = QString("first=%1,second=%2")
                    .arg(data.pair.first.constData())
                    .arg(data.pair.second.c_str());
    strResult.append("pair:(");
    strResult.append(strPar);
    strResult.append(")");

    const QString strRet = QString("\tcall result: error:%1,errorString:%2---return result:%3---reference result:%4")
                            .arg(result.error())
                            .arg(result.errorString())
                            .arg(result ? "true": "false")
                            .arg(strResult);
    ui->textEdit->append(strRet + "\n");
}


void Widget::on_pushButton_test_9_clicked()
{
    QRpcCall call;
    call.setModuleName("TestService");
    call.setMethodName("testReference2");

    QHash<int, QString> outHash;
    QRpcResult<bool> result = _cli.invokeMethod(call, QString("input"), qReference(outHash));

    const QString invokeMethod = QString("invokeMethod \"bool testReference2(const QString &, QHash<int, QString>&)\":");
    ui->textEdit->append(invokeMethod);


    QString hashString;
    QDebug debug(&hashString);
    debug << outHash;
    const QString strRet = QString("\tcall result: error:%1,errorString:%2---return result:%3---reference result:%4")
                            .arg(result.error())
                            .arg(result.errorString())
                            .arg(result ? "true" : "false")
                            .arg(hashString);
    ui->textEdit->append(strRet + "\n");
}


void Widget::on_pushButton_test_10_clicked()
{
    QRpcCall call;
    call.setModuleName("TestServiceTwo");
    call.setMethodName("testVariant1");
    QRpcResult<bool> result = _cli.invokeMethod(call, QVariant("123"));
    const QString invokeMethod = QString("invokeMethod \"bool testVariant1(QVariant)\":");
    ui->textEdit->append(invokeMethod);

    const QString strRet = QString("\tcall result: error:%1,errorString:%2---return result:%3")
                            .arg(result.error())
                            .arg(result.errorString())
                            .arg(result ? "true" : "false");
    ui->textEdit->append(strRet + "\n");
}


void Widget::on_pushButton_test_11_clicked()
{
    QRpcCall call;
    call.setModuleName("TestServiceTwo");
    call.setMethodName("testVariant2");

    QVariantMap map;
    map.insert("1", 1);
    map.insert("2", 2.02);
    map.insert("3", "string3");
    map.insert("4", QByteArray("4"));
    QRpcResult<bool> result = _cli.invokeMethod(call, map);
    const QString invokeMethod = QString("invokeMethod \"bool testVariant1(QVariantMap)\":");
    ui->textEdit->append(invokeMethod);

    const QString strRet = QString("\tcall result: error:%1,errorString:%2---return result:%3")
                            .arg(result.error())
                            .arg(result.errorString())
                            .arg(result ? "true" : "false");
    ui->textEdit->append(strRet + "\n");
}


void Widget::on_pushButton_test_12_clicked()
{
    QRpcCall call;
    call.setModuleName("TestServiceTwo");
    call.setMethodName("testVariant3");

    QVariantHash hash;
    hash.insert("1", 1);
    hash.insert("2", 2.02);
    hash.insert("3", "string3");
    hash.insert("4", QByteArray("4"));
    QRpcResult<bool> result = _cli.invokeMethod(call, hash);
    const QString invokeMethod = QString("invokeMethod \"bool testVariant3(QVariantHash)\":");
    ui->textEdit->append(invokeMethod);

    const QString strRet = QString("\tcall result: error:%1,errorString:%2---return result:%3")
                            .arg(result.error())
                            .arg(result.errorString())
                            .arg(result ? "true" : "false");
    ui->textEdit->append(strRet + "\n");
}


void Widget::on_pushButton_test_13_clicked()
{
    QRpcCall call;
    call.setModuleName("TestServiceTwo");
    call.setMethodName("testComplexVariant");


    QHash<QByteArray, QByteArray> hash;
    hash["123"] = QByteArray("321");

    // 使用QVariant存放一个复杂的类型(需要使用QVariant::fromValue赋值的类型)，需要手动注册该类型，同时服务器上也必须要手动注册该类型
    qRpcRegisterMetaType<QHash<QByteArray, QByteArray>>();
    QVariant v = QVariant::fromValue(hash);


    QRpcResult<bool> result = _cli.invokeMethod(call, v);
    const QString invokeMethod = QString("invokeMethod \"bool testComplexVariant(QVariant)\":");
    ui->textEdit->append(invokeMethod);

    const QString strRet = QString("\tcall result: error:%1,errorString:%2---return result:%3")
                            .arg(result.error())
                            .arg(result.errorString())
                            .arg(result ? "true" : "false");
    ui->textEdit->append(strRet + "\n");
}


void Widget::on_pushButton_clicked()
{
    QRpcCall call;
    call.setModuleName("TestService");
    call.setMethodName("testFun3");
    call.setInvokeMode(QRpcCall::ASYNC);
    call.setTimeout(3000);


    QRpcResult<int> result = _cli.invokeMethod(call, 100, 200);

    QRpcResultCallWatcher *watcher = new QRpcResultCallWatcher(result);
    connect(watcher, &QRpcResultCallWatcher::invokeFinished, this, [this, result, watcher]{

        const QString strRet = QString("invokeMethod \"int testFun3(int, int)\": call result: error:%1,errorString:%2---return result:%3")
                .arg(result.error())
                .arg(result.errorString())
                .arg(result);

        ui->textEdit->append(strRet + "\n");

        watcher->deleteLater();
    });
}

