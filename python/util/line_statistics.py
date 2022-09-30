import matplotlib.pyplot as plt
if __name__ == '__main__':
    with open(r"C:\Users\jlli.AGIOEMA\Desktop\1.txt") as f:
        nums = list(map(int, f.readlines()))
    plt.hist(nums,bins=50)
    #plt.boxplot(nums)
    plt.show()


