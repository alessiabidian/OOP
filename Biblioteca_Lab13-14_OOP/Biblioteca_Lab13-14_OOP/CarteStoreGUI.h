#pragma once
#include <vector>
#include <string>
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableWidget>
#include <QListWidget>
#include <QMessageBox>
#include <QHeaderView>
#include <QGroupBox>
#include <QRadioButton>
#include "biblioteca.h"
#include "BasketGUI.h"

using std::vector;
using std::string;
class CarteStoreGUI : public QWidget {
private:

	Biblioteca& srv;
	BasketGUI basketWindow{ srv };
	QPushButton* btnBasket;

	QLabel* lblTitlu = new QLabel{ "Titlu carte:" };
	QLabel* lblAutor = new QLabel{ "Autor carte:" };
	QLabel* lblGen = new QLabel{ "Gen carte:" };
	QLabel* lblAn = new QLabel{ "An publicatie carte:" };

	QLabel* lblNewTitlu = new QLabel{ "Titlu carte:" };
	QLabel* lblNewAutor = new QLabel{ "Autor carte:" };
	QLabel* lblNewGen = new QLabel{ "Gen carte:" };
	QLabel* lblNewAn = new QLabel{ "An publicatie carte:" };
	QLabel* lblPozitie = new QLabel{ "Pozitia cartii de modificat cu datele noi:" };

	QLabel* lblCautaTitlu = new QLabel{ "Titlu carte:" };
	QLabel* lblCautaAutor = new QLabel{ "Autor carte:" };

	QLineEdit* editTitlu;
	QLineEdit* editAutor;
	QLineEdit* editGen;
	QLineEdit* editAn;

	QLineEdit* editNewTitlu;
	QLineEdit* editNewAutor;
	QLineEdit* editNewGen;
	QLineEdit* editNewAn;
	QLineEdit* editPozitie;

	QPushButton* btnAddCarte;

	QGroupBox* groupBox = new QGroupBox(tr("Tip sortare"));

	QRadioButton* radioSrtAnGen = new QRadioButton(QString::fromStdString("An+Gen"));
	QRadioButton* radioSrtTitlu = new QRadioButton(QString::fromStdString("Titlu"));
	QRadioButton* radioSrtAutor = new QRadioButton(QString::fromStdString("Autor"));
	QPushButton* btnSortBooks;

	QLabel* lblFilterCriteria = new QLabel{ "Titlul/Anul dupa care se filtreaza:" };
	QLineEdit* editFilter;
	QPushButton* btnFilterBooks;

	//eu
	QPushButton* btnModify;
	QPushButton* btnSearch;

	QLineEdit* editCautaTitlu;
	QLineEdit* editCautaAutor;

	QLabel* lblExportFile = new QLabel{ "Fisierul de export este:" };

	QLineEdit* editTitluBasket;
	QLineEdit* editAutorBasket;
	QLineEdit* editExportFile;

	QPushButton* btnExport;
	QPushButton* btnFilterBooks2;

	QGroupBox* groupBox2 = new QGroupBox(tr("Stergere dupa pozitie"));
	QLabel* lblDelete = new QLabel{ "Pozitia cartii de sters sau nr k care sa divida anii:" };
	QLineEdit* editDelete;
	QPushButton* btnDeleteCarte;
	QPushButton* btnRemoveIf;
	QPushButton* btnNewWindow;

	QLabel* lblHowMany = new QLabel{ "Introduceti cate carti sa se adauge random in cos:" };
	QLineEdit* editHowMany;
	QPushButton* btnAddRandom;
	QPushButton* btnEmptyBasket;
	QPushButton* btnAddCarteBasket;

	QPushButton* btnLeft;
	QPushButton* btnRight;

	QWidget* window2;
	QWidget* windowCauta;
	QWidget* windowModifica;
	//eu

	QPushButton* btnReloadData;

	QPushButton* btnUndoLast;

	QPushButton* btnTest;

	QTableWidget* tableBooks;
	QTableWidget* tableBooks2;
	QListWidget* listBooks;

	vector<QPushButton*> vectorButtons;
	QWidget* listButtons;
	QVBoxLayout* lyListButtons;

	QPushButton* buttons[2];
	QPushButton* btnCauta;
	QPushButton* btnModifica;
	QGroupBox* horizontalGroupBox;

	void initializeGUIComponents();

	void connectSignalsSlots();
	void reloadCarteList(vector<Carte> books);
	void reloadBasketList(vector<Carte> books);
	void reloadBasketList2();

	void guiAddButtonsDinamic(string newgen);
	void guiDeleteButtonsDinamic(string newgen);
	void guiInitializareButoane();
	//void guiWindow2();
	void guiWindowModifica();
	void guiWindowCauta();

	void createHorizontalGroupBox();

public:
	CarteStoreGUI(Biblioteca& carteSrv) : srv{ carteSrv } {
		initializeGUIComponents();
		connectSignalsSlots();
		reloadCarteList(srv.getAll());
		guiInitializareButoane();
	}
	void guiAddCarte();
	void guiAddCarteBasket();

};
