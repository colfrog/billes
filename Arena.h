#pragma once

#include <list>
#include <random>

#include "Bille.h"

class Arena {
public:
	Arena(quint32 width, quint32 height);

	const std::list<Bille> &billes() const;

	void resize(quint32 width, quint32 height);

	void add_bille();
	void iterate();
	void collide();
	void bounce();

private:
	quint32 m_width, m_height;
	std::list<Bille> m_billes;

	static std::random_device random_device;
	static std::mt19937 rng;
	static std::uniform_int_distribution<std::mt19937::result_type>
	random_mass;
	static std::uniform_real_distribution<>
	random_velocity;
	std::uniform_int_distribution<std::mt19937::result_type>
	random_x;
	std::uniform_int_distribution<std::mt19937::result_type>
	random_y;
};
