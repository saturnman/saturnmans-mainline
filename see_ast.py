# see_ast.py
# author: saturnman
# usage:  see_ast.py original_filename
#!/usr/bin/env python
import sys
import os
import re
global_struct_number = 0
filename = "" 
#global_struct_number = 0
global outfile
def start_function(title,func_count):
    global global_struct_number
    global outfile
    global filename
    name = "default"
    name_match =  re.search('[a-z]+[ a-zA-Z_][a-zA-Z_0-9]*',title)
    if(name_match!=None):
        name = title[name_match.start():name_match.end()]
        name = name[name.find(" "):].strip()
    global_struct_number = global_struct_number+1
    filename = name+"."+str(global_struct_number)+".dot" 
    outfile = open(filename,'w')
    line_content =  "digraph G"+str(func_count)+"{ \n node [shape=record]\n edge[color=red]; ranksep=2.5;\n"
    print line_content
    outfile.write(line_content)
def end_function():
    global outfile
    global filename
    line_content = "}"
    print line_content
    outfile.write(line_content+"\n")
    outfile.close()
    command = "dot -Tsvg "+ filename + " -o " +filename.replace("dot","svg")
    print "exec "+command
    os.system(command)
def gen_node(node_line):
    global global_struct_number;
    global outfile
    global colorList
    global colorindex
    #print "DEBUG LINE,",node_line
    #print "DEBUG LINE LENGTH,",len(node_line)
    #gen struct
    #print ,[shape=record,label="{",
    id = re.match('@\d+',node_line)
    if(id!=None):
        #gen id
        line_content = node_line[id.start():id.end()].replace("@","AT")+"[shape=record,label=\"{"+"{id:"+node_line[id.start():id.end()]+"|"
        outfile.write(line_content)
        print line_content,
    type = re.search('[a-z_]+',node_line)
    if(type!=None):
        #gen type
        line_content =  "TreeType:"+node_line[type.start():type.end()]+"}|"
        outfile.write(line_content)
        print line_content,
    iterator =  re.finditer('[ ][ a-zA-Z0-9@]*[ ]*:[ ]*[_\-@a-zA-Z0-9:\.]+',node_line)
    match = None;
    line_content = "{"
    outfile.write(line_content)
    print line_content,
    while True:
        try:
            match = iterator.next();
            prop = node_line[match.start():match.end()]
            prop_iter = re.finditer('@\d+',prop)
            for prop_match in prop_iter:
                prop = "<"+prop[prop_match.start():prop_match.end()].replace("@","AT")+">"+prop
            line_content = prop+" | "
            outfile.write(line_content)
            print line_content,
        except StopIteration:
            if(match!=None):
                prop = node_line[match.start():match.end()]
                prop_iter = re.finditer('@\d+',prop)
                for prop_match in prop_iter:
                    prop = "<"+prop[prop_match.start():prop_match.end()].replace("@","AT")+">"+prop
                line_content = "-"+"}}\"];"
                #end
                outfile.write(line_content)
                print line_content,
            else:
                line_content = "-"+"}}\"];"
                #end
                outfile.write(line_content)
                print line_content,
            break
    line_content = "\n"
    outfile.write(line_content)
    print line_content,
    prop_iterator =  re.finditer('[ ][ a-zA-Z0-9@]*[ ]*:[ ]*[_\-@a-zA-Z0-9:\.]+',node_line)
    property_line_match = None;
    while True:
        try:
            property_line_match = prop_iterator.next();
            prop2 = node_line[property_line_match.start():property_line_match.end()]
            prop_item_iter = re.finditer('@\d+',prop2)
            for property_item_match in prop_item_iter:
                if(id!=None):
                    line_content =  node_line[id.start():id.end()].replace("@","AT")+":"+prop2[property_item_match.start():property_item_match.end()].replace("@","AT")+"->"+prop2[property_item_match.start():property_item_match.end()].replace("@","AT")+";"+"edge[color="+colorList[colorindex%len(colorList)]+"];\n"
                    colorindex += 1
                    outfile.write(line_content)
                    print line_content,
        except StopIteration:
            if(property_line_match!=None):
                prop2 = node_line[property_line_match.start():property_line_match.end()]
                prop_item_iter = re.finditer('@\d+',prop)
                for property_item_match in prop_item_iter:
                    if(id!=None):
                        line_content = node_line[id.start():id.end()].replace("@","AT")+":"+prop2[property_item_match.start():property_item_match.end()].replace("@","AT")+"->"+prop2[property_item_match.start():property_item_match.end()].replace("@","AT")+";"+"edge[color="+colorList[colorindex%len(colorList)]+"];\n"
                        colorindex += 1
            break
    line_content = "\n"
    outfile.write(line_content)
    print line_content,

colorList = ['red','black','purple','maroon','orange','deepskyblue','indigo','dodgerblue','plum','mediumpurple','limegreen','navy','indigo']
colorindex = 0
if len(sys.argv) <2:
    print "raw original tree file as input."
    exit()
file = open(sys.argv[1])
lines = file.readlines();
function_count = 0
lines_sum = ""
has_function = False
global global_struct_number
global outfile
global_struct_number = 0
for line in lines:
    if(len(line.strip())>0):
        #start of an function
        if(line.find(";;")==0 and line.find("Function")!=-1): 
            if(has_function == False):
                has_function = True
            else:
                if len(lines_sum.strip())>0:
                    gen_node(lines_sum)
                    end_function()
                #print "#end function"
                lines_sum = ""
            title = line[line.find("Function ")+len("Function "):]
            #print "#start function ",title
            function_count += 1
            start_function(title,function_count)
        elif(line.find(";;")==0 and line.find("Function")==-1):
            line_content = "\n"
            outfile.write(line_content)
            print line_content,
        elif(line.find("@")==0):
            #print lines_sum
            if len(lines_sum.strip())>0:
                gen_node(lines_sum)
            lines_sum = ""
            lines_sum += line.replace("\n"," ")
        else:
            lines_sum += line.replace("\n"," ")
# gen last line
if len(lines_sum.strip())>0:
    gen_node(lines_sum)
    end_function()
#print "#end function"

