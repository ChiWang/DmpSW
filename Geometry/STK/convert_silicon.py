#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 
#@
#@ Converts single the single solid, containting all the silicon detectors [output_file_name],
#@ into the true array of silicon detectors [output_file_name]  
#@ Usage:
#@   python conver_silicon.py
#@
#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


#@ Options:
input_file_name   = "./stk_si.gdml"
#output_file_name  = "./stk_si_advanced.gdml"
output_file_name  = "./stk_si_advanced.gdml"
SOLID_BASE_NAME   =  'DAM_TRKAss1_Si-stl0x11f2da0'       # (see stk_si.gdml)
VOLUME_BASE_NAME  =  'ActiveTile'                        # (see stk_si.gdml)
PLANE_BASE_NAME   =  'STKDetector'

#USE_LATEST_COORDINATE_SYSTEM = True



#@ GDML constants
VERTICES_PER_RECTANGLE = 12

#@ STK constants
N_LAYERS           = 6
N_X_TILES          = 8
N_Y_TILES          = 8
N_TILES_PER_PLANE  = 4
N_PLANES_PER_LAYER = 4
EVEN_LAYER_DETECTOR_TYPE = "Y"  #(counting layers from 0 to 11)
ODD_LAYER_DETECTOR_TYPE  = "X"

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


"""    
f=open("stk_si.gdml")
l=f.readlines()
a=parce_vertices_for_gdml_file(l)
f.close()
""" 


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



def get_STK_detector_coordinates(all_vertices_info, layers = "even"):
    #@
    all_z = []
    for vertexname in all_vertices_info.keys():
        z= all_vertices_info[vertexname][2]
        if z in all_z: continue
        all_z.append(z)    
    all_z = sorted(all_z)
        
    #@ get x,y -coordinates for readout-even/odd layers
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
            
        #@ Use only even layers
        if   layers == "even": 
            if z_layer%2:      continue
        elif layers == "odd":
            if z_layer%2 == 0: continue
        else:
            raise Exception("Illegal value for argument 'layers'")
            
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
all_x_even, all_y_even, all_z_even = get_STK_detector_coordinates(all_vertices_info,)
all_x_odd,  all_y_odd,  all_z_odd  = get_STK_detector_coordinates(all_vertices_info, "odd")
assert(len(all_x_even)==N_X_TILES * 2)
assert(len(all_y_even)==N_Y_TILES * 2)
assert(len(all_z_even)==N_LAYERS  * 2)
assert(len(all_x_odd)==N_X_TILES * 2)
assert(len(all_y_odd)==N_Y_TILES * 2)
assert(len(all_z_odd)==N_LAYERS  * 2)

#@ Cresete logical volumes
tmpfile1     = open(tmp_file_name1, "w")
volume_names     = [] 
detecto_even_counter = 0
detecto_odd_counter  = 0
for i in xrange(1,tessellated_counter+1):
    
    #@ 
    #@ Assign name to a volume
    #@
    solid_name = SOLID_BASE_NAME + '-%d'%i
    vertex = find_vertices_for_resselated_solid(solid_name, tmpfile_lines)[0]
    #print "all_vertices_info[vertex] : ", all_vertices_info[vertex]
    x, y, z = all_vertices_info[vertex]
    
    try:
        z_layer      = all_z_even.index(z)
        #if USE_LATEST_COORDINATE_SYSTEM: z_layer = len(all_z_even)-1-z_layer
        x_index      = all_x_even.index(x)        
        y_index      = all_y_even.index(y)
        #if USE_LATEST_COORDINATE_SYSTEM: y_index = len(all_y_even)-1-y_index 
        detecortype  = EVEN_LAYER_DETECTOR_TYPE
        detector_number = detecto_even_counter 
        detecto_even_counter += 1
    except ValueError:
        z_layer      = all_z_odd.index(z)
        #if USE_LATEST_COORDINATE_SYSTEM: z_layer = len(all_z_odd)-1-z_layer
        x_index      = all_x_odd.index(x)
        y_index      = all_y_odd.index(y)      
        #if USE_LATEST_COORDINATE_SYSTEM: y_index = len(all_y_odd)-1-y_index
        detecortype  = ODD_LAYER_DETECTOR_TYPE
        detector_number = detecto_odd_counter
        detecto_odd_counter += 1
        
    x_index = x_index /  2 
    y_index = y_index /  2 
    z_layer = z_layer /  2
    
    x_plane = x_index /  N_TILES_PER_PLANE
    y_plane = y_index /  N_TILES_PER_PLANE
    
    x_index_insideplane    = x_index %  N_TILES_PER_PLANE
    y_index_insideplane    = y_index %  N_TILES_PER_PLANE
    
    
    
    tilenumber_insideplane = x_index_insideplane*N_TILES_PER_PLANE + y_index_insideplane
    planenumber = z_layer* N_PLANES_PER_LAYER +  x_plane * N_PLANES_PER_LAYER/2 + y_plane     
    """
    print "\n---------------------"
    print "x_plane, y_plane, z_layer = ", x_plane, y_plane, z_layer
    print "\n---------------------"
    """    
    #volume_name = VOLUME_BASE_NAME + detecortype +"-%d"%detector_number + "_plane-%d"%planenumber
    #volume_name = VOLUME_BASE_NAME + detecortype + "-%d"%detector_number + "_" + PLANE_BASE_NAME + detecortype + "-%d"%planenumber
    #volume_name = VOLUME_BASE_NAME + detecortype + "-%d"%tilenumber_insideplane + "_" + PLANE_BASE_NAME + detecortype + "-%d"%planenumber
    volume_name = PLANE_BASE_NAME + detecortype + "-%d"%planenumber+"_"+VOLUME_BASE_NAME + detecortype + "-%d"%tilenumber_insideplane    
    volume_names.append(volume_name)
    
    #@ Create volume
    #tmpfile1.write('    <volume name="' + VOLUME_BASE_NAME + '-%d">\n'%i)
    tmpfile1.write('    <volume name="' + volume_name + '">\n')
    tmpfile1.write('      <materialref ref="Silicon"/>\n')
    tmpfile1.write('      <solidref ref="'+ solid_name + '"/>\n')
    tmpfile1.write('    </volume>\n')  
    
    
    """    
    if volume_name == (VOLUME_BASE_NAME + "X-0_" + PLANE_BASE_NAME + "X-19"):
        print "volume_name:", volume_name
        ver = find_vertices_for_resselated_solid(solid_name, tmpfile_lines)
    """
        
    
tmpfile1.close()


#@
#@ Physical volumes
#@
"""
tmpfile2 = open(tmp_file_name2, "w")
for i in xrange(1,tessellated_counter+1):
    tmpfile2.write('      <physvol>\n')      
    #tmpfile.write('        <file name="./Geometry/STK/stk_si_advanced.gdml"/>\n')  
    tmpfile2.write('        <volumeref ref="' + VOLUME_BASE_NAME + '-%d"/>\n'%i)
    #tmpfile.write('        <position x="stk_adjust_x_position" y="stk_adjust_y_position" z="stk_adjust_z_position" unit="mm"/>\n')
    tmpfile2.write('      </physvol>\n')  
tmpfile2.close()
"""
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
    

        
        













"""
#@ read file
f=open(input_file_name)
l=f.readlines()
f.close()
all_vertices_info=parce_vertices_for_gdml_file(l)
x,y,z = get_STK_detector_coordinates(all_vertices_info, "odd")
"""
        
          
"""
#@ Use it for silicons          
f=open("stk_si_advanced_v2.gdml")
l=f.readlines()
N_LAYERS  = 12
N_X_TILES = 8
N_Y_TILES = 8

#@ get all z for silicons
all_vertices_info=parce_vertices_for_gdml_file(l)
all_z = []
for i in xrange(1,tessellated_counter+1):
    solidname = SOLID_BASE_NAME + '-%d'%i
    verticesforsolid = find_vertices_for_resselated_solid(solidname,l)
    for vertexname in verticesforsolid:
        z= all_vertices_info[vertexname][2]
        if z in all_z: continue
        all_z.append(z)    
    #lowestvertices[solidname] = find_lowest_vertex_for_solid(all_vertices_info,verticesforsolid)
all_z   = sorted(all_z)
assert(len(all_z)==N_LAYERS * 2)

#@ get x-coordinates for readout-Y silicons
all_x = []
all_y = []
for tess_i in xrange(1,tessellated_counter+1):
    solidname = SOLID_BASE_NAME + '-%d'%tess_i
    verticesforsolid = find_vertices_for_resselated_solid(solidname,l)
    for vertexname in verticesforsolid:
        x= all_vertices_info[vertexname][0]
        y= all_vertices_info[vertexname][1]
        z= all_vertices_info[vertexname][2]
        
        #@ z_layer 0 -- 11
        z_layer = filter(lambda i: all_z[i]==z, xrange(len(all_z)))
        assert(len(z_layer)==1)
        z_layer = z_layer [0]
        z_layer = z_layer / 2
        
        #@ Use only even layers
        if z_layer%2:      continue  # readout Y
        #if z_layer%2 == 1: continue  # readout X
        
        #@ Append x, y coordinates
        if x not in all_x: all_x.append(x)
        if y not in all_y: all_y.append(y)    

all_x = sorted(all_x)
all_y = sorted(all_y)

assert(len(all_x) == 2 * N_X_TILES)
assert(len(all_y) == 2 * N_Y_TILES)

f.close()
"""




"""
#@ Use it for ladders
f=open("stk_ladders.gdml")
l=f.readlines()
N_LAYERS  = 12
N_X_TILES = 8
N_Y_TILES = 8



#@ get all z for silicons
all_vertices_info=parce_vertices_for_gdml_file(l)
tessellated_counter = len(all_vertices_info)
all_z = []
for i in xrange(1,tessellated_counter+1):    
    vertexname = all_vertices_info.keys()[i-1]
    z= all_vertices_info[vertexname][2]
    if z in all_z: continue
    all_z.append(z)    
    #lowestvertices[solidname] = find_lowest_vertex_for_solid(all_vertices_info,verticesforsolid)
all_z   = sorted(all_z)
assert(len(all_z)==N_LAYERS * 2)
  

#@ get x-coordinates for readout-Y (readpout-X?) silicons
all_x = []
all_y = []
for tess_i in xrange(1,tessellated_counter+1):    
    vertexname = all_vertices_info.keys()[tess_i-1]
    x= all_vertices_info[vertexname][0]
    y= all_vertices_info[vertexname][1]
    z= all_vertices_info[vertexname][2]
        
    #@ z_layer 0 -- 11
    z_layer = filter(lambda i: all_z[i]==z, xrange(len(all_z)))
    assert(len(z_layer)==1)
    z_layer = z_layer [0]
    z_layer = z_layer / 2
        
    #@ Use only even layers
    if z_layer%2 == 0: continue
        
    #@ Append x, y coordinates
    if x not in all_x: all_x.append(x)
    if y not in all_y: all_y.append(y)    

all_x = sorted(all_x)
all_y = sorted(all_y)

#assert(len(all_x) == 2 * N_X_TILES)
#assert(len(all_y) == 2 * N_Y_TILES)

f.close()
"""




         
        
        
        