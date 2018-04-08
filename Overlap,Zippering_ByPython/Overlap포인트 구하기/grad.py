import pprint
F_L1 = [620,380]
F_L2 = []
F_L3 = [680,480]

def getGradMore(P1, P3):
    if P1[0] == P3[0]:
        return 1.0
    return (P1[1] - P3[1])/float(P1[0] - P3[0])
def getGradDelPoint(P1,P3):
    m = getGradMore(P1, P3)
    k = (-P1[0]) * m + P1[1]

    lists = []
    for ele in range(P3[1], P1[1]-1, -1):
        lists.append([int((ele - k) / m), ele])
    return lists[:]

F_LL = getGradDelPoint(F_L1,F_L3)

pprint.pprint(F_LL)
