#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "Game.h"

#include <vector>

class Card;
struct Command;
class Observer;
class Player;
enum class PlayerType;

class GameController {
  // Handles communication between the model (Game) and the view (TextUserInterface)
  // Specification Fields:
  //   game = representation of the state of a game of straights
  private:
    Game *game_;

  public:
    GameController(int seed, std::vector<PlayerType>, Observer *);
    // ensures: initializes this to a new GameController with a new Game

    ~GameController();
    // modifies: this
    // ensures:  this no longer exists; memory is deallocated

    void startGame();
    // modifies: this
    // ensures: the game is started

    void executeCommand(Command command);
    // modifies: this
    // ensures: the command is executed in the game

    GameBoard getGameBoard() const;
    // returns: the game board associated with the game

    std::vector<Player> getPlayers() const;
    // returns: a list of players that are participating in the game

    std::vector<int> getWinners() const;
    // returns: a list of player id that have the lowest scores in the game

    int getCurrentPlayer() const;
    // returns: the id of the current player in the game

    Card getLastCard() const;
    // returns: the last card played or discarded in the game. In the case that there is no last
    //          card played, the ace of spades will be returned.

    std::vector<Card> getCurrentPlayerCards() const;
    // returns: a list of cards associated with the current player in the game

    std::vector<Card> getCurrentPlayerValidCards() const;
    // returns: a list of cards associated with the current player that can be played on the board

    Deck getDeck() const;
    // returns: the deck of cards in the game

    Game::GameState getGameState() const;
    // returns: the state of the game
};

#endif
