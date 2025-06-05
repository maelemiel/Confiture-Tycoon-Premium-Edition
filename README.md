# Ultra Dual Death Run 2 Deluxe Edition Remastered
# Ultra Dual Death Run 2 - Deluxe Edition Remastered

## 🚀 Installation et compilation

### Prérequis
- CMake 3.11 ou plus récent
- Compilateur C++17 compatible (GCC, Clang, MSVC)
- Git

### Compilation
```bash
mkdir build
cd build
cmake ..
make -j$(nproc)
```

### Lancement
```bash
./bin/UltraDualDeathRun2
```


## 🏗️ Structure du projet

```
├── src/
│   ├── main.cpp          # Point d'entrée
│   ├── Game.hpp/.cpp     # Classe principale du jeu
│   └── Player.hpp/.cpp   # Classe joueur
├── assets/
│   ├── images/           # Sprites, textures
│   ├── sounds/           # Effets sonores, musique
│   └── fonts/            # Polices personnalisées
├── build/                # Dossier de compilation
└── CMakeLists.txt        # Configuration CMake
```


## 🔧 TODO / Fonctionnalités à implémenter

### Core Gameplay
- [ ] Système de double saut
- [ ] Obstacles et pièges
- [ ] Collectibles
- [ ] Système de vies/mort
- [ ] Respawn/checkpoints

### Multijoueur
- [ ] Support jusqu'à 6 joueurs
- [ ] Contrôles configurables
- [ ] Modes de jeu coopératif/compétitif

### Niveaux
- [ ] Système de loading de niveaux
- [ ] Éditeur de niveaux simple
- [ ] Plateformes mobiles
- [ ] Éléments interactifs

### Audio/Visuel
- [ ] Système de sprites/animations
- [ ] Particules (mort, collectibles)
- [ ] Musique de fond
- [ ] Effets sonores

### Interface
- [ ] Menu principal
- [ ] Sélection des joueurs
- [ ] Écran de fin de partie
- [ ] HUD en jeu

## 🎯 Conseils pour la game jam

### Workflow Git
```bash
# Créer une branche pour votre fonctionnalité
git checkout -b feature/nom-de-votre-feature

# Après vos modifications
git add .
git commit -m "Description de vos changements"
git push origin feature/nom-de-votre-feature

# Puis créer une Pull Request
```

### Bonnes pratiques
- **Commits fréquents** avec des messages clairs
- **Testez** avant de push
- **Communiquez** les changements importants
- **Gardez des backups** des assets importants
- **Priorisez** les fonctionnalités core avant le polish

## 🛠️ Classes utiles à créer

```cpp
// Suggestions de classes pour l'équipe:
class Level;           // Gestion des niveaux
class Obstacle;        // Obstacles et pièges
class Collectible;     // Items à collecter
class AudioManager;    // Gestion audio
class InputManager;    // Gestion des contrôles
class ParticleSystem;  // Effets visuels
class Camera;          // Caméra qui suit l'action
class GameState;       // États du jeu (menu, jeu, pause, etc.)
```

## 📚 Ressources Raylib utiles

- [Documentation Raylib](https://www.raylib.com/)
- [Exemples de code](https://www.raylib.com/examples.html)
- [Raylib Cheatsheet](https://www.raylib.com/cheatsheet/cheatsheet.html)

## 🐛 Debug et outils

Pour débugger:
```cpp
// Dans votre code, utilisez:
std::cout << "Debug: " << variable << std::endl;
DrawText(TextFormat("Debug: %d", variable), 10, 50, 20, RED);
```
