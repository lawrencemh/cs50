import sys

def main():
    # check encryption string passed
    if len(sys.argv) != 2:
        print("Usage: <key>")
        return 1
    else:
        p = sys.argv[1]
 
    # check key is alpha!
    if not str.isalpha(p):
        print("Usage: <key>")
        return 1
    
    # get string from user to encrypt
    k = input()
    
    # init encryption key p loop
    j = 0
    pLen = int(len(p))
    
    # iterate through each character in k
    for char in k:
        # calculate how many char to shift using p[j]
        if str.isupper(p[j]):
            shiftBy = ord(p[j]) - 65
        else:
            shiftBy = ord(p[j]) - 97
        
        # only change & increment j if char is alpha
        if str.isalpha(char):
            # check if is upper / lower and shift accordingly
            if str.isupper(char):
                shift = (((ord(char) + shiftBy) - 65) % 26) + 65;
                char = chr(shift)
            elif str.islower(char):
                shift = (((ord(char) + shiftBy) - 97) % 26) + 97;
                char = chr(shift)
            
            # increment key counter as char is alpha
            j = ((j + 1) % pLen)
            
        # print character
        print (char, end="")
        
    # return success
    print("")
    return 0;

# call main function
if __name__ == "__main__":
    main()