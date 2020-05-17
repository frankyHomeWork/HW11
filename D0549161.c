#include <stdio.h>
#include <stdlib.h>

typedef struct people {
    int number;
    struct people *nextPeopel;
    struct people *prePeopel;
} People;

typedef struct {
    People *firstPeople;
    People *nextStartPeople;
    int size;
} CircleLine;

CircleLine createCircleLine(int numberOfPeopel) {
    CircleLine circleLine;
    circleLine.firstPeople = NULL;
    circleLine.nextStartPeople = NULL;
    circleLine.size = 0;

    int first = 1;

    People *prePeopel = NULL;

    int i;
    for (i = 1; i <= numberOfPeopel; i++) {
        People *newPeopel = (People *)malloc(sizeof(People));
        newPeopel->number = i;
        newPeopel->nextPeopel = NULL;
        newPeopel->prePeopel = NULL;

        if (first) {
            newPeopel->nextPeopel = newPeopel;
            newPeopel->prePeopel = newPeopel;

            circleLine.firstPeople = newPeopel;
            circleLine.nextStartPeople = circleLine.firstPeople;

            first = 0;
        } else {
            newPeopel->prePeopel = prePeopel;
            prePeopel->nextPeopel = newPeopel;
        }

        circleLine.size++;
        prePeopel = newPeopel;
    }
    prePeopel->nextPeopel =
        circleLine.firstPeople;  // the last people next link to first people

    circleLine.firstPeople->prePeopel =
        prePeopel;  // the first people pre link to last people

    return circleLine;
}

CircleLine killPeople(CircleLine circleLine, int countNumber) {
    if (circleLine.size <= 0) {
        return circleLine;
    }

    People *currentPeople = circleLine.nextStartPeople;
    int subtractionfirstCount = countNumber - 1;
    int i;
    for (i = 0; i < subtractionfirstCount; i++) {
        currentPeople = currentPeople->nextPeopel;
    }

    People *beKilledPeople = currentPeople;

    beKilledPeople->prePeopel->nextPeopel = beKilledPeople->nextPeopel;
    //      pre <- K <-> next
    //       |             |
    //       |-->-->--->-->|

    beKilledPeople->nextPeopel->prePeopel = beKilledPeople->prePeopel;
    //      pre <-  K  -> next
    //       |             |
    //       |<----------->|

    circleLine.nextStartPeople = beKilledPeople->nextPeopel;

    circleLine.size--;
    free(beKilledPeople);

    return circleLine;
}

void show(CircleLine circleLine) {  // for test
    if (circleLine.size <= 0) {
        printf("not People\n");
        return;
    }

    People *currentPeople = circleLine.nextStartPeople;
    int i;
    for (i = 0; i < circleLine.size; i++) {
        printf("People: %d\n", currentPeople->number);
        currentPeople = currentPeople->nextPeopel;
    }
}

int main() {
    int numberOfPeople;
    int countNumber;
    scanf("%d %d", &numberOfPeople, &countNumber);

    CircleLine circleLine = createCircleLine(numberOfPeople);
    while (circleLine.size != 1) {
        circleLine = killPeople(circleLine, countNumber);
    }
    printf("%d\n", circleLine.nextStartPeople->number);

    return 0;
}