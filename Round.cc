#include <algorithm>
#include <random>
#include <stdexcept>

#include "Round.h"
#include "PublicInfo.h"
#include "const.h"

Round::Round(int nplayers, int starting_player,
             std::default_random_engine rng,
             const int tokens[], bool verbose)
    : info_(nplayers, starting_player, tokens), drawn_(UNKNOWN), verbose_(verbose) {

    turn_ = 0;
    for (int card = GUARD; card <= PRINCESS; ++card) {
        for (int i = 0; i < quantity(Card(card)); ++i) {
            deck_[info_.deckSize_++] = (Card) card;
        }
    }

    std::shuffle(deck_, &deck_[16], rng);

    burn_ = drawCard();

    for (int i = 0; i < nplayers; ++i) {
        hands_[i] = drawCard();
    }
}

const PublicInfo& Round::getPublicInfo() const {
    return info_;
}

bool Round::isOver() const {
    return
        info_.livePlayers() <= 1 ||
        info_.deckSize_ == 0;
}

int Round::getWinner() const {
    int live_players = info_.livePlayers();

    if (live_players == 1) {
        for (int i = 0; i < info_.totalPlayers_; ++i) {
            if (info_.live_[i]) {
                return i;
            }
        }
    } else if (info_.deckSize_ == 0) {
        int winners[live_players];
        int num_winners = 0;
        Card high_card = UNKNOWN;

        for (int i = 0; i < info_.totalPlayers_; ++i) {
            if (!info_.live_[i]) {
                continue;
            }

            if (int(hands_[i]) > int(high_card)) {
                num_winners = 1;
                winners[0] = i;
                high_card = hands_[i];
            } else if (int(hands_[i] == int(high_card))) {
                winners[num_winners++] = i;
            }
        }

        if (num_winners == 1) {
            return winners[0];
        }

        // In case of a tie, sum all cards played or discarded. High
        // sum wins.
        int real_winner = 0;
        int high_sum = 0;
        for (int i = 0; i < num_winners; ++i) {
            int sum = info_.sumCards(winners[i]);
            // If two people have the same sum, the younger player
            // wins. We'll say that's the player with the lower id
            // number.
            if (sum > high_sum) {
                real_winner = winners[i];
                high_sum = sum;
            }
        }

        return real_winner;
    }

    throw std::logic_error("Called getWinner before the round finished.");
}

void Round::printHands() const {
    for (int i = 0; i < info_.totalPlayers_; ++i) {
        if (info_.live_[i]) {
            printf("Player %d: %s\n", i, name_of_card(hands_[i]));
        } else {
            printf("[Player %d is out of the game]\n", i);
        }
    }
    printf("\n");
}

void Round::printDeck() const {
    for (int i = 0; i < info_.deckSize_; ++i) {
        printf("%s\n", name_of_card(deck_[i]));
    }
    printf("\n");
}

void Round::discard(History& history, int source_player, int target_player) {
    if (target_player == NOBODY) {
        throw std::out_of_range("Tried to make NOBODY discard");
    }

    history.push_back(new DiscardEvent(turn_, source_player, target_player,
                                       hands_[target_player]));

    if (hands_[target_player] == PRINCESS && info_.live_[target_player]) {
        killPlayer(history, target_player);
    }

    hands_[target_player] = UNKNOWN;
}

Card Round::drawCard() {
    return info_.deckSize_ > 0 ? deck_[--info_.deckSize_] : burn_;
}

Choice Round::startTurn() {
    int player = info_.activePlayer_;
    info_.handmaiding_[player] = false;

    if (drawn_ == UNKNOWN) {
        drawn_ = drawCard();
    }

    return Choice(info_.turn_, player, hands_[player], drawn_);
}

bool Round::completeTurn(
    History& history,
    const Choice& choice
    ) {

    History events;
    int player = info_.activePlayer_;

    if (choice.player_ != player || !info_.legalMove(choice)) {
        return false;
    }

    drawn_ = UNKNOWN;
    events.push_back(new ActionEvent(turn_, player, choice.action_));

    const Action& action = *choice.action_;

    if (action.card_ == choice.holding_) {
        hands_[player] = choice.drawn_;
    }

    switch (action.card_) {
    case UNKNOWN:
        printf("Tried to play an UNKNOWN card!\n");
        exit(1);
        break;
    case HANDMAID:
        info_.handmaiding_[player] = true;
        break;
    case COUNTESS:
        break;
    case PRINCESS:
        killPlayer(events, player);
        break;
    default:
        break;
    }

    switch (action.card_) {
    case GUARD:
    case PRIEST:
    case BARON:
    case PRINCE:
    case KING:
        resolveTargetedAction(events, player, (const TargetedAction&) action);
    default:
        break;
    }

    for (auto& e : events) {
        history.push_back(e);
        info_.history_.push_back(e);
    }

    info_.nextPlayer();
    return true;
}

void Round::resolveTargetedAction(History& events, int player,
                                  const TargetedAction& action) {
    int target = action.targetPlayer_;
    if (target == NOBODY) {
        return;
    }

    switch (action.card_) {
    case GUARD:
    {
        const GuardAction& guard_action = (const GuardAction&) action;
        if (hands_[target] == guard_action.cardNamed_) {
            killPlayer(events, target);
        }
    }
        break;
    case PRIEST:
        break;
    case BARON:
        if (hands_[target] == hands_[player]) {
            break;
        }
        killPlayer(events, hands_[target] < hands_[player] ? target : player);
        break;
    case PRINCE:
        discard(events, player, target);
        if (info_.live_[target]) {
            hands_[target] = drawCard();
        }
        break;
    case KING:
    {
        Card temp = hands_[target];
        hands_[target] = hands_[player];
        hands_[player] = temp;
        break;
    }
    default:
        break;
    }
}

void Round::killPlayer(History& events, int player) {
    info_.live_[player] = false;

    events.push_back(new DeathEvent(turn_, player, hands_[player]));

    // The ousted player reveals their final card, unless that card
    // was already played.
    if (hands_[player] != PRINCESS) {
        discard(events, player, player);
    }

    if (verbose_) {
        printf("Player %d is out of the game!\n", player);
    }
}
