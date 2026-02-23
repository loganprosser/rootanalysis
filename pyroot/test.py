import ROOT
import sys
from io import StringIO


f = ROOT.TFile.Open("/data2/segmentlinking/CMSSW_12_5_0_pre3/RelValTTbar_14TeV_CMSSW_12_5_0_pre3/event_1000.root
")
dir = f.Get("trackingNtuple")
t = dir.Get("tree")

buf = StringIO()

sys.stdout = buf

t.Print()

sys.stdout = sys.__stdout__

tree_info = buff.getvalue()
print(tree_info)

#a = t.Print()

#print(a)


# import ROOT
# import sys

# if len(sys.argv) != 3:
#     print(f" USAGE : {sys.argv[0]} <input file > <output file >")
#     sys.exit (1)
    
# inFileName = sys.argv[1]
# outFileName = sys.argv[2]
# print(f"Input file : {inFileName}")
# print(f"Output file : {outFileName}")