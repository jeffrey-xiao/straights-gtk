#include "Card.h"
#include "Command.h"
#include "Game.h"
#include "Observer.h"
#include "Player.h"
#include "Straight.h"

#include <algorithm>
#include <cassert>
#include <random>
#include <vector>

const Card SEVEN_OF_SPADES = Card((Suit)CLUB, (Rank)SEVEN);

Game::Game(int seed, std::vector<PlayerType> playerTypes, Observer *userInterface):
  seed_(seed), userInterface_(userInterface), gameState_(GameState::ROUND_START)
{
  assert(playerTypes.size() == PLAYER_COUNT);

  // treating vectors like static arrays by reserving space
  // we opted to use vectors since objects do not have default constructors
  players_.reserve(PLAYER_COUNT);
  straights_.reserve(STRAIGHT_COUNT);
  deck_.reserve(CARD_COUNT);

  for (int i = 0; i < PLAYER_COUNT; i++)
    players_.push_back(Player(playerTypes[i]));

  for (int i = 0; i < STRAIGHT_COUNT; i++)
    straights_.push_back(Straight((Suit)i));

  for (int i = 0; i < SUIT_COUNT; i++)
    for (int j = 0; j < CARD_COUNT; j++)
      deck_.push_back(Card((Suit)i, (Rank)j));
}

std::vector<Straight> Game::getStraights() const {
  return straights_;
}

std::vector<Player> Game::getPlayers() const {
  return players_;
}

std::vector<Card> Game::getCurrentPlayerCards() const {
  return players_[currentPlayer_].getCards();
}

std::vector<Card> Game::getCurrentPlayerValidCards() const {
  std::vector<Card> validCards = players_[currentPlayer_].getCards();
  std::remove_if(
    validCards.begin(),
    validCards.end(),
    [this](const Card &card) {
      Suit suit = card.getSuit();
      return straights_[suit].getHiRank() != card.getRank() - 1 &&
        straights_[suit].getLoRank() != card.getRank() + 1;
    }
  );
  return validCards;
}

std::vector<Card> Game::getDeck() const {
  return deck_;
}

void Game::startRound() {
  // check if game is over
  for (int i = 0; i < PLAYER_COUNT; i++) {
    if (players_[currentPlayer_].getScore() >= MAX_SCORE) {
      gameState_ = GameState::GAME_END;
      notify();
      break;
    }
  }

  // shuffle the deck
  static std::mt19937 rng(seed_);
  int n = CARD_COUNT;
  while (n > 0) {
    int k = (int)(rng() % n--);
    std::swap(deck_[k], deck_[n]);
  }

  // find the player with 7 of spades
  for (int i = 0; i < PLAYER_COUNT; i++) {
    std::vector<Card> playerCards = players_[i].getCards();
    if (std::find(playerCards.begin(), playerCards.end(), SEVEN_OF_SPADES) != playerCards.end()) {
      currentPlayer_ = i;
      break;
    }
  }

  notify();
  runRound();
}

// TODO: check if hand has card before discarding or playing
void Game::executeCommand(Command command) {
  switch (command.type) {
    case PLAY:
      Suit suit = command.card.getSuit();
      Rank rank = command.card.getRank();
      bool isValidMove = false;

      if (straights_[suit].getHiRank() == rank - 1) {
        straights_[suit].setHiRank(rank);
        isValidMove = true;
      }

      if (straights_[suit].getLoRank() == rank + 1) {
        straights_[suit].setLoRank(rank);
        isValidMove = true;
      }

      if (isValidMove) {
        players_[currentPlayer_].playCard(command.card);
        gameState_ = GameState::PLAYED_CARD;
        notify();
        currentPlayer_ = (currentPlayer_ + 1) % 4;
        runRound();
      } else {
        gameState_ = GameState::INVALID_HUMAN_INPUT;
        notify();
      }

      break;

    case DISCARD:
      if (getCurrentPlayerValidCards().size() == 0) {
        players_[currentPlayer_].discardCard(command.card);
        gameState_ = GameState::DISCARDED_CARD;
        notify();
        currentPlayer_ = (currentPlayer_ + 1) % 4;
        runRound();
      } else {
        gameState_ = GameState::INVALID_HUMAN_INPUT;
      }

      break;

    case RAGEQUIT:
      players_[currentPlayer_].setPlayerType(PlayerType::COMPUTER);
      runRound();
      break;

    default:
      throw "Not Implemented";
  }
}

void Game::notify() {
  userInterface_->update();
}

void Game::runRound() {
  if (getCurrentPlayerCards().size() == 0) {
    gameState_ = GameState::ROUND_END;
    notify();
    startRound();
  } else if (players_[currentPlayer_].getPlayerType() == PlayerType::COMPUTER) {
    std::vector<Card> validCards = getCurrentPlayerValidCards();

    // if no valid cards, discard first valid card
    if (validCards.size() == 0) {
      Card card = getCurrentPlayerCards()[0];
      players_[currentPlayer_].discardCard(card);
      gameState_ = GameState::PLAYED_CARD;
    } else {
      players_[currentPlayer_].playCard(validCards[0]);
      gameState_ = GameState::DISCARDED_CARD;
    }
    notify();
    currentPlayer_ = (currentPlayer_ + 1) % 4;
    runRound();
  } else {
    gameState_ = GameState::HUMAN_INPUT;
    notify();
  }
}
