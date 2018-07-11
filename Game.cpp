#include "Card.h"
#include "Command.h"
#include "Game.h"
#include "Observer.h"
#include "Player.h"
#include "Deck.h"

#include <algorithm>
#include <cassert>
#include <vector>

const Card SEVEN_OF_SPADES = Card(SPADE, SEVEN);
const int PLAYER_COUNT = 4;
const int MAX_SCORE = 80;

Game::Game(int seed): seed_(seed), gameState_(GameState::ROUND_START), lastCard_(Card(SPADE, ACE)) {
  players_.reserve(PLAYER_COUNT);
  for (int i = 0; i < PLAYER_COUNT; i++) {
    players_.push_back(Player(i + 1));
  }
}

std::vector<Card> Game::getCurrentPlayerCards() const {
  return players_[currentPlayer_].getCards();
}

std::vector<Card> Game::getCurrentPlayerValidCards() const {
  std::vector<Card> validCards = players_[currentPlayer_].getCards();

  // If the player has a seven of spades, then it must be the first turn of the game. That player
  // must play the seven of spades regardless if the player has other sevens
  if (std::find(validCards.begin(), validCards.end(), SEVEN_OF_SPADES) != validCards.end()) {
    return { SEVEN_OF_SPADES };
  }

  // Else, remove all cards that cannot be played in the current game board
  else {
    validCards.erase(
      std::remove_if(
        validCards.begin(),
        validCards.end(),
        [this](const Card &card) { return !gameBoard_.canPlayCard(card); }
      ),
      validCards.end()
    );
  }
  return validCards;
}

GameBoard Game::getGameBoard() const {
  return gameBoard_;
}

std::vector<Player> Game::getPlayers() const {
  return players_;
}

Player Game::getCurrentPlayer() const {
  return players_[currentPlayer_];
}

Card Game::getLastCard() const {
  return lastCard_;
}

Deck Game::getDeck() const {
  return deck_;
}

Game::GameState Game::getGameState() const {
  return gameState_;
}

void Game::setGameState(Game::GameState gameState) {
  gameState_ = gameState;
  notify();
}

void Game::playCard(Card card) {
  // check if card is in the list of valid cards
  std::vector<Card> validCards = getCurrentPlayerValidCards();
  bool isValidMove = std::find(validCards.begin(), validCards.end(), card) != validCards.end();

  // if the card is a valid move, then add the card to game board, remove the card from the
  // player's hand and continue the game
  if (isValidMove) {
    gameBoard_.playCard(card);
    players_[currentPlayer_].playCard(card);
    lastCard_ = card;
    setGameState(GameState::PLAYED_CARD);
    currentPlayer_ = (currentPlayer_ + 1) % 4;
    runRound();
  }

  // if the card is an invalid move, then pause the game and request for user input
  else {
    setGameState(GameState::INVALID_PLAY_INPUT);
  }
}

void Game::discardCard(Card card) {
  std::vector<Card> cards = getCurrentPlayerCards();

  // if there are no valid cards to be played and the player has card, then card can be discarded
  // the card is removed from the player's hand and added to the player's discard pile, and play is
  // continued
  if (getCurrentPlayerValidCards().empty() && std::find(cards.begin(), cards.end(), card) != cards.end()) {
    players_[currentPlayer_].discardCard(card);
    lastCard_ = card;
    setGameState(GameState::DISCARDED_CARD);
    currentPlayer_ = (currentPlayer_ + 1) % 4;
    runRound();
  }

  // if the player has valid cards or card is not in the player's hand then pause the game and
  // request for user input
  else {
    setGameState(GameState::INVALID_DISCARD_INPUT);
  }
}

void Game::ragequit() {
  players_[currentPlayer_].setPlayerType(PlayerType::COMPUTER);
  runRound();
}

void Game::quit() {
  setGameState(Game::GameState::GAME_QUIT);
}

void Game::initGame() {
  setGameState(Game::GameState::GAME_START);
}

void Game::startGame(std::vector<PlayerType> playerTypes) {
  assert(playerTypes.size() == players_.size());

  for (size_t i = 0; i < players_.size(); i++) {
    players_[i].setPlayerType(playerTypes[i]); 
  }

  // reset scores
  for (size_t i = 0; i < players_.size(); i++) {
    players_[i].resetScore();
  }

  startRound();
}

void Game::startRound() {
  // update scores
  for (int i = 0; i < PLAYER_COUNT; i++) {
    players_[i].updateScore();
  }

  // check if game is over
  for (int i = 0; i < PLAYER_COUNT; i++) {
    if (players_[i].getScore() >= MAX_SCORE) {
      setGameState(GameState::GAME_END);
      return;
    }
  }

  // shuffle the deck
  deck_.shuffle(seed_);

  // reset the game board
  gameBoard_.resetBoard();

  // assign cards
  for (int i = 0; i < PLAYER_COUNT; i++) {
    players_[i].setCards(deck_.getHand(i));
  }

  // find the player with 7 of spades
  for (int i = 0; i < PLAYER_COUNT; i++) {
    std::vector<Card> playerCards = players_[i].getCards();
    if (std::find(playerCards.begin(), playerCards.end(), SEVEN_OF_SPADES) != playerCards.end()) {
      currentPlayer_ = i;
      break;
    }
  }

  setGameState(GameState::ROUND_START);
  runRound();
}

void Game::runRound() {
  // if the current player has no more cards in their hand, then the current round is over
  if (getCurrentPlayerCards().empty()) {
    setGameState(GameState::ROUND_END);
    startRound();
  }

  // if the current player is a human player, then request user input
  else if (players_[currentPlayer_].getPlayerType() == PlayerType::HUMAN) {
    setGameState(GameState::HUMAN_INPUT);
  }

  // else the current player is a computer player
  else {
    std::vector<Card> validCards = getCurrentPlayerValidCards();

    // if no valid cards, discard first valid card
    if (validCards.empty()) {
      discardCard(getCurrentPlayerCards()[0]);
    }

    // play first valid card
    else {
      playCard(validCards[0]);
    }
  }
}

void Game::setSeed(int seed) {
  seed_ = seed;
}
