#include "Command.h"
#include "GameController.h"
#include "TextUserInterface.h"

#include <cassert>
#include <iostream>
#include <vector>

void TextUserInterface::update() {
  using namespace std;

  Game::GameState gameState = gameController_->getGameState();

  // Update the view to reflect the Game's state
  switch (gameState) {
    // Notify the user that a round is starting
    case Game::GameState::ROUND_START:
      cout << "A new round begins. It's player " << gameController_->getCurrentPlayer()
        << "'s turn to play." << endl;
      break;

    // Notify the user that it is a Human player's turn
    case Game::GameState::HUMAN_INPUT: {
      cout << gameController_->getGameBoard();

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
      break;
    }

    // Notify the user that they have attempted to play an invalid card
    case Game::GameState::INVALID_PLAY_INPUT:
      cout << "This is not a legal play." << endl;
      break;

    // Notify the user that they have attempted to discard an invalid card.
    case Game::GameState::INVALID_DISCARD_INPUT:
      cout << "You have a legal play. You may not discard." << endl;
      break;

    // Notify the user that a player has discarded a card
    case Game::GameState::DISCARDED_CARD:
      cout << "Player " << gameController_->getCurrentPlayer() << " discards "
        << gameController_->getLastCard() << "." << endl;
      break;

    // Notify the user that a player has played a card
    case Game::GameState::PLAYED_CARD:
      cout << "Player " << gameController_->getCurrentPlayer() << " plays "
        << gameController_->getLastCard() << "." << endl;
      break;

    // Notify the user that a round has ended
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

    // Notify the user that the game has ended and print results
    case Game::GameState::GAME_END:
      for (int winner : gameController_->getWinners()) {
        cout << "Player " << winner << " wins!" << endl;
      }
      break;

    default:
      assert(false);
  }
}

void TextUserInterface::startGame() {
  gameController_->startGame();

  // While the game is still in progress, read in user commands
  while (gameController_->getGameState() != Game::GameState::GAME_END) {
    Command command;
    std::cout << ">";
    std::cin >> command;

    switch (command.type) {
      // Set the current player to be controlled by the computer
      case RAGEQUIT:
        std::cout << "Player " << gameController_->getCurrentPlayer()
          << " ragequits. A computer will now take over." << std::endl;

      // Tell the game to play/discard a card
      case PLAY:
      case DISCARD:
        gameController_->executeCommand(command);
        break;

      // Print the order of the cards in the deck
      case DECK: {
        Deck deck = gameController_->getDeck();

        for (int i = 0; i < SUIT_COUNT; i++) {
          for (int j = 0; j < RANK_COUNT; j++) {
            std::cout << deck[i * RANK_COUNT + j];
            if (j != RANK_COUNT - 1) {
              std::cout << " ";
            }
          }
          std::cout << std::endl;
        }

        break;
      }

      // Terminate the game
      case QUIT:
        return;

      default:
        assert(false);
    }
  }
}

void TextUserInterface::setGameController(GameController *gameController) {
  gameController_ = gameController;
}
