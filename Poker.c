#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FACES 13
#define SUITS 4
#define CARDS 52
#define HANDS 10

struct player_chips
{
    unsigned int coinValue1;
    unsigned int coinValue5;
    unsigned int coinValue10;
};
typedef struct player_chips player_chips;

void shuffle(unsigned int deckShuffle[][FACES]);
void initializePlayerChips(player_chips *player_chips);
void drawCardsToPlayer(int *histogram, int *player);
void handValue(int *playerCards, int *playerHandValue, unsigned int deckValuation[][FACES]);
void showPlayerCards(int playerCards[], unsigned int deckCards[][FACES], const char *cardSuit[], const char *cardFace[]);
void showPlayerHandValue(int playerHandValue, const char *handValues[], unsigned int potValue);
void printDeckAndHandForDebug(unsigned int deckDebug[][FACES], int playerCardsDebug[]);
int sumPlayerChips(player_chips playerChipSum, int *sumOfPlayerChips);
void potInitialBet(player_chips *playerChipInitialBet, unsigned int *potPtr, int *houndIn);
void betRoundPlayer(int *playerHoundIn, unsigned int *totalBet, int *personalRoundBet, player_chips *playerChipsRound, unsigned int *potRound, int *endOfBet, int *foldI);
void printCurrentRoundStatus(unsigned int potStatus, int personalRoundStatus, player_chips *playerChipsStatus, unsigned int call);
void betRoundNpc(int *playerHoundIn, unsigned int *totalBet, int *personalRoundBet, player_chips *playerChipsRound, unsigned int *potRound, int npc, int *endOfBet, int *foldI);
void theRoundWinner(int player1HoundIndex, int player2HoundIndex, int player3HoundIndex, int player4HoundIndex, int player5HoundIndex, int *playerHandValue1, int *playerHandValue2, int *playerHandValue3, int *playerHandValue4, int *playerHandValue5, unsigned int potWin, player_chips *player1Chips, player_chips *player2Chips, player_chips *player3Chips, player_chips *player4Chips, player_chips *player5Chips);

int main()
{
    int player1Cards[5] = {0}, player2Cards[5] = {0}, player3Cards[5] = {0}, player4Cards[5] = {0}, player5Cards[5] = {0};
    int player1ChipsSum = 0, player2ChipsSum = 0, player3ChipsSum = 0, player4ChipsSum = 0, player5ChipsSum = 0;
    int personal1Bet = 0, personal2Bet = 0, personal3Bet = 0, personal4Bet = 0, personal5Bet = 0;
    int player1HoundIn = 0, player2HoundIn = 0, player3HoundIn = 0, player4HoundIn = 0, player5HoundIn = 0;
    int player1HandValue = 0, player2HandValue = 0, player3HandValue = 0, player4HandValue = 0, player5HandValue = 0;
    player_chips player1Chips, player2Chips, player3Chips, player4Chips, player5Chips;
    unsigned int deck[SUITS][FACES] = {0};
    int histogramOfDrawCards[CARDS] = {0};
    const char *suits[SUITS] = {"Hearts", "Diamond", "Clubs", "Spades"};
    const char *hands[HANDS] = {"High Card", "Pair", "Two Pair's", "Three of a Kind", "Straight", "Flush", "Full House", "Four of a Kind", "Straight Flush", "Royal Flush"};
    const char *faces[FACES] = {"Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};
    unsigned int pot = 0;
    unsigned int betTotal = 0;
    int endBet = 0;
    int foldIndex = 0;

    initializePlayerChips(&player1Chips);
    initializePlayerChips(&player2Chips);
    initializePlayerChips(&player3Chips);
    initializePlayerChips(&player4Chips);
    initializePlayerChips(&player5Chips);

    srand(time(NULL));

    puts("POKER THE GAME by GigiLucas");
    puts("Press enter to continue...");
    getchar();

    while (sumPlayerChips(player1Chips, &player1ChipsSum) && sumPlayerChips(player2Chips, &player2ChipsSum) && sumPlayerChips(player3Chips, &player3ChipsSum) && sumPlayerChips(player4Chips, &player4ChipsSum) && sumPlayerChips(player5Chips, &player5ChipsSum))
    {

        shuffle(deck);

        potInitialBet(&player1Chips, &pot, &player1HoundIn);
        potInitialBet(&player2Chips, &pot, &player2HoundIn);
        potInitialBet(&player3Chips, &pot, &player3HoundIn);
        potInitialBet(&player4Chips, &pot, &player4HoundIn);
        potInitialBet(&player5Chips, &pot, &player5HoundIn);

        drawCardsToPlayer(histogramOfDrawCards, player1Cards);
        drawCardsToPlayer(histogramOfDrawCards, player2Cards);
        drawCardsToPlayer(histogramOfDrawCards, player3Cards);
        drawCardsToPlayer(histogramOfDrawCards, player4Cards);
        drawCardsToPlayer(histogramOfDrawCards, player5Cards);

        handValue(player1Cards, &player1HandValue, deck);
        handValue(player2Cards, &player2HandValue, deck);
        handValue(player3Cards, &player3HandValue, deck);
        handValue(player4Cards, &player4HandValue, deck);
        handValue(player5Cards, &player5HandValue, deck);

        showPlayerCards(player1Cards, deck, suits, faces);

        showPlayerHandValue(player1HandValue, hands, pot);

        puts("#### START OF THE BET ####");
        do
        {
            printCurrentRoundStatus(pot, personal1Bet, &player1Chips, betTotal);
            getchar();
            betRoundPlayer(&player1HoundIn, &betTotal, &personal1Bet, &player1Chips, &pot, &endBet, &foldIndex);
            if (endBet + foldIndex >= 5)
            {
                break;
            }
            getchar();
            betRoundNpc(&player2HoundIn, &betTotal, &personal2Bet, &player2Chips, &pot, 2, &endBet, &foldIndex);
            if (endBet + foldIndex >= 5)
            {
                break;
            }
            getchar();
            betRoundNpc(&player3HoundIn, &betTotal, &personal3Bet, &player3Chips, &pot, 3, &endBet, &foldIndex);
            if (endBet + foldIndex >= 5)
            {
                break;
            }
            getchar();
            betRoundNpc(&player4HoundIn, &betTotal, &personal4Bet, &player4Chips, &pot, 4, &endBet, &foldIndex);
            if (endBet + foldIndex >= 5)
            {
                break;
            }
            getchar();
            betRoundNpc(&player5HoundIn, &betTotal, &personal5Bet, &player5Chips, &pot, 5, &endBet, &foldIndex);
        } while (endBet + foldIndex < 5);

        puts("#### END OF THE BET ####");

        printCurrentRoundStatus(pot, personal1Bet, &player1Chips, betTotal);

        theRoundWinner(player1HoundIn, player2HoundIn, player3HoundIn, player4HoundIn, player5HoundIn, &player1HandValue, &player2HandValue, &player3HandValue, &player4HandValue, &player5HandValue, pot, &player1Chips, &player2Chips, &player3Chips, &player4Chips, &player5Chips);

        memset(deck, 0, sizeof(deck));
        memset(histogramOfDrawCards, 0, sizeof(histogramOfDrawCards));
        memset(player1Cards, 0, sizeof(player1Cards));
        memset(player2Cards, 0, sizeof(player2Cards));
        memset(player3Cards, 0, sizeof(player3Cards));
        memset(player4Cards, 0, sizeof(player4Cards));
        memset(player5Cards, 0, sizeof(player5Cards));
        player1ChipsSum = 0,
        player2ChipsSum = 0, player3ChipsSum = 0, player4ChipsSum = 0, player5ChipsSum = 0;
        personal1Bet = 0, personal2Bet = 0, personal3Bet = 0, personal4Bet = 0, personal5Bet = 0;
        player1HoundIn = 0, player2HoundIn = 0, player3HoundIn = 0, player4HoundIn = 0, player5HoundIn = 0;
        player1HandValue = 0, player2HandValue = 0, player3HandValue = 0, player4HandValue = 0, player5HandValue = 0;
        pot = 0, betTotal = 0, endBet = 0, foldIndex = 0;
        getchar();
    }
    puts("Someone win's.");
    printDeckAndHandForDebug(deck, player1Cards);

    return 0;
}

void shuffle(unsigned int deckShuffle[][FACES])
{
    for (size_t i = 0; i < CARDS; i++)
    {
        size_t row;
        size_t column;
        do
        {
            row = rand() % SUITS;
            column = rand() % FACES;
        } while (deckShuffle[row][column] != 0);
        deckShuffle[row][column] = i;
    }
}

void initializePlayerChips(player_chips *player_chips)
{
    // Setup of the Variables.
    // First round entry price
    player_chips->coinValue1 = 10;
    player_chips->coinValue5 = 4;
    player_chips->coinValue10 = 2;
}

void drawCardsToPlayer(int *histogram, int *playerCardsToDraw)
{
    size_t card = rand() % CARDS;
    int cardsDrawed = 0;
    while (cardsDrawed <= 4)
    {
        if (histogram[card] == 0)
        {
            playerCardsToDraw[cardsDrawed] = card;
            histogram[card]++;
            cardsDrawed++;
        }
        card = rand() % CARDS;
    }
}

void handValue(int *playerCards, int *playerHandValue, unsigned int deckValuation[][FACES])
{
    // Straight histograms to find the hand rankings.
    int histogramFaces[FACES] = {0};
    int histogramSuits[SUITS] = {0};
    int playerCardsCounter = 0;
    while (playerCardsCounter < 5)
    {
        for (size_t i = 0; i < SUITS; i++)
        {
            for (size_t j = 0; j < FACES; j++)
            {
                if (playerCardsCounter == 5)
                {
                    break;
                }
                if (deckValuation[i][j] == playerCards[playerCardsCounter])
                {
                    histogramFaces[j]++;
                    histogramSuits[i]++;
                    playerCardsCounter++;
                }
            }
        }
    }
    // Find a pair, 2 pair's, three of a kind, four of a kind and full houses.
    // Setting the value to a variable who will become the index of the Hand.
    for (size_t i = 0; i < FACES; i++)
    {
        if (histogramFaces[i] == 2)
        {
            if (*playerHandValue == 1)
            {
                *playerHandValue = 2;
                continue;
            }
            if (*playerHandValue == 3)
            {
                *playerHandValue = 6;
                continue;
            }
            *playerHandValue = 1;
        }
        if (histogramFaces[i] == 3)
        {
            if (*playerHandValue == 1)
            {
                *playerHandValue = 6;
                continue;
            }
            *playerHandValue = 3;
        }
        if (histogramFaces[i] == 4)
        {
            *playerHandValue = 7;
        }
    }
    // Find a straight, flush, straight flush and royal flush.
    // Setting the value to a variable who will become the index of the Hand.
    if (*playerHandValue == 0)
    {
        int sequence = 0;
        for (size_t i = 0; i < FACES - 1; i++)
        {
            if (histogramFaces[i] == 1 && histogramFaces[i + 1] == 1)
            {
                sequence++;
            }
            if (sequence == 4)
            {
                *playerHandValue = 4;
            }
        }
        for (size_t i = 0; i < SUITS; i++)
        {
            if (histogramSuits[i] == 5)
            {
                if (*playerHandValue == 4)
                {
                    *playerHandValue = 8;
                    if (histogramFaces[12] == 1)
                    {
                        *playerHandValue = 9;
                    }
                }
                else
                {
                    *playerHandValue = 5;
                }
            }
        }
    }
}

void showPlayerCards(int playerCards[], unsigned int deckCards[][FACES], const char *cardSuit[], const char *cardFace[])
{
    puts("###");
    puts("Your hand is:");
    for (size_t card = 0; card < 5; card++)
    {
        for (size_t i = 0; i < SUITS; i++)
        {
            for (size_t j = 0; j < FACES; j++)
            {
                if (deckCards[i][j] == playerCards[card])
                {
                    printf("%lu -> %s of %s <-\n", card + 1, cardFace[j], cardSuit[i]);
                }
            }
        }
    }
    puts("###");
}

void showPlayerHandValue(int playerHandValue, const char *handValues[], unsigned int potValue)
{
    puts("###");
    printf("Your hand have a %s.\n", handValues[playerHandValue]);
    printf("The pot value is $%d.\n", potValue);
    puts("###");
}

void printDeckAndHandForDebug(unsigned int deckDebug[][FACES], int playerCardsDebug[])
{
    for (size_t i = 0; i < SUITS; i++)
    {
        puts("");
        for (size_t j = 0; j < FACES; j++)
        {
            printf("%d ", deckDebug[i][j]);
        }
    }
    puts("");
    for (size_t i = 0; i < 5; i++)
    {
        printf("%d ", playerCardsDebug[i]);
    }
}

int sumPlayerChips(player_chips playerChipSum, int *sumOfPlayerChips)
{
    *sumOfPlayerChips = playerChipSum.coinValue1 + (playerChipSum.coinValue5 * 5) + (playerChipSum.coinValue10 * 10);
    if (*sumOfPlayerChips == 250)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void potInitialBet(player_chips *playerChipInitialBet, unsigned int *potPtr, int *houndIn)
{
    if (playerChipInitialBet->coinValue5 == 0)
    {
        if (playerChipInitialBet->coinValue10 > 0)
        {
            playerChipInitialBet->coinValue10--;
            playerChipInitialBet->coinValue5 += 2;
        }
    }
    if (playerChipInitialBet->coinValue1 == 0)
    {
        if (playerChipInitialBet->coinValue5 > 0)
        {
            playerChipInitialBet->coinValue5--;
            playerChipInitialBet->coinValue1 += 5;
        }
    }
    if (playerChipInitialBet->coinValue1 > 0)
    {
        playerChipInitialBet->coinValue1--;
        *potPtr += 1;
    }
    if (playerChipInitialBet->coinValue5 == 0 && playerChipInitialBet->coinValue1 == 0 && playerChipInitialBet->coinValue10 == 0)
    {
        *houndIn = 2;
    }
}

void betRoundPlayer(int *playerHoundIn, unsigned int *totalBet, int *personalRoundBet, player_chips *playerChipsRound, unsigned int *potRound, int *endOfBet, int *foldI)
{
    if (*playerHoundIn == 0)
    {
        int playerRoute = 0;
        puts("Press 1 for call/check, 2 for raise/bet, and 3 for fold: (then press enter)");
        scanf("%d", &playerRoute);
        while (playerRoute > 3 || playerRoute < 0)
        {
            puts("Incorrect number, select the right number for action:");
            scanf("%d", &playerRoute);
        }
        if (playerRoute == 1)
        {
            if (*personalRoundBet == *totalBet)
            {
                *endOfBet += 1;
                return;
            }
            int sumChips = playerChipsRound->coinValue1 + (playerChipsRound->coinValue5 * 5) + (playerChipsRound->coinValue10 * 10);
            if ((*totalBet - *personalRoundBet) >= sumChips)
            {
                playerChipsRound->coinValue1 = 0;
                playerChipsRound->coinValue5 = 0;
                playerChipsRound->coinValue10 = 0;
                *potRound += sumChips;
                *personalRoundBet += (*totalBet - *personalRoundBet);
                *endOfBet += 1;
                return;
            }
            int difT = *totalBet - *personalRoundBet;
            int dif1 = 0;
            int dif5 = 0;
            int dif10 = 0;
            if (playerChipsRound->coinValue10 < dif10)
            {
                while (playerChipsRound->coinValue10 < dif10)
                {
                    dif10--;
                    dif5 += 2;
                }
                while (playerChipsRound->coinValue5 < dif5)
                {
                    dif5--;
                    dif1 += 5;
                }
                if (playerChipsRound->coinValue1 >= dif1)
                {
                    playerChipsRound->coinValue1 -= dif1;
                    *potRound += dif1;
                }
                if (playerChipsRound->coinValue5 >= dif5)
                {
                    playerChipsRound->coinValue5 -= dif5;
                    *potRound += dif5 * 5;
                }
                if (playerChipsRound->coinValue10 >= dif10)
                {
                    playerChipsRound->coinValue10 -= dif10;
                    *potRound += dif10 * 10;
                }
            }
            else
            {
                if (playerChipsRound->coinValue1 >= dif1)
                {
                    playerChipsRound->coinValue1 -= dif1;
                    *potRound += dif1;
                }
                if (playerChipsRound->coinValue5 >= dif5)
                {
                    playerChipsRound->coinValue5 -= dif5;
                    *potRound += dif5 * 5;
                }
                if (playerChipsRound->coinValue10 >= dif10)
                {
                    playerChipsRound->coinValue10 -= dif10;
                    *potRound += dif10 * 10;
                }
            }
            *personalRoundBet += (*totalBet - *personalRoundBet);
            *endOfBet += 1;
            return;
        }
        if (playerRoute == 2)
        {
            int sumChips = playerChipsRound->coinValue1 + (playerChipsRound->coinValue5 * 5) + (playerChipsRound->coinValue10 * 10);
            if ((*totalBet - *personalRoundBet) >= sumChips)
            {
                puts("You do not have enough chips to bet/raise. This is an all in.");
                playerChipsRound->coinValue1 = 0;
                playerChipsRound->coinValue5 = 0;
                playerChipsRound->coinValue10 = 0;
                *potRound += sumChips;
                *personalRoundBet += sumChips;
                *endOfBet += 1;
                return;
            }
            puts("How much are you betting/raising?");
            int bet;
            scanf("%d", &bet);
            while (bet + (*totalBet - *personalRoundBet) > sumChips)
            {
                puts("You can't bet/raise that amount, try again:");
                scanf("%d", &bet);
            }
            int difT = (*totalBet - *personalRoundBet) + bet;
            int dif1 = 0;
            int dif5 = 0;
            int dif10 = 0;
            if (difT >= 10)
            {
                dif1 = difT % 10;
                dif10 = (difT - dif1) / 10;
            }
            else
            {
                dif1 = difT;
            }
            if (dif1 > 5)
            {
                dif1 -= 5;
                dif5 += 1;
            }
            if (playerChipsRound->coinValue10 < dif10)
            {
                while (playerChipsRound->coinValue10 < dif10)
                {
                    dif10--;
                    dif5 += 2;
                }
                while (playerChipsRound->coinValue5 < dif5)
                {
                    dif5--;
                    dif1 += 5;
                }
                if (playerChipsRound->coinValue1 >= dif1)
                {
                    playerChipsRound->coinValue1 -= dif1;
                    *potRound += dif1;
                }
                if (playerChipsRound->coinValue5 >= dif5)
                {
                    playerChipsRound->coinValue5 -= dif5;
                    *potRound += dif5 * 5;
                }
                if (playerChipsRound->coinValue10 >= dif10)
                {
                    playerChipsRound->coinValue10 -= dif10;
                    *potRound += dif10 * 10;
                }
            }
            else
            {
                if (playerChipsRound->coinValue1 >= dif1)
                {
                    playerChipsRound->coinValue1 -= dif1;
                    *potRound += dif1;
                }
                if (playerChipsRound->coinValue5 >= dif5)
                {
                    playerChipsRound->coinValue5 -= dif5;
                    *potRound += dif5 * 5;
                }
                if (playerChipsRound->coinValue10 >= dif10)
                {
                    playerChipsRound->coinValue10 -= dif10;
                    *potRound += dif10 * 10;
                }
            }

            *personalRoundBet += (*totalBet - *personalRoundBet) + bet;
            *totalBet += bet;
            *endOfBet = 1;
            return;
        }
        if (playerRoute == 3)
        {
            puts("You fold.");
            *playerHoundIn = 1;
            *foldI += 1;
            return;
        }
    }
    if (*playerHoundIn == 2)
    {
        *playerHoundIn += 1;
        *foldI += 1;
        return;
    }
}

void printCurrentRoundStatus(unsigned int potStatus, int personalRoundStatus, player_chips *playerChipsStatus, unsigned int call)
{
    int sumChips = playerChipsStatus->coinValue1 + (playerChipsStatus->coinValue5 * 5) + (playerChipsStatus->coinValue10 * 10);
    printf("The pot is $%d.\nThe current money put in is $%d.\nYou have left in balance $%d\nThe minimum call is %d\n", potStatus, personalRoundStatus + 1, sumChips, call);
}

void betRoundNpc(int *playerHoundIn, unsigned int *totalBet, int *personalRoundBet, player_chips *playerChipsRound, unsigned int *potRound, int npc, int *endOfBet, int *foldI)
{
    if (*playerHoundIn == 0)
    {
        int playerRoute = rand() % 100;

        if (playerRoute <= 70)
        {
            if (*personalRoundBet == *totalBet)
            {
                printf("Player %d make a call/check.\n", npc);
                *endOfBet += 1;
                return;
            }
            int sumChips = playerChipsRound->coinValue1 + (playerChipsRound->coinValue5 * 5) + (playerChipsRound->coinValue10 * 10);
            if ((*totalBet - *personalRoundBet) >= sumChips)
            {
                printf("Player %d make a call/check.\n", npc);
                playerChipsRound->coinValue1 = 0;
                playerChipsRound->coinValue5 = 0;
                playerChipsRound->coinValue10 = 0;
                *potRound += sumChips;
                *personalRoundBet += (*totalBet - *personalRoundBet);
                *endOfBet += 1;
                return;
            }
            int difT = *totalBet - *personalRoundBet;
            int dif1 = 0;
            int dif5 = 0;
            int dif10 = 0;
            if (difT >= 10)
            {
                dif1 = difT % 10;
                dif10 = (difT - dif1) / 10;
            }
            else
            {
                dif1 = difT;
            }
            if (dif1 > 5)
            {
                dif1 -= 5;
                dif5 += 1;
            }
            if (playerChipsRound->coinValue10 < dif10)
            {
                while (playerChipsRound->coinValue10 < dif10)
                {
                    dif10--;
                    dif5 += 2;
                }
                while (playerChipsRound->coinValue5 < dif5)
                {
                    dif5--;
                    dif1 += 5;
                }
                if (playerChipsRound->coinValue1 >= dif1)
                {
                    playerChipsRound->coinValue1 -= dif1;
                    *potRound += dif1;
                }
                if (playerChipsRound->coinValue5 >= dif5)
                {
                    playerChipsRound->coinValue5 -= dif5;
                    *potRound += dif5 * 5;
                }
                if (playerChipsRound->coinValue10 >= dif10)
                {
                    playerChipsRound->coinValue10 -= dif10;
                    *potRound += dif10 * 10;
                }
            }
            else
            {
                if (playerChipsRound->coinValue1 >= dif1)
                {
                    playerChipsRound->coinValue1 -= dif1;
                    *potRound += dif1;
                }
                if (playerChipsRound->coinValue5 >= dif5)
                {
                    playerChipsRound->coinValue5 -= dif5;
                    *potRound += dif5 * 5;
                }
                if (playerChipsRound->coinValue10 >= dif10)
                {
                    playerChipsRound->coinValue10 -= dif10;
                    *potRound += dif10 * 10;
                }
            }
            printf("Player %d make a call.\n", npc);
            *personalRoundBet += (*totalBet - *personalRoundBet);
            *endOfBet += 1;
            return;
        }
        if (playerRoute > 70 && playerRoute <= 85)
        {
            int sumChips = playerChipsRound->coinValue1 + (playerChipsRound->coinValue5 * 5) + (playerChipsRound->coinValue10 * 10);
            if ((*totalBet - *personalRoundBet) >= sumChips)
            {
                printf("Player %d make an all in.\n", npc);
                playerChipsRound->coinValue1 = 0;
                playerChipsRound->coinValue5 = 0;
                playerChipsRound->coinValue10 = 0;
                *potRound += sumChips;
                *personalRoundBet += sumChips;
                *endOfBet += 1;
                return;
            }
            int bet = 1 + rand() % (sumChips - (*totalBet - *personalRoundBet));
            int difT = (*totalBet - *personalRoundBet) + bet;
            int dif1 = 0;
            int dif5 = 0;
            int dif10 = 0;
            if (difT >= 10)
            {
                dif1 = difT % 10;
                dif10 = (difT - dif1) / 10;
            }
            else
            {
                dif1 = difT;
            }
            if (dif1 > 5)
            {
                dif1 -= 5;
                dif5 += 1;
            }
            // printf("%d %d %d %d\n", difT, dif1, dif5, dif10);
            if (playerChipsRound->coinValue10 < dif10)
            {
                while (playerChipsRound->coinValue10 < dif10)
                {
                    dif10--;
                    dif5 += 2;
                }
                while (playerChipsRound->coinValue5 < dif5)
                {
                    dif5--;
                    dif1 += 5;
                }
                if (playerChipsRound->coinValue1 >= dif1)
                {
                    playerChipsRound->coinValue1 -= dif1;
                    *potRound += dif1;
                }
                if (playerChipsRound->coinValue5 >= dif5)
                {
                    playerChipsRound->coinValue5 -= dif5;
                    *potRound += dif5 * 5;
                }
                if (playerChipsRound->coinValue10 >= dif10)
                {
                    playerChipsRound->coinValue10 -= dif10;
                    *potRound += dif10 * 10;
                }
            }
            else
            {
                if (playerChipsRound->coinValue1 >= dif1)
                {
                    playerChipsRound->coinValue1 -= dif1;
                    *potRound += dif1;
                }
                if (playerChipsRound->coinValue5 >= dif5)
                {
                    playerChipsRound->coinValue5 -= dif5;
                    *potRound += dif5 * 5;
                }
                if (playerChipsRound->coinValue10 >= dif10)
                {
                    playerChipsRound->coinValue10 -= dif10;
                    *potRound += dif10 * 10;
                }
            }
            printf("Player %d make a bet/raise of %d.\n", npc, bet);
            *personalRoundBet += (*totalBet - *personalRoundBet) + bet;
            *totalBet += bet;
            *endOfBet = 1;
            return;
        }
        if (playerRoute > 85)
        {
            printf("Player %d folded.\n", npc);
            *playerHoundIn = 1;
            *foldI += 1;
            return;
        }
    }
    if (*playerHoundIn == 2)
    {
        *playerHoundIn += 1;
        *foldI += 1;
        return;
    }
}

void theRoundWinner(int player1HoundIndex, int player2HoundIndex, int player3HoundIndex, int player4HoundIndex, int player5HoundIndex, int *playerHandValue1, int *playerHandValue2, int *playerHandValue3, int *playerHandValue4, int *playerHandValue5, unsigned int potWin, player_chips *player1Chips, player_chips *player2Chips, player_chips *player3Chips, player_chips *player4Chips, player_chips *player5Chips)
{
    int hands[5] = {-1, -1, -1, -1, -1};
    int bestHandIndex[5] = {-1, -1, -1, -1, -1};
    int counter = 0, bestHand = -1;
    if (player1HoundIndex == 0)
    {
        hands[0] = *playerHandValue1;
    }
    if (player2HoundIndex == 0)
    {
        hands[1] = *playerHandValue2;
    }
    if (player3HoundIndex == 0)
    {
        hands[2] = *playerHandValue3;
    }
    if (player4HoundIndex == 0)
    {
        hands[3] = *playerHandValue4;
    }
    if (player5HoundIndex == 0)
    {
        hands[4] = *playerHandValue5;
    }
    for (size_t i = 0; i < 5; i++)
    {
        if (hands[i] > bestHand)
        {
            bestHand = hands[i];
        }
    }
    for (size_t i = 0; i < 5; i++)
    {
        if (bestHand == hands[i])
        {
            bestHandIndex[counter] = i;
            counter++;
        }
    }
    for (size_t i = 0; i < counter; i++)
    {
        if (bestHandIndex[i] == 0)
        {
            int difT = (potWin / counter);
            if (i == 1)
            {
                difT += (potWin % counter);
            }
            printf("Player 1 win, and gets %d dolars.\n", difT);
            int dif1 = 0;
            int dif5 = 0;
            int dif10 = 0;
            if (difT >= 10)
            {
                dif1 = difT % 10;
                dif10 = (difT - dif1) / 10;
            }
            else
            {
                dif1 = difT;
            }
            if (dif1 > 5)
            {
                dif1 -= 5;
                dif5 += 1;
            }
            player1Chips->coinValue1 += dif1;
            player1Chips->coinValue5 += dif5;
            player1Chips->coinValue10 += dif10;
        }
        if (bestHandIndex[i] == 1)
        {
            int difT = (potWin / counter);
            if (i == 1)
            {
                difT += (potWin % counter);
            }
            printf("Player 2 win, and gets %d dolars.\n", difT);
            int dif1 = 0;
            int dif5 = 0;
            int dif10 = 0;
            if (difT >= 10)
            {
                dif1 = difT % 10;
                dif10 = (difT - dif1) / 10;
            }
            else
            {
                dif1 = difT;
            }
            if (dif1 > 5)
            {
                dif1 -= 5;
                dif5 += 1;
            }
            player2Chips->coinValue1 += dif1;
            player2Chips->coinValue5 += dif5;
            player2Chips->coinValue10 += dif10;
        }
        if (bestHandIndex[i] == 2)
        {
            int difT = (potWin / counter);
            if (i == 1)
            {
                difT += (potWin % counter);
            }
            printf("Player 3 win, and gets %d dolars.\n", difT);
            int dif1 = 0;
            int dif5 = 0;
            int dif10 = 0;
            if (difT >= 10)
            {
                dif1 = difT % 10;
                dif10 = (difT - dif1) / 10;
            }
            else
            {
                dif1 = difT;
            }
            if (dif1 > 5)
            {
                dif1 -= 5;
                dif5 += 1;
            }
            player3Chips->coinValue1 += dif1;
            player3Chips->coinValue5 += dif5;
            player3Chips->coinValue10 += dif10;
        }
        if (bestHandIndex[i] == 3)
        {
            int difT = (potWin / counter);
            if (i == 1)
            {
                difT += (potWin % counter);
            }
            printf("Player 4 win, and gets %d dolars.\n", difT);
            int dif1 = 0;
            int dif5 = 0;
            int dif10 = 0;
            if (difT >= 10)
            {
                dif1 = difT % 10;
                dif10 = (difT - dif1) / 10;
            }
            else
            {
                dif1 = difT;
            }
            if (dif1 > 5)
            {
                dif1 -= 5;
                dif5 += 1;
            }
            player4Chips->coinValue1 += dif1;
            player4Chips->coinValue5 += dif5;
            player4Chips->coinValue10 += dif10;
        }
        if (bestHandIndex[i] == 4)
        {
            int difT = (potWin / counter);
            if (i == 1)
            {
                difT += (potWin % counter);
            }
            printf("Player 5 win, and gets %d dolars.\n", difT);
            int dif1 = 0;
            int dif5 = 0;
            int dif10 = 0;
            if (difT >= 10)
            {
                dif1 = difT % 10;
                dif10 = (difT - dif1) / 10;
            }
            else
            {
                dif1 = difT;
            }
            if (dif1 > 5)
            {
                dif1 -= 5;
                dif5 += 1;
            }
            player5Chips->coinValue1 += dif1;
            player5Chips->coinValue5 += dif5;
            player5Chips->coinValue10 += dif10;
        }
    }
    return;
}