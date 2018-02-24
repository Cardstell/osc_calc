import sys
from math import *
x = -float(sys.argv[1])
out = ""
while (x<=float(sys.argv[1])):
	try:
		tmp = eval(sys.argv[3].replace("x","("+str(x)+")"))
		out += str(tmp)+";"
	except:
		out += "ERROR;"
	x += float(sys.argv[1])/float(sys.argv[2])*2
print out

