#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<iostream>
using namespace std;
using namespace sf;

class Button {
    RectangleShape buttonShape;
    Text buttonText;
public:
    Button(){}
    Button(const std::string& text, const Font& font, const Vector2f& position, const Vector2f& size) {
        buttonShape.setPosition(position);
        buttonShape.setSize(size);
        Color bcolor(240, 0, 0);
        buttonShape.setFillColor(bcolor);
        buttonShape.setOutlineColor(Color::Black);
        buttonShape.setOutlineThickness(2);

        buttonText.setFont(font);
        buttonText.setString(text);
        buttonText.setCharacterSize(30);
        buttonText.setFillColor(Color::Black);
        buttonText.setPosition(
            position.x + (size.x - buttonText.getGlobalBounds().width-20) / 2,
            position.y + (size.y - buttonText.getGlobalBounds().height-20) / 2
        );
    }

    void draw(RenderWindow& window) {
        window.draw(buttonShape);
        window.draw(buttonText);
    }

    bool isClicked(const Vector2f& mousePos) {
        return buttonShape.getGlobalBounds().contains(mousePos);
    }

};
