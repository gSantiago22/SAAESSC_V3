from Src.views.data_visualization_view import DataVisualizationView
from Src.controllers.data_visualization_controller import DataVisualizationController
from ..constructor.device_connection_constructor import device_connection_constructor

def data_visualization_constructor():
    device_conn = device_connection_constructor()
    device_conn.connect()

    data_visualization_controller = DataVisualizationController(device_conn)
    
    data_visualization_controller.create_file("data")
    data_visualization_controller.open_file()
    file = data_visualization_controller.file
    data_visualization_view = DataVisualizationView(file)

    #data_visualization_view.create_figure()

    data_visualization_controller.plot_command()
    
    while (1):
        data = data_visualization_controller.read_data() 
        if data["test"] == True:
            #salva dados
            data_visualization_controller.write_file(data)
            print(f'{data["voltage"]} {data["current"]} {data["time"]}')
        elif data["test"] == False:
            break

    #data_visualization_view.plot_figure()
    device_conn.disconnect()
    data_visualization_controller.close_file()




