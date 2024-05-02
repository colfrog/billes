#include "Arena.h"
#include <QPair>
#include <iostream>

std::random_device Arena::random_device;
std::mt19937 Arena::rng{random_device()};
std::uniform_int_distribution<std::mt19937::result_type>
Arena::random_mass{100, 1000};
std::uniform_real_distribution<>
Arena::random_velocity{-1.0, 1.0};

Arena::Arena(quint32 width, quint32 height)
	: m_width(width), m_height(height),
	  random_x(0, width), random_y(0, height)
{}

const std::list<Bille> &Arena::billes() const {
	return m_billes;
}

void Arena::resize(quint32 width, quint32 height) {
	m_width = width;
	m_height = height;
	random_x = std::uniform_int_distribution<std::mt19937::result_type>(0, width - 1);
	random_y = std::uniform_int_distribution<std::mt19937::result_type>(0, height - 1);
}

void Arena::add_bille() {
	m_billes.push_back(Bille(QPoint(random_x(rng), random_y(rng)),
				 QVector2D(random_velocity(rng),
					   random_velocity(rng)),
				 random_mass(rng)));
}

void Arena::iterate() {
	for (Bille &bille : m_billes)
		bille.iterate();
}

void Arena::collide() {
	for (auto it1 = m_billes.begin(); it1 != m_billes.end(); it1++)
		for (auto it2 = it1; it2 != m_billes.end(); it2++)
			if (it1 != it2 && it1->overlaps(*it2))
				it1->collide(*it2);
}

void Arena::bounce() {
	for (Bille &bille : m_billes) {
		const QPointF &pos = bille.position();
		const quint32 r = bille.radius();
		if (pos.x() + r >= m_width) {
			bille.setX(m_width - (r + 1));
			bille.bounce(Bille::BounceDirection::RIGHT);
		}
		if (pos.x() - r <= 0) {
			bille.setX(r);
			bille.bounce(Bille::BounceDirection::LEFT);
		}
		if (pos.y() + r >= m_height) {
			bille.setY(m_height - (r + 1));
			bille.bounce(Bille::BounceDirection::DOWN);
		}
		if (pos.y() - r <= 0) {
			bille.setY(r);
			bille.bounce(Bille::BounceDirection::UP);
		}
	}
}
