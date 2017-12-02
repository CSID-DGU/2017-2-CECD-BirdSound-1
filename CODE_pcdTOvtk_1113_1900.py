width = 0
POINTS = 0
A = []
B = []
filename = raw_input(".vtk Filename(except Extension) : ")
#filename = "basic"
header = "# vtk DataFile Version 3.0\nvtk output\nASCII\nDATASET POLYDATA\nPOINTS "
POINTS_str = ""
with open(filename+'.pcd','r') as f:
    txt = f.read()
    txt = txt.splitlines()

    #width
    width = int(txt[6].split()[1])
    print("Width : "+str(width))
    
    POINTS = int(txt[9].split()[1])
    header = header+str(POINTS)+" float\n"
    
    A = txt[11:POINTS+11]
    A_join = '\n'.join(A)
    header = header + A_join
    print("Number of POINTS : "+str(POINTS))
    
    for i in range(POINTS):
        A[i] = A[i].split()
        for j in range(3):
            A[i][j] = float(A[i][j])
        #print(A[i])
    print("Load ended")
    #print(header)

#abs(A[i][2]-A[i+width+1][2]) > abs(A[i+1][2] - A[i+width][2]
with open(filename+'.vtk','w') as f2:
    f2.write(header)
    ct = 0
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
    
    f2.write("\n\nPOLYGONS "+str(ct)+" "+str(ct*4)+"\n")
    for i in range(POINTS):
        #print(i)
        #print("3 "+str(ini)+" "+str(ini+width)+" "+str(ini+1))
        if (i+width+1)<POINTS and (i+1)%width!=0:
            if abs(A[i][2]-A[i+width+1][2]) > abs(A[i+1][2] - A[i+width][2]):
                if(A[i][0] !=0 and A[i+width][0] !=0 and A[i+1][0] != 0):
                    f2.write("3 "+str(i)+" "+str(i+width)+" "+str(i+1)+"\n")
                if(A[i+width][0] !=0 and A[i+1][0] !=0 and A[i+width+1][0] != 0):
                    f2.write("3 "+str(i+width)+" "+str(i+1)+" "+str(i+width+1)+"\n")
            else:
                if(A[i][0] !=0 and A[i+width][0] !=0 and A[i+width+1][0] != 0):
                    f2.write("3 "+str(i)+" "+str(i+width)+" "+str(i+width+1)+"\n")
                if(A[i+1][0] !=0 and A[i+width+1][0] !=0 and A[i][0] != 0):
                    f2.write("3 "+str(i+1)+" "+str(i+width+1)+" "+str(i)+"\n")                    
                
    print(ct,ct*4)
    
