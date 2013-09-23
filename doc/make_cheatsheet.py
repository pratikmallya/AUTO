#! /usr/bin/env python

import os
import string
import re

cheat_sheet_string = ""
def append(text):
    global cheat_sheet_string
    cheat_sheet_string = cheat_sheet_string + text 


header= """
\documentclass[12pt]{report}

\usepackage{epsf}
\usepackage{include/harvard}
\usepackage{longtable}
\usepackage{float}
\usepackage{xr}
\externaldocument{auto}
\pagestyle{plain}
\\topmargin=-45pt
\\textwidth=6.85in
\\textheight=9in
\evensidemargin=-15pt
\oddsidemargin=-15pt
%
\input{macros}

\\begin{document}
"""

footer = """
\end{document}
"""

constants = open("constants.tex","r")
constants = constants.read()
os.system("cp include/harvard.sty /tmp")
nameList  = ["NDIM","IPS","IRS","ILP","NICP","ICP",
             "NTST","NCOL","IAD","ISP","ISW","IPLT",
             "NBC","NINT","NMX","RL0","RL1","A0",
             "A1","NPR","MXBF","IID","ITMX","ITNW",
             "NWTN","JAC","EPSL","EPSU","EPSS","DS",
             "DSMIN","DSMAX","IADS","NTHL","NTHU","NUZR"]

nameList.sort()
append(header)

append("{\\footnotesize\n")
append("\\begin{tabular}{|l|p{5in}|}\n")
append("\\hline \n")
for name in nameList:
    match = re.search("%%AUTODOC %s SHORT(.*)%%AUTODOC %s FULL"%(name,name),
                      constants,re.S)
    doc = string.replace(match.group(1),"%","")
    append(name+" & "+doc +"\\\ " )
    append("\\hline \n")

append("\\end{tabular}\n")


append("\n\n\\pagebreak\n\n")

append("\\begin{longtable}{|l|p{5in}|}\n")
append("\\hline \n")
for name in nameList:
    match = re.search("%%AUTODOC %s TEX(.*)%%AUTODOC %s END"%(name,name),
                      constants,re.S)
    doc = match.group(1)
    if name != "IPS":
        append(name+" & "+doc +"\\\ " )
    else:
        append(name+" & {\\tiny "+doc +" }\\\ " )
        
    append("\\hline \n")
append("\\end{longtable}\n")
append("}")
    
append(footer)
output = open("cheat_sheet.tex","w")
output.write(cheat_sheet_string)



