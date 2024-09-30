# app.py
from PyQt5.QtWidgets import QMainWindow
from PyQt5.QtWebEngineWidgets import QWebEngineView
from PyQt5.QtCore import QUrl
import os

class App(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('App HTML')
        self.setGeometry(100, 100, 300, 400)
        self.initUI()

    def initUI(self):
        self.browser = QWebEngineView()
        self.setCentralWidget(self.browser)
        # Assicurati di specificare il percorso corretto del file HTML
        app_html_path = os.path.abspath('app.html')
        self.browser.load(QUrl.fromLocalFile(app_html_path))
