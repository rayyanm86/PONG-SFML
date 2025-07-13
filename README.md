# 🎮 Pong SFML Game

A classic Pong game built with **C++** and **SFML**, featuring:

* **Single Player Mode:** Play against an AI opponent with two difficulty levels.
* **Two Player Mode:** Challenge a friend locally.
* **Timed Matches:** Each round lasts **60 seconds**, and the player with the highest score wins.

---

## 🛠️ Features

-Single Player with **Easy and Hard Difficulty Modes**
-Local Two Player Mode
-Score Tracking
-60-Second Rounds
-Adaptive AI Speed in Hard Mode – The AI paddle **gradually increases its speed over time**
-Simple, retro-inspired visuals

---

## 🧰 Requirements

* **C++ Compiler** (C++11 or later recommended)
* **SFML Library** installed (version 2.5 or compatible)

> **Note:** On Windows, you may need to configure your linker to include SFML dependencies:

```
-lsfml-graphics -lsfml-window -lsfml-system
```

---

## 🚀 Building the Game

1. **Clone the Repository**

   ```bash
   git clone https://github.com/yourusername/pong-sfml-game.git
   cd pong-sfml-game
   ```

2. **Compile**

   ```bash
   g++ -o pong main.cpp -lsfml-graphics -lsfml-window -lsfml-system
   ```

3. **Run**

   ```bash
   ./pong
   ```

> On Windows (MinGW), the command might look like:
>
> ```bash
> g++ -o pong.exe main.cpp -lsfml-graphics -lsfml-window -lsfml-system
> ```

---

## 🎮 How to Play

### Game Modes

**Single Player Mode**
At the start, you can choose:

* **Easy Difficulty:** AI speed stays constant and predictable.
* **Hard Difficulty:** AI paddle **gets faster over time**, making it more challenging as the match progresses.

**Two Player Mode**
Compete locally against another player.

---

### Controls

**Player Paddle (Left):**

* `W` – Move Up
* `S` – Move Down

**AI Paddle (Right):**

* Moves automatically depending on difficulty.

**Two Player Mode (Right Paddle):**

* `Up Arrow` – Move Up
* `Down Arrow` – Move Down

---

### Objective

* Hit the ball past your opponent to score points.
* The match timer runs for **60 seconds**.
* When time is up, the player with the **highest score wins**.
* There is **no danger zone**—the playfield stays the same throughout the match.

---

### AI Difficulty

* **Easy Mode:** AI paddle speed remains **constant**.
* **Hard Mode:** AI paddle speed **increases gradually over time**, rewarding early scoring.

---

## 📝 Customization

You can easily adjust in the source code:

* **Game Duration** – Change the 60-second timer.
* **Paddle and Ball Speeds** – Make the game faster or slower.
* **AI Speeds and Difficulty Scaling** – Tune how quickly the AI improves in Hard Mode.

---

## 📄 License

This project is open-source and available under the [MIT License](LICENSE).
