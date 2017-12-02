width = 0
height = 0
POINTS = 0
A = []
B = []
###
#filename = raw_input(".vtk Filename(except Extension) : ")
filename = "f"
#imgFile = raw_input(".bmp Filename(except Extension) : ")
imgFile = filename
###

POINTS_str = ""
objHeader = "# This file is generated from Renai prs file.\n"
mtlFile = "newmtl f\nKd 0.00 0.00 0.00\nKa 0.00 0.00 0.00\nTf 1.00 1.00 1.00\nmap_Kd "+imgFile+".bmp\nNi 1.00"
with open(imgFile+'.bmp','r') as f:
    print('Img load')
with open(filename+'.mtl','w') as f:
    f.write(mtlFile)
    
with open(filename+'.pcd','r') as f:
    txt = f.read()
    txt = txt.splitlines()

    #width
    width = int(txt[6].split()[1])
    height= int(txt[7].split()[1])
    print("Resolution : "+str(width)+"x" + str(height))
    
    POINTS = int(txt[9].split()[1])
    #header = header+str(POINTS)+" float\n"
    
    A = txt[11:POINTS+11]
    A_join = '\nv '.join(A)
    objHeader = objHeader +"mtllib "+filename+".mtl\nv "+ A_join +'\n'
    print("Number of POINTS : "+str(POINTS))
    
    for i in range(POINTS):
        A[i] = A[i].split()
        #print(A[i])
        for j in range(3):
            A[i][j] = -float(A[i][j])
        #print(A[i])
    print(".pcd Loaded")
    #print(header)

    c = 1
    tex_s = []
    with open(filename+'.txt','r') as tex:
        tex_s = tex.read()
        tex_s = tex_s.splitlines()
        #tex_join = '\nv '.join(tex_s)
        #or i in range(5):
        #    print(tex_s[i])
        for i in range(POINTS):
            tex_s[i] = tex_s[i].split()
            for j in range(2):
                tex_s[i][j] = float(tex_s[i][j])
            #print(tex_s[i])
    print(".texture Load ended: "+str(len(tex_s))+"")

with open(filename+'.obj','w') as f2:
    f2.write(objHeader)
    f2.write("usemtl "+filename+"\n")
    
    for j in range(height):
        for i in range(width):
            #print(i,j)
            f2.write("vt "+str(0.005+int(tex_s[j*width+i][0])/float(width))+" "+str(int(tex_s[j*width+i][1])/float(height))+"\n")
    
    for i in range(POINTS):
        if (i+width+1)<POINTS and (i+1)%width!=0:
            if abs(A[i][2]-A[i+width+1][2]) > abs(A[i+1][2] - A[i+width][2]):
                if(A[i][0] !=0 and A[i+width][0] !=0 and A[i+1][0] != 0):
                    f2.write(filename+" "+str(i+1+c)+"/"+ str(i+1+c)+" "+str(i+width+c)+"/"+str(i+width+c)+" "+str(i+c)+"/"+str(i+c)+"\n")
                if(A[i+width][0] !=0 and A[i+1][0] !=0 and A[i+width+1][0] != 0):
                    f2.write(filename+" "+str(i+width+c)+"/"+str(i+width+c)+" "+str(i+1+c)+"/"+str(i+1+c)+" "+str(i+width+1+c)+"/"+str(i+width+1+c)+"\n")
            else:
                if(A[i][0] !=0 and A[i+width][0] !=0 and A[i+width+1][0] != 0):
                    f2.write(filename+" "+str(i+width+1+c)+"/"+str(i+width+1+c)+" "+str(i+width+c)+"/"+str(i+width+c)+" "+str(i+c)+"/"+str(i+c)+"\n")
                if(A[i+1][0] !=0 and A[i+width+1][0] !=0 and A[i][0] != 0):
                    f2.write(filename+" "+str(i+1+c)+"/"+ str(i+1+c)+" "+str(i+width+1+c)+"/"+str(i+width+1+c)+" "+str(i+c)+"/"+str(i+c)+"\n")                    
    
