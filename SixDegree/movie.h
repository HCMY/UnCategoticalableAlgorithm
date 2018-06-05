#ifndef MOVIE_H_INCLUDED
#define MOVIE_H_INCLUDED

#include <string>
#include <vector>

class Actor;

class Movie
{
public:
	Movie(std::string title, int year)
		:title_{title}, year_{year}
		{}
	~Movie();


	void addActors(Actor *actors); //add actor to this object
	const int getYear() const;
	const std::vector<Actor *> getActors() const;
	const std::string getTitle() const;

private:
	std::vector<Actor *> actors_;
	std::string title_;
	int year_;
};

#endif // MOVIE_H_INCLUDED
