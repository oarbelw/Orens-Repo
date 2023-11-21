from random import sample

txtfiles = ["d1.txt","d2.txt","d3.txt","d4.txt","d5.txt","d6.txt"]
fulldict = "dictionary.txt"
# for tf in txtfiles:
with open(fulldict, 'r') as fp:
    entries = fp.read().splitlines()
    print('Total lines:', len(entries))
    d1len = sample(entries,1000)
    d2len = sample(entries,2000)
    d3len = sample(entries,4000)
    d4len = sample(entries,6000)
    d5len = sample(entries,8000)
    d6len = sample(entries,10000)
    tlens = [d1len, d2len, d3len, d4len, d5len, d6len]

for i in range(len(tlens)):
    with open(txtfiles[i], 'w') as f:
        for item in tlens[i]:
            print(item)
            f.writelines(item+"\n")
f.close()
