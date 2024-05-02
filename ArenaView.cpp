#include "ArenaView.h"
#include <QPainter>
#include <QKeyEvent>

ArenaView::ArenaView(QWidget *parent)
	: QWidget(parent), m_arena(500, 500), m_timer(this)
{
	for (int i = 0; i < 100; i++)
		m_arena.add_bille();

	connect(&m_timer, &QTimer::timeout,
		this, &ArenaView::iterate);
	m_timer.start(10);
}

void ArenaView::iterate() {
	m_arena.collide();
	m_arena.bounce();
	m_arena.iterate();
	update();
}

void ArenaView::paintEvent(QPaintEvent *event) {
	QPainter painter(this);
	painter.setBrush(QColor("#000"));
	painter.setPen(QColor("#000"));
	painter.drawRect(0, 0, width(), height());

	painter.setBrush(QColor("#f00"));
	painter.setPen(QColor("#fff"));
	int r, g, b, col;
	for (const Bille &bille : m_arena.billes()) {
		col = 0xffffff*bille.mass()/1000;
		r = (col>>16)&0xff;
		g = (col>>8)&0xff;
		b = col&0xff;
		painter.setBrush(QColor(r, g, b));
		painter.drawEllipse(bille.position(), bille.radius(), bille.radius());
	}
}

void ArenaView::resizeEvent(QResizeEvent *event) {
	m_arena.resize(width(), height());
}

void ArenaView::keyPressEvent(QKeyEvent *event) {
	if (event->key() == Qt::Key_A)
		m_arena.add_bille();
}
