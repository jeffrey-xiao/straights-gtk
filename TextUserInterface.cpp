#include "TextUserInterface.h"
#include "Game.h"
#include "Straight.h"
#include "Card.h"
#include "Player.h"
#include "Command.h"
#include <vector>
#include <iostream>
#include <assert.h>

TextUserInterface::TextUserInterface() {}

void TextUserInterface::update() {
  Game::GameState gameState = game_->getGameState();

  using namespace std;

  switch (gameState) {
    case Game::GameState::ROUND_START:
      cout << "A new round begins. It's player " << game_->getCurrentPlayer() << "'s turn to play." << endl;
      break;
    case Game::GameState::HUMAN_INPUT:
      {
        cout << "Cards on the table:" << endl;
        for (Straight straight : game_->getStraights()) {
          cout << straight << endl;
        }
        vector<Card> cards = game_->getCurrentPlayerCards();
        cout << "Your hand: ";
        for (size_t i = 0; i < cards.size(); i++) {
          if(i != cards.size() - 1) {
            cout << cards[i] << " ";
          } else {
            cout << cards[i] << endl;
          }
        }

        vector<Card> legalPlays = game_->getCurrentPlayerValidCards();
        cout << "Legal plays: ";
        for (size_t i = 0; i < legalPlays.size(); i++) {
          if(i != legalPlays.size() - 1) {
            cout << legalPlays[i] << " ";
          } else {
            cout << legalPlays[i] << endl;
          }
        }
        getUserCommand();
      }
      break;

    case Game::GameState::INVALID_PLAY_INPUT:
      cout << "This is not a legal play." << endl;

      getUserCommand();
      break;

    case Game::GameState::INVALID_DISCARD_INPUT:
      cout << "You have a legal play. You may not discard." << endl;

      getUserCommand();
      break;

    case Game::GameState::DISCARDED_CARD:
      cout << "Player " << game_->getCurrentPlayer() << " discards " << game_->getLastCard() << endl;
      break;
    case Game::GameState::PLAYED_CARD:
      cout << "Player " << game_->getCurrentPlayer() << " plays " << game_->getLastCard() << endl;
      break;

    case Game::GameState::ROUND_END:
      {
        vector<Player> players = game_->getPlayers();
        for (size_t i = 0; i < players.size(); i++) {
          cout << "Player " << i + 1 << "'s discards: ";

          vector<Card> discards = players[i].getDiscardedCards();

          for (size_t j = 0; j < discards.size(); j++) {
            if (j == discards.size() - 1) {
              cout << discards[i] << endl;
            } else {
              cout << discards[i] << " ";
            }
          }
          // TODO: Print score
          cout << "Player " << i + 1 << "'s score: ";

        }
      }
      break;

    case Game::GameState::GAME_END:
      // TODO: Print winners
      break;
    default:
      assert(false);
  }
}

void TextUserInterface::getUserCommand() {
  Command command;
  std::cin >> command;

  switch (command.type) {
    case PLAY:
    case DISCARD:
    case RAGEQUIT:
      game_->executeCommand(command);
      break;
    case DECK:
      {
        std::vector<Card> deck = game_->getDeck();

        for (size_t i = 0; i < deck.size(); i++) {
          if ((i + 1) % 13 == 0) {
            std::cout << deck[i] << std::endl;
          } else {
            std::cout << deck[i] << " ";
          }
        }
      }
      break;
    case QUIT:
      break;
    default:
      assert(false);
  }
}

void TextUserInterface::setGame(Game * game) {
  game_ = game;
}
