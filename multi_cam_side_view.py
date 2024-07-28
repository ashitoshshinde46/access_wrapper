import sys
import cv2
import json
from PyQt5.QtWidgets import QApplication, QMainWindow, QLabel, QPushButton,QComboBox, QHBoxLayout,QVBoxLayout, QWidget,QGridLayout,QScrollArea
from PyQt5.QtCore import QTimer
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QPixmap, QImage 
import datetime
import os

class MultiCameraViewer(QMainWindow):
    def __init__(self):
        super().__init__()
        self.config={}
        self.loadConfig()
        self.setWindowTitle("Winch Camera")
        self.setGeometry(1660, 1, 444,850)
        self.setFixedWidth(390)
        self.setFixedHeight(870)
        self.setWindowFlag(Qt.FramelessWindowHint)

        self.setStyleSheet("""
            QMainWindow {
                background-color: rgb(87, 86, 87) ;
                font-size: 18px;
            }
            QPushButton {
                background-color: rgb(140, 174, 179) ;
                color: black;
                border: 1px solid black;
                border-radius: 1px;
            }
                           
            QPushButton:hover {
                background-color: skyblue;
            }
            QLabel{
                color: green;        
            }
        """)

        self.video_path=self.config["video_path"]
        self.num_cameras =[]
        self.getCameraPath()
        #comment this line in deployment
        self.num_cameras = ["/mnt/f/home_camera/captured_video_16_03_2023.mp4","/mnt/f/home_camera/captured_video17_03_2023.mp4","/mnt/f/home_camera/IMG_2377_.mp4"]
        self.checkCamDir(len(self.num_cameras))
        self.video_captures = [cv2.VideoCapture(i) for i in self.num_cameras]

        self.zoom_factor = 1.0

        self.scroll_cam = 0
        self.central_widget = QWidget(self)
        self.setCentralWidget(self.central_widget)

        self.scrollArea = QScrollArea()
        self.main_video_label = QLabel(self)
        self.main_video_label.setAlignment(Qt.AlignCenter)
        # self.main_video_label.setStyleSheet("border: 2px solid black;")
        text_cam_label=QLabel(f"Single Camera View")
        text_cam_label.setStyleSheet("color: green;font-size: 28px;")
        self.cb = QComboBox()
        self.cb.setFixedSize(100, 40)
        self.cb.setStyleSheet("""background-color: rgb(140, 174, 179) ;
                color: black;
                border: 1px solid black;
                border-radius: 1px;""")
        self.cb.addItems(["Cam 1", "Cam 2", "Cam 3"])
        self.cb.currentIndexChanged.connect(self.selectionchange)
        
        self.scroll = QScrollArea()
        self.scroll.setWidgetResizable(True)
        self.scroll_widget = QWidget()
        self.scroll_layout = QVBoxLayout( self.scroll_widget)
        self.scroll_layout.addWidget(text_cam_label)
        self.scroll_layout.addWidget(self.cb)
        self.scroll_layout.addWidget(self.main_video_label)
        self.scroll.setWidget(self.scroll_widget)
        self.scroll_widget.mousePressEvent = self.on_mouse_press_scroll
        self.scroll.setStyleSheet("background-color: rgb(87, 86, 87)")

       

        self.video_labels = [QLabel(self) for _ in range(len(self.num_cameras))]
        for i, label in enumerate(self.video_labels):
            label.setAlignment(Qt.AlignCenter)
            label.setStyleSheet("border: 1px solid black;")
            
        self.button_layout=QHBoxLayout()
        self.record_button = QPushButton("Record", self)
        self.record_button.setFixedSize(100, 40)
        self.record_button.clicked.connect(self.toggle_recording)


        self.expand_view_button = QPushButton("Expand", self)
        self.expand_view_button.setFixedSize(100, 40)
        self.expand_view_button.clicked.connect(self.expandView)

        
        self.button_layout.addWidget(self.expand_view_button)
        self.button_layout.addWidget(self.record_button)


        self.layout=QHBoxLayout(self.central_widget)
        layout_1 = QVBoxLayout()
        layout_1.setSpacing(5)
        layout_1.setContentsMargins(0, 0, 0, 0)
        text_cam_label=QLabel(f"All Camera View")
        text_cam_label.setStyleSheet("color: green;font-size: 28px;")
        layout_1.addWidget(text_cam_label,alignment=Qt.AlignCenter)
        layout_1.addLayout(self.button_layout)
        for i,label in enumerate(self.video_labels):
            text_label=QLabel(f"Camera_{i}")
            layout_1.addWidget(text_label,alignment=Qt.AlignCenter)
            layout_1.addWidget(label)
            # self.scrollArea.setWidget(label)
        # layout_2 = QVBoxLayout()
        # layout_2.addWidget(self.cb)
        self.scroll.show()
        self.layout.addWidget(self.scroll)
        
        self.layout.addLayout(layout_1)
        self.layout.setSpacing(0)
        self.layout.setContentsMargins(0, 0, 0, 0)
        # layout.addLayout(layout_2)
        # self.scrollArea.setLayout(layout_1)
        self.central_widget.setLayout(self.layout)

        self.timer = QTimer(self)
        self.timer.timeout.connect(self.update_frames)
        self.timer.start(10)  # Update frames every 30 milliseconds

        self.is_recording = False
        self.is_expand = False
        self.video_writers = [None] * len(self.num_cameras)
        self.showMaximized()
        self.expand_view_button.click()

    def update_frames(self):
        for i, video_capture in enumerate(self.video_captures):
            ret, frame = video_capture.read()
            if ret:    
                frame = self.zoom_frame(frame)
                self.display_frame(frame, i)
                if self.scroll_cam==i:
                    self.display_main_frame(frame)
                if self.is_recording:
                    self.video_writers[i].write(frame)

    def zoom_frame(self, frame): 
        height, width, _ = frame.shape
        new_height, new_width = int(height * self.zoom_factor), int(width * self.zoom_factor)
        # new_height, new_width = int(height * 0.5), int(width * 0.5)
        resized_frame = cv2.resize(frame, (new_width, new_height))
        return resized_frame

    def resize_thumbnail_frame(self, frame):
        height, width, _ = frame.shape
        # new_height, new_width = int(height * self.zoom_factor), int(width * self.zoom_factor)
        new_height, new_width = 48*5, 64*6
        resized_frame = cv2.resize(frame, (new_width, new_height))
        return resized_frame
        
    def on_mouse_press_scroll(self, event):
        if event.button() == Qt.LeftButton:
            # print('Left mouse button clicked')
            if (self.zoom_factor<2):
                self.zoom_factor+=0.5
        elif event.button() == Qt.RightButton:
            # print('Right mouse button clicked')
            if (self.zoom_factor>1):
                self.zoom_factor-=0.5
        
    def display_frame(self, frame, index):
        frame=self.resize_thumbnail_frame(frame)
        rgb_image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        qt_image = QImage(rgb_image.data, rgb_image.shape[1], rgb_image.shape[0], QImage.Format_RGB888)
        self.video_labels[index].setPixmap(QPixmap.fromImage(qt_image))

    def display_main_frame(self, frame):
        rgb_image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        qt_image = QImage(rgb_image.data, rgb_image.shape[1], rgb_image.shape[0], QImage.Format_RGB888)
        self.main_video_label.setPixmap(QPixmap.fromImage(qt_image))

    def selectionchange(self,i):
        self.scroll_cam=i

    def checkVideoDir(self,current_time,camera_number):
        month=current_time.month
        year=current_time.year
        if not os.path.exists(self.video_path+"cam_"+str(camera_number)+"/"+str(month)+"_"+str(year)):
            os.mkdir(self.video_path+"cam_"+str(camera_number)+"/"+str(month)+"_"+str(year))
	
    def checkCamDir(self,no_cameras):
        for i in range(no_cameras):
            if not os.path.exists(self.video_path+"cam_"+str(i)):
                os.mkdir(self.video_path+"cam_"+str(i))
	

    def toggle_recording(self):
        if not self.is_recording:
            fourcc = cv2.VideoWriter_fourcc(*"XVID")
            current_time = datetime.datetime.now()
            month=current_time.month
            year=current_time.year
            vid_name=current_time.strftime("%d_%m_%Y-%H_%M_%S")
            print("date:",vid_name)
            for i in range(len(self.num_cameras)):
                self.checkVideoDir(current_time,i)
                recording_path=self.video_path+"cam_"+str(i)+"/"+str(month)+"_"+str(year)+"/cam_"+str(i)+"_"+vid_name+".avi"
                print(f"Recording path cam{i}:",recording_path)
                self.video_writers[i] = cv2.VideoWriter(recording_path, fourcc, 20.0, (640, 480))
            self.is_recording = True
            self.record_button.setText("Stop Recording")
            for i, label in enumerate(self.video_labels):
                label.setAlignment(Qt.AlignCenter)
                label.setStyleSheet("border: 1px solid red;")
        else:
            for writer in self.video_writers:
                writer.release()
            self.is_recording = False
            self.record_button.setText("Record")
            for i, label in enumerate(self.video_labels):
                label.setAlignment(Qt.AlignCenter)
                label.setStyleSheet("border: 1px solid balck;")

    def expandView(self):
        if not self.is_expand:
            self.setGeometry(750, 1, 444,850)
            self.setFixedWidth(1200)
            self.setFixedHeight(870)
            self.scroll.show()
            self.is_expand = True
            self.expand_view_button.setText("Collapse")
        else:
            self.is_expand = False
            self.expand_view_button.setText("Expand")
            self.scroll.hide()
            self.setGeometry(1560, 1, 444,850)
            self.setFixedWidth(390)
            self.setFixedHeight(870)
            

    def closeEvent(self, event):
        for video_capture in self.video_captures:
            video_capture.release()
        if self.is_recording:
            for writer in self.video_writers:
                writer.release()
        super().closeEvent(event)

    def loadConfig(self):
        try:
            with open("config.json", "r") as f:
                self.config = json.load(f)
        except Exception as e:
            print("EXception in load config:",e)

    def getCameraPath(self):
        for i in range(3):
            camera="http://"+self.config["ip_address"]+":"+self.config["cam_"+str(i)+"_port"]+"/camera_"+str(i)
            print(f"camera source {i}:",camera)
            self.num_cameras.append(camera)
        
if __name__ == "__main__":
    app = QApplication(sys.argv)
    viewer = MultiCameraViewer()
    viewer.show()
    sys.exit(app.exec_())
