#include "TextUserInterface.h"
#include "Game.h"
#include "Straight.h"
#include "Card.h"
#include "Player.h"
#include "Command.h"
#include <vector>
#include <iostream>
#include <assert.h>

void TextUserInterface::update() {
  using namespace std;

  Game::GameState gameState = game_->getGameState();

  switch (gameState) {
    case Game::GameState::ROUND_START:
      cout << "A new round begins. It's player " << game_->getCurrentPlayer() << "'s turn to play."
        << endl;
      break;

    case Game::GameState::HUMAN_INPUT: {
      cout << "Cards on the table:" << endl;
      for (Straight straight : game_->getStraights()) {
        cout << straight << endl;
      }

      vector<Card> cards = game_->getCurrentPlayerCards();
      cout << "Your hand: ";
      for (size_t i = 0; i < cards.size(); i++) {
        cout << cards[i];
        if (i != cards.size() - 1) {
          cout << " ";
        }
      }
      cout << endl;

      vector<Card> legalPlays = game_->getCurrentPlayerValidCards();
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
      cout << "Player " << game_->getCurrentPlayer() << " discards " << game_->getLastCard() << "." << endl;
      break;

    case Game::GameState::PLAYED_CARD:
      cout << "Player " << game_->getCurrentPlayer() << " plays " << game_->getLastCard() << "." << endl;
      break;

    case Game::GameState::ROUND_END: {
      vector<Player> players = game_->getPlayers();
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
      for (int winner : game_->getWinners()) {
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
      std::cout << "Player " << game_->getCurrentPlayer() << " ragequits. A computer will now take over." << std::endl;
    case PLAY:
    case DISCARD:
      game_->executeCommand(command);
      break;

    case DECK: {
      std::vector<Card> deck = game_->getDeck();

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

void TextUserInterface::setGame(Game *game) {
  game_ = game;
}
