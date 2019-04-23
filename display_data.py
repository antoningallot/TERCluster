import matplotlib.pyplot as plt
# import numpy as np
import random
from operator import itemgetter
import sys

def get_points(filename):
    f = open(filename, "r")
    res = list()
    cpt = 0
    for line in f:
        if cpt == 0: 
            cpt = cpt + 1
        else:
            newline = line.split()
            res.append( (float(newline[0]), float(newline[1])) )
    return res

def get_clusters(filename):
    f = open(filename, "r")
    res = list()
    for line in f:
        newline = line.split()
        res.append( (int(newline[0]), int(newline[1])) )
    return sorted(res, key=itemgetter(0))

def belongs(i, cluster):
    return i >= cluster[0] and i <= cluster[1]

def display(points, clusters):
    cpt = 0
    # clust = clusters[cpt]
    color = [[random.uniform(0, 1), random.uniform(0, 1), random.uniform(0, 1)]]
    fig = plt.figure()
    ax = fig.add_subplot(111)
    for i,p in enumerate(points):
        if(not belongs(i, clusters[cpt]) ):
            # print(i)
            cpt += 1
            color = [[random.uniform(0, 1), random.uniform(0, 1), random.uniform(0, 1)]]
        ax.scatter(p[0], p[1], c=color)
    # plt.plot(xlist, ylist, 'k.')
    plt.show()
    
filename_points = str(sys.argv[1])
# filename_results = filename_points[:len(filename_points)-4] + "_result.txt"
filename_results = str(sys.argv[2])
points = get_points(filename_points)
clusters = get_clusters(filename_results)
display(points, clusters)
