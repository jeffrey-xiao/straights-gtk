#ifndef GAME_H
#define GAME_H

#include "Card.h"
#include "Deck.h"
#include "GameBoard.h"
#include "Player.h"
#include "Subject.h"

#include <vector>

struct Command;
class Observer;

const int PLAYER_COUNT = 4;
const int MAX_SCORE = 80;

class Game : public Subject {
  // Represents the state of a game of straights
  // Specification Fields:
  //   ROUND_START: Represents that the game of straights has started
  //   HUMAN_INPUT: Represents that the game is waiting on a human player
  //   INVALID_PLAY_INPUT: Represents that the last human play input is invalid
  //   INVALID_DISCARD_INPUT: Represents that the last human discard input is invalid
  //   DISCARDED_CARD: Represents that a card has been discarded in the game
  //   PLAYED_CARD: Represents that a card has been played in the game
  //   ROUND_END: Represents that a round has ended
  //   GAME_END: Represents that the game has ended
  public:
    enum class GameState {
      GAME_START,
      ROUND_START,
      HUMAN_INPUT,
      INVALID_PLAY_INPUT,
      INVALID_DISCARD_INPUT,
      DISCARDED_CARD,
      PLAYED_CARD,
      ROUND_END,
      GAME_END,
      GAME_QUIT,
    };
    explicit Game(int);
    // ensures: initializes this to a new Game with a specified seed and list of Players

    std::vector<Card> getCurrentPlayerCards() const;
    // returns: a list of cards associated with the current player in the game

    std::vector<Card> getCurrentPlayerValidCards() const;
    // returns: a list of cards associated with the current player that can be played on the boar

    void initGame();
    // modifies: this
    // ensures: the game is prepared to start and all observers are notified that a new game is
    //          preparing to start.

    void startGame(std::vector<PlayerType>);
    // modifies: this
    // ensures: the game is started. All observers are notified that a new game has started.

    void startRound();
    // modifies: this
    // ensures: the deck is reshuffled, all hands are dealt to players, the discard piles are
    //          emptied, and a new round of straights is started. All observers are notified that
    //          a new round has started.

    void playCard(Card);
    // modifies: this
    // ensures: if the card is able to be played, then the game state is changed to PLAYED_CARD and
    //          the card is removed from the hand of the player and put onto the game board. If the
    //          card is an invalid play, then the game state is changed to INVALID_PLAY_INPUT. The
    //          state of the game board and hand does not change. All observers are notified that a
    //          card has been played.

    void discardCard(Card);
    // modifies: this
    // ensures: if the card is able to be discarded, then the game state is changed to
    //          DISCARDED_CARD and the card is removed from the hand of the player and put in the
    //          player's discard pile. If the card is an invalid discard, then the game state is
    //          changed to INVALID_DISCARD_INPUT. The state of the game board, hand, and discard
    //          pile does not change. All observers are notified that a card has been discarded.

    void ragequit();
    // modifies: this
    // ensures: the current player changed to a computer player and all observers are notified that
    //          a human player has ragequit.

    void quit();
    // modifies: this
    // ensures: the game is terminated

    GameBoard getGameBoard() const;
    // returns: the game board associated with the game

    std::vector<Player> getPlayers() const;
    // returns: a list of players that are participating in the game

    Player getCurrentPlayer() const;
    // returns: the id of the current player in the game

    Card getLastCard() const;
    // requires: a card has been played
    // returns: the last played or discarded in the game

    Deck getDeck() const;
    // returns: the deck of cards in the game

    GameState getGameState() const;
    // returns: the state of the game

    void setSeed(int);
    // modifies: this
    // ensures: sets of the seed of the game

    bool canUndoMove() const;
    // return: true if a human player has made a move in the current round
    //         false if a human player has not

    void undoMove();
    // modifies: this
    // requires: canUndoMove()
    // ensures: undos moves in the round until it undos a move by a human player, or
    //          no moves have been played

  private:
    int seed_;
    GameBoard gameBoard_;
    std::vector<Player> players_;
    int currentPlayer_;
    Deck deck_;
    GameState gameState_;
    std::vector<Card> cardsPlayed_;

    void runRound();
    // modifies: this
    // ensures: plays the first valid card or discards the first hand if there are no valid cards
    //          until the current player is a human player

    void setGameState(GameState gameState);
    // modifies: this
    // ensures: gameState_ is set to gameState and the user interface is notified of the change in
    //          state
};

#endif
