header =""
filename = "result"
A= []
B = []
C = []
with open(filename+'.txt','r') as f:
    txt = f.read()
    txt = txt.splitlines()
    print(len(txt))
    
    POINTS = len(txt)
    
    A = txt[:921600]
    B = txt[929280:1850880]
    C = txt[1858560:2780160]
    A = A[:]+B[:]+C[:]
    POINTS = len(A)
    print("Number of POINTS : "+str(POINTS))

#포인트 실수로 만들기 
    for i in range(POINTS):
        A[i] = A[i].split()
        for j in range(3):
            A[i][j] = float(A[i][j])
        if A[i][2]<0.4 or A[i][0] > 0.4 or A[i][0] <-0.1 or A[i][2] >0.8:
            A[i][0] =A[i][1]=A[i][2]=0.0
        else:
            A[i][0] = -A[i][0]
            A[i][1] = -A[i][1]
            A[i][2] = -A[i][2]
            

#전처리된 포인트 문자열로 만들기
A_str = []
for i in range(POINTS):
    tmp = []
    for j in range(3):
        tmp.append(str(A[i][j]))
    A_str.append('\t'.join(tmp))
A_str = '\n'.join(A_str)
header = header + A_str
print("Load ended")

with open(filename+"tmp"+'.txt','w') as f2:
    f2.write(header)
