#pragma once
#include<QAbstractListModel>
#include "carte.h"
#include <vector>
#include <qdebug.h>
#include <QColor>

class MyListModel :public QAbstractListModel {
	std::vector<Carte> books;
public:
	MyListModel(const std::vector<Carte>& books) :books{ books } {
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return books.size();
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			qDebug() << "get row:" << index.row();
			auto genuri = books[index.row()].getGen();
			return QString::fromStdString(genuri);
		}
		if (role == Qt::UserRole) {
			auto carte = books[index.row()];
			//return QString::fromStdString(tt);
			return QString::fromStdString(carte.getTitlu() + "\t" + carte.getAutor() + "\t" + carte.getGen() + "\t" + to_string(carte.getAn()));

		}
		if (role == Qt::BackgroundRole) {
			if (books[index.row()].getGen()[0] == 'z') {
				return QColor(Qt::red);
			}
		}
		return QVariant{};
	}
	void setBooks(const std::vector<Carte>& books) {
		this->books = books;
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(), 0);
		emit dataChanged(topLeft, bottomR);
	}
};