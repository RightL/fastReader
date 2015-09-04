#ifndef READER_H
#define READER_H

#include <QWidget>
#include <QFont>
#include <QTimer>

namespace Ui {
class Reader;
}

class Reader : public QWidget
{
	Q_OBJECT

public:
	explicit Reader(QWidget *parent = 0);
	~Reader();

private slots:
	void timerUpdate();

	void on_setFont_clicked();

	void on_setSpeed_valueChanged(int arg1);

	void on_start_clicked();

	void on_openFile_clicked();

private:
	Ui::Reader *ui;
	QFont font;
	QTimer *timer;
	void startTimer();
	QString text;
	short int wordLocation;
};

#endif // READER_H
