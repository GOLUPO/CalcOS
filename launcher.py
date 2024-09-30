# launcher.py
from PyQt5.QtWidgets import QMainWindow, QWidget, QVBoxLayout, QPushButton

class LauncherApp(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('Launcher')
        self.setGeometry(100, 100, 300, 400)
        self.initUI()

    def initUI(self):
        # Widget centrale
        central_widget = QWidget()
        self.setCentralWidget(central_widget)

        # Layout principale
        layout = QVBoxLayout()
        central_widget.setLayout(layout)

        # Pulsanti delle app
        apps = ['Calcolatrice', 'Control Panel', 'Notifiche', 'App HTML']
        for app_name in apps:
            button = QPushButton(app_name)
            button.clicked.connect(self.open_app)
            layout.addWidget(button)

    def open_app(self):
        sender = self.sender()
        app_name = sender.text()
        if app_name == 'Calcolatrice':
            import Calculator
            self.app = Calculator.CalculatorApp()
        elif app_name == 'Control Panel':
            import control_panel
            self.app = control_panel.ControlPanelApp()
        elif app_name == 'Notifiche':
            import notify
            self.app = notify.NotifyApp()
        else:
            import app
            self.app = app.App()
        self.app.show()
        self.close()
