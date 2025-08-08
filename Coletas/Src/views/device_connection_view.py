import os
from typing import Dict

class DeviceConnectionView:
    def connecting_view(self):
        #os.system('cls||clear')

        print('Conectando...')
    
    def connected_view(self, response:Dict):
        #os.system('cls||clear')


        print(f'Conectado na porta {response['port']}')
        
    def unconnected_view(self):
        #os.system('cls||clear')

        print('Falha na conexão.')
