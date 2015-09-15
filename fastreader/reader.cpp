#include "reader.h"
#include "ui_reader.h"
#include <QPalette>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QFileDialog>
#include <QDebug>
#include <QColor>
#include <QColorDialog>
#include <QFontDialog>

#define YYY 100
#define DEFAULT_SPEED 200
#define DEFAULT_FONT_SIZE 20

Reader::Reader(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Reader)
{
	ui->setupUi(this);
	QPalette p = this->palette();
	p.setColor(QPalette::Window, Qt::darkGray);
	this->setPalette(p);
	timer = new QTimer(this);
	wordLocation = 0;
	wordIndex = 0;
	speed = DEFAULT_SPEED;
	font.setPointSize(DEFAULT_FONT_SIZE);
	updateFont();
	connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
	ui->setSpeed->setValue(DEFAULT_SPEED);
	this->installEventFilter(this);
	this->setFocus();

}

Reader::~Reader()
{
	delete ui;
}

bool Reader::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
	handleKeyPressed((QKeyEvent *)event);
	return true;
    } else {
	return QObject::eventFilter(object, event);
    }
}

void Reader::handleKeyPressed(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Space:
	    if (timer->isActive()) {
		    timer->stop();
	    } else {
		    on_start_clicked();
	    }
	break;
    case Qt::Key_Left:
	     goBack();
	break;
    case Qt::Key_Up:
	    ui->setSpeed->setValue(ui->setSpeed->value() + 1);
	break;
    case Qt::Key_Down:
	    ui->setSpeed->setValue(ui->setSpeed->value() - 1);
	break;
    default:
	break;
    }
}

void Reader::timerUpdate()
{
	if (wordIndex >= wordLenth) {
		timer->stop();
		return;
	}
	label = getLocation(wordLocation);
	if (wordIndex % YYY == 0) {
		label->setText("@");
		++wordLocation;
		if (wordLocation > 3)
			wordLocation = 0;
		label = getLocation(wordLocation);

	}
	label->setText(text.at(wordIndex++));
}

void Reader::on_setFont_clicked()
{
	bool ok;
	font = QFontDialog::getFont(&ok, this);
	if (ok)
		updateFont();
	this->setFocus();


}

void Reader::on_setSpeed_valueChanged(int arg1)
{
	speed = arg1;
	if (timer->isActive())
		startTimer(speed);
	this->setFocus();
}

void Reader::on_start_clicked()
{
	if (text.isEmpty())
		return;
	startTimer(speed);
	timerUpdate();
	this->setFocus();
}

void Reader::on_openFile_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("txt(*.txt)"));
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	QTextStream in(&file);
	if (text.isEmpty()) {
		text.clear();
		wordIndex = 0;
	}
	while (!in.atEnd())
		text.append(in.readAll());
	file.close();
	wordLenth = text.size();
	this->setFocus();
}

void Reader::startTimer(int speed)
{
	timer->start(speed);
}

QLabel *Reader::getLocation(short locationIndex)
{
	switch (locationIndex) {
	case 0:
		return ui->label;
	case 1:
		return ui->label_2;
	case 2:
		return ui->label_3;
	case 3:
		return ui->label_4;
	default:
		return NULL;
	}
}

void Reader::updateFont()
{
	ui->label_4->setFont(font);
	ui->label_2->setFont(font);
	ui->label_3->setFont(font);
	ui->label->setFont(font);
}

void Reader::on_stop_clicked()
{
    timer->stop();
    this->setFocus();
}

void Reader::on_bgColor_clicked()
{
	QPalette p = this->palette();
	p.setColor(QPalette::Window,
		   QColorDialog::getColor(Qt::black, this, tr("Choose a color")));
	this->setPalette(p);
	this->setFocus();
}

void Reader::on_fontColor_clicked()
{
	QPalette p;
	p.setColor(QPalette::WindowText,
		   QColorDialog::getColor(Qt::black, this, tr("Choose a color")));
	ui->label_4->setPalette(p);
	ui->label_2->setPalette(p);
	ui->label_3->setPalette(p);
	ui->label->setPalette(p);
	this->setFocus();
}

void Reader::goBack()
{
//	timer->stop();
	if (wordIndex > 1)
		wordIndex--;
//	timer->start();
}
