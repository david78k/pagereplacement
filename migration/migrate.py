#!/usr/bin/python

"""Make a diagram."""

# Written by Felix Wiemann <http://www.ososo.de/>, licensed under GPL-2.
# Edited by Tae Seung Kang, 2/18/2014

import algorithms
import access
import random
import simulate
import Gnuplot

physicalpages = 64 # total number of physical pages
physicalpages = 5 # total number of physical pages
virtualpages = 10000 # total number of virtual pages
accesscount = 100000 # total number of memory access

d = []    # List of gnuplot data
"""for i in [algorithms.FIFO, algorithms.SecondChance, algorithms.NRU,
          algorithms.LRU, algorithms.Aging]: #, algorithms.Optimal]:
"""
for i in [algorithms.PRE]:
    # List of tupels of (ws_length, page_faults_to_accesses_ratio).
    ratios = []
    for j in range(1, 5):
    #for j in range(1, 61):
        mms = i(physicalpages)    # Instantiate with the number of totalpages of physical memory.
        mms.shift = 200	# for Aging and NRU algorithms
        mms.firstbit = 1 << 7 # for Aging algorithm

	mms.migrate()
"""
	# create a working set from virtual page numbers ranging 0 to 9999
        ws = access.wsmake(mem=range(virtualpages), rand=random, size=j)

	# create a access list
        mms.alist = access.makealist(range(virtualpages), ws, random, 0.95, accesscount)
	
	# simulate accessing the physical memory to read pages in the access list
	# and append the ratio of page faults
        ratios.append((j, simulate.simulate(mms, mms.alist)))

        print i.__name__ + ": " + str(j)

    d.append(Gnuplot.Data(ratios, title=i.__name__, inline=1))

g = Gnuplot.Gnuplot()
#g('set data style lines')
#g('set style data lines')
g('set style data linespoints')
g('set yrange [0:]')
g('set terminal epslatex monochrome')
g('set output "migrate.eps"')
g('set xlabel "working set size in pages"')
g('set ylabel "ratio of page faults to accesses"')
g.plot(*d)

g('set terminal png')
g('set output "migrate.png"')
g.plot(*d)

#print "\nNow move diagram1.* to ../"
"""
