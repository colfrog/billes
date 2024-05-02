#include "Bille.h"
#include <cmath>
#include <iostream>

Bille::Bille()
	: m_position(QPointF(0, 0)), m_velocity(QPoint(0, 0)), m_mass(1)
{}

Bille::Bille(QPointF position, QVector2D velocity, qreal mass)
	: m_position(position), m_velocity(velocity), m_mass(mass), m_radius(m_mass/100)
{}

const QPointF &Bille::position() const {
	return m_position;
}

const QVector2D &Bille::velocity() const {
	return m_velocity;
}

quint32 Bille::mass() const {
	return m_mass;
}

quint32 Bille::radius() const {
	return m_radius;
}

void Bille::setX(qreal x) {
	m_position.setX(x);
}

void Bille::setY(qreal y) {
	m_position.setY(y);
}

void Bille::iterate() {
	m_position.rx() += m_velocity.x();
	m_position.ry() += m_velocity.y();
}

void Bille::collide(Bille &other) {
	QVector2D x1(m_position);
	QVector2D x2(other.m_position);
	QVector2D v1(m_velocity);
	QVector2D v2(other.m_velocity);
	qreal m1 = m_mass, m2 = other.m_mass;
	QVector2D v1f = v1 - ((2*m2/(m1 + m2))
			      * (QVector2D::dotProduct(v1 - v2, x1 - x2)
				 / (x1 - x2).lengthSquared()))*(x1 - x2);
	QVector2D v2f = v2 - ((2*m1/(m1 + m2))
			      * (QVector2D::dotProduct(v2 - v1, x2 - x1)
				 / (x2 - x1).lengthSquared()))*(x2 - x1);
	m_velocity = v1f;
	other.m_velocity = v2f;
	QVector2D dir = (x2 - x1).normalized();
	other.m_position = m_position + ((m_radius + other.m_radius + 1)*dir).toPointF();
}

bool Bille::overlaps(const Bille &other) const {
	QVector2D p1(m_position);
	QVector2D p2(other.m_position);
	qreal dist = p1.distanceToPoint(p2);
	return dist <= m_radius + other.m_radius;
}

void Bille::bounce(BounceDirection dir) {
	double vx = m_velocity.x(), vy = m_velocity.y();
	switch (dir) {
	case BounceDirection::UP:
	case BounceDirection::DOWN:
		m_velocity.setY(-vy);
		break;
	case BounceDirection::LEFT:
	case BounceDirection::RIGHT:
		m_velocity.setX(-vx);
		break;
	}
}

bool Bille::operator==(const Bille &other) const {
	return m_position == other.m_position &&
		m_velocity == other.m_velocity &&
		m_mass == other.m_mass;
}

bool Bille::operator!=(const Bille &other) const {
	return !(*this == other);
}
