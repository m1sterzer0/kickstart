
import random
random.seed(1234)
print(100)
for i in range(100) :
    print(5)
    aa = [ random.randrange(1,1000001) for x in range(15) ]
    bb = [ random.randrange(1,1000001) for x in range(15) ]
    print(" ".join(str(x) for x in aa))
    print(" ".join(str(x) for x in bb))
    
