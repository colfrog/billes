#pragma once

#include <QPoint>
#include <QVector2D>

class Bille {
public:
	Bille();
	Bille(QPointF position, QVector2D velocity, qreal mass);

	const QPointF &position() const;
	const QVector2D &velocity() const;
	quint32 mass() const;
	quint32 radius() const;

	void setX(qreal x);
	void setY(qreal y);

	enum class BounceDirection {
		UP, DOWN, LEFT, RIGHT
	};

	void iterate();
	void collide(Bille &other);
	bool overlaps(const Bille &other) const;
	void bounce(BounceDirection dir);

	bool operator==(const Bille &other) const;
	bool operator!=(const Bille &other) const;

private:
	QPointF m_position;
	QVector2D m_velocity;
	qreal m_mass;
	qreal m_radius;
};
