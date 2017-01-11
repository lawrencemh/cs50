# Harvard's CS50 Problem Sets

### Problem Set 1 (2016)
This brief problem set introduced me to the language of C where I implemented the following basic programs:
- [hello.c](/pset1/hello.c) - A simple program that prints "Hello World".
- [mario.c](/pset1/mario.c) - This program takes a int parameter n and prints a hash pyramid on screen of n height.
- [water.c](/pset1/water.c) - This program prompts the user for the length of their shower in minutes, and prints the equivalent bottles of water used.
- [greedy.c](/pset1/greedy.c) - Calculated the total minimum coins required to return a customer's change based on USD. 

### Problem Set 2 (2016)
In this problem set I started using C to manipulate ASCII characters and implement basic cryptology functions.
- [initials.c](/pset2/initials.c) - This program prompts the user for their full name and prints their initials to screen.
- [caesar.c](/pset2/caesar.c) - Caesar take one parameter n. The user can then enter a string which is then output where each character is moved n places to the right.
- [vigenere.c](/pset2/vigenere.c) - Vigenere improves on Caesar's very basic cryptology by iterating through a "key" which is passed as a parameter. The user enters a string where each character is then rotated to the right based on the index of the letter in the key as it is iterated through. For example, with an 8 letter string and a key of abc each character of the string would be rotated to the right by 12312312.

### Problem Set 3 (2016)
In this problem set I implemented the classic game of Fifteen using C and the Binary Search function for the program find.c
- [Fifteen.c](/pset3/fifteen/fifteen.c) - The classic game of Fifteen. This program takes one argument n being the size of the grid (e.g. n = 3 will result in a 3 x 3 grid).
- [Find.c](/pset3/find) - For the find.c application, I implemented the Binary Search and Bubble Sort functions in [helpers.c](/pset3/find/helpers.c).

### Problem Set 4 (2016)
This problem set presented two challenges. Firstly, restoring and resizing bmp images. Secondly, forensically analysing and restoring JPG images from a simulated corrupted FAT file system.
- [resize.c](/pset4/bmp/resize.c) Takes 3 inputs: n input_file output_file with n being the factor to resize (e.g. ./resize 3 smile.bmp smile_big.bmp).
- [whodunit.c](/pset4/bmp/whodunit.c) Takes two arguments (input_file output_file). Clue.bmp can be passed to whodunit.c which will restore the image by removing and repairing any red pixels.
- [recover.c](/pset4/jpg/recover.c) recovers any JPGs found in the card.raw file in the directory it is run. It will then extract each jpg in the current directory as 000.jpg, 001.jpg etc. card.raw is expected to be a FAT file system.

### Problem Set 5 (2016)
Here I had the opportunity to create a relatively fast spell checker and to create my own data structures in C using structs and pointers.
- [speller.c](/pset5/speller.c) - Takes two arguments [dictionary_path] text_to_check_path. Dictionary path is optional and by default dictionaries/large is used. In speller.c I implemented a Trie to load the entire dictionary in memory and allow words to be spell checked very fast with a worst case of O(n) where n is the length of the word. The additional challenge here using C was to ensure all memory blocks used by the trie are freed upon exit as to avoid any memory leakage. The checker works very fast loading 143,091 words into a trie in 0.15 seconds. The actual time to check, for example austinpowers.txt with 19,190 words only takes 0.01 seconds.

### Problem Set 6 (2017)
In Pset6 I had the opportunity to move away from C (which is a low level language) and start using Python! For this problem set I was required to port 3 of my previous programs I had created using C to help gain familiarity with Python's syntax. I chose to port greedy.c mario.c & vigenere.c. I also had the chance to create a very basic Python MVC application using Flask.
- [greedy.py](/pset6/greedy.py)
- [mario.py](/pset6/mario.py)
- [vigenere.py](/pset6/vigenere.py)
- [Sentiments](/sentiments)
- [smile](/sentiments/smile) - uses analyzer.py to categorise the word passed as an argument (e.g. ./smile good).
- [tweet](/sentiments/tweet) - uses analyzer.py and twitter's API to categorise a user's last 50 tweets (usage ./tweets @twitterHandler).
- [Flask App](/sentiments/application.py) Web application for Sentiments.

Sentiments is a very basic MVC Flask application that allows a user to analyse a twitter user's tweets from the homepage. A page containing a pie chart is then shown categorising the user's tweets as good, bad or neutral.
The sentiments application can be run when flask is installed using "flask run". However, a valid twitter API key and secret must be set in order to interact with Twitter's API. This can be set with the following commands:
- export API_KEY=value
- export API_SECRET=value

### Problem Set 7 (2017)
In pset7 I created a MVC web application allowing users to buy and sell stocks with a virtual portfolio. users can register for a personal account and have $10,000 pretend funds available by default. This application largely makes use of Yahoo's finance API.

 