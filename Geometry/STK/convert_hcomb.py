#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 
#@
#@ Input & Output file names and other parameters
#@ Usage:
#@   python conver_silicon_v2.py
#@
input_file_name   = "./stk_hcomb.gdml"
#output_file_name  = "./stk_si_advanced.gdml"
output_file_name  = "./stk_hcomb_advanced.gdml"
SOLID_BASE_NAME   =  'DAM_ALLTRAY_Ass_Hcomb-stl0x89bfb0'  
#@
#@
#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


#@ GDML constants
VERTICES_PER_RECTANGLE = 12

#@ other constants
VOLUME_BASE_NAME = "STK_hcomb"

#@ STK constants
#@ others...
tmp_file_name     = "./tmp.txt"
tmp_file_name1    = "./tmp1.txt"
tmp_file_name2    = "./tmp2.txt"





#@
#@ Auxiliary gdml parsing functions   ---NOT USED YET!!!!
#@
def parce_vertices_for_gdml_file(filelines):
    vertices = {}
    for line in filelines:
        if "<position" not in line: continue
        name = line.split('name=')[1].split('"')[1]
        
        x = line.split('x=')[1].split('"')[1]
        if (".") in x:
            x = x.split(".")[0] + "." + x.split(".")[1][0:5]
        x = float(x)        
         
        y = line.split('y=')[1].split('"')[1]
        if (".") in y:
            y = y.split(".")[0] + "." + y.split(".")[1][0:5]
        y = float(y)
        
        z = line.split('z=')[1].split('"')[1]
        if (".") in z:
            z = z.split(".")[0] + "." + z.split(".")[1][0:5]
        z = float(z)
        
        if name in vertices: continue
        vertices[name] = [x,y,z] 
        
    return vertices


def find_vertices_for_resselated_solid(solidname, filelines):
    #@ Parce start and stop position
    startline = None
    stopline  = None        
    for i in xrange(len(filelines)):
        line = filelines[i]
        if "<tessellated" not in line: continue
        if solidname      not in line: continue
        startline = i
        break
    
    if startline is None:
        return None
    
    for i in xrange(startline + 1,len(filelines)):
        line = filelines[i]
        if "</tessellated>" not in line: continue
        stopline = i
        break
    
    if stopline is None:
        return None
    
    #@ Look for vertices
    vertices  = []
    for i in xrange(startline +1, stopline):
        line = filelines[i]
        if "triangular" not in line: continue
        vertexname1 = line.split('vertex1')[1].split('"')[1] #.split('"')[0]
        vertexname2 = line.split('vertex2')[1].split('"')[1] #.split('"')[0]
        vertexname3 = line.split('vertex3')[1].split('"')[1] #.split('"')[0]
        if vertexname1 not in vertices: vertices.append(vertexname1)
        if vertexname2 not in vertices: vertices.append(vertexname2)
        if vertexname3 not in vertices: vertices.append(vertexname3)
    return vertices


def get_foil_coordinates(all_vertices_info):
    #@
    all_z = []
    for vertexname in all_vertices_info.keys():
        z= all_vertices_info[vertexname][2]
        if z in all_z: continue
        all_z.append(z)    
    all_z = sorted(all_z)        
    #@
    return all_z

def get_vertices_for_line(line):
    vertexname1 = line.split('vertex1')[1].split('"')[1] #.split('"')[0]
    vertexname2 = line.split('vertex2')[1].split('"')[1] #.split('"')[0]    
    vertexname3 = line.split('vertex3')[1].split('"')[1] #.split('"')[0]
    return [vertexname1, vertexname2, vertexname3] 

def get_z_difference(line1,line2, allvertices):
    z = []
    for vertexname in get_vertices_for_line(line1)+get_vertices_for_line(line2):
        z.append(allvertices[vertexname][2])
    return max(z) - min(z)



#@ Read input file
input_file  = open(input_file_name,  "r")
lines = input_file.readlines()
input_file.close()
total_triangular_lines = len(filter(lambda line: "<triangular" in line, lines))
all_vertices_info = parce_vertices_for_gdml_file(lines)
all_z   = get_foil_coordinates(all_vertices_info)
triangular_counter     = 0  #@ number of <triangular> tags in input gdml file
tessellated_counter    = 1  #@ number of output subsolids (there is ata least one subsolid)

#@
#@ Create subsolids
#@ 
#output_file = open(output_file_name, "w")
tmpfile= open(tmp_file_name, "w")
tmpfile.write('    <tessellated aunit="deg" lunit="mm" name="'+ SOLID_BASE_NAME +'-%d">\n'%tessellated_counter)

for i in xrange(len(lines)):
    line = lines[i]        
    if not "<triangular" in line:
        continue    
    
    triangular_counter+=1    
    if  (triangular_counter * 1.0 / VERTICES_PER_RECTANGLE - triangular_counter  / VERTICES_PER_RECTANGLE == 0
         and triangular_counter > 0 
         and triangular_counter < total_triangular_lines): 
       
        tessellated_counter+=1
        tmpfile.write(line)
        tmpfile.write('    </tessellated>\n')        
        tmpfile.write('    <tessellated aunit="deg" lunit="mm" name="'+ SOLID_BASE_NAME +'-%d">\n'%tessellated_counter)
        continue
    
    tmpfile.write(line)    

tmpfile.write('    </tessellated>\n')
tmpfile.close()
    
    
    


#@
#@ Logival volumes
#@

#@ Cresete logical volumes

tmpfile = open(tmp_file_name,   'r') 
tmpfile_lines = tmpfile.readlines()
tmpfile.close()


tmpfile1     = open(tmp_file_name1, "w")
volume_names     = [] 
foil_counter   = 0
for i in xrange(1,tessellated_counter+1):
    
    #@ 
    #@ Assign name to a volume
    #@
    solid_name = SOLID_BASE_NAME + '-%d'%i
    vertex = find_vertices_for_resselated_solid(solid_name, tmpfile_lines)[0]    
    x, y, z = all_vertices_info[vertex]
    
    z_layer = all_z.index(z)         
    z_layer = z_layer /  2
    
        
    volume_name = VOLUME_BASE_NAME +"-%d"%z_layer
    volume_names.append(volume_name)
    
    #@ Create volume
    #tmpfile1.write('    <volume name="' + VOLUME_BASE_NAME + '-%d">\n'%i)
    tmpfile1.write('    <volume name="' + volume_name + '">\n')
    tmpfile1.write('      <materialref ref="Honeycomb"/>\n')
    tmpfile1.write('      <solidref ref="'+ solid_name + '"/>\n')
    tmpfile1.write('    </volume>\n')  
tmpfile1.close()


#@
#@ Physical volumes
#@
tmpfile2 = open(tmp_file_name2, "w")
for volume_name in volume_names:
    tmpfile2.write('      <physvol>\n')      
    #tmpfile.write('        <file name="./Geometry/STK/stk_si_advanced.gdml"/>\n')  
    tmpfile2.write('        <volumeref ref="' + volume_name+'"/>\n')
    #tmpfile.write('        <position x="stk_adjust_x_position" y="stk_adjust_y_position" z="stk_adjust_z_position" unit="mm"/>\n')
    tmpfile2.write('      </physvol>\n')  
tmpfile2.close()
#@ 




#@
#@ Combine things into the output file
#@
#
#output_file.close()
tmpfile     = open(tmp_file_name,  "r")
tmpfile1    = open(tmp_file_name1, "r")
tmpfile2    = open(tmp_file_name2, "r")
tmplines  = tmpfile.readlines()
tmplines1 = tmpfile1.readlines()
tmplines2 = tmpfile2.readlines()
tmpfile.close()
tmpfile1.close()
tmpfile2.close()

output_file = open(output_file_name, "w")
for line in lines:
    output_file.write(line)
    
    if "<solids>" in line:        
        for tmpline in tmplines:
            output_file.write(tmpline)
        continue
    
    if "<structure>" in line:
        for tmpline in tmplines1:
            output_file.write(tmpline)
        continue
    
    if '<solidref' in line and  SOLID_BASE_NAME in line:
        for tmpline in tmplines2:
            output_file.write(tmpline)
        continue
output_file.close()
    

        
        



       