/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

#define BUFFER_LEN 256
#define NUM_PLAYERS 4
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define RESET "\033[0m"

// Processes the answer from the user containing "what is" or "who is" and tokenizes it
void tokenize(char *input, char **tokens) {
    char *token = strtok(input, " ");
    int index = 0;
    while (token != NULL) {
        tokens[index++] = token;
        token = strtok(NULL, " ");
    }
    tokens[index] = NULL;
}

// Displays the game results for each player, ranked from first to last place
void show_results(player *players, int num_players) {
    for (int i = 0; i < num_players - 1; i++) {
        for (int j = 0; j < num_players - i - 1; j++) {
            if (players[j].score < players[j + 1].score) {
                player temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }
    
    printf("\n" YELLOW "Final Results:" RESET "\n");
    for (int i = 0; i < num_players; i++) {
        printf("%d. %s - " GREEN "$%d" RESET "\n", i + 1, players[i].name, players[i].score);
    }
}

int main() {
    srand(time(NULL));
    player players[NUM_PLAYERS];
    char buffer[BUFFER_LEN];
    
    printf(BLUE "Welcome to Jeopardy!\n" RESET);
    initialize_game();
    
    for (int i = 0; i < NUM_PLAYERS; i++) {
        printf("Enter name for Player %d: ", i + 1);
        fgets(players[i].name, MAX_LEN, stdin);
        players[i].name[strcspn(players[i].name, "\n")] = 0;
        players[i].score = 0;
    }
    
    while (1) {
        display_categories();
        printf("Enter player name to pick a question: ");
        fgets(buffer, BUFFER_LEN, stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        
        if (!player_exists(players, NUM_PLAYERS, buffer)) {
            printf(RED "Invalid player name. Try again.\n" RESET);
            continue;
        }
        
        char category[MAX_LEN];
        int value;
        printf("Enter category: ");
        fgets(category, MAX_LEN, stdin);
        category[strcspn(category, "\n")] = 0;
        printf("Enter value: ");
        scanf("%d", &value);
        getchar();
        
        if (already_answered(category, value)) {
            printf(RED "Question already answered. Pick another.\n" RESET);
            continue;
        }
        
        display_question(category, value);
        printf("You have 10 seconds to answer...\n");
        sleep(10);
        printf("Your answer: ");
        fgets(buffer, BUFFER_LEN, stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        
        char *tokens[MAX_LEN];
        tokenize(buffer, tokens);
        
        if (valid_answer(category, value, tokens[2])) {
            printf(GREEN "Correct! You earn $%d\n" RESET, value);
            update_score(players, NUM_PLAYERS, buffer, value);
        } else {
            printf(RED "Incorrect! No points awarded.\n" RESET);
        }
        
        for (int i = 0; i < NUM_QUESTIONS; i++) {
            if (strcmp(questions[i].category, category) == 0 && questions[i].value == value) {
                questions[i].answered = true;
                break;
            }
        }
        
        int all_answered = 1;
        for (int i = 0; i < NUM_QUESTIONS; i++) {
            if (!questions[i].answered) {
                all_answered = 0;
                break;
            }
        }
        if (all_answered) break;
    }
    
    show_results(players, NUM_PLAYERS);
    return 0;
}
