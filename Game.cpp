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

const Card SEVEN_OF_SPADES = Card(SPADE, SEVEN);

Game::Game(int seed, std::vector<PlayerType> playerTypes, Observer *userInterface):
  seed_(seed), userInterface_(userInterface), gameState_(GameState::ROUND_START),
  lastCard_(Card(SPADE, ACE))
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
    for (int j = 0; j < RANK_COUNT; j++)
      deck_.push_back(Card((Suit)i, (Rank)j));
}

std::vector<Straight> Game::getStraights() const {
  return straights_;
}

std::vector<Player> Game::getPlayers() const {
  return players_;
}

std::vector<int> Game::getWinners() const {
  int minScore = players_[0].getScore();
  for (int i = 1; i < PLAYER_COUNT; i++) {
    minScore = std::min(minScore, players_[i].getScore());
  }

  std::vector<int> winners;
  for (int i = 0; i < PLAYER_COUNT; i++) {
    if (minScore == players_[i].getScore()) {
      winners.push_back(i + 1);
    }
  }

  return winners;
}

int Game::getCurrentPlayer() const {
  return currentPlayer_ + 1;
}

Card Game::getLastCard() const {
  return lastCard_;
}

std::vector<Card> Game::getCurrentPlayerCards() const {
  return players_[currentPlayer_].getCards();
}

std::vector<Card> Game::getCurrentPlayerValidCards() const {
  std::vector<Card> validCards = players_[currentPlayer_].getCards();
  if (std::find(validCards.begin(), validCards.end(), SEVEN_OF_SPADES) != validCards.end()) {
    return { SEVEN_OF_SPADES };
  } else {
    validCards.erase(
      std::remove_if(
        validCards.begin(),
        validCards.end(),
        [this](const Card &card) {
          Suit suit = card.getSuit();
          return !straights_[suit].canPlayCard(card);
        }
      ),
      validCards.end()
    );
  }
  return validCards;
}

std::vector<Card> Game::getDeck() const {
  return deck_;
}

Game::GameState Game::getGameState() const {
  return gameState_;
}

void Game::startRound() {
  // update scores
  for (int i = 0; i < PLAYER_COUNT; i++) {
    players_[i].updateScore();
  }

  // check if game is over
  for (int i = 0; i < PLAYER_COUNT; i++) {
    if (players_[i].getScore() >= MAX_SCORE) {
      gameState_ = GameState::GAME_END;
      notify();
      return;
    }
  }

  // shuffle the deck
  static std::mt19937 rng(seed_);
  int n = CARD_COUNT;
  while (n > 1) {
    int k = (int)(rng() % n--);
    std::swap(deck_[k], deck_[n]);
  }

  // reset straights
  for (int i = 0; i < SUIT_COUNT; i++) {
    straights_[i] = Straight((Suit)i);
  }

  // assign cards
  std::vector<Card> currentHand;
  for (int i = 0; i < PLAYER_COUNT; i++) {
    for (int j = 0; j < CARD_COUNT / PLAYER_COUNT; j++) {
      currentHand.push_back(deck_[13 * i + j]);
    }
    players_[i].setCards(currentHand);
    currentHand.clear();
  }

  // find the player with 7 of spades
  for (int i = 0; i < PLAYER_COUNT; i++) {
    std::vector<Card> playerCards = players_[i].getCards();
    if (std::find(playerCards.begin(), playerCards.end(), SEVEN_OF_SPADES) != playerCards.end()) {
      currentPlayer_ = i;
      break;
    }
  }

  gameState_ = GameState::ROUND_START;
  notify();
  runRound();
}

void Game::executeCommand(Command command) {
  switch (command.type) {
    case PLAY: {
      Suit suit = command.card.getSuit();
      std::vector<Card> validCards = getCurrentPlayerValidCards();
      bool isValidMove = straights_[suit].canPlayCard(command.card) &&
        std::find(validCards.begin(), validCards.end(), command.card) != validCards.end();

      if (isValidMove) {
        straights_[suit].playCard(command.card);
        players_[currentPlayer_].playCard(command.card);
        gameState_ = GameState::PLAYED_CARD;
        lastCard_ = command.card;
        notify();
        currentPlayer_ = (currentPlayer_ + 1) % 4;
        runRound();
      } else {
        gameState_ = GameState::INVALID_PLAY_INPUT;
        notify();
      }

      break;
    }


    case DISCARD: {
      std::vector<Card> cards = getCurrentPlayerCards();
      if (getCurrentPlayerValidCards().empty() && std::find(cards.begin(), cards.end(), command.card) != cards.end()) {
        players_[currentPlayer_].discardCard(command.card);
        gameState_ = GameState::DISCARDED_CARD;
        lastCard_ = command.card;
        notify();
        currentPlayer_ = (currentPlayer_ + 1) % 4;
        runRound();
      } else {
        gameState_ = GameState::INVALID_DISCARD_INPUT;
        notify();
      }

      break;
    }

    case RAGEQUIT:
      players_[currentPlayer_].setPlayerType(PlayerType::COMPUTER);
      runRound();
      break;

    default:
      assert(false);
  }
}

void Game::notify() {
  userInterface_->update();
}

void Game::runRound() {
  if (getCurrentPlayerCards().empty()) {
    gameState_ = GameState::ROUND_END;
    notify();
    startRound();
  } else if (players_[currentPlayer_].getPlayerType() == PlayerType::COMPUTER) {
    std::vector<Card> validCards = getCurrentPlayerValidCards();

    // if no valid cards, discard first valid card
    if (validCards.empty()) {
      Card card = getCurrentPlayerCards()[0];
      players_[currentPlayer_].discardCard(card);
      lastCard_ = card;
      gameState_ = GameState::DISCARDED_CARD;
    } else {
      players_[currentPlayer_].playCard(validCards[0]);
      straights_[validCards[0].getSuit()].playCard(validCards[0]);
      lastCard_ = validCards[0];
      gameState_ = GameState::PLAYED_CARD;
    }
    notify();
    currentPlayer_ = (currentPlayer_ + 1) % 4;
    runRound();
  } else {
    gameState_ = GameState::HUMAN_INPUT;
    notify();
  }
}
