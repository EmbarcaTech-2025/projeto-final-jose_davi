import tkinter as tk
from tkinter import font
import paho.mqtt.client as mqtt
import json
import threading

MQTT_BROKER = "192.168.0.146" 
MQTT_PORT = 1883
MQTT_TOPIC = "bitdoglab/sensor_data"
MQTT_USERNAME = "interface"
MQTT_PASSWORD = "12345678"

class SensorDashboard(tk.Tk):
    def __init__(self):
        super().__init__()

        # Configurações da janela principal
        self.title("Dashboard de Sensores - EmbarcaTech")
        self.geometry("400x300")
        self.configure(bg="#2E2E2E")
        self.resizable(False, False)

        # Fontes personalizadas
        self.title_font = font.Font(family="Helvetica", size=18, weight="bold")
        self.label_font = font.Font(family="Helvetica", size=14)
        self.value_font = font.Font(family="Helvetica", size=20, weight="bold")

        # Variáveis de controle para os textos dos sensores
        self.temp_var = tk.StringVar(value="--.- °C")
        self.pressure_var = tk.StringVar(value="----.- hPa")
        self.humidity_var = tk.StringVar(value="--.- %")
        self.lux_var = tk.StringVar(value="---- lx")

        # Cria e posiciona os widgets na tela
        self._create_widgets()
        
        # Inicia o cliente MQTT em uma thread separada para não travar a UI
        self._start_mqtt_thread()

    def _create_widgets(self):
        """Cria e organiza os componentes da interface."""
        title_label = tk.Label(self, text="Monitoramento Ambiental", font=self.title_font, bg="#2E2E2E", fg="#FFFFFF")
        title_label.pack(pady=10)

        # Frame para organizar os sensores
        main_frame = tk.Frame(self, bg="#2E2E2E")
        main_frame.pack(pady=10, padx=20, fill="both", expand=True)

        # Nomes dos sensores (coluna 0)
        tk.Label(main_frame, text="🌡️ Temperatura:", font=self.label_font, bg="#2E2E2E", fg="#E0E0E0").grid(row=0, column=0, sticky="w", pady=5)
        tk.Label(main_frame, text="💨 Pressão:", font=self.label_font, bg="#2E2E2E", fg="#E0E0E0").grid(row=1, column=0, sticky="w", pady=5)
        tk.Label(main_frame, text="💧 Umidade:", font=self.label_font, bg="#2E2E2E", fg="#E0E0E0").grid(row=2, column=0, sticky="w", pady=5)
        tk.Label(main_frame, text="☀️ Luminosidade:", font=self.label_font, bg="#2E2E2E", fg="#E0E0E0").grid(row=3, column=0, sticky="w", pady=5)

        # Valores dos sensores (coluna 1)
        tk.Label(main_frame, textvariable=self.temp_var, font=self.value_font, bg="#2E2E2E", fg="#FFB347").grid(row=0, column=1, sticky="e", padx=10)
        tk.Label(main_frame, textvariable=self.pressure_var, font=self.value_font, bg="#2E2E2E", fg="#87CEEB").grid(row=1, column=1, sticky="e", padx=10)
        tk.Label(main_frame, textvariable=self.humidity_var, font=self.value_font, bg="#2E2E2E", fg="#77DD77").grid(row=2, column=1, sticky="e", padx=10)
        tk.Label(main_frame, textvariable=self.lux_var, font=self.value_font, bg="#2E2E2E", fg="#FDFD96").grid(row=3, column=1, sticky="e", padx=10)
        
        main_frame.columnconfigure(1, weight=1) 

    def on_message(self, client, userdata, message):
        try:
            # Decodifica o payload para string e o converte de JSON para um dicionário Python
            payload_str = message.payload.decode("utf-8")
            data = json.loads(payload_str)
            
            print(f"Dados recebidos: {data}")

            # Atualiza as variáveis da interface com os novos valores
            self.temp_var.set(f"{data.get('temperature', 0):.1f} °C")
            self.pressure_var.set(f"{data.get('pressure', 0) :.1f} kPa") 
            self.humidity_var.set(f"{data.get('humidity', 0):.1f} %")
            self.lux_var.set(f"{data.get('lux', 0):.0f} lx")

        except Exception as e:
            print(f"Erro ao processar mensagem: {e}")

    def _start_mqtt_thread(self):
        client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2, "python_dashboard_sub")
        client.on_connect = self.on_connect
        client.on_message = self.on_message

        client.username_pw_set(MQTT_USERNAME, MQTT_PASSWORD)
        
        try:
            client.connect(MQTT_BROKER, MQTT_PORT, 60)
            thread = threading.Thread(target=client.loop_forever)
            thread.daemon = True 
            thread.start()
        except Exception as e:
            print(f"Não foi possível conectar ao broker MQTT: {e}")
            self.temp_var.set("Erro de Conexão")


    def on_connect(self, client, userdata, flags, rc, properties=None):
        """Callback executado ao conectar-se ao broker."""
        if rc == 0:
            print(f"Conectado com sucesso ao broker MQTT! Assinando o tópico '{MQTT_TOPIC}'...")
            client.subscribe(MQTT_TOPIC)
        else:
            print(f"Falha na conexão, código de retorno: {rc}\n")


if __name__ == "__main__":
    app = SensorDashboard()
    app.mainloop()