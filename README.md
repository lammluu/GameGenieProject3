GameGenie: A virtual video game chatbot assisstant
​
GameGenie Version 1:
​
	This version of GameGenie is the original version. The video attached
	to the report includes a live demo of the functional code. This version
	includes various features such as the following:
	
		- Find a game and output the info from this data, then compare the 
		  efficiency of different sorts (radix, quick, bucket) 
		- Give the user a Top 10 and Top 100 ranked games (based on global sales) 
		  then compare the efficiency of different sorts (radix, quick, bucket) 
		- Give the user a list of games that were published in a single year.
		- Users ask questions if a game is online-available, available on multiple 
		  platforms, or other things, then the program returns true or false.
		  
		  
	How to use it:
	
	
	
GameGenie Version 2:
​
	This version of GameGenie is an updated version that features improvements to
	the I/O system as well as making the overall experience more visually appealing
	and user friendly. Both versions were included because they are sufficiently 
	different user experiences. This version includes various features such as 
	the following:
	
		- Display the top of bottom X results based on metric score
		- Search a game by various parameters such as
			- Title
			- Genre
			- Year published
			- Publisher
			- Consoles
		- Performs all 3 sorting algorithms at once and prints out the results
		- Uses cool colors on the console to make it visually appealing
		
	
	How to use it:
	
		1. Execute the file in the terminal
		2. Input the desired menu option into the command line when asked
		3. The bot will ask the user "What can I help you with today?"
		4. The user inputs the desired option into the terminal, 1 for display 
		top ranked, 2 for search game, and 3 for exiting the program
		
		Option 1: Display top ranked games
			- The bot will ask the user "How many games to display?" This is the
			amount of games that should be printed out at the end after the vector
			of games is sorted
			- Then it will ask the user "Start from the bottom (b) or top (t)?"
			Enter b into the terminal for bottom and t for top
			Printing from the bottom up will print the worst ranked games first, 
			while printing from the top down will print the best ranked games
			- Then the bot will print out the top/bottom X results based on
			what the user chose along with the associated metric score (in yellow)
			- Bot prints out the time it took for each sorting algorithm to execute
			
		Option 2: Search Game
			- The bot will ask which category the user wants to search the game by
			- User inputs the number corresponding to which option
				- 1. Title
				- 2. Genre
				- 3. Year Released
				- 4. Publisher
				- 5. Release Consoles
				- 6. Exit the current stage (not the whole program)
			- Then the program will search through all the games and find matches
			- Each sorting algorithm is performed to print out the matching games
			in order of increasing metric score
			- All matching games and relevant data are printed out
			- The time it takes to execute the sorting algorithms is printed
			
