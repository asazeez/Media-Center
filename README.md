# Media Center Application
Media center application final projected completed for COE 718 (Embedded Systems design).
## Abstract
The media center that was developed for this project is comprised of several subsystems (written in C programming) which utilize the MCB1700 boards instruments. The center's features are a photo gallery, an MP3 player that plays audio from the PC, and a game center for flappy bird and tic tac toe. Each of these features use the LCD for the user interface and joystick for navigation. This media center was designed and implemented using the concepts that were studied and practiced regarding embedded system design. 

## Design
### Main Menu
The main menu is used to display the main features of the media center: photo gallery, MP3 player, and game center. The user is able to scroll through each option by moving the joystick up and down and using the select button to select an option. 
![IMG-0493 (1)](https://github.com/user-attachments/assets/85283336-8c59-4b96-b797-3b244516902d)

### Photo Gallery
The photo gallery is designed to display images to the user in a carousel format. To allow this slideshow format to be scrollable, the function reads in the joystick movement and displays the image accordingly.The image is drawn on the LCD using the GLCD_Bitmap() function.
![IMG-0495 (1)](https://github.com/user-attachments/assets/26432a84-3399-4672-acf3-9dc1ac213fce) 

### Game
The flappy bird game is designed to follow the original rules of the game. The tubes were drawn and erased on the screen using GLCD_DisplayChar().
![IMG-0500 (1)](https://github.com/user-attachments/assets/4488879e-beb9-4a56-8234-0c69b9e2d317)

### MP3 Player
The MP3 player module connects the USB audio driver to the PC to be an audio output device. It initializes the hardware for the audio system. It sets up the ADC for reading the potentiometer for controlling the volume and DAC for the audio output. There is also a timer configured to generate periodic interrupts for audio processing with the TIMER0_IRQHandler() interrupt service routine used for processing audio data, adjusting volume, and managing audio playback.
![IMG-0503 (1)](https://github.com/user-attachments/assets/868dc56a-f146-41e9-a419-f6211604bf66)

Through the diverse features that were created for this media center, the project provided great experience in designing embedded systems. 
