#include "BasketGUI.h"

void BasketGUI::initGUI() {
	lyMain = new QHBoxLayout{};
	this->setLayout(lyMain);

	QWidget* leftSide = new QWidget{};
	QVBoxLayout* lyLeft = new QVBoxLayout{};
	leftSide->setLayout(lyLeft);

	QWidget* formW = new QWidget{};
	QFormLayout* lyEdits = new QFormLayout{};
	lblTitlu = new QLabel{ "Titlu" };
	lblAutor = new QLabel{ "Autor" };
	lblFisier = new QLabel{ "Fisier" };
	editTitlu = new QLineEdit{};
	editAutor = new QLineEdit{};
	editFisier = new QLineEdit{};

	lblSlider = new QLabel{ "Nr. carti random de generat" };
	editNoSlider = new QLineEdit{};
	lyEdits->addRow(lblTitlu, editTitlu);
	lyEdits->addRow(lblAutor, editAutor);
	lyEdits->addRow(lblFisier, editFisier);
	lyEdits->addRow(lblSlider, editNoSlider);
	formW->setLayout(lyEdits);


	btnAdd = new QPushButton{ "Adauga in cos" };
	btnGenerate = new QPushButton{ "Genereaza random" };
	btnEmpty = new QPushButton{ "Goleste cos" };
	btnExport = new QPushButton{ "Export cos" };
	btnClose = new QPushButton{ "Close" };

	btnEmpty->setStyleSheet("background-color: #eb87ff; color: green; font-weight: bold;");

	btnLabelWindow = new QPushButton{ "Fereastra label" };
	btnLabelWindow->setStyleSheet("background-color: cyan");

	btnTableWindow = new QPushButton{ "Cos CRUD GUI" }; //fereastra tabel
	btnTableWindow->setStyleSheet("background-color: magenta");

	btnDrawWindow = new QPushButton{ "Cos Read-Only GUI" }; //fereastra desen
	btnDrawWindow->setStyleSheet("background-color: yellow");


	sliderGenerate = new QSlider{};
	sliderGenerate->setMinimum(1);
	sliderGenerate->setMaximum(static_cast<int>(srv.getAll().size()));

	lyLeft->addWidget(formW);
	lyLeft->addWidget(btnAdd);
	lyLeft->addWidget(btnGenerate);
	lyLeft->addWidget(btnEmpty);
	lyLeft->addWidget(btnExport);
	lyLeft->addWidget(btnClose);
	//lyLeft->addWidget(btnLabelWindow);
	lyLeft->addWidget(btnTableWindow);
	lyLeft->addWidget(btnDrawWindow);

	QWidget* rightSide = new QWidget{};
	QVBoxLayout* lyRight = new QVBoxLayout{};
	rightSide->setLayout(lyRight);

	listBooks = new QListWidget{};
	listBooks->setFixedWidth(320);
	listBooks->setSelectionMode(QAbstractItemView::SingleSelection);

	lyRight->addWidget(listBooks);

	widgetDynamic = new QWidget{};
	lyBtnDynamic = new QVBoxLayout{};
	widgetDynamic->setLayout(lyBtnDynamic);
	//reloadDynamicButtons();

	lyMain->addWidget(leftSide);
	lyMain->addWidget(sliderGenerate);
	lyMain->addWidget(rightSide);
	lyMain->addWidget(widgetDynamic);

}
set<string> BasketGUI::getGenres(const vector<Carte>& basketBooks) {
	set<string> genres;

	for (const auto& s : basketBooks) {
		genres.insert(s.getGen());
	}
	return genres;
}
int howManyWithGenre(const vector<Carte>& books, string genre) {
	int noBooks = count_if(books.begin(), books.end(), [&](Carte b) {
		return b.getGen() == genre; });
	return noBooks;
}
void clearLayout(QLayout* layout) {
	if (layout == NULL)
		return;
	QLayoutItem* item;
	while ((item = layout->takeAt(0))) {
		if (item->layout()) {
			clearLayout(item->layout());
			delete item->layout();
		}
		if (item->widget()) {
			delete item->widget();
		}
		delete item;
	}
}
//void BasketGUI::reloadDynamicButtons() {
//	clearLayout(this->lyBtnDynamic);
//	const vector<Song>& playlistSongs = this->srv.getPlaylistSongs();
//	set<string> genres = this->getGenres(playlistSongs);
//
//	for (string genre : genres) {
//		QPushButton* btn = new QPushButton{ QString::fromStdString(genre) };
//		lyBtnDynamic->addWidget(btn);
//		int howMany = howManyWithGenre(playlistSongs, genre);
//		//mult mai eficient: puteam sa folosim un dictionar cu cheia = gen, valoare=nr melodii
//		//->o singura parcurgere a listei de melodii
//		QObject::connect(btn, &QPushButton::clicked, [genre, howMany]() {
//			QMessageBox::information(nullptr, "Info", QString::fromStdString("Melodii cu genul " + genre + " : " + to_string(howMany)));
//
//			});
//	}
//
//}
void BasketGUI::connectSignalsSlots() {
	srv.getBasket().addObserver(this);
	QObject::connect(btnAdd, &QPushButton::clicked, this, &BasketGUI::addToBasket);
	QObject::connect(sliderGenerate, &QSlider::sliderReleased, [&]() {
		qDebug() << sliderGenerate->value();
		});
	QObject::connect(btnGenerate, &QPushButton::clicked, [&]() {
		int noBooks = this->sliderGenerate->value();
		editNoSlider->setText(QString::number(noBooks));
		qDebug() << "This many books to add:" << noBooks;
		srv.addRandomToBasket(noBooks);
		this->reloadBasket();
		});
	QObject::connect(btnEmpty, &QPushButton::clicked, [&]() {
		srv.emptyBasket();
		this->reloadBasket();
		});
	QObject::connect(btnExport, &QPushButton::clicked, [&]() {
		string filename = editFisier->text().toStdString();
		this->srv.exportBasket(filename);

		//afisam un mesaj pentru a anunta utilizatorul ca s-a exportat cosul
		QMessageBox::information(this, "Info", QString::fromStdString("Cos exportat cu succes!"));
		});
	QObject::connect(btnClose, &QPushButton::clicked, this, &BasketGUI::close);

	QObject::connect(btnLabelWindow, &QPushButton::clicked, this, [&]() {
		auto labelWindow = new BasketGUILabel{ srv.getBasket() };
		labelWindow->show();
		});

	QObject::connect(btnTableWindow, &QPushButton::clicked, this, [&]() {
		auto tableWindow = new BasketGUITable{ srv.getBasket(), srv.getAll() };
		tableWindow->show();
		});

	QObject::connect(btnDrawWindow, &QPushButton::clicked, this, [&]() {
		auto drawWindow = new BasketGUIDraw{ srv.getBasket() };
		drawWindow->show();
		});

	QObject::connect(listBooks, &QListWidget::itemSelectionChanged, [&]() {
		auto selItms = listBooks->selectedItems();
		for (auto item : selItms) {
			qDebug() << item->text();
			item->setBackground(Qt::green); // sets green background
		}

		});
}


void BasketGUI::reloadBasket() {

	this->listBooks->clear();

	const vector<Carte>& books = srv.getBasketBooks();
	for (auto& carte : books) {
		QString currentItem = QString::fromStdString(carte.getTitlu() + "\t" + carte.getAutor() + "\t" + carte.getGen() + "\t" + to_string(carte.getAn()));
		this->listBooks->addItem(currentItem);
	}
	//reloadDynamicButtons();
}


void BasketGUI::addToBasket() {
	try {
		string titlu = editTitlu->text().toStdString();
		string autor = editAutor->text().toStdString();

		editTitlu->clear();
		editAutor->clear();


		this->srv.addToBasket(titlu, autor);
		this->reloadBasket();

		//afisam un mesaj pentru a anunta utilizatorul ca melodia s-a adaugat
		QMessageBox::information(this, "Info", QString::fromStdString("Carte adaugata cu succes in cos."));

	}
	catch (CarteRepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
	catch (ValidateException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMessages()));
	}

}