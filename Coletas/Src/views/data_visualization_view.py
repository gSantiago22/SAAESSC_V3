import matplotlib.pyplot as plt
import matplotlib.animation as animation
import matplotlib

class DataVisualizationView():
    
    def __init__(self, file):
        self.fig = None
        self.graph = None
        self.interval = 1
        self.file = file
        self.time = []
        self.voltage = []
        self.current = []

    def create_figure(self):
        self.fig = plt.figure()
        self.graph = self.fig.add_subplot(111)
        pass
    def update_graph(self, i):
        self.file.seek(0)
        dados=self.file.read()
        linhas=dados.split("\n")
        for y in linhas:
            if len(y)>0:
                values = y.split()        
                self.voltage.append(float(values[0]))
                self.current.append(float(values[1]))
                self.time.append(float(values[2]))
        
        self.graph.cla()

        self.graph.plot(self.time, self.voltage, label='Channel 1')
        plt.plot(self.time, self.current, label='Channel 2')

        plt.legend(loc='upper left')
        plt.tight_layout()
        
        self.voltage.clear()
        self.current.clear()
        self.time.clear()


    def plot_figure(self):
        ani = animation.FuncAnimation(plt.gcf(), self.update_graph, frames=10, interval=1000)

        plt.tight_layout()
        plt.show()  