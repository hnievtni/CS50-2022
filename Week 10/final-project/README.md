# Dig-Out
#### Video Demo: <https://youtu.be/S4FO_UIOLV4>
#### Description:
Hi, I'm Hanie Vatani from Iran.
This is my final project for CS50X Iran.
It's called Dig-Out and it is inspired by the original Dig-Out game.

You can change the settings in the game and you have to enter your name before starting.
Also after the game ended you can come back to the menu and start over or you can check your previous records.
After the first move, gravity will work.
Gravity works for rocks, coins, bombs, life potions, power potions, and robots.
If a rock falls on you, you will die.
If a coin falls on you, you will receive a coin.
If a bomb falls on you, your strength will decrease as much as the power of the bomb and if your strength reaches zero you will lose a life point.
If a life potion falls on you, you will receive a life point.
If a power potion falls on you, your strength will increase as much as the power of the power potion.
If a robot falls on you, you will fight the robot and if the robot's life is more than the player's life, the player will die, and if not the player will lose a life point.

Functions:
1- main: in this function, we will initialize the variables.
2- menu: menu would print the menu in the console.
3- playersinfo: saves the player's name and if you finish the game it would write it into records file with your score.
4- startgame: displays the instructions of the game and arranges the game field.
5- setting: the player can change the variables with this function.
6- saverecords: this would open the records file and add the new records.
7- displayrecords: this would display the records by opening and reading from the records file.
8- randpositions: this would check the field and it would place rocks, bombs, ... in the blocks that are sand;
    except for the first row first column (players starting position).
9- updategamefield: this would display the game field by printing the game field 2D array.
10- inputs: check the inputs for movements and digging up the blocks.
11- diggingupblocks: if inputs were i, j, k, or l this function would be called to dig up.
    it requires 3 arguments which are a char to specify the direction of digging and two integers which are the player's row and column position.
12- blockcheck: it would check the block player wants to dig up to see if it is possible or not.
    it requires 2 arguments which are the row and the column of the block, the player wants to dig up.
13- updateplayersposition: if inputs were w, s, a, or d this function would be called to move into.
    it requires 3 arguments which are a char to specify the direction of movement and two integers which are the player's row and column position.
14- enteringcheck: it would check the block, the player wants to move into to see if it is possible or not.
    it requires 2 arguments which are the row and the column of the block, the player wants to move into.
15- gainvictory: checks if the player got all the coins and won.
16- gravity: this would check the gravity. and it checks each row of a column twice.
17- error: this will print the needed error in the console. it requires the value error for each error.
18- updatelifecount: checks if the player's life point reached zero or not.
19- updateplayersstrength: checks if the player's strength counter reached zero or not; if it did player would lose a life point.
20- movementlimit: check the remaining moves, if it reached zero player will lose the game.