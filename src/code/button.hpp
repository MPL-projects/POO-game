// button.hpp

#ifndef BUTTON_HPP
#define BUTTON_HPP


class Button {
    private:
        float x; // Coordonnée en x du boutton
		float y; // Coordonnée en y du boutton
		char name; // Nom du boutton


    public:
		// Constructeur
		Button(char name, float x, float y);

		// Destructeur

		// Accesseurs 
        float getX() const;
        float getY() const;
		char getName() const;
        void setX(float x);
        void setY(float y);
		void setName(float Name);


};

#endif