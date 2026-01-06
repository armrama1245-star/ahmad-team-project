# ahmad-team-project

## Angry Birds Game
First Semester – University Project

## Overview
This project is a team-based academic assignment focused on developing a simplified version of the Angry Birds game using the C++ programming language.
The goal of this project is to apply fundamental programming concepts in a practical environment while improving logical thinking and problem-solving skills.

## Project Description
This project is developed as the final project for the Fundamentals of Programming course during the first academic semester.
The main objective is to implement the core mechanics of the Angry Birds game in C++, including user interaction, timing control, and simple game logic.

In addition to programming fundamentals, the project emphasizes teamwork, structured code organization, and the use of Git and GitHub to simulate a real-world collaborative development environment.

## Learning Objectives
- Applying fundamental programming concepts in C++
- Understanding basic game logic and program flow
- Improving problem-solving skills
- Practicing team-based software development
- Using Git and GitHub for version control

## Technologies Used
- Programming Language: C++
- Version Control System: Git
- Collaboration Platform: GitHub

## Libraries Used
The following libraries are used in this project. Each library has a specific role in the implementation of the game.

--------------------------------------------------

Library: iostream
Purpose:
Used for standard input and output operations. It allows the program to display menus, messages, and game information, and to receive user input.

Used code:
#include <iostream>
using namespace std;

cout << "Welcome to Angry Birds Game!" << endl;
cin >> choice;

--------------------------------------------------

Library: thread
Purpose:
Used to manage threads and introduce controlled delays during program execution to simulate pauses in gameplay.

Used code:
#include <thread>

this_thread::sleep_for(std::chrono::milliseconds(500));

--------------------------------------------------

Library: chrono
Purpose:
Used for time-related operations. It works together with the thread library to control delays and timing.

Used code:
#include <chrono>

std::chrono::milliseconds delay(500);

--------------------------------------------------

Library: fstream
Purpose:
Used for file input and output operations such as saving scores or loading game data.

Used code:
#include <fstream>

ofstream file("score.txt");
file << score;
file.close();

--------------------------------------------------

Library: windows.h
Purpose:
Used to access Windows-specific system functions such as handling delays and controlling console behavior.

Used code:
#include <windows.h>

Sleep(1000);

--------------------------------------------------

Library: conio.h
Purpose:
Used to handle console input without waiting for the Enter key, enabling real-time user interaction.

Used code:
#include <conio.h>

getch();

--------------------------------------------------

## Project Type
Academic – University Final Project (First Semester)

## Team Members
- Arman Amirafshari
- Mohammad Amin Ahmadpour

## University
Shokat Abad University of Birjand

Javascript Code:
console.log(&quotHello, World!&quot)
Python Code:
print(&quotHello, World in Python!&quot)
