# import libraries
from vidgear.gears import NetGear
from vidgear.gears import CamGear
import threading
import cv2

CAM_ID_1="/mnt/f/home_camera/captured_video_16_03_2023.mp4"
CAM_ID_2="/mnt/f/home_camera/captured_video17_03_2023.mp4"
CAM_ID_3="/mnt/f/home_camera/IMG_2377_.mp4"


# activate multiserver_mode
options = {"multiserver_mode": True,"jpeg_compression": True,
    "jpeg_compression_quality": 90,
    "jpeg_compression_fastdct": True,
    "jpeg_compression_fastupsample": True,}

# Open suitable video stream (webcam on first index in our case)
stream_1 = CamGear(source=CAM_ID_1).start()

# Define NetGear Server at Client's IP address and assign a unique port address and other parameters
# !!! change following IP address '192.168.x.xxx' with yours !!!
server_1 = NetGear(
    address="172.23.98.89", port="5566", protocol="tcp", pattern=1, **options
)

stream_2 = CamGear(source=CAM_ID_2).start()

# Define NetGear Server at Client's IP address and assign a unique port address and other parameters
# !!! change following IP address '192.168.x.xxx' with yours !!!
server_2 = NetGear(
    address="172.23.98.89", port="5567", protocol="tcp", pattern=1, **options
)

stream_3 = CamGear(source=CAM_ID_3).start()

# Define NetGear Server at Client's IP address and assign a unique port address and other parameters
# !!! change following IP address '192.168.x.xxx' with yours !!!
server_3 = NetGear(
    address="172.23.98.89", port="5568", protocol="tcp", pattern=1, **options
)


def stream_frames(stream, server):
# loop over until Keyboard Interrupted
    while True:
    
        try:
            # read frames from stream
            frame = stream.read()
    
            # check for frame if not None-type
            if frame is None:
                break
    
            # {do something with the frame here}
            frame=cv2.resize(frame, (640, 480), interpolation=cv2.INTER_LINEAR) 
            # send frame to server
            server.send(frame)
    
        except KeyboardInterrupt:
            break
    
    
# Start threads for streaming from each camera
thread0 = threading.Thread(target=stream_frames, args=(stream_1, server_1))
thread1 = threading.Thread(target=stream_frames, args=(stream_2, server_2))
thread2 = threading.Thread(target=stream_frames, args=(stream_3, server_3))

thread0.start()
thread1.start()
thread2.start()

# Wait for threads to finish (you can add more logic here if needed)
thread0.join()
thread1.join()
thread2.join()

# safely close video stream

stream_1.stop()
stream_2.stop()
stream_3.stop()

# safely close server
server_1.close()
server_2.close()
server_3.close()
