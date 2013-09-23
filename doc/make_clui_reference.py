#! /usr/bin/env python

import os
import string
import re
import AUTOCommands

clui_reference_string = ""
def append(text):
    global clui_reference_string
    clui_reference_string = clui_reference_string + text 

commandList = []
append("\\begin{longtable}{|l|p{1.5in}|p{2in}|}\n")
append("\\hline \n")
command = AUTOCommands.commandHelp("")
helpDict = command().data
append("Command & Aliases & Description\\\ " )
append("\\hline \n")
keys = helpDict.keys()
keys.sort()
for key in keys:
    aliases = ""
    for alias in  helpDict[key]['aliases']:
        aliases = aliases + alias + " "
    append(key+" & "+aliases+" & "+helpDict[key]['description']+"\\\ " )
    append("\\hline \n")
    commandList.append(key)

append("\\end{longtable}\n")

output = open("clui_quick_reference.tex","w")
output.write(clui_reference_string)

clui_reference_string = ""
for command in commandList:
    func = AUTOCommands.commandHelp(command)
    doc = func().data
    aliases = ""
    for alias in  doc['aliases']:
        aliases = aliases + alias + " "
    append("\\subsection{%s} \\label{sec:clui_ref_%s}"%(command,command))
    append("\\begin{minipage}{6in}")
    append("\\hrule")
    append("\\medskip")
    append("\\section*{Purpose}\n")
    append(doc["short description"])
    append("\\section*{Description}\n")
    #append("\\begin{alltt}{\\rm")
    append(doc["long description"])
    #append("}\\end{alltt}")
    append("\\section*{Aliases}\n")
    append(aliases)
    append("\\medskip")
    append("\\hrule")
    append("\\end{minipage}")
    #append("\\pagebreak")

output = open("clui_reference.tex","w")
output.write(clui_reference_string)


