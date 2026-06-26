import serial 
import serial.tools.list_ports
import time

class DeviceConnectionController:
    def __init__(self, baudrate=115200, timeout=1):
        self.baudrate = baudrate
        self.timeout = timeout
        self.serial_conn = None
        self.port = None

    def find_bluetooth_port(self):
        ports = serial.tools.list_ports.comports()
        if not ports:
            #print("Nenhuma porta serial encontrada.")
            return {"success": False}
        for port in ports:
            try:
                if port.device=="COM5":
                    if "Bluetooth" in port.description or "Bluetooth" in port.hwid:
                        #print(f"Tentando abrir a porta {port.device}...")
                    # Tenta abrir a porta serial
                        with serial.Serial(port=port.device, baudrate=115200, timeout=1, write_timeout=2, rtscts=False, dsrdtr=False) as ser:
                            if ser.is_open:
                                #print(f"Porta {port.device} aberta com sucesso.")
                                for i in range(10):  # Até 10 tentativas de teste de conexão
                                    test = self.test_connection(ser)
                                    if test["success"]:
                                        #print(f"Conexão bem-sucedida na porta {port.device}.")
                                        self.port = port.device  # Define self.port corretamente
                                        return {"success": True, "port": port.device}
                                    time.sleep(0.5)  # Pequena pausa entre tentativas
                                print(f"Conexão não estabelecida na porta {port.device}.")
            except serial.SerialException as e:
                print(f"Erro ao acessar a porta {port.device}: {e}")
            except Exception as e:
                print(f"Erro inesperado na porta {port.device}: {e}")
        return {"success": False}

    
    def test_connection(self, ser):
        try:
        # Envia o comando de teste
            ser.write(b'Ping\n')
            line = ser.readline().decode('utf-8').strip()
            #print(f"Recebido: {line}")
            if line == 'Pong':
                return {"success": True}
        except Exception as e:
            print(f"Erro em test_connection: {e}")
            return {"success": False, "error": str(e)}
        # Retorno padrão se a resposta não for "Pong"
        return {"success": False, "error": "Resposta inesperada ou vazia."}

    def connect(self):
        if self.port == None:
            return {"success": False, "error": "Nenhuma porta Bluetooth válida encontrada."}
        try:
            #print(f'Conectando a {self.port}')
            ser = serial.Serial(port=self.port, baudrate=self.baudrate, timeout=self.timeout, write_timeout=2)
            #print(f'Conexão bem-sucedida na porta {self.port}.')
            test = self.test_connection(ser)
            if test["success"]:
                self.serial_conn = ser
                return {"success": True, "port": self.port}
        except Exception as e:
            return {"success": False, "error": str(e)}
        return {"success": False}
    
    def disconnect(self):
        self.serial_conn.close()

    def send_data(self, data):
        if isinstance(data, (int, float)):
            data = str(data)
        if isinstance(data, str):
            self.serial_conn.write(data.encode() + b'\n') 
            return {"success": True, "data": data}
        return {"success": False}

    def read_data(self):
        line = self.serial_conn.readline().decode('utf-8').strip()
        #print(f"Recebido: {line}")
        return line
  