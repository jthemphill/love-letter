#include "PublicInfo.h"

PublicInfo::PublicInfo(int starting_player, int num_players)
    : turn_(0), activePlayer_(starting_player), totalPlayers_(num_players),
      deckSize_(0) {
    for (int i = 0; i < num_players; ++i) {
        tokens_[i] = 0;
        handmaiding_[i] = false;
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

    if (card != choice.holding_ && card != choice.drawn_) {
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
        // If no target, make sure no one else is targetable
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
        (countess_caught(choice.holding_, choice.drawn_) ||
         countess_caught(choice.drawn_, choice.holding_))
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

int PublicInfo::targetablePlayers() const {
    int count = 0;
    for (int i = 0; i < totalPlayers_; ++i) {
        if (canTarget(i)) {
            ++count;
        }
    }
    return count;
}

bool PublicInfo::canTarget(int player) const {
    if (!live_[player] || handmaiding_[player]) {
        return false;
    }

    return true;
}

int PublicInfo::sumCards(int player) const {
    const ActionEvent* ae = NULL;
    const DiscardEvent* de = NULL;

    int sum = 0;
    for (const Event* e : history_) {
        switch (e->type_) {
        case Event::DISCARD:
            de = (const DiscardEvent*) e;
            if (de->sourcePlayer_ == player) {
                sum += int(de->cardDiscarded_);
            }
            break;
        case Event::ACTION:
            ae = (const ActionEvent*) e;
            if (ae->sourcePlayer_ == player) {
                sum += int(ae->action_.played_);
            }
            break;
        default:
            break;;
        }
    }

    return sum;
}
