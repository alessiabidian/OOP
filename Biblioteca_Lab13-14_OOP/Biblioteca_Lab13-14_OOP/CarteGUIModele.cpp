#include "CarteGUIModele.h"
#include "carte.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <string>
#include "MyListModel.h"
#include "MyTableModel.h"
void CarteStoreGUIModele::initializeGUIComponents() {
	//main layout
	QHBoxLayout* lyMain = new QHBoxLayout;
	this->setLayout(lyMain);

	//left part of the window ------------------------------------------------------------------------------------------------
	//pentru aceasta parte setam layout vertical
	QWidget* left = new QWidget;
	QVBoxLayout* lyLeft = new QVBoxLayout;
	left->setLayout(lyLeft);

	//componente pentru functionalitatea de adaugare a unei carti
	//folosim un QFormLayout pentru detaliile de adaugare a unei carti
	QWidget* form = new QWidget;
	QFormLayout* lyForm = new QFormLayout;
	form->setLayout(lyForm);
	editTitlu = new QLineEdit;
	editAutor = new QLineEdit;
	editGen = new QLineEdit;
	editAn = new QLineEdit;

	lyForm->addRow(lblTitlu, editTitlu);
	lyForm->addRow(lblAutor, editAutor);
	lyForm->addRow(lblGen, editGen);
	lyForm->addRow(lblAn, editAn);
	btnAddCarte = new QPushButton("Adauga carte");
	lyForm->addWidget(btnAddCarte);

	//adaugam toate componentele legate de adaugare carte
	//in layout-ul care corespunde partii din stanga a ferestrei
	lyLeft->addWidget(form);

	QVBoxLayout* lyRadioBox = new QVBoxLayout;
	this->groupBox->setLayout(lyRadioBox);
	lyRadioBox->addWidget(radioSrtAnGen);
	lyRadioBox->addWidget(radioSrtTitlu);
	lyRadioBox->addWidget(radioSrtAutor);

	btnSortBooks = new QPushButton("Sorteaza carti");
	lyRadioBox->addWidget(btnSortBooks);

	//adaugam acest grup in partea stanga, 
	//dupa componentele pentru adaugare in layout-ul vertical
	lyLeft->addWidget(groupBox);

	//cream un form pentru filtrarea dupa titlu 
	QWidget* formFilter = new QWidget;
	QFormLayout* lyFormFilter = new QFormLayout;
	formFilter->setLayout(lyFormFilter);
	editFilter = new QLineEdit();
	lyFormFilter->addRow(lblFilterCriteria, editFilter);
	btnFilterBooks = new QPushButton("Filtreaza carti dupa titlu");
	lyFormFilter->addWidget(btnFilterBooks);
	btnFilterBooks2 = new QPushButton("Filtreaza carti dupa an");
	lyFormFilter->addWidget(btnFilterBooks2);

	lyLeft->addWidget(formFilter);

	//eu
	//cream un form pentru stergerea dupa pozitie 
	QWidget* formDelete = new QWidget;
	QFormLayout* lyFormDelete = new QFormLayout;
	formDelete->setLayout(lyFormDelete);
	editDelete = new QLineEdit();
	lyFormDelete->addRow(lblDelete, editDelete);
	btnDeleteCarte = new QPushButton("Sterge Carte");
	lyFormDelete->addWidget(btnDeleteCarte);
	btnRemoveIf = new QPushButton("Sterge Daca An Nu Div");
	lyFormDelete->addWidget(btnRemoveIf);
	lyLeft->addWidget(formDelete);
	//eu

	horizontalGroupBox = new QGroupBox(tr("Cauta sau Modifica"));
	QHBoxLayout* layout = new QHBoxLayout;

	btnCauta = new QPushButton(tr("Buton Cauta"));
	layout->addWidget(btnCauta);
	btnModifica = new QPushButton(tr("Buton Modifica"));
	layout->addWidget(btnModifica);

	horizontalGroupBox->setLayout(layout);
	lyLeft->addWidget(horizontalGroupBox);

	//eu
	//Buton folosit pentru UNDO
	//i.e. afisam cartile in tabel, inaintea ultimei operatii
	btnUndoLast = new QPushButton("Undo");
	btnUndoLast->setStyleSheet("background-color: #7cfcde; color: red; font-weight: bold;");
	lyLeft->addWidget(btnUndoLast);
	//eu

	//Buton folosit pentru a reincarca datele
	//i.e. afisam toate cartile in tabel, in ordinea initiala din fisier
	btnReloadData = new QPushButton("Reload data");
	lyLeft->addWidget(btnReloadData);

	/*btnNewWindow = new QPushButton("Fereastra Cos");
	lyLeft->addWidget(btnNewWindow);*/

	btnBasket = new QPushButton{ "Open basket" };
	lyLeft->addWidget(btnBasket);

	//componenta right - contine doar tabelul cu carti ----------------------------------------------------------------
	QWidget* right = new QWidget;
	QVBoxLayout* lyRight = new QVBoxLayout;
	right->setLayout(lyRight);

	//!!!!!!!!!!
	lstV = new QListView;
	lstV->setUniformItemSizes(true);
	lyRight->addWidget(lstV);
	//!!!!!!!!!!
	lyRight->addWidget(tblV);

	listButtons = new QWidget;
	lyListButtons = new QVBoxLayout;
	listButtons->setLayout(lyListButtons);
	
	lyMain->addWidget(left);
	lyMain->addWidget(right);
	lyMain->addWidget(listButtons);
}


void CarteStoreGUIModele::connectSignalsSlots() {
	QObject::connect(btnAddCarte, &QPushButton::clicked, this, &CarteStoreGUIModele::guiAddCarte);

	QObject::connect(btnSortBooks, &QPushButton::clicked, [&]() {
		if (this->radioSrtAnGen->isChecked())
			this->reloadList(srv.sortByGenAn());
		else if (this->radioSrtTitlu->isChecked())
			this->reloadList(srv.sortByTitlu());
		else if (this->radioSrtAutor->isChecked())
			this->reloadList(srv.sortByAutor());
		this->an = 2000;
		});

	QObject::connect(btnFilterBooks, &QPushButton::clicked, [&]() {
		string filterC = this->editFilter->text().toStdString();
		this->reloadList(srv.filtrareTitlu(filterC));
		});

	QObject::connect(btnFilterBooks2, &QPushButton::clicked, [&]() {
		int filterC = this->editFilter->text().toInt();
		this->reloadList(srv.filtrareAnMaiMic(filterC));
		});

	QObject::connect(btnCauta, &QPushButton::clicked, this, &CarteStoreGUIModele::guiWindowCauta);
	QObject::connect(btnModifica, &QPushButton::clicked, this, &CarteStoreGUIModele::guiWindowModifica);

	//eu
	QObject::connect(btnDeleteCarte, &QPushButton::clicked, [&]() {
		try {
			int pozitie = this->editDelete->text().toInt();
			Carte c = srv.getAll().at(pozitie - 1);
			srv.deleteCarte(pozitie);
			this->guiDeleteButtonsDinamic(c.getGen());
			this->reloadList(srv.getAll());
		}
		catch (CarteRepoException& re) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
		}
		});

	QObject::connect(btnRemoveIf, &QPushButton::clicked, [&]() {
		try {
			int criteriu = this->editDelete->text().toInt();
			srv.delete_daca(criteriu);
			//this->guiDeleteButtonsDinamic(c.getGen());
			this->reloadList(srv.getAll());
		}
		catch (CarteRepoException& re) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
		}
		});
	//eu

	QObject::connect(btnReloadData, &QPushButton::clicked, [&]() {
		this->reloadList(srv.getAll());
		});

	QObject::connect(btnUndoLast, &QPushButton::clicked, [&]() {
		try {
			int init_size = int(srv.getAll().size());
			Carte c_init = srv.getAll()[init_size - 1];

			srv.undo();

			int current_size = int(srv.getAll().size());
			Carte c_current = srv.getAll()[current_size - 1];

			if (current_size < init_size)
			{
				this->guiDeleteButtonsDinamic(c_init.getGen());
			}
			else if (current_size > init_size)
			{
				this->guiAddButtonsDinamic(c_current.getGen());  //adaug butonu inapoi daca o fost sters
			}
			else {
				this->guiDeleteButtonsDinamic(c_init.getGen());
				this->guiAddButtonsDinamic(c_current.getGen());  //adaug butonu inapoi daca o fost modificat
			}
		}
		catch (CarteRepoException& re) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
		}
		this->reloadList(srv.getAll());
		});

	//QObject::connect(btnNewWindow, &QPushButton::clicked, this, &CarteStoreGUI::guiWindow2);

	QObject::connect(btnBasket, &QPushButton::clicked, [&]() {

		basketWindow.show();
		});
	//selectia in tabel
	QObject::connect(tblV->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		if (tblV->selectionModel()->selectedIndexes().isEmpty()) {
			editTitlu->setText("");
			editAutor->setText("");
			editGen->setText("");
			editAn->setText("");
			return;
		}
		int selRow = tblV->selectionModel()->selectedIndexes().at(0).row();
		auto cel0Index = tblV->model()->index(selRow, 0);
		auto cel0Value = tblV->model()->data(cel0Index, Qt::DisplayRole).toString();
		editTitlu->setText(cel0Value);
		auto cel1Index = tblV->model()->index(selRow, 1);
		auto cel1Value = tblV->model()->data(cel1Index, Qt::DisplayRole).toString();
		editAutor->setText(cel1Value);
		auto cel2Index = tblV->model()->index(selRow, 2);
		auto cel2Value = tblV->model()->data(cel2Index, Qt::DisplayRole).toString();
		editGen->setText(cel2Value);
		auto cel3Index = tblV->model()->index(selRow, 3);
		auto cel3Value = tblV->model()->data(cel3Index, Qt::DisplayRole).toString();
		editAn->setText(cel3Value);
		});
}

void CarteStoreGUIModele::guiWindowCauta()
{
	windowCauta = new QWidget;

	QVBoxLayout* ly = new QVBoxLayout;
	windowCauta->setLayout(ly);

	QWidget* form = new QWidget;
	QFormLayout* lyForm = new QFormLayout;
	form->setLayout(lyForm);
	editCautaTitlu = new QLineEdit;
	editCautaAutor = new QLineEdit;

	lyForm->addRow(lblCautaTitlu, editCautaTitlu);
	lyForm->addRow(lblCautaAutor, editCautaAutor);

	btnSearch = new QPushButton("Cauta carte");
	lyForm->addWidget(btnSearch);

	ly->addWidget(form);

	QObject::connect(btnSearch, &QPushButton::clicked, [&]() {
		try {
			//preluare detalii din QLineEdit-uri
			string titlu = editCautaTitlu->text().toStdString();
			string autor = editCautaAutor->text().toStdString();

			//optional - golim QLineEdit-urile dupa apasarea butonului
			editCautaTitlu->clear();
			editCautaAutor->clear();

			const Carte carte = this->srv.cautare(titlu, autor);

			this->tableBooks->clearContents();
			this->tableBooks->setRowCount(int(1));

			int lineNumber = 0;
			this->tableBooks->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(carte.getTitlu())));
			this->tableBooks->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(carte.getAutor())));
			this->tableBooks->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(carte.getGen())));
			this->tableBooks->setItem(lineNumber, 3, new QTableWidgetItem(QString::number(carte.getAn())));

			//afisam un mesaj pentru a anunta utilizatorul ca s-a adaugat cartea
			QMessageBox::information(this, "Info", QString::fromStdString("Carte gasita cu succes."));

		}
		catch (CarteRepoException& re) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
		}
		catch (ValidateException& ve) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMessages()));
		}
		});

	QHBoxLayout* lyMainCauta = new QHBoxLayout;
	windowCauta->setLayout(lyMainCauta);

	windowCauta->show();
}

void CarteStoreGUIModele::guiWindowModifica()
{
	windowModifica = new QWidget;

	QVBoxLayout* ly = new QVBoxLayout;
	windowModifica->setLayout(ly);

	QWidget* form = new QWidget;
	QFormLayout* lyForm = new QFormLayout;
	form->setLayout(lyForm);
	editNewTitlu = new QLineEdit;
	editNewAutor = new QLineEdit;
	editNewGen = new QLineEdit;
	editNewAn = new QLineEdit;
	editPozitie = new QLineEdit;

	lyForm->addRow(lblNewTitlu, editNewTitlu);
	lyForm->addRow(lblNewAutor, editNewAutor);
	lyForm->addRow(lblNewGen, editNewGen);
	lyForm->addRow(lblNewAn, editNewAn);
	lyForm->addRow(lblPozitie, editPozitie);

	btnModify = new QPushButton("Modifica carte");
	lyForm->addWidget(btnModify);

	QObject::connect(btnModify, &QPushButton::clicked, [&]() {
		try {
			//preluare detalii din QLineEdit-uri
			string titlu = editNewTitlu->text().toStdString();
			string autor = editNewAutor->text().toStdString();
			string gen = editNewGen->text().toStdString();
			int an = editNewAn->text().toInt();
			int pos = editPozitie->text().toInt();

			//optional - golim QLineEdit-urile dupa apasarea butonului
			editNewTitlu->clear();
			editNewAutor->clear();
			editNewGen->clear();
			editNewAn->clear();
			editPozitie->clear();

			Carte c = srv.getAll()[pos - 1];
			this->srv.modifyCarte(titlu, autor, gen, an, pos);
			this->reloadList(this->srv.getAll());

			this->guiAddButtonsDinamic(gen);
			this->guiDeleteButtonsDinamic(c.getGen());

			//afisam un mesaj pentru a anunta utilizatorul ca s-a adaugat cartea
			QMessageBox::information(this, "Info", QString::fromStdString("Carte modificata cu succes."));

		}
		catch (CarteRepoException& re) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
		}
		catch (ValidateException& ve) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMessages()));
		}
		});

	//adaugam toate componentele legate de adaugare carte
	//in layout-ul care corespunde partii din stanga a ferestrei
	ly->addWidget(form);

	QHBoxLayout* lyMainModifica = new QHBoxLayout;
	windowModifica->setLayout(lyMainModifica);

	windowModifica->show();
}

void CarteStoreGUIModele::guiAddButtonsDinamic(string newgen)
{
	int gasit = 0;
	for (const auto& it : vectorButtons)
		if ((*it).text().toStdString() == newgen)
			gasit = 1;

	if (gasit == 0)
	{
		QPushButton* newbtn = new QPushButton;
		newbtn->setText(QString::fromStdString(newgen));
		lyListButtons->addWidget(newbtn);
		vectorButtons.push_back(newbtn);

		QObject::connect(newbtn, &QPushButton::clicked, this, [=]() {
			int howmany = int(srv.filtrareGen(newgen).size());
			QMessageBox::information(this, "Nr carti", QString::number(howmany));
			});
	}
}

void CarteStoreGUIModele::guiDeleteButtonsDinamic(string gen)
{
	int cont = 0;
	if (srv.filtrareGen(gen).size() == 0)
	{
		for (auto& button : vectorButtons)
		{
			if (button->text().toStdString() == gen)
			{
				delete button;
				vectorButtons.erase(vectorButtons.begin() + cont);
				break;
			}
			cont++;
		}
	}
}

void CarteStoreGUIModele::reloadList(std::vector<Carte> books) {
	model->setBooks(books);
	//model2->setBooks(books);
}

void CarteStoreGUIModele::reloadBasketList(vector<Carte> books) {
	this->tableBooks2->clearContents();
	this->tableBooks2->setRowCount(int(books.size()));

	int lineNumber = 0;
	for (auto& carte : books) {
		this->tableBooks2->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(carte.getTitlu())));
		this->tableBooks2->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(carte.getAutor())));
		this->tableBooks2->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(carte.getGen())));
		this->tableBooks2->setItem(lineNumber, 3, new QTableWidgetItem(QString::number(carte.getAn())));
		lineNumber++;
	}
}

void CarteStoreGUIModele::guiInitializareButoane()
{
	for (const auto& carte : srv.getAll())
		this->guiAddButtonsDinamic(carte.getGen());
}

void CarteStoreGUIModele::guiAddCarte() {
	try {
		//preluare detalii din QLineEdit-uri
		string titlu = editTitlu->text().toStdString();
		string artist = editAutor->text().toStdString();
		string gen = editGen->text().toStdString();
		int an = editAn->text().toInt();

		//optional - golim QLineEdit-urile dupa apasarea butonului
		editTitlu->clear();
		editAutor->clear();
		editGen->clear();
		editAn->clear();

		this->srv.addCarte(titlu, artist, gen, an);
		this->reloadList(this->srv.getAll());

		this->guiAddButtonsDinamic(gen);

		//afisam un mesaj pentru a anunta utilizatorul ca s-a adaugat cartea
		QMessageBox::information(this, "Info", QString::fromStdString("Carte adaugata cu succes."));

	}
	catch (CarteRepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
	catch (ValidateException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMessages()));
	}

}

void CarteStoreGUIModele::createHorizontalGroupBox()
{
	horizontalGroupBox = new QGroupBox(tr("Horizontal layout"));
	QHBoxLayout* layout = new QHBoxLayout;

	for (int i = 0; i < 2; ++i) {
		buttons[i] = new QPushButton(tr("Button %1").arg(i + 1));
		layout->addWidget(buttons[i]);
	}
	horizontalGroupBox->setLayout(layout);
}

void CarteStoreGUIModele::reloadBasketList2() {

	this->listBooks->clear();

	const vector<Carte>& books = srv.getBasketBooks();
	for (auto& carte : books) {
		QString currentItem = QString::fromStdString(carte.getTitlu() + " ; " + carte.getAutor() + " ; " + carte.getGen() + " ; " + std::to_string(carte.getAn()));
		this->listBooks->addItem(currentItem);
	}
}
void CarteStoreGUIModele::guiAddCarteBasket() {
	try {
		//preluare detalii din QLineEdit-uri
		string titlu = editTitluBasket->text().toStdString();
		string autor = editAutorBasket->text().toStdString();

		//optional - golim QLineEdit-urile dupa apasarea butonului
		editTitluBasket->clear();
		editAutorBasket->clear();

		this->srv.addToBasket(titlu, autor);
		//this->reloadBasketList(this->srv.getBasketBooks());
		this->reloadBasketList2();

		//afisam un mesaj pentru a anunta utilizatorul ca s-a adaugat cartea
		QMessageBox::information(this, "Info", QString::fromStdString("Carte adaugata in cos cu succes."));

	}
	catch (CarteRepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
	catch (ValidateException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMessages()));
	}
}
