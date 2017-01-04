def main():
    # init change due var
    changef = 0;
    
    # get change due from user
    while True:
        changef = float(input("How much change is due? e.g. $0.84 : $"))
        if changef > 0:
            break;
    
    # init change_due and coins vars
    change_due = int(changef * 100)
    coins = 0
    coin_list = [25, 10, 5, 1]
    
    # loop through each coin
    for i in coin_list:
        # calculate max coins that can be deducted for this coin
        coins = coins + (change_due // i)
        # update change due
        change_due = (change_due % i)
    
    # return coin count to user
    print(coins)
    
# call main
if __name__ == "__main__":
    main()
    
    