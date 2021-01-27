import matplotlib.pyplot as mpl

n = int(input())
graph = [list(map(int, input().split())) for _ in range(n)]
*perm, = map(int, input().split())

mpl.plot(
    [graph[x][0] for x in perm] +
    [graph[perm[0]][0]],
    [graph[y][1] for y in perm] +
    [graph[perm[0]][1]],
    color='orange',
    linewidth=3,
    marker='o',
    markerfacecolor='red',
    markersize=12
)
mpl.xlim(min([x[0] for x in graph]) - 1, max([x[0] for x in graph]) + 1)
mpl.ylim(min([x[1] for x in graph]) - 1, max([x[1] for x in graph]) + 1)
mpl.title('G R A P H')
mpl.show()
