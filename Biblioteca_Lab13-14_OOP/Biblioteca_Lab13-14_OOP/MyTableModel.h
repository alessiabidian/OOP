#pragma once
#include <QAbstractTableModel>
#include "carte.h"
#include <vector>
#include <qdebug.h>
#include <QBrush>

class MyTableModel :public QAbstractTableModel {
	std::vector<Carte> books;
	int& an;
public:
	MyTableModel(const std::vector<Carte>& books, int& an) :books{ books }, an{ an } {};

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return books.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		qDebug() << "row:" << index.row() << " col:" << index.column() << " role" << role;
		if (role == Qt::ForegroundRole) {
			Carte c = books[index.row()];
			if (c.getAn() > an) {
				return QBrush{ Qt::blue };
			}
		}
		if (role == Qt::DisplayRole) {
		//if (role == Qt::UserRole) {

			Carte c = books[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(c.getTitlu());
			}
			else if (index.column() == 1) {
				return QString::fromStdString(c.getAutor());
			}
			else if (index.column() == 2) {
				return QString::fromStdString(c.getGen());
			}
			else if (index.column() == 3) {
				return QString::number(c.getAn());
			}
		}

		return QVariant{};
	}

	void setBooks(const std::vector<Carte>& books) {
		this->books = books;
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomR);
		emit layoutChanged();
	}
};