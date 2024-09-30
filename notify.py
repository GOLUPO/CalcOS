# notify.py
from PyQt5.QtWidgets import QMainWindow, QWidget, QVBoxLayout, QLabel

class NotifyApp(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('Notifiche')
        self.setGeometry(100, 100, 300, 400)
        self.initUI()

    def initUI(self):
        # Widget centrale
        central_widget = QWidget()
        self.setCentralWidget(central_widget)

        # Layout principale
        layout = QVBoxLayout()
        central_widget.setLayout(layout)

        # Lista delle notifiche
        notifications = ['Notifica 1', 'Notifica 2', 'Notifica 3']
        for notif in notifications:
            label = QLabel(notif)
            layout.addWidget(label)
