#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<iostream>
using namespace std;
using namespace sf;
class player {
protected:
  int score;
  RectangleShape paddle;
public:
  player() {
    score = 0;
  }
  RectangleShape& getShape() {
    return paddle;
  }
  int& getScore() { return score; }
  void increment_score() { score++; }
};
class player1 : public player {
  int width;;
  int height;
public:
  player1(int w, int h) : player() {
  score = 0;
  width = w;
  height = h;
  paddle.setPosition(50, 200);
  paddle.setSize(Vector2f(width, height));
}


};
class player2 : public player {

public:
  player2() : player() {
    score = 0;
    paddle.setPosition(700, 200);
    paddle.setSize(Vector2f(10, 100));
}


};
class AIopponent : public player {
public:
  AIopponent() : player() {
    paddle.setPosition(700, 200);
    paddle.setSize(Vector2f(10, 130));
}
};
