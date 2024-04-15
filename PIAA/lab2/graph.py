from PIAA_2_2 import *
import graphviz


def showing(list):
    graph = graphviz.Digraph()
    for key in list:
        graph.node(str(key))
        for i in range(len(list[key])):
            if str(key) != str(list[key][i][0]):
                graph.edge(str(key), str(list[key][i][0]), str(list[key][i][1]))

    name = 'graph'
    graph.render(name)


def main():
    start, end, nodes = my_input()
    showing(nodes)


if __name__ == '__main__':
    main()
