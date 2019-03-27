import matplotlib.pyplot as plt
# import numpy as np
import random

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
    return res

def belongs(i, cluster):
    return i >= cluster[0] and i <= cluster[1]

def display(points, clusters):
    cpt = 0
    # clust = clusters[cpt]
    color = (random.uniform(0, 1), random.uniform(0, 1), random.uniform(0, 1))
    fig = plt.figure()
    ax = fig.add_subplot(111)
    for i,p in enumerate(points):
        if(not belongs(i, clusters[cpt]) ):
            cpt += 1
            color = (random.uniform(0, 1), random.uniform(0, 1), random.uniform(0, 1))
        ax.scatter(p[0], p[1], c=color)
    # plt.plot(xlist, ylist, 'k.')
    plt.show()
    
filename_points = "dataAlea_100_100_100_ex0.txt"
filename_results = "dataAlea_100_100_100_ex0_result.txt"
points = get_points(filename_points)
clusters = get_clusters(filename_results)
display(points, clusters)
