#include "reader.h"
#include "ui_reader.h"
#include <QPalette>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QFileDialog>
#include <QDebug>

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
}

Reader::~Reader()
{
	delete ui;
}

void Reader::timerUpdate()
{

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
	startTimer();
}

void Reader::on_openFile_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("txt(*.txt)"));
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	QTextStream in(&file);
	if (text.isEmpty())
		text.clear();
	while (!in.atEnd())
		text.append(in.readAll());
	qDebug() << text;
}

void Reader::startTimer()
{

}
