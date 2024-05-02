#pragma once

#include <QWidget>
#include <QTimer>

#include "Arena.h"

class ArenaView : public QWidget {
public:
	ArenaView(QWidget *parent = nullptr);

public slots:
	void iterate();

protected:
	void paintEvent(QPaintEvent *event) override;
	void resizeEvent(QResizeEvent *event) override;
	void keyPressEvent(QKeyEvent *event) override;

private:
	Arena m_arena;
	QTimer m_timer;
};
