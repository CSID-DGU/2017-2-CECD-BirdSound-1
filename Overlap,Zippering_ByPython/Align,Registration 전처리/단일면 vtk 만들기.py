import math

width = 1280
POINTS = 921600

A = []
A_str = []

T= []
degree = 0
#filename = input(".vtk Filename(except Extension) : ")
filename = "resulttmp03"
header = "# vtk DataFile Version 3.0\nvtk output\nASCII\nDATASET POLYDATA\nPOINTS "
POINTS_str = ""
##
L1 = [710,340] #눈꼬리 
L2 = [] #코볼
L3 = [680,480] #입꼬리

F_L1 = [790,330]
F_L2 = []
F_L3 = [760,470] 

F_R1 = [620,380]
F_R2 = []
F_R3 = [680,480]

R1 = [740, 340]
R2 = []
R3 = [800, 460]
##
#when a point is zero to negative location, Mesh is right location


delPointList = []

T_F0 = [240,160]
A = []
B = []
C = []
#포인트 파일 가져오기
with open(filename+'.txt','r') as f:
    txt = f.read()
    txt = txt.splitlines()

    A = txt
    print(len(txt))
    #width
    print("Width : "+str(width))

    header = header+str(POINTS)+" float\n"
    
    A = txt[:]
    print("Number of POINTS : "+str(POINTS))

#포인트 실수로 만들기 
    for i in range(POINTS):
        A[i] = A[i].split()
        for j in range(3):
            A[i][j] = float(A[i][j])



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


#Mesh 갯수 확인하기 
ct = 0
ct_list = []
for i in range(POINTS):
    if (i+width+1)<POINTS and (i+1)%width!=0:
        if abs(A[i][2]-A[i+width+1][2]) > abs(A[i+1][2] - A[i+width][2]):
            if(A[i][0] !=0 and A[i+width][0] !=0 and A[i+1][0] != 0):
                ct+=1
            if(A[i+width][0] !=0 and A[i+1][0] !=0 and A[i+width+1][0] != 0):
                ct+=1
        else:
            if(A[i][0] !=0 and A[i+width][0] !=0 and A[i+width+1][0] != 0):
                ct+=1
            if(A[i+1][0] !=0 and A[i+width+1][0] !=0 and A[i][0] != 0):
                ct+=1

#Mesh 만들기 
for i in range(POINTS):
    if (i+width+1)<POINTS and (i+1)%width!=0:
        if abs(A[i][2]-A[i+width+1][2]) > abs(A[i+1][2] - A[i+width][2]):
            if(A[i][0] !=0 and A[i+width][0] !=0 and A[i+1][0] != 0):
                ct_list.append("3 "+str(i+1)+" "+str(i+width)+" "+str(i))
            if(A[i+width][0] !=0 and A[i+1][0] !=0 and A[i+width+1][0] != 0):
                ct_list.append("3 "+str(i+width)+" "+str(i+1)+" "+str(i+width+1))
        else:
            if(A[i][0] !=0 and A[i+width][0] !=0 and A[i+width+1][0] != 0):
                ct_list.append("3 "+str(i+width+1)+" "+str(i+width)+" "+str(i))
            if(A[i+1][0] !=0 and A[i+width+1][0] !=0 and A[i][0] != 0):
                ct_list.append("3 "+str(i+1)+" "+str(i+width+1)+" "+str(i))


#Mesh 만들면서 저장하기
ct_list = '\n'.join(ct_list)
header += "\n\nPOLYGONS "+str(ct)+" "+str(ct*4)+"\n"+ct_list
with open(filename+'.vtk','w') as f2:
    f2.write(header)
    
    print(ct,ct*4)
