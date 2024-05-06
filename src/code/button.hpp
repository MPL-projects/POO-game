// button.hpp

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>

using namespace std;

class Button {
    private:
        float x; 		// Coordonnée en x du boutton
		float y; 		// Coordonnée en y du boutton
		string name; 	// Nom du boutton


    public:
		// Constructeur
		Button() : x(0), y(0), name("None") {};
		Button(float Cx, float Cy, string name) : x(Cx), y(Cy), name(name) {};

		// Destructeur
		~Button();

		// Accesseurs 
        float getX() const;
        float getY() const;
		char getName() const;
        void setX(float x);
        void setY(float y);
		void setName(float Name);
};

#endif