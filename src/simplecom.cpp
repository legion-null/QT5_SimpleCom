#include "simplecom.h"

#include "ui_simplecom.h"

SimpleCom::SimpleCom(QWidget *parent) :
		QMainWindow(parent), m_ui(new Ui::SimpleCom) {
	m_ui->setupUi(this);

	initComs();
	initBps();
	initCheckBit();
	initDataBit();
	initStopBit();

	connectAll();
}

SimpleCom::~SimpleCom() = default;

void SimpleCom::initComs() {
	qDebug() << "初始化可用串口列表" << Qt::endl;

	foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
{	m_ui->comboBox_com->addItem(info.portName());
}
}

void SimpleCom::initBps() {
	QStringList bps = { "2400", "4800", "9600", "14400", "19200", "38400", "57600", "76800", "115200", "128000", "230400",
			"256000", "460800" };
	for (int i = 0; i < bps.length(); i++) {
		m_ui->comboBox_bps->addItem(bps[i], bps[i].toInt());
	}
}

void SimpleCom::initCheckBit() {
	m_ui->comboBox_checkBit->addItem("无 None", QSerialPort::NoParity);
	m_ui->comboBox_checkBit->addItem("奇 Odd", QSerialPort::OddParity);
	m_ui->comboBox_checkBit->addItem("偶 Even", QSerialPort::EvenParity);
	m_ui->comboBox_checkBit->addItem("零 Space", QSerialPort::SpaceParity);
	m_ui->comboBox_checkBit->addItem("一 Mark", QSerialPort::MarkParity);
}

void SimpleCom::initDataBit() {
	m_ui->comboBox_dataBit->addItem("8", QSerialPort::Data8);
	m_ui->comboBox_dataBit->addItem("7", QSerialPort::Data7);
	m_ui->comboBox_dataBit->addItem("6", QSerialPort::Data6);
	m_ui->comboBox_dataBit->addItem("5", QSerialPort::Data5);
}

void SimpleCom::initStopBit() {
	m_ui->comboBox_stopBit->addItem("1", QSerialPort::OneStop);
	m_ui->comboBox_stopBit->addItem("1.5", QSerialPort::OneAndHalfStop);
	m_ui->comboBox_stopBit->addItem("2", QSerialPort::TwoStop);
}

bool SimpleCom::connectCom() {
	// 关闭串口
	com.close();

	// 设置串口
	com.setPortName(m_ui->comboBox_com->currentText());
	// 设置波特率
	com.setBaudRate(m_ui->comboBox_bps->currentData().toInt());
	// 设置校验位
	com.setParity((QSerialPort::Parity) (m_ui->comboBox_checkBit->currentData().toInt()));
	// 设置数据位
	com.setDataBits((QSerialPort::DataBits) (m_ui->comboBox_dataBit->currentData().toInt()));
	// 设置停止位
	com.setStopBits((QSerialPort::StopBits) (m_ui->comboBox_stopBit->currentData().toInt()));

	// 连接
	return com.open(QIODevice::ReadWrite);
}

void SimpleCom::closeCom() {
	com.close();
}

void SimpleCom::sendMessage() {
	if (com.isOpen() == false)
		return;

	QString temp = m_ui->plainTextEdit_send->toPlainText();

	m_ui->plainTextEdit_receive->appendPlainText(
			"[LocalMachine] " + QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss.zzz"));
	m_ui->plainTextEdit_receive->appendPlainText(temp);

	com.write(temp.toLatin1());
}

void SimpleCom::receiveMessage() {
	if (com.isOpen() == false)
		return;

	QByteArray temp = com.readAll();

	if (temp.isEmpty() == true)
		return;

	m_ui->plainTextEdit_receive->appendPlainText(
			"[" + com.portName() + "] " + QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss.zzz"));
	m_ui->plainTextEdit_receive->appendPlainText(QString::fromLatin1(temp));
}

void SimpleCom::connectAll() {
	// 打开关闭串口按钮
	connect(m_ui->pushButton_com, &QPushButton::clicked, this, &SimpleCom::onPushButtonCom);
	// 发送按钮
	connect(m_ui->pushButton_send, &QPushButton::clicked, this, &SimpleCom::onPushButtonSend);
	// 清空按钮
	connect(m_ui->pushButton_clear, &QPushButton::clicked, this, &SimpleCom::onPushButtonClear);

	// 接收定时器
	tim.setInterval(100);
	connect(&tim, &QTimer::timeout, this, &SimpleCom::receiveThread);
	tim.start();
}

void SimpleCom::onPushButtonCom() {
	if (com.isOpen() == false) {
		m_ui->pushButton_com->setText(connectCom() ? "关闭串口" : "打开串口");
	} else {
		closeCom();
		m_ui->pushButton_com->setText("打开串口");
	}
}

void SimpleCom::onPushButtonSend() {
	sendMessage();
}

void SimpleCom::onPushButtonClear() {
	m_ui->plainTextEdit_receive->setPlainText("");
}

void SimpleCom::receiveThread() {
	receiveMessage();
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on;
