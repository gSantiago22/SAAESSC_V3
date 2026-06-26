import os

class DataVisualizationController():
    def __init__(self, device_conn):
        self.device_conn = device_conn
        self.file_path = None
        self.file = None
    
    def create_file(self, base_name, path = "Assets/data", extension = ".txt"):
        destination_folder = os.path.abspath(path)    
        os.makedirs(destination_folder, exist_ok=True)
        file_path = os.path.join(destination_folder, base_name)
        
        counter = 0
        
        while True:
            if counter == 0:
                file_name = f"{file_path}{extension}"
            else:
                file_name = f"{file_path}_{counter}{extension}"
            
            if not os.path.exists(file_name):
                with open(file_name, "w") as file:
                    file.write("") 
                self.file_path = file_name 
                return file_name  
            counter += 1
    def write_file(self, data):
        try:
            data_w = f'{data["voltage"]} {data["current"]} {data["time"]}\n'
            self.file.write(data_w)
            return {"success": True}
        except:
            return {"success": False}


    def open_file(self):
        self.file = open(self.file_path, 'r+')
    
    def close_file(self):
        self.file.close()

    def plot_command(self):
        self.device_conn.send_data(1)

    def read_data(self):
        data = self.device_conn.read_data()
        if data:
            if data == "end":
                return {"test": False, "success": True}
            
            values = data.split()
            if len(values) == 3:
                return {"test": True, "success": True, "voltage": values[0], "current": values[1], "time": values[2]}
        return {"test": True, "success": False, "voltage": "", "current": "", "time": ""}