#include <stdexcept>

#include "GuardBot.h"
#include "PublicInfo.h"
#include "const.h"

GuardBot::GuardBot(const PublicInfo& info, int seed, int player)
  : info_(info), player_(player), random_(seed) {}

void GuardBot::addEvent(const Event& event) {
    events_.push_back(&event);
}

const Action* GuardBot::makeChoice(Card hand_card, Card drawn_card) {
    if (countess_caught(hand_card, drawn_card) ||
        countess_caught(drawn_card, hand_card)) {
        return new Action(COUNTESS);
    }

    Card lower_card;
    if (hand_card <= drawn_card) {
        lower_card = hand_card;
    } else {
        lower_card = drawn_card;
    }

    switch (lower_card) {
    case GUARD:
    {
        int target = random_.target(info_, player_, false);
        Card named_card = chooseCardToName(hand_card, drawn_card);
        return new GuardAction(target, named_card);
    }
    case PRIEST:
    case BARON:
    case KING:
    {
        int target = random_.target(info_, player_, false);
        return new TargetedAction(lower_card, target);
    }
    case PRINCE:
    {
        int target = random_.target(info_, player_, true);
        return new TargetedAction(lower_card, target);
    }
    default:
        return new Action(lower_card);
    }
}

Card GuardBot::chooseCardToName(Card hand_card, Card drawn_card) {
    int num_revealed = 0;
    int unseen_cards[9];
    for (int i = int(UNKNOWN); i <= int(PRINCESS); ++i) {
        unseen_cards[i] = QUANTITIES[i];
    }

    for (auto e : events_) {
        switch (e->type_) {
        case Event::DISCARD:
        {
            const DiscardEvent& discard_event = *(DiscardEvent*) e;
            if (discard_event.cardDiscarded_ > PRINCESS ||
                discard_event.cardDiscarded_ < GUARD) {
              throw std::range_error("Not a card");
            }
            --unseen_cards[discard_event.cardDiscarded_];
            ++num_revealed;
            break;
        }
        case Event::ACTION:
        {
            const ActionEvent& action_event = *(ActionEvent*) e;
            if (action_event.action_->card_ > PRINCESS ||
                action_event.action_->card_ < GUARD) {
              throw std::range_error("Not a card");
            }
            --unseen_cards[action_event.action_->card_];
            ++num_revealed;
            break;
        }
        case Event::DEATH:
        case Event::REVEALED:
            break;
        }
    }

    --unseen_cards[hand_card];
    --unseen_cards[drawn_card];

    int num_unseen_cards = 0;
    for (int i = GUARD; i <= PRINCESS; ++i) {
        if (unseen_cards[i] < 0 || unseen_cards[i] > quantity(Card(i))) {
            printf("I count %d %s cards.\n", unseen_cards[i], name_of_card((Card) i));
            throw std::domain_error("Leaving.");
        }
        num_unseen_cards += unseen_cards[i];
    }

    int unseen_non_guards = num_unseen_cards - unseen_cards[GUARD];

    // If there are only guards left in the game, we have to waste it.
    if (unseen_non_guards == 0) {
      return PRINCESS;
    } else if (unseen_non_guards < 0) {
      throw std::domain_error("Negative cards???");
    }

    int choice = random_.roll(0, unseen_non_guards);
    if (choice > num_unseen_cards) {
      throw std::range_error("Good to go.");
    }
    Card named_card = PRINCESS;
    int i = 0;
    while (true) {
      if (i++ > 100) {
        throw std::range_error("Loop");
      }

      if (choice > num_unseen_cards) {
        throw std::range_error("Good to go.");
      }

        if (named_card == UNKNOWN) {
            throw std::range_error("Made it to UNKNOWN");
        }

        if (unseen_cards[named_card] == 0) {
            named_card = Card(int(named_card) - 1);
        } else {
            --unseen_cards[named_card];
        }

        if (choice == 0) {
            break;
        }

        --choice;
    }

    return named_card;
}
