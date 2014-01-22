#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 
#@
#@ Input & Output file names and other parameters
#@ Usage:
#@   python conver_silicon_v2.py
#@
input_file_name   = "./stk_tungsten.gdml"
#output_file_name  = "./stk_si_advanced.gdml"
output_file_name  = "./stk_tungsten_advanced.gdml"
SOLID_BASE_NAME   =  'DAM_ALLTRAY_Ass_TUNGSTEN-stl0x2044830'  
#@
#@
#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


#@ GDML constants
VERTICES_PER_RECTANGLE = 12

#@ STK constants
N_LAYERS           = 4  #3
N_X_TILES          = 4
N_Y_TILES          = 4
THIN_LAYERS        = [1,2,3]  #[0,1,2]
THICK_LAYERS       = [0]      # []
THIN_CONVERTER_NAME  = "Converter"
THIN_LAYER_NAME      = "PlaneThinW"  
THICK_CONVERTER_NAME = "ThickConverter"
THICK_LAYER_NAME     = "PlaneThickW"

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
        x = x.split(".")[0] + "." + x.split(".")[1][0:5]
        x = float(x)        
         
        y = line.split('y=')[1].split('"')[1]
        y = y.split(".")[0] + "." + y.split(".")[1][0:5]
        y = float(y)
        
        z = line.split('z=')[1].split('"')[1]
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



def get_converter_coordinates(all_vertices_info, layers):
    #@
    all_z = []
    for vertexname in all_vertices_info.keys():
        z= all_vertices_info[vertexname][2]
        if z in all_z: continue
        all_z.append(z)    
    all_z = sorted(all_z)
        
    #@ get x,y -coordinates for [layers] of converter
    final_x = []
    final_y = []
    final_z = []
    for vertexname in all_vertices_info.keys():
        x= all_vertices_info[vertexname][0]
        y= all_vertices_info[vertexname][1]
        z= all_vertices_info[vertexname][2]
            
        #@ z_layer 0 -- 11
        z_layer = all_z.index(z)        
        z_layer = z_layer / 2
            
        #@ Use only layers in [layers]        
        if z_layer not in layers:
            continue        
            
        #@ Append x, y coordinates
        if x not in final_x: final_x.append(x)
        if y not in final_y: final_y.append(y)    
        if z not in final_z: final_z.append(z)
    
    final_x = sorted(final_x)
    final_y = sorted(final_y)
    final_z = sorted(final_z)
    
    return final_x, final_y, final_z















#@ Read input file
input_file  = open(input_file_name,  "r")
lines = input_file.readlines()
input_file.close()
total_triangular_lines = len(filter(lambda line: "<triangular" in line, lines))
triangular_counter     = 0  #@ number of <triangular> tags in input gdml file
tessellated_counter    = 1  #@ number of output subsolids (there is ata least one subsolid)

#@
#@ Create subsolids
#@ 
#output_file = open(output_file_name, "w")
tmpfile= open(tmp_file_name, "w")
tmpfile.write('    <tessellated aunit="deg" lunit="mm" name="'+ SOLID_BASE_NAME +'-%d">\n'%tessellated_counter)

for line in lines:        
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

#@ Analyze tracker coordinates
f       = open(input_file_name, 'r')
tmpfile = open(tmp_file_name,   'r') 
l=f.readlines()
tmpfile_lines = tmpfile.readlines()
f.close()
tmpfile.close()
all_vertices_info=parce_vertices_for_gdml_file(l)
all_x_thin,   all_y_thin,  all_z_thin   = get_converter_coordinates(all_vertices_info, THIN_LAYERS)
all_x_thick,  all_y_thick, all_z_thick  = get_converter_coordinates(all_vertices_info, THICK_LAYERS)
if THIN_LAYERS:
    assert(len(all_x_thin)==N_X_TILES * 2)
    assert(len(all_y_thin)==N_Y_TILES * 2)
    assert(len(all_z_thin)==len(THIN_LAYERS)* 2)
if THICK_LAYERS:
    assert(len(all_x_thick)==N_X_TILES * 2)
    assert(len(all_y_thick)==N_Y_TILES * 2)
    assert(len(all_z_thick)==len(THICK_LAYERS)* 2)

#@ Cresete logical volumes
tmpfile1     = open(tmp_file_name1, "w")
volume_names     = [] 
converter_thin_counter   = 0
converter_thick_counter  = 0
for i in xrange(1,tessellated_counter+1):
    
    #@ 
    #@ Assign name to a volume
    #@
    solid_name = SOLID_BASE_NAME + '-%d'%i
    vertex = find_vertices_for_resselated_solid(solid_name, tmpfile_lines)[0]    
    x, y, z = all_vertices_info[vertex]
    
    try:
        z_layer          = all_z_thin.index(z)
        #x_plane          = all_x_thin.index(x)
        #y_plane          = all_y_thin.index(y)
        convertername    = THIN_CONVERTER_NAME
        layername        = THIN_LAYER_NAME
        converter_number = converter_thin_counter 
        converter_thin_counter += 1
    except ValueError:
        z_layer          = all_z_thick.index(z)        
        #x_plane          = all_x_thick.index(x)
        #y_plane          = all_y_thick.index(y)
        convertername    = THICK_CONVERTER_NAME
        layername        = THICK_LAYER_NAME
        converter_number = converter_thick_counter 
        converter_thick_counter += 1
        
    #x_plane = x_plane /  2 
    #y_plane = y_plane /  2 
    z_layer = z_layer /  2
    
        
    volume_name = convertername +"-%d"%converter_number+"_"+layername+"-%d"%z_layer
    volume_names.append(volume_name)
    
    #@ Create volume
    #tmpfile1.write('    <volume name="' + VOLUME_BASE_NAME + '-%d">\n'%i)
    tmpfile1.write('    <volume name="' + volume_name + '">\n')
    tmpfile1.write('      <materialref ref="Tungsten"/>\n')
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
    

        
        



       