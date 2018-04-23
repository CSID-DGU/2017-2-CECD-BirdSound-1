import math
import pprint
import shelve
WIDTH = 1280
HEIGHT = 720
POINTS = 921600
A = []
A_str = []

#When you see the mesh model, the right mesh model is RI
RI = 0
FR = 1
LE = 2

T= []
PageNum = 3
filename = "resulttmp"
POINTS_str = ""

#filename = input(".vtk Filename(except Extension) : ")
header = "# vtk DataFile Version 3.0\nvtk output\nASCII\nDATASET POLYDATA\nPOINTS " +str(POINTS*PageNum)+" float\n"

#
#when a x point is zero to negative location, Mesh is right location
#when a y point is zero to nagative location, Mesh is upper location
 
##
L1 = [710,340] #눈꼬리 
L2 = [] #코볼
L3 = [680,480] #입꼬리

F_L1 = [620,380]
F_L2 = []
F_L3 = [680,480]

F_R1 = [790,330]
F_R2 = []
F_R3 = [760,470]
F_LL = []
F_RL = []

R1 = [740, 340]
R2 = []
R3 = [800, 460]
##

#포인트 파일 가져오기
def getXYZData():
    global header, A
    with open(filename+'.txt','r') as f:
        txt = f.read()
        txt = txt.splitlines()

        for i in range(PageNum):
            A.append(txt[POINTS*i:POINTS*(i+1)])
        print("Number of POINTS : "+str(POINTS*PageNum))

    #포인트 실수로 만들기
        for ix in range(PageNum):
            for i in range(POINTS):
                A[ix][i] = A[ix][i].split()
                for j in range(3):
                    A[ix][i][j] = float(A[ix][i][j])
    '''
        for i in range(POINTS):
        for j in range(3):
            A[RI][i][j] = 0.0
    '''

def getPointIdx(A):
    return A[0] + A[1]*WIDTH
def delPointFromTexture(point, page, direction):
    global A,T,POINTS
    T_ix = getPointIdx(point)
    print(T_ix)
    T_s = T[page][T_ix]
    if direction == "LEFT":
        for ix in range(POINTS):
            if T[page][ix][0] > T_s[0] : 
                A[page][ix][0] = A[page][ix][1] = A[page][ix][2] = 0.0
    else :
        for ix in range(POINTS):
            if T[page][ix][0] < T_s[0] : 
                A[page][ix][0] = A[page][ix][1] = A[page][ix][2] = 0.0

def getGrad(P1, P3):
    if P1[0] == P3[0]:
        print("분모 is 0 ")
        return exit(1)
    return (P1[1] - P3[1])/float(P1[0] - P3[0])
def getGradDelPoint(P1,P3):
    m = getGrad(P1, P3)
    k = (-P1[0]) * m + P1[1]

    lists = []
    for ele in range(P1[1],P3[1]):
        lists.append([int((ele - k) / m), ele])
        lists.append([int((ele - k) / m), ele])
        lists.append([int((ele - k) / m), ele])
    return lists[:]
def getDeleteIndex2(remainPage, deletePage, D1,remaine_list):
    del_point = []
    d_nxt =D1[:]
    del_point.append([remaine_list[0],d_nxt])
    WS_d = getWorkingSet(deletePage,d_nxt)
    for r_nxt in remaine_list:  #최대 하강 길이까지
        min_idx = 0
        min = 99999.0
        for d_idx in range(len(WS_d)):
            tmp = getDistance3D(A[remainPage][getPointIdx(r_nxt)],WS_d[d_idx])    #주변 점들의 거리를 계산하고

            if min > tmp :      #최소인 점 min에 대해
                min = tmp
                min_idx = d_idx
        d_nxt = getNextWorkingSetIndex(d_nxt,min_idx)
        del_point.append([r_nxt,d_nxt]) #그리고 해당점은 제거할 리스트에 넣는다.

        WS_d = getWorkingSet(deletePage, d_nxt)
        #print(min_idx)
    return del_point[:],0,1

def getDistance3D(P1,P2):
    return math.sqrt(pow(P1[0]-P2[0],2) + pow(P1[1]-P2[1],2)+pow(P1[2]-P2[2],2))
def getWorkingSet(page, P ):
    tmp = []
    P_idx = getPointIdx(P)
    P_idx = P_idx
    tmp.append(A[page][P_idx-1])
    tmp.append(A[page][P_idx])
    tmp.append(A[page][P_idx+1])
    P_idx = P_idx+WIDTH
    tmp.append(A[page][P_idx])
    #print("page:",page,P)
    return tmp[:]
def getNextWorkingSetIndex(now_p, idx):
    if idx == 0:
        return [now_p[0]-1,now_p[1]]
    elif idx == 1:
        return [now_p[0],now_p[1]]
    elif idx == 2:
        return  [now_p[0]+1,now_p[1]]
    elif idx == 3:
        return [now_p[0],now_p[1]+1]

def getDeleteIndex(remainPage, deletePage,remain_land_eye,remain_land_mouse,delete_land_eye,delete_land_mouse):
    del_point = []
    t = remain_land_mouse[1]
    pre = remain_land_eye[1]
    #print(t,pre)
    r_nxt = remain_land_eye[:]
    d_nxt =delete_land_eye[:]

    WS_r = getWorkingSet(remainPage,r_nxt)
    WS_d = getWorkingSet(deletePage,d_nxt)
    del_point.append([r_nxt,d_nxt])
    while(pre < t+120):  #최대 하강 길이까지
        min_idx = [0,0]
        min = 99999.0
        for r_idx in range(len(WS_r)):
            for d_idx in range(len(WS_d)):
                tmp = getDistance3D(WS_r[r_idx],WS_d[d_idx])    #주변 점들의 거리를 계산하고 

                if min > tmp :      #최소인 점 min에 대해 
                    min = tmp
                    min_idx = [r_idx,d_idx]
        #print(remainPage,getNextWorkingSetIndex(r_nxt,min_idx[0]),remain_land_mouse, getNextWorkingSetIndex(d_nxt,min_idx[1]), delete_land_mouse)
        if getNextWorkingSetIndex(r_nxt,min_idx[0]) == remain_land_mouse[0] or getNextWorkingSetIndex(d_nxt,min_idx[1]) ==  delete_land_mouse[0]: #점이 최대 x좌표 까지 간다면
            r_nxt = getNextWorkingSetIndex(r_nxt, 3)    #아래에 있는 점을 다음점으로 지정한다.
            d_nxt = getNextWorkingSetIndex(d_nxt, 3)
        elif getNextWorkingSetIndex(r_nxt,min_idx[0])[0] == remain_land_mouse[0]:
            r_nxt = getNextWorkingSetIndex(r_nxt, 3)
            d_nxt = getNextWorkingSetIndex(d_nxt,min_idx[1])
        elif getNextWorkingSetIndex(d_nxt,min_idx[1])[0]  ==  delete_land_mouse[0]:
            r_nxt = getNextWorkingSetIndex(r_nxt,min_idx[0]) 
            d_nxt = getNextWorkingSetIndex(d_nxt, 3)
        else:
            r_nxt = getNextWorkingSetIndex(r_nxt,min_idx[0])
            d_nxt = getNextWorkingSetIndex(d_nxt,min_idx[1])
            if r_nxt[:] == del_point[len(del_point)-1][0][:] and d_nxt[:] == del_point[len(del_point)-1][1][:] : #그런데 두 값이 같으면
                r_nxt = getNextWorkingSetIndex(r_nxt, 3)    #아래에 있는 점을 다음점으로 지정한다.
                d_nxt = getNextWorkingSetIndex(d_nxt, 3)
        del_point.append([r_nxt,d_nxt]) #그리고 해당점은 제거할 리스트에 넣는다. 

        pre = r_nxt[1]
        WS_r = getWorkingSet(remainPage, r_nxt)
        WS_d = getWorkingSet(deletePage, d_nxt)
        #print(min_idx)
    return del_point[:],0,1
def getDeletePoint(page, del_point,direction):
    part_dic_del_point = {}
    for idx in range(len(del_point)):
        if direction == "deleteNagative" :
            part_dic_del_point.setdefault(del_point[idx][page][1],WIDTH)
            if part_dic_del_point[del_point[idx][page][1]] > del_point[idx][page][0] :
                part_dic_del_point[del_point[idx][page][1]] = del_point[idx][page][0]
        elif direction == "deletePositive" :
            part_dic_del_point.setdefault(del_point[idx][page][1],0)
            if part_dic_del_point[del_point[idx][page][1]] < del_point[idx][page][0] :
                part_dic_del_point[del_point[idx][page][1]] = del_point[idx][page][0]

    del_point = []
    mesh_point = []
    part_list_x_del_point = []
    part_list_y_del_point = sorted(part_dic_del_point.keys())
    for item in part_list_y_del_point:
        part_list_x_del_point.append(part_dic_del_point[item])
    for j in range(len(part_list_y_del_point)):
        del_point.append([part_list_x_del_point[j],part_list_y_del_point[j]])

    return del_point[:]

#Overlap 제거
def deletePoint(page, direction, part_del_point, ):
        for idx in range(len(part_del_point)):
            st_0 = getPointIdx(part_del_point[idx])
            if direction == "deletePositive":
                part_del_point[idx][0] = part_del_point[idx][0]-1
                for ix in range(st_0  ,st_0+WIDTH):
                    #print(ix)
                    if ix % WIDTH == 0:
                        break
                    else:
                        for i in range(3):
                            A[page][ix][i] = 0.0

            elif direction == "deleteNagative":
                part_del_point[idx][0] = part_del_point[idx][0] + 1
                for ix in range(st_0, st_0 - WIDTH, -1):
                    # print(ix)
                    if ix % WIDTH == 0:
                        break
                    else:
                        for i in range(3):
                            A[page][ix][i] = 0.0
#전처리된 포인트 문자열로 만들기
def transPointToStr(A):
    A_str = []
    for i in range(POINTS):
        tmp = []
        for j in range(3):
            tmp.append(str(A[i][j]))
        A_str.append('\t'.join(tmp))
    A_str = '\n'.join(A_str)
    return A_str
#Mesh 갯수 확인하기
def confirmMeshNumber(A):
    ct = 0
    for i in range(POINTS):
        if (i+WIDTH+1)<POINTS and (i+1)%WIDTH!=0:
            if abs(A[i][2]-A[i+WIDTH+1][2]) > abs(A[i+1][2] - A[i+WIDTH][2]):
                if(A[i][0] !=0 and A[i+WIDTH][0] !=0 and A[i+1][0] != 0):
                    ct+=1
                if(A[i+WIDTH][0] !=0 and A[i+1][0] !=0 and A[i+WIDTH+1][0] != 0):
                    ct+=1
            else:
                if(A[i][0] !=0 and A[i+WIDTH][0] !=0 and A[i+WIDTH+1][0] != 0):
                    ct+=1
                if(A[i+1][0] !=0 and A[i+WIDTH+1][0] !=0 and A[i][0] != 0):
                    ct+=1
    return ct

#Mesh 만들기
def makeStrMesh(p1,p2,p3):
    return "3 "+str(p1)+" "+str(p2)+" "+str(p3)
def makeMesh(A,base):
    ct_list = []
    for i in range(POINTS):
        if (i+WIDTH+1)<POINTS and (i+1)%WIDTH!=0:
            if abs(A[i][2]-A[i+WIDTH+1][2]) > abs(A[i+1][2] - A[i+WIDTH][2]):
                if(A[i][0] !=0 and A[i+WIDTH][0] !=0 and A[i+1][0] != 0):
                    ct_list.append(makeStrMesh(base+i+1,base+i+WIDTH,base+i))
                if(A[i+WIDTH][0] !=0 and A[i+1][0] !=0 and A[i+WIDTH+1][0] != 0):
                    ct_list.append(makeStrMesh(base+i+WIDTH,base+i+1,base+i+WIDTH+1 ))
            else:
                if(A[i][0] !=0 and A[i+WIDTH][0] !=0 and A[i+WIDTH+1][0] != 0):
                    ct_list.append(makeStrMesh(base+i+WIDTH+1,base+i+WIDTH,base+i ))
                if(A[i+1][0] !=0 and A[i+WIDTH+1][0] !=0 and A[i][0] != 0):
                    ct_list.append(makeStrMesh(base+i+1,base+i+WIDTH+1,base+i ))
    return '\n'.join(ct_list)

def getMeshLine(part_del_point_0,part_del_point_1,page0,page1):
    now_ptr_s = 0
    connPoint = []
    for i in range(len(part_del_point_0)):
        min = 100.0
        min_idx = -1
        if A[page0][getPointIdx(part_del_point_0[i])][0] !=0.0:
            for j in range(len(part_del_point_1)):
                tmp = getDistance3D(A[page0][getPointIdx(part_del_point_0[i])],A[page1][getPointIdx(part_del_point_1[j])])
                if min>tmp:
                    min_idx = j
                    min = tmp
            if now_ptr_s !=0 and min_idx <= now_ptr_s:
                print(connPoint[len(connPoint)-1][1])
                connPoint.append([part_del_point_0[i], connPoint[len(connPoint)-1][1]])
            else:
                for idx in range(now_ptr_s,min_idx+1):
                    connPoint.append([part_del_point_0[i],part_del_point_1[idx]])
                now_ptr_s = min_idx+1
    return connPoint[:]
def addedMakeMesh(page0,page1,connP):
    addedmesh = []
    page0_base = page0*POINTS
    page1_base = page1*POINTS
    for idx in range(len(connP)-1):
        p1 = connP[idx][0]
        p2 = connP[idx+1][0]
        p3 = connP[idx+1][1]
        p4 = connP[idx][1]
        #add spatial mesh

        for s1,s2,i in list([[p1,p2,0],[p4,p3,1],[p2,p1,0],[p3,p4,1]]):
            if i==0:
                base = page0_base
                page = page0
            elif i==1:
                base = page1_base
                page = page1
            if p1[0] < p2[0] :
                for i in range(s2[0]-s1[0]-1):
                    pp1 = s1
                    pp2 = [s2[0]-i,s2[1]]
                    pp3 = [s2[0]-i-1, s2[1]]
                    print(A[page][getPointIdx(pp1)][0] ,A[page][getPointIdx(pp2)][0] , A[page][getPointIdx(pp3)][0])
                    if A[page][getPointIdx(pp1)][0] != 0.0 and A[page][getPointIdx(pp2)][0] != 0.0 and A[page][getPointIdx(pp3)][0] != 0.0:
                        addedmesh.append(makeStrMesh(getPointIdx(pp1) + base, getPointIdx(pp2) + base, getPointIdx(pp3) + base))
            if s1[0] > s2[0] :
                for i in range(s1[0]-s2[0]-1):
                    pp1 = s1
                    pp2 = [s2[0]+i+1, s2[1]]
                    pp3 = [s2[0]+i,s2[1]]
                    print(A[page][getPointIdx(pp1)][0] ,A[page][getPointIdx(pp2)][0] , A[page][getPointIdx(pp3)][0])
                    if A[page][getPointIdx(pp1)][0] != 0.0 and A[page][getPointIdx(pp2)][0] != 0.0 and A[page][getPointIdx(pp3)][0] != 0.0:
                        addedmesh.append(makeStrMesh(getPointIdx(pp1) + base, getPointIdx(pp2) + base, getPointIdx(pp3) + base))
        print('\n')
        if page0 == RI:    #메시 중
            if p1[0] < p2[0] :
                for i in range(p2[0]-p1[0]-1):
                    pp1 = p1
                    pp2 = [p2[0]-i,p2[1]]
                    pp3 = [p2[0]-i-1, p2[1]]
                    print(A[page0][getPointIdx(pp1)][0] ,A[page0][getPointIdx(pp2)][0] , A[page0][getPointIdx(pp3)][0])
                    if A[page0][getPointIdx(pp1)][0] != 0.0 and A[page0][getPointIdx(pp2)][0] != 0.0 and A[page0][getPointIdx(pp3)][0] != 0.0:
                        addedmesh.append(makeStrMesh(getPointIdx(pp1) + page0_base, getPointIdx(pp2) + page0_base, getPointIdx(pp3) + page0_base))
            if p1[0] > p2[0] :
                for i in range(p1[0]-p2[0]-1):
                    pp1 = p1
                    pp2 = [p2[0]+i+1, p2[1]]
                    pp3 = [p2[0]+i,p2[1]]
                    print(A[page0][getPointIdx(pp1)][0] ,A[page0][getPointIdx(pp2)][0] , A[page0][getPointIdx(pp3)][0])
                    if A[page0][getPointIdx(pp1)][0] != 0.0 and A[page0][getPointIdx(pp2)][0] != 0.0 and A[page0][getPointIdx(pp3)][0] != 0.0:
                        addedmesh.append(makeStrMesh(getPointIdx(pp1) + page0_base, getPointIdx(pp2) + page0_base, getPointIdx(pp3) + page0_base))
        #connect mesh
        if(getDistance3D(A[page0][getPointIdx(p1)],A[page1][getPointIdx(p3)]) < getDistance3D(A[page0][getPointIdx(p2)],A[page1][getPointIdx(p4)])):
            if A[page0][getPointIdx(p1)][0] != 0.0 and A[page1][getPointIdx(p3)][0] != 0.0 and A[page1][getPointIdx(p4)][0] != 0.0:
                addedmesh.append(makeStrMesh(getPointIdx(p1)+page0_base, getPointIdx(p3) + page1_base, getPointIdx(p4)+page1_base))
            if p1[:] != p2[:]:
                if A[page0][getPointIdx(p1)][0] != 0.0 and A[page0][getPointIdx(p2)][0] != 0.0 and A[page1][getPointIdx(p3)][0] != 0.0:
                    addedmesh.append(makeStrMesh(getPointIdx(p1) + page0_base, getPointIdx(p2) + page0_base, getPointIdx(p3) + page1_base))
        else:
            if A[page0][getPointIdx(p1)][0] != 0.0 and A[page0][getPointIdx(p2)][0] != 0.0 and A[page1][getPointIdx(p4)][0] != 0.0:
                addedmesh.append(makeStrMesh(getPointIdx(p1)+page0_base,getPointIdx(p2)+page0_base,getPointIdx(p4)+page1_base))
            if p3[:] != p4[:]:
                if A[page0][getPointIdx(p2)][0] != 0.0 and A[page1][getPointIdx(p3)][0] != 0.0 and A[page1][getPointIdx(p4)][0] != 0.0:
                    addedmesh.append(makeStrMesh(getPointIdx(p2)+page0_base, getPointIdx(p3) + page1_base, getPointIdx(p4)+page1_base))
    return addedmesh[:]
''''''''''''

'''
#image로 부터 점 제거
delPointFromTexture(F_L1,FR,"LEFT")
delPointFromTexture(F_R1,FR,"RIGHT")
delPointFromTexture(L2,LE,"RIGHT")
'''

'''

getXYZData()

#FR 이미지의 포인트 구하기
F_LL = getGradDelPoint([F_L1[0]-30,F_L1[1]-100],F_L1)+getGradDelPoint(F_L1,F_L3)+getGradDelPoint(F_L3,[F_L3[0]+10,HEIGHT])
F_RL = getGradDelPoint([F_R1[0]+30,F_R1[1]-100],F_R1)+getGradDelPoint(F_R1,F_R3)+getGradDelPoint(F_R3,[F_R3[0]+200,HEIGHT])
#FR 기준에서 가장 가까운점 구하기

#중첩된점 구하기
print("\tget \t\tOverlap Point ")
#del_tmp_point_frle,frle_point_page_FR,frle_point_page_LE = getDeleteIndex(FR,LE,F_L1,F_L3,L1,L3)
del_tmp_point_frle,frle_point_page_FR,frle_point_page_LE = getDeleteIndex2(FR,LE,[L1[0]-30,L1[1]-100],F_LL)
part_del_point_frle_FR = getDeletePoint(frle_point_page_FR, del_tmp_point_frle, "deletePositive")
part_del_point_frle_LE = getDeletePoint(frle_point_page_LE, del_tmp_point_frle,"deleteNagative")  #deleteNagative / deletePositive

#del_tmp_point_frri,frri_point_page_FR,frri_point_page_RI = getDeleteIndex(FR,RI,F_R1,F_R3,R1,R3)
del_tmp_point_frri,frri_point_page_FR,frri_point_page_RI = getDeleteIndex2(FR,RI,[R1[0]+30,R1[1]-100],F_RL)
part_del_point_frri_FR = getDeletePoint(frri_point_page_FR, del_tmp_point_frri, "deleteNagative")
part_del_point_frri_RI = getDeletePoint(frri_point_page_RI,del_tmp_point_frri,"deletePositive")  #deleteNagative / deletePositive




#중첩된 점 제거
print("\tdelete \t\tOverlap Point ")
deletePoint(FR,"deleteNagative",part_del_point_frle_FR)
deletePoint(LE,"deletePositive",part_del_point_frle_LE)

deletePoint(FR,"deletePositive",part_del_point_frri_FR)
deletePoint(RI,"deleteNagative",part_del_point_frri_RI)

#point를 str으로 생성
print("\ttranslate points to string")
header += transPointToStr(A[RI]) +"\n"
header += transPointToStr(A[FR]) +"\n"
header += transPointToStr(A[LE])
print("Load ended\n")

#파일 임시 저장
sF = shelve.open('preDate')

sF['A'] = A
sF['header'] = header
sF['part_del_point_frle_FR'] =part_del_point_frle_FR
sF['part_del_point_frle_LE'] =part_del_point_frle_LE
sF['part_del_point_frri_FR'] =part_del_point_frri_FR
sF['part_del_point_frri_RI'] =part_del_point_frri_RI
sF.close()
exit(1)
'''
#파일 불러오기
print('*** Load Shelf File ***\n')
sF = shelve.open('preDate')
A = sF['A']
header = sF['header']
part_del_point_frle_FR = sF['part_del_point_frle_FR']
part_del_point_frle_LE = sF['part_del_point_frle_LE']
part_del_point_frri_FR = sF['part_del_point_frri_FR']
part_del_point_frri_RI = sF['part_del_point_frri_RI']
print('*** Finished Shelf File ***\n')

#Mesh 연결할 Polygon 구하기
print("\tget \t\tMesh Polygon")
connPoint_frle = getMeshLine(part_del_point_frle_FR, part_del_point_frle_LE,FR,LE)
addedmesh_frle = addedMakeMesh(FR,LE, connPoint_frle)
print("\t\tconnect \tPoint Length(frle) : ", len(connPoint_frle))

connPoint_frri = getMeshLine(part_del_point_frri_RI,part_del_point_frri_FR,RI,FR)
addedmesh_frri = addedMakeMesh(RI,FR, connPoint_frri)
print("\t\tconnect \tPoint Length(frri) : ", len(connPoint_frri))


#만들어질 Mesh 갯수 구하기
print("Get \tMesh")
A_ct = confirmMeshNumber(A[RI])
A_ct_list = makeMesh(A[RI],POINTS*RI)

B_ct = confirmMeshNumber(A[FR])
B_ct_list = makeMesh(A[FR],POINTS*FR)

C_ct = confirmMeshNumber(A[LE])
C_ct_list = makeMesh(A[LE],POINTS*LE)


#Polygon 출력하기
print(" ")
print("Ready for writting Mesh Polygon")
ct = A_ct+B_ct+C_ct
ct += len(addedmesh_frle)
ct += len(addedmesh_frri)
addedmesh_list = ""
addedmesh_list += '\n'.join(addedmesh_frle) +"\n"
addedmesh_list += '\n'.join(addedmesh_frri)


#Mesh 만들면서 저장하기
print("\twrtie Polygon",ct )
header += "\n\nPOLYGONS "+str(ct)+" "+str(ct*4)+"\n"+A_ct_list+"\n"+B_ct_list +"\n"+C_ct_list +"\n" +addedmesh_list
with open(filename+'.vtk','w') as f2:
    f2.write(header)
