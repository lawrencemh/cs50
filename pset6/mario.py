def main():
    # get height of pyramid from user
    height = 0
    while not (height > 0 and height <= 23):
        height = int(input("Enter a height: "))
    
    # init spaces and # variables
    spaces = height
    hash = 1
    
    # loop through each pyramid row
    for i in range(height):
        print(" " * spaces + "#" * hash + " " + "#" * hash + " " * spaces)
        # decrement spaces
        spaces -= 1
        # increment hashes
        hash += 1
    
# call main
if __name__ == "__main__":
    main()
    