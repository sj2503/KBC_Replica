Description of how to run the code and observe the output:

1. There is 1 input file "Question_File.txt". Keep it in same folder in which 2019B3PS0385P_P3.c is present. Introduction and all questions along with options including jackpot question are taken from it.
2. The exe is called 2019B3PS0385P_P3.exe. Open it to run the program. If by chance it doesn't open then please compile 2019B3PS0385P_P3.c using gcc compiler.
3. When you run the exe, it will prompt you introduction and the required instructions to start the game.
4. We have deliberately given pause in between introduction to give it an animation effect. If you want to increase speed you can make a change in animation() function by decrasing value of 2500000.
5. Press enter to start the game, which will provide you questions on your prompt.
6. For any question if you chose correct option you go to further questions.
7. If user gives incorrect input to what is being asked, like when asked of choosing an option between 1-4, if user types "5fsf", the first character of the string is taken as input, now in our example since '5' is not a feasable option it will prompt to select once again till required input is not provided.
8. Likewise if user types "1fsf", it will take 1 as input.
9. If you press 'Q' it will quit the current game at any question and will show your winnings.
10. If you press 'L' it will allow you to chose either of the two lifelines, further press '1' or '2' to chose the desired lifeline that is 'fifty-fifty' or 'flip the question' respectively.
11. At any point of the game if you choose the correct option you would be shown the corresponding prize money you won.
12. However if you select wrong option for any question, the prize money counter would be reduced to zero or to the three intermediate level which are preselected for you and are set up at the questions 4, 8 and 12, respectively
13. You can opt for the bonus or sixteenth question after you have completed all the fifteen questions to turn your winnings from 1 crore to 7 crores.
14. You can choose to participate in the bonus question by pressing 'Y' otherwise by pressing 'N' you exit the game. However you cannot quit the game or use any of the lifelines after you press 'Y'.
15. If you get the 16th question wrong, your winnings will reduce to 50 Lakhs from 1 Crore.
16. Program will automatically terminate once you finish all questions, or decide to quit or gave any incorrect answer after showing your winnings and correct answer.
17. Any information necessary at any point of the program is also provided in the program itself.

#############################################################
