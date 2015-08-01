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
    const Action* action = choice.action_;
    Card card = action->card_;

    if (card == UNKNOWN) {
        return false;
    }

    if (card != choice.holding_ && card != choice.drawn_) {
        return false;
    }

    switch (card) {
    case GUARD:
    case PRIEST:
    case BARON:
    case PRINCE:
    case KING:
        if (!legalTarget(choice.player_, *((const TargetedAction*) action))) {
            return false;
        }
        break;
    default:
        break;
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

bool PublicInfo::legalTarget(int source_player,
                             const TargetedAction& action) const {
    int target = action.targetPlayer_;

    if (target == source_player) {
        // The prince is the only targeted card that you can target
        // yourself with.
        return action.card_ == PRINCE;
    }

    if (target != NOBODY) {
        if (!canTarget(target)) {
            return false;
        }
    } else {
        // You cannot target nobody with the prince
        if (action.card_ == PRINCE) {
            return false;
        }

        // With any other targeted card, you can target nobody only if
        // no one else is a legal target
        for (int i = 0; i < totalPlayers_; ++i) {
            if (i != source_player && canTarget(i)) {
                return false;
            }
        }
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
    int sum = 0;
    for (auto& e : history_) {
        switch (e->type_) {
        case Event::DISCARD:
        {
            const DiscardEvent& discard_event = *((DiscardEvent *) e);
            if (discard_event.sourcePlayer_ == player) {
                sum += int(discard_event.cardDiscarded_);
            }
            break;
        }
        case Event::ACTION:
        {
            const ActionEvent& action_event = *((ActionEvent *) e);
            if (action_event.sourcePlayer_ == player) {
                sum += int(action_event.action_->card_);
            }
            break;
        }
        default:
            break;;
        }
    }

    return sum;
}
