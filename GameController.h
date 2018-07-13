#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "Game.h"
#include "Subject.h"

#include <vector>

class Card;
struct Command;
class Observer;
class Player;
enum class PlayerType;

class GameController : public Subject {
  // Handles communication between the model (Game) and the view (TextUserInterface)
  // Specification Fields:
  //   game = representation of the state of a game of straights
  private:
    Game *game_;

  public:
    explicit GameController(int seed);
    // ensures: initializes this to a new GameController with a new Game, the new Game
    //          is made using the specified seed

    ~GameController();
    // modifies: this
    // ensures:  this no longer exists; owned memory is deallocated

    void initGame();
    // modifies: this
    // ensures: the game is prepared to start and all observers are notified

    void startGame(std::vector<PlayerType>);
    // modifies: this
    // ensures: the game is started

    void executeCommand(Command command);
    // modifies: this
    // ensures: the command is executed in the game

    GameBoard getGameBoard() const;
    // returns: the game board associated with the game

    std::vector<Player> getPlayers() const;
    // returns: a list of players that are participating in the game

    std::vector<Player> getWinners() const;
    // returns: a list of players that have the lowest scores in the game

    int getCurrentPlayerId() const;
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

    void addObserver(Observer *);
    // modifies: this
    // ensures: adds an observer to the game

    void setSeed(int);
    // modifies: this
    // ensures: sets the seed of the game

    bool canUndoMove() const;
    // return: true if a human player has made a move in the current round
    //         false if a human player has not

    void undoMove();
    // modifies: this
    // requires: canUndoMove()
    // ensures: undos moves in the round until it undos a move by a human player, or
    //          no moves have been played
};

#endif
