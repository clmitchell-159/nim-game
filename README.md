# nim-game
TITLE: The Unbeatable Game of Nim
Author: Chandler Mitchell
Section: E - 12:00

### Problem Description ###
This program will implement that game of Nim with a graphical
interface using SFML. Nim is a simple game in concept. The game
begins with a number of flags several fields. If the starting
number of fields is greater than one, Players take turns removing
any number of flags from a single field. If the starting fields is
one, then players can take up to three flags  Whoever removes
the last flag from the last field loses the game.  This program would
allow single player and a multiplayer option. In the single
player option, the player would play against the AI, while the
multiplayer option allows for several humans and/or AI to play
against each other, with the looser being eliminated. SFML will
be used to draw the flags, and display each player taking flags.
SFML allows for buttons, so players can click on flags to remove
them from the field.

## Program Documentation ##
Requires SFML

### MENUS ###

#### Main Menu ####
From the main menu, the user can choose to play, change options, or 
view the rules by clicking on the corresponding button. Clicking Rules
will print the rules to the console. Clicking Play (without selecting
options) starts a Normal Game vs. the AI (via the default constructor).
Selecting options brings up the Options Menu (and use the non-default
constructor).

#### Options Menu ####
On this screen, the user can change various parameters of the game, 
including the number of computers, humans and fields by clicking on
the corresponding + and - buttons. This updates the count for the
category displayed on the screen. If the screen did not update, your
click was not registered. Clicking on "Toggle Music Playback" will 
play/pause the music. Clicking on "Edit Fields" will open the Field
Menu. Clicking "Save" results in the options being save and the user
returned to the Main Menu, where clicking play will load a game with
their custom settings. Attempting to change a setting beyond the
acceptable range results in an error message printed to the console.

#### Field Menu ####
This menu allow for the user to change the number of flags in each
field by clicking the associated + and - buttons. Clicking "Save" 
saves the user's settings, and returns them to the Options Menu.

### PLAYING ###

After clicking play, the user is prompted to enter the names of each
human player. There is no character limit, but in places the names
will be truncated to 10 characters.

Once the user has reached the Board screen, they are playing Nim.
The UI displays the name of the player who's turn it currently is.
Below this, the UI displays instructions of what to do. Clicking
on a field (or in single field games, the field is selected
automatically), brings up a window for the player to choose how
many flags they would like to remove from that field. The user
selects the number of flags they would like to remove by clicking
the + and - buttons, the clicks "Accept" to finalize their
decision.
The AI will print its decisions to the console.

Play continues until the last flag is removed. The player who 
removed the last flag is eliminated from the game, and the game
resets. If there is only one player left, they win and the game
ends.

During play, the score at the bottom is updated to show how many
flags each player has taken that round.

### Additional Features ###

As it stands, the game is rather bland. Adding backgrounds and
other UI visual improvements would have been nice.
Each + and - button can only increment the associated count by
one. This can become tedious quickly. An option select (shift)
that allows increments of 5 or 10 would improve the user
experience. Improve the multifield AI - it is fairly simple, and
probably doesn't play perfectly.

### Program Documentation ###

Spaghetti: ✓
The program first loads music, then begins the menus loop.
The loop runs until the user selects play and the game 
launches. Otherwise, the loop displays the options menu if
the player clicked the options button, or prints the rules
to the console. Once the user clicks play, the loop creates
and returns the appropriate GameState.

At any point, if the user clicks the X on the window, the game
exits by setting the winner and/or active player to -1.

Once the game has loaded, the game checks if there are more
than one fields.
If so, the game then checks if the player is human. If so, the
	game waits for the player to click on a field. Once a field
	has been clicked, the game brings up a menu that asks how
	many flags to remove. Once the user has answered, the game
	moves the flags from the field to the player then updates
	the display.
If the player is a computes, the computer takes flags in such a
	way that it is in a winning position. This is done by
	XORing the binary representation of the number of flags in
	each field and making sure the result is all 0's. If it is
	not all zeros, the AI takes a number of flags from a field
	that has an unpaired bit. If it is all zeros, the AI takes
	one flag and hopes for a mistake.
If there is only one field, a similar process is repeated with
a slightly different AI. This one attempts to make sure there
is a multiple of 4 flags remaining or exactly  1 flag remaining
when its turn ends.

Once a player has lost, the game checks if there are two or
more not lost players remaining. if so, it resets the board
and plays with the remaining players. If not, it declares the
last remaining player the winner and exits.

### TESTS ###

1: Normal Game, Rules and AI.
	Click Rules, and Rules should print to the console.
	Click Play, enter any string. This string will be displayed
	at the top of the "Board" window, and another window called 
	"Select Flags" should pop up. The board window should be 
	unresponsive - it is waiting on the "Select Flags" window to
	return a value. The field should have 21 flags drawn in it. 
	The "Select Flags" window should allow you to
	select 1 - 3 flags. Select 1. Click accept. The "Board" window
	will update removing a flag and incrementing the count by your
	name by one, the AI will take its turn, print its decision to
	the console (3 from 0)and the "Board" window will update again.
	update removing a flag and incrementing the count by the AI's
	name by one. Then the "Select Flags" window will open again.
	Continuing to select 1 flag to take will cause the AI take 3
	flags until you lose. The board will update accordingly. When
	you loose, the game will congratulate the computer and exit.
2: Normal Game, Music, AI
	Click Options, click Toggle Music Playback. The music should
	pause. Subsequent clicks should toggle the music playback.
	If the music paused when you opened the options menu, SFML
	thought you clicked Toggle Music Playback - the buttons are in
	the same spot. Click edit fields, the change the number of
	flags in field one to 35. Click save until you are back at
	the main menu. Click Play, enter any string. This string
	will be displayed at the top of the "Board" window, and another
	window called "Select Flags" should pop up. The board window
	should be unresponsive - it is waiting on the "Select Flags"
	window to return a value. The field should have 35 flags drawn
	in it. Remove 1, the AI will remove 1. In subsequent rounds,
	the AI will take 4 - your choice until you lose.
3: Force Close
	At any Active window, hitting the X button on the window will
	result in the game closing. Windows: Main Menu, Options, Edit
	Fields, Select Flags, Board (MultiPlayer).
4: MultiPlayer
	Click Options, set there to be two humans. save then play.
	Enter names for the two humans. Play Normally, have one of
	the humans loose. The game will print that player has lost,
	and start a new round in which that player does not get a
	turn.
5: MultiFields
	click options, set there to be more than one field. Save then
	play. The board will have the number of fields you selected,
	each with 21 flags in it. Click on a field, remove flags.
	The board will update with that field and only that field 
	having a different number of flags in it. Then the AI will
	take its turn, and it will removes flags from a field, and
	the board will update again. This AI is significantly worse
	and will make mistakes. When you or the AI has lost, the game
	will congratulate the winner and exit.

### Reflections ###

From this project, I learned now quickly software projects can grow
into beasts. I did not think that this project would be as
complicated as it was, and as a result had to make sacrifices to
meet the deadline. These sacrifices include making the game look good,
and having a perfect AI, which is possible.
I learned to prioritize things that are required to make the software
work before adding features. I added the music at the beginning of the
project when I had time, but that time could have been spent elsewhere
more effectively. If I could redo the project, I would limit the scope
in order to deliver a higher quality project.

