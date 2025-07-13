Absolutely—here’s the **complete polished `README.md`** incorporating *everything you shared*:

---

# 🎮 Pong SFML Game

A classic Pong game built with **C++** and **SFML**, featuring:

* **Single Player Mode**: Play against an adaptive AI opponent.
* **Two Player Mode**: Challenge a friend locally.
* **Timed Matches**: Each round lasts **60 seconds**, and the player with the highest score wins.

---

## 🛠️ Features

✅ Single Player vs AI
✅ Local Two Player Mode
✅ Score Tracking
✅ 60-Second Rounds
✅ Adaptive AI Speed – The AI paddle **gradually increases its speed over time**, becoming more challenging as the match progresses.
✅ Simple, retro-inspired visuals

---

## 🧰 Requirements

* **C++ Compiler** (C++11 or later recommended)
* **SFML Library** installed (version 2.5 or compatible)

> **Note**: On Windows, you may need to configure your linker to include SFML dependencies:

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

### Controls

**Single Player Mode**

* **Player Paddle (Left):**

  * `W` – Move Up
  * `S` – Move Down
* The AI paddle (Right) moves automatically and **gets faster over time**.

**Two Player Mode**

* **Player 1 (Left):**

  * `W` – Move Up
  * `S` – Move Down
* **Player 2 (Right):**

  * `Up Arrow` – Move Up
  * `Down Arrow` – Move Down

### Objective

* Hit the ball past your opponent to score points.
* The match timer runs for **60 seconds**.
* When time is up, the player with the **highest score wins**.
* There is **no danger zone**—the play area stays the same throughout.

### AI Difficulty

In Single Player Mode, the AI paddle starts at a moderate speed and **ramps up gradually as time progresses**, so scoring early gives you an advantage.

---

## 📝 Customization

You can easily adjust in the source code:
**Game Duration** – Change the 60-second timer.
**Paddle and Ball Speeds** – Make the game faster or slower.
**AI Difficulty Curve** – Tune how quickly the AI speed increases over time.

---

## 📄 License

This project is open-source and available under the [MIT License](LICENSE).
