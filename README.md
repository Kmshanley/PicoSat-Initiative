# PicoSat-Initiative
![](/Docs/Assets/picosat-03-trans.png)
The Wentworth Picosat initiative is a group at Wentworth Institute of technology dedicated to making a pocket cube satellite capable of earth observation from LEO.

The pocket cube standard requires satellites to be 5x5x5cm and under 250 grams. Upon completion of this Wentworth PicoSat it will become one of the smallest satellites capable of high resolution imagery from LEO.

* **Homepage:** <https://picosat.notion.site>
* **Communication:** <https://discord.gg/C9kFq642a>

Organization
------------------------
This repository is divided into two primary sections:
### Test
> Contains all firmware related to testing boards or individual components.
### Flight
> Contains the development for the main flight firmware that will be deployed in space.

Getting Started
------------------------
The easiest way to get started is by using the Stm32CubeIDE.

Downloadable here: https://www.st.com/en/development-tools/stm32cubeide.html

From here you should be able to import the various project files (.ioc) and CubeIDE will handle setup, build tools, and compilation.

High Level Overview
------------------------
![Exploded and Annotated Render of the Satellite's Internal Stack](/Docs/Assets/ExplodedRender_Annotated.png)

The Satellite is composed of several **subsystems**:

* Onboard Computer System (OBC)
    * Responsible for handling commands from the ground station
    * Running ADCS algorithms
    * Commanding the image sensor to take pictures
        * Compressing and Storing these pictures until downlink
    * Gathering telemetry from sensors
        * Feeding telemetry to the appropriate subsystem
            * I.e. LUX sensor data to ADCS
    * Managing Satellite Energy consumption
        * Monitoring battery health and determining wakeup periods
* Electrical Power System (EPS)
    * Responsible for generating, storing, and regulating electrical power
* Communications (COMMS)
    * Responsible for uplink and downlink to ground station 
* Attitude Control and determination (ADCS)
    * Responsible for determining the attitude (rotation) of the satellite
    * Responsible for executing rotational maneuvers


Hardware Overview
------------------------
![System diagram of all satellite components](/Docs/Assets/Digital%20Block%20Diagram.png)

Contact
------------------------
You can join our discord with the link above or contact us directly via email:

OBC Team Lead (Kieran Shanley): <kmshanley01@gmail.com>