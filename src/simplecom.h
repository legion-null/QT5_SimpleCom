#ifndef SAMPLECOM_H
#define SAMPLECOM_H

#include <QMainWindow>
#include <QScopedPointer>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <QtCore/QDateTime>

#include <QTimer>

#include <QDebug>

namespace Ui {
class SimpleCom;
}

class SimpleCom: public QMainWindow {
	Q_OBJECT

public:
	explicit SimpleCom(QWidget *parent = nullptr);
	~SimpleCom() override;

private:
	QScopedPointer<Ui::SimpleCom> m_ui;
	QSerialPort com;
	QTimer tim;

private:
	void initComs();
	void initBps();
	void initCheckBit();
	void initDataBit();
	void initStopBit();

	bool connectCom();
	void closeCom();

	void sendMessage();
	void receiveMessage();

private:
	void connectAll();

private slots:
	void onPushButtonCom();
	void onPushButtonSend();
	void onPushButtonClear();

	void receiveThread();
};

#endif // SAMPLECOM_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on;
