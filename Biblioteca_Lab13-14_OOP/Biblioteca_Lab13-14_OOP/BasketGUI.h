#pragma once
#include <QtWidgets/QApplication>
#include <QWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QWidget>
#include <QListWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QFormLayout>
#include "biblioteca.h"
#include <QMessageBox>
#include <string>
#include <set>
#include <vector>
#include <QDebug>
#include <QPainter>
#include <cstdlib>
#include "Observer.h"
using std::to_string;
using std::set;
using std::vector;

class BasketGUI : public QWidget, public Observer {
private:
	Biblioteca& srv;
	QHBoxLayout* lyMain;
	QListWidget* listBooks; //!!!!!!!!!!!!!!!!!!!!!!!!

	QLabel* lblTitlu;
	QLabel* lblAutor;
	QLabel* lblFisier;
	QLineEdit* editTitlu;
	QLineEdit* editAutor;
	QLineEdit* editFisier;
	QLineEdit* editHowManyRandom;

	QPushButton* btnAdd;
	QPushButton* btnGenerate;
	QPushButton* btnEmpty;
	QPushButton* btnExport;
	QPushButton* btnClose;
	QPushButton* btnLabelWindow;
	QPushButton* btnTableWindow;
	QPushButton* btnDrawWindow;
	QPushButton* btnAddRandom;


	QLineEdit* editNoSlider;
	QLabel* lblSlider;
	QSlider* sliderGenerate;

	QWidget* widgetDynamic;
	QVBoxLayout* lyBtnDynamic;
	void initGUI();
	void connectSignalsSlots();

	void reloadBasket();
	void addToBasket();

	//ar trebui ca aceasta metoda sa fie aici sau in service?
	set<string> getGenres(const vector<Carte>& basketBooks);
	//void reloadDynamicButtons();
	void update() override {
		reloadBasket();
	}

public:
	BasketGUI(Biblioteca& bookStore) : srv{ bookStore } {
		initGUI();
		connectSignalsSlots();
	}

};
class BasketGUILabel :public QWidget, public Observer {
private:
	Basket& b;
	QLabel* lblNoBooks;
	QLineEdit* editNoBooks;
	void initGUI() {
		QHBoxLayout* ly = new QHBoxLayout{};
		this->setLayout(ly);
		lblNoBooks = new QLabel{ "Numar de carti:" };
		editNoBooks = new QLineEdit{};
		ly->addWidget(lblNoBooks);
		ly->addWidget(editNoBooks);
		setAttribute(Qt::WA_DeleteOnClose);
		b.addObserver(this);
	};
	void update() override {
		this->editNoBooks->setText(QString::number((int)b.getAllBooksFromBasket().size()));
	};
	~BasketGUILabel() {
		b.removeObserver(this);
	}

public:
	BasketGUILabel(Basket& basket) :b{ basket } {
		initGUI();
	};

};
class BasketGUITable :public QWidget, public Observer {
private:
	Basket& b;
	const vector<Carte>& allfromsrv;
	//Biblioteca& srv;
	QTableWidget* table;
	QPushButton* btnEmpty;
	QLabel* lblHowMany;
	QPushButton* btnGenereaza;
	QLineEdit* editHowMany;
	void initGUI() {
		QHBoxLayout* ly = new QHBoxLayout{};
		this->setLayout(ly);
		table = new QTableWidget{};
		lblHowMany = new QLabel{ "Nr carti de generat random:" };
		editHowMany = new QLineEdit{};
		btnGenereaza = new QPushButton{ "Genereaza random" };
		ly->addWidget(lblHowMany);
		ly->addWidget(editHowMany);
		ly->addWidget(btnGenereaza);
		btnEmpty = new QPushButton{ "Goleste cos" };
		ly->addWidget(table);
		ly->addWidget(btnEmpty);
		setAttribute(Qt::WA_DeleteOnClose);
		b.addObserver(this);
	};
	void reloadTableData(const vector<Carte>& books) {
		this->table->setColumnCount(4);
		this->table->setRowCount(static_cast<int>(books.size()));
		for (int i = 0; i < books.size(); i++) {
			table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(books[i].getTitlu())));
			table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(books[i].getAutor())));
			table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(books[i].getGen())));
			table->setItem(i, 3, new QTableWidgetItem(QString::number(books[i].getAn())));
		}

	};

	void connectSignalsSlots() {
		b.addObserver(this);

		QObject::connect(btnEmpty, &QPushButton::clicked, [&]() {
			b.emptyBasket();
			//srv.emptyBasket();
			reloadTableData(b.getAllBooksFromBasket());
			//reloadTableData(srv.getBasketBooks());
			});

		QObject::connect(btnGenereaza, &QPushButton::clicked, [&]() {
			int noBooks = this->editHowMany->text().toInt();
			//QMessageBox::information(this, "Info", QString::number(noBooks));
			qDebug() << "This many books to add:" << noBooks;
			b.emptyBasket();
			b.addRandomBooks(allfromsrv, noBooks);
			//srv.addRandomToBasket(noBooks);
			reloadTableData(b.getAllBooksFromBasket());
			//reloadTableData(srv.getBasketBooks());
			});
	}

public:
	BasketGUITable(Basket& basket, const vector<Carte>& allfromsrv) : b{ basket }, allfromsrv{ allfromsrv } {
		//BasketGUITable(Biblioteca& srv) : srv{ srv } {
		initGUI();
		connectSignalsSlots();
	};

	void update() override {
		this->reloadTableData(b.getAllBooksFromBasket());
		//this->reloadTableData(srv.getBasketBooks());
	}
	~BasketGUITable() {
		b.removeObserver(this);
	}
};

class BasketGUIDraw :public QWidget, public Observer {
private:
	Basket& basket;
	void paintEvent(QPaintEvent*) override {
		QPainter p{ this };
		int x = 0;
		int y = 0;
		for (auto carte : basket.getAllBooksFromBasket()) {
			//p.drawRect(x, y, 10, song.getDurata() * 10);
			x = rand() % 400 + 1;
			y = rand() % 400 + 1;
			qDebug() << x << " " << y;
			QRectF target(x, y, 100, 94);
			QRectF source(0, 0, 732, 720);
			QImage image("book1.jpg");

			p.drawImage(target, image, source);

			x += 40;

		}
	}

	void update() override {
		repaint();
	};
	~BasketGUIDraw() {
		basket.removeObserver(this);
	}

public:
	BasketGUIDraw(Basket& basket) :basket{ basket } {
		basket.addObserver(this);
	};

};
