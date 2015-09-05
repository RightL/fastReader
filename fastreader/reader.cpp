#include "reader.h"
#include "ui_reader.h"
#include <QPalette>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QFileDialog>
#include <QDebug>
#include <QFontDialog>

#define YYY 200
#define DEFAULT_SPEED 500
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
//	ui->setSpeed->setValue();
	font.setPointSize(DEFAULT_FONT_SIZE);
	updateFont();
	connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
}

Reader::~Reader()
{
	delete ui;
}

void Reader::timerUpdate()
{
	if (wordIndex >= wordLenth) {
		timer->stop();
		return;
	}
	label = getLocation(wordLocation);
	if (wordIndex % YYY == 0) {
		label->setText("");
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
}

void Reader::on_setSpeed_valueChanged(int arg1)
{
	speed = arg1;
	if (timer->isActive())
		startTimer(speed);
}

void Reader::on_start_clicked()
{
	if (text.isEmpty())
		return;
	startTimer(speed);
	timerUpdate();
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
}
