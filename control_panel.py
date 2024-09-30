# control_panel.py
from PyQt5.QtWidgets import QMainWindow, QWidget, QVBoxLayout, QLabel, QSlider, QPushButton

class ControlPanelApp(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('Control Panel')
        self.setGeometry(100, 100, 300, 400)
        self.initUI()

    def initUI(self):
        # Widget centrale
        central_widget = QWidget()
        self.setCentralWidget(central_widget)

        # Layout principale
        layout = QVBoxLayout()
        central_widget.setLayout(layout)

        # Luminosità
        brightness_label = QLabel('Luminosità')
        layout.addWidget(brightness_label)
        brightness_slider = QSlider()
        brightness_slider.setOrientation(Qt.Horizontal)
        layout.addWidget(brightness_slider)

        # Volume
        volume_label = QLabel('Volume')
        layout.addWidget(volume_label)
        volume_slider = QSlider()
        volume_slider.setOrientation(Qt.Horizontal)
        layout.addWidget(volume_slider)

        # Modalità silenziosa
        silent_button = QPushButton('Modalità Silenziosa')
        layout.addWidget(silent_button)

        # Batteria
        battery_label = QLabel('Batteria: 100%')
        layout.addWidget(battery_label)
