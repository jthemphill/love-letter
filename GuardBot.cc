#include <stdexcept>

#include "GuardBot.h"
#include "PublicInfo.h"
#include "const.h"

GuardBot::GuardBot(const PublicInfo& info, int player)
    : info_(info), player_(player) {}

void GuardBot::addEvent(const Event& event) {
    events_.push_back(&event);
}

const Action* GuardBot::makeChoice(Card hand_card, Card drawn_card) {
    if (countess_caught(hand_card, drawn_card) ||
        countess_caught(drawn_card, hand_card)) {
        return new Action(COUNTESS);
    }

    Card lower_card;
    Card higher_card;
    if (hand_card <= drawn_card) {
        lower_card = hand_card;
        higher_card = drawn_card;
    } else {
        lower_card = drawn_card;
        higher_card = hand_card;
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
            --unseen_cards[discard_event.cardDiscarded_];
            ++num_revealed;
            break;
        }
        case Event::ACTION:
        {
            const ActionEvent& action_event = *(ActionEvent*) e;
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
        if (unseen_cards[i] < 0) {
            printf("I count %d %s cards.\n", unseen_cards[i], name_of_card((Card) i));
            throw std::domain_error("Leaving.");
        }
        num_unseen_cards += unseen_cards[i];
    }

    int choice = random_.roll(unseen_cards[GUARD], num_unseen_cards - 1);
    Card named_card = PRINCESS;
    while (true) {
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
