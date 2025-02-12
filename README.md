/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
 
 Jeopardy game

This program simulates the game of Jeopardy. It uses a command line prompt for user interaction. It first asks for the four player names which will be recorded and their initial earnings set to 0.
The program then prints out each of the question categories and displays the dollar values for each question.
The program will accept the name of the person selected to pick a question and validates that the name matches to one of the prerecorded player names.
The program then prompts the player for the category and dollar amount question and check if it's not already answered.
The program will then display the question and await for input which contains either the phrases "what is" or "who is" at the start.
After the player answers the question the program displays whether they got it correct or incorrect. If the player answered the question correctly the program updates their score. If they answered incorrectly the program displays the answer and no user will receive any points.
