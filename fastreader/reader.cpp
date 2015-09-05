#include "reader.h"
#include "ui_reader.h"
#include <QPalette>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QFileDialog>
#include <QDebug>

#define YYY 5
#define DEFAULT_SPEED 200

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
	connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
}

Reader::~Reader()
{
	delete ui;
}

void Reader::timerUpdate()
{
	switch (wordLocation) {
	case 0:
		label = ui->label;
		break;
	case 1:
		label = ui->label_2;
		break;
	case 2:
		label = ui->label_3;
		break;
	case 3:
		label = ui->label_4;
		break;
	default:
		return;
	}
	if (wordIndex >= wordLenth) {
		timer->stop();
		return;
	}
	if (wordIndex % YYY == 0) {
		label->setText("");
		if (wordLocation > 3)
			wordLocation = 0;
		else
			wordLocation++;
	}
	label->setText(text.at(wordIndex++));
}

void Reader::on_setFont_clicked()
{

}

void Reader::on_setSpeed_valueChanged(int arg1)
{

}

void Reader::on_start_clicked()
{
	if (text.isEmpty())
		return;
	startTimer(DEFAULT_SPEED);
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
