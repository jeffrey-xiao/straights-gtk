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
      ROUND_START,
      HUMAN_INPUT,
      INVALID_PLAY_INPUT,
      INVALID_DISCARD_INPUT,
      DISCARDED_CARD,
      PLAYED_CARD,
      ROUND_END,
      GAME_END,
    };
    Game(int, std::vector<PlayerType>);
    // ensures: initializes this to a new Game with a specified seed and list of Players

    std::vector<Card> getCurrentPlayerCards() const;
    // returns: a list of cards associated with the current player in the game

    std::vector<Card> getCurrentPlayerValidCards() const;
    // returns: a list of cards associated with the current player that can be played on the boar

    void startRound();
    // modifies: this
    // ensures: the deck is reshuffled, all hands are dealt to players, the discard piles are
    //          emptied, and a new round of straights is started

    void playCard(Card);
    // modifies: this
    // ensures: if the card is able to be played, then the game state is changed to PLAYED_CARD and
    //          the card is removed from the hand of the player and put onto the game board. If the
    //          card is an invalid play, then the game state is changed to INVALID_PLAY_INPUT. The
    //          state of the game board and hand does not change.

    void discardCard(Card);
    // modifies: this
    // ensures: if the card is able to be discarded, then the game state is changed to
    //          DISCARDED_CARD and the card is removed from the hand of the player and put in the
    //          player's discard pile. If the card is an invalid discard, then the game state is
    //          changed to INVALID_DISCARD_INPUT. The state of the game board, hand, and discard
    //          pile does not change

    void ragequit();
    // modifies: this
    // ensures: the current player changed to a computer player
    
    void quit();
    // modifies: this
    // ensures: the game is terminated

    GameBoard getGameBoard() const;
    // returns: the game board associated with the game

    std::vector<Player> getPlayers() const;
    // returns: a list of players that are participating in the game

    int getCurrentPlayer() const;
    // returns: the id of the current player in the game

    Card getLastCard() const;
    // returns: the last played or discarded in the game. In the case that there is no last card
    //          played, the ace of spaces will be returned.

    Deck getDeck() const;
    // returns: the deck of cards in the game

    GameState getGameState() const;
    // returns: the state of the game

  private:
    int seed_;
    GameBoard gameBoard_;
    std::vector<Player> players_;
    int currentPlayer_;
    Deck deck_;
    GameState gameState_;
    Card lastCard_;

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
