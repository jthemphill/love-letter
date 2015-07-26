#include <algorithm>
#include <random>

#include "Env.hpp"
#include "types.hpp"
#include "util.hpp"

PublicInfo::PublicInfo(int starting_player, int num_players)
    : turn_(0), activePlayer_(starting_player), totalPlayers_(num_players),
      deckSize_(0) {
    for (int i = 0; i < num_players; ++i) {
        tokens_[i] = 0;
        live_[i] = true;
    }
}

void PublicInfo::nextPlayer() {
    int original = activePlayer_;
    do {
        activePlayer_ = (activePlayer_ + 1) % totalPlayers_;
    } while (!live_[activePlayer_] && activePlayer_ != original);

    for (int i = 0; i < totalPlayers_; ++i) {
        if (!live_[i]) {
            continue;
        }

        if (activePlayer_ == i) {
            ++turn_;
        }
        break;
    }
}

bool PublicInfo::legalMove(const Choice& choice) const {
    const Action& action = choice.action_;
    Card card = action.card_;
    int target = action.targetPlayer_;

    if (!action.played_ || card == UNKNOWN) {
        return false;
    }

    if (target >= 0) {
        // If there is a target, make sure it's legal
        if (!canTarget(target)) {
            return false;
        }

        switch (card) {
        case GUARD:
        case PRIEST:
        case BARON:
        case KING:
            if (target == choice.player_) {
                return false;
            }
            break;
        default:
            break;
        }
    } else {
        switch (card) {
        case GUARD:
        case PRIEST:
        case BARON:
        case PRINCE:
        case KING:
            for (int i = 0; i < totalPlayers_; ++i) {
                if (i != choice.player_ && canTarget(i)) {
                    return false;
                }
            }
            break;
        default:
            break;
        }
    }

    // Countess rule
    if (card != COUNTESS &&
        (countessCaught(choice.holding_, choice.drawn_) ||
         countessCaught(choice.drawn_, choice.holding_))
        ) {
        return false;
    }

    return true;
}

int PublicInfo::livePlayers() const {
    int count = 0;
    for (bool is_live : live_) {
        if (is_live) {
            ++count;
        }
    }
    return count;
}

bool PublicInfo::canTarget(int player) const {
    if (!live_[player]) {
        return false;
    }

    // TODO handmaid
    return true;
}

Env::Env(int starting_player, int num_players, bool verbose)
    : env_(starting_player, num_players), drawn_(UNKNOWN), verbose_(verbose) {
    for (int card = GUARD; card <= PRINCESS; ++card) {
        for (int i = 0; i < quantity(Card(card)); ++i) {
            deck_[env_.deckSize_++] = (Card) card;
        }
    }

    std::shuffle(deck_, &deck_[15], std::default_random_engine());

    burn_ = drawCard();

    for (int i = 0; i < num_players; ++i) {
        hands_[i] = drawCard();
    }
}

const PublicInfo& Env::getPublicInfo() const {
    return env_;
}

int Env::winner() const {
    if (env_.livePlayers() == 1) {
        for (int i = 0; i < env_.totalPlayers_; ++i) {
            if (env_.live_[i]) {
                return i;
            }
        }
    } else if (env_.deckSize_ == 0) {
        int best_player = -1;
        int num_ties = 0;
        Card high_card = UNKNOWN;

        for (int i = 0; i < 4; ++i) {
            if (!env_.live_[i]) {
                continue;
            }

            if (int(hands_[i]) > int(high_card)) {
                num_ties = 0;
                best_player = i;
                high_card = hands_[i];
            } else if (int(hands_[i] == int(high_card))) {
                ++num_ties;
                best_player = -2;
            }
        }

        return best_player;
    }

    return -1;
}

void Env::printHands() const {
    for (int i = 0; i < env_.totalPlayers_; ++i) {
        if (env_.live_[i]) {
            printf("Player %d: %s\n", i, name_of_card(hands_[i]));
        } else {
            printf("[Player %d is out of the game]\n", i);
        }
    }
    printf("\n");
}

void Env::printDeck() const {
    for (int i = 0; i < env_.deckSize_; ++i) {
        printf("%s\n", name_of_card(deck_[i]));
    }
    printf("\n");
}

void Env::discard(int player) {
    if (hands_[player] == PRINCESS) {
        killPlayer(player);
    }

    history_.emplace_back(
        env_.turn_, player, hands_[player], UNKNOWN, Action(hands_[player], false, -1, UNKNOWN));
}

Card Env::drawCard() {
    return env_.deckSize_ > 0 ? deck_[env_.deckSize_--] : burn_;
}

Choice Env::startTurn() {
    int player = env_.activePlayer_;
    if (drawn_ == UNKNOWN) {
        drawn_ = drawCard();
    }

    return Choice(env_.turn_, player, hands_[player], drawn_);
}

bool Env::completeTurn(const Choice& choice) {
    drawn_ = UNKNOWN;
    history_.push_back(choice);

    if (!env_.legalMove(choice)) {
        return false;
    }

    const Action& action = choice.action_;

    int player = env_.activePlayer_;
    int target = action.targetPlayer_;
    Card named = action.cardNamed_;
    Card temp = UNKNOWN;

    switch (action.card_) {
    case UNKNOWN:
        break;
    case GUARD:
        if (hands_[target] == named) {
            killPlayer(target);
        }
        break;
    case PRIEST:
        break;
    case BARON:
        killPlayer(hands_[target] < hands_[player] ? target : player);
        break;
    case HANDMAID:
        break;
    case PRINCE:
        discard(target);
        hands_[target] = drawCard();
        break;
    case KING:
        temp = hands_[target];
        hands_[target] = hands_[player];
        hands_[player] = temp;
        break;
    case COUNTESS:
        break;
    case PRINCESS:
        killPlayer(player);
        break;
    }

    env_.nextPlayer();
    return true;
}

void Env::killPlayer(int player) {
    env_.live_[player] = false;

    if (verbose_) {
        printf("Player %d is out of the game!\n", player);
    }
}
