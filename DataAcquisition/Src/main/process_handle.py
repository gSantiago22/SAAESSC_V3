from .constructor.introduction_process import introduction_process
from .constructor.device_connection_constructor import device_connection_constructor
from .constructor.data_visualization_constructor import data_visualization_constructor

def start() -> None:
    while True:
        command = introduction_process()

        if command == '1': device_connection_constructor()
        elif command == '2': 
            data_visualization_constructor()
        elif command == '5': exit()
        else: print('\n Comando nao encontrado!! \n\n')