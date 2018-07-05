#include "Card.h"
#include "Command.h"
#include "GameController.h"
#include "Player.h"
#include "Straight.h"
#include "TextUserInterface.h"

#include <cassert>
#include <iostream>
#include <vector>

void TextUserInterface::update() {
  using namespace std;

  Game::GameState gameState = gameController_->getGameState();

  switch (gameState) {
    case Game::GameState::ROUND_START:
      cout << "A new round begins. It's player " << gameController_->getCurrentPlayer()
        << "'s turn to play." << endl;
      break;

    case Game::GameState::HUMAN_INPUT: {
      cout << "Cards on the table:" << endl;
      for (Straight straight : gameController_->getStraights()) {
        cout << straight << endl;
      }

      vector<Card> cards = gameController_->getCurrentPlayerCards();
      cout << "Your hand: ";
      for (size_t i = 0; i < cards.size(); i++) {
        cout << cards[i];
        if (i != cards.size() - 1) {
          cout << " ";
        }
      }
      cout << endl;

      vector<Card> legalPlays = gameController_->getCurrentPlayerValidCards();
      cout << "Legal plays:";
      if (!legalPlays.empty()) {
        cout << " ";
      }
      for (size_t i = 0; i < legalPlays.size(); i++) {
        cout << legalPlays[i];
        if (i != legalPlays.size() - 1) {
          cout << " ";
        }
      }
      cout << endl;

      getUserCommand();
      break;
    }

    case Game::GameState::INVALID_PLAY_INPUT:
      cout << "This is not a legal play." << endl;
      getUserCommand();
      break;

    case Game::GameState::INVALID_DISCARD_INPUT:
      cout << "You have a legal play. You may not discard." << endl;
      getUserCommand();
      break;

    case Game::GameState::DISCARDED_CARD:
      cout << "Player " << gameController_->getCurrentPlayer() << " discards "
        << gameController_->getLastCard() << "." << endl;
      break;

    case Game::GameState::PLAYED_CARD:
      cout << "Player " << gameController_->getCurrentPlayer() << " plays "
        << gameController_->getLastCard() << "." << endl;
      break;

    case Game::GameState::ROUND_END: {
      vector<Player> players = gameController_->getPlayers();
      for (size_t i = 0; i < players.size(); i++) {
        vector<Card> discards = players[i].getDiscardedCards();
        cout << "Player " << i + 1 << "'s discards:";
        if (!discards.empty()) {
          cout << " ";
        }
        for (size_t j = 0; j < discards.size(); j++) {
          cout << discards[j];
          if (j != discards.size() - 1) {
            cout << " ";
          }
        }
        cout << endl;

        int score = players[i].getScore();
        int roundScore = players[i].getRoundScore();
        cout << "Player " << i + 1 << "'s score: " << score << " + " << roundScore << " = "
          << score + roundScore << endl;
      }
      break;
    }

    case Game::GameState::GAME_END:
      for (int winner : gameController_->getWinners()) {
        cout << "Player " << winner << " wins!" << endl;
      }
      break;

    default:
      assert(false);
  }
}

void TextUserInterface::getUserCommand() {
  Command command;
  std::cout << ">";
  std::cin >> command;

  switch (command.type) {
    case RAGEQUIT:
      std::cout << "Player " << gameController_->getCurrentPlayer()
        << " ragequits. A computer will now take over." << std::endl;
    case PLAY:
    case DISCARD:
      gameController_->executeCommand(command);
      break;

    case DECK: {
      std::vector<Card> deck = gameController_->getDeck();

      for (size_t i = 0; i < deck.size(); i++) {
        if ((i + 1) % RANK_COUNT == 0) {
          std::cout << deck[i] << std::endl;
        } else {
          std::cout << deck[i] << " ";
        }
      }

      getUserCommand();
      break;
    }

    case QUIT:
      break;

    default:
      assert(false);
  }
}

void TextUserInterface::setGameController(GameController *gameController) {
  gameController_ = gameController;
}
