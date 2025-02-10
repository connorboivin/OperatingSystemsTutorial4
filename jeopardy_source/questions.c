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
#include "questions.h"

// Initializes the array of questions for the game
void initialize_game(void) {
    srand(time(NULL));  // Ensure questions are randomized for each game

    // Define questions for each category
    strcpy(questions[0].category, "programming");
    strcpy(questions[0].question, "What is the primary language used in system programming?");
    strcpy(questions[0].answer, "C");
    questions[0].value = 100;
    questions[0].answered = false;

    strcpy(questions[1].category, "algorithms");
    strcpy(questions[1].question, "What sorting algorithm has O(n log n) time complexity?");
    strcpy(questions[1].answer, "Merge Sort");
    questions[1].value = 200;
    questions[1].answered = false;

    strcpy(questions[2].category, "databases");
    strcpy(questions[2].question, "Which SQL statement is used to update data?");
    strcpy(questions[2].answer, "UPDATE");
    questions[2].value = 300;
    questions[2].answered = false;

    // Shuffle the questions for randomness
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        int j = rand() % NUM_QUESTIONS;
        question temp = questions[i];
        questions[i] = questions[j];
        questions[j] = temp;
    }
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void) {
    printf("\nCategories and Available Questions:\n");
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (!questions[i].answered) {
            printf("%s - $%d\n", questions[i].category, questions[i].value);
        }
    }
}

// Displays the question for the category and dollar value
void display_question(char *category, int value) {
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value && !questions[i].answered) {
            printf("\nQuestion: %s\n", questions[i].question);
            return;
        }
    }
    printf("Invalid category or value, or question already answered.\n");
}

// Returns true if the answer is correct for the question in that category and dollar value
bool valid_answer(char *category, int value, char *answer) {
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value && !questions[i].answered) {
            return strcmp(questions[i].answer, answer) == 0;
        }
    }
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value) {
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value) {
            return questions[i].answered;
        }
    }
    return false;
}
