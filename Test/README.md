# Current Test Firmware

### devBoardTest
------------------------
Designed to test every component on the OBC-Proto board. Will conduct test I/O operations on external memory and poll every sensor on board. A successful pass on this program will validate that a OBC proto board has been manufactured correctly.
### picoSat_cameraTest
------------------------
Designed to test the use of a OV5640 camera module with a NUCLEO-H723ZG development board. This program will validate that the DCMI interface of the stm32h723 works with a OV5640
### picoSat_epsTest
------------------------
Designed to test all the digital sensors present on the EPS board. This program will validate that a EPS board has been manufactured correctly (or at least all the digital sensors).