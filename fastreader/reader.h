#ifndef READER_H
#define READER_H

#include <QWidget>
#include <QFont>
#include <QTimer>
#include <QLabel>
#include <QEvent>
#include <QKeyEvent>


namespace Ui {
class Reader;
}

class Reader : public QWidget
{
	Q_OBJECT

public:
	explicit Reader(QWidget *parent = 0);
	~Reader();

protected:
    bool eventFilter(QObject *object, QEvent *event);

private slots:
	void timerUpdate();

	void on_setFont_clicked();

	void on_setSpeed_valueChanged(int arg1);

	void on_start_clicked();

	void on_openFile_clicked();

	void on_stop_clicked();

	void on_bgColor_clicked();

	void on_fontColor_clicked();

private:
	Ui::Reader *ui;
	QFont font;
	QTimer *timer;
	void goBack();
	void handleKeyPressed(QKeyEvent *event);
	void startTimer(int speed);
	QString text;
	QLabel *label;
	int speed;
	QLabel *getLocation(short locationIndex);
	long long int wordLenth;
	long long int wordIndex;
	short wordLocation;
	void updateFont();
};

#endif // READER_H
