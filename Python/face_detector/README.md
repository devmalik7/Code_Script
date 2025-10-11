# Real-Time Face Detection with OpenCV Haar cascades

## Description
This Python script captures video from a webcam and performs real-time face detection using OpenCV’s built-in Haar cascades.  
Key features include:  
- Detection of multiple faces per frame.  
- Smoothing of face positions using Exponential Moving Average (EMA) to reduce jitter.  
- Dynamic scaling of label text based on the detected face size.  
- Drawing bounding boxes around detected faces.  
- Display of FPS (Frames Per Second) to monitor processing speed.  

All detection and display parameters are fully configurable via constants at the top of the script.  
This includes:  
- Camera source index (`CAMERA_SOURCE`)  
- Haar cascade parameters (`FD_SCALE_FACTOR`, `FD_MIN_NEIGHBORS`)  
- Face box appearance (`FACEBOX_COLOR`, `FACEBOX_THICKNESS`)  
- Label text settings (`TEXT_FONT`, `TEXT_DEFAULT_SIZE`, `TEXT_COEFF`, `TEXT_MARGIN`)  
- Smoothing parameters (`SMOOTH_ALPHA`, `SMOOTH_THRESHOLD`)  
- Matching distance for tracking faces (`MATCH_MAX_DISTANCE`)  
- FPS display settings (`FPS_COLOR`, `FPS_FONT_SCALE`, `FPS_POSITION`, `FPS_FONT`)  

This makes it easy to tweak the behavior and appearance of the face detection system without modifying the core logic.

## Installation
1. Make sure you have Python 3.10 or higher installed.
2. Clone or download this repository.
3. Install required dependencies using the `requirements.txt` file:
    ```bash
   pip install -r requirements.txt
    ````

## How to Run

1. Connect a webcam or ensure your camera source is available.
2. Run the script:

    ```bash
    python main.py
    ```
3. A window will open showing the live video feed. Detected faces will have rectangles and labels.
4. Press `q` to exit the video window.